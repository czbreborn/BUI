#ifndef __BUIWINDOW_H__
#define __BUIWINDOW_H__

#pragma once

namespace BUI{
	class BUIWindow;
	typedef LRESULT(BUIWindow::*WINMsgFunction)(UINT uMsg, WPARAM wParam, LPARAM lParam);
	typedef map<int, WINMsgFunction> MSGMAP;
	typedef MSGMAP::iterator MSGMAPIT;

	class BUIManager;
	class BUI_API BUIWindow : public BUIObject
	{
	public:
		BUIWindow();
		~BUIWindow();

	public:
		HWND Create(HWND parent, LPCTSTR name, DWORD style, DWORD exStyle, const RECT rc);
		void CenterWindow();
		void ShowWindow(int show/* = SW_SHOW*/);

	protected:
		LRESULT MessageDelegate(UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:
		virtual LPCTSTR GetWindowClassName() const = 0;
		virtual UINT GetClassStyle() const;

		// 消息路由
		virtual LRESULT MessageRouting(UINT uMsg, WPARAM wParam, LPARAM lParam);

		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnQuit(UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		bool registerWindowClass();

	protected:
		HWND m_hwnd;

		MSGMAP m_msgMap;

		BUIManager*	m_pUIManager;
	};
}

#endif