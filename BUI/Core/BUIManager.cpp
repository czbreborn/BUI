#include "stdafx.h"

namespace BUI{
	WMPROCMAP BUIManager::s_wmProcMap;

	BUIManager::BUIManager()
		: m_hWndPaint(NULL),
		m_hdcPaint(NULL),
		m_name(_T("")),
		m_bUpdateNeeded(false),
		m_rootWidget(NULL),
		m_eventClickWidget(NULL)
	{
	#define WMPROCBIND(msg, func) \
		s_wmProcMap.insert(make_pair(msg, SELECTOR(func)))

		// 绘制消息
		WMPROCBIND(WM_ERASEBKGND, BUIManager::OnEraseBkgnd);
		WMPROCBIND(WM_PAINT, BUIManager::OnPaint);
		// 鼠标消息
		WMPROCBIND(WM_MOUSEMOVE, BUIManager::OnMouseMove);
		WMPROCBIND(WM_LBUTTONDOWN, BUIManager::OnLButtonDown);
		WMPROCBIND(WM_LBUTTONUP, BUIManager::OnLButtonUp);
		WMPROCBIND(WM_LBUTTONDBLCLK, BUIManager::OnLButtonDBClick);
		WMPROCBIND(WM_RBUTTONDOWN, BUIManager::OnRButtonDown);
		WMPROCBIND(WM_RBUTTONUP, BUIManager::OnRButtonUp);
		WMPROCBIND(WM_RBUTTONDBLCLK, BUIManager::OnRButtonDBClick);
		WMPROCBIND(WM_MBUTTONDOWN, BUIManager::OnMButtonDown);
		WMPROCBIND(WM_MBUTTONUP, BUIManager::OnMButtonUp);
		WMPROCBIND(WM_MBUTTONDBLCLK, BUIManager::OnMButtonDBClick);
		WMPROCBIND(WM_MOUSEWHEEL, BUIManager::OnMouseWheel);	
		WMPROCBIND(WM_SETCURSOR, BUIManager::OnSetCursor);
		WMPROCBIND(WM_COMMAND, BUIManager::OnCommand);
	}


	BUIManager::~BUIManager()
	{
	}

	void BUIManager::Init(HWND hwnd, LPCTSTR name/* = NULL*/)
	{
		if (m_name.empty())
			m_name = name;

		if (m_hWndPaint != hwnd)
		{
			m_hWndPaint = hwnd;
			m_hdcPaint = GetDC(hwnd);
		}
	}


	HDC BUIManager::GetPaintDC()
	{
		return m_hdcPaint;
	}

	bool BUIManager::IsUpdateNeeded() const
	{
		return m_bUpdateNeeded;
	}

	void BUIManager::NeedUpdate()
	{
		m_bUpdateNeeded = true;
	}

	void BUIManager::Invalidate()
	{
		::InvalidateRect(m_hWndPaint, NULL, false);
	}

	void BUIManager::Invalidate(RECT& rcItem)
	{
		if (rcItem.left < 0)
			rcItem.left = 0;
		if (rcItem.top < 0)
			rcItem.top = 0;
		if (rcItem.right < rcItem.left)
			rcItem.right = rcItem.left;
		if (rcItem.bottom < rcItem.top)
			rcItem.bottom = rcItem.top;
		::InvalidateRect(m_hWndPaint, &rcItem, FALSE);
	}

	bool BUIManager::AttachWidget(BUIWidget* root)
	{
		m_rootWidget = root;
		return true;
	}

	BUIWidget* BUIManager::GetFocus() const
	{

	}

	void BUIManager::SetFocus(BUIWidget* widget)
	{

	}

	LRESULT BUIManager::MessageRouting(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT res = -1;
		WMPROCMAPIT it = s_wmProcMap.find(uMsg);
		if (it != s_wmProcMap.end())
		{
			WMPROC proc = static_cast<WMPROC>(it->second);
			res = (this->*proc)(wParam, lParam);
		}

		std::wstringstream ss;
		ss << ::GetTickCount();
		ss << _T(" ");
		ss << uMsg;
		ss << _T("\n");
		::OutputDebugString(ss.str().c_str());

		return res;
	}

	LRESULT BUIManager::OnEraseBkgnd(WPARAM wParam, LPARAM lParam)
	{
		return 1;
	}

	LRESULT BUIManager::OnPaint(WPARAM wParam, LPARAM lParam)	
	{
		UNREFERENCED_PARAMETER(wParam);
		UNREFERENCED_PARAMETER(lParam);

		PAINTSTRUCT ps = { 0 };
		BeginPaint(m_hWndPaint, &ps);
		if (m_rootWidget != NULL)
		{
			RECT rcClient = { 0 };
			::GetClientRect(m_hWndPaint, &rcClient);

			m_rootWidget->SetPos(rcClient);
			SIZE szxy = m_rootWidget->GetBorderRound();
			if (szxy.cx > 0 || szxy.cy > 0)
			{
				RECT rootRc = m_rootWidget->GetPos();
				BRenderEngineManager::GetInstance()->RenderEngine()->DrawWindowRoundRgn(m_hWndPaint, rootRc, szxy.cx, szxy.cy);
			}

			m_rootWidget->Paint(m_hdcPaint, rcClient);
		}
		EndPaint(m_hWndPaint, &ps);

		return 0;
	}

	LRESULT BUIManager::OnMouseMove(WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	LRESULT BUIManager::OnLButtonDown(WPARAM wParam, LPARAM lParam)
	{
		// We alway set focus back to our app (this helps
		// when Win32 child windows are placed on the dialog
		// and we need to remove them on focus change).
		::SetFocus(m_hWndPaint);
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		//m_ptLastMousePos = pt;
		BUIWidget* pWidget = FindControl(pt);
		if( pWidget == NULL ) 
			return 1;
		if( pWidget->GetManager() != this ) 
			return 1;

		m_eventClickWidget = pWidget;
		pWidget->SetFocus();
		TEventUI event = { 0 };
		event.type = uievent_buttondown;
		event.wParam = wParam;
		event.lParam = lParam;
		event.ptMouse = pt;
		event.wKeyState = wParam;
		event.dwTimestamp = ::GetTickCount();
		pWidget->Event(event);
		// We always capture the mouse
		::SetCapture(m_hWndPaint);

		return 0;
	}

	LRESULT BUIManager::OnLButtonUp(WPARAM wParam, LPARAM lParam)
	{
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		//m_ptLastMousePos = pt;
		if (m_eventClickWidget == NULL)
			return 1;

		::ReleaseCapture();
		TEventUI event = { 0 };
		event.type = uievent_buttonup;
		event.wParam = wParam;
		event.lParam = lParam;
		event.ptMouse = pt;
		event.wKeyState = wParam;
		event.dwTimestamp = ::GetTickCount();
		m_eventClickWidget->Event(event);
		m_eventClickWidget = NULL;
		return 0;
	}

	LRESULT BUIManager::OnLButtonDBClick(WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	LRESULT BUIManager::OnRButtonDown(WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}
	
	LRESULT BUIManager::OnRButtonUp(WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	LRESULT BUIManager::OnRButtonDBClick(WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	LRESULT BUIManager::OnMButtonDown(WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	LRESULT BUIManager::OnMButtonUp(WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	LRESULT BUIManager::OnMButtonDBClick(WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	LRESULT BUIManager::OnMouseWheel(WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	LRESULT BUIManager::OnSetCursor(WPARAM wParam, LPARAM lParam)
	{
		return -1;
	}

	LRESULT BUIManager::OnCommand(WPARAM wParam, LPARAM lParam)
	{
		if(lParam == 0)
			return 0;

		HWND hWndChild = (HWND)lParam;
		return ::SendMessage(hWndChild, OCM__BASE + WM_COMMAND, wParam, lParam);
	}

	BUIWidget* BUIManager::FindControl(POINT pt) const
	{
		return m_rootWidget->FindControl(BUIAssist::FindWidgetFromPoint, &pt, UIFIND_VISIBLE | UIFIND_HITTEST);
	}

	BUIWidget* BUIManager::FindControl(LPCTSTR pstrName)
	{
		return NULL;
	}
}