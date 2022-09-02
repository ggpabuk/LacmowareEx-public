#pragma once

#include "CFeature.h"
#include "offsets.h"
#include "memory.h"
#include "patterns.h"

class CBypassKeycodes :
    public CFeature
{
private:
    BYTE m_aBuffer1[6];
    DWORD *m_pdwKeycodeValidation;
public:
    CBypassKeycodes(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
};
