#include "pch.h"
#include "CForceVoice.h"

CForceVoice::CForceVoice(CHotkey COHotkey) :
    CFeature("Force Voice", COHotkey, Tab::Fun)
{
    ZeroMemory(m_aBuffer1, LENGTH(m_aBuffer1));
    m_pdwVoicechatUpdate = reinterpret_cast<DWORD *>(memory::fnFindPatternIDA(0x00000000, 0x10000000, patterns::voicechatUpdate.c_str()) + 0x2B);
}

void CForceVoice::fnEnable()
{
    CFeature::fnEnable();
    
    BYTE aBuffer[7] =
    {
        0xC7, 0x00, 0x01, 0x00, 0x00, 0x00, // mov DWORD PTR [eax], 0x1
        0x90                                // nop
    };
    memory::fnReplaceWithBuffer(m_pdwVoicechatUpdate, m_aBuffer1, aBuffer, LENGTH(aBuffer));
}

void CForceVoice::fnDisable()
{
    CFeature::fnDisable();
    memcpy(m_pdwVoicechatUpdate, m_aBuffer1, LENGTH(m_aBuffer1));
}
