//
// Demonstration on how to call custom 3ds Max notifications in C++.
// Works with 3ds Max 2019 and above.
// (c) 2019 Wesley Hill
//

#pragma once

#include "Max.h"

#include "istdplug.h"
#include "iparamb2.h"
#include "iparamm2.h"
#include "resource.h"
#include <maxtypes.h>
#include <utilapi.h>
#include <set>

extern HINSTANCE hInstance;
extern TCHAR *GetString(int id);

class Example : public UtilityObj
{
public:
	Example() { }
	virtual ~Example() { }
	virtual void DeleteThis() { }
	static void ForceUnregister();
	static void Unregister();
	static void Broadcast();
	static void Register();
	virtual void BeginEditParams(Interface *ip, IUtil *iu);
	virtual void EndEditParams(Interface *ip, IUtil *iu);

	enum CustomNotificationCode {
		Custom1 = 4098, // 0x00001002
		Custom2 = 4099, // 0x00001003
		Custom3 = 4100, // 0x00001004
		Custom4 = 4101, // 0x00001005
		Custom5 = 4102, // 0x00001006
		Custom6 = 4103, // 0x00001007
		Custom7 = 4104, // 0x00001008
	};

	void InitDialog();
	static INT_PTR DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	Interface *ip;
	HWND   hPanel;
};

static Example ex;
static std::set<int> registeredCodes;

class ExampleClassDesc : public ClassDesc2
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL) 						{ return &ex; }
	virtual const TCHAR *	ClassName() 			{ return L"Custom Notifications Demo"; }
	virtual SClass_ID SuperClassID() 				{ return UTILITY_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return Class_ID(0x6a287c04, 0x76533d12); }
	virtual const TCHAR* Category() 				{ return L"CustomNotificationsDemo"; }
	virtual const TCHAR* InternalName() 			{ return L"CustomNotificationsDemo"; }
	virtual HINSTANCE HInstance() 					{ return hInstance; }
};
