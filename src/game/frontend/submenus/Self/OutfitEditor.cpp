#include "OutfitEditor.hpp"
#include "game/frontend/items/Items.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/backend/Outfit.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/features/recovery/Wardrobe.hpp"
#include "game/gta/Natives.hpp"
#include "core/util/Strings.hpp"
#include "misc/cpp/imgui_stdlib.h"

#include <cstdio>
#include <cstring>

namespace YimMenu
{
	// Real GTA V text formatting tokens (from GTA V Text Formatting spec):
	// ~r~ = Red, ~o~ = Orange, ~y~ = Yellow, ~g~ = Green, ~b~ = Blue,
	// ~q~ = Pink, ~p~ = Purple, ~h~ = White, ~c~ = Grey, ~m~ = Darker Grey,
	// ~u~ = Black, ~s~ = Reset
	static const std::vector<std::pair<const char*, ImVec4>>& GetOutfitTokens()
	{
		static const std::vector<std::pair<const char*, ImVec4>> tokens = {
			{"r",   ImVec4(1.00f, 0.00f, 0.00f, 1.0f)}, // ~r~ Red
			{"o",   ImVec4(1.00f, 0.55f, 0.10f, 1.0f)}, // ~o~ Orange
			{"y",   ImVec4(1.00f, 0.85f, 0.20f, 1.0f)}, // ~y~ Yellow
			{"g",   ImVec4(0.20f, 0.90f, 0.35f, 1.0f)}, // ~g~ Green
			{"b",   ImVec4(0.25f, 0.45f, 1.00f, 1.0f)}, // ~b~ Blue
			{"q",   ImVec4(1.00f, 0.45f, 0.75f, 1.0f)}, // ~q~ Pink
			{"p",   ImVec4(0.70f, 0.35f, 1.00f, 1.0f)}, // ~p~ Purple
			{"h",   ImVec4(1.00f, 1.00f, 1.00f, 1.0f)}, // ~h~ White
			{"c",   ImVec4(0.55f, 0.55f, 0.55f, 1.0f)}, // ~c~ Grey
			{"m",   ImVec4(0.38f, 0.38f, 0.38f, 1.0f)}, // ~m~ Darker Grey
			{"u",   ImVec4(0.15f, 0.15f, 0.15f, 1.0f)}, // ~u~ Black
		};
		return tokens;
	}

	static void DrawTokenizedText(const std::string& text)
	{
		size_t pos = 0;
		while (pos < text.size())
		{
			auto start = text.find('~', pos);
			if (start == std::string::npos)
			{
				ImGui::TextUnformatted(text.substr(pos).c_str());
				break;
			}

			if (start > pos)
			{
				ImGui::TextUnformatted(text.substr(pos, start - pos).c_str());
				ImGui::SameLine();
			}

			auto end = text.find('~', start + 1);
			if (end == std::string::npos)
			{
				ImGui::TextUnformatted(text.substr(pos).c_str());
				break;
			}

			std::string token = text.substr(start + 1, end - start - 1);
			bool found = false;
			ImVec4 color = ImGui::GetStyleColorVec4(ImGuiCol_Text);
			for (const auto& [name, c] : GetOutfitTokens())
			{
				if (token == name)
				{
					color = c;
					found = true;
					break;
				}
			}

			if (found)
				ImGui::PushStyleColor(ImGuiCol_Text, color);

			size_t nextStart = text.find('~', end + 1);
			if (nextStart == std::string::npos)
			{
				ImGui::TextUnformatted(text.substr(end + 1).c_str());
				if (found)
					ImGui::PopStyleColor();
				break;
			}
			else
			{
				ImGui::TextUnformatted(text.substr(end + 1, nextStart - end - 1).c_str());
				if (found)
					ImGui::PopStyleColor();
				ImGui::SameLine();
				pos = nextStart;
				continue;
			}
		}
	}

	// Row of colored token buttons that append their GTA token (~r~, ~g~, ...) to buf.
	static void RenderTokenButtons(char* buf, size_t bufSize)
	{
		ImGui::TextDisabled("Color tokens (~x~)");
		for (size_t i = 0; i < GetOutfitTokens().size(); i++)
		{
			const auto& [name, color] = GetOutfitTokens()[i];
			if (i % 6 != 0)
				ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Text, color);
			std::string label = std::string("~") + name + "~##tok" + std::to_string(i);
			if (ImGui::SmallButton(label.c_str()))
			{
				std::string token   = std::string("~") + name + "~";
				std::string current = buf;

				// collapse duplicate adjacent tokens instead of stacking them
				if (current.size() >= token.size() && current.compare(current.size() - token.size(), token.size(), token) == 0)
					current.erase(current.size() - token.size());

				while (!current.empty() && current.back() == ' ')
					current.pop_back();

				if (current.size() + token.size() + 2 < bufSize)
				{
					if (!current.empty())
						current += " ";
					current += token;
					std::snprintf(buf, bufSize, "%s", current.c_str());
				}
			}
			ImGui::PopStyleColor();
		}
	}

	class OutfitEditorMenu
	{
		Outfit::OutfitComponents components{};
		Outfit::OutfitProps props{};
		std::vector<std::string> folders{}, files{};
		std::string folder{}, file{};
		char outfitName[64]{}, newFolder[50]{};

	public:
		// refreshes the outfit editor data to current ped outfit
		void RefreshStats()
		{
			auto ped = Self::GetPed().GetHandle();
			for (auto& t : components.items)
			{
				auto& item = t.second;
				item.drawable_id = PED::GET_PED_DRAWABLE_VARIATION(ped, t.first);
				item.drawable_id_max = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, t.first) - 1;
				item.texture_id = PED::GET_PED_TEXTURE_VARIATION(ped, t.first);
				item.texture_id_max = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, t.first, item.drawable_id) - 1;
			}

			for (auto& t : props.items)
			{
				auto& item = t.second;
				item.drawable_id = PED::GET_PED_PROP_INDEX(ped, t.first, 0);
				item.drawable_id_max = PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(ped, t.first) - 1;
				item.texture_id = PED::GET_PED_PROP_TEXTURE_INDEX(ped, t.first);
				item.texture_id_max = PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(ped, t.first, item.drawable_id) - 1;
			}
		}

		void RenderComponents()
		{
			ImGui::BeginGroup();
			for (auto& t : components.items)
			{
				auto& item = t.second;
				ImGui::SetNextItemWidth(120);
				if (ImGui::InputInt(std::format("{} [0,{}]##1", item.label, item.drawable_id_max).c_str(), &item.drawable_id))
				{
					Outfit::OutfitEditor::CheckBoundsDrawable(item, 0);
					FiberPool::Push([id = t.first, item, this] {
						PED::SET_PED_COMPONENT_VARIATION(Self::GetPed().GetHandle(), id, item.drawable_id, 0, PED::GET_PED_PALETTE_VARIATION(Self::GetPed().GetHandle(), id));
						RefreshStats();
					});
				}
			}
			ImGui::EndGroup();
		}

		void RenderComponentsTextures()
		{
			ImGui::BeginGroup();
			for (auto& t : components.items)
			{
				auto& item = t.second;
				ImGui::SetNextItemWidth(120);
				if (ImGui::InputInt(std::format("{} TEX [0,{}]##2", item.label, item.texture_id_max).c_str(), &item.texture_id))
				{
					Outfit::OutfitEditor::CheckBoundsTexture(item, 0);
					FiberPool::Push([id = t.first, item, this] {
						PED::SET_PED_COMPONENT_VARIATION(Self::GetPed().GetHandle(), id, item.drawable_id, item.texture_id, PED::GET_PED_PALETTE_VARIATION(Self::GetPed().GetHandle(), id));
						RefreshStats();
					});
				}
			}
			ImGui::EndGroup();
		}

		void RenderProps()
		{
			for (auto& t : props.items)
			{
				auto& item = t.second;
				ImGui::SetNextItemWidth(120);
				if (ImGui::InputInt(std::format("{} [0,{}]##3", item.label, item.drawable_id_max).c_str(), &item.drawable_id))
				{
					Outfit::OutfitEditor::CheckBoundsDrawable(item, -1);
					FiberPool::Push([id = t.first, item, this] {
						if (item.drawable_id == -1)
							PED::CLEAR_PED_PROP(Self::GetPed().GetHandle(), id, 1);
						else
							PED::SET_PED_PROP_INDEX(Self::GetPed().GetHandle(), id, item.drawable_id, 0, TRUE, 0);
						RefreshStats();
					});
				}
			}
		}

		void RenderPropsTextures()
		{
			for (auto& t : props.items)
			{
				auto& item = t.second;
				ImGui::SetNextItemWidth(120);
				if (ImGui::InputInt(std::format("{} TEX [0,{}]##4", item.label, item.texture_id_max).c_str(), &item.texture_id))
				{
					Outfit::OutfitEditor::CheckBoundsTexture(item, -1);
					FiberPool::Push([id = t.first, item, this] {
						PED::SET_PED_PROP_INDEX(Self::GetPed().GetHandle(), id, item.drawable_id, item.texture_id, TRUE, 0);
						RefreshStats();
					});
				}
			}
		}

		void RenderOutfitList()
		{
			ImGui::BeginGroup();
			{
				// folders
				ImGui::SetNextItemWidth(300.f);
				if (ImGui::BeginCombo("", folder.empty() ? "Root" : folder.c_str()))
				{
					if (ImGui::Selectable("Root", folder == ""))
					{
						folder.clear();
						FiberPool::Push([this] {
							Outfit::OutfitEditor::RefreshList(folder, folders, files);
						});
					}

					for (std::string folderName : folders)
						if (ImGui::Selectable(folderName.c_str(), folder == folderName))
						{
							folder = folderName;
							FiberPool::Push([this] {
								Outfit::OutfitEditor::RefreshList(folder, folders, files);
							});
						}

					ImGui::EndCombo();
				}

				// files
				static std::string search;
				ImGui::SetNextItemWidth(300);
				if (ImGui::InputTextWithHint("###outfitname", "Search", &search))
					std::transform(search.begin(), search.end(), search.begin(), tolower);
				if (ImGui::BeginListBox("##saved_outfits", ImVec2(300, 300)))
				{
					for (const auto& pair : files)
					{
						std::string pair_lower = pair;
						std::transform(pair_lower.begin(), pair_lower.end(), pair_lower.begin(), tolower);
						if (pair_lower.contains(search))
						{
							auto fileName = pair.c_str();
							if (ImGui::Selectable(fileName, file == pair, ImGuiSelectableFlags_AllowItemOverlap))
								file = pair;
						}
					}
					ImGui::EndListBox();
				}
			}
			ImGui::EndGroup();
		}

		void RenderSaveButton(bool saveToNewFolder)
		{
			if (ImGui::Button("Save Outfit"))
				FiberPool::Push([saveToNewFolder, this] {
					std::string fileName = TrimString(outfitName);
					strcpy(outfitName, "");

					if (!fileName.size())
					{
						Notifications::Show("Outfit", "Filename empty!", NotificationType::Warning);
						return;
					}

					Outfit::OutfitEditor::SaveOutfit(fileName, folder);

					if (saveToNewFolder)
					{
						folder = newFolder; // set current folder to newly created folder
						strcpy(newFolder, "");
					}

					Outfit::OutfitEditor::RefreshList(folder, folders, files);
				});
		};

		void RenderOutfitListControls()
		{
			ImGui::BeginGroup();
			{
				if (ImGui::Button("Refresh list"))
					FiberPool::Push([this] {
						Outfit::OutfitEditor::RefreshList(folder, folders, files);
					});
				ImGui::Spacing();
				static bool applyHair = false;
				ImGui::Checkbox("Apply hair", &applyHair);
				ImGui::Spacing();
				if (ImGui::Button("Apply Selected Outfit"))
					FiberPool::Push([this] {
						Outfit::OutfitEditor::ApplyOutfitFromJson(folder, file, applyHair);
						applyHair = false; // reset everytime
						RefreshStats();
					});

				ImGui::Spacing();

				// save outfit
				ImGui::Text("Outfit Name");
				ImGui::SameLine();
				ImGui::SetNextItemWidth(250);
				ImGui::InputText("##filename", outfitName, IM_ARRAYSIZE(outfitName));

				if (folder.empty())
				{
					ImGui::Text("Folder Name");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(250);
					ImGui::InputText("##foldername", newFolder, IM_ARRAYSIZE(newFolder));
					RenderSaveButton(true);
				}
				else
					RenderSaveButton(false);
			}
			ImGui::EndGroup();
		}

		// Quick-save outfit slots with token-colored names
		void RenderWardrobeSlots()
		{
			auto& w = Wardrobe::GetInstance();

			static char editBuf[21][64]{};
			static int openSlot = -1;

			for (int i = 0; i < 21; i++)
			{
				ImGui::PushID(i);
				auto& slot = w.GetSlot(i);

				// slot name, tokens rendered in color
				ImGui::SetNextItemWidth(220);
				if (slot.name.empty())
					ImGui::TextDisabled("Slot %02d", i + 1);
				else
					DrawTokenizedText(slot.name);

				ImGui::SameLine();
				if (ImGui::SmallButton("Edit"))
				{
					openSlot  = i;
					auto name = slot.name;
					std::snprintf(editBuf[i], sizeof(editBuf[i]), "%s", name.c_str());
				}

				ImGui::SameLine();
				if (ImGui::SmallButton("Save"))
					FiberPool::Push([&w, i] {
						w.SaveSlot(i);
						w.SetGameSlotName(i, w.GetSlotName(i));
						Notifications::Show("Outfit", "Slot name saved.", NotificationType::Success);
					});

				ImGui::SameLine();
				if (ImGui::SmallButton("Load"))
					FiberPool::Push([&w, i] { w.ApplySlot(i); });

				ImGui::SameLine();
				if (ImGui::SmallButton("Clear"))
					FiberPool::Push([&w, i] { w.ClearSlot(i); });

				ImGui::SameLine();
				if (slot.hasData)
					ImGui::TextColored(ImVec4(0.30f, 0.85f, 0.35f, 1.0f), "saved");
				else
					ImGui::TextDisabled("empty");

				// edit popup: name field + color token buttons (per-slot popup ID)
				if (openSlot == i)
				{
					ImGui::OpenPopup(("Edit Slot Name##" + std::to_string(i)).c_str());
					openSlot = -1;
				}

				if (ImGui::BeginPopup(("Edit Slot Name##" + std::to_string(i)).c_str()))
				{
					ImGui::Text("Slot %02d name", i + 1);
					ImGui::SetNextItemWidth(320);
					ImGui::InputText("##slotname", editBuf[i], sizeof(editBuf[i]));

					ImGui::Spacing();
					RenderTokenButtons(editBuf[i], sizeof(editBuf[i]));

					ImGui::Spacing();
					if (ImGui::Button("Apply Name"))
					{
						w.SetSlotName(i, editBuf[i]);
						ImGui::CloseCurrentPopup();
					}
					ImGui::SameLine();
					if (ImGui::Button("Cancel"))
						ImGui::CloseCurrentPopup();

					ImGui::EndPopup();
				}

				ImGui::PopID();
			}
		}
	};

	std::shared_ptr<Category> CreateOutfitsMenu()
	{
		static OutfitEditorMenu editor{};
		auto category = std::make_shared<Category>("Outfit Editor");

		category->AddItem(std::make_shared<ImGuiItem>([] {
			if (ImGui::Button("Refresh Stats"))
				FiberPool::Push([] {
					editor.RefreshStats();
				});
			ImGui::SameLine();
			if (ImGui::Button("Randomize Outfit"))
				FiberPool::Push([] {
					Self::GetPed().RandomizeOutfit2();
				});

			editor.RenderComponents();
			ImGui::SameLine();
			editor.RenderComponentsTextures();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				editor.RenderProps();
				ImGui::Spacing();
				editor.RenderPropsTextures();
			}
			ImGui::EndGroup();

			ImGui::Spacing();

			editor.RenderOutfitList();
			ImGui::SameLine();
			editor.RenderOutfitListControls();

			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();

			ImGui::TextDisabled("Quick Slots");
			ImGui::Text("Click Edit on a slot, then use the color buttons to tag its name.");
			ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.1f, 1.0f), "Work in progress — syncing names to the game wardrobe may not work on all versions.");
			ImGui::Spacing();
			editor.RenderWardrobeSlots();
		}));

		return category;
	}
}
