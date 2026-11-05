#pragma once

#include <array>
#include <string>

#include "core/settings/IStateSerializer.hpp"
#include <nlohmann/json.hpp>

namespace YimMenu
{

struct OutfitData
{
    std::array<int, 12> drawable{};     // Drawable ID for component 0-11
    std::array<int, 12> drawableTex{};  // Texture ID for drawable 0-11
    std::array<int, 11> prop{};         // Prop ID for component 0-10
    std::array<int, 11> propTex{};      // Texture ID for prop 0-10
};

struct WardrobeSlot
{
    std::string name;
    OutfitData data;
    bool hasData = false;
};

class Wardrobe : public IStateSerializer
{
public:
    Wardrobe();
    static Wardrobe& GetInstance();

    void SaveSlot(int slotIndex);
    void ApplySlot(int slotIndex);
    void ClearSlot(int slotIndex);
    
    const WardrobeSlot& GetSlot(int index) const;
    std::string GetSlotName(int index) const;
    void SetSlotName(int index, const std::string& name);
    bool HasSlotData(int index) const;

    // IStateSerializer
    const char* GetSerializerComponentName();
    void SaveStateImpl(nlohmann::json& value) override;
    void LoadStateImpl(nlohmann::json& state) override;

private:
    std::array<WardrobeSlot, 21> m_Slots{};
    bool m_Dirty = false;

    void SaveOutfitToSlot(int slotIndex);
    void ApplyOutfitToSlot(int slotIndex);
};

}
