#include <Windows.h>

using namespace std;

DWORD WINAPI Main(LPVOID)
{
    static auto Base = __int64(GetModuleHandleW(0));
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x107BE7E), "\x90\x90\x90\x90\x90\x90", 6, NULL); // pak is invalid
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x4734154), "\xC7\x03\x00\x00\x00\x00", 6, NULL); // failed to decrypt toc signature
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)(Base + 0x4734638), "\x41\xC7\x06\x00\x00\x00\x00", 7, NULL); // missing signature

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
