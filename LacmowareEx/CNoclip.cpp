#include "pch.h"
#include "CNoclip.h"

CNoclip *CNoclip::m_pCOInstance;

CNoclip::CNoclip(CHotkey COHotkey) :
    CFeature("Noclip", COHotkey, Tab::Movement)
{
    m_pCOInstance = this;
    m_noclipSpeed = 2.0;
}

void CNoclip::fnEnable()
{
    CFeature::fnEnable();

    SDK::pCOPlayerStats->Noclip = 1;

    freezeManager::floatFreezes.insert(std::pair(&SDK::pCOPlayerStats->NoclipSpeed, m_noclipSpeed));
}

void CNoclip::fnDisable()
{
    CFeature::fnDisable();

    SDK::pCOPlayerStats->Noclip = 0;

    freezeManager::floatFreezesMutex.lock();
    freezeManager::floatFreezes.erase(freezeManager::floatFreezes.find(&SDK::pCOPlayerStats->NoclipSpeed));
    freezeManager::floatFreezesMutex.unlock();
}

void CNoclip::fnDraw(unsigned int &uElementId)
{
    CFeature::fnDraw(uElementId);

    if (ImGui::SliderFloat("Noclip speed", &m_noclipSpeed, 1.0, 10.0))
    {
        fnReload();
    }
}
