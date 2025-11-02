#include <Windows.h>

using namespace std;

DWORD WINAPI Main(LPVOID)
{
    static auto Base = __int64(GetModuleHandleW(0));
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x4D75F88), "\x90\x90\x90\x90\x90\x90", 6, NULL); // pak is invalid
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x3838C78), "\xC7\x03\x00\x00\x00\x00", 6, NULL); // missing signature
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x383048A), "\x41\xC7\x04\x24\x00\x00\x00\x00", 8, NULL); // missing signature
    Sleep(3500); // Restore bytes before loading screen or else it crashes
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x4D75F88), "\x0F\x84\x39\x09\x00\x00", 6, NULL); // pak is invalid
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x3838C78), "\xC7\x03\x0C\x00\x00\x00", 6, NULL); // missing signature
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x383048A), "\x41\xC7\x04\x24\x0C\x00\x00\x00", 8, NULL); // missing signature

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
