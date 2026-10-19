#include "Menu.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "core/renderer/Renderer.hpp"
#include "game/frontend/fonts/Fonts.hpp"
#include "submenus/Self.hpp"
#include "submenus/Vehicle.hpp"
#include "submenus/Teleport.hpp"
#include "submenus/Network.hpp"
#include "submenus/Players.hpp"
#include "submenus/Recovery.hpp"
#include "submenus/Settings.hpp"
#include "submenus/Debug.hpp"
#include "submenus/World.hpp"
#include "Onboarding.hpp"

namespace YimMenu
{
	void Menu::Init()
	{
		// Arguably the only place this file should be edited at for more menus
		UIManager::AddSubmenu(std::make_shared<Submenus::Self>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Vehicle>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Teleport>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Network>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Players>());
		UIManager::AddSubmenu(std::make_shared<Submenus::World>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Recovery>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Settings>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Debug>());

		Renderer::AddRendererCallback(
		    [&] {
			    ProcessOnboarding();
			    if (!GUI::IsOpen())
				    return;

			    ImGui::PushFont(Menu::Font::g_DefaultFont);
			    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImU32(ImColor(21, 21, 21)));

			    UIManager::Draw();

			    ImGui::PopStyleColor();
			    ImGui::PopFont();
		    },
		    -1);
	}

	static const ImWchar* GetGlyphRangesCyrillicOnly()
	{
		static const ImWchar ranges[] =
		    {
		        0x0400,
		        0x052F, // Cyrillic + Cyrillic Supplement
		        0x2DE0,
		        0x2DFF, // Cyrillic Extended-A
		        0xA640,
		        0xA69F, // Cyrillic Extended-B
		        0,
		    };
		return &ranges[0];
	}

	static ImFont* CreateFontWithCyrillicSupport(ImGuiIO& io, float size)
	{
		ImFontConfig FontCfg{};
		FontCfg.FontDataOwnedByAtlas = false;

		auto font = io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::MainFont), sizeof(Fonts::MainFont), size, &FontCfg, io.Fonts->GetGlyphRangesDefault());

		// just use Arial for Cyrillic

		FontCfg.MergeMode = true;
		io.Fonts->AddFontFromFileTTF((std::filesystem::path(std::getenv("SYSTEMROOT")) / "Fonts" / "arial.ttf").string().c_str(), size, &FontCfg, GetGlyphRangesCyrillicOnly());
		io.Fonts->AddFontFromFileTTF((std::filesystem::path(std::getenv("SYSTEMROOT")) / "Fonts" / "meiryo.ttc").string().c_str(), size, &FontCfg, io.Fonts->GetGlyphRangesJapanese());

		io.Fonts->Build();

		return font;
	}

	static std::filesystem::path FindFirstExistingFont(const std::vector<std::filesystem::path>& candidates)
	{
		for (const auto& candidate : candidates)
		{
			std::error_code ec;
			if (std::filesystem::exists(candidate, ec) && !ec)
				return candidate;
		}

		return {};
	}

	static ImFont* LoadFontFile(ImGuiIO& io, const std::filesystem::path& path, float size)
	{
		if (path.empty())
			return nullptr;

		ImFontConfig cfg{};
		cfg.FontDataOwnedByAtlas = false;
		return io.Fonts->AddFontFromFileTTF(path.string().c_str(), size, &cfg, io.Fonts->GetGlyphRangesDefault());
	}

	void Menu::SetupFonts()
	{
		auto& IO = ImGui::GetIO();
		auto file_path = std::filesystem::path(std::getenv("appdata")) / "Epsilon" / "imgui.ini";
		static auto path = file_path.string();
		IO.IniFilename = path.c_str();
		IO.LogFilename = NULL;
		ImFontConfig FontCfg{};
		FontCfg.FontDataOwnedByAtlas = false;

		IO.Fonts->Clear();
		Menu::Font::g_DefaultFont = CreateFontWithCyrillicSupport(IO, Menu::Font::g_DefaultFontSize);
		Menu::Font::g_OptionsFont = CreateFontWithCyrillicSupport(IO, Menu::Font::g_OptionsFontSize);
		Menu::Font::g_ChildTitleFont = CreateFontWithCyrillicSupport(IO, Menu::Font::g_ChildTitleFontSize);
		Menu::Font::g_ChatFont = CreateFontWithCyrillicSupport(IO, Menu::Font::g_ChatFontSize);
		Menu::Font::g_OverlayFont = CreateFontWithCyrillicSupport(IO, Menu::Font::g_OverlayFontSize);
		static const ImWchar full_range[] = {0x0020, 0xFFFF, 0};
		Menu::Font::g_AwesomeFont = IO.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::IconFont), sizeof(Fonts::IconFont), Menu::Font::g_AwesomeFontSize, &FontCfg, full_range);

		UIManager::SetOptionsFont(Menu::Font::g_OptionsFont);

		// Drop Inter-Regular.ttf / Inter-SemiBold.ttf and LiberationSerif-Regular.ttf into
		// %APPDATA%\Epsilon\fonts to get the intended Epsilon look; otherwise we fall back to
		// Times New Roman from the Windows font directory, then to the bundled font.
		const auto fontDir = std::filesystem::path(std::getenv("appdata")) / "Epsilon" / "fonts";
		const auto winFonts = std::filesystem::path(std::getenv("SYSTEMROOT")) / "Fonts";

		const auto uiFontPath = FindFirstExistingFont({
		    fontDir / "Inter-Regular.ttf",
		    fontDir / "inter.ttf",
		    winFonts / "Inter-Regular.ttf",
		    winFonts / "Inter.ttf",
		    winFonts / "segoeui.ttf",
		    winFonts / "tahoma.ttf",
		});

		const auto serifFontPath = FindFirstExistingFont({
		    fontDir / "LiberationSerif-Regular.ttf",
		    winFonts / "times.ttf",
		    winFonts / "LiberationSerif-Regular.ttf",
		});

		if (auto uiFont = LoadFontFile(IO, uiFontPath, Menu::Font::g_EpsilonUIFontSize))
			Menu::Font::g_EpsilonUIFont = uiFont;
		else
			Menu::Font::g_EpsilonUIFont = Menu::Font::g_OptionsFont;

		if (auto serifFont = LoadFontFile(IO, serifFontPath, Menu::Font::g_EpsilonSerifFontSize))
			Menu::Font::g_EpsilonSerifFont = serifFont;
		else
			Menu::Font::g_EpsilonSerifFont = Menu::Font::g_DefaultFont;

		IO.Fonts->Build();

		if (auto notificationFont = LoadFontFile(IO, uiFontPath, 15.0f))
			Menu::Font::g_NotificationFont = notificationFont;
		else
			Menu::Font::g_NotificationFont = Menu::Font::g_OptionsFont;

		Renderer::SetFontsUpdated();
	}
}
