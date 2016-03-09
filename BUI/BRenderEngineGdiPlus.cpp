#include "stdafx.h"

#include <gdiplus.h>
#include <gdiplusenums.h>

#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

namespace BUI{
	BRenderEngineGdiPlus BRenderEngineGdiPlus::s_renderEngineGdiPlus;
	BRenderEngineGdiPlus* BRenderEngineGdiPlus::GetInstance()
	{
		return &s_renderEngineGdiPlus;
	}

	BRenderEngineGdiPlus::BRenderEngineGdiPlus()
	{
		Init();
	}


	BRenderEngineGdiPlus::~BRenderEngineGdiPlus()
	{
		Uninit();
	}

	void BRenderEngineGdiPlus::Init()
	{
		GdiplusStartupInput input;
		ULONG_PTR uGdiPlus;
		GdiplusStartup(&m_uGdiPlus, &input, NULL);
	}

	void BRenderEngineGdiPlus::Uninit()
	{
		GdiplusShutdown(m_uGdiPlus);
	}

	void BRenderEngineGdiPlus::DrawLine(HDC hdc, const POINT& startP, const POINT& endP, int size, DWORD penColor, int style/* = PS_SOLID*/)
	{
		Pen pen(penColor, size);

		Graphics grap(hdc);
		Gdiplus::PointF startPF(startP.x, startP.y);
		Gdiplus::PointF endPF(endP.x, endP.y);
		grap.DrawLine(&pen, startPF, endPF);
	}

	void BRenderEngineGdiPlus::DrawRect(HDC hdc, const RECT& rc, int size, DWORD penColor, int style/* = PS_SOLID*/)
	{
		Pen pen(penColor, size);

		Graphics grap(hdc);
		Gdiplus::RectF rect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
		grap.DrawRectangle(&pen, rect);
	}

	void BRenderEngineGdiPlus::DrawText(HDC hdc, const RECT& rc, LPCTSTR lpstrText, DWORD textColor, int fontSize, LPCTSTR pstrfontFamily, UINT style)
	{
		bstring strfamily(_T("Arial"));
		if (pstrfontFamily != NULL && pstrfontFamily[0] != _T('\0'))
			strfamily = pstrfontFamily;
		FontFamily fontFamily(strfamily.c_str());
		Font font(&fontFamily, fontSize, style, UnitPixel);
		Gdiplus::PointF point(rc.left, rc.top);
		SolidBrush brush(textColor);

		Graphics grap(hdc);
		grap.DrawString(lpstrText, -1, &font, point, &brush);
	}

	void BRenderEngineGdiPlus::DrawImage(HDC hdc, LPCTSTR lpstrFileName, const RECT& rc)
	{
		Image image(lpstrFileName);

		Graphics grap(hdc);
		Gdiplus::Rect rect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
		grap.DrawImage(&image, rect);
	}

	void BRenderEngineGdiPlus::DrawGradient(HDC hdc, const RECT& rc, DWORD dwColor1, DWORD dwColor2)
	{
		PointF startPF(rc.left, (rc.top + rc.bottom) / 2);
		PointF endPF(rc.right, (rc.top + rc.bottom) / 2);
		Gdiplus::LinearGradientBrush linGrBrush(
			startPF,
			endPF,
			dwColor1,
			dwColor2
			);

		Graphics grap(hdc);
		Gdiplus::Rect rect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
		grap.FillRectangle(&linGrBrush, rect);
	}
}