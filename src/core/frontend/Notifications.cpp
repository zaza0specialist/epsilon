#include "Notifications.hpp"

#include "core/logger/LogHelper.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/util/Joaat.hpp"
#include "game/frontend/Menu.hpp"

#include <algorithm>
#include <cctype>
#include <mutex>

namespace YimMenu
{

	Notification Notifications::ShowImpl(std::string title, std::string message, NotificationType type, int duration, std::function<void()> context_function, std::string context_function_name)
	{
		if (title.empty() || message.empty())
			return {};

		auto message_id = Joaat(title + message);

		auto exists = std::find_if(m_Notifications.begin(), m_Notifications.end(), [&](auto& notification) {
			return notification.second.m_Identifier == message_id;
		});

		if (exists != m_Notifications.end())
		{
			exists->second.m_CreatedOn = std::chrono::system_clock::now();
			return {};
		}

		Notification notification{};
		notification.m_Title = title;
		notification.m_Message = message;
		notification.m_Type = type;
		notification.m_CreatedOn = std::chrono::system_clock::now();
		notification.m_Duration = duration;
		notification.m_Identifier = message_id;

		if (context_function)
		{
			notification.m_ContextFunc = context_function;
			notification.m_ContextFuncName = context_function_name.empty() ? "Context Function" : context_function_name;
		}

		std::lock_guard<std::mutex> lock(m_mutex);
		auto result = m_Notifications.insert(std::make_pair(title + message, notification));

		return notification;
	}

	bool Notifications::EraseImpl(Notification notification)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		for (auto& [id, n] : m_Notifications)
		{
			if (n.m_Identifier == notification.m_Identifier)
			{
				n.m_Erasing = true;
				return true;
			}
		}

		return false;
	}

	namespace
	{
		// Brand accent, kept in sync with the Epsilon style so toasts match the window.
		const ImVec4 k_Accent{140.0f / 255.0f, 174.0f / 255.0f, 217.0f / 255.0f, 1.0f};

		constexpr float k_Radius = 10.0f;
		constexpr float k_PadX = 14.0f;

		std::string Upper(std::string text)
		{
			std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
				return static_cast<char>(std::toupper(c));
			});
			return text;
		}

		ImVec4 StatusColor(NotificationType type)
		{
			switch (type)
			{
			case NotificationType::Success:
				return ImVec4(0.36f, 0.78f, 0.47f, 1.0f);
			case NotificationType::Warning:
				return ImVec4(0.95f, 0.75f, 0.30f, 1.0f);
			case NotificationType::Error:
				return ImVec4(0.92f, 0.40f, 0.42f, 1.0f);
			case NotificationType::Info:
			default:
				return k_Accent;
			}
		}
	}

	static void DrawNotification(Notification& notification, int position)
	{
		const float yPos = position * (m_CardSizeY + 10.0f);
		const float xPos = 10.0f;

		const ImVec2 cardSize(m_CardSizeX, m_CardSizeY);

		ImGui::SetNextWindowSize(cardSize, ImGuiCond_Always);
		ImGui::SetNextWindowPos(ImVec2(xPos + notification.m_AnimationOffset, yPos + 10.0f), ImGuiCond_Always);

		const std::string windowTitle = std::to_string(position);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, k_Radius);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin(
		    windowTitle.c_str(),
		    nullptr,
		    ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
		        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
		        ImGuiWindowFlags_NoFocusOnAppearing);

		ImFont* font = Menu::Font::g_NotificationFont ? Menu::Font::g_NotificationFont : ImGui::GetFont();
		if (font)
			ImGui::PushFont(font);

		auto* draw = ImGui::GetWindowDrawList();
		const ImVec2 origin = ImGui::GetWindowPos();
		const ImVec2 size = ImGui::GetWindowSize();
		const ImVec2 end(origin.x + size.x, origin.y + size.y);

		const ImVec4 status = StatusColor(notification.m_Type);
		const ImU32 statusCol = ImGui::ColorConvertFloat4ToU32(status);

		draw->AddRectFilled(origin, end, ImGui::GetColorU32(ImGuiCol_ChildBg), k_Radius);
		draw->AddRect(origin, end, ImGui::GetColorU32(ImGuiCol_Border), k_Radius);

		// status dot
		const float dotY = origin.y + 19.0f;
		draw->AddCircleFilled(ImVec2(origin.x + k_PadX + 3.5f, dotY), 3.5f, statusCol);

		// title
		const std::string title = Upper(notification.m_Title);
		ImGui::SetCursorScreenPos(ImVec2(origin.x + k_PadX + 14.0f, origin.y + 9.0f));
		ImGui::TextUnformatted(title.c_str());

		// message
		ImGui::SetCursorScreenPos(ImVec2(origin.x + k_PadX + 14.0f, origin.y + 30.0f));
		ImGui::PushTextWrapPos(end.x - k_PadX);
		ImGui::TextColored(
		    ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled),
		    "%s",
		    notification.m_Message.c_str());
		ImGui::PopTextWrapPos();

		if (notification.m_ContextFunc)
		{
			ImGui::SetCursorScreenPos(ImVec2(origin.x + k_PadX + 14.0f, origin.y + size.y - 26.0f));
			if (ImGui::SmallButton(notification.m_ContextFuncName.c_str()))
			{
				FiberPool::Push([notification] {
					notification.m_ContextFunc();
				});
			}
		}

		// depletion line along the bottom edge
		const auto timeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - notification.m_CreatedOn).count();
		const float depletion = 1.0f - (timeElapsed / (float)notification.m_Duration);
		const float clamped = std::clamp(depletion, 0.0f, 1.0f);
		const float barHeight = 2.0f;

		draw->AddRectFilled(
		    ImVec2(origin.x + 1.0f, end.y - barHeight - 1.0f),
		    ImVec2(origin.x + 1.0f + (size.x - 2.0f) * clamped, end.y - 1.0f),
		    statusCol,
		    1.0f);

		if (font)
			ImGui::PopFont();

		ImGui::End();
		ImGui::PopStyleVar(3);
	}

	void Notifications::DrawImpl()
	{
		std::vector<std::string> keys_to_erase;
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			int position = 0;

			for (auto& [id, notification] : m_Notifications)
			{
				DrawNotification(notification, position);

				if (!notification.m_Erasing)
				{
					if (notification.m_AnimationOffset < 0)
						notification.m_AnimationOffset += m_CardAnimationSpeed;

					//Need this to account for changes in card size (x dimension), custom increments might result in odd numbers
					if (notification.m_AnimationOffset > 0)
						notification.m_AnimationOffset = 0.f;
				}
				else
				{
					notification.m_AnimationOffset -= m_CardAnimationSpeed;
					if (notification.m_AnimationOffset <= -m_CardSizeX)
						keys_to_erase.push_back(id);
				}


				if ((float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - notification.m_CreatedOn).count() >= notification.m_Duration)
					keys_to_erase.push_back(id);

				position++;
			}
		}
		std::lock_guard<std::mutex> lock(m_mutex);
		for (const auto& key : keys_to_erase)
		{
			m_Notifications.erase(key);
		}
	}
}
