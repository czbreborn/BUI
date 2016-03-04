#pragma once

enum RENDERENGINEMODE
{
	renderengine_mode_gdiplus = 0,
	renderengine_mode_gdi,
	renderengine_mode_external,
};

class BIRenderEngine
{
public:
	virtual ~BIRenderEngine() = 0 {}

public:
	virtual void DrawLine(HDC hdc, const POINT& startP, const POINT& endP, int size, DWORD penColor, int style = PS_SOLID) = 0;
	virtual void DrawRect(HDC hdc, const RECT& rc, int size, DWORD penColor, int style = PS_SOLID) = 0;
	virtual void DrawText(HDC hdc, const RECT& rc, LPCTSTR lpstrText, DWORD textColor, int fontSize, LPCTSTR pstrfontFamily, UINT style) = 0;
	virtual void DrawImage(HDC hdc, LPCTSTR lpstrFileName, const RECT& rc) = 0;
};