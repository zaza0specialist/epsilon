#include "Protections.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/commands/Commands.hpp"
#include "game/backend/Players.hpp"
#include "game/gta/Player.hpp"
#include "types/script/ScriptEvent.hpp"
#include <algorithm>
#include <cstdint>
#include <format>
#include <string_view>

namespace YimMenu
{
	std::mutex Protections::m_LogMutex;
	std::deque<AttackRecord> Protections::m_AttackLog;
	std::mutex Protections::m_SessionMutex;
	std::unordered_map<int, PlayerSessionStat> Protections::m_Sessions;

	void Protections::OnPlayerJoined(Player player)
	{
		std::lock_guard lock(m_SessionMutex);
		auto& stat = m_Sessions[player.GetId()];
		stat.Name     = player.GetName();
		stat.Joined   = std::chrono::steady_clock::now();
		stat.Blocked  = 0;
		stat.Reasons.clear();
		stat.MoreReasons = false;
	}

	void Protections::NoteBlocked(Player player, const char* event_name)
	{
		std::lock_guard lock(m_SessionMutex);
		auto& stat = m_Sessions[player.GetId()];
		if (stat.Name.empty())
			stat.Name = player.GetName();

		stat.Blocked++;

		if (std::find(stat.Reasons.begin(), stat.Reasons.end(), event_name) == stat.Reasons.end())
		{
			if (stat.Reasons.size() < 8)
				stat.Reasons.emplace_back(event_name);
			else
				stat.MoreReasons = true;
		}
	}

	void Protections::OnPlayerLeft(Player player)
	{
		PlayerSessionStat stat;
		bool found = false;

		{
			std::lock_guard lock(m_SessionMutex);
			auto it = m_Sessions.find(player.GetId());
			if (it != m_Sessions.end())
			{
				stat  = std::move(it->second);
				found = true;
				m_Sessions.erase(it);
			}
		}

		if (!found)
			return;

		const auto seconds =
		    std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - stat.Joined).count();

		if (stat.Blocked == 0)
		{
			LOGF(WARNING, "{} left after {}s — no protection triggers", stat.Name, seconds);
			return;
		}

		std::string reasons;
		for (size_t i = 0; i < stat.Reasons.size(); i++)
		{
			if (i)
				reasons += ", ";
			reasons += stat.Reasons[i];
		}
		if (stat.MoreReasons)
			reasons += ", ...";

		LOGF(WARNING, "{} left after {}s — {} protection triggers ({})", stat.Name, seconds, stat.Blocked, reasons);
	}

	struct RateWindow
	{
		int Count = 0;
		std::chrono::steady_clock::time_point Start{};
	};

	static std::mutex s_RateMutex;
	static std::array<std::unordered_map<int, RateWindow>, static_cast<size_t>(RateBucket::Count)> s_RateWindows;
	static std::unordered_map<int, RateWindow> s_GlobalRateWindow;
	static std::mutex s_FlagMutex;
	static std::unordered_map<int, std::chrono::steady_clock::time_point> s_FlaggedPlayers;

	bool Protections::CheckRateLimit(Player player, RateBucket bucket, const char* event_name, int limit_per_sec)
	{
		const auto now = std::chrono::steady_clock::now();
		bool over_limit = false;

		{
			std::lock_guard lock(s_RateMutex);
			auto& window = s_RateWindows[static_cast<size_t>(bucket)][player.GetId()];

			if (window.Count == 0 || now - window.Start >= std::chrono::seconds(1))
			{
				window.Count = 1;
				window.Start = now;
			}
			else
			{
				window.Count++;
				over_limit = window.Count > limit_per_sec;
			}
		}

		if (over_limit)
		{
			ReportAttack(player, event_name);
			std::lock_guard lock(s_FlagMutex);
			s_FlaggedPlayers[player.GetId()] = now;
		}

		return over_limit;
	}

	bool Protections::CheckGlobalRateLimit(Player player, int limit_per_sec)
	{
		const auto now = std::chrono::steady_clock::now();
		bool over_limit = false;

		{
			std::lock_guard lock(s_RateMutex);
			auto& window = s_GlobalRateWindow[player.GetId()];

			if (window.Count == 0 || now - window.Start >= std::chrono::seconds(1))
			{
				window.Count = 1;
				window.Start = now;
			}
			else
			{
				window.Count++;
				over_limit = window.Count > limit_per_sec;
			}
		}

		if (over_limit)
		{
			ReportAttack(player, "NetEvent flood (global)");
			std::lock_guard lock(s_FlagMutex);
			s_FlaggedPlayers[player.GetId()] = now;
		}

		return over_limit;
	}

	bool Protections::IsPlayerFlagged(Player player)
	{
		std::lock_guard lock(s_FlagMutex);
		auto it = s_FlaggedPlayers.find(player.GetId());
		if (it == s_FlaggedPlayers.end())
			return false;

		if (std::chrono::steady_clock::now() - it->second > std::chrono::minutes(30))
		{
			s_FlaggedPlayers.erase(it);
			return false;
		}

		return true;
	}

	static std::mutex s_UnknownMutex;
	static std::unordered_map<int, int> s_UnknownEventCounts;

	bool Protections::IsKnownEvent(int index)
	{
		switch (static_cast<ScriptEventIndex>(index))
		{
		case ScriptEventIndex::Bounty:
		case ScriptEventIndex::CeoBan:
		case ScriptEventIndex::CeoKick:
		case ScriptEventIndex::CeoMoney:
		case ScriptEventIndex::ClearWantedLevel:
		case ScriptEventIndex::ForceMission:
		case ScriptEventIndex::GtaBanner:
		case ScriptEventIndex::NetworkBail:
		case ScriptEventIndex::PersonalVehicleDestroyed:
		case ScriptEventIndex::RemoteOffradar:
		case ScriptEventIndex::SendToCutscene:
		case ScriptEventIndex::SendToCayoPerico:
		case ScriptEventIndex::SendToLocation:
		case ScriptEventIndex::SoundSpam:
		case ScriptEventIndex::Spectate:
		case ScriptEventIndex::Teleport:
		case ScriptEventIndex::TeleportToWarehouse:
		case ScriptEventIndex::VehicleKick:
		case ScriptEventIndex::MCTeleport:
		case ScriptEventIndex::StartActivity:
		case ScriptEventIndex::MarkPlayerAsBeast:
		case ScriptEventIndex::KickFromInterior:
		case ScriptEventIndex::InteriorControl:
		case ScriptEventIndex::SendTextLabelSMS:
		case ScriptEventIndex::Crash:
		case ScriptEventIndex::Crash2:
		case ScriptEventIndex::Crash3:
		case ScriptEventIndex::TSECommand:
		case ScriptEventIndex::TSECommandRotateCam:
		case ScriptEventIndex::TSECommandSound:
		case ScriptEventIndex::TSECommandLaunchHeist:
		case ScriptEventIndex::NotificationCrash1:
		case ScriptEventIndex::NotificationCrash2:
		case ScriptEventIndex::DestroyPersonalVehicle:
		case ScriptEventIndex::TriggerCEORaid:
		case ScriptEventIndex::StartScriptBegin:
		case ScriptEventIndex::StartScriptProceed:
		case ScriptEventIndex::Notification:
		case ScriptEventIndex::NotificationMoneyBanked:
		case ScriptEventIndex::NotificationMoneyRemoved:
		case ScriptEventIndex::NotificationMoneyStolen:
			return true;
		default:
			return false;
		}
	}

	void Protections::LogUnknownScriptEvent(Player player, int event_index, const std::int64_t* args, int argc)
	{
		if (auto cmd = Commands::GetCommand<BoolCommand>("prot_logunknown"_J); !cmd || !cmd->GetState())
			return;

		int count;

		{
			std::lock_guard lock(s_UnknownMutex);
			count = ++s_UnknownEventCounts[event_index];
		}

		// first sighting gets the full payload, later ones just a counter
		if (count == 1)
		{
			std::string payload;

			for (int i = 1; i < argc && i < 8; i++)
				payload += std::format(" [{}] 0x{:X}", i, static_cast<std::uint64_t>(args[i]));

			LOGF(WARNING, "Unknown script event 0x{:08X} (signed {}) from {} (RID: {}) argc={}{}",
			    static_cast<std::uint32_t>(event_index), event_index, player.GetName(), player.GetRID(), argc, payload);
		}
		else if (count % 50 == 0)
		{
			LOGF(WARNING, "Unknown script event 0x{:08X} seen {}x from {}", static_cast<std::uint32_t>(event_index), count, player.GetName());
		}
	}

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
		const auto now = std::chrono::steady_clock::now();

		NoteBlocked(player, event_name);

		{
			std::lock_guard lock(m_LogMutex);

			for (auto& record : m_AttackLog)
			{
				if (record.Rid == player.GetRID() && record.EventName == event_name)
				{
					record.Count++;
					record.LastSeen = now;
					return;
				}
			}

			m_AttackLog.push_front(AttackRecord{player.GetName(), player.GetRID(), event_name, 1, now});

			if (m_AttackLog.size() > 64)
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

		// diagnostics/A-B: log only, never block (use when a legitimate player is being broken by a block)
		if (auto compat = Commands::GetCommand<BoolCommand>("prot_compat"_J); compat && compat->GetState())
		{
			if (name && std::string_view(name) != "Unknown Event")
				LOGF(WARNING, "[compat] observed {} from {} (not blocked)", name, player.GetName());
			return false;
		}

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
			case ScriptEventIndex::DestroyPersonalVehicle:
			case ScriptEventIndex::TriggerCEORaid:
			case ScriptEventIndex::Spectate:
			case ScriptEventIndex::ForceMission:
			case ScriptEventIndex::ClearWantedLevel:
			case ScriptEventIndex::RemoteOffradar:
			case ScriptEventIndex::PersonalVehicleDestroyed:
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

		if (auto cmd = Commands::GetCommand<BoolCommand>("prot_cash"_J); cmd && cmd->GetState())
		{
			switch (index)
			{
			case ScriptEventIndex::CeoMoney:
				ReportAttack(player, name);
				return true;
			default:
				break;
			}
		}

		return false;
	}
}
