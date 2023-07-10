#pragma once

#include "CFeature.h"

class CCameraFix :
    public CFeature
{
private:
    float *m_pUp;
    float *m_pUpEbx;
    float *m_pDown;
    float *m_pDownEbx;
public:
    CCameraFix();

    void fnEnable() override;
    void fnDisable() override;
};
