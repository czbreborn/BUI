#ifndef __BRENDERENGINEGDIPLUS_H__
#define __BRENDERENGINEGDIPLUS_H__

#pragma once

namespace BUI{
	class BRenderEngineGdiPlus : public BIRenderEngine
	{
	protected:
		BRenderEngineGdiPlus();
		~BRenderEngineGdiPlus();

	public:
		static BRenderEngineGdiPlus* GetInstance();

	public:
		virtual void DrawLine(HDC hdc, const POINT& startP, const POINT& endP, int size, DWORD penColor, int style = penstyle_solid);
		virtual void DrawRect(HDC hdc, const RECT& rc, int size, DWORD penColor, int style = penstyle_solid);
		virtual void DrawRect(HDC hdc, const RECT& rc, RECT borderSize, DWORD penColor, int style = penstyle_solid);
		virtual void DrawRoundRect(HDC hdc, const RECT& rc, int size, int width, int height, DWORD penColor, int style = penstyle_solid);
		virtual void DrawText(HDC hdc, const RECT& rc, const TextDescription& textDesc);
		virtual void DrawImage(HDC hdc, LPCTSTR lpstrFileName, const RECT& rcDst, const RECT& rcPaint);
		virtual void DrawGradient(HDC hdc, const RECT& rc, DWORD dwColor1, DWORD dwColor2);
		virtual void DrawRoundGradient(HDC hdc, const RECT& rc, int width, int height, DWORD dwColor1, DWORD dwColor2);
		
		virtual bool DrawWindowRgn(HWND hwnd, const RECT& rc);
		virtual bool DrawWindowRoundRgn(HWND hwnd, const RECT& rc, int width, int height);

	private:
		void init();
		void uninit();
		
	private:
		DashStyle convertStyle(int style);
		StringAlignment convertAlignment(UINT align);
		StringAlignment convertLineAlignment(UINT align);
		GraphicsPath* genRoundRectPath(const RECT& rc, int width, int height);

	private:
		ULONG_PTR m_uGdiPlus;

	private:
		static BRenderEngineGdiPlus s_renderEngineGdiPlus;
	};
}
#endif