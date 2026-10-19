#include "core/hooking/DetourHook.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/commands/Commands.hpp"
#include "core/scripting/LuaManager.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/backend/Players.hpp"
#include "game/backend/Protections.hpp"
#include "game/frontend/ChatDisplay.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/gta/Packet.hpp"
#include "game/backend/Self.hpp"
#include "types/network/netEvent.hpp"
#include "types/network/netMessage.hpp"
#include "types/rage/datBitBuffer.hpp"
#include "core/frontend/widgets/imgui_colors.h"
#include <algorithm>
#include <array>

namespace YimMenu::Hooks
{
	static std::optional<rage::netMessage::Type> ReadType(rage::datBitBuffer& buffer)
	{
		if (buffer.Read<int>(14) != 0x3246)
			return std::nullopt;

		auto extended = buffer.Read<bool>(1);
		return buffer.Read<rage::netMessage::Type>(extended ? 16 : 8);
	}

	void Network::ReceiveNetMessage(void* a1, rage::netConnectionManager* mgr, rage::netEvent* event)
	{
		if (!g_Running)
			return BaseHook::Get<Network::ReceiveNetMessage, DetourHook<decltype(&Network::ReceiveNetMessage)>>()->Original()(a1, mgr, event);

		if (event->GetEventType() != rage::netEvent::Type::FrameReceived)
			return BaseHook::Get<Network::ReceiveNetMessage, DetourHook<decltype(&Network::ReceiveNetMessage)>>()->Original()(a1, mgr, event);

		// TODO: port security ID stuff from V1
		auto fr_evt = reinterpret_cast<rage::netEventFrameReceived*>(event);
		rage::datBitBuffer buffer(fr_evt->m_Data, fr_evt->m_Length, true);

		rage::netMessage::Type type = ReadType(buffer).value_or(rage::netMessage::Type::Invalid);

		switch (type)
		{
		case rage::netMessage::Type::TextMessage:
		{
			auto player = Players::GetByMessageId(fr_evt->m_MsgId);
			if (player)
			{
				char msg[256]{};
				buffer.ReadString(msg, sizeof(msg)); // we don't need the rest

				if (auto cmd = Commands::GetCommand<BoolCommand>("prot_chat"_J); cmd && cmd->GetState())
				{
					std::string lower = msg;
					std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return static_cast<char>(::tolower(c)); });

					static constexpr std::array ad_markers = {
					    "http://", "https://", "www.", "discord.", ".gg/", "t.me/", "youtube.com", "free money", "cheap money", ".com/", ".net/", ".xyz/"};

					if (std::ranges::any_of(ad_markers, [&lower](const char* marker) { return lower.find(marker) != std::string::npos; }))
					{
						LOGF(WARNING, "Blocked chat ad from {}: {}", player.GetName(), msg);
						Protections::ReportAttack(player, "Chat Ad");
						return;
					}
				}

				if (!LuaManager::DispatchEvent(MenuEvent::ChatMessageReceived, [player, msg](lua_State* state){
					lua_pushinteger(state, player.GetId());
					lua_pushstring(state, msg);
					return 2;
				}))
					return;

				ChatDisplay::Show(player.GetName(), msg, ImGui::Colors::LightBlue);
			}
			return; // the game doesn't handle that anyway
		}
		case rage::netMessage::Type::PackedEvents:
		{
			auto player = Players::GetByMessageId(fr_evt->m_MsgId);

			if (!player)
				break;

			uint32_t count = buffer.Read<uint32_t>(5);
			uint32_t buffer_size = buffer.Read<uint32_t>(15);

			if (buffer_size > 7296)
				buffer_size = 7296;

			int remaining = buffer_size;

			while (remaining >= 39)
			{
				int bits_read = buffer.m_BitsRead;

				uint16_t event_id = buffer.Read<uint16_t>(7);
				uint32_t event_index = buffer.Read<uint32_t>(9);
				uint32_t event_handled_bits = buffer.Read<uint32_t>(8);
				uint32_t event_data_size = buffer.Read<uint32_t>(15);

				if (buffer.Read<bool>(1))
					buffer.Read<uint32_t>(16);

				char event_data[4096 + 1];
				if (event_data_size)
				{
					buffer.ReadArray(event_data, event_data_size);
				}

				rage::datBitBuffer event_buffer(event_data, sizeof(event_data), true);
				event_buffer.m_MaxBit = event_data_size + 1;

				ReceiveNetGameEvent(player, event_id, event_index, event_handled_bits, event_buffer);

				remaining -= (int)buffer.m_BitsRead - bits_read;
			}

			break;
		}
		case rage::netMessage::Type::PackedReliables:
		{
			auto player = Players::GetByMessageId(fr_evt->m_MsgId);

			auto flags = buffer.Read<int>(4);

			if ((flags & 1) != 0)
			{
				auto timestamp = buffer.Read<std::uint32_t>(32);
				if (auto num_msgs = buffer.Read<int>(5))
					buffer.Seek(buffer.Read<std::uint32_t>(13));
			}

			if ((flags & 2) != 0)
			{
				if (auto num_msgs = buffer.Read<int>(5))
					buffer.Seek(buffer.Read<std::uint32_t>(13));
			}

			if ((flags & 4) != 0)
			{
				if (auto num_msgs = buffer.Read<int>(5))
				{
					auto sz = buffer.Read<std::uint32_t>(13);
					auto pos_now = buffer.m_BitsRead;
					while (pos_now + sz > buffer.m_BitsRead)
					{
						auto id = buffer.Read<std::uint16_t>(13);
						auto token = buffer.Read<int>(5);
						bool reject = false;

						if (Self::GetPed().GetPointer<void*>() && Self::GetPed().GetNetworkObjectId() == id)
						{
							if (player)
								LOGF(WARNING, "Blocked player deletion crash from {}", player.GetName());
							reject = true;
						}

						if (Self::GetVehicle() && Self::GetVehicle().HasControl() && Self::GetVehicle().GetNetworkObjectId() == id)
						{
							if (player)
								LOGF(WARNING, "Blocked vehicle deletion from {}", player.GetName());
							reject = true;
						}

						if (reject)
						{
							rage::datBitBuffer write_buf(fr_evt->m_Data, fr_evt->m_Length);
							write_buf.Seek(buffer.m_BitsRead - 5 - 13);
							write_buf.Write<std::uint16_t>(0xFFFF, 16);
						}
					}
				}
			}

			break;
		}
		case rage::netMessage::Type::KickPlayer:
		{
			if (!AnticheatBypass::IsFSLProvidingBattlEyeBypass())
			{
				LOGF(WARNING, "Blocked KickPlayer (host kick) message");
				return;
			}
			LOGF(WARNING, "Passing KickPlayer (host kick) message through (FSL provides BE bypass)");
			break;
		}
		case rage::netMessage::Type::BattlEyeCmd:
		{
			if (!AnticheatBypass::IsFSLProvidingBattlEyeBypass() && !AnticheatBypass::IsBattlEyeRunning())
			{
				char data[1028]{};
				int size = buffer.Read<int>(11);
				bool from_client = buffer.Read<bool>(1);
				buffer.Seek(4); // normalize before we read
				buffer.ReadArrayBytes(&data, size);

				const auto log_be = [] {
					auto cmd = Commands::GetCommand<BoolCommand>("prot_lognet"_J);
					return cmd && cmd->GetState();
				}();

				if (log_be)
					LOGF(WARNING, "BattlEyeCmd size={} from_client={} op=0x{:02X} b1=0x{:02X}", size, from_client,
					    size > 0 ? static_cast<unsigned char>(data[0]) : 0, size > 1 ? static_cast<unsigned char>(data[1]) : 0);

				if (from_client)
					break;

				break;
			}
			break;
		}
		default:
			break;
		}

		BaseHook::Get<Network::ReceiveNetMessage, DetourHook<decltype(&Network::ReceiveNetMessage)>>()->Original()(a1, mgr, event);
	}
}