#pragma once

#include "CFeature.h"
#include "freezeManager.h"
#include "sdk.h"

class CInfAmmo :
    public CFeature
{
public:
    CInfAmmo(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
};
