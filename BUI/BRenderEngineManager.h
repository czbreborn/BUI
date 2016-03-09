#ifndef __BRENDERENGINEMANAGER_H__
#define __BRENDERENGINEMANAGER_H__

#pragma once

namespace BUI{
	class BRenderEngineManager
	{
	protected:
		BRenderEngineManager();
		~BRenderEngineManager();

	public:
		static BRenderEngineManager* GetInstance();

	public:
		void SetRenderEngineMode(RENDERENGINEMODE mode, LPCTSTR moduleName = NULL);
		BIRenderEngine* RenderEngine();

	private:
		RENDERENGINEMODE m_renderEngineMode;
		BIRenderEngine* m_renderEngineInterface;

		static BRenderEngineManager m_renderEngineManager;
	};
}

#endif