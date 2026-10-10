#include "Themes.hpp"
#include "core/commands/ColorCommand.hpp"
#include "game/frontend/submenus/Settings/GUISettings.hpp"

namespace YimMenu
{
	void DefaultStyle()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		// Text
		style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

		// Backgrounds (Chrome Believer: #151515 base, #1A1E24 panels, #222830 cards)
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.082f, 0.082f, 0.082f, 1.00f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.102f, 0.118f, 0.141f, 1.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.070f, 0.070f, 0.090f, 0.95f);

		// Borders
		style.Colors[ImGuiCol_Border] = ImVec4(0.28f, 0.28f, 0.28f, 0.25f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

		// Frames
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.133f, 0.157f, 0.188f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.549f, 0.682f, 0.851f, 0.35f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.549f, 0.682f, 0.851f, 0.50f);

		// Title bars
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.06f, 0.07f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.102f, 0.118f, 0.141f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.04f, 0.04f, 0.05f, 1.00f);

		// Menus/tabs (baby blue #8CAED9 / hover #A8C4E8 / pressed #6E96C8)
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.102f, 0.118f, 0.141f, 1.00f);
		style.Colors[ImGuiCol_Tab] = ImVec4(0.549f, 0.682f, 0.851f, 0.85f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.659f, 0.769f, 0.910f, 0.85f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.549f, 0.682f, 0.851f, 1.00f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.35f, 0.45f, 0.58f, 0.70f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.549f, 0.682f, 0.851f, 0.85f);

		// Scrollbar
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.80f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.35f, 0.42f, 0.52f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.431f, 0.588f, 0.784f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.549f, 0.682f, 0.851f, 1.00f);

		// Checkmarks, sliders
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.549f, 0.682f, 0.851f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.549f, 0.682f, 0.851f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.431f, 0.588f, 0.784f, 1.00f);

		// Buttons
		style.Colors[ImGuiCol_Button] = ImVec4(0.549f, 0.682f, 0.851f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.659f, 0.769f, 0.910f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.431f, 0.588f, 0.784f, 1.00f);

		// Headers
		style.Colors[ImGuiCol_Header] = ImVec4(0.40f, 0.52f, 0.68f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.549f, 0.682f, 0.851f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.431f, 0.588f, 0.784f, 1.00f);

		// Separators
		style.Colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.50f);
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.549f, 0.682f, 0.851f, 0.78f);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.659f, 0.769f, 0.910f, 1.00f);

		// Resize grips
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.549f, 0.682f, 0.851f, 0.30f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.549f, 0.682f, 0.851f, 0.60f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.659f, 0.769f, 0.910f, 0.90f);

		// Plots
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.80f, 0.80f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.85f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.549f, 0.682f, 0.851f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.659f, 0.769f, 0.910f, 1.00f);

		// Drag & drop
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.549f, 0.682f, 0.851f, 0.90f);

		// Navigation highlighting
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.549f, 0.682f, 0.851f, 1.00f);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);

		// Modal/background dimming
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.35f);

		// Rounding
		style.GrabRounding = style.FrameRounding = style.ChildRounding = style.WindowRounding = 8.0f;
	}

	void SetupStyle()
	{
		// Apply default style first
		DefaultStyle();

		// Initialize the color/rounding commands and load saved settings
		InitializeColorCommands(); // This will call LoadSettings internally

		// Apply loaded colors/rounding to ImGui
		ApplyThemeToImGui();
	}
}
