#include "pch.h"
#include "CWireframe.h"

CWireframe::CWireframe(CHotkey COHotkey) :
    CFeature("Wireframe", COHotkey, Tab::Visuals)
{

}

void CWireframe::fnEnable()
{
    CFeature::fnEnable();

    int iTemp = *SDK::g_piGammaUpdate;

    if (iTemp) *SDK::g_piGammaUpdate = 0;

    *SDK::g_piWireframe = 1;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    if (iTemp) *SDK::g_piGammaUpdate = 1;
}

void CWireframe::fnDisable()
{
    CFeature::fnDisable();

    int iTemp = *SDK::g_piGammaUpdate;

    if (iTemp) *SDK::g_piGammaUpdate = 0;

    *SDK::g_piWireframe = 0;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    if (iTemp) *SDK::g_piGammaUpdate = 1;
}
