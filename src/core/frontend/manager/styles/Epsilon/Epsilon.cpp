#include "game/pointers/Pointers.hpp"
#include "game/frontend/Menu.hpp"
#include "game/frontend/GUI.hpp"
#include "game/frontend/items/Items.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "game/frontend/submenus/Settings/GUISettings.hpp"
#include "core/frontend/widgets/toggle/imgui_toggle.hpp"
#include <algorithm>
#include <cctype>
#include <cfloat>
#include <format>
#include <memory>
#include <string>
#include <vector>

namespace YimMenu
{
	namespace
	{
		// Brand accent, pinned so the interface can never drift toward purple.
		const ImVec4 k_Accent{140.0f / 255.0f, 174.0f / 255.0f, 217.0f / 255.0f, 1.0f};

		constexpr float k_Radius = 14.0f;
		constexpr float k_HeaderHeight = 62.0f;
		constexpr float k_SidebarWidth = 212.0f;
		constexpr float k_CardHeaderHeight = 36.0f;
		constexpr float k_CardRadius = 10.0f;
		constexpr float k_Gap = 12.0f;
		constexpr float k_SidebarRowHeight = 40.0f;
		constexpr float k_RowPadX = 14.0f;
		constexpr float k_SwitchGap = 10.0f;

		const ImVec4& Accent()
		{
			return k_Accent;
		}

		ImU32 WithAlpha(const ImVec4& color, float alpha)
		{
			return ImGui::ColorConvertFloat4ToU32({color.x, color.y, color.z, color.w * alpha});
		}

		ImU32 StyleColor(ImGuiCol idx)
		{
			return ImGui::GetColorU32(idx);
		}

		std::string Upper(std::string text)
		{
			std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
				return static_cast<char>(std::toupper(c));
			});
			return text;
		}

		float RowHeight()
		{
			// label + description + breathing room, so descriptions never touch the next label
			const float fontSize = ImGui::GetFontSize();
			return fontSize * 2.0f + 14.0f;
		}

		float ToggleWidth()
		{
			return ImGui::GetFrameHeight() * 1.85f;
		}

		// Usable text width for a row: card width minus the left pad, the switch, the right pad
		// and a gap so descriptions never run under the switch.
		float RowTextWidth(float width)
		{
			return std::max(60.0f, width - k_RowPadX - ToggleWidth() - k_RowPadX - k_SwitchGap);
		}

		// Rows are measured instead of assumed: a description that wraps to two lines grows its
		// own row rather than sliding under the switch or into the next label.
		float MeasureRowHeight(const UIItem& item, float width)
		{
			auto row = item.GetToggleRow();
			if (!row)
				return RowHeight();

			ImFont* font = Menu::Font::g_EpsilonUIFont ? Menu::Font::g_EpsilonUIFont : ImGui::GetFont();
			const float fontSize = ImGui::GetFontSize();
			const float labelHeight = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, row->Label.c_str()).y;

			if (row->Description.empty())
				return labelHeight + 20.0f;

			const float descHeight = font->CalcTextSizeA(fontSize, RowTextWidth(width), 0.0f, row->Description.c_str()).y;
			return labelHeight + descHeight + 4.0f + 20.0f;
		}

		// ImGui has no letter spacing, so wide-tracked wordmarks are drawn glyph by glyph.
		float SpacedWidth(ImFont* font, float size, const std::string& text, float spacing)
		{
			float width = 0.0f;
			for (char c : text)
			{
				const std::string glyph(1, c);
				width += font->CalcTextSizeA(size, FLT_MAX, 0.0f, glyph.c_str(), glyph.c_str() + 1).x + spacing;
			}

			return width > 0.0f ? width - spacing : 0.0f;
		}

		void SpacedText(ImDrawList* draw, ImFont* font, float size, ImVec2 pos, ImU32 color, const std::string& text, float spacing)
		{
			float x = pos.x;
			for (char c : text)
			{
				const std::string glyph(1, c);
				draw->AddText(font, size, ImVec2(x, pos.y), color, glyph.c_str());
				x += font->CalcTextSizeA(size, FLT_MAX, 0.0f, glyph.c_str(), glyph.c_str() + 1).x + spacing;
			}
		}

		struct CardData
		{
			std::shared_ptr<Group> Group;
			int Total = 0;
			int Enabled = 0;
		};

		// label + grey description on the left, switch on the right
		void DrawToggleRow(UIItem& item, float width, float height)
		{
			auto row = item.GetToggleRow();
			if (!row)
				return;

			const ImVec2 start = ImGui::GetCursorScreenPos();

			ImFont* font = Menu::Font::g_EpsilonUIFont ? Menu::Font::g_EpsilonUIFont : ImGui::GetFont();
			const float fontSize = ImGui::GetFontSize();
			const ImVec2 labelSize = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, row->Label.c_str());
			const bool hasDescription = !row->Description.empty();

			const float toggleHeight = ImGui::GetFrameHeight();
			const float toggleWidth = ToggleWidth();
			const float switchLeft = start.x + width - toggleWidth - k_RowPadX;

			float descHeight = 0.0f;
			if (hasDescription)
				descHeight = font->CalcTextSizeA(fontSize, RowTextWidth(width), 0.0f, row->Description.c_str()).y;

			// The switch is submitted before the row hitbox and the hitbox stops short of it.
			// ImGui awards hover/click to the first item under the cursor, so a full-width
			// InvisibleButton placed first would swallow every click meant for the toggle.
			bool state = row->State;
			bool changed = false;

			ImGui::SetCursorScreenPos(ImVec2(switchLeft, start.y + (height - toggleHeight) * 0.5f));
			if (ImGui::Toggle("##epsilonSwitch", &state, ImVec2(toggleWidth, toggleHeight)))
				changed = true;

			const float rowWidth = std::max(40.0f, switchLeft - k_SwitchGap - start.x);

			ImGui::SetCursorScreenPos(start);
			ImGui::InvisibleButton("##epsilonRow", ImVec2(rowWidth, height));
			const bool hovered = ImGui::IsItemHovered();

			// Clicking anywhere on the row toggles it too.
			if (ImGui::IsItemClicked())
				changed = true;

			if (hovered)
				ImGui::GetWindowDrawList()->AddRectFilled(start, start + ImVec2(width, height), WithAlpha(Accent(), 0.07f), k_CardRadius * 0.5f);

			if (changed)
				item.SetToggleState(!row->State);

			const float blockHeight = labelSize.y + (hasDescription ? descHeight + 2.0f : 0.0f);
			const float blockTop = start.y + (height - blockHeight) * 0.5f;

			ImGui::PushFont(font);
			ImGui::SetCursorScreenPos(ImVec2(start.x + k_RowPadX, blockTop));
			ImGui::TextColored(ImGui::GetStyleColorVec4(ImGuiCol_Text), "%s", row->Label.c_str());

			if (hasDescription)
			{
				ImGui::SetCursorScreenPos(ImVec2(start.x + k_RowPadX, blockTop + labelSize.y + 2.0f));

				// PushTextWrapPos works in window-local space, so anchor it to the cursor.
				ImGui::PushTextWrapPos(ImGui::GetCursorPosX() + RowTextWidth(width));
				ImGui::TextColored(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled), "%s", row->Description.c_str());
				ImGui::PopTextWrapPos();
			}
			ImGui::PopFont();

			ImGui::SetCursorScreenPos(ImVec2(start.x, start.y + height));

			// Hotkey assignment, mirroring BoolCommandItem so the feature is not lost.
			const std::string popupTitle = std::format("{} Hotkey", row->Label);
			if (hovered)
			{
				ImGui::SetTooltip("%s", row->Description.c_str());
				if (GetAsyncKeyState(VK_OEM_3) & 0x8000)
					ImGui::OpenPopup(popupTitle.c_str());
			}

			ImGui::SetNextWindowSize(ImVec2(500, 120));
			if (ImGui::BeginPopupModal(popupTitle.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar))
			{
				ImGui::BulletText("Hover over the command name to change its hotkey");
				ImGui::BulletText("Press any registered key to remove");
				ImGui::Separator();
				ImGui::Spacing();

				if (ImGui::Button("Close") || ((!ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered()) && ImGui::IsMouseClicked(ImGuiMouseButton_Left)))
					ImGui::CloseCurrentPopup();

				ImGui::EndPopup();
			}
		}

		float DrawCard(const CardData& card, float width)
		{
			ImGui::PushID(card.Group->GetName().c_str());

			float bodyHeight = 0.0f;
			for (auto& child : card.Group->GetItems())
			{
				if (child && child->CanDraw() && child->GetToggleRow())
					bodyHeight += MeasureRowHeight(*child, width);
			}

			const float height = k_CardHeaderHeight + 4.0f + bodyHeight + 8.0f;

			const ImVec2 start = ImGui::GetCursorScreenPos();
			const ImVec2 end(start.x + width, start.y + height);
			auto* draw = ImGui::GetWindowDrawList();

			draw->AddRectFilled(start, end, StyleColor(ImGuiCol_ChildBg), k_CardRadius);
			draw->AddRect(start, end, StyleColor(ImGuiCol_Border), k_CardRadius);

			const std::string title = Upper(card.Group->GetName());
			const bool allOn = card.Enabled == card.Total;
			const bool noneOn = card.Enabled == 0;

			ImFont* titleFont = Menu::Font::g_EpsilonUIFont ? Menu::Font::g_EpsilonUIFont : ImGui::GetFont();
			ImGui::PushFont(titleFont);
			const float titleSize = ImGui::GetFontSize();
			const float titleHeight = ImGui::CalcTextSize(title.c_str()).y;
			ImGui::PopFont();

			const float headerMid = start.y + k_CardHeaderHeight * 0.5f;
			const float dotRadius = 3.5f;
			const ImVec2 dot(start.x + 16.0f + dotRadius, headerMid);
			draw->AddCircleFilled(dot, dotRadius, WithAlpha(Accent(), allOn ? 1.0f : 0.45f));

			draw->AddText(
			    titleFont,
			    titleSize,
			    ImVec2(dot.x + dotRadius + 8.0f, headerMid - titleHeight * 0.5f),
			    StyleColor(ImGuiCol_Text),
			    title.c_str());

			const std::string badge = allOn ? std::format("{} ON", card.Enabled) : (noneOn ? "DEFAULT" : "MIXED");

			ImGui::PushFont(titleFont);
			const ImVec2 badgeSize = ImGui::CalcTextSize(badge.c_str());
			ImGui::PopFont();

			const float padX = 9.0f;
			const float padY = 4.0f;
			const ImVec2 badgeMin(end.x - 14.0f - badgeSize.x - padX * 2.0f, headerMid - badgeSize.y * 0.5f - padY);
			const ImVec2 badgeMax(end.x - 14.0f, headerMid + badgeSize.y * 0.5f + padY);

			draw->AddRectFilled(badgeMin, badgeMax, WithAlpha(Accent(), allOn ? 0.20f : 0.08f), (badgeMax.y - badgeMin.y) * 0.5f);
			draw->AddText(
			    titleFont,
			    titleSize,
			    ImVec2(badgeMin.x + padX, badgeMin.y + padY),
			    allOn ? WithAlpha(Accent(), 1.0f) : StyleColor(ImGuiCol_TextDisabled),
			    badge.c_str());

			draw->AddLine(
			    ImVec2(start.x + 1.0f, start.y + k_CardHeaderHeight),
			    ImVec2(end.x - 1.0f, start.y + k_CardHeaderHeight),
			    StyleColor(ImGuiCol_Border));

			float y = start.y + k_CardHeaderHeight + 4.0f;
			int rowIndex = 0;
			for (auto& child : card.Group->GetItems())
			{
				if (!child || !child->CanDraw())
					continue;

				const float rowHeight = MeasureRowHeight(*child, width);

				ImGui::PushID(rowIndex++);
				ImGui::SetCursorScreenPos(ImVec2(start.x, y));
				DrawToggleRow(*child, width, rowHeight);
				ImGui::PopID();
				y += rowHeight;
			}

			ImGui::SetCursorScreenPos(ImVec2(start.x, end.y));
			ImGui::Dummy(ImVec2(0, 0));

			ImGui::PopID();

			return height;
		}

		void DrawHeaderDecorations(float width)
		{
			auto* draw = ImGui::GetWindowDrawList();
			const ImVec2 origin = ImGui::GetCursorScreenPos();

			const float tileSize = 32.0f;
			const ImVec2 tileMin(origin.x + 18.0f, origin.y + (k_HeaderHeight - tileSize) * 0.5f);
			const ImVec2 tileMax(tileMin.x + tileSize, tileMin.y + tileSize);
			draw->AddRectFilled(tileMin, tileMax, WithAlpha(Accent(), 1.0f), 9.0f);

			ImFont* serif = Menu::Font::g_EpsilonSerifFont ? Menu::Font::g_EpsilonSerifFont : ImGui::GetFont();
			const float serifSize = Menu::Font::g_EpsilonSerifFontSize;
			const ImVec2 markSize = serif->CalcTextSizeA(serifSize, FLT_MAX, 0.0f, "E");
			draw->AddText(serif, serifSize, ImVec2(tileMin.x + (tileSize - markSize.x) * 0.5f, tileMin.y + (tileSize - markSize.y) * 0.5f - 1.0f), ImGui::ColorConvertFloat4ToU32({0.08f, 0.08f, 0.09f, 1.0f}), "E");

			const std::string wordmark = "EPSILON";
			const float textLeft = tileMax.x + 14.0f;

			SpacedText(draw, serif, serifSize, ImVec2(textLeft, origin.y + 13.0f), StyleColor(ImGuiCol_Text), wordmark, 3.0f);

			ImFont* uiFont = Menu::Font::g_EpsilonUIFont ? Menu::Font::g_EpsilonUIFont : ImGui::GetFont();
			draw->AddText(
			    uiFont,
			    ImGui::GetFontSize(),
			    ImVec2(textLeft, origin.y + 13.0f + serifSize + 3.0f),
			    StyleColor(ImGuiCol_TextDisabled),
			    "Kifflom, brother");

			if (Menu::Font::g_AwesomeFont)
			{
				// Screen-space, so anchor to the window origin rather than the content width.
				const float right = origin.x + width;
				const ImU32 ghost = WithAlpha(Accent(), 0.09f);
				draw->AddText(Menu::Font::g_AwesomeFont, 40.0f, ImVec2(right - 240.0f, origin.y + 6.0f), ghost, "\xef\x84\xb2");
				draw->AddText(Menu::Font::g_AwesomeFont, 40.0f, ImVec2(right - 178.0f, origin.y + 6.0f), ghost, "\xef\x80\x87");
				draw->AddText(Menu::Font::g_AwesomeFont, 40.0f, ImVec2(right - 116.0f, origin.y + 6.0f), ghost, "\xef\x83\xa3");
			}

			draw->AddLine(ImVec2(origin.x, origin.y + k_HeaderHeight), ImVec2(origin.x + width, origin.y + k_HeaderHeight), StyleColor(ImGuiCol_Border));
		}

		bool DrawWindowButton(const char* id, const char* glyph, ImVec2 min, ImVec2 max, bool close)
		{
			ImGui::SetCursorScreenPos(min);
			ImGui::InvisibleButton(id, max - min);

			const bool hovered = ImGui::IsItemHovered();
			auto* draw = ImGui::GetWindowDrawList();

			if (hovered)
				draw->AddRectFilled(min, max, close ? WithAlpha({0.85f, 0.35f, 0.35f, 1.0f}, 0.35f) : WithAlpha(Accent(), 0.18f), 8.0f);

			ImFont* font = ImGui::GetFont();
			const float fontSize = ImGui::GetFontSize();
			const ImVec2 size = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, glyph);
			draw->AddText(
			    font,
			    fontSize,
			    ImVec2(min.x + (max.x - min.x - size.x) * 0.5f, min.y + (max.y - min.y - size.y) * 0.5f),
			    hovered ? StyleColor(ImGuiCol_Text) : StyleColor(ImGuiCol_TextDisabled),
			    glyph);

			return ImGui::IsItemClicked();
		}
	}

	void RenderEpsilonTheme()
	{
		YimMenu::SyncColorCommandsToStyle();

		auto& style = ImGui::GetStyle();
		style.WindowRounding = k_Radius;
		style.ChildRounding = k_CardRadius;
		style.ScrollbarRounding = k_Radius;
		style.WindowBorderSize = 0.0f;

		static bool collapsed = false;
		static ImVec2 dragOffset{0.0f, 0.0f};
		static ImVec2 fullSize{0.0f, 0.0f};
		static bool sizeDirty = false;
		static bool dragArmed = false;

		const float defaultWidth = *YimMenu::Pointers.ScreenResX / 1.8f;
		const float defaultHeight = *YimMenu::Pointers.ScreenResY / 1.7f;

		// fullSize tracks the live window, so the glow and the collapsed strip follow a manual resize.
		const float liveWidth = fullSize.x > 1.0f ? fullSize.x : defaultWidth;
		// The collapsed strip is exactly the header, plus the window's own padding — otherwise the
		// 62px header child gets clipped and the tagline is cut in half.
		const float collapsedHeight = k_HeaderHeight + style.FramePadding.y * 2.0f;
		const ImVec2 windowSize(liveWidth, collapsed ? collapsedHeight : (fullSize.y > 1.0f ? fullSize.y : defaultHeight));
		const ImVec2 basePos((*YimMenu::Pointers.ScreenResX - windowSize.x) * 0.5f, (*YimMenu::Pointers.ScreenResY - windowSize.y) * 0.5f);

		if (auto* background = ImGui::GetBackgroundDrawList())
		{
			const ImVec2 pos = basePos + dragOffset;
			for (int i = 4; i >= 1; --i)
			{
				const float spread = static_cast<float>(i) * 3.5f;
				background->AddRectFilled(
				    pos - ImVec2(spread, spread),
				    pos + windowSize + ImVec2(spread, spread),
				    WithAlpha(Accent(), 0.010f * static_cast<float>(5 - i)),
				    k_Radius + spread);
			}
		}

		ImGui::SetNextWindowPos(basePos + dragOffset, ImGuiCond_Always);

		// Only force the size on the frames where the collapsed state actually changes, so a
		// manual window resize is not reverted every frame.
		if (collapsed)
		{
			ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
		}
		else if (sizeDirty)
		{
			ImGui::SetNextWindowSize(fullSize, ImGuiCond_Always);
			sizeDirty = false;
		}
		else
		{
			ImGui::SetNextWindowSize(ImVec2(defaultWidth, defaultHeight), ImGuiCond_FirstUseEver);
		}

		const ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
		                               ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;

		if (!ImGui::Begin("##EpsilonWindow", nullptr, flags))
		{
			ImGui::End();
			return;
		}

		if (!collapsed)
			fullSize = ImGui::GetWindowSize();

		ImFont* uiFont = Menu::Font::g_EpsilonUIFont ? Menu::Font::g_EpsilonUIFont : Menu::Font::g_DefaultFont;
		if (uiFont)
			ImGui::PushFont(uiFont);

		const float bodyWidth = ImGui::GetContentRegionAvail().x;

		if (ImGui::BeginChild(
		        "##epsilonHeader",
		        ImVec2(bodyWidth, k_HeaderHeight),
		        false,
		        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground))
		{
			DrawHeaderDecorations(ImGui::GetContentRegionAvail().x);

			const float top = ImGui::GetCursorScreenPos().y;
			const float buttonSize = 26.0f;

			const ImVec2 headerOrigin = ImGui::GetWindowPos();
			const float right = headerOrigin.x + ImGui::GetContentRegionAvail().x - 14.0f;
			const float buttonY = top + (k_HeaderHeight - buttonSize) * 0.5f;

			const ImVec2 closeMin(right - buttonSize, buttonY);
			const ImVec2 closeMax(right, buttonY + buttonSize);
			const ImVec2 minMin(right - buttonSize - 8.0f - buttonSize, buttonY);
			const ImVec2 minMax(right - buttonSize - 8.0f, buttonY + buttonSize);

			if (DrawWindowButton("##epsilonClose", "\xc3\x97", closeMin, closeMax, true))
				GUI::Toggle();

			if (DrawWindowButton("##epsilonMinimize", "\xe2\x88\x92", minMin, minMax, false))
			{
				collapsed = !collapsed;
				sizeDirty = true;
			}

			// The whole header bar is a drag surface, apart from the window buttons.
			// The mouse is tested against the header rect directly: SetCursorScreenPos
			// takes screen coordinates, so an InvisibleButton strip could not be
			// anchored to the window's left edge without ending up off-screen.
			const ImVec2 headerMin = ImGui::GetWindowPos();
			const ImVec2 headerMax = headerMin + ImGui::GetWindowSize();
			const ImVec2 mouse = ImGui::GetIO().MousePos;

			const auto inside = [&](const ImVec2& a, const ImVec2& b) {
				return mouse.x >= a.x && mouse.x <= b.x && mouse.y >= a.y && mouse.y <= b.y;
			};

			const bool overButton = inside(closeMin, closeMax) || inside(minMin, minMax);
			const bool overHeader = inside(headerMin, headerMax);

			if (overHeader && !overButton && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				dragArmed = true;

			if (dragArmed && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
				dragArmed = false;

			if (dragArmed && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
				dragOffset += ImGui::GetIO().MouseDelta;

			ImGui::SetCursorScreenPos(ImVec2(0.0f, top + k_HeaderHeight));
		}
		ImGui::EndChild();

		if (!collapsed)
		{
			const float bodyHeight = ImGui::GetContentRegionAvail().y;

			if (ImGui::BeginChild("##epsilonSidebar", ImVec2(k_SidebarWidth, bodyHeight), false, ImGuiWindowFlags_NoScrollbar))
			{
				const auto& submenus = YimMenu::UIManager::GetSubmenus();
				const auto activeSubmenu = YimMenu::UIManager::GetActiveSubmenu();

				for (size_t i = 0; i < submenus.size(); ++i)
				{
					const auto& submenu = submenus[i];
					const bool isActive = submenu == activeSubmenu;

					ImGui::PushID(static_cast<int>(i));
					ImGui::SetCursorScreenPos(ImVec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y));

					const float rowWidth = ImGui::GetContentRegionAvail().x;
					const ImVec2 rowStart = ImGui::GetCursorScreenPos();

					ImGui::InvisibleButton("##epsilonSide", ImVec2(rowWidth, k_SidebarRowHeight - 4.0f));
					const bool hovered = ImGui::IsItemHovered();

					if (ImGui::IsItemClicked())
					{
						YimMenu::UIManager::SetActiveSubmenu(submenu);
						YimMenu::UIManager::SetShowContentWindow(true);
					}

					const ImVec2 rowEnd(rowStart.x + rowWidth, rowStart.y + k_SidebarRowHeight - 4.0f);
					auto* draw = ImGui::GetWindowDrawList();

					if (isActive)
					{
						draw->AddRectFilled(rowStart, rowEnd, WithAlpha(Accent(), 0.20f), k_SidebarRowHeight * 0.5f);
						draw->AddRect(rowStart, rowEnd, WithAlpha(Accent(), 0.55f), k_SidebarRowHeight * 0.5f);
					}
					else if (hovered)
					{
						draw->AddRectFilled(rowStart, rowEnd, WithAlpha(Accent(), 0.08f), k_SidebarRowHeight * 0.5f);
					}

					const float midY = rowStart.y + (k_SidebarRowHeight - 4.0f) * 0.5f;

					if (Menu::Font::g_AwesomeFont && !submenu->m_Icon.empty())
					{
						const ImVec2 iconSize = Menu::Font::g_AwesomeFont->CalcTextSizeA(20.0f, FLT_MAX, 0.0f, submenu->m_Icon.c_str());
						draw->AddText(
						    Menu::Font::g_AwesomeFont,
						    20.0f,
						    ImVec2(rowStart.x + 14.0f, midY - iconSize.y * 0.5f),
						    isActive ? WithAlpha(Accent(), 1.0f) : StyleColor(ImGuiCol_TextDisabled),
						    submenu->m_Icon.c_str());
					}

					ImFont* font = ImGui::GetFont();
					const float fontSize = ImGui::GetFontSize();
					const ImVec2 labelSize = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, submenu->m_Name.c_str());
					draw->AddText(
					    font,
					    fontSize,
					    ImVec2(rowStart.x + 44.0f, midY - labelSize.y * 0.5f),
					    isActive ? StyleColor(ImGuiCol_Text) : StyleColor(ImGuiCol_TextDisabled),
					    submenu->m_Name.c_str());

					ImGui::SetCursorScreenPos(ImVec2(rowStart.x, rowEnd.y));
					ImGui::PopID();
				}
			}
			ImGui::EndChild();

			ImGui::SameLine(0.0f, k_Gap);

			if (ImGui::BeginChild("##epsilonContent", ImVec2(0.0f, bodyHeight), false))
			{
				auto submenu = YimMenu::UIManager::GetActiveSubmenu();

				if (submenu)
				{
					for (auto& category : submenu->m_Categories)
					{
						if (!category)
							continue;

						const bool isActive = category == submenu->GetActiveCategory();
						const ImVec2 start = ImGui::GetCursorScreenPos();

						ImGui::PushID(category->m_Name.c_str());
						ImGui::PushFont(Menu::Font::g_EpsilonUIFont ? Menu::Font::g_EpsilonUIFont : ImGui::GetFont());
						const ImVec2 size = ImGui::CalcTextSize(category->m_Name.c_str());
						ImFont* font = ImGui::GetFont();
						const float fontSize = ImGui::GetFontSize();
						ImGui::PopFont();

						const float padX = 14.0f;
						const float padY = 6.0f;
						const ImVec2 min(start.x, start.y);
						const ImVec2 max(start.x + size.x + padX * 2.0f, start.y + size.y + padY * 2.0f);

						ImGui::SetCursorScreenPos(start);
						ImGui::InvisibleButton("##epsilonCategory", max - min);

						if (ImGui::IsItemClicked())
							submenu->SetActiveCategory(category);

						auto* draw = ImGui::GetWindowDrawList();
						if (isActive)
							draw->AddRectFilled(min, max, WithAlpha(Accent(), 0.22f), (max.y - min.y) * 0.5f);
						else if (ImGui::IsItemHovered())
							draw->AddRectFilled(min, max, WithAlpha(Accent(), 0.09f), (max.y - min.y) * 0.5f);

						draw->AddText(font, fontSize, ImVec2(min.x + padX, min.y + padY), isActive ? StyleColor(ImGuiCol_Text) : StyleColor(ImGuiCol_TextDisabled), category->m_Name.c_str());

						ImGui::SetCursorScreenPos(ImVec2(start.x, max.y));
						ImGui::PopID();
						ImGui::SameLine(0.0f, 6.0f);
					}

					ImGui::NewLine();
					ImGui::Spacing();

					if (auto category = submenu->GetActiveCategory())
					{
						std::vector<CardData> cards;
						std::vector<std::shared_ptr<UIItem>> loose;

						for (auto& item : category->GetItems())
						{
							if (!item)
								continue;

							auto group = std::dynamic_pointer_cast<Group>(item);
							if (!group)
							{
								loose.push_back(item);
								continue;
							}

							CardData card;
							card.Group = group;
							bool onlyToggles = !group->GetName().empty();

							// Classification looks at what the group can hold, not at what happens to be
							// visible right now. A conditional row that is hidden at this moment must not
							// move the whole group between the card layout and the legacy renderer, or
							// enabling the condition would swap the entire submenu back to the old UI.
							for (auto& child : group->GetItems())
							{
								if (!child)
									continue;

								if (!child->GetToggleRow())
								{
									onlyToggles = false;
									break;
								}
							}

							// The badge counts what is on screen right now.
							for (auto& child : group->GetItems())
							{
								if (!child || !child->CanDraw())
									continue;

								auto row = child->GetToggleRow();
								if (!row)
									continue;

								card.Total++;
								card.Enabled += row->State ? 1 : 0;
							}

							if (onlyToggles && card.Total > 0)
							{
								cards.push_back(card);
							}
							else
							{
								loose.push_back(item);
							}
						}

						if (!cards.empty())
						{
							// Widths are computed out here and applied explicitly; letting the table
							// infer them left the cards short and a dead gap between columns.
							const float available = ImGui::GetContentRegionAvail().x;
							const float columnWidth = std::max(200.0f, (available - k_Gap * 3.0f) * 0.5f);

							const ImGuiTableFlags tableFlags = ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_PadOuterX;

							if (ImGui::BeginTable("##epsilonGrid", 2, tableFlags, ImVec2(available, 0.0f)))
							{
								ImGui::TableSetupColumn("##col0", ImGuiTableColumnFlags_WidthFixed, columnWidth);
								ImGui::TableSetupColumn("##col1", ImGuiTableColumnFlags_WidthFixed, columnWidth);

								for (size_t i = 0; i < cards.size(); i += 2)
								{
									ImGui::TableNextRow();
									ImGui::TableNextColumn();

									const float leftHeight = DrawCard(cards[i], columnWidth);

									ImGui::TableNextColumn();
									if (i + 1 < cards.size())
										DrawCard(cards[i + 1], columnWidth);
									else
										ImGui::Dummy(ImVec2(0.0f, leftHeight));
								}

								ImGui::EndTable();
							}

							ImGui::Spacing();
						}

						for (auto& item : loose)
						{
							if (item && item->CanDraw())
								item->Draw();
						}
					}
				}
			}
			ImGui::EndChild();
		}

		if (uiFont)
			ImGui::PopFont();

		ImGui::End();
	}
}