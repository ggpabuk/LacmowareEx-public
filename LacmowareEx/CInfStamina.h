#pragma once

#include "CFeature.h"
#include "memory.h"
#include "patterns.h"
#include "freezeManager.h"
#include "sdk.h"

class CInfStamina :
    public CFeature
{
public:
    CInfStamina(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
};
