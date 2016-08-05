#ifndef __BUIMANAGER_H__
#define __BUIMANAGER_H__

#pragma once

namespace BUI{
	class BUIManager;
	typedef LRESULT(BUIManager::*WMPROC)(WPARAM wParam, LPARAM lParam);
	typedef map<int, WMPROC> WMPROCMAP;
	typedef WMPROCMAP::iterator WMPROCMAPIT;

	class BUI_API BUIManager
	{
	public:
		BUIManager();
		~BUIManager();

		void Init(HWND hwnd, LPCTSTR name = NULL);
		HDC GetPaintDC();
		HWND GetPaintWindow() const;

	public:
		bool IsUpdateNeeded() const;
		void NeedUpdate();
		void Invalidate();
		void Invalidate(RECT& rcItem);

		bool AttachWidget(BUIWidget* root);
		BUIWidget* GetFocus() const;
		void SetFocus(BUIWidget* widget);

		RECT& GetSizeBox();
		void SetSizeBox(const RECT& rcSizeBox);
		RECT& GetCaptionRect();
		void SetCaptionRect(const RECT& rcCaption);
		SIZE GetRoundCorner() const;
		void SetRoundCorner(int cx, int cy);

		SIZE GetMinInfo() const;
		void SetMinInfo(int cx, int cy);
		SIZE GetMaxInfo() const;
		void SetMaxInfo(int cx, int cy);

		BUIWidget* FindControl(POINT pt) const;
		BUIWidget* FindControl(LPCTSTR pstrName);

	public:
		// 光标管理
		BOOL CreateCaret(int width, int height, HBITMAP hBitmap = NULL);
		BOOL DestroyCaret();
		BOOL ShowCaret();
		BOOL HideCaret();
		BOOL SetCaretPos(int x, int y);
		BOOL GetCaretPos(LPPOINT lpPoint);

	public:
		 bool MessageRouting(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);

	protected:
		LRESULT OnEraseBkgnd(WPARAM wParam, LPARAM lParam);
		LRESULT OnPaint(WPARAM wParam, LPARAM lParam);

		LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
		LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
		LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);
		LRESULT OnLButtonDBClick(WPARAM wParam, LPARAM lParam);
		LRESULT OnRButtonDown(WPARAM wParam, LPARAM lParam);
		LRESULT OnRButtonUp(WPARAM wParam, LPARAM lParam);
		LRESULT OnRButtonDBClick(WPARAM wParam, LPARAM lParam);
		LRESULT OnMButtonDown(WPARAM wParam, LPARAM lParam);
		LRESULT OnMButtonUp(WPARAM wParam, LPARAM lParam);
		LRESULT OnMButtonDBClick(WPARAM wParam, LPARAM lParam);
		LRESULT OnMouseWheel(WPARAM wParam, LPARAM lParam);
		LRESULT OnSetCursor(WPARAM wParam, LPARAM lParam);

		LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
		LRESULT OnSize(WPARAM wParam, LPARAM lParam);
		LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);

		LRESULT OnChar(WPARAM wParam, LPARAM lParam);

	private:
		static WMPROCMAP s_wmProcMap;

		HWND m_hWndPaint;
		HDC  m_hdcPaint;
		bstring m_name;

		bool m_bUpdateNeeded;
		bool m_bResizeNeeded;

		SIZE m_szMinWindow;
		SIZE m_szMaxWindow;

		BUIWidget* m_rootWidget;
		BUIWidget* m_focusedWidget;
		BUIWidget* m_eventClickWidget;

		SIZE m_szInitWindowSize;
		RECT m_rcSizeBox;
		RECT m_rcCaption;
		SIZE m_szRoundCorner;
		POINT m_ptLastMousePos;

		// 光标相关属性
		int m_caretWidth;
		int m_caretHeight;
		HBITMAP m_caretBitMap;
		bool m_existCaret;
	};
}

#endif