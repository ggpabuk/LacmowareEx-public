#pragma once

#include "CFeature.h"
#include "CHotkey.h"
#include "freezeManager.h"
#include "sdk.h"

class CSpeedhack :
    public CFeature
{
private:
    float m_speed;
public:
    CSpeedhack(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
    void fnDraw(unsigned int &uElementId) override;
};
