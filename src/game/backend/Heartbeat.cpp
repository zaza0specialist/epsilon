#include "Heartbeat.hpp"

#include "core/backend/ScriptMgr.hpp"
#include "core/logger/LogHelper.hpp"

#include <chrono>

namespace YimMenu::Features
{
	void RunHeartbeatScript()
	{
		auto next = std::chrono::steady_clock::now() + std::chrono::seconds(10);

		while (true)
		{
			const auto now = std::chrono::steady_clock::now();
			if (now >= next)
			{
				next = now + std::chrono::seconds(10);
				LOGF(INFO, "[heartbeat] script thread alive");
			}

			ScriptMgr::Yield();
		}
	}
}
