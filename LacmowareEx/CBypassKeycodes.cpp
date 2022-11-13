#include "pch.h"
#include "CBypassKeycodes.h"

CBypassKeycodes::CBypassKeycodes(CHotkey COHotkey) :
    CFeature("Bypass Keycodes", COHotkey, Tab::Fun)
{
    ZeroMemory(m_aBuffer1, LENGTH(m_aBuffer1));
    m_pdwKeycodeValidation = reinterpret_cast<DWORD *>(memory::fnFindPatternIDA(0x00000000, 0x10000000, patterns::keycodeValidation.c_str()) + 0xC3);
}

void CBypassKeycodes::fnEnable()
{
    CFeature::fnEnable();

    BYTE aBuffer[6] =
    {
        0xEB, 0x25,             // jmp 0x27 
        0x90, 0x90, 0x90, 0x90  // nop 4x
    };
    memory::fnReplaceWithBuffer(m_pdwKeycodeValidation, m_aBuffer1, aBuffer, LENGTH(aBuffer));
}

void CBypassKeycodes::fnDisable()
{
    CFeature::fnDisable();
    memcpy(m_pdwKeycodeValidation, m_aBuffer1, LENGTH(m_aBuffer1));
}
