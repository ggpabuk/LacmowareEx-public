#pragma once

#include "CFeature.h"
#include "CHotkey.h"
#include "freezeManager.h"
#include "sdk.h"
#include "memory.h"
#include "patterns.h"

class CForceVoice :
    public CFeature
{
private:
    DWORD *m_pdwVoicechatUpdate;
    BYTE m_aBuffer1[7];
public:
    CForceVoice(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
};
