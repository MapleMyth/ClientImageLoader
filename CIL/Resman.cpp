#include "CIL.h"

enum RESMAN_PARAM {
	RC_AUTO_SERIALIZE = 0x1,
	RC_AUTO_SERIALIZE_NO_CACHE = 0x2,
	RC_NO_AUTO_SERIALIZE = 0x4,
	RC_DEFAULT_AUTO_SERIALIZE = 0x0,
	RC_AUTO_SERIALIZE_MASK = 0x7,
	RC_AUTO_REPARSE = 0x10,
	RC_NO_AUTO_REPARSE = 0x20,
	RC_DEFAULT_AUTO_REPARSE = 0x0,
	RC_AUTO_REPARSE_MASK = 0x30,
};

typedef void(__fastcall* CWvsApp__InitializeResMan_t)(void*);

// Function Address
auto CWvsApp__InitializeResMan = reinterpret_cast<CWvsApp__InitializeResMan_t>(0x000000);
auto PcCreateObject_IWzResMan = (void(__cdecl*)(void*, void*, void*))0x000000;
auto PcCreateObject_IWzNameSpace = (void(__cdecl*)(void*, void*, void*))0x000000;
auto PcCreateObject_IWzFileSystem = (void(__cdecl*)(void*, void*, void*))0x000000;
auto CWvsApp__Dir_BackSlashToSlash = (void(__cdecl*)(void*))0x000000;
auto CWvsApp__Dir_upDir = (void(__cdecl*)(void*))0x000000;
auto bstr_constructor = (void(__fastcall*)(void*, void*, void*))0x000000;
auto IWzFileSystem__Init = (void*(__fastcall*)(void*, void*, void*))0x000000;
auto IWZNameSpace__Mount = (void*(__fastcall*)(void*, void*, void*, void*, void*))0x000000;

// DWORD Address
auto g_rm = (void**)0x000000;
auto g_root = (void**)0x000000;
auto pNameSpace = (int*)0x000000;

// Disable Restrictions
#pragma optimize("", off)

BOOL Hook_InitializeResMan(BOOL bEnable) {

	CWvsApp__InitializeResMan_t Hook = [](void*) {

		// Generic
		void* pFileSystem = nullptr;
		void* pUnkOuter = 0;
		void* nPriority = 0;
		void* sPath;
		void* base = "./Data";

		// Resman
		PcCreateObject_IWzResMan(L"ResMan", g_rm, pUnkOuter);

		void* pIWzResMan_Instance = *g_rm;
		auto IWzResMan__SetResManParam = *(void(__cdecl**)(void*, int, int, int))((*(int*)pIWzResMan_Instance) + 20);
		IWzResMan__SetResManParam(pIWzResMan_Instance, RC_AUTO_REPARSE | RC_AUTO_SERIALIZE, -1, -1);

		// NameSpace
		PcCreateObject_IWzNameSpace(L"NameSpace", g_root, pUnkOuter);

		void* pIWzNameSpace_Instance = g_root;
		auto PcSetRootNameSpace = (void(__cdecl*)(void*, int))*pNameSpace;
		PcSetRootNameSpace(pIWzNameSpace_Instance, 1);

		// Game FileSystem
		PcCreateObject_IWzFileSystem(L"NameSpace#FileSystem", &pFileSystem, pUnkOuter);

		char sStartPath[MAX_PATH];
		GetModuleFileNameA(NULL, sStartPath, MAX_PATH);
		CWvsApp__Dir_BackSlashToSlash(sStartPath);
		CWvsApp__Dir_upDir(sStartPath);

		bstr_constructor(&sPath, nullptr, sStartPath);

		auto a = IWzFileSystem__Init(pFileSystem, nullptr, sPath);

		bstr_constructor(&sPath, nullptr, "/");

		auto b = IWZNameSpace__Mount(*g_root, nullptr, sPath, pFileSystem, nPriority);

		// Data FileSystem
		PcCreateObject_IWzFileSystem(L"NameSpace#FileSystem", &pFileSystem, pUnkOuter);

		bstr_constructor(&sPath, nullptr, base);

		auto c = IWzFileSystem__Init(pFileSystem, nullptr, sPath);

		bstr_constructor(&sPath, nullptr, "/");

		auto d = IWZNameSpace__Mount(*g_root, nullptr, sPath, pFileSystem, nPriority);
	};

	return SetHook(bEnable, reinterpret_cast<void**>(&CWvsApp__InitializeResMan), Hook);
}

// Enable Restrictions
#pragma optimize("", on)
