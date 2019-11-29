//
// Demonstration on how to call custom 3ds Max notifications in C++.
// Works with 3ds Max 2019 and above.
// (c) 2019 Wesley Hill
//

#include "Example.h"

extern ClassDesc2* GetUtilitySampleDesc();

HINSTANCE hInstance;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, ULONG fdwReason, LPVOID)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		hInstance = hinstDLL;
		DisableThreadLibraryCalls(hInstance);
	}
	return(TRUE);
}

__declspec(dllexport) int LibNumberClasses()
{
	return 1;
}

__declspec(dllexport) ULONG LibVersion()
{
	return VERSION_3DSMAX;
}

__declspec(dllexport) const TCHAR* LibDescription()
{
	return L"Demonstration on how to call custom 3ds Max notifications in C++ (Autodesk 3DS Max 2019 and up).";
}

__declspec(dllexport) ClassDesc* LibClassDesc(int i)
{
	switch (i) {
	case 0: return GetUtilitySampleDesc();
	default: return 0;
	}
}

TCHAR *GetString(int id)
{
	static TCHAR buf[256];

	if (hInstance)
		return LoadString(hInstance, id, buf, _countof(buf)) ? buf : nullptr;
	return nullptr;
}
