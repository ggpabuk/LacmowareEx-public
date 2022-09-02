#pragma once

#include <Windows.h>

class CServerInfo
{
public:
    UINT  Stream;
    int   IP;
    int   Port;
    int   ServerTimeout;
    int   Timeout;
    float EventProb;
    UINT  IPs;
    UINT  Ports;
    int   TcpStream;
    float JumpHeight;
    int   JumpMode;
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
