#include "Wardrobe.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu
{

Wardrobe::Wardrobe() : IStateSerializer("wardrobe")
{
}

Wardrobe& Wardrobe::GetInstance()
{
    static Wardrobe instance;
    return instance;
}

void Wardrobe::SaveOutfitToSlot(int slotIndex)
{
    auto ped = PLAYER::PLAYER_PED_ID();
    if (!ped) return;

    auto& slot = m_Slots[slotIndex];
    
    for (int i = 0; i < 12; i++)
    {
        slot.data.drawable[i] = PED::GET_PED_DRAWABLE_VARIATION(ped, i);
        slot.data.drawableTex[i] = PED::GET_PED_TEXTURE_VARIATION(ped, i);
    }
    
    slot.hasData = true;
    MarkStateDirty();
}

void Wardrobe::ApplyOutfitToSlot(int slotIndex)
{
    auto ped = PLAYER::PLAYER_PED_ID();
    if (!ped) return;

    auto& slot = m_Slots[slotIndex];
    if (!slot.hasData) return;

    for (int i = 0; i < 12; i++)
    {
        PED::SET_PED_COMPONENT_VARIATION(ped, i, slot.data.drawable[i], slot.data.drawableTex[i], 0);
    }
}

void Wardrobe::SaveSlot(int slotIndex)
{
    SaveOutfitToSlot(slotIndex);
}

void Wardrobe::ApplySlot(int slotIndex)
{
    ApplyOutfitToSlot(slotIndex);
}

void Wardrobe::ClearSlot(int slotIndex)
{
    auto& slot = m_Slots[slotIndex];
    slot = WardrobeSlot{};
    MarkStateDirty();
}

const WardrobeSlot& Wardrobe::GetSlot(int index) const
{
    return m_Slots[index];
}

std::string Wardrobe::GetSlotName(int index) const
{
    return m_Slots[index].name;
}

void Wardrobe::SetSlotName(int index, const std::string& name)
{
    m_Slots[index].name = name;
    MarkStateDirty();
}

bool Wardrobe::HasSlotData(int index) const
{
    return m_Slots[index].hasData;
}

const char* Wardrobe::GetSerializerComponentName()
{
    return "wardrobe";
}

void Wardrobe::SaveStateImpl(nlohmann::json& value)
{
    for (int i = 0; i < 21; i++)
    {
        auto& slot = m_Slots[i];
        auto& slotJson = value[std::to_string(i)];
        slotJson["name"] = slot.name;
        slotJson["hasData"] = slot.hasData;
        
        if (slot.hasData)
        {
            for (int j = 0; j < 12; j++)
            {
                slotJson["drawable"][j] = slot.data.drawable[j];
                slotJson["drawableTex"][j] = slot.data.drawableTex[j];
            }
        }
    }
}

void Wardrobe::LoadStateImpl(nlohmann::json& value)
{
    for (int i = 0; i < 21; i++)
    {
        auto it = value.find(std::to_string(i));
        if (it == value.end() || !it->is_object()) continue;
        
        auto& slot = m_Slots[i];
        slot.name = it->value("name", std::string{});
        slot.hasData = it->value("hasData", false);
        
        if (slot.hasData)
        {
            for (int j = 0; j < 12; j++)
            {
                slot.data.drawable[j] = it->value("drawable", std::array<int, 12>{})[j];
                slot.data.drawableTex[j] = it->value("drawableTex", std::array<int, 12>{})[j];
            }
        }
    }
    MarkStateDirty();
}

}
