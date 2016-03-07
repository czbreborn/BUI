#pragma once
#include "BUI.h"
#include "BRenderEngineDef.h"

class BRenderEngineGdiPlus : public BIRenderEngine
{
protected:
	BRenderEngineGdiPlus();
	~BRenderEngineGdiPlus();

public:
	static BRenderEngineGdiPlus* GetInstance();

public:
	virtual void DrawLine(HDC hdc, const POINT& startP, const POINT& endP, int size, DWORD penColor, int style = PS_SOLID);
	virtual void DrawRect(HDC hdc, const RECT& rc, int size, DWORD penColor, int style = PS_SOLID);
	virtual void DrawText(HDC hdc, const RECT& rc, LPCTSTR lpstrText, DWORD textColor, int fontSize, LPCTSTR pstrfontFamily, UINT style);
	virtual void DrawImage(HDC hdc, LPCTSTR lpstrFileName, const RECT& rc);

private:
	void Init();
	void Uninit();

private:
	ULONG_PTR m_uGdiPlus;

private:
	static BRenderEngineGdiPlus s_renderEngineGdiPlus;
};

