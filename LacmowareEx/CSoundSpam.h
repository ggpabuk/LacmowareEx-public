#pragma once
#include "CFeature.h"

class CSoundSpam :
    public CFeature
{
public:
    CSoundSpam();

    void fnDraw(unsigned int &uElementId) override;

};
