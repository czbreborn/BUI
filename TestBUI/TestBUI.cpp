#pragma once
#include "stdafx.h"

class TestWindow : public BUIWindow
{
public:
	TestWindow() {}
	LPCTSTR GetWindowClassName() const { return _T("TestWindow"); }
};

int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	BProcessResources::GetInstance()->SetProcessInstance(hinst);
	BProcessResources::GetInstance()->SetResourcesPath(L"123");

	RECT rc;
	rc.left = 500;
	rc.right = 800;
	rc.top = 300;
	rc.bottom = 800;
	TestWindow* win = new TestWindow();
	win->Create(NULL, L"testbui", WS_OVERLAPPEDWINDOW, 0, rc);
	win->CenterWindow();
	win->ShowWindow(SW_SHOW);

	MSG msg = { 0 };
	while (::GetMessage(&msg, NULL, 0, 0)) 
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return 0;
}