#include "Troll.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildTrollMenu()
	{
		auto menu = std::make_shared<Category>("Troll");

		auto general = std::make_shared<Group>("General");
		auto vehicle = std::make_shared<Group>("Vehicle");

		general->AddItem(std::make_shared<PlayerCommandItem>("giveweapons"_J));

		vehicle->AddItem(std::make_shared<PlayerCommandItem>("deleteveh"_J));

		menu->AddItem(general);
		menu->AddItem(vehicle);

		return menu;
	}
}
