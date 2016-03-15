#include "stdafx.h"

namespace BUI{
	BApplication BApplication::m_processResources;
	BApplication::BApplication()
		: m_processInstance(NULL),
		m_resorcesPath(_T("")),
		m_zipName(_T(""))
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
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
}