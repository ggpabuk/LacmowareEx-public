#pragma once

#include "CFeature.h"
#include "offsets.h"
#include "memory.h"
#include "patterns.h"
#include "freezeManager.h"
#include "sdk.h"

class CNoclip
    : public CFeature
{
private:
    float m_noclipSpeed;
public:
    static CNoclip *m_pCOInstance;

    CNoclip(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
    void fnDraw(unsigned int &uElementId) override;
};
