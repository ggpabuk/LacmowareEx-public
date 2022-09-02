#pragma once

#include "CFeature.h"
#include "patterns.h"
#include "memory.h"

class CWallhack :
    public CFeature
{
private:
    BYTE m_aBuffer1[6];
    BYTE m_aBuffer2[6];
    DWORD m_dwAddress;
public:
    CWallhack(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
};
