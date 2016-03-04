#pragma once

#include "BUI.h"
#include "BRenderEngineDef.h"

class BRenderEngineManager
{
public:
	BRenderEngineManager();
	~BRenderEngineManager();

	void SetRenderEngineMode(RENDERENGINEMODE mode, LPCTSTR moduleName = NULL);
	BIRenderEngine* RenderEngine();

private:
	RENDERENGINEMODE m_renderEngineMode;
	BIRenderEngine* m_renderEngineInterface;
};

