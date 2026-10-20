#include "core/hooking/DetourHook.hpp"
#include "game/backend/NetTrace.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/network/netMessage.hpp"
#include "types/rage/datBitBuffer.hpp"

namespace YimMenu::Hooks
{
	// Every message we put on the wire. The trace channel is the only consumer, so
	// the hook is a straight pass through when the channel is off.
	void Network::QueuePacket(rage::netConnectionManager* mgr, int msg_id, void* data, int size, int flags, std::uint16_t* out_seq_id)
	{
		if (NetTrace::Enabled(NetTrace::Channel::Sent) && data && size > 0)
		{
			rage::datBitBuffer buffer(data, static_cast<std::uint32_t>(size), true);

			rage::netMessage::Type type = rage::netMessage::Type::Invalid;
			if (buffer.Read<int>(14) == 0x3246)
			{
				const auto extended = buffer.Read<bool>(1);
				type = buffer.Read<rage::netMessage::Type>(extended ? 16 : 8);
			}

			std::string payload;
			NetTrace::AppendHex(payload, data, static_cast<std::size_t>(size), 24);

			NetTrace::Log(NetTrace::Channel::Sent,
			    std::format("{} (0x{:02X}) len={} to_id={} flags=0x{:X}{}", rage::GetNetMessageName(type),
			                static_cast<int>(type), size, msg_id, flags, payload.empty() ? "" : " data=" + payload));
		}

		BaseHook::Get<Network::QueuePacket, DetourHook<decltype(&Network::QueuePacket)>>()->Original()(mgr, msg_id, data, size, flags, out_seq_id);
	}
}
