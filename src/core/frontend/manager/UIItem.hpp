#pragma once
#include "core/util/Joaat.hpp"
#include <optional>
#include <string>

namespace YimMenu
{
	// Preferably, all items should be saved in a global instance to make UI elements searchable
	class UIItem
	{
	public:
		struct ToggleRow
		{
			std::string Label;
			std::string Description;
			bool State = false;
		};

		virtual void Draw() = 0;
		virtual bool CanDraw()
		{
			return true;
		}

		// Only toggle-backed items return a row here. Styles that lay out their own
		// rows use this to render a label/description/switch without losing the command.
		virtual std::optional<ToggleRow> GetToggleRow() const
		{
			return std::nullopt;
		}

		virtual bool SetToggleState(bool state)
		{
			return false;
		}
	};
}