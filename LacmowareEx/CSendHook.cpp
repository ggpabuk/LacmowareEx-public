#include "pch.h"
#include "CSendHook.h"

std::map<Network, std::vector<Modifer_t>> CSendHook::m_packetModifiers;
char CSendHook::m_lastPlayerId;
SOCKET CSendHook::m_lastSocket;
const sockaddr *CSendHook::m_lastTo;
int CSendHook::m_lastTolen;
pSendTo_t CSendHook::m_oSendto;

int __stdcall CSendHook::hkSendto(SOCKET s, const char *buf, int len, int flags, const sockaddr *to, int tolen)
{
    if (buf[0] == (char)Network::M_UPDATE) m_lastPlayerId = buf[1];

    m_lastSocket = s;
    m_lastTo = to;
    m_lastTolen = tolen;

    char *patchedbuf = new char[len];
    memcpy(patchedbuf, buf, len);
    auto pPacketId = reinterpret_cast<Network *>(patchedbuf);

    auto it = m_packetModifiers.find(*pPacketId);
    if (it != m_packetModifiers.end())
    {
        for (auto &modifier : it->second)
        {
            modifier(patchedbuf, len);
        }
    }

    int result = m_oSendto(s, patchedbuf, len, flags, to, tolen);

    delete[] patchedbuf;
    return result;
}

void CSendHook::enable()
{
    MH_CreateHook((LPVOID)::sendto, (LPVOID)CSendHook::hkSendto, (LPVOID *)&m_oSendto);
    MH_EnableHook((LPVOID)::sendto);
}

void CSendHook::disable()
{
    MH_DisableHook((LPVOID)::sendto);
}

void CSendHook::addPacketModifier(Network packetId, Modifer_t modifierFunction)
{
    m_packetModifiers[packetId].push_back(modifierFunction);
}
