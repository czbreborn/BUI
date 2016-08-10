#include "stdafx.h"
#include <zmouse.h>
namespace BUI{
	WMPROCMAP BUIManager::s_wmProcMap;

	BUIManager::BUIManager()
		: m_hWndPaint(NULL),
		m_hdcPaint(NULL),
		m_name(_T("")),
		m_bUpdateNeeded(false),
		m_bResizeNeeded(false),
		m_bMouseTrack(false),
		m_rootWidget(NULL),
		m_focusedWidget(NULL),
		m_eventClickWidget(NULL),
		m_caretWidth(-1),
		m_caretHeight(-1),
		m_caretBitMap(NULL),
		m_existCaret(false)
	{
	#define WMPROCBIND(msg, func) \
		s_wmProcMap.insert(make_pair(msg, SELECTOR(func)))

		// 绘制消息
		WMPROCBIND(WM_ERASEBKGND, BUIManager::OnEraseBkgnd);
		WMPROCBIND(WM_PAINT, BUIManager::OnPaint);

		// 鼠标消息
		WMPROCBIND(WM_MOUSEHOVER, BUIManager::OnMouseHover);
		WMPROCBIND(WM_MOUSEMOVE, BUIManager::OnMouseMove);
		WMPROCBIND(WM_MOUSELEAVE, BUIManager::OnMouseLeave);
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
		WMPROCBIND(WM_SIZE, BUIManager::OnSize);
		WMPROCBIND(WM_GETMINMAXINFO, BUIManager::OnGetMinMaxInfo);

		// 键盘消息
		WMPROCBIND(WM_KEYDOWN, BUIManager::OnKeyDown);
		WMPROCBIND(WM_CHAR, BUIManager::OnChar);
		
		m_szMinWindow.cx = m_szMinWindow.cy = 0;
		m_szMaxWindow.cx = m_szMaxWindow.cy = 0;
		m_szInitWindowSize.cx = m_szInitWindowSize.cy = 300;
		m_szRoundCorner.cx = m_szRoundCorner.cy = 0;

		::ZeroMemory(&m_rcSizeBox, sizeof(m_rcSizeBox));
		::ZeroMemory(&m_rcCaption, sizeof(m_rcCaption));

		m_ptLastMousePos.x = m_ptLastMousePos.y = 0;
	}


	BUIManager::~BUIManager()
	{
		ReleaseDC(m_hWndPaint, m_hdcPaint);
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

	HWND BUIManager::GetPaintWindow() const
	{
		return m_hWndPaint;
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

		m_bResizeNeeded = true;
		return true;
	}

	BUIWidget* BUIManager::GetFocus() const
	{
		return m_focusedWidget;
	}

	void BUIManager::SetFocus(BUIWidget* widget)
	{
		// Paint manager window has focus?
		HWND hFocusWnd = ::GetFocus();
		if (hFocusWnd != m_hWndPaint && 
			widget != m_focusedWidget) {
			::SetFocus(m_hWndPaint);
		}

		// Already has focus?
		if (widget == m_focusedWidget) 
			return;

		// Remove focus from old control
		if (m_focusedWidget != NULL) {
			TEventUI event = { 0 };
			event.type = uievent_killfocus;
			event.pSender = widget;
			event.dwTimestamp = ::GetTickCount();
			m_focusedWidget->Event(event);
			//SendNotify(m_pFocus, DUI_MSGTYPE_KILLFOCUS);
			m_focusedWidget = NULL;
		}

		if (widget == NULL) 
			return;

		// Set focus to new control
		if (widget != NULL && 
			widget->GetManager() == this &&
			widget->IsVisible() &&
			widget->IsEnabled()) {
			m_focusedWidget = widget;
			TEventUI event = { 0 };
			event.type = uievent_setfocus;
			event.pSender = widget;
			event.dwTimestamp = ::GetTickCount();
			m_focusedWidget->Event(event);
			// SendNotify(m_pFocus, DUI_MSGTYPE_SETFOCUS);
		}
	}

	RECT& BUIManager::GetSizeBox()
	{
		return m_rcSizeBox;
	}

	void BUIManager::SetSizeBox(const RECT& rcSizeBox)
	{
		m_rcSizeBox = rcSizeBox;
	}

	RECT& BUIManager::GetCaptionRect()
	{
		return m_rcCaption;
	}

	void BUIManager::SetCaptionRect(const RECT& rcCaption)
	{
		m_rcCaption = rcCaption;
	}

	SIZE BUIManager::GetRoundCorner() const
	{
		return m_szRoundCorner;
	}

	void BUIManager::SetRoundCorner(int cx, int cy)
	{
		m_szRoundCorner.cx = cx;
		m_szRoundCorner.cy = cy;
	}

	SIZE BUIManager::GetMinInfo() const
	{
		return m_szMinWindow;
	}

	void BUIManager::SetMinInfo(int cx, int cy)
	{
		m_szMinWindow.cx = cx;
		m_szMinWindow.cy = cy;
	}

	SIZE BUIManager::GetMaxInfo() const
	{
		return m_szMaxWindow;
	}

	void BUIManager::SetMaxInfo(int cx, int cy)
	{
		m_szMaxWindow.cx = cx;
		m_szMaxWindow.cy = cy;
	}

	bool BUIManager::MessageRouting(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes)
	{
		WMPROCMAPIT it = s_wmProcMap.find(uMsg);
		if (it != s_wmProcMap.end())
		{
			WMPROC proc = static_cast<WMPROC>(it->second);
			lRes = (this->*proc)(wParam, lParam);
			if (lRes != -1)
				return true;
			else
				return false;
		}

		return false;
	}

	LRESULT BUIManager::OnEraseBkgnd(WPARAM wParam, LPARAM lParam)
	{
		return 0;
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
			if (m_bResizeNeeded)
			{
				m_bResizeNeeded = false;
				m_rootWidget->SetPos(rcClient);
			}
			
			SIZE szxy = GetRoundCorner();
			if (szxy.cx > 0 || szxy.cy > 0)
			{
				RECT rootRc = m_rootWidget->GetPos();
				BRenderEngineManager::GetInstance()->RenderEngine()->DrawWindowRoundRgn(m_hWndPaint, rootRc, szxy.cx, szxy.cy);
			}
			
			// 创建画布，基于画布绘制
			BCanvas* canvas = BRenderCanvas::GetInstance()->GetDCCanvas(m_hdcPaint);
			if (canvas == NULL)
				canvas = BRenderCanvas::GetInstance()->GenDCCanvas(m_hdcPaint, rcClient);
			assert(canvas);
			m_rootWidget->Paint(m_hdcPaint, ps.rcPaint);
			// 绘制画布到整个窗口
			BRenderEngineManager::GetInstance()->RenderEngine()->DrawCanvas(canvas, ps.rcPaint);
		}
		EndPaint(m_hWndPaint, &ps);

		return 0;
	}

	LRESULT BUIManager::OnMouseHover(WPARAM wParam, LPARAM lParam)
	{
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		BUIWidget* pNewWidget = FindControl(pt);
		if (pNewWidget != NULL)
			return 1;

		if (m_eventClickWidget != NULL) {
			TEventUI event = { 0 };
			event.ptMouse = pt;
			event.type = uievent_mousehover;
			event.pSender = m_eventClickWidget;
			event.dwTimestamp = ::GetTickCount();
			m_eventClickWidget->Event(event);
		}

		return 1;
	}

	LRESULT BUIManager::OnMouseMove(WPARAM wParam, LPARAM lParam)
	{
		if (!m_bMouseTrack) {
			TRACKMOUSEEVENT tme = { 0 };
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_HOVER | TME_LEAVE;
			tme.hwndTrack = m_hWndPaint;
			tme.dwHoverTime = 400;
			::TrackMouseEvent(&tme);
			m_bMouseTrack = true;
		}

		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		m_ptLastMousePos = pt;
		BUIWidget* pNewWidget = FindControl(pt);
		if (pNewWidget != NULL && pNewWidget->GetManager() != this)
			return 1;

		TEventUI event = { 0 };
		event.ptMouse = pt;
		event.dwTimestamp = ::GetTickCount();
		if (m_eventClickWidget != NULL && 
			m_eventClickWidget != pNewWidget) {
			event.type = uievent_mouseleave;
			event.pSender = m_eventClickWidget;
			m_eventClickWidget->Event(event);
			m_eventClickWidget = NULL;
		}

		if (pNewWidget != NULL && 
			pNewWidget != m_eventClickWidget) {
			event.type = uievent_mouseenter;
			event.pSender = pNewWidget;
			pNewWidget->Event(event);
			m_eventClickWidget = pNewWidget;
		}

		if (m_eventClickWidget != NULL) {
			event.type = uievent_mousemove;
			event.pSender = m_eventClickWidget;
			m_eventClickWidget->Event(event);
		} else if (pNewWidget != NULL) {
			event.type = uievent_mousemove;
			event.pSender = pNewWidget;
			pNewWidget->Event(event);
		}

		return 0;
	}

	LRESULT BUIManager::OnMouseLeave(WPARAM wParam, LPARAM lParam)
	{
		if (m_bMouseTrack) {
			::SendMessage(m_hWndPaint, WM_MOUSEMOVE, 0, (LPARAM)-1);
		}
		return 1;
	}

	LRESULT BUIManager::OnLButtonDown(WPARAM wParam, LPARAM lParam)
	{
		// We alway set focus back to our app (this helps
		// when Win32 child windows are placed on the diuievent_mousemovealog
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

	LRESULT BUIManager::OnSize(WPARAM wParam, LPARAM lParam)
	{
		m_bResizeNeeded = true;

		return 0;
	}

	LRESULT BUIManager::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
		if (m_szMinWindow.cx > 0) 
			lpMMI->ptMinTrackSize.x = m_szMinWindow.cx;
		if (m_szMinWindow.cy > 0)
			lpMMI->ptMinTrackSize.y = m_szMinWindow.cy;
		if (m_szMaxWindow.cx > 0)
			lpMMI->ptMaxTrackSize.x = m_szMaxWindow.cx;
		if (m_szMaxWindow.cy > 0)
			lpMMI->ptMaxTrackSize.y = m_szMaxWindow.cy;
		return 1;
	}

	LRESULT BUIManager::OnKeyDown(WPARAM wParam, LPARAM lParam)
	{
		if (m_focusedWidget) {
			TEventUI event = { 0 };
			event.type = uievent_keydown;
			event.wParam = wParam;
			event.lParam = lParam;
			event.chKey = wParam;
			event.wKeyState = lParam;
			event.dwTimestamp = ::GetTickCount();
			m_focusedWidget->Event(event);

			bstringstream woss;
			woss << L"OnKeyDown ::" << wParam << L"::" << lParam << L"type" << m_focusedWidget->GetType() << endl;
			::OutputDebugString(woss.str().c_str());
		}

		return 1;
	}

	LRESULT BUIManager::OnChar(WPARAM wParam, LPARAM lParam)
	{
		if (m_focusedWidget) {
			TEventUI event = { 0 };
			event.type = uievent_char;
			event.wParam = wParam;
			event.lParam = lParam;
			event.chKey = wParam;
			event.wKeyState = lParam;
			event.dwTimestamp = ::GetTickCount();
			m_focusedWidget->Event(event);
		}

		return 1;
	}

	BUIWidget* BUIManager::FindControl(POINT pt) const
	{
		return m_rootWidget->FindControl(BUIAssist::FindWidgetFromPoint, &pt, UIFIND_VISIBLE | UIFIND_HITTEST);
	}

	BUIWidget* BUIManager::FindControl(LPCTSTR pstrName)
	{
		return NULL;
	}

	BOOL BUIManager::CreateCaret(int width, int height, HBITMAP hBitmap/* = NULL*/)
	{
		BOOL ret = FALSE;
		if (m_existCaret) {
			if (m_caretWidth != width ||
				m_caretHeight != height ||
				m_caretBitMap != hBitmap) {
					if (DestroyCaret()){
						if (::CreateCaret(m_hWndPaint, hBitmap, width, height)) {
							m_caretBitMap = hBitmap;
							m_caretWidth = width;
							m_caretHeight = height;
							m_existCaret = true;
							ret = TRUE;
						}
					}
			} else {	// 存在相同的光标
				ret = TRUE;
			}
		} else {
			if (::CreateCaret(m_hWndPaint, hBitmap, width, height)) {
				m_caretBitMap = hBitmap;
				m_caretWidth = width;
				m_caretHeight = height;
				m_existCaret = true;
				ret = TRUE;
			}
		}
		return ret;
	}

	BOOL BUIManager::DestroyCaret()
	{
		BOOL ret = FALSE;
		if (::DestroyCaret()) {
			m_caretBitMap = NULL;
			m_caretWidth = -1;
			m_caretHeight = -1;
			m_existCaret = false;
			ret = TRUE;
		}
		return ret;
	}

	BOOL BUIManager::ShowCaret()
	{
		return ::ShowCaret(m_hWndPaint);
	}

	BOOL BUIManager::HideCaret()
	{
		return ::HideCaret(m_hWndPaint);
	}

	BOOL BUIManager::SetCaretPos(int x, int y)
	{
		return ::SetCaretPos(x, y);
	}

	BOOL BUIManager::GetCaretPos(LPPOINT lpPoint)
	{
		return ::GetCaretPos(lpPoint);
	}
}