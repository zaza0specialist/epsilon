#include "Network.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Protections.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/frontend/submenus/Network/SavedPlayers.hpp"
#include "game/frontend/submenus/Network/RandomEvents.hpp"
#include "game/gta/Network.hpp"
#include <chrono>

namespace YimMenu::Submenus
{
	Network::Network() :
		#define ICON_FA_ROUTE "\xef\x9b\xbf"
	    Submenu::Submenu("Network", ICON_FA_ROUTE)
	{
		// TODO: this needs a rework
		auto session = std::make_shared<Category>("Session");
		auto joinGroup = std::make_shared<Group>("Join");
		auto toxicGroup = std::make_shared<Group>("Toxic");
		auto teleportGroup = std::make_shared<Group>("Teleport");
		auto trollGroup = std::make_shared<Group>("Troll");
		auto miscGroup = std::make_shared<Group>("Misc");
		auto enhancements = std::make_shared<Group>("Enhancements");

		auto joinSession = std::make_shared<Group>("", 1);
		joinSession->AddItem(std::make_shared<ListCommandItem>("joinsessiontype"_J, "Session Type"));
		joinSession->AddItem(std::make_shared<CommandItem>("joinsession"_J, "Join##session"));

		joinGroup->AddItem(joinSession);
		joinGroup->AddItem(std::make_shared<ImGuiItem>([] {
			static std::uint64_t rockstar_id{};
			static char name_buf[24]{};

			ImGui::SetNextItemWidth(150.0f);
			ImGui::InputText("Username", name_buf, sizeof(name_buf));
			ImGui::SameLine();
			if (ImGui::Button("Join##username"))
				FiberPool::Push([] {
					auto rid = YimMenu::Network::ResolveRockstarId(name_buf);
					if (rid)
					{
						YimMenu::Network::JoinRockstarId(*rid);
					}
					else
					{
						Notifications::Show("Joiner", "Failed to get RID from username", NotificationType::Error);
					}
				});

			ImGui::SetNextItemWidth(150.0f);
			ImGui::InputScalar("Rockstar Id", ImGuiDataType_U64, &rockstar_id);
			ImGui::SameLine();
			if (ImGui::Button("Join##rid"))
				FiberPool::Push([] {
					YimMenu::Network::JoinRockstarId(rockstar_id);
				});
		}));

		auto customPlayerTp = std::make_shared<Group>("", 1);
		customPlayerTp->AddItem(std::make_shared<Vector3CommandItem>("playertpcoord"_J, ""));
		customPlayerTp->AddItem(std::make_shared<CommandItem>("tpplayertocoordall"_J, "Teleport Everyone"));
		teleportGroup->AddItem(customPlayerTp);
		teleportGroup->AddItem(std::make_shared<CommandItem>("bringall"_J, "Bring All"));

		trollGroup->AddItem(std::make_shared<BoolCommandItem>("harassplayers"_J));
		trollGroup->AddItem(std::make_shared<BoolCommandItem>("spamkillfeed"_J));
		trollGroup->AddItem(std::make_shared<CommandItem>("deletevehall"_J, "Delete Player Vehicles"));

		toxicGroup->AddItem(std::make_shared<CommandItem>("killall"_J, "Kill All"));
		toxicGroup->AddItem(std::make_shared<CommandItem>("explodeall"_J, "Explode All"));

		miscGroup->AddItem(std::make_shared<BoolCommandItem>("forcethunder"_J));

		enhancements->AddItem(std::make_shared<BoolCommandItem>("notifyonplayerjoin"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("fastjoin"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("disabledeathbarriers"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("despawnbypass"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("bypasscasinogeoblock"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("forcescripthost"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("pausegame"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("nocalls"_J));

		session->AddItem(joinGroup);
		session->AddItem(trollGroup);
		session->AddItem(teleportGroup);
		session->AddItem(toxicGroup);
		session->AddItem(miscGroup);
		session->AddItem(enhancements);

		auto spoofing = std::make_shared<Category>("Spoofing");
		auto matchmakingGroup = std::make_shared<Group>("Matchmaking (Client)");
		matchmakingGroup->AddItem(std::make_shared<BoolCommandItem>("cheaterpool"_J));
		auto spoofMMRegion = std::make_shared<Group>("", 1);
		spoofMMRegion->AddItem(std::make_shared<BoolCommandItem>("spoofmmregion"_J, "Spoof Region"));
		spoofMMRegion->AddItem(std::make_shared<ConditionalItem>("spoofmmregion"_J, std::make_shared<ListCommandItem>("mmregion"_J, "##mmregion")));
		matchmakingGroup->AddItem(std::make_shared<ConditionalItem>("cheaterpool"_J, spoofMMRegion, true));
		matchmakingGroup->AddItem(std::make_shared<BoolCommandItem>("spoofdatahash"_J));
		matchmakingGroup->AddItem(std::make_shared<CommandItem>("learncleanhashes"_J));
		spoofing->AddItem(matchmakingGroup);

		auto matchmakingSrvGroup = std::make_shared<Group>("Matchmaking (Server)");
		auto srvSpoofRegion = std::make_shared<Group>("", 1);
		srvSpoofRegion->AddItem(std::make_shared<BoolCommandItem>("mmspoofregiontype"_J));
		srvSpoofRegion->AddItem(std::make_shared<ConditionalItem>("mmspoofregiontype"_J, std::make_shared<ListCommandItem>("mmregiontype"_J, "##mmregiontype")));
		auto srvSpoofLanguage = std::make_shared<Group>("", 1);
		srvSpoofLanguage->AddItem(std::make_shared<BoolCommandItem>("mmspooflanguage"_J));
		srvSpoofLanguage->AddItem(std::make_shared<ConditionalItem>("mmspooflanguage"_J, std::make_shared<ListCommandItem>("mmlanguage"_J, "##mmlanguage")));
		auto srvSpoofPlayerCount = std::make_shared<Group>("", 1);
		srvSpoofPlayerCount->AddItem(std::make_shared<BoolCommandItem>("mmspoofplayercount"_J));
		srvSpoofPlayerCount->AddItem(std::make_shared<ConditionalItem>("mmspoofplayercount"_J, std::make_shared<IntCommandItem>("mmplayercount"_J, "##mmplayercount")));
		auto srvMultiplex = std::make_shared<Group>("", 1);
		srvMultiplex->AddItem(std::make_shared<BoolCommandItem>("mmmultiplexsession"_J));
		srvMultiplex->AddItem(std::make_shared<ConditionalItem>("mmmultiplexsession"_J, std::make_shared<IntCommandItem>("mmmultiplexsessioncount"_J, "##mmmultiplexsessioncount")));
		matchmakingSrvGroup->AddItem(std::move(srvSpoofRegion));
		matchmakingSrvGroup->AddItem(std::move(srvSpoofLanguage));
		matchmakingSrvGroup->AddItem(std::move(srvSpoofPlayerCount));
		matchmakingSrvGroup->AddItem(std::move(srvMultiplex));
		spoofing->AddItem(matchmakingSrvGroup);

		AddCategory(std::move(session));
		AddCategory(std::move(spoofing));

		auto protections = std::make_shared<Category>("Protections");
		auto toggles = std::make_shared<Group>("Script Events");
		toggles->AddItem(std::make_shared<BoolCommandItem>("prot_kicks"_J));
		toggles->AddItem(std::make_shared<BoolCommandItem>("prot_grief"_J));
		toggles->AddItem(std::make_shared<BoolCommandItem>("prot_spam"_J));
		toggles->AddItem(std::make_shared<BoolCommandItem>("prot_cash"_J));
		toggles->AddItem(std::make_shared<BoolCommandItem>("prot_chat"_J));
		toggles->AddItem(std::make_shared<BoolCommandItem>("prot_lognet"_J));
		toggles->AddItem(std::make_shared<BoolCommandItem>("prot_logunknown"_J));
		toggles->AddItem(std::make_shared<BoolCommandItem>("prot_compat"_J));

		auto attackLog = std::make_shared<Group>("Attack Log");
		attackLog->AddItem(std::make_shared<ImGuiItem>([] {
			auto log = Protections::GetAttackLog();

			if (log.empty())
			{
				ImGui::TextDisabled("No attacks blocked yet");
				return;
			}

			if (ImGui::BeginChild("##attacklog", ImVec2(0, 200), true))
			{
				for (auto& record : log)
				{
					auto age = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - record.LastSeen).count();

					ImGui::Text("%s", record.PlayerName.c_str());
					ImGui::SameLine();
					ImGui::TextDisabled("- %s", record.EventName.c_str());
					if (record.Count > 1)
					{
						ImGui::SameLine();
						ImGui::TextDisabled(" x%d", record.Count);
					}
					if (age > 0 && age < 120)
					{
						ImGui::SameLine();
						ImGui::TextDisabled(" (%llds ago)", static_cast<long long>(age));
					}
				}
			}
			ImGui::EndChild();

			if (ImGui::Button("Clear Log"))
				Protections::ClearAttackLog();
		}));

		protections->AddItem(toggles);

		protections->AddItem(attackLog);
		AddCategory(std::move(protections));

		AddCategory(std::move(BuildSavedPlayersMenu()));
		AddCategory(BuildRandomEventsMenu());
	}
}