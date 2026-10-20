#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace YimMenu
{
	// Master network tracer. Writes to its own file so a large trace does not bury
	// the readable cout.log, and so a trace can be handed over on its own.
	//
	// Every channel is off by default and the tracer only formats a line when the
	// channel is on, because the hooks that call into it sit in the network hot
	// path.
	class NetTrace
	{
	public:
		enum class Channel
		{
			Message,  // received net messages
			Sent,     // queued net messages
			Event,    // net game events
			Script,   // script events
			Session,  // joins, leaves, session state
			BattlEye, // BattlEye state and commands
			Count
		};

		static void Init();
		static void Shutdown();

		// True when the channel (or the master switch) is on.
		static bool Enabled(Channel channel);

		// Writes one line. The caller is responsible for checking Enabled() first
		// when building an expensive message.
		static void Write(std::string_view line);

		// Convenience helpers.
		static void Message(std::string_view text);
		static void Session(std::string_view text);
		static void BattlEye(std::string_view text);

		// Writes a line on the given channel, prefixed with the channel name.
		static void Log(Channel channel, std::string_view text);

		// Formats a payload as hex, capped at cap bytes, and appends it to out.
		static void AppendHex(std::string& out, const void* data, std::size_t size, std::size_t cap);

		// The trace file path, for the UI.
		static std::string FilePath();
	};
}
