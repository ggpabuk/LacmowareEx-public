#pragma once
#include <winsock2.h>
#include <map>
#include <functional>
#include "Network.h"

typedef int (WSAAPI *recvfrom_t)(SOCKET s, char *buf, int len, int flags, sockaddr *from, int *fromlen);

class CRecvHook
{
private:
    static LPVOID m_target;
    static std::map<Network, std::vector<Modifer_t>> m_packetModifiers;
    static int WSAAPI hkRecvfrom(SOCKET s, char *buf, int len, int flags, sockaddr *from, int *fromlen);
public:
    static SOCKET m_lastSocket;
    static const sockaddr *m_lastFrom;
    static int m_lastFromlen;
    static recvfrom_t m_oRecvfrom;

    static void enable();
    static void disable();
    static void addPacketModifier(Network packetId, Modifer_t modifierFunction);
};
