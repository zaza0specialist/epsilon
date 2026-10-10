#include "game/backend/Protections.hpp"
#include "game/backend/Self.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/network/netGameEvent.hpp"
#include "types/script/globals/GPBD_FM_3.hpp"
#include "types/script/globals/GlobalPlayerBD.hpp"
#include "types/script/ScriptEvent.hpp"
#include "core/scripting/LuaManager.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/util/Joaat.hpp"

namespace YimMenu::Hooks
{
	static bool CheckLuaScripts(Player player, CScriptedGameEvent& event)
	{
		return LuaManager::DispatchEvent(MenuEvent::ScriptedGameEventReceived, [player, &event](lua_State* state)
		{
			Lua::CreateObject<YimMenu::Player>(state, player);

			lua_newtable(state);
			auto length = event.m_ArgsSize / 8;
			for (int i = 0; i < length; i++)
			{
				lua_pushinteger(state, i == 0 ? (ptrdiff_t)(int)event.m_Args[i] : event.m_Args[i]);
				lua_rawseti(state, -2, i + 1);
			}

			return 2;
		}, true);
	}

	bool Network::HandleScriptedGameEvent(Player player, CScriptedGameEvent& event)
	{
		if (!CheckLuaScripts(player, event))
			return false;

		SCRIPT_EVENT* script_event = reinterpret_cast<SCRIPT_EVENT*>(event.m_Args);

		if (Protections::ShouldBlockEvent(player, script_event->GetEventIndex()))
			return false;

		switch (static_cast<ScriptEventIndex>(script_event->GetEventIndex()))
		{
		case ScriptEventIndex::Bounty:
		{
			SCRIPT_EVENT_BOUNTY* bounty = static_cast<SCRIPT_EVENT_BOUNTY*>(script_event);

			if (event.m_ArgsSize != SCRIPT_EVENT_BOUNTY::GetSize())
			{
				Protections::ReportAttack(player, "Malformed Bounty");
				return false;
			}

			if (bounty->Target == Self::GetPlayer().GetId())
			{
				Protections::ReportAttack(player, "Bounty (self)");
				return false;
			}

			break;
		}
		case ScriptEventIndex::CeoKick:
		{
			// allow your actual boss to kick you from the org (legit game mechanic)
			if (player.GetId() != GPBD_FM_3::Get()->Entries[Self::GetPlayer().GetId()].BossGoon.Boss)
			{
				Protections::ReportAttack(player, "CEO Kick (not boss)");
				return false;
			}

			break;
		}
		case ScriptEventIndex::InteriorControl:
		{
			SCRIPT_EVENT_SEND_TO_INTERIOR* interior_control = static_cast<SCRIPT_EVENT_SEND_TO_INTERIOR*>(script_event);

			if (interior_control->Interior < 0 || interior_control->Interior >= static_cast<int>(eSimpleInteriorIndex::SIMPLE_INTERIOR_MAX))
			{
				Protections::ReportAttack(player, "Interior Control (null function kick)");
				return false;
			}

			if (!interior_control->GoonsOnly)
			{
				Protections::ReportAttack(player, "Interior Control (forced teleport)");
				return false;
			}

			break;
		}
		default:
			break;
		}

		return true;
	}
}
