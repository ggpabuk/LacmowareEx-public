#pragma once

#include "CFeature.h"
#include "freezeManager.h"
#include "sdk.h"

class CFovChanger :
    public CFeature
{
private:
    float m_fov;
    float m_oldFov;
public:
    CFovChanger(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
    void fnDraw(unsigned int &uElementId) override;
};
