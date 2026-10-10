#include "Protections.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/commands/Commands.hpp"
#include "game/backend/Players.hpp"
#include "game/gta/Player.hpp"
#include "types/script/ScriptEvent.hpp"

namespace YimMenu
{
	std::mutex Protections::m_LogMutex;
	std::deque<AttackRecord> Protections::m_AttackLog;

	static const char* GetEventName(int index)
	{
		switch (static_cast<ScriptEventIndex>(index))
		{
		case ScriptEventIndex::Bounty: return "Bounty";
		case ScriptEventIndex::CeoBan: return "CEO Ban";
		case ScriptEventIndex::CeoKick: return "CEO Kick";
		case ScriptEventIndex::CeoMoney: return "CEO Money";
		case ScriptEventIndex::ClearWantedLevel: return "Clear Wanted Level";
		case ScriptEventIndex::ForceMission: return "Force Mission";
		case ScriptEventIndex::GtaBanner: return "GTA Banner";
		case ScriptEventIndex::NetworkBail: return "Network Bail";
		case ScriptEventIndex::PersonalVehicleDestroyed: return "PV Destroyed";
		case ScriptEventIndex::RemoteOffradar: return "Remote Off-Radar";
		case ScriptEventIndex::SendToCutscene: return "Send To Cutscene";
		case ScriptEventIndex::SendToCayoPerico: return "Send To Cayo Perico";
		case ScriptEventIndex::SendToLocation: return "Send To Location";
		case ScriptEventIndex::SoundSpam: return "Sound Spam";
		case ScriptEventIndex::Spectate: return "Force Spectate";
		case ScriptEventIndex::Teleport: return "Forced Teleport";
		case ScriptEventIndex::TeleportToWarehouse: return "Teleport To Warehouse";
		case ScriptEventIndex::VehicleKick: return "Vehicle Kick";
		case ScriptEventIndex::MCTeleport: return "MC Teleport";
		case ScriptEventIndex::StartActivity: return "Force Activity";
		case ScriptEventIndex::MarkPlayerAsBeast: return "Mark As Beast";
		case ScriptEventIndex::KickFromInterior: return "Kick From Interior";
		case ScriptEventIndex::InteriorControl: return "Interior Control";
		case ScriptEventIndex::SendTextLabelSMS: return "Text Label SMS";
		case ScriptEventIndex::Crash: return "Crash";
		case ScriptEventIndex::Crash2: return "Crash 2";
		case ScriptEventIndex::Crash3: return "Crash 3";
		case ScriptEventIndex::TSECommand: return "TSE Command";
		case ScriptEventIndex::TSECommandRotateCam: return "TSE Rotate Cam";
		case ScriptEventIndex::TSECommandSound: return "TSE Sound";
		case ScriptEventIndex::TSECommandLaunchHeist: return "TSE Launch Heist";
		case ScriptEventIndex::NotificationCrash1: return "Notification Crash 1";
		case ScriptEventIndex::NotificationCrash2: return "Notification Crash 2";
		case ScriptEventIndex::DestroyPersonalVehicle: return "Destroy PV";
		case ScriptEventIndex::TriggerCEORaid: return "Trigger CEO Raid";
		case ScriptEventIndex::StartScriptBegin: return "Force Script (Begin)";
		case ScriptEventIndex::StartScriptProceed: return "Force Script (Proceed)";
		default: return "Unknown Event";
		}
	}

	void Protections::ReportAttack(Player player, const char* event_name)
	{
		{
			std::lock_guard lock(m_LogMutex);

			for (auto& record : m_AttackLog)
			{
				if (record.Rid == player.GetRID())
				{
					record.EventName = event_name;
					record.Count++;
					return;
				}
			}

			m_AttackLog.push_front(AttackRecord{player.GetName(), player.GetRID(), event_name, 1});

			if (m_AttackLog.size() > 32)
				m_AttackLog.pop_back();
		}

		LOGF(WARNING, "Blocked {} from {} (RID: {})", event_name, player.GetName(), player.GetRID());
	}

	std::deque<AttackRecord> Protections::GetAttackLog()
	{
		std::lock_guard lock(m_LogMutex);
		return m_AttackLog;
	}

	void Protections::ClearAttackLog()
	{
		std::lock_guard lock(m_LogMutex);
		m_AttackLog.clear();
	}

	bool Protections::ShouldBlockEvent(Player player, int event_index)
	{
		const auto index = static_cast<ScriptEventIndex>(event_index);
		const char* name  = GetEventName(event_index);

		// always blocked: known crash/rat events, no exceptions
		switch (index)
		{
		case ScriptEventIndex::Crash:
		case ScriptEventIndex::Crash2:
		case ScriptEventIndex::Crash3:
		case ScriptEventIndex::NotificationCrash1:
		case ScriptEventIndex::NotificationCrash2:
		case ScriptEventIndex::TSECommandLaunchHeist:
		case ScriptEventIndex::StartScriptBegin:
		case ScriptEventIndex::StartScriptProceed:
			ReportAttack(player, name);
			return true;
		default:
			break;
		}

		// toggled blocks
		if (auto cmd = Commands::GetCommand<BoolCommand>("prot_kicks"_J); cmd && cmd->GetState())
		{
			switch (index)
			{
			case ScriptEventIndex::NetworkBail:
			case ScriptEventIndex::CeoBan:
			case ScriptEventIndex::VehicleKick:
			case ScriptEventIndex::KickFromInterior:
				ReportAttack(player, name);
				return true;
			default:
				break;
			}
		}

		if (auto cmd = Commands::GetCommand<BoolCommand>("prot_grief"_J); cmd && cmd->GetState())
		{
			switch (index)
			{
			case ScriptEventIndex::SendToCutscene:
			case ScriptEventIndex::SendToCayoPerico:
			case ScriptEventIndex::SendToLocation:
			case ScriptEventIndex::Teleport:
			case ScriptEventIndex::TeleportToWarehouse:
			case ScriptEventIndex::MCTeleport:
			case ScriptEventIndex::StartActivity:
			case ScriptEventIndex::MarkPlayerAsBeast:
			case ScriptEventIndex::DestroyPersonalVehicle:
			case ScriptEventIndex::TriggerCEORaid:
			case ScriptEventIndex::Spectate:
				ReportAttack(player, name);
				return true;
			default:
				break;
			}
		}

		if (auto cmd = Commands::GetCommand<BoolCommand>("prot_spam"_J); cmd && cmd->GetState())
		{
			switch (index)
			{
			case ScriptEventIndex::SoundSpam:
			case ScriptEventIndex::SendTextLabelSMS:
			case ScriptEventIndex::GtaBanner:
			case ScriptEventIndex::Notification:
			case ScriptEventIndex::NotificationMoneyBanked:
			case ScriptEventIndex::NotificationMoneyRemoved:
			case ScriptEventIndex::NotificationMoneyStolen:
				ReportAttack(player, name);
				return true;
			default:
				break;
			}
		}

		return false;
	}
}
