#include "UIManager.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/frontend/Menu.hpp"
#include "core/commands/ListCommand.hpp"

#include <cstring>

namespace YimMenu::Features
{
	static const std::vector<std::pair<int, const char*>> g_StyleOptions = {
		{0, "Classic"},
		{1, "Modern"},
		{2, "Modern (Vertical)"},
	    {3, "Modern (Modular)"},
	    {4, "Epsilon"},
	};

	// Expose as global reference so other code can use it
	static ListCommand _StyleSelector{
		"styleselector",
		"UI Style",
		"Choose the UI style",
		g_StyleOptions,
		4};
}

namespace YimMenu
{
	void UIManager::AddSubmenuImpl(const std::shared_ptr<Submenu>&& submenu)
	{
		if (!m_ActiveSubmenu)
			m_ActiveSubmenu = submenu;

		m_Submenus.push_back(std::move(submenu));
	}

	void UIManager::RemoveSubmenuImpl(const std::shared_ptr<Submenu>& submenu)
	{
		std::erase(m_Submenus, submenu);

		if (m_ActiveSubmenu == submenu)
			m_ActiveSubmenu = m_Submenus.empty() ? nullptr : m_Submenus.front();
	}

	void UIManager::SetActiveSubmenuImpl(const std::shared_ptr<Submenu> submenu)
	{
		m_ActiveSubmenu = submenu;
	}

	void UIManager::DrawImpl()
	{
		int selectedIndex = Features::_StyleSelector.GetState();

		// Render the selected theme based on the index, append when adding new themes
		switch (static_cast<UITheme>(selectedIndex))
		{
		case UITheme::Classic:
			RenderClassicTheme();
			break;
		case UITheme::Modern:
			RenderModernTheme();
			break;
		case UITheme::ModernV:
			RenderModernVTheme();
			break;
		case UITheme::Modular:
			RenderModularTheme();
			break;
		case UITheme::Epsilon:
			RenderEpsilonTheme();
			break;
		default:
			RenderClassicTheme(); // Default theme
			break;
		}
	}

	std::shared_ptr<Submenu> UIManager::GetActiveSubmenuImpl()
	{
		return m_ActiveSubmenu;
	}

	std::shared_ptr<Category> UIManager::GetActiveCategoryImpl()
	{
		if (m_ActiveSubmenu)
		{
			return m_ActiveSubmenu->GetActiveCategory();
		}

		return nullptr;
	}

	void UIManager::DrawGlobalSearchBar()
	{
		auto& inst = GetInstance();
		ImGui::PushItemWidth(300.0f);
		ImGui::InputTextWithHint("##globalMenuSearch", "Search all options...", inst.m_GlobalSearchBuffer, sizeof(inst.m_GlobalSearchBuffer));
		ImGui::PopItemWidth();

		// Keep the std::string in sync with the char buffer
		inst.m_GlobalSearchQuery = inst.m_GlobalSearchBuffer;

		if (!inst.m_GlobalSearchQuery.empty())
		{
			ImGui::SameLine();
			if (ImGui::SmallButton("Clear##globalMenuSearchClear"))
			{
				inst.m_GlobalSearchQuery.clear();
				inst.m_GlobalSearchBuffer[0] = '\0';
			}
		}
	}

	std::vector<UIManager::SearchResult> UIManager::SearchAllItems(const std::string& query)
	{
		auto& inst = GetInstance();
		std::vector<SearchResult> results;

		std::string needle = query;
		std::transform(needle.begin(), needle.end(), needle.begin(), [](unsigned char c) { return std::tolower(c); });

		for (auto& submenu : inst.m_Submenus)
		{
			if (!submenu)
				continue;

			for (auto& category : submenu->m_Categories)
			{
				if (!category)
					continue;

				for (auto& item : category->GetItems())
				{
					if (!item)
						continue;

					auto text = item->GetSearchText();
					if (text.empty())
						continue;

					auto haystack = text;
					std::transform(haystack.begin(), haystack.end(), haystack.begin(), [](unsigned char c) { return std::tolower(c); });

					if (haystack.find(needle) != std::string::npos)
					{
						results.push_back({submenu, category, item, text});
					}
				}
			}
		}

		return results;
	}
}