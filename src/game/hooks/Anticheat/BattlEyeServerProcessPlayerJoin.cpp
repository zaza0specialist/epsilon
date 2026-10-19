#include "core/hooking/DetourHook.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/commands/Commands.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/gta/Natives.hpp"
#include "types/battleye/CBattlEyePlayerModifyContext.hpp"
#include "game/backend/AnticheatBypass.hpp"

namespace YimMenu::Hooks
{
		bool Anticheat::BattlEyeServerProcessPlayerJoin(CBattlEyePlayerModifyInterface* server_iface, CBattlEyePlayerModifyContext* context)
		{
			if (!AnticheatBypass::IsBattlEyeRunning())
			{
				// BattlEye is not running (FSL or disabled) — allow all joiners so remote players can enter our sessions.
				return true;
			}

			// BE is running: only force-allow the local player into private sessions, or anyone if in Epsilon-only pool.
			if (context->m_IsLocal)
			{
				if (NETWORK::NETWORK_SESSION_IS_CLOSED_FRIENDS() || NETWORK::NETWORK_SESSION_IS_CLOSED_CREW() || NETWORK::NETWORK_SESSION_IS_SOLO() || NETWORK::NETWORK_SESSION_IS_PRIVATE())
				{
					return true;
				}
			}

			static auto cheater_pool = Commands::GetCommand<BoolCommand>("cheaterpool"_J);
			if (cheater_pool->GetState())
			{
				return true;
			}

			return BaseHook::Get<Anticheat::BattlEyeServerProcessPlayerJoin, DetourHook<decltype(&Anticheat::BattlEyeServerProcessPlayerJoin)>>()->Original()(server_iface, context);
		}
}