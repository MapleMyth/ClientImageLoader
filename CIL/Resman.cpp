#include "Resman.h"

typedef void*(__fastcall* CWvsApp__InitializeResMan_t)(void*, void*, void*);
typedef void*(__fastcall* Ztl_bstr_t)(void*, void*, void*);

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

BOOL Hook_InitializeResMan(BOOL bEnable) {

	static auto CWvsApp__InitializeResMan = reinterpret_cast<CWvsApp__InitializeResMan_t>(0x008E7BA0);
	static auto Ztl_bstr = reinterpret_cast<Ztl_bstr_t>(0x008E7C01);

	CWvsApp__InitializeResMan_t Hook = [](void* ecx, void* edx, void* cwvsapp) -> void* {

		auto g_rm = get_rm();

		// Create Resource Manager Instance.
		PcCreateObject_IWzResMan((void*)L"ResMan", g_rm);

		void* pIWzResMan_Instance = _com_IWzResMan_arrow(g_rm, nullptr);
		IWzResMan__SetResManParam(pIWzResMan_Instance, nullptr, RC_AUTO_REPARSE | RC_AUTO_SERIALIZE, -1, -1);

		// Create NameSpace Instance.
		auto g_root = get_root();
		PcCreateObject_IWzNameSpace((void*)L"NameSpace", g_root);

		void* pIWzNameSpace_Instance = _com_IWzNameSpace_deref(g_root, nullptr);
		PcSetRootNameSpace(pIWzNameSpace_Instance); // PcSetRootNameSpace(*((void**)g_root));

													// Create FileSystem Instance
		int pIWzFileSystem;
		void* com_iwfsp = _com_IWzFileSystem_ptr(&pIWzFileSystem, nullptr);
		PcCreateObject_IWzFileSystem((void*)L"NameSpace#FileSystem", com_iwfsp);

		// Initialize FileSystem
		char sStartPath[MAX_PATH];
		GetModuleFileNameA(NULL, sStartPath, MAX_PATH);
		CWvsApp__Dir_BackSlashToSlash(sStartPath);
		CWvsApp__Dir_upDir(sStartPath);

		printf("Path: %s\n", sStartPath);

		Ztl_bstr_t* p_bstr_data = new Ztl_bstr_t();
		ztl_bstr_constructor(p_bstr_data, nullptr, sStartPath);

		void* pIWzFileSystem_Idek = _com_IWzFileSystem_arrow(&pIWzFileSystem, nullptr);
		auto iahefauf = IWzFileSystem__Init(pIWzFileSystem_Idek, nullptr, *p_bstr_data);

		// Mount time OwO
		// bms does some checks, but who cares about that
		void* ppRoot = _com_IWzNameSpace_arrow(g_root, nullptr); // *((void**)g_root)
		Ztl_bstr_t* p_bstr_path = new Ztl_bstr_t();
		void* p_down;

		ztl_bstr_constructor(p_bstr_path, nullptr, (const char*)"/");
		p_down = _com_IWzPackage_deref(&pIWzFileSystem, nullptr);

		auto ajefgeaf = IWZNameSpace__Mount(ppRoot, nullptr, *p_bstr_path, p_down, 0);

		// Create FileSystem Instance
		int pDataFileSystem;
		void* com_iwdsp = _com_IWzFileSystem_ptr(&pDataFileSystem, nullptr);
		PcCreateObject_IWzFileSystem((void*)L"NameSpace#FileSystem", com_iwdsp);

		Ztl_bstr_t* pDataStr = new Ztl_bstr_t();
		ztl_bstr_constructor(pDataStr, nullptr, "./Data");

		void* pDataArrow = _com_IWzFileSystem_arrow(&pDataFileSystem, nullptr);
		auto fsinitret = IWzFileSystem__Init(pDataArrow, nullptr, *pDataStr);

		p_down = _com_IWzPackage_deref(&pDataFileSystem, nullptr);
		p_bstr_path = new Ztl_bstr_t();
		ztl_bstr_constructor(p_bstr_path, nullptr, (const char*)"/");
		ppRoot = _com_IWzNameSpace_arrow(get_root(), nullptr); // *((void**)g_root)
		auto ejhafaf = IWZNameSpace__Mount(ppRoot, nullptr, *p_bstr_path, p_down, 0);

		return (void*)0;
	};


	return SetHook(bEnable, reinterpret_cast<void**>(&CWvsApp__InitializeResMan), Hook);
}

VOID * get_rm()
{
	return (void*)0;
}

VOID * get_root()
{
	return (void*)0;
}

VOID * PcCreateObject_IWzResMan(void *, void *)
{
	return (void*)0;
}

VOID * _com_IWzResMan_arrow(void *, void *)
{
	return (void*)0;
}

VOID * _com_IWzFileSystem_arrow(int *, void *)
{
	return (void*)0;
}

VOID * IWzResMan__SetResManParam(void *, void *, int a, int b, int c)
{
	return (void*)0;
}

VOID * PcCreateObject_IWzNameSpace(void *, void *)
{
	return (void*)0;
}

VOID * _com_IWzNameSpace_deref(void *, void *)
{
	return (void*)0;
}

VOID * PcSetRootNameSpace(void *)
{
	return (void*)0;
}

VOID * _com_IWzFileSystem_ptr(int *, void *)
{
	return (void*)0;
}

VOID * PcCreateObject_IWzFileSystem(void *, void *)
{
	return (void*)0;
}

VOID * CWvsApp__Dir_BackSlashToSlash(char *)
{
	return (void*)0;
}

VOID * CWvsApp__Dir_upDir(char *)
{
	return (void*)0;
}

VOID * IWzFileSystem__Init(void *, void *, void *)
{
	return (void*)0;
}

VOID * ztl_bstr_constructor(void *, void *, const char *)
{
	return (void*)0;
}

VOID * _com_IWzNameSpace_arrow(void *, void *)
{
	return (void*)0;
}

VOID * _com_IWzPackage_deref(void *, void *)
{
	return (void*)0;
}

VOID * IWZNameSpace__Mount(void *, void *, void *, void *, int a)
{
	return (void*)0;
}
