#include "pch.h"
#include "CPlayerListElement.h"

bool CPlayerListElement::fnIsPlayerValid()
{
    return m_COplayer && *m_COplayer &&
        memory::fnIsMemoryReadable(*m_COplayer, 1);
}

CPlayerListElement *CPlayerListElement::fnGetNext()
{
    return reinterpret_cast<CPlayerListElement*>(*reinterpret_cast<DWORD*>(this) + 0x04);
}
