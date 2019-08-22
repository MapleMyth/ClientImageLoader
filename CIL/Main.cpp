#include "APIDummy.h"
#include "CIL.h"
#include <stdio.h>
#include <intrin.h>

VOID WINAPI ShowConsole()
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());

	freopen("CON", "w", stdout);

	char cc[128];
	sprintf_s(cc, "Client: %i", GetCurrentProcessId());
	SetConsoleTitleA(cc);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	DisableThreadLibraryCalls(hinstDLL);

	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		//ShowConsole(); //Uncomment for debugging.

		if (Hook_InitializeResMan(true)) {
			printf("Resman is hooked.\n");
		}

		return TRUE;
	}

	printf("Hook failed.\n");

	return FALSE;
}

DWORD GetFuncAddress(LPCSTR lpModule, LPCSTR lpFunc)
{
	auto mod = LoadLibraryA(lpModule);

	if (!mod)
	{
		return 0;
	}

	auto address = (DWORD)GetProcAddress(mod, lpFunc);

	printf(__FUNCTION__ " [%s] %s @ %8X\n", lpModule, lpFunc, address);

	return (DWORD)GetProcAddress(mod, lpFunc);
}

APIDummy::APIDummy() {

}