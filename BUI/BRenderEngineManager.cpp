#include "stdafx.h"

namespace BUI{
	BRenderEngineManager BRenderEngineManager::m_renderEngineManager;

	BRenderEngineManager::BRenderEngineManager()
		: m_renderEngineMode(renderengine_mode_gdiplus)
	{
		m_renderEngineInterface = BRenderEngineGdiPlus::GetInstance();
	}


	BRenderEngineManager::~BRenderEngineManager()
	{
	}

	BRenderEngineManager* BRenderEngineManager::GetInstance()
	{
		return &m_renderEngineManager;
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
}