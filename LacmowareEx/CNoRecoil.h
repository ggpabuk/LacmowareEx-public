#pragma once

#include "CFeature.h"
#include "CGunsContainer.h"
#include "freezeManager.h"
#include "sdk.h"

class CNoRecoil :
    public CFeature
{
private:
    float m_aOldRecoil[13];
public:
    CNoRecoil(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
};
