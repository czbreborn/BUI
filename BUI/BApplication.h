#ifndef __BAPPLICATION_H__
#define __BAPPLICATION_H__

#pragma once

namespace BUI{
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

		LRESULT MessageRouting(UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		static BApplication m_processResources;

		HINSTANCE m_processInstance;
		bstring m_resorcesPath;
		bstring m_zipName;
	};
}
#endif // __BAPPLICATION_H__