#pragma once
#include <deque>
#include <mutex>
#include <string>

namespace YimMenu
{
	class Player;

	struct AttackRecord
	{
		std::string PlayerName;
		std::uint64_t Rid;
		std::string EventName;
		int Count;
	};

	// Central script-event protection: blocklists + sender-attributed attack log.
	// Called from the HandleScriptedGameEvent hook (network thread) — UI reads the log from the game thread.
	class Protections
	{
	public:
		// returns true if the event should be blocked
		static bool ShouldBlockEvent(Player player, int event_index);
		static void ReportAttack(Player player, const char* event_name);

		static std::deque<AttackRecord> GetAttackLog();
		static void ClearAttackLog();

	private:
		static std::mutex m_LogMutex;
		static std::deque<AttackRecord> m_AttackLog;
	};
}
