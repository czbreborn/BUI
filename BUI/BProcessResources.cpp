#include "stdafx.h"
#include "BProcessResources.h"

BProcessResources BProcessResources::m_processResources;
BProcessResources::BProcessResources()
	: m_processInstance(NULL),
	  m_resorcesPath(L"")
{
}


BProcessResources::~BProcessResources()
{
}

BProcessResources* BProcessResources::GetInstance() {
	return &m_processResources;
}

void BProcessResources::SetProcessInstance(HINSTANCE inst)
{
	m_processInstance = inst;
}

HINSTANCE BProcessResources::GetProcessInstance() const
{
	return m_processInstance;
}

void BProcessResources::SetResourcesPath(LPCTSTR resPath)
{
	m_resorcesPath = resPath;
}

LPCTSTR BProcessResources::GetResourcesPath() const
{
	return m_resorcesPath.c_str();
}