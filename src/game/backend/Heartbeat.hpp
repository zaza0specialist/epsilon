#pragma once

namespace YimMenu::Features
{
	// Periodic line from the script/fiber context. A crash vector aimed at the host
	// kills the game's script threads, but the network hooks keep logging, so the
	// network log alone cannot tell the two apart. If the heartbeat stops while
	// net events keep arriving, the script context died.
	void RunHeartbeatScript();
}
