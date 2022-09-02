﻿#include "pch.h"
#include "dllmain.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        std::thread(fnInit).detach();
    }

    return TRUE;
}

void fnInit()
{
    srand(GetTickCount64());

#ifndef _DEBUG
    fnCreateConsole();
    SetConsoleTitle("LacmowareEx debug");
#endif // !_DEBUG

    SDK::fnInit();

    const HWND hWndConsole = GetConsoleWindow();
    SetWindowPos(
        hWndConsole,
        HWND_TOPMOST,
        NULL,
        NULL,
        NULL,
        NULL,
        SWP_NOMOVE | SWP_NOSIZE
    );

    freezeManager::fnInit();
    
    menuRenderer::init();
}

void fnCreateConsole()
{
    FILE *fDummy;

    AllocConsole();

    freopen_s(&fDummy, "conin$", "r", stdin);
    freopen_s(&fDummy, "conout$", "w", stdout);
    freopen_s(&fDummy, "conout$", "w", stderr);

    setlocale(LC_ALL, "");
}
