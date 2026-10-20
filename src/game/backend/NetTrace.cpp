#include "NetTrace.hpp"

#include "core/commands/BoolCommand.hpp"
#include "core/logger/LogHelper.hpp"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <mutex>

namespace YimMenu
{
	namespace
	{
		class TraceCommand : public BoolCommand
		{
		public:
			using BoolCommand::BoolCommand;
		};

		// Master switch plus one command per channel. The channel commands default
		// to on, so the master switch turns everything on and a specific channel can
		// then be narrowed down.
		static TraceCommand _nettrace{
		    "nettrace",
		    "Network Trace",
		    "Master switch for the network tracer. Writes every net message, event and script event to nettrace.log in %APPDATA%\\Epsilon. Off by default, it is heavy on the network thread",
		    false};

		static TraceCommand _nettrace_msg{"nettrace_msg", "Trace: Messages", "Log every received net message with its name, size and sender", true};
		static TraceCommand _nettrace_sent{"nettrace_sent", "Trace: Sent Messages", "Log every net message we queue and send", true};
		static TraceCommand _nettrace_event{"nettrace_event", "Trace: Net Events", "Log every net game event with its id, sender and arguments", true};
		static TraceCommand _nettrace_script{"nettrace_script", "Trace: Script Events", "Log every script event with its hash, name and arguments", true};
		static TraceCommand _nettrace_session{"nettrace_session", "Trace: Session", "Log joins, leaves and session state changes", true};
		static TraceCommand _nettrace_be{"nettrace_battleye", "Trace: BattlEye", "Log BattlEye state changes and every BattlEye command", true};

		// Hard cap on the trace file. A trace that fills the disk is worse than none.
		constexpr std::size_t k_MaxFileBytes = 16u * 1024u * 1024u;

		std::ofstream g_Out;
		std::mutex g_Mutex;
		std::size_t g_Written = 0;
		int g_LinesSinceFlush = 0;
		bool g_Stopped = false;
		std::chrono::system_clock::time_point g_Start = std::chrono::system_clock::now();
	}

	std::string NetTrace::FilePath()
	{
		const char* appdata = std::getenv("APPDATA");
		return (std::filesystem::path(appdata ? appdata : ".") / "Epsilon" / "nettrace.log").string();
	}

	void NetTrace::Init()
	{
		const auto path = std::filesystem::path(FilePath());
		std::error_code ec;
		std::filesystem::create_directories(path.parent_path(), ec);

		g_Out.open(path, std::ios::out | std::ios::trunc);
		if (!g_Out.is_open())
		{
			LOGF(WARNING, "Net trace could not open {}", path.string());
			return;
		}

		g_Written = 0;
		g_Stopped = false;
		g_Start = std::chrono::system_clock::now();

		g_Out << "# Epsilon network trace\n";
		g_Out << "# build: " << __DATE__ << " " << __TIME__ << "\n";
		g_Out << "# channels: msg sent event script session be\n";
		g_Out << "# format: [offset_ms] channel: message\n";
		g_Out.flush();
	}

	void NetTrace::Shutdown()
	{
		std::lock_guard lock(g_Mutex);
		if (g_Out.is_open())
		{
			g_Out << "# trace closed\n";
			g_Out.flush();
			g_Out.close();
		}
	}

	bool NetTrace::Enabled(Channel channel)
	{
		if (!_nettrace.GetState())
			return false;

		switch (channel)
		{
		case Channel::Message:
			return _nettrace_msg.GetState();
		case Channel::Sent:
			return _nettrace_sent.GetState();
		case Channel::Event:
			return _nettrace_event.GetState();
		case Channel::Script:
			return _nettrace_script.GetState();
		case Channel::Session:
			return _nettrace_session.GetState();
		case Channel::BattlEye:
			return _nettrace_be.GetState();
		default:
			return false;
		}
	}

	void NetTrace::Write(std::string_view line)
	{
		std::lock_guard lock(g_Mutex);

		if (g_Stopped || !g_Out.is_open())
			return;

		const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - g_Start).count();

		g_Out << "[" << elapsed << "ms] " << line << "\n";
		g_Written += line.size() + 32;

		if (g_Written > k_MaxFileBytes)
		{
			g_Out << "# trace stopped: size cap reached\n";
			g_Out.flush();
			g_Stopped = true;
			return;
		}

		// Flushing every line is too costly on the network thread, but a trace that
		// is lost when the game dies is worthless, so it is flushed often enough
		// that only the last few lines can be lost.
		if (++g_LinesSinceFlush >= 16)
		{
			g_LinesSinceFlush = 0;
			g_Out.flush();
		}
	}

	void NetTrace::Message(std::string_view text)
	{
		if (!Enabled(Channel::Message))
			return;

		Write(std::string("msg: ") + std::string(text));
	}

	void NetTrace::Session(std::string_view text)
	{
		if (!Enabled(Channel::Session))
			return;

		Write(std::string("session: ") + std::string(text));
	}

	void NetTrace::BattlEye(std::string_view text)
	{
		if (!Enabled(Channel::BattlEye))
			return;

		Write(std::string("be: ") + std::string(text));
	}

	void NetTrace::Log(Channel channel, std::string_view text)
	{
		if (!Enabled(channel))
			return;

		const char* name = "trace";
		switch (channel)
		{
		case Channel::Message:
			name = "msg";
			break;
		case Channel::Sent:
			name = "sent";
			break;
		case Channel::Event:
			name = "event";
			break;
		case Channel::Script:
			name = "script";
			break;
		case Channel::Session:
			name = "session";
			break;
		case Channel::BattlEye:
			name = "be";
			break;
		default:
			break;
		}

		Write(std::string(name) + ": " + std::string(text));
	}

	void NetTrace::AppendHex(std::string& out, const void* data, std::size_t size, std::size_t cap)
	{
		if (!data || size == 0)
			return;

		const auto* bytes = static_cast<const unsigned char*>(data);
		const std::size_t count = size < cap ? size : cap;

		for (std::size_t i = 0; i < count; i++)
		{
			char buf[4];
			std::snprintf(buf, sizeof(buf), "%02X", bytes[i]);
			out += buf;
			if (i + 1 < count)
				out += ' ';
		}

		if (size > cap)
			out += " ...";
	}
}
