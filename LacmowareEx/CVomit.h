#pragma once

#include "CFeature.h"
#include "CHotkey.h"
#include "freezeManager.h"
#include "sdk.h"

class CVomit :
    public CFeature
{
public:
    CVomit(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
};
