#include "pch.h"
#include "CFovChanger.h"

CFovChanger::CFovChanger(CHotkey COHotkey) :
    CFeature("Fov", COHotkey, Tab::Visuals)
{
    m_fov = SDK::pCOSettings->m_fov;
}

void CFovChanger::fnEnable()
{
    CFeature::fnEnable();
    
    m_oldFov = SDK::pCOSettings->m_fov;
    freezeManager::floatFreezes.insert(std::pair(&SDK::pCOSettings->m_fov, m_fov));
}

void CFovChanger::fnDisable()
{
    CFeature::fnDisable();

    freezeManager::floatFreezesMutex.lock();
    freezeManager::floatFreezes.erase(freezeManager::floatFreezes.find(&SDK::pCOSettings->m_fov));
    freezeManager::floatFreezesMutex.unlock();

    SDK::pCOSettings->m_fov = m_oldFov;
}

void CFovChanger::fnDraw(unsigned int &uElementId)
{
    CFeature::fnDraw(uElementId);
    if (ImGui::SliderFloat("Fov", &m_fov, 10.0, 180.0))
    {
        fnReload();
    }
}
