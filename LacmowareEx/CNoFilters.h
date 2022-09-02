#pragma once

#include "CFeature.h"
#include "CHotkey.h"
#include "freezeManager.h"
#include "sdk.h"

class CNoFilters :
    public CFeature
{
private:
    float m_oldCameraFogNear;
    float m_oldCameraFogFar;
public:
    CNoFilters(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
};

