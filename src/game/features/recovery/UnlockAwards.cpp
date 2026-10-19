#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"
#include "game/pointers/Pointers.hpp"

// Ported from reference/Ultimate_Menu_V3_1.73_Legacy.lua (Awards Unlocker Menu)
namespace YimMenu::Features
{
	static void AwardsVictory()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_AWD_FM_DM_WINS", 50);
	        Stats::SetInt("MPX_AWD_FM_TDM_WINS", 50);
	        Stats::SetInt("MPX_AWD_FM_TDM_MVP", 50);
	        Stats::SetInt("MPX_AWD_RACES_WON", 50);
	        Stats::SetInt("MPX_AWD_FMWINAIRRACE", 25);
	        Stats::SetInt("MPX_AWD_FMWINSEARACE", 25);
	        Stats::SetInt("MPX_AWD_FM_GTA_RACES_WON", 50);
	        Stats::SetBool("MPX_AWD_FMKILL3ANDWINGTARACE", true);
	        Stats::SetInt("MPX_AWD_FMRALLYWONDRIVE", 25);
	        Stats::SetInt("MPX_AWD_FMRALLYWONNAV", 25);
	        Stats::SetBool("MPX_AWD_FMWINCUSTOMRACE", true);
	        Stats::SetInt("MPX_AWD_FMWINRACETOPOINTS", 25);
	        Stats::SetBool("MPX_CL_RACE_MODDED_CAR", true);
	        Stats::SetInt("MPX_AWD_FM_RACE_LAST_FIRST", 25);
	        Stats::SetBool("MPX_AWD_FMRACEWORLDRECHOLDER", true);
	        Stats::SetInt("MPX_AWD_FM_RACES_FASTEST_LAP", 50);
	        Stats::SetBool("MPX_AWD_FMWINALLRACEMODES", true);
	        Stats::SetInt("MPX_AWD_FMHORDWAVESSURVIVE", 10);
	        Stats::SetInt("MPX_NUMBER_SLIPSTREAMS_IN_RACE", 100);
	        Stats::SetInt("MPX_NUMBER_TURBO_STARTS_IN_RACE", 50);
	        Stats::SetInt("MPX_AWD_NO_ARMWRESTLING_WINS", 25);
	        Stats::SetInt("MPX_MOST_ARM_WRESTLING_WINS", 25);
	        Stats::SetInt("MPX_AWD_WIN_AT_DARTS", 25);
	        Stats::SetInt("MPX_AWD_FM_GOLF_WON", 25);
	        Stats::SetInt("MPX_AWD_FM_TENNIS_WON", 25);
	        Stats::SetBool("MPX_AWD_FM_TENNIS_5_SET_WINS", true);
	        Stats::SetBool("MPX_AWD_FM_TENNIS_STASETWIN", true);
	        Stats::SetInt("MPX_AWD_FM_SHOOTRANG_CT_WON", 25);
	        Stats::SetInt("MPX_AWD_FM_SHOOTRANG_RT_WON", 25);
	        Stats::SetInt("MPX_AWD_FM_SHOOTRANG_TG_WON", 25);
	        Stats::SetBool("MPX_AWD_FM_SHOOTRANG_GRAN_WON", true);
	        Stats::SetBool("MPX_AWD_FMWINEVERYGAMEMODE", true);
	        Stats::SetInt("MPX_AWD_WIN_CAPTURES", 50);
	        Stats::SetInt("MPX_AWD_WIN_CAPTURE_DONT_DYING", 25);
	        Stats::SetInt("MPX_AWD_WIN_LAST_TEAM_STANDINGS", 50);
	        Stats::SetInt("MPX_AWD_ONLY_PLAYER_ALIVE_LTS", 50);
	        Stats::SetInt("MPX_AWD_KILL_TEAM_YOURSELF_LTS", 25);
	        Stats::SetInt("MPX_AIR_LAUNCHES_OVER_40M", 25);
	        Stats::SetInt("MPX_AWD_CARS_EXPORTED", 50);
	        Stats::SetInt("MPX_AWD_LESTERDELIVERVEHICLES", 25);
	        Stats::SetInt("MPX_TOTAL_RACES_WON", 500);
	        Stats::SetInt("MPX_TOTAL_RACES_LOST", 250);
	        Stats::SetInt("MPX_TOTAL_CUSTOM_RACES_WON", 500);
	        Stats::SetInt("MPX_TOTAL_DEATHMATCH_LOST", 250);
	        Stats::SetInt("MPX_TOTAL_DEATHMATCH_WON", 500);
	        Stats::SetInt("MPX_TOTAL_TDEATHMATCH_LOST", 250);
	        Stats::SetInt("MPX_TOTAL_TDEATHMATCH_WON", 500);
	        Stats::SetInt("MPX_SHOOTINGRANGE_WINS", 500);
	        Stats::SetInt("MPX_SHOOTINGRANGE_LOSSES", 250);
	        Stats::SetInt("MPX_TENNIS_MATCHES_WON", 500);
	        Stats::SetInt("MPX_TENNIS_MATCHES_LOST", 250);
	        Stats::SetInt("MPX_GOLF_WINS", 500);
	        Stats::SetInt("MPX_GOLF_LOSSES", 250);
	        Stats::SetInt("MPX_DARTS_TOTAL_WINS", 500);
	        Stats::SetInt("MPX_DARTS_TOTAL_MATCHES", 750);
	        Stats::SetInt("MPX_SHOOTINGRANGE_TOTAL_MATCH", 800);
	        Stats::SetInt("MPX_BJ_WINS", 500);
	        Stats::SetInt("MPX_BJ_LOST", 250);
	        Stats::SetInt("MPX_RACE_2_POINT_WINS", 500);
	        Stats::SetInt("MPX_RACE_2_POINT_LOST", 250);
	        Stats::SetInt("MPX_KILLS_PLAYERS", 3593);
	        Stats::SetInt("MPX_DEATHS_PLAYER", 1002);
	        Stats::SetInt("MPX_MISSIONS_CREATED", 500);
	        Stats::SetInt("MPX_LTS_CREATED", 500);
	        Stats::SetInt("MPX_FM_MISSION_LIKES", 1500);
	}

	static void AwardsGeneral()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetBool("MPX_AWD_FM25DIFFERENTDM", true);
	        Stats::SetInt("MPX_CR_DIFFERENT_DM", 25);
	        Stats::SetBool("MPX_AWD_FM25DIFFERENTRACES", true);
	        Stats::SetInt("MPX_CR_DIFFERENT_RACES", 25);
	        Stats::SetInt("MPX_AWD_PARACHUTE_JUMPS_20M", 25);
	        Stats::SetInt("MPX_AWD_PARACHUTE_JUMPS_50M", 25);
	        Stats::SetInt("MPX_AWD_FMBASEJMP", 25);
	        Stats::SetBool("MPX_AWD_FMATTGANGHQ", true);
	        Stats::SetBool("MPX_AWD_FM6DARTCHKOUT", true);
	        Stats::SetInt("MPX_AWD_FM_GOLF_BIRDIES", 25);
	        Stats::SetBool("MPX_AWD_FM_GOLF_HOLE_IN_1", true);
	        Stats::SetInt("MPX_AWD_FM_TENNIS_ACE", 25);
	        Stats::SetInt("MPX_AWD_FMBBETWIN", 50000);
	        Stats::SetInt("MPX_AWD_LAPDANCES", 25);
	        Stats::SetInt("MPX_AWD_FMCRATEDROPS", 25);
	        Stats::SetBool("MPX_AWD_FMPICKUPDLCCRATE1ST", true);
	        Stats::SetBool("MPX_AWD_FM25DIFITEMSCLOTHES", true);
	        Stats::SetInt("MPX_AWD_NO_HAIRCUTS", 25);
	        Stats::SetBool("MPX_AWD_BUY_EVERY_GUN", true);
	        Stats::SetBool("MPX_AWD_DRIVELESTERCAR5MINS", true);
	        Stats::SetBool("MPX_AWD_FMTATTOOALLBODYPARTS", true);
	        Stats::SetInt("MPX_AWD_DROPOFF_CAP_PACKAGES", 100);
	        Stats::SetInt("MPX_AWD_PICKUP_CAP_PACKAGES", 100);
	        Stats::SetInt("MPX_AWD_MENTALSTATE_TO_NORMAL", 50);
	        Stats::SetBool("MPX_AWD_STORE_20_CAR_IN_GARAGES", true);
	        Stats::SetInt("MPX_AWD_TRADE_IN_YOUR_PROPERTY", 25);
	        Stats::SetBool("MPX_AWD_DAILYOBJWEEKBONUS", true);
	        Stats::SetBool("MPX_AWD_DAILYOBJMONTHBONUS", true);
	        Stats::SetInt("MPX_AWD_FM_CR_DM_MADE", 25);
	        Stats::SetInt("MPX_AWD_FM_CR_RACES_MADE", 25);
	        Stats::SetInt("MPX_AWD_FM_CR_PLAYED_BY_PEEP", 1598);
	        Stats::SetInt("MPX_AWD_FM_CR_MISSION_SCORE", 100);
	        Stats::SetBool("MPX_CL_DRIVE_RALLY", true);
	        Stats::SetBool("MPX_CL_PLAY_GTA_RACE", true);
	        Stats::SetBool("MPX_CL_PLAY_BOAT_RACE", true);
	        Stats::SetBool("MPX_CL_PLAY_FOOT_RACE", true);
	        Stats::SetBool("MPX_CL_PLAY_TEAM_DM", true);
	        Stats::SetBool("MPX_CL_PLAY_VEHICLE_DM", true);
	        Stats::SetBool("MPX_CL_PLAY_MISSION_CONTACT", true);
	        Stats::SetBool("MPX_CL_PLAY_A_PLAYLIST", true);
	        Stats::SetBool("MPX_CL_PLAY_POINT_TO_POINT", true);
	        Stats::SetBool("MPX_CL_PLAY_ONE_ON_ONE_DM", true);
	        Stats::SetBool("MPX_CL_PLAY_ONE_ON_ONE_RACE", true);
	        Stats::SetBool("MPX_CL_SURV_A_BOUNTY", true);
	        Stats::SetBool("MPX_CL_SET_WANTED_LVL_ON_PLAY", true);
	        Stats::SetBool("MPX_CL_GANG_BACKUP_GANGS", true);
	        Stats::SetBool("MPX_CL_GANG_BACKUP_LOST", true);
	        Stats::SetBool("MPX_CL_GANG_BACKUP_VAGOS", true);
	        Stats::SetBool("MPX_CL_CALL_MERCENARIES", true);
	        Stats::SetBool("MPX_CL_PHONE_MECH_DROP_CAR", true);
	        Stats::SetBool("MPX_CL_GONE_OFF_RADAR", true);
	        Stats::SetBool("MPX_CL_FILL_TITAN", true);
	        Stats::SetBool("MPX_CL_MOD_CAR_USING_APP", true);
	        Stats::SetBool("MPX_CL_MOD_CAR_USING_APP", true);
	        Stats::SetBool("MPX_CL_BUY_INSURANCE", true);
	        Stats::SetBool("MPX_CL_BUY_GARAGE", true);
	        Stats::SetBool("MPX_CL_ENTER_FRIENDS_HOUSE", true);
	        Stats::SetBool("MPX_CL_CALL_STRIPPER_HOUSE", true);
	        Stats::SetBool("MPX_CL_CALL_FRIEND", true);
	        Stats::SetBool("MPX_CL_SEND_FRIEND_REQUEST", true);
	        Stats::SetBool("MPX_CL_W_WANTED_PLAYER_TV", true);
	        Stats::SetBool("MPX_FM_INTRO_CUT_DONE", true);
	        Stats::SetBool("MPX_FM_INTRO_MISS_DONE", true);
	        Stats::SetBool("MPX_SHOOTINGRANGE_SEEN_TUT", true);
	        Stats::SetBool("MPX_TENNIS_SEEN_TUTORIAL", true);
	        Stats::SetBool("MPX_DARTS_SEEN_TUTORIAL", true);
	        Stats::SetBool("MPX_ARMWRESTLING_SEEN_TUTORIAL", true);
	        Stats::SetBool("MPX_HAS_WATCHED_BENNY_CUTSCE", true);
	        Stats::SetInt("MPX_NO_PHOTOS_TAKEN", 100);
	        Stats::SetInt("MPX_BOUNTSONU", 200);
	        Stats::SetInt("MPX_BOUNTPLACED", 500);
	        Stats::SetInt("MPX_BETAMOUNT", 500);
	        Stats::SetInt("MPX_CRARMWREST", 500);
	        Stats::SetInt("MPX_CRBASEJUMP", 500);
	        Stats::SetInt("MPX_CRDARTS", 500);
	        Stats::SetInt("MPX_CRDM", 500);
	        Stats::SetInt("MPX_CRGANGHIDE", 500);
	        Stats::SetInt("MPX_CRGOLF", 500);
	        Stats::SetInt("MPX_CRHORDE", 500);
	        Stats::SetInt("MPX_CRMISSION", 500);
	        Stats::SetInt("MPX_CRSHOOTRNG", 500);
	        Stats::SetInt("MPX_CRTENNIS", 500);
	        Stats::SetInt("MPX_NO_TIMES_CINEMA", 500);
	}

	static void AwardsWeapons()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_CHAR_WEAP_UNLOCKED", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_UNLOCKED2", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_UNLOCKED3", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_UNLOCKED4", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_ADDON_1_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_ADDON_2_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_ADDON_3_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_ADDON_4_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_FREE", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_FREE2", -1);
	        Stats::SetInt("MPX_CHAR_FM_WEAP_FREE", -1);
	        Stats::SetInt("MPX_CHAR_FM_WEAP_FREE2", -1);
	        Stats::SetInt("MPX_CHAR_FM_WEAP_FREE3", -1);
	        Stats::SetInt("MPX_CHAR_FM_WEAP_FREE4", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_PURCHASED", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_PURCHASED2", -1);
	        Stats::SetInt("MPX_WEAPON_PICKUP_BITSET", -1);
	        Stats::SetInt("MPX_WEAPON_PICKUP_BITSET2", -1);
	        Stats::SetInt("MPX_CHAR_FM_WEAP_UNLOCKED", -1);
	        Stats::SetInt("MPX_NO_WEAPONS_UNLOCK", -1);
	        Stats::SetInt("MPX_NO_WEAPON_MODS_UNLOCK", -1);
	        Stats::SetInt("MPX_NO_WEAPON_CLR_MOD_UNLOCK", -1);
	        Stats::SetInt("MPX_CHAR_FM_WEAP_UNLOCKED2", -1);
	        Stats::SetInt("MPX_CHAR_FM_WEAP_UNLOCKED3", -1);
	        Stats::SetInt("MPX_CHAR_FM_WEAP_UNLOCKED4", -1);
	        Stats::SetInt("MPX_CHAR_KIT_1_FM_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_KIT_2_FM_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_KIT_3_FM_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_KIT_4_FM_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_KIT_5_FM_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_KIT_6_FM_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_KIT_7_FM_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_KIT_8_FM_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_KIT_9_FM_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_KIT_10_FM_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_KIT_11_FM_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_KIT_12_FM_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_KIT_FM_PURCHASE", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_FM_PURCHASE", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_FM_PURCHASE2", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_FM_PURCHASE3", -1);
	        Stats::SetInt("MPX_CHAR_WEAP_FM_PURCHASE4", -1);
	        Stats::SetInt("MPX_FIREWORK_TYPE_1_WHITE", 1000);
	        Stats::SetInt("MPX_FIREWORK_TYPE_1_RED", 1000);
	        Stats::SetInt("MPX_FIREWORK_TYPE_1_BLUE", 1000);
	        Stats::SetInt("MPX_FIREWORK_TYPE_2_WHITE", 1000);
	        Stats::SetInt("MPX_FIREWORK_TYPE_2_RED", 1000);
	        Stats::SetInt("MPX_FIREWORK_TYPE_2_BLUE", 1000);
	        Stats::SetInt("MPX_FIREWORK_TYPE_3_WHITE", 1000);
	        Stats::SetInt("MPX_FIREWORK_TYPE_3_RED", 1000);
	        Stats::SetInt("MPX_FIREWORK_TYPE_3_BLUE", 1000);
	        Stats::SetInt("MPX_FIREWORK_TYPE_4_WHITE", 1000);
	        Stats::SetInt("MPX_FIREWORK_TYPE_4_RED", 1000);
	        Stats::SetInt("MPX_FIREWORK_TYPE_4_BLUE", 1000);
	        Stats::SetInt("MPX_WEAP_FM_ADDON_PURCH", -1);
	        for (int i = 2; i <= 19; i++) {
	            Stats::SetInt("MPX_WEAP_FM_ADDON_PURCH" + std::to_string(i), -1);
	        }
	        for (int j = 1; j <= 19; j++) {
	            Stats::SetInt("MPX_CHAR_FM_WEAP_ADDON_" + std::to_string(j) + "_UNLCK", -1);
	        }
	        for (int m = 1; m <= 41; m++) {
	            Stats::SetInt("MPX_CHAR_KIT_" + std::to_string(m) + "_FM_UNLCK", -1);
	        }
	        for (int l = 2; l <= 41; l++) {
	            Stats::SetInt("MPX_CHAR_KIT_FM_PURCHASE" + std::to_string(l), -1);
	        }
	}

	static void AwardsCrimes()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_AWD_FMTIME5STARWANTED", 120);
	        Stats::SetInt("MPX_AWD_5STAR_WANTED_AVOIDANCE", 50);
	        Stats::SetInt("MPX_AWD_FMSHOOTDOWNCOPHELI", 25);
	        Stats::SetInt("MPX_AWD_VEHICLES_JACKEDR", 500);
	        Stats::SetInt("MPX_AWD_SECURITY_CARS_ROBBED", 25);
	        Stats::SetInt("MPX_AWD_HOLD_UP_SHOPS", 20);
	        Stats::SetInt("MPX_AWD_ODISTRACTCOPSNOEATH", 25);
	        Stats::SetInt("MPX_AWD_ENEMYDRIVEBYKILLS", 100);
	        Stats::SetInt("MPX_CHAR_WANTED_LEVEL_TIME5STAR", 18000000);
	        Stats::SetInt("MPX_CARS_COPS_EXPLODED", 300);
	        Stats::SetInt("MPX_BIKES_EXPLODED", 100);
	        Stats::SetInt("MPX_BOATS_EXPLODED", 168);
	        Stats::SetInt("MPX_HELIS_EXPLODED", 98);
	        Stats::SetInt("MPX_PLANES_EXPLODED", 138);
	        Stats::SetInt("MPX_QUADBIKE_EXPLODED", 50);
	        Stats::SetInt("MPX_BICYCLE_EXPLODED", 48);
	        Stats::SetInt("MPX_SUBMARINE_EXPLODED", 28);
	        Stats::SetInt("MPX_TIRES_POPPED_BY_GUNSHOT", 500);
	        Stats::SetInt("MPX_NUMBER_CRASHES_CARS", 300);
	        Stats::SetInt("MPX_NUMBER_CRASHES_BIKES", 300);
	        Stats::SetInt("MPX_BAILED_FROM_VEHICLE", 300);
	        Stats::SetInt("MPX_NUMBER_CRASHES_QUADBIKES", 300);
	        Stats::SetInt("MPX_NUMBER_STOLEN_COP_VEHICLE", 300);
	        Stats::SetInt("MPX_NUMBER_STOLEN_CARS", 300);
	        Stats::SetInt("MPX_NUMBER_STOLEN_BIKES", 300);
	        Stats::SetInt("MPX_NUMBER_STOLEN_BOATS", 300);
	        Stats::SetInt("MPX_NUMBER_STOLEN_HELIS", 300);
	        Stats::SetInt("MPX_NUMBER_STOLEN_PLANES", 300);
	        Stats::SetInt("MPX_NUMBER_STOLEN_QUADBIKES", 300);
	        Stats::SetInt("MPX_NUMBER_STOLEN_BICYCLES", 300);
	        Stats::SetInt("MPX_MC_CONTRIBUTION_POINTS", 1000);
	        Stats::SetInt("MPX_MEMBERSMARKEDFORDEATH", 700);
	        Stats::SetInt("MPX_MCKILLS", 500);
	        Stats::SetInt("MPX_MCDEATHS", 700);
	        Stats::SetInt("MPX_RIVALPRESIDENTKILLS", 700);
	        Stats::SetInt("MPX_RIVALCEOANDVIPKILLS", 700);
	        Stats::SetInt("MPX_CLUBHOUSECONTRACTSCOMPLETE", 700);
	        Stats::SetInt("MPX_CLUBHOUSECONTRACTEARNINGS", 32698547);
	        Stats::SetInt("MPX_CLUBCHALLENGESCOMPLETED", 700);
	        Stats::SetInt("MPX_MEMBERCHALLENGESCOMPLETED", 700);
	        Stats::SetInt("MPX_GHKILLS", 500);
	        Stats::SetInt("MPX_HORDELVL", 10);
	        Stats::SetInt("MPX_HORDKILLS", 500);
	        Stats::SetInt("MPX_UNIQUECRATES", 500);
	        Stats::SetInt("MPX_BJWINS", 500);
	        Stats::SetInt("MPX_HORDEWINS", 500);
	        Stats::SetInt("MPX_MCMWINS", 500);
	        Stats::SetInt("MPX_GANGHIDWINS", 500);
	        Stats::SetInt("MPX_KILLS", 800);
	        Stats::SetInt("MPX_HITS_PEDS_VEHICLES", 100);
	        Stats::SetInt("MPX_SHOTS", 1000);
	        Stats::SetInt("MPX_HEADSHOTS", 100);
	        Stats::SetInt("MPX_KILLS_ARMED", 650);
	        Stats::SetInt("MPX_SUCCESSFUL_COUNTERS", 100);
	        Stats::SetInt("MPX_KILLS_PLAYERS", 3593);
	        Stats::SetInt("MPX_DEATHS_PLAYER", 1002);
	        Stats::SetInt("MPX_KILLS_STEALTH", 100);
	        Stats::SetInt("MPX_KILLS_INNOCENTS", 500);
	        Stats::SetInt("MPX_KILLS_ENEMY_GANG_MEMBERS", 500);
	        Stats::SetInt("MPX_KILLS_FRIENDLY_GANG_MEMBERS", 500);
	        Stats::SetInt("MPX_KILLS_BY_OTHERS", 100);
	        Stats::SetInt("MPX_BIGGEST_VICTIM_KILLS", 500);
	        Stats::SetInt("MPX_ARCHENEMY_KILLS", 500);
	        Stats::SetInt("MPX_KILLS_COP", 4500);
	        Stats::SetInt("MPX_KILLS_SWAT", 500);
	        Stats::SetInt("MPX_STARS_ATTAINED", 5000);
	        Stats::SetInt("MPX_STARS_EVADED", 4000);
	        Stats::SetInt("MPX_VEHEXPORTED", 500);
	        Stats::SetInt("MPX_TOTAL_NO_SHOPS_HELD_UP", 100);
	        Stats::SetInt("MPX_CR_GANGATTACK_CITY", 1000);
	        Stats::SetInt("MPX_CR_GANGATTACK_COUNTRY", 1000);
	        Stats::SetInt("MPX_CR_GANGATTACK_LOST", 1000);
	        Stats::SetInt("MPX_CR_GANGATTACK_VAGOS", 1000);
	        Stats::SetInt("MPX_NO_NON_CONTRACT_RACE_WIN", 500);
	        Stats::SetInt("MPX_DIED_IN_DROWNING", 833);
	        Stats::SetInt("MPX_DIED_IN_DROWNINGINVEHICLE", 833);
	        Stats::SetInt("MPX_DIED_IN_EXPLOSION", 833);
	        Stats::SetInt("MPX_DIED_IN_FALL", 833);
	        Stats::SetInt("MPX_DIED_IN_FIRE", 833);
	        Stats::SetInt("MPX_DIED_IN_ROAD", 833);
	        Stats::SetInt("MPX_GRENADE_ENEMY_KILLS", 50);
	        Stats::SetInt("MPX_MICROSMG_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_SMG_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_ASLTSMG_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_CRBNRIFLE_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_ADVRIFLE_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_MG_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_CMBTMG_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_ASLTMG_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_RPG_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_PISTOL_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_PLAYER_HEADSHOTS", 500);
	        Stats::SetInt("MPX_SAWNOFF_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_STKYBMB_ENEMY_KILLS", 50);
	        Stats::SetInt("MPX_UNARMED_ENEMY_KILLS", 50);
	        Stats::SetInt("MPX_SNIPERRFL_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_HVYSNIPER_ENEMY_KILLS", 500);
	}

	static void AwardsVehicles()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_AWD_50_VEHICLES_BLOWNUP", 500);
	        Stats::SetInt("MPX_CARS_EXPLODED", 500);
	        Stats::SetInt("MPX_AWD_CAR_EXPORT", 100);
	        Stats::SetInt("MPX_AWD_FMDRIVEWITHOUTCRASH", 30);
	        Stats::SetInt("MPX_AWD_PASSENGERTIME", 4);
	        Stats::SetInt("MPX_AWD_TIME_IN_HELICOPTER", 4);
	        Stats::SetInt("MPX_AWD_VEHICLE_JUMP_OVER_40M", 25);
	        Stats::SetInt("MPX_MOST_FLIPS_IN_ONE_JUMP", 5);
	        Stats::SetInt("MPX_MOST_SPINS_IN_ONE_JUMP", 5);
	        Stats::SetInt("MPX_CHAR_FM_VEHICLE_1_UNLCK", -1);
	        Stats::SetInt("MPX_CHAR_FM_VEHICLE_2_UNLCK", -1);
	        Stats::SetInt("MPX_NO_CARS_REPAIR", 1000);
	        Stats::SetInt("MPX_VEHICLES_SPRAYED", 500);
	        Stats::SetInt("MPX_NUMBER_NEAR_MISS_NOCRASH", 500);
	        Stats::SetInt("MPX_USJS_FOUND", 50);
	        Stats::SetInt("MPX_USJS_COMPLETED", 50);
	        Stats::SetInt("MPX_USJS_TOTAL_COMPLETED", 50);
	        Stats::SetInt("MPX_CRDEADLINE", 5);
	        Stats::SetInt("MPX_FAVOUTFITBIKETIMECURRENT", 2069146067);
	        Stats::SetInt("MPX_FAVOUTFITBIKETIME1ALLTIME", 2069146067);
	        Stats::SetInt("MPX_FAVOUTFITBIKETYPECURRENT", 2069146067);
	        Stats::SetInt("MPX_FAVOUTFITBIKETYPEALLTIME", 2069146067);
	        Stats::SetInt("MPX_LONGEST_WHEELIE_DIST", 1000);
	        Stats::SetInt("MPX_RACES_WON", 50);
	        Stats::SetInt("MPX_COUNT_HOTRING_RACE", 20);
	        Stats::SetBool("MPX_AWD_FMFURTHESTWHEELIE", true);
	        Stats::SetBool("MPX_AWD_FMFULLYMODDEDCAR", true);
	}

	static void AwardsCombat()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_AWD_100_HEADSHOTS", 500);
	        Stats::SetInt("MPX_AWD_FMOVERALLKILLS", 1000);
	        Stats::SetInt("MPX_AWD_FMKILLBOUNTY", 25);
	        Stats::SetInt("MPX_AWD_FM_DM_3KILLSAMEGUY", 50);
	        Stats::SetInt("MPX_AWD_FM_DM_KILLSTREAK", 100);
	        Stats::SetInt("MPX_AWD_FM_DM_STOLENKILL", 50);
	        Stats::SetInt("MPX_AWD_FM_DM_TOTALKILLS", 500);
	        Stats::SetBool("MPX_AWD_FMKILLSTREAKSDM", true);
	        Stats::SetBool("MPX_AWD_FMMOSTKILLSGANGHIDE", true);
	        Stats::SetBool("MPX_AWD_FMMOSTKILLSSURVIVE", true);
	        Stats::SetInt("MPX_AWD_FMREVENGEKILLSDM", 50);
	        Stats::SetInt("MPX_AWD_KILL_CARRIER_CAPTURE", 100);
	        Stats::SetInt("MPX_AWD_NIGHTVISION_KILLS", 100);
	        Stats::SetInt("MPX_AWD_KILL_PSYCHOPATHS", 100);
	        Stats::SetInt("MPX_AWD_TAKEDOWNSMUGPLANE", 50);
	        Stats::SetInt("MPX_AWD_100_KILLS_PISTOL", 500);
	        Stats::SetInt("MPX_AWD_100_KILLS_SMG", 500);
	        Stats::SetInt("MPX_AWD_100_KILLS_SHOTGUN", 500);
	        Stats::SetInt("MPX_ASLTRIFLE_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_AWD_100_KILLS_SNIPER", 500);
	        Stats::SetInt("MPX_MG_ENEMY_KILLS", 500);
	        Stats::SetInt("MPX_AWD_25_KILLS_STICKYBOMBS", 50);
	        Stats::SetInt("MPX_AWD_50_KILLS_GRENADES", 50);
	        Stats::SetInt("MPX_AWD_50_KILLS_ROCKETLAUNCH", 50);
	        Stats::SetInt("MPX_AWD_20_KILLS_MELEE", 50);
	        Stats::SetInt("MPX_AWD_CAR_BOMBS_ENEMY_KILLS", 25);
	        Stats::SetInt("MPX_MELEEKILLS", 700);
	        Stats::SetInt("MPX_HITS", 10000);
	        Stats::SetInt("MPX_DEATHS", 499);
	        Stats::SetInt("MPX_HIGHEST_SKITTLES", 900);
	        Stats::SetInt("MPX_NUMBER_NEAR_MISS", 1000);
	}

	static void AwardsUnlockAllApartmentHeistsAwards()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_AWD_FINISH_HEISTS", 50);
	        Stats::SetInt("MPX_AWD_FINISH_HEIST_SETUP_JOB", 50);
	        Stats::SetInt("MPX_AWD_COMPLETE_HEIST_NOT_DIE", -1);
	        Stats::SetBool("MPX_AWD_FINISH_HEIST_NO_DAMAGE", true);
	        Stats::SetInt("MPX_AWD_WIN_GOLD_MEDAL_HEISTS", 25);
	        Stats::SetInt("MPX_AWD_DO_HEIST_AS_MEMBER", 25);
	        Stats::SetInt("MPX_AWD_DO_HEIST_AS_THE_LEADER", 25);
	        Stats::SetBool("MPX_AWD_SPLIT_HEIST_TAKE_EVENLY", true);
	        Stats::SetBool("MPX_AWD_ACTIVATE_2_PERSON_KEY", true);
	        Stats::SetInt("MPX_AWD_CONTROL_CROWDS", 25);
	        Stats::SetBool("MPX_AWD_ALL_ROLES_HEIST", true);
	        Stats::SetInt("MPX_HEIST_COMPLETION", 25);
	        Stats::SetInt("MPX_HEISTS_ORGANISED", -1);
	        Stats::SetInt("MPX_HEIST_START", -1);
	        Stats::SetInt("MPX_HEIST_END", -1);
	        Stats::SetInt("MPX_CUTSCENE_MID_PRISON", -1);
	        Stats::SetInt("MPX_CUTSCENE_MID_HUMANE", -1);
	        Stats::SetInt("MPX_CUTSCENE_MID_NARC", -1);
	        Stats::SetInt("MPX_CUTSCENE_MID_ORNATE", -1);
	        Stats::SetInt("MPX_CR_FLEECA_PREP_1", -1);
	        Stats::SetInt("MPX_CR_FLEECA_PREP_2", -1);
	        Stats::SetInt("MPX_CR_FLEECA_FINALE", -1);
	        Stats::SetInt("MPX_CR_PRISON_PLANE", -1);
	        Stats::SetInt("MPX_CR_PRISON_BUS", -1);
	        Stats::SetInt("MPX_CR_PRISON_STATION", -1);
	        Stats::SetInt("MPX_CR_PRISON_UNFINISHED_BIZ", -1);
	        Stats::SetInt("MPX_CR_PRISON_FINALE", -1);
	        Stats::SetInt("MPX_CR_HUMANE_KEY_CODES", -1);
	        Stats::SetInt("MPX_CR_HUMANE_ARMORDILLOS", -1);
	        Stats::SetInt("MPX_CR_HUMANE_EMP", -1);
	        Stats::SetInt("MPX_CR_HUMANE_VALKYRIE", -1);
	        Stats::SetInt("MPX_CR_HUMANE_FINALE", -1);
	        Stats::SetInt("MPX_CR_NARC_COKE", -1);
	        Stats::SetInt("MPX_CR_NARC_TRASH_TRUCK", -1);
	        Stats::SetInt("MPX_CR_NARC_BIKERS", -1);
	        Stats::SetInt("MPX_CR_NARC_WEED", -1);
	        Stats::SetInt("MPX_CR_NARC_STEAL_METH", -1);
	        Stats::SetInt("MPX_CR_NARC_FINALE", -1);
	        Stats::SetInt("MPX_CR_PACIFIC_TRUCKS", -1);
	        Stats::SetInt("MPX_CR_PACIFIC_WITSEC", -1);
	        Stats::SetInt("MPX_CR_PACIFIC_HACK", -1);
	        Stats::SetInt("MPX_CR_PACIFIC_BIKES", -1);
	        Stats::SetInt("MPX_CR_PACIFIC_CONVOY", -1);
	        Stats::SetInt("MPX_CR_PACIFIC_FINALE", -1);
	        Stats::SetInt("MPPLY_HEIST_ACH_TRACKER", -1);
	        Stats::SetInt("MPPLY_WIN_GOLD_MEDAL_HEISTS", 25);
	        Stats::SetBool("MPPLY_AWD_FLEECA_FIN", true);
	        Stats::SetBool("MPPLY_AWD_PRISON_FIN", true);
	        Stats::SetBool("MPPLY_AWD_HUMANE_FIN", true);
	        Stats::SetBool("MPPLY_AWD_SERIESA_FIN", true);
	        Stats::SetBool("MPPLY_AWD_PACIFIC_FIN", true);
	        Stats::SetBool("MPPLY_AWD_HST_ORDER", true);
	        Stats::SetBool("MPPLY_AWD_COMPLET_HEIST_MEM", true);
	        Stats::SetBool("MPPLY_AWD_COMPLET_HEIST_1STPER", true);
	        Stats::SetBool("MPPLY_AWD_HST_SAME_TEAM", true);
	        Stats::SetBool("MPPLY_AWD_HST_ULT_CHAL", true);
	        Stats::SetBool("MPX_AWD_MATCHING_OUTFIT_HEIST", true);
	        Stats::SetBool("MPX_HEIST_PLANNING_DONE_PRINT", true);
	        Stats::SetBool("MPX_HEIST_PLANNING_DONE_HELP_0", true);
	        Stats::SetBool("MPX_HEIST_PLANNING_DONE_HELP_1", true);
	        Stats::SetBool("MPX_HEIST_PRE_PLAN_DONE_HELP_0", true);
	        Stats::SetBool("MPX_HEIST_CUTS_DONE_FINALE", true);
	        Stats::SetBool("MPX_HEIST_IS_TUTORIAL", true);
	        Stats::SetBool("MPX_HEIST_STRAND_INTRO_DONE", true);
	        Stats::SetBool("MPX_HEIST_CUTS_DONE_ORNATE", true);
	        Stats::SetBool("MPX_HEIST_CUTS_DONE_PRISON", true);
	        Stats::SetBool("MPX_HEIST_CUTS_DONE_BIOLAB", true);
	        Stats::SetBool("MPX_HEIST_CUTS_DONE_NARCOTIC", true);
	        Stats::SetBool("MPX_HEIST_CUTS_DONE_TUTORIAL", true);
	        Stats::SetBool("MPX_HEIST_AWARD_DONE_PREP", true);
	        Stats::SetBool("MPX_HEIST_AWARD_BOUGHT_IN", true);
	        Stats::SetInt("MPX_HEIST_PLANNING_STAGE", -1);
	}

	static void AwardsUnlockAllDiamondCasinoHeistAwards()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_CAS_HEIST_NOTS", -1);
	        Stats::SetInt("MPX_CAS_HEIST_FLOW", -1);
	        Stats::SetInt("MPX_SIGNAL_JAMMERS_COLLECTED", 50);
	        Stats::SetInt("MPX_AWD_PREPARATION", 40);
	        Stats::SetInt("MPX_AWD_ASLEEPONJOB", 20);
	        Stats::SetInt("MPX_AWD_DAICASHCRAB", 100000);
	        Stats::SetInt("MPX_AWD_BIGBRO", 40);
	        Stats::SetInt("MPX_AWD_SHARPSHOOTER", 40);
	        Stats::SetInt("MPX_AWD_RACECHAMP", 40);
	        Stats::SetInt("MPX_AWD_BATSWORD", 1000000);
	        Stats::SetInt("MPX_AWD_COINPURSE", 950000);
	        Stats::SetInt("MPX_AWD_ASTROCHIMP", 3000000);
	        Stats::SetInt("MPX_AWD_MASTERFUL", 40000);
	        Stats::SetInt("MPX_H3_BOARD_DIALOGUE0", -1);
	        Stats::SetInt("MPX_H3_BOARD_DIALOGUE1", -1);
	        Stats::SetInt("MPX_H3_BOARD_DIALOGUE2", -1);
	        Stats::SetInt("MPX_H3_VEHICLESUSED", -1);
	        Stats::SetInt("MPX_H3_CR_STEALTH_1A", 100);
	        Stats::SetInt("MPX_H3_CR_STEALTH_2B_RAPP", 100);
	        Stats::SetInt("MPX_H3_CR_STEALTH_2C_SIDE", 100);
	        Stats::SetInt("MPX_H3_CR_STEALTH_3A", 100);
	        Stats::SetInt("MPX_H3_CR_STEALTH_4A", 100);
	        Stats::SetInt("MPX_H3_CR_STEALTH_5A", 100);
	        Stats::SetInt("MPX_H3_CR_SUBTERFUGE_1A", 100);
	        Stats::SetInt("MPX_H3_CR_SUBTERFUGE_2A", 100);
	        Stats::SetInt("MPX_H3_CR_SUBTERFUGE_2B", 100);
	        Stats::SetInt("MPX_H3_CR_SUBTERFUGE_3A", 100);
	        Stats::SetInt("MPX_H3_CR_SUBTERFUGE_3B", 100);
	        Stats::SetInt("MPX_H3_CR_SUBTERFUGE_4A", 100);
	        Stats::SetInt("MPX_H3_CR_SUBTERFUGE_5A", 100);
	        Stats::SetInt("MPX_H3_CR_DIRECT_1A", 100);
	        Stats::SetInt("MPX_H3_CR_DIRECT_2A1", 100);
	        Stats::SetInt("MPX_H3_CR_DIRECT_2A2", 100);
	        Stats::SetInt("MPX_H3_CR_DIRECT_2BP", 100);
	        Stats::SetInt("MPX_H3_CR_DIRECT_2C", 100);
	        Stats::SetInt("MPX_H3_CR_DIRECT_3A", 100);
	        Stats::SetInt("MPX_H3_CR_DIRECT_4A", 100);
	        Stats::SetInt("MPX_H3_CR_DIRECT_5A", 100);
	        Stats::SetInt("MPX_CR_ORDER", 100);
	        Stats::SetBool("MPX_AWD_SCOPEOUT", true);
	        Stats::SetBool("MPX_AWD_CREWEDUP", true);
	        Stats::SetBool("MPX_AWD_MOVINGON", true);
	        Stats::SetBool("MPX_AWD_PROMOCAMP", true);
	        Stats::SetBool("MPX_AWD_GUNMAN", true);
	        Stats::SetBool("MPX_AWD_SMASHNGRAB", true);
	        Stats::SetBool("MPX_AWD_INPLAINSI", true);
	        Stats::SetBool("MPX_AWD_UNDETECTED", true);
	        Stats::SetBool("MPX_AWD_ALLROUND", true);
	        Stats::SetBool("MPX_AWD_ELITETHEIF", true);
	        Stats::SetBool("MPX_AWD_PRO", true);
	        Stats::SetBool("MPX_AWD_SUPPORTACT", true);
	        Stats::SetBool("MPX_AWD_SHAFTED", true);
	        Stats::SetBool("MPX_AWD_COLLECTOR", true);
	        Stats::SetBool("MPX_AWD_DEADEYE", true);
	        Stats::SetBool("MPX_AWD_PISTOLSATDAWN", true);
	        Stats::SetBool("MPX_AWD_TRAFFICAVOI", true);
	        Stats::SetBool("MPX_AWD_CANTCATCHBRA", true);
	        Stats::SetBool("MPX_AWD_WIZHARD", true);
	        Stats::SetBool("MPX_AWD_APEESCAPE", true);
	        Stats::SetBool("MPX_AWD_MONKEYKIND", true);
	        Stats::SetBool("MPX_AWD_AQUAAPE", true);
	        Stats::SetBool("MPX_AWD_KEEPFAITH", true);
	        Stats::SetBool("MPX_AWD_TRUELOVE", true);
	        Stats::SetBool("MPX_AWD_NEMESIS", true);
	        Stats::SetBool("MPX_AWD_FRIENDZONED", true);
	        Stats::SetBool("MPX_VCM_FLOW_CS_RSC_SEEN", true);
	        Stats::SetBool("MPX_VCM_FLOW_CS_BWL_SEEN", true);
	        Stats::SetBool("MPX_VCM_FLOW_CS_MTG_SEEN", true);
	        Stats::SetBool("MPX_VCM_FLOW_CS_OIL_SEEN", true);
	        Stats::SetBool("MPX_VCM_FLOW_CS_DEF_SEEN", true);
	        Stats::SetBool("MPX_VCM_FLOW_CS_FIN_SEEN", true);
	        Stats::SetBool("MPX_HELP_FURIA", true);
	        Stats::SetBool("MPX_HELP_MINITAN", true);
	        Stats::SetBool("MPX_HELP_YOSEMITE2", true);
	        Stats::SetBool("MPX_HELP_ZHABA", true);
	        Stats::SetBool("MPX_HELP_IMORGEN", true);
	        Stats::SetBool("MPX_HELP_SULTAN2", true);
	        Stats::SetBool("MPX_HELP_VAGRANT", true);
	        Stats::SetBool("MPX_HELP_VSTR", true);
	        Stats::SetBool("MPX_HELP_STRYDER", true);
	        Stats::SetBool("MPX_HELP_SUGOI", true);
	        Stats::SetBool("MPX_HELP_KANJO", true);
	        Stats::SetBool("MPX_HELP_FORMULA", true);
	        Stats::SetBool("MPX_HELP_FORMULA2", true);
	        Stats::SetBool("MPX_HELP_JB7002", true);
	        for (int i = 0; i <= 4; i++) {
	            for (int j = 0; j <= 63; j++) {
	                Stats::SetMaskedBool("MPX_CASINOHSTPSTAT_BOOL" + std::to_string(i), j, true);
	            }
	        }
	}

	static void AwardsUnlockAllCayoHeistAwards()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetBool("MPX_AWD_INTELGATHER", true);
	        Stats::SetBool("MPX_AWD_COMPOUNDINFILT", true);
	        Stats::SetBool("MPX_AWD_LOOT_FINDER", true);
	        Stats::SetBool("MPX_AWD_MAX_DISRUPT", true);
	        Stats::SetBool("MPX_AWD_THE_ISLAND_HEIST", true);
	        Stats::SetBool("MPX_AWD_GOING_ALONE", true);
	        Stats::SetBool("MPX_AWD_TEAM_WORK", true);
	        Stats::SetBool("MPX_AWD_MIXING_UP", true);
	        Stats::SetBool("MPX_AWD_TEAM_WORK", true);
	        Stats::SetBool("MPX_AWD_MIXING_UP", true);
	        Stats::SetBool("MPX_AWD_PRO_THIEF", true);
	        Stats::SetBool("MPX_AWD_CAT_BURGLAR", true);
	        Stats::SetBool("MPX_AWD_ONE_OF_THEM", true);
	        Stats::SetBool("MPX_AWD_GOLDEN_GUN", true);
	        Stats::SetBool("MPX_AWD_ELITE_THIEF", true);
	        Stats::SetBool("MPX_AWD_PROFESSIONAL", true);
	        Stats::SetBool("MPX_AWD_HELPING_OUT", true);
	        Stats::SetBool("MPX_AWD_COURIER", true);
	        Stats::SetBool("MPX_AWD_PARTY_VIBES", true);
	        Stats::SetBool("MPX_AWD_HELPING_HAND", true);
	        Stats::SetBool("MPX_AWD_ELEVENELEVEN", true);
	        Stats::SetBool("MPX_COMPLETE_H4_F_USING_VETIR", true);
	        Stats::SetBool("MPX_COMPLETE_H4_F_USING_LONGFIN", true);
	        Stats::SetBool("MPX_COMPLETE_H4_F_USING_ANNIH", true);
	        Stats::SetBool("MPX_COMPLETE_H4_F_USING_ALKONOS", true);
	        Stats::SetBool("MPX_COMPLETE_H4_F_USING_PATROLB", true);
	        Stats::SetInt("MPX_AWD_LOSTANDFOUND", 500000);
	        Stats::SetInt("MPX_AWD_SUNSET", 1800000);
	        Stats::SetInt("MPX_AWD_TREASURE_HUNTER", 1000000);
	        Stats::SetInt("MPX_AWD_WRECK_DIVING", 1000000);
	        Stats::SetInt("MPX_AWD_KEINEMUSIK", 1800000);
	        Stats::SetInt("MPX_AWD_PALMS_TRAX", 1800000);
	        Stats::SetInt("MPX_AWD_MOODYMANN", 1800000);
	        Stats::SetInt("MPX_AWD_FILL_YOUR_BAGS", 1000000000);
	        Stats::SetInt("MPX_AWD_WELL_PREPARED", 80);
	        Stats::SetInt("MPX_H4_H4_DJ_MISSIONS", -1);
	        Stats::SetInt("MPX_H4CNF_APPROACH", -1);
	        Stats::SetInt("MPX_H4_MISSIONS", -1);
	        Stats::SetInt("MPX_H4_PLAYTHROUGH_STATUS", 100);
	        for (int i = 0; i <= 2; i++) {
	            for (int j = 0; j <= 63; j++) {
	                Stats::SetMaskedBool("MPX_HISLANDPSTAT_BOOL" + std::to_string(i), j, true);
	            }
	        }
	}

	static void AwardsUnlockAllDoomsdayHeistAwards()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_GANGOPS_HEIST_STATUS", -1);
	        Stats::SetInt("MPX_GANGOPS_HEIST_STATUS", -229384);
	        Stats::SetInt("MPX_GANGOPS_FM_MISSION_PROG", -1);
	        Stats::SetInt("MPX_GANGOPS_FLOW_MISSION_PROG", -1);
	        Stats::SetInt("MPPLY_GANGOPS_ALLINORDER", 100);
	        Stats::SetInt("MPPLY_GANGOPS_LOYALTY", 100);
	        Stats::SetInt("MPPLY_GANGOPS_CRIMMASMD", 100);
	        Stats::SetInt("MPPLY_GANGOPS_LOYALTY2", 100);
	        Stats::SetInt("MPPLY_GANGOPS_LOYALTY3", 100);
	        Stats::SetInt("MPPLY_GANGOPS_CRIMMASMD2", 100);
	        Stats::SetInt("MPPLY_GANGOPS_CRIMMASMD3", 100);
	        Stats::SetInt("MPPLY_GANGOPS_SUPPORT", 100);
	        Stats::SetInt("MPX_CR_GANGOP_MORGUE", 10);
	        Stats::SetInt("MPX_CR_GANGOP_DELUXO", 10);
	        Stats::SetInt("MPX_CR_GANGOP_SERVERFARM", 10);
	        Stats::SetInt("MPX_CR_GANGOP_IAABASE_FIN", 10);
	        Stats::SetInt("MPX_CR_GANGOP_STEALOSPREY", 10);
	        Stats::SetInt("MPX_CR_GANGOP_FOUNDRY", 10);
	        Stats::SetInt("MPX_CR_GANGOP_RIOTVAN", 10);
	        Stats::SetInt("MPX_CR_GANGOP_SUBMARINECAR", 10);
	        Stats::SetInt("MPX_CR_GANGOP_SUBMARINE_FIN", 10);
	        Stats::SetInt("MPX_CR_GANGOP_PREDATOR", 10);
	        Stats::SetInt("MPX_CR_GANGOP_BMLAUNCHER", 10);
	        Stats::SetInt("MPX_CR_GANGOP_BCCUSTOM", 10);
	        Stats::SetInt("MPX_CR_GANGOP_STEALTHTANKS", 10);
	        Stats::SetInt("MPX_CR_GANGOP_SPYPLANE", 10);
	        Stats::SetInt("MPX_CR_GANGOP_FINALE", 10);
	        Stats::SetInt("MPX_CR_GANGOP_FINALE_P2", 10);
	        Stats::SetInt("MPX_CR_GANGOP_FINALE_P3", 10);
	        Stats::SetBool("MPPLY_AWD_GANGOPS_IAA", true);
	        Stats::SetBool("MPPLY_AWD_GANGOPS_SUBMARINE", true);
	        Stats::SetBool("MPPLY_AWD_GANGOPS_MISSILE", true);
	        Stats::SetBool("MPPLY_AWD_GANGOPS_ALLINORDER", true);
	        Stats::SetBool("MPPLY_AWD_GANGOPS_LOYALTY", true);
	        Stats::SetBool("MPPLY_AWD_GANGOPS_LOYALTY2", true);
	        Stats::SetBool("MPPLY_AWD_GANGOPS_LOYALTY3", true);
	        Stats::SetBool("MPPLY_AWD_GANGOPS_CRIMMASMD", true);
	        Stats::SetBool("MPPLY_AWD_GANGOPS_CRIMMASMD2", true);
	        Stats::SetBool("MPPLY_AWD_GANGOPS_CRIMMASMD3", true);
	        Stats::SetBool("MPPLY_AWD_GANGOPS_SUPPORT", true);
	        for (int j = 0; j <= 63; j++) {
	            Stats::SetMaskedBool("MPX_GANGOPSPSTAT_BOOL0", j, true);
	        }
	        Stats::SetMaskedInt("MPX_DLCSMUGCHARPSTAT_INT260", 16, 8, 3);
	        Stats::SetMaskedInt("MPX_BUSINESSBATPSTAT_INT260", 24, 8, 3);
	        Stats::SetMaskedInt("MPX_BUSINESSBATPSTAT_INT260", 32, 8, 3);
	        Stats::SetMaskedInt("MPX_BUSINESSBATPSTAT_INT260", 40, 8, 3);
	        Stats::SetMaskedInt("MPX_BUSINESSBATPSTAT_INT260", 48, 8, 3);
	}

	static void AwardsTheKortzCenterHeist()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetBool("MPX_AWD_SCOPING", true);
	        Stats::SetInt("MPX_AWD_PREPPER", 20);
	        Stats::SetBool("MPX_AWD_ADAPTABLE", true);
	        Stats::SetBool("MPX_AWD_KORTZCENTERHEIST", true);
	        Stats::SetBool("MPX_AWD_FINDSAWAY", true);
	        Stats::SetBool("MPX_AWD_WHOSTHERE", true);
	        Stats::SetBool("MPX_AWD_ELITETHIEF", true);
	        Stats::SetBool("MPX_AWD_NOLIFER", true);
	        Stats::SetBool("MPX_AWD_SOLITUDE", true);
	        Stats::SetBool("MPX_AWD_COORDINATION", true);
	        Stats::SetBool("MPX_AWD_FLEXIBLETHIEF", true);
	        Stats::SetInt("MPX_AWD_REPEATOFFENDER", 20);
	        Stats::SetInt("MPX_AWD_FULLBAGS", 5000000);
	        Stats::SetBool("MPX_AWD_HIDDENINPLAINSIGHT", true);
	        Stats::SetInt("MPX_AWD_CURATOR", 5);
	        Stats::SetInt("MPX_AWD_LAPIDARY", 5);
	        Stats::SetBool("MPX_AWD_PACIFIST", true);
	        Stats::SetBool("MPX_AWD_PUTRIDPILFERING", true);
	        Stats::SetBool("MPX_AWD_METEORITICS", true);
	}

	static void AwardsASafehouseInTheHills()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetBool("MPX_AWD_NEGATIVEPRESS", true);
	        Stats::SetBool("MPX_AWD_USESELFDRIVINGVEH", true);
	        Stats::SetBool("MPX_AWD_LIONSDEN", true);
	        Stats::SetBool("MPX_AWD_TAKEOUTLEADEXPLO", true);
	        Stats::SetBool("MPX_AWD_SUBWAYTRAIN", true);
	        Stats::SetBool("MPX_AWD_SUBWAYSTUNTJUMP", true);
	        Stats::SetBool("MPX_AWD_TRASHCOLLECTORS", true);
	        Stats::SetBool("MPX_AWD_ALLTRASHCOLLECTED", true);
	        Stats::SetBool("MPX_AWD_FIBFINALE", true);
	        Stats::SetBool("MPX_AWD_HELPER", true);
	        Stats::SetBool("MPX_AWD_FIBFINALECHALLENGE", true);
	        Stats::SetBool("MPX_AWD_MANSIONDEFEND", true);
	        Stats::SetBool("MPX_AWD_DEFLOWMOTIONKILLS", true);
	        Stats::SetBool("MPX_AWD_YOUVEMADEIT", true);
	        Stats::SetBool("MPX_AWD_ANIMALLOVER", true);
	        Stats::SetBool("MPX_AWD_MANSADVERSARYWIN", true);
	        Stats::SetBool("MPX_AWD_ONTHECLOCK", true);
	        Stats::SetInt("MPX_AWD_TAXIDESTRUCTION", 20);
	        Stats::SetInt("MPX_AWD_YOGA", 50);
	        Stats::SetInt("MPX_AWD_JUICEDUP", 100);
	        Stats::SetInt("MPX_AWD_MANADVERSARYDEFUSE", 10);
	        Stats::SetInt("MPX_AWD_FIREFIGHTER", 20);
	        Stats::SetInt("MPX_AWD_ALPHAMAIL", 20);
	        Stats::SetInt("MPX_AWD_LOSSANTOSMETEOR", 20);
	}

	static void AwardsAgentsOfSabotage()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        for (int i = 9542; i <= 9546; i++) {
	            Stats::SetPackedBool(i, true);
	        }
	        Stats::SetPackedBool(9549, true);
	        Stats::SetPackedInt(24903, 25);
	        Stats::SetPackedInt(24904, 2);
	        Stats::SetInt("MPX_HACKER24_GEN_BS", 8160);
	        Stats::SetBool("MPX_AWD_FINEART", true);
	        Stats::SetBool("MPX_AWD_BRUTEFORCE", true);
	        Stats::SetBool("MPX_AWD_PROJECTBREAK", true);
	        Stats::SetBool("MPX_AWD_BLACKBOXFILE", true);
	        Stats::SetBool("MPX_AWD_BONUSPOINTS", true);
	        Stats::SetInt("MPX_AWD_DARNELLBROSINC", 50);
	        Stats::SetInt("MPX_AWD_GET_READY", 50);
	}

	static void AwardsAfterHours()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_AWD_DANCE_TO_SOLOMUN", 120);
	        Stats::SetInt("MPX_AWD_DANCE_TO_TALEOFUS", 120);
	        Stats::SetInt("MPX_AWD_DANCE_TO_DIXON", 120);
	        Stats::SetInt("MPX_AWD_DANCE_TO_BLKMAD", 120);
	        Stats::SetInt("MPX_AWD_CLUB_DRUNK", 200);
	        Stats::SetInt("MPX_NIGHTCLUB_VIP_APPEAR", 700);
	        Stats::SetInt("MPX_NIGHTCLUB_JOBS_DONE", 700);
	        Stats::SetInt("MPX_NIGHTCLUB_EARNINGS", 5721002);
	        Stats::SetInt("MPX_HUB_SALES_COMPLETED", 1001);
	        Stats::SetInt("MPX_HUB_EARNINGS", 20721002);
	        Stats::SetInt("MPX_DANCE_COMBO_DURATION_MINS", 3600000);
	        Stats::SetInt("MPX_NIGHTCLUB_PLAYER_APPEAR", 100);
	        Stats::SetInt("MPX_LIFETIME_HUB_GOODS_SOLD", 784672);
	        Stats::SetInt("MPX_LIFETIME_HUB_GOODS_MADE", 507822);
	        Stats::SetInt("MPX_DANCEPERFECTOWNCLUB", 120);
	        Stats::SetInt("MPX_NUMUNIQUEPLYSINCLUB", 120);
	        Stats::SetInt("MPX_DANCETODIFFDJS", 4);
	        Stats::SetInt("MPX_NIGHTCLUB_HOTSPOT_TIME_MS", 3600000);
	        Stats::SetInt("MPX_NIGHTCLUB_CONT_TOTAL", 20);
	        Stats::SetInt("MPX_NIGHTCLUB_CONT_MISSION", -1);
	        Stats::SetInt("MPX_CLUB_CONTRABAND_MISSION", 1000);
	        Stats::SetInt("MPX_HUB_CONTRABAND_MISSION", 1000);
	        Stats::SetBool("MPX_AWD_CLUB_HOTSPOT", true);
	        Stats::SetBool("MPX_AWD_CLUB_CLUBBER", true);
	        Stats::SetBool("MPX_AWD_CLUB_COORD", true);
	        for (int j = 0; j <= 63; j++) {
	            Stats::SetMaskedBool("MPX_BUSINESSBATPSTAT_BOOL0", j, true);
	            Stats::SetMaskedBool("MPX_BUSINESSBATPSTAT_BOOL1", j, true);
	        }
	        if (Stats::GetMaskedInt("MPX_BUSINESSBATPSTAT_INT380", 0, 8) < 20) {
	            Stats::SetMaskedInt("MPX_BUSINESSBATPSTAT_INT380", 0, 8, 20);
	        }
	        Stats::SetMaskedInt("MPX_BUSINESSBATPSTAT_INT379", 8, 8, 50);
	        Stats::SetMaskedInt("MPX_BUSINESSBATPSTAT_INT379", 16, 8, 100);
	        Stats::SetMaskedInt("MPX_BUSINESSBATPSTAT_INT379", 24, 8, 20);
	        Stats::SetMaskedInt("MPX_BUSINESSBATPSTAT_INT379", 32, 8, 80);
	        Stats::SetMaskedInt("MPX_BUSINESSBATPSTAT_INT379", 40, 8, 60);
	        Stats::SetMaskedInt("MPX_BUSINESSBATPSTAT_INT379", 48, 8, 40);
	        Stats::SetMaskedInt("MPX_BUSINESSBATPSTAT_INT379", 56, 8, 10);
	}

	static void AwardsArenaWar()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_ARN_BS_TRINKET_TICKERS", -1);
	        Stats::SetInt("MPX_ARN_BS_TRINKET_SAVED", -1);
	        Stats::SetInt("MPX_AWD_WATCH_YOUR_STEP", 50);
	        Stats::SetInt("MPX_AWD_TOWER_OFFENSE", 50);
	        Stats::SetInt("MPX_AWD_READY_FOR_WAR", 50);
	        Stats::SetInt("MPX_AWD_THROUGH_A_LENS", 50);
	        Stats::SetInt("MPX_AWD_SPINNER", 50);
	        Stats::SetInt("MPX_AWD_YOUMEANBOOBYTRAPS", 50);
	        Stats::SetInt("MPX_AWD_MASTER_BANDITO", 50);
	        Stats::SetInt("MPX_AWD_SITTING_DUCK", 50);
	        Stats::SetInt("MPX_AWD_CROWDPARTICIPATION", 50);
	        Stats::SetInt("MPX_AWD_KILL_OR_BE_KILLED", 50);
	        Stats::SetInt("MPX_AWD_MASSIVE_SHUNT", 50);
	        Stats::SetInt("MPX_AWD_YOURE_OUTTA_HERE", 200);
	        Stats::SetInt("MPX_AWD_WEVE_GOT_ONE", 50);
	        Stats::SetInt("MPX_AWD_ARENA_WAGEWORKER", 1000000);
	        Stats::SetInt("MPX_AWD_TIME_SERVED", 1000);
	        Stats::SetInt("MPX_AWD_TOP_SCORE", 55000);
	        Stats::SetInt("MPX_AWD_CAREER_WINNER", 1000);
	        Stats::SetInt("MPX_ARENAWARS_SP", 0);
	        Stats::SetInt("MPX_ARENAWARS_SKILL_LEVEL", 20);
	        Stats::SetInt("MPX_ARENAWARS_SP_LIFETIME", 100);
	        Stats::SetInt("MPX_ARENAWARS_AP", 0);
	        Stats::SetInt("MPX_ARENAWARS_AP_TIER", 1000);
	        Stats::SetInt("MPX_ARENAWARS_AP_LIFETIME", 5055000);
	        Stats::SetInt("MPX_ARENAWARS_CARRER_UNLK", -1);
	        Stats::SetInt("MPX_ARN_W_THEME_SCIFI", 1000);
	        Stats::SetInt("MPX_ARN_W_THEME_APOC", 1000);
	        Stats::SetInt("MPX_ARN_W_THEME_CONS", 1000);
	        Stats::SetInt("MPX_ARN_W_PASS_THE_BOMB", 1000);
	        Stats::SetInt("MPX_ARN_W_DETONATION", 1000);
	        Stats::SetInt("MPX_ARN_W_ARCADE_RACE", 1000);
	        Stats::SetInt("MPX_ARN_W_CTF", 1000);
	        Stats::SetInt("MPX_ARN_W_TAG_TEAM", 1000);
	        Stats::SetInt("MPX_ARN_W_DESTR_DERBY", 1000);
	        Stats::SetInt("MPX_ARN_W_CARNAGE", 1000);
	        Stats::SetInt("MPX_ARN_W_MONSTER_JAM", 1000);
	        Stats::SetInt("MPX_ARN_W_GAMES_MASTERS", 1000);
	        Stats::SetInt("MPX_ARN_L_PASS_THE_BOMB", 500);
	        Stats::SetInt("MPX_ARN_L_DETONATION", 500);
	        Stats::SetInt("MPX_ARN_L_ARCADE_RACE", 500);
	        Stats::SetInt("MPX_ARN_L_CTF", 500);
	        Stats::SetInt("MPX_ARN_L_TAG_TEAM", 500);
	        Stats::SetInt("MPX_ARN_L_DESTR_DERBY", 500);
	        Stats::SetInt("MPX_ARN_L_CARNAGE", 500);
	        Stats::SetInt("MPX_ARN_L_MONSTER_JAM", 500);
	        Stats::SetInt("MPX_ARN_L_GAMES_MASTERS", 500);
	        Stats::SetInt("MPX_NUMBER_OF_CHAMP_BOUGHT", 1000);
	        Stats::SetInt("MPX_ARN_SPECTATOR_KILLS", 1000);
	        Stats::SetInt("MPX_ARN_LIFETIME_KILLS", 1000);
	        Stats::SetInt("MPX_ARN_LIFETIME_DEATHS", 500);
	        Stats::SetInt("MPX_ARENAWARS_CARRER_WINS", 1000);
	        Stats::SetInt("MPX_ARENAWARS_CARRER_WINT", 1000);
	        Stats::SetInt("MPX_ARENAWARS_MATCHES_PLYD", 1000);
	        Stats::SetInt("MPX_ARENAWARS_MATCHES_PLYDT", 1000);
	        Stats::SetInt("MPX_ARN_SPEC_BOX_TIME_MS", 86400000);
	        Stats::SetInt("MPX_ARN_SPECTATOR_DRONE", 1000);
	        Stats::SetInt("MPX_ARN_SPECTATOR_CAMS", 1000);
	        Stats::SetInt("MPX_ARN_SMOKE", 1000);
	        Stats::SetInt("MPX_ARN_DRINK", 1000);
	        Stats::SetInt("MPX_ARN_VEH_MONSTER", 1000);
	        Stats::SetInt("MPX_ARN_VEH_MONSTER", 1000);
	        Stats::SetInt("MPX_ARN_VEH_MONSTER", 1000);
	        Stats::SetInt("MPX_ARN_VEH_CERBERUS", 1000);
	        Stats::SetInt("MPX_ARN_VEH_CERBERUS2", 1000);
	        Stats::SetInt("MPX_ARN_VEH_CERBERUS3", 1000);
	        Stats::SetInt("MPX_ARN_VEH_BRUISER", 1000);
	        Stats::SetInt("MPX_ARN_VEH_BRUISER2", 1000);
	        Stats::SetInt("MPX_ARN_VEH_BRUISER3", 1000);
	        Stats::SetInt("MPX_ARN_VEH_SLAMVAN4", 1000);
	        Stats::SetInt("MPX_ARN_VEH_SLAMVAN5", 1000);
	        Stats::SetInt("MPX_ARN_VEH_SLAMVAN6", 1000);
	        Stats::SetInt("MPX_ARN_VEH_BRUTUS", 1000);
	        Stats::SetInt("MPX_ARN_VEH_BRUTUS2", 1000);
	        Stats::SetInt("MPX_ARN_VEH_BRUTUS3", 1000);
	        Stats::SetInt("MPX_ARN_VEH_SCARAB", 1000);
	        Stats::SetInt("MPX_ARN_VEH_SCARAB2", 1000);
	        Stats::SetInt("MPX_ARN_VEH_SCARAB3", 1000);
	        Stats::SetInt("MPX_ARN_VEH_DOMINATOR4", 1000);
	        Stats::SetInt("MPX_ARN_VEH_DOMINATOR5", 1000);
	        Stats::SetInt("MPX_ARN_VEH_DOMINATOR6", 1000);
	        Stats::SetInt("MPX_ARN_VEH_IMPALER2", 1000);
	        Stats::SetInt("MPX_ARN_VEH_IMPALER3", 1000);
	        Stats::SetInt("MPX_ARN_VEH_IMPALER4", 1000);
	        Stats::SetInt("MPX_ARN_VEH_ISSI4", 1000);
	        Stats::SetInt("MPX_ARN_VEH_ISSI5", 1000);
	        Stats::SetInt("MPX_ARN_VEH_ISSI", 61000);
	        Stats::SetInt("MPX_ARN_VEH_IMPERATOR", 1000);
	        Stats::SetInt("MPX_ARN_VEH_IMPERATOR2", 1000);
	        Stats::SetInt("MPX_ARN_VEH_IMPERATOR3", 1000);
	        Stats::SetInt("MPX_ARN_VEH_ZR380", 1000);
	        Stats::SetInt("MPX_ARN_VEH_ZR3802", 1000);
	        Stats::SetInt("MPX_ARN_VEH_ZR3803", 1000);
	        Stats::SetInt("MPX_ARN_VEH_DEATHBIKE", 1000);
	        Stats::SetInt("MPX_ARN_VEH_DEATHBIKE2", 1000);
	        Stats::SetInt("MPX_ARN_VEH_DEATHBIKE3", 1000);
	        Stats::SetBool("MPX_AWD_BEGINNER", true);
	        Stats::SetBool("MPX_AWD_FIELD_FILLER", true);
	        Stats::SetBool("MPX_AWD_ARMCHAIR_RACER", true);
	        Stats::SetBool("MPX_AWD_LEARNER", true);
	        Stats::SetBool("MPX_AWD_SUNDAY_DRIVER", true);
	        Stats::SetBool("MPX_AWD_THE_ROOKIE", true);
	        Stats::SetBool("MPX_AWD_BUMP_AND_RUN", true);
	        Stats::SetBool("MPX_AWD_GEAR_HEAD", true);
	        Stats::SetBool("MPX_AWD_DOOR_SLAMMER", true);
	        Stats::SetBool("MPX_AWD_HOT_LAP", true);
	        Stats::SetBool("MPX_AWD_ARENA_AMATEUR", true);
	        Stats::SetBool("MPX_AWD_PAINT_TRADER", true);
	        Stats::SetBool("MPX_AWD_SHUNTER", true);
	        Stats::SetBool("MPX_AWD_JOCK", true);
	        Stats::SetBool("MPX_AWD_WARRIOR", true);
	        Stats::SetBool("MPX_AWD_T_BONE", true);
	        Stats::SetBool("MPX_AWD_MAYHEM", true);
	        Stats::SetBool("MPX_AWD_WRECKER", true);
	        Stats::SetBool("MPX_AWD_CRASH_COURSE", true);
	        Stats::SetBool("MPX_AWD_ARENA_LEGEND", true);
	        Stats::SetBool("MPX_AWD_PEGASUS", true);
	        Stats::SetBool("MPX_AWD_UNSTOPPABLE", true);
	        Stats::SetBool("MPX_AWD_CONTACT_SPORT", true);
	        Stats::SetMaskedInt("MPX_ARENAWARSPSTAT_INT", 35, 8, 1);
	        for (int i = 0; i <= 8; i++) {
	            for (int j = 0; j <= 63; j++) {
	                Stats::SetMaskedBool("MPX_ARENAWARSPSTAT_BOOL" + std::to_string(i), j, true);
	            }
	        }
	}

	static void AwardsDiamondCasinoNResort()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_AWD_ODD_JOBS", 50);
	        Stats::SetInt("MPX_VCM_FLOW_PROGRESS", -1);
	        Stats::SetInt("MPX_VCM_STORY_PROGRESS", 5);
	        Stats::SetBool("MPX_AWD_FIRST_TIME1", true);
	        Stats::SetBool("MPX_AWD_FIRST_TIME2", true);
	        Stats::SetBool("MPX_AWD_FIRST_TIME3", true);
	        Stats::SetBool("MPX_AWD_FIRST_TIME4", true);
	        Stats::SetBool("MPX_AWD_FIRST_TIME5", true);
	        Stats::SetBool("MPX_AWD_FIRST_TIME6", true);
	        Stats::SetBool("MPX_AWD_ALL_IN_ORDER", true);
	        Stats::SetBool("MPX_AWD_SUPPORTING_ROLE", true);
	        Stats::SetBool("MPX_AWD_LEADER", true);
	        Stats::SetBool("MPX_AWD_SURVIVALIST", true);
	        bool Paragon = Stats::GetBool("MPX_CAS_VEHICLE_REWARD");
	        if (Paragon == true) {
	            Stats::SetBool("MPX_CAS_VEHICLE_REWARD", true);
	            } else {
	            Stats::SetBool("MPX_CAS_VEHICLE_REWARD", false);
	        }
	        for (int i = 0; i <= 6; i++) {
	            for (int j = 0; j <= 63; j++) {
	                Stats::SetMaskedBool("MPX_CASINOPSTAT_BOOL" + std::to_string(i), j, true);
	            }
	        }
	}

	static void AwardsArcade()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_AWD_PREPARATION", 50);
	        Stats::SetInt("MPX_AWD_ASLEEPONJOB", 20);
	        Stats::SetInt("MPX_AWD_DAICASHCRAB", 100000);
	        Stats::SetInt("MPX_AWD_BIGBRO", 40);
	        Stats::SetInt("MPX_AWD_SHARPSHOOTER", 40);
	        Stats::SetInt("MPX_AWD_RACECHAMP", 40);
	        Stats::SetInt("MPX_AWD_BATSWORD", 1000000);
	        Stats::SetInt("MPX_AWD_COINPURSE", 950000);
	        Stats::SetInt("MPX_AWD_ASTROCHIMP", 3000000);
	        Stats::SetInt("MPX_AWD_MASTERFUL", 40000);
	        Stats::SetInt("MPX_SCGW_NUM_WINS_GANG_0", 50);
	        Stats::SetInt("MPX_SCGW_NUM_WINS_GANG_1", 50);
	        Stats::SetInt("MPX_SCGW_NUM_WINS_GANG_2", 50);
	        Stats::SetInt("MPX_SCGW_NUM_WINS_GANG_3", 50);
	        Stats::SetInt("MPX_CH_ARC_CAB_CLAW_TROPHY", -1);
	        Stats::SetInt("MPX_CH_ARC_CAB_LOVE_TROPHY", -1);
	        Stats::SetInt("MPX_IAP_MAX_MOON_DIST", 2147483647);
	        Stats::SetInt("MPX_SCGW_INITIALS_0", 69644);
	        Stats::SetInt("MPX_SCGW_INITIALS_1", 50333);
	        Stats::SetInt("MPX_SCGW_INITIALS_2", 63512);
	        Stats::SetInt("MPX_SCGW_INITIALS_3", 46136);
	        Stats::SetInt("MPX_SCGW_INITIALS_4", 21638);
	        Stats::SetInt("MPX_SCGW_INITIALS_5", 2133);
	        Stats::SetInt("MPX_SCGW_INITIALS_6", 1215);
	        Stats::SetInt("MPX_SCGW_INITIALS_7", 2444);
	        Stats::SetInt("MPX_SCGW_INITIALS_8", 38023);
	        Stats::SetInt("MPX_SCGW_INITIALS_9", 2233);
	        Stats::SetInt("MPX_FOOTAGE_INITIALS_0", 0);
	        Stats::SetInt("MPX_FOOTAGE_INITIALS_1", 64);
	        Stats::SetInt("MPX_FOOTAGE_INITIALS_2", 8457);
	        Stats::SetInt("MPX_FOOTAGE_INITIALS_3", 91275);
	        Stats::SetInt("MPX_FOOTAGE_INITIALS_4", 53260);
	        Stats::SetInt("MPX_FOOTAGE_INITIALS_5", 78663);
	        Stats::SetInt("MPX_FOOTAGE_INITIALS_6", 25103);
	        Stats::SetInt("MPX_FOOTAGE_INITIALS_7", 102401);
	        Stats::SetInt("MPX_FOOTAGE_INITIALS_8", 12672);
	        Stats::SetInt("MPX_FOOTAGE_INITIALS_9", 74380);
	        Stats::SetInt("MPX_FOOTAGE_SCORE_0", 284544);
	        Stats::SetInt("MPX_FOOTAGE_SCORE_1", 275758);
	        Stats::SetInt("MPX_FOOTAGE_SCORE_2", 100000);
	        Stats::SetInt("MPX_FOOTAGE_SCORE_3", 90000);
	        Stats::SetInt("MPX_FOOTAGE_SCORE_4", 80000);
	        Stats::SetInt("MPX_FOOTAGE_SCORE_5", 70000);
	        Stats::SetInt("MPX_FOOTAGE_SCORE_6", 60000);
	        Stats::SetInt("MPX_FOOTAGE_SCORE_7", 50000);
	        Stats::SetInt("MPX_FOOTAGE_SCORE_8", 40000);
	        Stats::SetInt("MPX_FOOTAGE_SCORE_9", 30000);
	        for (int i = 0; i <= 9; i++) {
	            Stats::SetInt("MPX_IAP_INITIALS_" + std::to_string(i), 50);
	            Stats::SetInt("MPX_IAP_SCORE_" + std::to_string(i), 50);
	            Stats::SetInt("MPX_IAP_SCORE_" + std::to_string(i), 50);
	            Stats::SetInt("MPX_SCGW_SCORE_" + std::to_string(i), 50);
	            Stats::SetInt("MPX_DG_DEFENDER_INITIALS_" + std::to_string(i), 69644);
	            Stats::SetInt("MPX_DG_DEFENDER_SCORE_" + std::to_string(i), 50);
	            Stats::SetInt("MPX_DG_MONKEY_INITIALS_" + std::to_string(i), 69644);
	            Stats::SetInt("MPX_DG_MONKEY_SCORE_" + std::to_string(i), 50);
	            Stats::SetInt("MPX_DG_PENETRATOR_INITIALS_" + std::to_string(i), 69644);
	            Stats::SetInt("MPX_DG_PENETRATOR_SCORE_" + std::to_string(i), 50);
	            Stats::SetInt("MPX_GGSM_INITIALS_" + std::to_string(i), 69644);
	            Stats::SetInt("MPX_GGSM_SCORE_" + std::to_string(i), 50);
	            Stats::SetInt("MPX_TWR_INITIALS_" + std::to_string(i), 69644);
	            Stats::SetInt("MPX_TWR_SCORE_" + std::to_string(i), 50);
	        }
	        Stats::SetBool("MPX_AWD_SCOPEOUT", true);
	        Stats::SetBool("MPX_AWD_CREWEDUP", true);
	        Stats::SetBool("MPX_AWD_MOVINGON", true);
	        Stats::SetBool("MPX_AWD_PROMOCAMP", true);
	        Stats::SetBool("MPX_AWD_GUNMAN", true);
	        Stats::SetBool("MPX_AWD_SMASHNGRAB", true);
	        Stats::SetBool("MPX_AWD_INPLAINSI", true);
	        Stats::SetBool("MPX_AWD_UNDETECTED", true);
	        Stats::SetBool("MPX_AWD_ALLROUND", true);
	        Stats::SetBool("MPX_AWD_ELITETHEIF", true);
	        Stats::SetBool("MPX_AWD_PRO", true);
	        Stats::SetBool("MPX_AWD_SUPPORTACT", true);
	        Stats::SetBool("MPX_AWD_SHAFTED", true);
	        Stats::SetBool("MPX_AWD_COLLECTOR", true);
	        Stats::SetBool("MPX_AWD_DEADEYE", true);
	        Stats::SetBool("MPX_AWD_PISTOLSATDAWN", true);
	        Stats::SetBool("MPX_AWD_TRAFFICAVOI", true);
	        Stats::SetBool("MPX_AWD_CANTCATCHBRA", true);
	        Stats::SetBool("MPX_AWD_WIZHARD", true);
	        Stats::SetBool("MPX_AWD_APEESCAP", true);
	        Stats::SetBool("MPX_AWD_MONKEYKIND", true);
	        Stats::SetBool("MPX_AWD_AQUAAPE", true);
	        Stats::SetBool("MPX_AWD_KEEPFAITH", true);
	        Stats::SetBool("MPX_AWD_TRUELOVE", true);
	        Stats::SetBool("MPX_AWD_NEMESIS", true);
	        Stats::SetBool("MPX_AWD_FRIENDZONED", true);
	        Stats::SetBool("MPX_IAP_CHALLENGE_0", true);
	        Stats::SetBool("MPX_IAP_CHALLENGE_1", true);
	        Stats::SetBool("MPX_IAP_CHALLENGE_2", true);
	        Stats::SetBool("MPX_IAP_CHALLENGE_3", true);
	        Stats::SetBool("MPX_IAP_CHALLENGE_4", true);
	        Stats::SetBool("MPX_IAP_GOLD_TANK", true);
	        Stats::SetBool("MPX_SCGW_WON_NO_DEATHS", true);
	        for (int i = 0; i <= 4; i++) {
	            for (int j = 0; j <= 63; j++) {
	                Stats::SetMaskedBool("MPX_CASINOHSTPSTAT_BOOL" + std::to_string(i), j, true);
	            }
	        }
	        for (int i = 0; i <= 6; i++) {
	            for (int j = 0; j <= 63; j++) {
	                Stats::SetMaskedBool("MPX_CASINOPSTAT_BOOL" + std::to_string(i), j, true);
	            }
	        }
	}

	static void AwardsLsSummerSpecial()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetBool("MPX_AWD_KINGOFQUB3D", true);
	        Stats::SetBool("MPX_AWD_QUBISM", true);
	        Stats::SetBool("MPX_AWD_QUIBITS", true);
	        Stats::SetBool("MPX_AWD_GODOFQUB3D", true);
	        Stats::SetBool("MPX_AWD_ELEVENELEVEN", true);
	        Stats::SetBool("MPX_AWD_GOFOR11TH", true);
	        Stats::SetMaskedInt("MPX_SU20PSTAT_INT", 35, 8, 1);
	        for (int i = 0; i <= 1; i++) {
	            for (int j = 0; j <= 63; j++) {
	                Stats::SetMaskedBool("MPX_SU20PSTAT_BOOL" + std::to_string(i), j, true);
	                Stats::SetMaskedBool("MPX_SU20TATTOOSTAT_BOOL" + std::to_string(i), j, true);
	            }
	        }
	}

	static void AwardsLsTuners()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_AWD_CAR_CLUB_MEM", 100);
	        Stats::SetInt("MPX_AWD_SPRINTRACER", 50);
	        Stats::SetInt("MPX_AWD_STREETRACER", 50);
	        Stats::SetInt("MPX_AWD_PURSUITRACER", 50);
	        Stats::SetInt("MPX_AWD_TEST_CAR", 240);
	        Stats::SetInt("MPX_AWD_AUTO_SHOP", 50);
	        Stats::SetInt("MPX_AWD_GROUNDWORK", 40);
	        Stats::SetInt("MPX_AWD_CAR_EXPORT", 100);
	        Stats::SetInt("MPX_AWD_ROBBERY_CONTRACT", 100);
	        Stats::SetInt("MPX_AWD_FACES_OF_DEATH", 100);
	        Stats::SetBool("MPX_AWD_CAR_CLUB", true);
	        Stats::SetBool("MPX_AWD_PRO_CAR_EXPORT", true);
	        Stats::SetBool("MPX_AWD_UNION_DEPOSITORY", true);
	        Stats::SetBool("MPX_AWD_MILITARY_CONVOY", true);
	        Stats::SetBool("MPX_AWD_FLEECA_BANK", true);
	        Stats::SetBool("MPX_AWD_FREIGHT_TRAIN", true);
	        Stats::SetBool("MPX_AWD_BOLINGBROKE_ASS", true);
	        Stats::SetBool("MPX_AWD_IAA_RAID", true);
	        Stats::SetBool("MPX_AWD_METH_JOB", true);
	        Stats::SetBool("MPX_AWD_BUNKER_RAID", true);
	        Stats::SetBool("MPX_AWD_STRAIGHT_TO_VIDEO", true);
	        Stats::SetBool("MPX_AWD_MONKEY_C_MONKEY_DO", true);
	        Stats::SetBool("MPX_AWD_TRAINED_TO_KILL", true);
	        Stats::SetBool("MPX_AWD_DIRECTOR", true);
	        for (int i = 0; i <= 8; i++) {
	            for (int j = 0; j <= 63; j++) {
	                Stats::SetMaskedBool("MPX_TUNERPSTAT_BOOL" + std::to_string(i), j, true);
	            }
	        }
	}

	static void AwardsContract()
	{
		if (!*Pointers.IsSessionStarted)
			return;
	        Stats::SetInt("MPX_AWD_CONTRACTOR", 50);
	        Stats::SetInt("MPX_AWD_COLD_CALLER", 50);
	        Stats::SetInt("MPX_AWD_PRODUCER", 60);
	        Stats::SetInt("MPX_FIXERTELEPHONEHITSCOMPL", 10);
	        Stats::SetInt("MPX_PAYPHONE_BONUS_KILL_METHOD", 10);
	        Stats::SetInt("MPX_PAYPHONE_BONUS_KILL_METHOD", -1);
	        Stats::SetInt("MPX_FIXER_GENERAL_BS", -1);
	        Stats::SetInt("MPX_FIXER_COMPLETED_BS", -1);
	        Stats::SetInt("MPX_FIXER_STORY_BS", -1);
	        Stats::SetInt("MPX_FIXER_STORY_STRAND", -1);
	        Stats::SetInt("MPX_FIXER_STORY_COOLDOWN", -1);
	        Stats::SetInt("MPX_FIXER_COUNT", 510);
	        Stats::SetInt("MPX_FIXER_SC_VEH_RECOVERED", 85);
	        Stats::SetInt("MPX_FIXER_SC_VAL_RECOVERED", 85);
	        Stats::SetInt("MPX_FIXER_SC_GANG_TERMINATED", 85);
	        Stats::SetInt("MPX_FIXER_SC_VIP_RESCUED", 85);
	        Stats::SetInt("MPX_FIXER_SC_ASSETS_PROTECTED", 85);
	        Stats::SetInt("MPX_FIXER_SC_EQ_DESTROYED", 85);
	        Stats::SetInt("MPX_FIXER_EARNINGS", 19734860);
	        Stats::SetBool("MPX_AWD_TEEING_OFF", true);
	        Stats::SetBool("MPX_AWD_PARTY_NIGHT", true);
	        Stats::SetBool("MPX_AWD_BILLIONAIRE_GAMES", true);
	        Stats::SetBool("MPX_AWD_HOOD_PASS", true);
	        Stats::SetBool("MPX_AWD_STUDIO_TOUR", true);
	        Stats::SetBool("MPX_AWD_DONT_MESS_DRE", true);
	        Stats::SetBool("MPX_AWD_BACKUP", true);
	        Stats::SetBool("MPX_AWD_SHORTFRANK_1", true);
	        Stats::SetBool("MPX_AWD_SHORTFRANK_2", true);
	        Stats::SetBool("MPX_AWD_SHORTFRANK_3", true);
	        Stats::SetBool("MPX_AWD_CONTR_KILLER", true);
	        Stats::SetBool("MPX_AWD_DOGS_BEST_FRIEND", true);
	        Stats::SetBool("MPX_AWD_MUSIC_STUDIO", true);
	        Stats::SetBool("MPX_AWD_SHORTLAMAR_1", true);
	        Stats::SetBool("MPX_AWD_SHORTLAMAR_2", true);
	        Stats::SetBool("MPX_AWD_SHORTLAMAR_3", true);
	        Stats::SetBool("MPX_BS_FRANKLIN_DIALOGUE_0", true);
	        Stats::SetBool("MPX_BS_FRANKLIN_DIALOGUE_1", true);
	        Stats::SetBool("MPX_BS_FRANKLIN_DIALOGUE_2", true);
	        Stats::SetBool("MPX_BS_IMANI_D_APP_SETUP", true);
	        Stats::SetBool("MPX_BS_IMANI_D_APP_STRAND", true);
	        Stats::SetBool("MPX_BS_IMANI_D_APP_PARTY", true);
	        Stats::SetBool("MPX_BS_IMANI_D_APP_PARTY_2", true);
	        Stats::SetBool("MPX_BS_IMANI_D_APP_PARTY_F", true);
	        Stats::SetBool("MPX_BS_IMANI_D_APP_BILL", true);
	        Stats::SetBool("MPX_BS_IMANI_D_APP_BILL_2", true);
	        Stats::SetBool("MPX_BS_IMANI_D_APP_BILL_F", true);
	        Stats::SetBool("MPX_BS_IMANI_D_APP_HOOD", true);
	        Stats::SetBool("MPX_BS_IMANI_D_APP_HOOD_2", true);
	        Stats::SetBool("MPX_BS_IMANI_D_APP_HOOD_F", true);
	        for (int j = 0; j <= 63; j++) {
	            Stats::SetMaskedBool("MPX_FIXERPSTAT_BOOL0", j, true);
	            Stats::SetMaskedBool("MPX_FIXERPSTAT_BOOL1", j, true);
	            Stats::SetMaskedBool("MPX_FIXERTATTOOSTAT_BOOL0", j, true);
	        }
	}

	class CmdAwardsVictory : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsVictory();
		}
	};

	static CmdAwardsVictory _awards_victory{"awards_victory", "Awards: Victory", "Unlocks the Victory award stats."};

	class CmdAwardsGeneral : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsGeneral();
		}
	};

	static CmdAwardsGeneral _awards_general{"awards_general", "Awards: General", "Unlocks the General award stats."};

	class CmdAwardsWeapons : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsWeapons();
		}
	};

	static CmdAwardsWeapons _awards_weapons{"awards_weapons", "Awards: Weapons", "Unlocks the Weapons award stats."};

	class CmdAwardsCrimes : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsCrimes();
		}
	};

	static CmdAwardsCrimes _awards_crimes{"awards_crimes", "Awards: Crimes", "Unlocks the Crimes award stats."};

	class CmdAwardsVehicles : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsVehicles();
		}
	};

	static CmdAwardsVehicles _awards_vehicles{"awards_vehicles", "Awards: Vehicles", "Unlocks the Vehicles award stats."};

	class CmdAwardsCombat : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsCombat();
		}
	};

	static CmdAwardsCombat _awards_combat{"awards_combat", "Awards: Combat", "Unlocks the Combat award stats."};

	class CmdAwardsUnlockAllApartmentHeistsAwards : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsUnlockAllApartmentHeistsAwards();
		}
	};

	static CmdAwardsUnlockAllApartmentHeistsAwards _awards_unlock_all_apartment_heists_awards{"awards_unlock_all_apartment_heists_awards", "Awards: Unlock All Apartment Heists Awards", "Unlocks the Unlock All Apartment Heists Awards award stats."};

	class CmdAwardsUnlockAllDiamondCasinoHeistAwards : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsUnlockAllDiamondCasinoHeistAwards();
		}
	};

	static CmdAwardsUnlockAllDiamondCasinoHeistAwards _awards_unlock_all_diamond_casino_heist_awards{"awards_unlock_all_diamond_casino_heist_awards", "Awards: Unlock All Diamond Casino Heist Awards", "Unlocks the Unlock All Diamond Casino Heist Awards award stats."};

	class CmdAwardsUnlockAllCayoHeistAwards : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsUnlockAllCayoHeistAwards();
		}
	};

	static CmdAwardsUnlockAllCayoHeistAwards _awards_unlock_all_cayo_heist_awards{"awards_unlock_all_cayo_heist_awards", "Awards: Unlock All Cayo Heist Awards", "Unlocks the Unlock All Cayo Heist Awards award stats."};

	class CmdAwardsUnlockAllDoomsdayHeistAwards : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsUnlockAllDoomsdayHeistAwards();
		}
	};

	static CmdAwardsUnlockAllDoomsdayHeistAwards _awards_unlock_all_doomsday_heist_awards{"awards_unlock_all_doomsday_heist_awards", "Awards: Unlock All Doomsday Heist Awards", "Unlocks the Unlock All Doomsday Heist Awards award stats."};

	class CmdAwardsTheKortzCenterHeist : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsTheKortzCenterHeist();
		}
	};

	static CmdAwardsTheKortzCenterHeist _awards_the_kortz_center_heist{"awards_the_kortz_center_heist", "Awards: The Kortz Center Heist", "Unlocks the The Kortz Center Heist award stats."};

	class CmdAwardsASafehouseInTheHills : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsASafehouseInTheHills();
		}
	};

	static CmdAwardsASafehouseInTheHills _awards_a_safehouse_in_the_hills{"awards_a_safehouse_in_the_hills", "Awards: A Safehouse In The Hills", "Unlocks the A Safehouse In The Hills award stats."};

	class CmdAwardsAgentsOfSabotage : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsAgentsOfSabotage();
		}
	};

	static CmdAwardsAgentsOfSabotage _awards_agents_of_sabotage{"awards_agents_of_sabotage", "Awards: Agents of Sabotage", "Unlocks the Agents of Sabotage award stats."};

	class CmdAwardsAfterHours : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsAfterHours();
		}
	};

	static CmdAwardsAfterHours _awards_after_hours{"awards_after_hours", "Awards: After Hours", "Unlocks the After Hours award stats."};

	class CmdAwardsArenaWar : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsArenaWar();
		}
	};

	static CmdAwardsArenaWar _awards_arena_war{"awards_arena_war", "Awards: Arena War", "Unlocks the Arena War award stats."};

	class CmdAwardsDiamondCasinoNResort : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsDiamondCasinoNResort();
		}
	};

	static CmdAwardsDiamondCasinoNResort _awards_diamond_casino_n_resort{"awards_diamond_casino_n_resort", "Awards: Diamond Casino n Resort", "Unlocks the Diamond Casino n Resort award stats."};

	class CmdAwardsArcade : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsArcade();
		}
	};

	static CmdAwardsArcade _awards_arcade{"awards_arcade", "Awards: Arcade", "Unlocks the Arcade award stats."};

	class CmdAwardsLsSummerSpecial : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsLsSummerSpecial();
		}
	};

	static CmdAwardsLsSummerSpecial _awards_ls_summer_special{"awards_ls_summer_special", "Awards: LS Summer Special", "Unlocks the LS Summer Special award stats."};

	class CmdAwardsLsTuners : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsLsTuners();
		}
	};

	static CmdAwardsLsTuners _awards_ls_tuners{"awards_ls_tuners", "Awards: LS Tuners", "Unlocks the LS Tuners award stats."};

	class CmdAwardsContract : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsContract();
		}
	};

	static CmdAwardsContract _awards_contract{"awards_contract", "Awards: Contract", "Unlocks the Contract award stats."};

	class CmdUnlockAllAwards : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			AwardsVictory();
			AwardsGeneral();
			AwardsWeapons();
			AwardsCrimes();
			AwardsVehicles();
			AwardsCombat();
			AwardsUnlockAllApartmentHeistsAwards();
			AwardsUnlockAllDiamondCasinoHeistAwards();
			AwardsUnlockAllCayoHeistAwards();
			AwardsUnlockAllDoomsdayHeistAwards();
			AwardsTheKortzCenterHeist();
			AwardsASafehouseInTheHills();
			AwardsAgentsOfSabotage();
			AwardsAfterHours();
			AwardsArenaWar();
			AwardsDiamondCasinoNResort();
			AwardsArcade();
			AwardsLsSummerSpecial();
			AwardsLsTuners();
			AwardsContract();
		}
	};

	static CmdUnlockAllAwards _allawards{"allawards", "Unlock All Awards", "Unlocks every award (stats) group ported from Ultimate Menu."};
}
