#pragma once
#include "Category.hpp"

#include <algorithm>
#include <cctype>
#include <string>

namespace YimMenu
{
	class Submenu
	{
	public:
		constexpr Submenu(std::string name, std::string icon = "") :
		    m_Name(name),
		    m_Icon(icon)
		{
		}

		std::shared_ptr<Category> GetActiveCategory() const
		{
			return m_ActiveCategory;
		}

		void AddCategory(std::shared_ptr<Category>&& category);
		void RemoveCategory(const std::shared_ptr<Category>& category);
		void DrawCategorySelectors();
		void SetActiveCategory(const std::shared_ptr<Category> category);
		void Draw();

		// Search
		void DrawSearchBar();
		bool HasActiveSearch() const { return m_SearchQuery.size() > 0; }
		const std::string& GetSearchQuery() const { return m_SearchQuery; }
		char* GetSearchBuffer() { return m_SearchBuffer; }
		size_t GetSearchBufferSize() { return sizeof(m_SearchBuffer); }
		void SetSearchQuery(std::string query) { m_SearchQuery = std::move(query); strncpy(m_SearchBuffer, m_SearchQuery.c_str(), sizeof(m_SearchBuffer) - 1); m_SearchBuffer[sizeof(m_SearchBuffer) - 1] = '\0'; }
		void ClearSearch() { m_SearchQuery.clear(); m_SearchBuffer[0] = '\0'; }

	private:
		std::shared_ptr<Category> m_ActiveCategory;
		char m_SearchBuffer[256] = {};
		std::string m_SearchQuery;

	public:
		std::vector<std::shared_ptr<Category>> m_Categories;
		std::string m_Name;
		std::string m_Icon; // currently unused
	};
}