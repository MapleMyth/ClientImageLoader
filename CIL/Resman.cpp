#include "CIL.h"

#pragma optimize("", off)
typedef void(__fastcall* CWvsApp__InitializeResMan_t)(void*);
auto PcCreateObject_IWzResMan = (void(__cdecl*) (const wchar_t*, void*, void*))0x9FAF55;
auto PcCreateObject_IWzNameSpace = (void(__cdecl*) (const wchar_t*, void*, void*))0x9FAFBA;
auto PcCreateObject_IWzFileSystem = (void(__cdecl*) (const wchar_t*, void*, void*))0x9FB01F;
auto CWvsApp__Dir_BackSlashToSlash = (int(__cdecl*)(char*))0x9F95FE;
auto CWvsApp__Dir_upDir = (size_t(__cdecl*)(char*))0x9F9644;
auto bstr_constructor = (int(__fastcall*)(void* ecx, void* edx, char* str))0x406301;
auto IWzFileSystem__Init = (HRESULT(__fastcall*)(void* ecx, void* edx, void* sPath))0x9F7964;
auto IWZNameSpace__Mount = (int(__fastcall*)(void*, void*, void*, void*, int))0x9F790A;

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

struct CWvsApp
{
	/*Nothing for now*/
};


BOOL Hook_InitializeResMan(BOOL bEnable) {

	static auto CWvsApp__InitializeResMan = reinterpret_cast<CWvsApp__InitializeResMan_t>(0x9F7159);

	CWvsApp__InitializeResMan_t initresman = [](void* CWvsApp) -> void {

		auto g_rm = (void**)0xBF14E8;

		// Create Resource Manager Instance.
		PcCreateObject_IWzResMan(L"ResMan", (void*)g_rm, 0);

		void* pIWzResMan_Instance = *g_rm;
		auto IWzResMan__SetResManParam = *(int(__stdcall **)(int, signed int, signed int, signed int))((*(int*)pIWzResMan_Instance) + 20);
		IWzResMan__SetResManParam((int)pIWzResMan_Instance, RC_AUTO_REPARSE | RC_AUTO_SERIALIZE, -1, -1);

		// Create NameSpace Instance.
		auto g_root = (void**)0xBF14E0;
		PcCreateObject_IWzNameSpace(L"NameSpace", g_root, 0);

		void* pIWzNameSpace_Instance = *g_root;
		auto PcSetRootNameSpace = *(int(__cdecl**)(DWORD, DWORD))0xBF0CD0;
		PcSetRootNameSpace((DWORD)g_root, 1);

		// Create FileSystem Instance
		void* pIWzFileSystem = 0;
		PcCreateObject_IWzFileSystem(L"NameSpace#FileSystem", &pIWzFileSystem, 0);

		// Initialize FileSystem
		char sStartPath[MAX_PATH];
		GetModuleFileNameA(NULL, sStartPath, MAX_PATH);
		CWvsApp__Dir_BackSlashToSlash(sStartPath);
		CWvsApp__Dir_upDir(sStartPath);

		void* p_bstr_data;
		bstr_constructor(&p_bstr_data, nullptr, sStartPath);

		wprintf(L"p_bstr_data: %ws\r\n", *(wchar_t**)p_bstr_data);

		auto iahefauf = IWzFileSystem__Init((void*)pIWzFileSystem, nullptr, p_bstr_data);

		// Mount time OwO
		void* p_bstr_path;
		void* p_down;

		bstr_constructor(&p_bstr_path, nullptr, "/");
		p_down = pIWzFileSystem;

		auto ajefgeaf = IWZNameSpace__Mount(*g_root, nullptr, p_bstr_path, (void*)pIWzFileSystem, 0);

		// Create FileSystem Instance
		void* pDataFileSystem = nullptr;
		PcCreateObject_IWzFileSystem(L"NameSpace#FileSystem", &pDataFileSystem, 0);

		void* pDataStr;
		bstr_constructor(&pDataStr, nullptr, "./Data");

		auto fsinitret = IWzFileSystem__Init(pDataFileSystem, nullptr, pDataStr);

		p_down = pDataFileSystem;
		bstr_constructor(&p_bstr_path, nullptr, "/");
		auto ejhafaf = IWZNameSpace__Mount(*g_root, nullptr, p_bstr_path, p_down, 0);

	};

	return SetHook(bEnable, reinterpret_cast<void**>(&CWvsApp__InitializeResMan), initresman);
}
#pragma optimize("", on)