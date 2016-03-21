#ifndef __BAPPLICATION_H__
#define __BAPPLICATION_H__

#pragma once

namespace BUI{
	class BUIManager;
	class BUI_API BApplication
	{
	protected:
		BApplication();
		~BApplication();

	public:
		static BApplication* GetInstance();

	public:
		void SetProcessInstance(HINSTANCE inst);
		HINSTANCE GetProcessInstance() const;
		void SetResourcesPath(LPCTSTR resPath);
		LPCTSTR GetResourcesPath() const;
		void SetResourceZip(LPCTSTR zipName);
		LPCTSTR GetResourceZip() const;

		void LoopMessage();
		BOOL TranslateMessage(LPMSG pMsg);

		LRESULT MessageRouting(UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		// 添加窗口UI管理实例
		void AddUIManager(HWND hwnd, BUIManager* uimanager);
		BUIManager* GetUIManager(HWND hwnd);

	private:
		static BApplication m_processResources;

		HINSTANCE m_processInstance;
		bstring m_resorcesPath;
		bstring m_zipName;

		typedef map<HWND, BUIManager*> UIMANAGERMAP;
		typedef UIMANAGERMAP::iterator UIMANAGERMAPIT;
		UIMANAGERMAP m_uiManagerMap;
	};
}
#endif // __BAPPLICATION_H__