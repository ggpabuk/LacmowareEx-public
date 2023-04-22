#pragma once

#define APPLICATION_ID "1099388509694996481"

#include "CFeature.h"

class CRpc :
    public CFeature
{
private:
    bool m_clearRpc;

    void InitRpc();
    void BeginUpdateRpc();
public:
    CRpc(CHotkey COHotkey);

    void fnEnable() override;
    void fnDisable() override;
};
