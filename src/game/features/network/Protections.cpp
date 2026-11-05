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

	// Crash protections (YimMenuV2 PR #1179 style)
	class BlockExplosionCrash : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockWeaponExploits : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockRadioHijack : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockDoorBreak : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockWorldStateCrash : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockEntitySyncCrash : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockNetEventCrash : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockScriptEventCrash : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockEntityState : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockCrashBait : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockRagdollNet : public BoolCommand { using BoolCommand::BoolCommand; };

	// Script event protections
	class BlockModdedSessionEvents : public BoolCommand { using BoolCommand::BoolCommand; };
	class SmartProtection : public BoolCommand { using BoolCommand::BoolCommand; };
	class AdvancedScriptEventProtection : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockModdedReports : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockEntitySpam : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockAntiSpectate : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockRemoteCameraShake : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockControlSwap : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockAntiCrash : public BoolCommand { using BoolCommand::BoolCommand; };

	static BlockKicks _prot_kicks{"prot_kicks", "Block Kicks", "Blocks remote kick script events (CEO ban, vehicle kick, network bail, kick from interior)", true};
	static BlockGrief _prot_grief{"prot_grief", "Block Griefing", "Blocks forced teleports, cutscenes, spectate, bounty abuse, forced missions, and other grief script events", true};
	static BlockSpam _prot_spam{"prot_spam", "Block Spam", "Blocks sound spam, SMS, fake notifications, and rate-limits explosion/PTFX/weapon/script event floods", true};
	static BlockCash _prot_cash{"prot_cash", "Block Cash Drops", "Blocks forced money events (CEO money, fake cash spawn notifications)", true};
	static ChatAds _prot_chat{"prot_chat", "Block Chat Ads", "Hides chat messages containing links or advertisements", true};
	static LogNetEvents _prot_lognet{"prot_lognet", "Log Net Events", "Logs every received net game event to cout.log (diagnostics)", false};
	static LogUnknownEvents _prot_logunknown{"prot_logunknown", "Log Unknown Script Events", "Logs the hash and payload of script events we don't recognize yet — use this to capture hashes for new kick vectors", false};
	static CompatMode _prot_compat{"prot_compat", "Compatibility Mode", "Logs every event instead of blocking anything — use this to test whether a legitimate player is being broken by our protections", false};

	// Crash protections
	static BlockExplosionCrash _prot_expl_crash{"prot_expl_crash", "Anti Explosion Crash", "Blocks explosion crash script events", false};
	static BlockWeaponExploits _prot_weapon_exp{"prot_weapon_exp", "Anti Weapon Exploits", "Blocks weapon exploit script events", false};
	static BlockRadioHijack _prot_radio_hijack{"prot_radio_hijack", "Anti Radio Hijack", "Blocks radio hijack script events", false};
	static BlockDoorBreak _prot_door_break{"prot_door_break", "Anti Door Break", "Blocks door break script events", false};
	static BlockWorldStateCrash _prot_world_crash{"prot_world_crash", "Anti World State Crash", "Blocks world state crash script events", false};
	static BlockEntitySyncCrash _prot_entity_sync{"prot_entity_sync", "Entity Sync Crash Protection", "Blocks entity sync crash events", false};
	static BlockNetEventCrash _prot_net_crash{"prot_net_crash", "Net Event Crash Protection", "Blocks net event crash events", false};
	static BlockScriptEventCrash _prot_script_crash{"prot_script_crash", "Script Event Crash Protection", "Blocks script event crash events", false};
	static BlockEntityState _prot_ent_state{"prot_ent_state", "Anti Entity State", "Blocks entity state manipulation", false};
	static BlockCrashBait _prot_crash_bait{"prot_crash_bait", "Crash Bait Guard", "Blocks crash bait script events", false};
	static BlockRagdollNet _prot_ragdoll_net{"prot_ragdoll_net", "Anti Ragdoll Net", "Blocks ragdoll network events", false};

	// Script event protections
	static BlockModdedSessionEvents _prot_mod_session{"prot_mod_session", "Block Modded Session Events", "Blocks modded session script events", false};
	static SmartProtection _prot_smart_prot{"prot_smart_prot", "Smart Protection", "Smart protection against unknown script events", false};
	static AdvancedScriptEventProtection _prot_adv_script{"prot_adv_script", "Advanced Script Event Protection", "Advanced protection against script events", false};
	static BlockModdedReports _prot_mod_reports{"prot_mod_reports", "Block Modded Reports", "Blocks modded report events", false};
	static BlockEntitySpam _prot_ent_spam{"prot_ent_spam", "Anti Entity Spam", "Blocks entity spam events", false};
	static BlockAntiSpectate _prot_anti_spectate{"prot_anti_spectate", "Anti Spectate", "Blocks spectate events", false};
	static BlockRemoteCameraShake _prot_remote_cam{"prot_remote_cam", "Anti Remote Camera Shake", "Blocks remote camera shake events", false};
	static BlockControlSwap _prot_ctrl_swap{"prot_ctrl_swap", "Anti Control Swap", "Blocks control swap events", false};
	static BlockAntiCrash _prot_anti_crash{"prot_anti_crash", "Anti Crash", "Blocks general crash script events", false};
}
