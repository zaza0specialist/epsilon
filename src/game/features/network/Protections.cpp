#include "core/commands/BoolCommand.hpp"

namespace YimMenu::Features
{
	class BlockKicks : public BoolCommand
	{
		using BoolCommand::BoolCommand;
	};

	class BlockGrief : public BoolCommand
	{
		using BoolCommand::BoolCommand;
	};

	class BlockSpam : public BoolCommand
	{
		using BoolCommand::BoolCommand;
	};

	class BlockCash : public BoolCommand
	{
		using BoolCommand::BoolCommand;
	};

	class ChatAds : public BoolCommand
	{
		using BoolCommand::BoolCommand;
	};

	class LogNetEvents : public BoolCommand
	{
		using BoolCommand::BoolCommand;
	};

	class LogUnknownEvents : public BoolCommand
	{
		using BoolCommand::BoolCommand;
	};

	class CompatMode : public BoolCommand
	{
		using BoolCommand::BoolCommand;
	};

	static BlockKicks _prot_kicks{"prot_kicks", "Block Kicks", "Blocks remote kick script events (CEO ban, vehicle kick, network bail, kick from interior)", true};
	static BlockGrief _prot_grief{"prot_grief", "Block Griefing", "Blocks forced teleports, cutscenes, spectate, bounty abuse, forced missions, and other grief script events", true};
	static BlockSpam _prot_spam{"prot_spam", "Block Spam", "Blocks sound spam, SMS, fake notifications, and rate-limits explosion/PTFX/weapon/script event floods", true};
	static BlockCash _prot_cash{"prot_cash", "Block Cash Drops", "Blocks forced money events (CEO money, fake cash spawn notifications)", true};
	static ChatAds _prot_chat{"prot_chat", "Block Chat Ads", "Hides chat messages containing links or advertisements", true};
	static LogNetEvents _prot_lognet{"prot_lognet", "Log Net Events", "Logs every received net game event to cout.log (diagnostics)", false};
	static LogUnknownEvents _prot_logunknown{"prot_logunknown", "Log Unknown Script Events", "Logs the hash and payload of script events we don't recognize yet — use this to capture hashes for new kick vectors", false};
	static CompatMode _prot_compat{"prot_compat", "Compatibility Mode", "Logs every event instead of blocking anything — use this to test whether a legitimate player is being broken by our protections", false};
}
