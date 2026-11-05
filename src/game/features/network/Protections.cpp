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

	// Anti-kick protections
	class BlockAutoKick : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockHostKick : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockSessionKick : public BoolCommand { using BoolCommand::BoolCommand; };
	static BlockAutoKick _prot_anti_kick{"prot_anti_kick", "Anti Auto Kick", "Blocks NETWORK_SESSION_KICK_PLAYER from being sent", false};
	static BlockHostKick _prot_host_kick{"prot_host_kick", "Anti Host Kick", "Blocks host kick attempts against your session", false};
	static BlockSessionKick _prot_session_kick{"prot_session_kick", "Anti Session Kick", "Blocks session kick events from other players", false};

	// Anti-spam protections
	class BlockBountySpam : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockPedSpam : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockVehicleSpam : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockExplosionSpam : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockPTFXSpam : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockSoundSpam : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockStunGunSpam : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockChatAds : public BoolCommand { using BoolCommand::BoolCommand; };

	// Anti-trolling protections
	class BlockModdedSounds : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockModdedPTFX : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockCages : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockRemoteBounty : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockRemoteClearTask : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockRemoteRagdoll : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockRemoteControl : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockAllControl : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockRemoveWeapon : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockGiveWeapon : public BoolCommand { using BoolCommand::BoolCommand; };

	// Local shields
	class ExplosionFireImmunity : public BoolCommand { using BoolCommand::BoolCommand; };
	class ClearProjectiles : public BoolCommand { using BoolCommand::BoolCommand; };
	class ClearParticles : public BoolCommand { using BoolCommand::BoolCommand; };
	class PhysicsGuard : public BoolCommand { using BoolCommand::BoolCommand; };
	class AntiVehicleRam : public BoolCommand { using BoolCommand::BoolCommand; };
	class AntiVehicleKick : public BoolCommand { using BoolCommand::BoolCommand; };
	class AntiStunRagdoll : public BoolCommand { using BoolCommand::BoolCommand; };
	class VehicleGuard : public BoolCommand { using BoolCommand::BoolCommand; };
	class SaveWeaponSnapshot : public BoolCommand { using BoolCommand::BoolCommand; };
	class WeaponGuard : public BoolCommand { using BoolCommand::BoolCommand; };
	class MenuCrashShield : public BoolCommand { using BoolCommand::BoolCommand; };

	// Script event guards
	class BlockBounty : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockSMS : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockCEO : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockInterior : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockAntiDetection : public BoolCommand { using BoolCommand::BoolCommand; };
	class BlockAntiSpam : public BoolCommand { using BoolCommand::BoolCommand; };

	// Other/kick protections
	class FreemodeKickProtection : public BoolCommand { using BoolCommand::BoolCommand; };
	class ScriptHostKickProtection : public BoolCommand { using BoolCommand::BoolCommand; };
	class EndSessionKickProtection : public BoolCommand { using BoolCommand::BoolCommand; };
	class NetErrorKickProtection : public BoolCommand { using BoolCommand::BoolCommand; };
	class WarnDirectConnections : public BoolCommand { using BoolCommand::BoolCommand; };
	class DisableCamShake : public BoolCommand { using BoolCommand::BoolCommand; };
	class NotifySpectate : public BoolCommand { using BoolCommand::BoolCommand; };

	static BlockBountySpam _prot_bounty_spam{"prot_bounty_spam", "Anti Bounty Spam", "Blocks bounty spam script events", false};
	static BlockPedSpam _prot_ped_spam{"prot_ped_spam", "Anti Ped Spam", "Blocks ped spam events", false};
	static BlockVehicleSpam _prot_vehicle_spam{"prot_vehicle_spam", "Anti Vehicle Spam", "Blocks vehicle spam events", false};
	static BlockExplosionSpam _prot_explosion_spam{"prot_explosion_spam", "Anti Explosion Spam", "Blocks explosion spam events", false};
	static BlockPTFXSpam _prot_ptfx_spam{"prot_ptfx_spam", "Anti PTFX Spam", "Blocks PTFX spam events", false};
	static BlockSoundSpam _prot_sound_spam{"prot_sound_spam", "Anti Sound Spam", "Blocks sound spam events", false};
	static BlockStunGunSpam _prot_stun_gun_spam{"prot_stun_gun_spam", "Anti Stun Gun Spam", "Blocks stun gun spam events", false};
	static BlockChatAds _prot_chat_ads{"prot_chat_ads", "Anti Chat Ads", "Blocks chat advertisement spam", false};

	static BlockModdedSounds _prot_modded_sounds{"prot_modded_sounds", "Anti Modded Sounds", "Blocks modded sound events", false};
	static BlockModdedPTFX _prot_modded_ptfx{"prot_modded_ptfx", "Anti Modded PTFX", "Blocks modded PTFX events", false};
	static BlockCages _prot_cages{"prot_cages", "Anti Cages", "Blocks cage trap events", false};
	static BlockRemoteBounty _prot_remote_bounty{"prot_remote_bounty", "Anti Remote Bounty", "Blocks remote bounty events", false};
	static BlockRemoteClearTask _prot_remote_clear_task{"prot_remote_clear_task", "Anti Remote Clear Task", "Blocks remote clear task events", false};
	static BlockRemoteRagdoll _prot_remote_ragdoll{"prot_remote_ragdoll", "Anti Remote Ragdoll", "Blocks remote ragdoll events", false};
	static BlockRemoteControl _prot_remote_control{"prot_remote_control", "Anti Remote Control", "Blocks remote control events", false};
	static BlockAllControl _prot_all_control{"prot_all_control", "Anti All Control", "Blocks all control override events", false};
	static BlockRemoveWeapon _prot_remove_weapon{"prot_remove_weapon", "Anti Remove Weapon", "Blocks weapon removal events", false};
	static BlockGiveWeapon _prot_give_weapon{"prot_give_weapon", "Anti Give Weapon", "Blocks forced weapon give events", false};

	static ExplosionFireImmunity _prot_expl_immunity{"prot_expl_immunity", "Explosion/Fire Immunity", "Grants immunity to explosion and fire damage", false};
	static ClearProjectiles _prot_clear_proj{"prot_clear_proj", "Clear Projectiles", "Automatically clears incoming projectiles", false};
	static ClearParticles _prot_clear_particles{"prot_clear_particles", "Clear Particles", "Automatically clears particle effects", false};
	static PhysicsGuard _prot_physics_guard{"prot_physics_guard", "Physics Guard", "Protects against physics manipulation", false};
	static AntiVehicleRam _prot_vehicle_ram{"prot_vehicle_ram", "Anti Vehicle Ram", "Blocks vehicle ramming attempts", false};
	static AntiVehicleKick _prot_vehicle_kick{"prot_vehicle_kick", "Anti Vehicle Kick", "Blocks vehicle kick attempts", false};
	static AntiStunRagdoll _prot_stun_ragdoll{"prot_stun_ragdoll", "Anti Stun/Ragdoll", "Blocks stun and ragdoll effects", false};
	static VehicleGuard _prot_vehicle_guard{"prot_vehicle_guard", "Vehicle Guard", "Protects your vehicle from tampering", false};
	static SaveWeaponSnapshot _prot_weapon_snapshot{"prot_weapon_snapshot", "Save Weapon Snapshot", "Saves your weapon loadout", false};
	static WeaponGuard _prot_weapon_guard{"prot_weapon_guard", "Weapon Guard", "Protects your weapons from being removed", false};
	static MenuCrashShield _prot_menu_crash_shield{"prot_menu_crash_shield", "Menu Crash Shield", "Protects against menu crash events", false};

	static BlockBounty _prot_bounty{"prot_bounty", "Anti Bounty", "Blocks bounty script events", false};
	static BlockSMS _prot_sms_spam{"prot_sms_spam", "Anti SMS Spam", "Blocks SMS spam events", false};
	static BlockCEO _prot_ceo_kick{"prot_ceo_kick", "Anti CEO Kick", "Blocks CEO kick events", false};
	static BlockInterior _prot_interior{"prot_interior", "Anti Interior", "Blocks interior teleport events", false};
	static BlockAntiDetection _prot_anti_detection{"prot_anti_detection", "Anti Detection", "Blocks detection events", false};
	static BlockAntiSpam _prot_anti_spam{"prot_anti_spam", "Anti Spam", "Blocks general spam events", false};

	static FreemodeKickProtection _prot_freemode_kick{"prot_freemode_kick", "Freemode Kick Protection", "Protects against freemode kicks", false};
	static ScriptHostKickProtection _prot_script_host_kick{"prot_script_host_kick", "Script Host Kick Protection", "Protects against script host kicks", false};
	static EndSessionKickProtection _prot_end_session_kick{"prot_end_session_kick", "End Session Kick Protection", "Protects against session end kicks", false};
	static NetErrorKickProtection _prot_net_error_kick{"prot_net_error_kick", "Net Error Kick Protection", "Protects against network error kicks", false};
	static WarnDirectConnections _prot_warn_direct{"prot_warn_direct", "Warn On Direct Connections", "Warns on direct connection attempts", false};
	static DisableCamShake _prot_disable_cam_shake{"prot_disable_cam_shake", "Disable Cam Shake", "Disables camera shake effects", false};
	static NotifySpectate _prot_notify_spectate{"prot_notify_spectate", "Notify Spectate", "Notifies when someone spectates you", false};

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
