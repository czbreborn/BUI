#include "stdafx.h"

namespace BUI{
	BApplication BApplication::m_processResources;
	BApplication::BApplication()
		: m_processInstance(NULL),
		m_resorcesPath(_T("")),
		m_zipName(_T("")),
		m_applicationPath(_T(""))
	{
	}


	BApplication::~BApplication()
	{
	}

	BApplication* BApplication::GetInstance() {
		return &m_processResources;
	}

	void BApplication::SetProcessInstance(HINSTANCE inst)
	{
		m_processInstance = inst;
	}

	HINSTANCE BApplication::GetProcessInstance() const
	{
		return m_processInstance;
	}

	LPCTSTR BApplication::GetApplicationPath()
	{
		if(m_processInstance == NULL) 
			return _T("");

		if (m_applicationPath.empty())
		{
			TCHAR moduleName[MAX_PATH + 1] = { 0 };
			::GetModuleFileName(m_processInstance, moduleName, MAX_PATH);
			m_applicationPath = moduleName;
			int pos = m_applicationPath.rfind(_T('\\'));
			if (pos >= 0) 
				m_applicationPath = m_applicationPath.substr(0, pos + 1);
		}

		return m_applicationPath.c_str();
	}

	void BApplication::SetResourcesPath(LPCTSTR resPath)
	{
		m_resorcesPath = resPath;
	}

	LPCTSTR BApplication::GetResourcesPath() const
	{
		return m_resorcesPath.c_str();
	}

	void BApplication::SetResourceZip(LPCTSTR zipName)
	{
		m_zipName = zipName;
	}

	LPCTSTR BApplication::GetResourceZip() const
	{
		return m_zipName.c_str();
	}

	void BApplication::LoopMessage()
	{
		MSG msg = { 0 };
		while (::GetMessage(&msg, NULL, 0, 0))
		{
			if (!TranslateMessage(&msg))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}
	}

	BOOL BApplication::TranslateMessage(LPMSG pMsg)
	{
		HWND hwnd = pMsg->hwnd;
		return 0;
	}

	void BApplication::AddUIManager(HWND hwnd, BUIManager* uimanager)
	{
		m_uiManagerMap.insert(make_pair(hwnd, uimanager));
	}

	BUIManager* BApplication::GetUIManager(HWND hwnd)
	{
		BUIManager* pUIManager = NULL;
		UIMANAGERMAPIT it = m_uiManagerMap.find(hwnd);
		if (it != m_uiManagerMap.end())
		{
			pUIManager = it->second;
		}

		return pUIManager;
	}
}