#ifndef __BRENDERENGINEDEF_H__
#define __BRENDERENGINEDEF_H__

#pragma once

namespace BUI{
	enum RENDERENGINEMODE
	{
		renderengine_mode_gdiplus = 0,
		renderengine_mode_gdi,
		renderengine_mode_external,
	};

	enum PENSTYLE
	{
		penstyle_solid = 0,      // 0
		penstyle_dash,			 // 1
		penstyle_dot,			 // 2
		penstyle_dashdot,		 // 3
		penstyle_dashdotdot,	 // 4
		penstyle_custom,		 // 5        
	};

	class BIRenderEngine
	{
	public:
		virtual ~BIRenderEngine() = 0 {}

	public:
		virtual void DrawLine(HDC hdc, const POINT& startP, const POINT& endP, int size, DWORD penColor, int style = penstyle_solid) = 0;
		virtual void DrawRect(HDC hdc, const RECT& rc, int size, DWORD penColor, int style = penstyle_solid) = 0;
		virtual void DrawRect(HDC hdc, const RECT& rc, RECT borderSize, DWORD penColor, int style = penstyle_solid) = 0;
		virtual void DrawRoundRect(HDC hdc, const RECT& rc, int size, int width, int height, DWORD penColor, int style = penstyle_solid) = 0;
		virtual void DrawText(HDC hdc, const RECT& rc, LPCTSTR lpstrText, DWORD textColor, int fontSize, LPCTSTR pstrfontFamily, UINT style) = 0;
		virtual void DrawImage(HDC hdc, LPCTSTR lpstrFileName, const RECT& rc) = 0;
		virtual void DrawGradient(HDC hdc, const RECT& rc, DWORD dwColor1, DWORD dwColor2) = 0;
		virtual void DrawRoundGradient(HDC hdc, const RECT& rc, int width, int height, DWORD dwColor1, DWORD dwColor2) = 0;

		virtual bool DrawWindowRgn(HWND hwnd, const RECT& rc) = 0;
		virtual bool DrawWindowRoundRgn(HWND hwnd, const RECT& rc, int width, int height) = 0;
	};
}

#endif