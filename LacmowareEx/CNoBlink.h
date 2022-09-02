#pragma once

#include "CFeature.h"
#include "freezeManager.h"
#include "sdk.h"

class CNoBlink :
    public CFeature
{
public:
    CNoBlink(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
};
