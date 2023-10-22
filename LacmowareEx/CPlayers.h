#pragma once

#include "CFeature.h"
#include "sdk.h"
#include "breachType.h"

class CPlayers :
    public CFeature
{
public:
    CPlayers();

    void fnDraw(unsigned int &uElementId) override;
};
