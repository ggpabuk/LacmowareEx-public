#include "pch.h"
#include "CPlayerListElement.h"

bool CPlayerListElement::fnIsPlayerValid()
{
    return m_COplayer &&
        *m_COplayer &&
        memory::fnIsMemoryReadable(&(*m_COplayer)->Id, sizeof((*m_COplayer)->Id));
}

CPlayerListElement *CPlayerListElement::fnGetNext()
{
    return reinterpret_cast<CPlayerListElement*>(*reinterpret_cast<DWORD*>(this) + 0x04);
}
