#pragma once
#include "CFeature.h"

class CFakeMove :
    public CFeature
{
private:
    DWORD *m_pTarget;
    DWORD m_original;

    int m_moveType;

public:
    CFakeMove();

    void fnDraw(unsigned int &uElementId) override;
    void fnEnable() override;
    void fnDisable() override;
};
