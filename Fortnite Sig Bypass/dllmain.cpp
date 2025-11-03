#include <Windows.h>

using namespace std;

DWORD WINAPI Main(LPVOID)
{
    static auto Base = __int64(GetModuleHandleW(0));
    BYTE invalidpakBytes[6];
    ReadProcessMemory(GetCurrentProcess(), (LPCVOID)(Base + 0x499B19B), invalidpakBytes, 6, NULL);
    
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x499B19B), "\x90\x90\x90\x90\x90\x90", 6, NULL); // pak is invalid
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x34D8DC8 + 2), "\x00", 1, NULL); // failed to decrypt toc signature
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x34D1035 + 4), "\x00", 1, NULL); // missing signature
    Sleep(3500); // Restore bytes so it doesnt crash
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x499B19B), invalidpakBytes, 6, NULL); // pak is invalid
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x34D8DC8 + 2), "\x0C", 1, NULL); // failed to decrypt toc signature
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x34D1035 + 4), "\x0C", 1, NULL); // missing signature

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, Main, 0, 0, 0);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
