#include "pch.h"
#include "CServerInfo.h"

bool CServerInfo::isProtected()
{
    return MyID != 0 &&
        IP == -1;
}
