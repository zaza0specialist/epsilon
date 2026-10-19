#pragma once
#include <array>
#include <chrono>
#include <deque>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace YimMenu
{
	class Player;

	struct AttackRecord
	{
		std::string PlayerName;
		std::uint64_t Rid;
		std::string EventName;
		int Count;
		std::chrono::steady_clock::time_point LastSeen;
	};

	// per-player block tally for the session, used to correlate our own blocks with a later disconnect
	struct PlayerSessionStat
	{
		std::string Name;
		std::chrono::steady_clock::time_point Joined;
		int Blocked = 0;
		std::vector<std::string> Reasons; // distinct, capped
		bool MoreReasons = false;
	};

	enum class RateBucket : int
	{
		Explosion,
		PlaySound,
		WeaponDamage,
		Ptfx,
		Scripted,
		RequestControl,
		Fire,
		Projectile,
		IncrementStat,
		KickVotes,
		ClearPedTasks,
		GiveWeapon,
		BlowUpVehicle,
		GiveControl,
		GivePickup,
		ReportCashSpawn,
		Count
	};

	// Central script-event protection: blocklists + sender-attributed attack log.
	// Called from the HandleScriptedGameEvent hook (network thread) — UI reads the log from the game thread.
	class Protections
	{
	public:
		// returns true if the event should be blocked
		static bool ShouldBlockEvent(Player player, int event_index);
		static void ReportAttack(Player player, const char* event_name);

		// returns true when the player exceeded limit_per_sec events of this bucket in the current 1s window
		static bool CheckRateLimit(Player player, RateBucket bucket, const char* event_name, int limit_per_sec);

		// global cap: all net-game events from one player combined
		static bool CheckGlobalRateLimit(Player player, int limit_per_sec);

		// true if this player has been flagged for attacking recently (used for optional auto-mute)
		static bool IsPlayerFlagged(Player player);

		// true when we recognize the event index (i.e. we know its name/behaviour)
		static bool IsKnownEvent(int event_index);

		// captures hashes of script events we don't have in ScriptEventIndex yet (once per hash, then every 50th)
		static void LogUnknownScriptEvent(Player player, int event_index, const std::int64_t* args, int argc);

		// session bookkeeping: join/leave hooks log how long they stayed and what we blocked for them
		static void OnPlayerJoined(Player player);
		static void OnPlayerLeft(Player player);
		static void NoteBlocked(Player player, const char* event_name);

		static std::deque<AttackRecord> GetAttackLog();
		static void ClearAttackLog();

	private:
		static std::mutex m_LogMutex;
		static std::deque<AttackRecord> m_AttackLog;
		static std::mutex m_SessionMutex;
		static std::unordered_map<int, PlayerSessionStat> m_Sessions;
	};
}
