#include "pch.h"
#include "CServerInfo.h"

bool CServerInfo::isProtected()
{
    return MyID != 0 &&
        IP == 0x51138d05; // 81.19.141.5
}
