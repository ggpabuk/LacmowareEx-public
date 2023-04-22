#include "pch.h"
#include "CRpc.h"
#include "sdk.h"
#include "breachType.h"

void CRpc::InitRpc()
{
    DiscordEventHandlers handlers = { 0 };
    Discord_Initialize(APPLICATION_ID, &handlers, 1, nullptr);
}

void CRpc::BeginUpdateRpc()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        if (m_clearRpc)
        {
            Discord_ClearPresence();
            m_clearRpc = false;
        }

        if (!m_bIsEnabled)
        {
            continue;
        }

        DiscordRichPresence rpc = { 0 };

        rpc.details = "Open SCP:CBM DLC: t.me/femboyhips";

        if (*SDK::pppCOServerInfo && **SDK::pppCOServerInfo &&
            SDK::pCOPlayerList && SDK::pCOPlayerList->fnIsPlayerValid())
        {
            CServerInfo *pServerInfo = **SDK::pppCOServerInfo;
            CPlayer *pPlayer = *SDK::pCOPlayerList->m_COplayer;

            rpc.partyId = "ggpabuk"; // any
            rpc.partySize = pServerInfo->PlayersCount;
            rpc.partyMax = pServerInfo->MaxPlayers;

            rpc.state = g_breachType[pPlayer->m_breachType];

            rpc.largeImageKey = "ingame";
            rpc.largeImageText = "ggpabuk's fan";
        }
        else
        {
            rpc.state = "Enjoying loading screen";

            rpc.largeImageKey = "chill";
            rpc.largeImageText = "thelifeworm's fan";
        }

        Discord_UpdatePresence(&rpc);
    }
}

CRpc::CRpc(CHotkey COHotkey) :
    CFeature("Discord RPC", COHotkey, Tab::Fun, true)
{
    m_clearRpc = false;

    InitRpc();
    std::thread([&]() { BeginUpdateRpc(); }).detach();
}

void CRpc::fnEnable()
{
    CFeature::fnEnable();
}

void CRpc::fnDisable()
{
    CFeature::fnDisable();
    m_clearRpc = true;
}
