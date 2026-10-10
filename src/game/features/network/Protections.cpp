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

	static BlockKicks _prot_kicks{"prot_kicks", "Block Kicks", "Blocks remote kick script events (CEO kick/ban, vehicle kick, network bail, forced missions)", true};
	static BlockGrief _prot_grief{"prot_grief", "Block Griefing", "Blocks forced teleports, cutscenes, spectate, off-radar, bounty abuse, and other grief script events", true};
	static BlockSpam _prot_spam{"prot_spam", "Block Spam", "Blocks sound spam, SMS, and fake notification events", true};
}
