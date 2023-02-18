#pragma once

#include <Windows.h>

class CServerInfo
{
public:
    bool isProtected();

    UINT  Stream;
    int   IP;
    int   Port;
    int   ServerTimeout;
    int   Timeout;
    float EventProb;
    UINT  IPs;
    UINT  Ports;
    int   TcpStream;
    BYTE  pad_0001[0x04];
    float JumpHeight;
    int   JumpMode;
    BYTE  pad_0002[0x08];
    int   MaxPlayers;
    int   Breach;
    int   BreachTime;
    int   BreachLight;
    int   MainPlayer;
    int   Tickrate;
    UINT  Password;
    UINT  ServerName;
    UINT  EntitiesLoaded;
    int   KeepItems;
    int   HaveVoice;
    int   SeeNames;
    int   CheckVoice;
    int   ChatOpen;
    int   MyID;
    int   PlayersCount;
    int   VoiceRate;
};
