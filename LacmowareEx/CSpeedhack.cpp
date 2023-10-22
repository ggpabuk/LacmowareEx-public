#include "pch.h"
#include "CSpeedhack.h"

CSpeedhack::CSpeedhack(CHotkey COHotkey) :
    CFeature("Speedhack", COHotkey, Tab::Movement)
{
    m_speed = 0.1;
}

void CSpeedhack::fnEnable()
{
    CFeature::fnEnable();
    freezeManager::floatFreezes.insert(std::pair(&SDK::pCOPlayerStats->CurrentSpeed, m_speed));
}

void CSpeedhack::fnDisable()
{
    CFeature::fnDisable();

    freezeManager::floatFreezesMutex.lock();
    freezeManager::floatFreezes.erase(freezeManager::floatFreezes.find(&SDK::pCOPlayerStats->CurrentSpeed));
    freezeManager::floatFreezesMutex.unlock();
}

void CSpeedhack::fnDraw(unsigned int &uElementId)
{
    CFeature::fnDraw(uElementId);
  
    float speed = m_speed;
    ImGui::SliderFloat("Speed", &speed, 0.01, 0.3);

    if (speed != m_speed)
    {
        fnReload();
    }

    m_speed = speed;
}
