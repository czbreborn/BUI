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

	public:
		bool IsUpdateNeeded() const;
		void NeedUpdate();
		void Invalidate();
		void Invalidate(RECT& rcItem);

		bool AttachWidget(BUIWidget* root);

	public:
		LRESULT MessageRouting(UINT uMsg, WPARAM wParam, LPARAM lParam);

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

	private:
		BUIWidget* FindControl(POINT pt) const;
		BUIWidget* FindControl(LPCTSTR pstrName);

	private:
		static WMPROCMAP s_wmProcMap;

		HWND m_hWndPaint;
		HDC  m_hdcPaint;
		bstring m_name;

		bool m_bUpdateNeeded;

		BUIWidget* m_rootWidget;
	};
}

#endif