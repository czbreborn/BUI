#include "stdafx.h"

namespace BUI{
	BRenderEngineGdiPlus BRenderEngineGdiPlus::s_renderEngineGdiPlus;
	BRenderEngineGdiPlus* BRenderEngineGdiPlus::GetInstance()
	{
		return &s_renderEngineGdiPlus;
	}

	BRenderEngineGdiPlus::BRenderEngineGdiPlus()
	{
		init();
	}


	BRenderEngineGdiPlus::~BRenderEngineGdiPlus()
	{
		uninit();
	}

	void BRenderEngineGdiPlus::init()
	{
		GdiplusStartupInput input;
		GdiplusStartup(&m_uGdiPlus, &input, NULL);
	}

	void BRenderEngineGdiPlus::uninit()
	{
		GdiplusShutdown(m_uGdiPlus);
	}

	DashStyle BRenderEngineGdiPlus::convertStyle(int style)
	{
		switch (style)
		{
		case penstyle_solid:
			return DashStyleSolid;

		case penstyle_dash:
			return DashStyleDash;

		case penstyle_dot:
			return DashStyleDot;

		case penstyle_dashdot:
			return DashStyleDashDot;

		case penstyle_dashdotdot:
			return DashStyleDashDotDot;

		case penstyle_custom:
			return DashStyleCustom;
		
		default:
			return DashStyleSolid;
		}
	}

	GraphicsPath* BRenderEngineGdiPlus::genRoundRectPath(const RECT& rc, int width, int height)
	{
		GraphicsPath* pPath = new GraphicsPath();
		pPath->AddArc(rc.left, rc.top, width * 2, height * 2, 180, 90);
		pPath->AddLine(rc.left + width, rc.top, rc.right - width, rc.top);
		pPath->AddArc(rc.right - 2 * width, rc.top, width * 2, height * 2, 270, 90);
		pPath->AddLine(rc.right, rc.top + height, rc.right, rc.bottom - height);
		pPath->AddArc(rc.right - 2 * width, rc.bottom - 2 * height, width * 2, height * 2, 0, 90);
		pPath->AddLine(rc.right - width, rc.bottom, rc.left + width, rc.bottom);
		pPath->AddArc(rc.left, rc.bottom - 2 * height, width * 2, height * 2, 90, 90);
		pPath->AddLine(rc.left, rc.bottom - height, rc.left, rc.top + height);
		return pPath;
	}

	void BRenderEngineGdiPlus::DrawLine(HDC hdc, const POINT& startP, const POINT& endP, int size, DWORD penColor, int style/* = penstyle_solid*/)
	{
		Pen pen(penColor, size);
		pen.SetDashStyle(convertStyle(style));

		Graphics grap(hdc);
		Gdiplus::PointF startPF(startP.x, startP.y);
		Gdiplus::PointF endPF(endP.x, endP.y);
		grap.SetSmoothingMode(SmoothingModeAntiAlias);
		grap.DrawLine(&pen, startPF, endPF);
	}

	void BRenderEngineGdiPlus::DrawRect(HDC hdc, const RECT& rc, int size, DWORD penColor, int style/* = penstyle_solid*/)
	{
		Pen pen(penColor, size);
		pen.SetDashStyle(convertStyle(style));

		Graphics grap(hdc);
		Gdiplus::RectF rect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
		grap.SetSmoothingMode(SmoothingModeAntiAlias);
		grap.DrawRectangle(&pen, rect);
	}

	void BRenderEngineGdiPlus::DrawRect(HDC hdc, const RECT& rc, RECT borderSize, DWORD penColor, int style/* = penstyle_solid*/)
	{
		POINT leftTop = {rc.left, rc.top};
		POINT rightTop = {rc.right, rc.top};
		POINT leftBottom = {rc.left, rc.bottom};
		POINT rightBottom = {rc.right, rc.bottom};

		DrawLine(hdc, leftTop, rightTop, borderSize.top, penColor, style);
		DrawLine(hdc, leftTop, leftBottom, borderSize.left, penColor, style);
		DrawLine(hdc, leftBottom, rightBottom, borderSize.bottom, penColor, style);
		DrawLine(hdc, rightTop, rightBottom, borderSize.right, penColor, style);
	}

	void BRenderEngineGdiPlus::DrawRoundRect(HDC hdc, const RECT& rc, int size, int width, int height, DWORD penColor, int style/* = penstyle_solid*/)
	{
		Pen pen(penColor, size);
		pen.SetDashStyle(convertStyle(style));

		GraphicsPath* pPath = genRoundRectPath(rc, width, height);
		Graphics grap(hdc);
		grap.SetSmoothingMode(SmoothingModeAntiAlias);
		grap.DrawPath(&pen, pPath);
		delete pPath;
	}

	void BRenderEngineGdiPlus::DrawText(HDC hdc, const RECT& rc, LPCTSTR lpstrText, DWORD textColor, int fontSize, LPCTSTR pstrfontFamily, UINT style)
	{
		bstring strfamily(_T("Arial"));
		if (pstrfontFamily != NULL && pstrfontFamily[0] != _T('\0'))
			strfamily = pstrfontFamily;
		FontFamily fontFamily(strfamily.c_str());
		Gdiplus::Font font(&fontFamily, fontSize, style, UnitPixel);
		Gdiplus::PointF point(rc.left, rc.top);
		SolidBrush brush(textColor);

		Graphics grap(hdc);
		grap.SetTextRenderingHint(TextRenderingHintAntiAlias);
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

	void BRenderEngineGdiPlus::DrawRoundGradient(HDC hdc, const RECT& rc, int width, int height, DWORD dwColor1, DWORD dwColor2)
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
		GraphicsPath* pPath = genRoundRectPath(rc, width, height);
		grap.FillPath(&linGrBrush, pPath);
	}

	bool BRenderEngineGdiPlus::DrawWindowRgn(HWND hwnd, const RECT& rc)
	{
		HDC hdc = GetDC(hwnd);

		Gdiplus::RectF rect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
		Region region(rect);
		Graphics grap(hdc);
		int ret = ::SetWindowRgn(hwnd, region.GetHRGN(&grap), TRUE);
		ReleaseDC(hwnd, hdc);

		return ret != 0;
	}

	bool BRenderEngineGdiPlus::DrawWindowRoundRgn(HWND hwnd, const RECT& rc, int width, int height)
	{
		HDC hdc = GetDC(hwnd);

		GraphicsPath* pPath = genRoundRectPath(rc, width, height);
		Region region(pPath);
		Graphics grap(hdc);
		int ret = ::SetWindowRgn(hwnd, region.GetHRGN(&grap), TRUE);
		delete pPath;

		ReleaseDC(hwnd, hdc);

		return ret != 0;
	}
}