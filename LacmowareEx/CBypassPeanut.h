#pragma once

#include "CFeature.h"
#include "freezeManager.h"
#include "sdk.h"

class CBypassPeanut :
    public CFeature
{
public:
    CBypassPeanut(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
};
