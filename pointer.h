#pragma once
#include "address.h"
#include "structure.h"

namespace pkodev
{
	namespace pointer
	{
		// void CGameApp::ShowNotify( const char *szStr, DWORD dwColor )
		typedef void(__thiscall* CGameApp__ShowNotify__Ptr)(void*, const char*, unsigned int);
		CGameApp__ShowNotify__Ptr CGameApp__ShowNotify = (CGameApp__ShowNotify__Ptr)(void*)(pkodev::address::MOD_EXE_VERSION::CGameApp__ShowNotify);
	}
}