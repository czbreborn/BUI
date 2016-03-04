#pragma once
#include "BUI.h"

class BUI_API BProcessResources
{
protected:
	BProcessResources();
	~BProcessResources();

public:
	static BProcessResources* GetInstance();

public:
	void SetProcessInstance(HINSTANCE inst);
	HINSTANCE GetProcessInstance() const;
	void SetResourcesPath(LPCTSTR resPath);
	LPCTSTR GetResourcesPath() const;

private:
	static BProcessResources m_processResources;

	HINSTANCE m_processInstance;
	bstring m_resorcesPath;
};

