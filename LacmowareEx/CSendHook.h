#pragma once
#include <winsock2.h>
#include <map>
#include <functional>
#include "Network.h"

typedef int (WINAPI *pSendTo_t)(SOCKET s, const char *buf, int len, int flags, const sockaddr *to, int tolen);

class CSendHook
{
private:
    static std::map<Network, std::vector<Modifer_t>> m_packetModifiers;
    static int WINAPI hkSendto(SOCKET s, const char *buf, int len, int flags, const sockaddr *to, int tolen);
public:
    static char m_lastPlayerId;
    static SOCKET m_lastSocket;
    static const sockaddr *m_lastTo;
    static int m_lastTolen;
    static pSendTo_t m_oSendto;
    
    static void enable();
    static void disable();
    static void addPacketModifier(Network packetId, Modifer_t modifierFunction);
};
