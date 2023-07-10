#include "pch.h"
#include "CCameraFix.h"
#include "offsets.h"
#include "patterns.h"

CCameraFix::CCameraFix()
    : CFeature("Camera Fix", CHotkey(), Tab::Visuals, true)
{
    BYTE *pbase = reinterpret_cast<BYTE *>(
        memory::fnFindPatternIDA(0x00000000, 0x10000000, patterns::cameraRotateLimit.c_str()));

    m_pUp = reinterpret_cast<float *>(pbase + 0x24);
    m_pUpEbx = reinterpret_cast<float *>(pbase + 0x02);
    m_pDown = reinterpret_cast<float *>(pbase - 0x0E);
    m_pDownEbx = reinterpret_cast<float *>(pbase - 0x30);

    if (m_bIsEnabled)
    {
        fnEnable();
    }
}

void CCameraFix::fnEnable()
{
    CFeature::fnEnable();
    *m_pUp = *m_pUpEbx = -90.0f;
    *m_pDown = *m_pDownEbx = 90.0f;
}

void CCameraFix::fnDisable()
{
    CFeature::fnDisable();
    *m_pUp = *m_pUpEbx = -70.0f;
    *m_pDown = *m_pDownEbx = 70.0f;
}
