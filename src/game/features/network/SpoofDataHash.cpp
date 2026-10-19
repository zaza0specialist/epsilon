#include "core/commands/BoolCommand.hpp"
#include "core/commands/Command.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/Natives.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/game_files/CGameDataHash.hpp"

#include <nlohmann/json.hpp>
#include <fstream>

namespace YimMenu::Features
{
	class DumpDataHash : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto log = LOG(VERBOSE);
			log << "DLC Hash: "
			    << BaseHook::Get<Hooks::Network::GetDLCHash, DetourHook<decltype(&Hooks::Network::GetDLCHash)>>()->Original()(
			           *Pointers.DLCManager,
			           0)
			    << "\n";
			if (auto hashes = Pointers.GameDataHash)
			{
				log << "validHashes = {" << "\n";
				for (int i = 0; i < hashes->m_Data.size(); i++)
					log << hashes->m_Data[i].getData() << ", // " << i << "\n";
				log << "};";
			}
		}
	};
	static DumpDataHash _DumpDataHash{"dumpdatahash", "Dump Data Hash", "Dumps the current data hash into the console"};

	static std::filesystem::path GetCleanHashesPath()
	{
		return FileMgr::GetProjectFile("./cleanhashes.json").Path();
	}

	static uint32_t s_LearnedDlcHash = 0;
	static bool s_HasLearnedDlcHash = false;
	static void PackOrderHook(rage::scrNativeCallContext* ctx);

	class LearnCleanHashes : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!Pointers.GameDataHash || !Pointers.DLCManager)
			{
				Notifications::Show("Data Hash", "GameDataHash not available yet.", NotificationType::Error);
				return;
			}

			nlohmann::json j;
			j["dlcHash"] = BaseHook::Get<Hooks::Network::GetDLCHash, DetourHook<decltype(&Hooks::Network::GetDLCHash)>>()->Original()(*Pointers.DLCManager, 0);
			j["hashes"] = nlohmann::json::array();
			for (int i = 0; i < Pointers.GameDataHash->m_Data.size(); i++)
				j["hashes"].push_back(Pointers.GameDataHash->m_Data[i].getData());

			try
			{
				std::ofstream file(GetCleanHashesPath(), std::ios::trunc);
				file << j.dump(2);
				Notifications::Show("Data Hash", "Saved clean hashes. Enable Spoof Data Hash to use them.");
			}
			catch (const std::exception& e)
			{
				Notifications::Show("Data Hash", std::string("Failed to save: ") + e.what(), NotificationType::Error);
			}
		}
	};
	static LearnCleanHashes _LearnCleanHashes{"learncleanhashes", "Learn Clean Hashes", "Saves your current game data hash as the clean baseline. Run this once on a clean install."};

	class SpoofDataHash : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		std::array<std::uint32_t, 16> origHashes{};
		bool savedOrig = false;
		bool appliedLearned = false;

		virtual void OnEnable() override
		{
			NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::GET_EVER_HAD_BAD_PACK_ORDER, &PackOrderHook);

			appliedLearned = false;
			s_HasLearnedDlcHash = false;
			s_LearnedDlcHash = 0;

			try
			{
				auto path = GetCleanHashesPath();
				if (!std::filesystem::exists(path))
				{
					Notifications::Show("Data Hash", "No clean hashes learned yet - only pack order spoof active. Run Learn Clean Hashes on a clean game first.");
					return;
				}

				std::ifstream file(path);
				nlohmann::json j;
				file >> j;

				if (!j.contains("hashes") || !j["hashes"].is_array() || j["hashes"].size() < 16 || !Pointers.GameDataHash)
					return;

				if (!savedOrig)
				{
					for (int i = 0; i < Pointers.GameDataHash->m_Data.size(); i++)
						origHashes[i] = Pointers.GameDataHash->m_Data[i].getData();
					savedOrig = true;
				}

				for (int i = 0; i < 16; i++)
					Pointers.GameDataHash->m_Data[i] = j["hashes"][i].get<std::uint32_t>();

				if (j.contains("dlcHash") && j["dlcHash"].is_number_unsigned())
				{
					s_LearnedDlcHash = j["dlcHash"].get<std::uint32_t>();
					s_HasLearnedDlcHash = true;
				}

				appliedLearned = true;
			}
			catch (const std::exception&)
			{
				// keep pack-order-only spoof
			}
		}

		virtual void OnDisable() override
		{
			if (appliedLearned && savedOrig && Pointers.GameDataHash)
			{
				for (int i = 0; i < origHashes.size(); i++)
					Pointers.GameDataHash->m_Data[i] = origHashes[i];
			}
			appliedLearned = false;
			s_HasLearnedDlcHash = false;
		}
	};

	static SpoofDataHash _SpoofDataHash{"spoofdatahash", "Spoof Data Hash", "Spoofs game data hash so you can join players with rpf mods. Requires Learn Clean Hashes first."};

	static void PackOrderHook(rage::scrNativeCallContext* ctx)
	{
		return ctx->SetReturnValue(FALSE);
	}
}

namespace YimMenu::Hooks
{
	uint32_t Network::GetDLCHash(void* manager, uint32_t seed)
	{
		if (YimMenu::Features::_SpoofDataHash.GetState() && YimMenu::Features::s_HasLearnedDlcHash)
			return YimMenu::Features::s_LearnedDlcHash;

		return BaseHook::Get<Network::GetDLCHash, DetourHook<decltype(&Network::GetDLCHash)>>()->Original()(manager, seed);
	}
}
