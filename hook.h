#pragma once
#include "structure.h"

namespace pkodev
{
	namespace hook
	{
		// void CGameApp::ShowNotify( const char *szStr, DWORD dwColor )
		void __fastcall CGameApp__ShowNotify(void* This, void* NotUsed, const char* szStr, unsigned int dwColor);
	}
}