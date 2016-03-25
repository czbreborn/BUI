#include "stdafx.h"

namespace BUI{
	BUIWindow::BUIWindow()
		: m_hwnd(NULL)
	{
#define MSGBIND(msg, func) \
	m_msgMap.insert(make_pair(msg, MSGFUNCTION(func)))

		MSGBIND(WM_CREATE, BUIWindow::OnCreate);
		MSGBIND(WM_DESTROY, BUIWindow::OnDestroy);
		MSGBIND(WM_QUIT, BUIWindow::OnQuit);
		MSGBIND(WM_NCCALCSIZE, BUIWindow::OnNcCalcSize);
		MSGBIND(WM_NCPAINT, BUIWindow::OnNcPaint);
		MSGBIND(WM_NCACTIVATE, BUIWindow::OnNcPaint);
	}

	BUIWindow::~BUIWindow()
	{
	}

	HWND BUIWindow::Create(HWND parent, LPCTSTR name, DWORD style, DWORD exStyle, const RECT rc)
	{
		if (!registerWindowClass())
			return NULL;

		m_hwnd = CreateWindow(GetWindowClassName(), name, style, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, parent, NULL, BApplication::GetInstance()->GetProcessInstance(), this);

		return m_hwnd;
	}

	void BUIWindow::CenterWindow()
	{
		RECT rcWin;
		::GetWindowRect(m_hwnd, &rcWin);
		int width = rcWin.right - rcWin.left;
		int height = rcWin.bottom - rcWin.top;

		HWND hWnd = m_hwnd;
		HWND hWndCenter = ::GetWindowOwner(m_hwnd);
		if (hWndCenter != NULL)
			hWnd = hWndCenter;

		// 处理多显示器模式下屏幕居中
		MONITORINFO monitorInfo = {};
		monitorInfo.cbSize = sizeof(MONITORINFO);
		::GetMonitorInfo(::MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &monitorInfo);
		RECT rcArea = monitorInfo.rcWork;

		RECT rcCenter;
		if (hWndCenter == NULL || IsIconic(hWndCenter))
			rcCenter = rcArea;
		else
			::GetWindowRect(hWndCenter, &rcCenter);

		int left = rcCenter.left + (rcCenter.right - rcCenter.left - width) / 2;
		int top = rcCenter.top + (rcCenter.bottom - rcCenter.top - height) / 2;
		::SetWindowPos(m_hwnd, NULL, left, top, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	void BUIWindow::ShowWindow(int show/* = SW_SHOW*/)
	{
		::ShowWindow(m_hwnd, show);
	}

	LRESULT BUIWindow::MessageDelegate(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		MSGMAPIT it = m_msgMap.find(uMsg);
		if (it != m_msgMap.end())
		{
			WINMsgFunction func = static_cast<WINMsgFunction>(it->second);
			return (this->*func)(uMsg, wParam, lParam);
		}

		return -1;
	}

	UINT BUIWindow::GetClassStyle() const
	{
		return CS_HREDRAW | CS_VREDRAW;;
	}

	LRESULT BUIWindow::MessageRouting(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return ::DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}

	LRESULT BUIWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		/*LONG style = GetWindowLong(m_hwnd, GWL_STYLE);
		style &= ~WS_CAPTION;
		SetWindowLong(m_hwnd, GWL_STYLE, style); //去标题栏

		LONG exStyle = GetWindowLong(m_hwnd, GWL_EXSTYLE);
		exStyle &= ~(WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME);
		SetWindowLong(m_hwnd, GWL_EXSTYLE, exStyle);  //去边框*/

		m_pUIManager = new BUIManager;
		m_pUIManager->Init(m_hwnd, GetWindowClassName());
		bstring xmlFilePath = BApplication::GetInstance()->GetApplicationPath();
		xmlFilePath.append(GetWindowResource());
		BUIWidgetBuilder builder;
		BUIWidget* pRoot = builder.CreateWidget(xmlFilePath.c_str(), m_pUIManager);
		m_pUIManager->AttachWidget(pRoot);

		return 0;
	}

	LRESULT BUIWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	LRESULT BUIWindow::OnQuit(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	LRESULT BUIWindow::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	LRESULT BUIWindow::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	LRESULT BUIWindow::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	LRESULT CALLBACK BUIWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		/*static BUIWindow* pThis;
		if (uMsg == WM_NCCREATE)
		{
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			pThis = static_cast<BUIWindow*>(lpcs->lpCreateParams);
			pThis->m_hwnd = hwnd;
		}*/

		BUIWindow* pThis = NULL;
		if( uMsg == WM_NCCREATE ) {
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			pThis = static_cast<BUIWindow*>(lpcs->lpCreateParams);
			::SetProp(hwnd, _T("WndX"), (HANDLE) pThis);
			pThis->m_hwnd = hwnd;
		} 
		else {
			pThis = reinterpret_cast<BUIWindow*>(::GetProp(hwnd, _T("WndX")));
			if( uMsg == WM_NCDESTROY && pThis != NULL ) {
				LRESULT lRes = ::DefWindowProc(hwnd, uMsg, wParam, lParam);
				::SetProp(hwnd, _T("WndX"), NULL);
				pThis->m_hwnd = NULL;
				return lRes;
			}
		}

		if (pThis != NULL)
		{
			LRESULT ret = pThis->MessageRouting(uMsg, wParam, lParam);
			return ret;
		}

		return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	bool BUIWindow::registerWindowClass()
	{
		WNDCLASS  wcs;
		wcs.style = GetClassStyle();
		wcs.lpfnWndProc = BUIWindow::WndProc;
		wcs.cbClsExtra = 0;
		wcs.cbWndExtra = 0;
		wcs.hInstance = BApplication::GetInstance()->GetProcessInstance();
		wcs.hIcon = 0;
		wcs.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		wcs.hbrBackground = NULL;
		wcs.lpszMenuName = NULL;
		wcs.lpszClassName = GetWindowClassName();
		ATOM ret = ::RegisterClass(&wcs);

		DWORD error = GetLastError();

		return (ret != NULL) || (error == ERROR_CLASS_ALREADY_EXISTS);
	}
}