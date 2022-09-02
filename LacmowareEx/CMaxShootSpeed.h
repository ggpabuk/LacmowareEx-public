#pragma once

#include "CFeature.h"
#include "CGun.h"
#include "freezeManager.h"
#include "sdk.h"

class CMaxShootSpeed :
    public CFeature
{
private:
    float m_aOldShootSpeed[13];
public:
    CMaxShootSpeed(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
};
