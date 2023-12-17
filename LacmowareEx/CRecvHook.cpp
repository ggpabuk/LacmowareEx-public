#include "pch.h"
#include "CRecvHook.h"

LPVOID CRecvHook::m_target = 0;
std::map<Network, std::vector<Modifer_t>> CRecvHook::m_packetModifiers;
SOCKET CRecvHook::m_lastSocket;
const sockaddr *CRecvHook::m_lastFrom;
int CRecvHook::m_lastFromlen;
recvfrom_t CRecvHook::m_oRecvfrom;

int WSAAPI CRecvHook::hkRecvfrom(SOCKET s, char *buf, int len, int flags, sockaddr *from, int *fromlen)
{
	m_lastSocket = s;
	m_lastFrom = from;
	m_lastFromlen = *fromlen;

	int result = m_oRecvfrom(s, buf, len, flags, from, fromlen);
	auto pPacketId = reinterpret_cast<Network *>(buf);

	auto it = m_packetModifiers.find(*pPacketId);
	if (it != m_packetModifiers.end())
	{
		for (auto &modifier : it->second)
		{
			modifier(buf, len);
		}
	}

	return result;
}

void CRecvHook::enable()
{
	if (!m_target)
	{
		HMODULE hWsock32 = GetModuleHandleA("wsock32.dll");
		m_target = (LPVOID)GetProcAddress(hWsock32, "recvfrom");

		MH_CreateHook(m_target, (LPVOID)CRecvHook::hkRecvfrom, (LPVOID *)&m_oRecvfrom);
			
	}

	MH_EnableHook(m_target);
}

void CRecvHook::disable()
{
	MH_DisableHook(m_target);
}

void CRecvHook::addPacketModifier(Network packetId, Modifer_t modifierFunction)
{
	m_packetModifiers[packetId].push_back(modifierFunction);
}
