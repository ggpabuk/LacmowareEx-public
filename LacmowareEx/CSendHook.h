#pragma once
#include <winsock2.h>
#include <map>
#include <functional>

enum class PacketId : char
{
    M_UPDATE = 1,
    M_ONSERV = 2,
    M_SOUND = 3,
    M_SOUNDSTR = 4,
    M_DECAL = 5,
    M_START = 6,
    M_EXPL = 7,
    M_EVENTS = 8,
    M_ANNOUNC = 9,
    M_CRNPC = 10,
    M_CHAT = 11,
    M_ISLOAD = 12,
    M_DISCONNECT = 13,
    M_ROTATEENTITY = 14,
    M_KILL = 15,
    M_RESPAWN = 16,
    M_UNLOCKEXITS = 18,
    M_TAKEITEM = 21,
    M_FIXITEMS = 22,
    M_DOOR = 23,
    M_DROPITEM = 24,
    M_ELEVATOR = 25,
    M_CONNECT = 26,
    M_NEWCLIENT = 27,
    M_ADDBOT = 28,
    M_VOICE = 29,
    M_REMOVENPC = 30,
    M_SERVERUPD = 31,
    M_SERVERONSERV = 32,
    M_NEWROOM = 33,
    M_SERVERLIST = 35,
    M_SERVERPING = 36,
    M_FEMUR = 37,
    M_EVENT173 = 38,
    M_NPCS = 39,
    M_SERVERCLOSE = 40,
    M_STOPSOUND = 42,
    M_REMOVEITEM = 44,
    M_SHOOT = 46,
    M_BREACH = 47,
    M_SHOOT2 = 48,
    M_RESETBREACH = 49,
    M_SYNCDOOR = 50,
    M_REMOTEDOOR = 51,
    M_GETROLE = 52,
    M_KILL2 = 53,
    M_ANNOUNC2 = 55,
    M_GIVE = 57,
    M_REMOVEDOOR = 58,
    M_INFOITEM = 59,
    M_SERVERSYNC = 60,
    M_NPCSYNC = 61,
    M_SYNCTOSERVER = 62,
    M_CHATSYNC = 63,
    M_CREATENPC = 64,
    M_ITEMSYNC = 65,
    M_FIXEDITEMS = 66,
    M_PLAYERSYNC = 67,
    M_GETRAND = 68,
    M_GETRND = 69,
    M_CONNECTBOT = 70,
    M_CONNECTISFULL = 71,
    M_CONNECTISSTARTED = 72,
    M_CONNECTVERSION = 73,
    M_WANTROLE = 74,
    M_RESTARTSERVERBREACH = 75,
    M_BREACHEXPLOSION = 76,
    M_CONNECTNAME = 77,
    M_CONNECTBANIP = 78,
    M_RCONCOMMANDS = 79,
    M_ROCKETS = 80,
    M_CREATEROCKET = 81,
    M_096TRIGGERED = 82,
    M_EVENTSWRITE = 83,
    M_ROOMOBJECTS = 84,
    M_GETLOAD = 85,
    M_CONNECTPASSWORD = 86,
    M_WANTITEMS = 87,
    M_WANTDOORS = 88,
    M_WANTNPCS = 89,
    M_WANTEVENTS = 90,
    M_WANTOBJECTS = 91,
    M_WANTSERVERINFO = 92,
    M_OBJECTS = 93,
    M_DRAWS = 94,
    M_TEXTS = 95,
    M_SETPOS = 96,
    M_CONSOLE = 97,
    M_MSG = 98,
    M_LIGHT = 99,
    M_PING = 100,
    M_BANKDOWNLOAD = 101,
    M_SOUND3D = 102,
    M_EVENTQUERY = 103,
    m_miscellaneous = 104,
    M_FOGRANGE = 105,
    M_MOUSE = 106,
    M_CREATEBULLET = 107,
    M_GETPOS = 108,
    M_REQUESTPLAYERNAME = 109,
    M_NOTARGET = 110,
    M_REQUESTLOAD = 111,
    M_LOADDATA = 112,
    M_CONNECTERROR = 113,
    M_RAWPACKET = 114,
    M_LIFTSTATE = 115,
    M_CREATEGRENADE = 116,
    M_WARHEADS = 117,
    M_GLOBALBLINK = 118,
    M_GLOBALCONSOLE = 119,
    M_SAVEPOS = 120,
    M_PUTHANDCUFFS = 121,
};

typedef int (WINAPI *pSendTo_t)(SOCKET s, const char *buf, int len, int flags, const sockaddr *to, int tolen);
typedef std::function<void(char *, int)> Modifer_t;

class CSendHook
{
private:
    static std::map<PacketId, std::vector<Modifer_t>> m_packetModifiers;
    static int WINAPI hkSendto(SOCKET s, const char *buf, int len, int flags, const sockaddr *to, int tolen);
public:
    static char m_lastPlayerId;
    static SOCKET m_lastSocket;
    static const sockaddr *m_lastTo;
    static int m_lastTolen;
    static pSendTo_t m_oSendto;
    
    static void enable();
    static void disable();
    static void addPacketModifier(PacketId packetId, Modifer_t modifierFunction);
};
