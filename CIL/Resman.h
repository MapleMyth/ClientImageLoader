#pragma once
#include "CIL.h"

VOID* get_rm();
VOID* get_root();
VOID* PcCreateObject_IWzResMan(void*, void*);
VOID* _com_IWzResMan_arrow(void*, void*);
VOID* _com_IWzFileSystem_arrow(int*, void*);
VOID* IWzResMan__SetResManParam(void*, void*, int a, int b, int c);
VOID* PcCreateObject_IWzNameSpace(void*, void*);
VOID* _com_IWzNameSpace_deref(void*, void*);
VOID* PcSetRootNameSpace(void*);
VOID* _com_IWzFileSystem_ptr(int*, void*);
VOID* PcCreateObject_IWzFileSystem(void*, void*);
VOID* CWvsApp__Dir_BackSlashToSlash(char*);
VOID* CWvsApp__Dir_upDir(char*);
VOID* IWzFileSystem__Init(void*, void*, void*);
VOID* ztl_bstr_constructor(void*, void*, const char*);
VOID* _com_IWzNameSpace_arrow(void*, void*);
VOID* _com_IWzPackage_deref(void*, void*);
VOID* IWZNameSpace__Mount(void*, void*, void*, void*, int a);
VOID* p_bstr_data;
VOID* p_bstr_path;