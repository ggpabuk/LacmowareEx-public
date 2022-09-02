#pragma once

#include "CFeature.h"
#include "CPlayerListElement.h"
#include "CPlayer.h"
#include "CServerInfo.h"
#include "CNoclip.h"
#include "sdk.h"

class CTeleportNext :
    public CFeature
{
private:
    int m_iCurrentPlayerNumber;
    CPlayerListElement *m_currentPlayerElement;
public:
    CTeleportNext(CHotkey COHotkey);

    void fnSelectFirstElement();
    bool fnTrySelectNext();
    void fnEnable() override;
};
