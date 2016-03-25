#pragma once
#include "stdafx.h"

class TestWindow : public BUIWindow
{
public:
	TestWindow() {}
	LPCTSTR GetWindowClassName() const { return _T("TestWindow"); }
	LPCTSTR GetWindowResource() const { return _T("test.xml"); }

	virtual LRESULT MessageRouting(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT ret = MessageDelegate(uMsg, wParam, lParam);
		if (ret != -1)
			return ret;

		ret = m_pUIManager->MessageRouting(uMsg, wParam, lParam);
		if (ret != -1)
			return ret;

		return BUIWindow::MessageRouting(uMsg, wParam, lParam);
	}
};

int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	BApplication::GetInstance()->SetProcessInstance(hinst);
	RECT rc;
	rc.left = 500;
	rc.right = 800;
	rc.top = 300;
	rc.bottom = 800;
	TestWindow* win = new TestWindow();
	win->Create(NULL, L"testbui", WS_OVERLAPPEDWINDOW, 0, rc);
	win->CenterWindow();
	win->ShowWindow(SW_SHOW);

	BApplication::GetInstance()->LoopMessage();

	return 0;
}