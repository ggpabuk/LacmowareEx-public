#include "pch.h"
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

#ifdef _DEBUG
    fnCreateConsole();
    SetConsoleTitleA("LacmowareEx debug");
#endif // _DEBUG

    SDK::fnInit();
    freezeManager::fnInit();
    menuRenderer::start();
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
