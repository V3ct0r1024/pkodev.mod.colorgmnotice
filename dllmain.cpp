#include <Windows.h>
#include <detours.h>

#include <string>
#include <regex>

#include "loader.h"

#include "address.h"
#include "pointer.h"
#include "hook.h"
#include "structure.h"


// Entry point
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    // Nothing to do . . .
    return TRUE;
}

// Get mod information
void GetModInformation(mod_info& info)
{
    strcpy_s(info.name, TOSTRING(MOD_NAME));
    strcpy_s(info.version, TOSTRING(MOD_VERSION));
    strcpy_s(info.author, TOSTRING(MOD_AUTHOR));
    info.exe_version = MOD_EXE_VERSION;
}

// Start the mod
void Start(const char* path)
{
    // Enable hooks
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)pkodev::pointer::CGameApp__ShowNotify, pkodev::hook::CGameApp__ShowNotify);
    DetourTransactionCommit();
}

// Stop the mod
void Stop()
{
    // Disable hooks
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)pkodev::pointer::CGameApp__ShowNotify, pkodev::hook::CGameApp__ShowNotify);
    DetourTransactionCommit();
}

// void CGameApp::ShowNotify( const char *szStr, DWORD dwColor )
void __fastcall pkodev::hook::CGameApp__ShowNotify(void* This, void* NotUsed, 
    const char* szStr, unsigned int dwColor)
{
    // Regular expression for message color
    const std::regex base_regex{ "\\{color:\\s*([0-9A-Fa-f]{8})\\}" };

    // Message color
    unsigned int color = dwColor;

    // Convert const char * to std::string type
    std::string msg{ szStr };

    // Matched substrings collection
    std::smatch base_match;


    // Search the substring with color in the message
    if (std::regex_search(msg, base_match, base_regex) == true)
    {
        // We should have 2 string: original string and matched substring with the color
        if (base_match.size() == 2)
        {
            // Convert substring with color to unsigned int
            color = std::strtoul(base_match[1].str().c_str(), nullptr, 16);

            // Remove the substring with color from the message
            msg = std::regex_replace(msg, base_regex, "$2$3");
        }
    }

    // Call original method void CGameApp::ShowNotify( const char *szStr, DWORD dwColor )
    pkodev::pointer::CGameApp__ShowNotify(This, msg.c_str(), color);
}