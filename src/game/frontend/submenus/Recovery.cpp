#include "Recovery.hpp"
#include "Recovery/HeistModifier.hpp"
#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"
#include "Recovery/DailyActivities.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
		#define ICON_FA_SACK_DOLLAR "\xef\x93\x80"
	    Submenu::Submenu("Recovery", ICON_FA_SACK_DOLLAR)
	{
		auto main = std::make_shared<Category>("Main");
		auto businesses = std::make_shared<Category>("Businesses");
		auto casino = std::make_shared<Category>("Casino");
		auto unlocks = std::make_shared<Category>("Unlocks");

		auto generalGroup = std::make_shared<Group>("General");
		auto businessGroup = std::make_shared<Group>("General");
		auto casinoSlots = std::make_shared<Group>("Slot Machines");
		auto casinoWheel = std::make_shared<Group>("Lucky Wheel");
		auto awardsGroup = std::make_shared<Group>("Awards");
		auto collectiblesGroup = std::make_shared<Group>("Collectibles");
		auto collectibleTpGroup = std::make_shared<Group>("Collectible Teleports");
		//auto casinoBlackJack = std::make_shared<Group>("Blackjack");
		//auto casinoRoulette = std::make_shared<Group>("Roulette");

		generalGroup->AddItem(std::make_shared<BoolCommandItem>("freeshopping"_J));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("playallmissionssolo"_J));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("unlockgtaplus"_J));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("overriderpmultiplier"_J));
		generalGroup->AddItem(std::make_shared<ConditionalItem>("overriderpmultiplier"_J, std::make_shared<FloatCommandItem>("rpmultiplierinput"_J)));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("freechangeappearance"_J));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("nochangeappearancecooldown"_J));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("allowgenderchange"_J));

		businessGroup->AddItem(std::make_shared<ListCommandItem>("businesssafe"_J));
		businessGroup->AddItem(std::make_shared<CommandItem>("claimsafeearnings"_J));

		casinoSlots->AddItem(std::make_shared<BoolCommandItem>("casinomanipulaterigslotmachines"_J));

		casinoWheel->AddItem(std::make_shared<ListCommandItem>("casinoluckywheelprize"_J));
		casinoWheel->AddItem(std::make_shared<BoolCommandItem>("casinomanipulateluckywheel"_J));

		awardsGroup->AddItem(std::make_shared<CommandItem>("allawards"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_victory"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_general"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_weapons"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_crimes"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_vehicles"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_combat"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_unlock_all_apartment_heists_awards"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_unlock_all_diamond_casino_heist_awards"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_unlock_all_cayo_heist_awards"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_unlock_all_doomsday_heist_awards"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_the_kortz_center_heist"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_a_safehouse_in_the_hills"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_agents_of_sabotage"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_after_hours"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_arena_war"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_diamond_casino_n_resort"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_arcade"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_ls_summer_special"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_ls_tuners"_J));
		awardsGroup->AddItem(std::make_shared<CommandItem>("awards_contract"_J));

		collectiblesGroup->AddItem(std::make_shared<CommandItem>("unlockallcollectibles"_J));
		collectiblesGroup->AddItem(std::make_shared<CommandItem>("unlockactionfigures"_J));
		collectiblesGroup->AddItem(std::make_shared<CommandItem>("unlocksignaljammers"_J));
		collectiblesGroup->AddItem(std::make_shared<CommandItem>("unlockplayingcards"_J));
		collectiblesGroup->AddItem(std::make_shared<CommandItem>("unlockprops"_J));
		collectiblesGroup->AddItem(std::make_shared<CommandItem>("unlockmovieprops"_J));
		collectiblesGroup->AddItem(std::make_shared<CommandItem>("unlockldorganics"_J));
		collectiblesGroup->AddItem(std::make_shared<CommandItem>("unlockghost"_J));

		collectibleTpGroup->AddItem(std::make_shared<IntCommandItem>("jackolanternindex"_J));
		collectibleTpGroup->AddItem(std::make_shared<CommandItem>("jackolanterntp"_J));
		collectibleTpGroup->AddItem(std::make_shared<CommandItem>("randomjackolanterntp"_J));
		collectibleTpGroup->AddItem(std::make_shared<IntCommandItem>("snowmanindex"_J));
		collectibleTpGroup->AddItem(std::make_shared<CommandItem>("snowmentp"_J));

		main->AddItem(generalGroup);
		businesses->AddItem(businessGroup);
		casino->AddItem(casinoSlots);
		casino->AddItem(casinoWheel);
		unlocks->AddItem(awardsGroup);
		unlocks->AddItem(collectiblesGroup);
		unlocks->AddItem(collectibleTpGroup);

		AddCategory(std::move(main));
		AddCategory(std::move(businesses));
		AddCategory(std::move(casino));
		AddCategory(std::move(unlocks));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
		AddCategory(BuildHeistModifierMenu());
		AddCategory(BuildDailyActivitiesMenu());
	}
}
