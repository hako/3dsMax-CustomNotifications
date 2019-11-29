//
// Demonstration on how to call custom 3ds Max notifications in C++.
// Works with 3ds Max 2019 and above.
// (c) 2019 Wesley Hill
//

#include "Example.h"
#include <notify.h>
#include <string>

ClassDesc2* GetUtilitySampleDesc() {
	static ExampleClassDesc exampleDesc;
	return &exampleDesc;
}

void ShowMessage(const wchar_t* msg) {
	HWND sbHandle = GetDlgItem(GetActiveWindow(), IDC_STATUS_BAR);
	SetWindowTextW(sbHandle, msg);
}

int GetNotificationCode() {
	HWND cHandle = GetDlgItem(GetActiveWindow(), IDC_COMBOBOX);

	wchar_t textCode[256];
	LRESULT idx = SendMessageW(cHandle, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	SendMessageW(cHandle, (UINT)CB_GETLBTEXT, (WPARAM)idx, (LPARAM)textCode);

	std::wstring str = std::wstring(textCode);
	if (str.compare(L"Custom1") == 0) { return Example::Custom1; }
	if (str.compare(L"Custom2") == 0) { return Example::Custom2; }
	if (str.compare(L"Custom3") == 0) { return Example::Custom3; }
	if (str.compare(L"Custom4") == 0) { return Example::Custom4; }
	if (str.compare(L"Custom5") == 0) { return Example::Custom5; }
	if (str.compare(L"Custom6") == 0) { return Example::Custom6; }
	if (str.compare(L"Custom7") == 0) { return Example::Custom7; }

	return -1;
}

void Callback(void *param, NotifyInfo *info) {
	MessageBoxW(nullptr, L"Hello World!", L"Result", MB_ICONINFORMATION);
}

void Example::Register() {
	int code = GetNotificationCode();

	if (registeredCodes.count(code) == 1 && code != -1) {
		ShowMessage(L"Notification already registered.");
		return;
	}
	RegisterNotification(Callback, nullptr, code);
	ShowMessage(L"Notification registered.");
	registeredCodes.insert(code);
}

void Example::Broadcast() {
	int code = GetNotificationCode();
	if (code != -1) {
		BroadcastNotification(code);
	}
}

void Example::Unregister() {
	int code = GetNotificationCode();
	if (registeredCodes.count(code) == 1 && code != -1) {
		UnRegisterNotification(Callback, nullptr, code);
		ShowMessage(L"Notification unegistered.");
		registeredCodes.erase(code);
		return;
	}
	ShowMessage(L"Notification not registered.");
}

void Example::ForceUnregister() {
	if (!registeredCodes.empty()) {
		for (int code = Custom1; code <= Custom7; code++) {
			UnRegisterNotification(Callback, nullptr, code);
		}
		ShowMessage(L"Notifications forcibly unregistered.");
		registeredCodes.clear();
		return;
	}
	ShowMessage(L"Notifications not registered.");
}

void Example::BeginEditParams(Interface* ip, IUtil* iu) {
	this->ip = ip;
	ex.InitDialog();
}

void Example::EndEditParams(Interface* ip, IUtil* iu) {
	this->ip = nullptr;
}

void Example::InitDialog() {
	CreateDialogParamW(hInstance, MAKEINTRESOURCE(IDD_PANEL), ip->GetMAXHWnd(), DlgProc, (LPARAM)this);

	HWND cHandle = GetDlgItem(GetActiveWindow(), IDC_COMBOBOX);
	for (int i = 1; i <= 7; i++) {
		std::wstring checkBoxText = L"Custom" + std::to_wstring(i);
		SendMessageW(cHandle, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)checkBoxText.c_str());
	}
	SendMessageW(cHandle, (UINT)CB_SELECTSTRING, (WPARAM)0, (LPARAM)L"Custom1");
}

INT_PTR CALLBACK Example::DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		break;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BN:
			Example::Broadcast();
			break;

		case IDC_RN:
			Example::Register();
			break;

		case IDC_UN:
			Example::Unregister();
			break;

		case IDC_FUN:
			Example::ForceUnregister();
			break;
		}
		break;

	default:
		return FALSE;
	}
	return TRUE;
}