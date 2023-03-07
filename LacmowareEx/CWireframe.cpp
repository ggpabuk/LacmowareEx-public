#include "pch.h"
#include "CWireframe.h"

CWireframe::CWireframe(CHotkey COHotkey) :
    CFeature("Wireframe", COHotkey, Tab::Visuals)
{

}

void CWireframe::fnEnable()
{
    CFeature::fnEnable();

    int iTemp = SDK::pCOSettings->m_gammaUpdateDisabled;

    if (iTemp) SDK::pCOSettings->m_gammaUpdateDisabled = 0;

    *SDK::piWireframe = 1;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    if (iTemp) SDK::pCOSettings->m_gammaUpdateDisabled = 1;
}

void CWireframe::fnDisable()
{
    CFeature::fnDisable();

    int iTemp = SDK::pCOSettings->m_gammaUpdateDisabled;

    if (iTemp) SDK::pCOSettings->m_gammaUpdateDisabled = 0;

    *SDK::piWireframe = 0;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    if (iTemp) SDK::pCOSettings->m_gammaUpdateDisabled = 1;
}
