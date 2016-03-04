#include "stdafx.h"
#include "BRenderEngineManager.h"
#include "BRenderEngineGdiPlus.h"

BRenderEngineManager::BRenderEngineManager()
	: m_renderEngineMode(renderengine_mode_gdiplus)
{
	m_renderEngineInterface = BRenderEngineGdiPlus::GetInstance();
}


BRenderEngineManager::~BRenderEngineManager()
{
}

void BRenderEngineManager::SetRenderEngineMode(RENDERENGINEMODE mode, LPCTSTR moduleName/* = NULL*/)
{
	if (mode != m_renderEngineMode)
	{
		switch (mode)
		{
		case renderengine_mode_gdiplus:
			m_renderEngineInterface = BRenderEngineGdiPlus::GetInstance();
			break;
		case renderengine_mode_gdi:
			break;
		case renderengine_mode_external:
			break;
		default:
			break;
		}
	}
}

BIRenderEngine* BRenderEngineManager::RenderEngine()
{
	return m_renderEngineInterface;
}