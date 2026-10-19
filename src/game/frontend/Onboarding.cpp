#include "Onboarding.hpp"
#include "GUI.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/BoolCommand.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	static BoolCommand _OnboardingComplete{"$onboardingcomplete", "", ""};

	void ProcessOnboarding()
	{
		if (_OnboardingComplete.GetState())
			return;

		static bool ensure_popup_open = [] {
			ImGui::OpenPopup("IMPORTANT! PLEASE READ!");
			GUI::SetOnboarding(true);
			return true;
		}();

		const auto window_size = ImVec2{700, 500};
		const auto window_position = ImVec2{(*Pointers.ScreenResX - window_size.x) / 2, (*Pointers.ScreenResY - window_size.y) / 2};

		ImGui::SetNextWindowSize(window_size, ImGuiCond_Once);
		ImGui::SetNextWindowPos(window_position, ImGuiCond_Once);

		if (ImGui::BeginPopupModal("IMPORTANT! PLEASE READ!", nullptr, ImGuiWindowFlags_NoSavedSettings))
		{
			ImGui::TextWrapped("%s",
			    "Welcome to Epsilon V1.0.0b! You can press INSERT or Ctrl+\\ to open the menu. "
			    "By default you can play with everyone. If BattlEye is running (no FSL), you may be kicked from public sessions "
			    "while using certain features — if that happens, enable Epsilon-only sessions to keep playing with other Epsilon users.");
			static int value = 0;
			ImGui::RadioButton("Play with everyone", &value, 0);
			ImGui::SameLine();
			ImGui::RadioButton("Play with Epsilon users only", &value, 1);
			ImGui::TextWrapped("%s",
			    "You can always change your choice later in Network > Spoofing > Join Epsilon-only Sessions. "
			    "This menu is private software. Only use builds obtained from your trusted source.");
			ImGui::TextWrapped("%s",
			    "Most importantly, mess around and have fun with Epsilon!");
			if (ImGui::Button("Close"))
			{
				Commands::GetCommand<BoolCommand>("cheaterpool"_J)->SetState(value == 1);
				_OnboardingComplete.SetState(true);
				GUI::SetOnboarding(false);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}
