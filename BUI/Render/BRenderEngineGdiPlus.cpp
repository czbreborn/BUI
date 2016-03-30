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

	StringAlignment BRenderEngineGdiPlus::convertAlignment(UINT align)
	{
		switch (align & 0x0F)
		{
		case textalignment_left:
			return StringAlignmentNear;

		case textalignment_right:
			return StringAlignmentFar;

		case textalignment_center:
			return StringAlignmentCenter;

		default:
			return StringAlignmentCenter;
		}
	}

	StringAlignment BRenderEngineGdiPlus::convertLineAlignment(UINT align)
	{
		switch (align & 0xF0)
		{
		case textalignment_top:
			return StringAlignmentNear;

		case textalignment_bottom:
			return StringAlignmentFar;

		case textalignment_vcenter:
			return StringAlignmentCenter;

		default:
			return StringAlignmentCenter;
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

	void BRenderEngineGdiPlus::DrawText(HDC hdc, const RECT& rc, const TextDescription& textDesc)
	{
		bstring strfamily(_T("Arial"));
		if (!textDesc.fontFamily.empty())
			strfamily = textDesc.fontFamily;
		FontFamily fontFamily(strfamily.c_str());
		StringFormat stringFormat;
		stringFormat.SetAlignment(convertAlignment(textDesc.align));
		stringFormat.SetLineAlignment(convertLineAlignment(textDesc.align));
		stringFormat.SetFormatFlags(textDesc.formatFlags);

		Graphics grap(hdc);
		grap.SetSmoothingMode(SmoothingModeAntiAlias);
		grap.SetInterpolationMode(InterpolationModeHighQualityBicubic);
		grap.SetTextRenderingHint(TextRenderingHintAntiAlias);
		RectF rcf(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
		GraphicsPath path;
		path.AddString(textDesc.content.c_str(), textDesc.content.length(), &fontFamily, textDesc.style, textDesc.fontSize, rcf, &stringFormat);
		if (textDesc.bGlow)
		{
			for (int i = 1; i < 8; i++)
			{
				Pen pen(textDesc.glowColor, i);
				pen.SetLineJoin(LineJoinRound);
				grap.DrawPath(&pen, &path);
			}

			DWORD dwColor1 = textDesc.textColor;
			DWORD dwColor2 = textDesc.textColor1;
			if (dwColor2 == 0)
				dwColor2 = dwColor1;
			Gdiplus::LinearGradientBrush linGrBrush(
				Gdiplus::PointF(rc.left, rc.top),
				Gdiplus::PointF(rc.right, rc.bottom),
				dwColor1,
				dwColor2
				);

			grap.FillPath(&linGrBrush, &path);

			return;
		}
		
		if (textDesc.bStroke)
		{
			if (textDesc.doubleColor > 0)
			{
				Pen pen(textDesc.doubleColor, 4);
				pen.SetLineJoin(LineJoinRound);
				grap.DrawPath(&pen, &path);
			}

			if (textDesc.singleColor > 0)
			{
				Pen pen(textDesc.singleColor, 2);
				pen.SetLineJoin(LineJoinRound);
				grap.DrawPath(&pen, &path);
			}

			Pen pen(textDesc.textColor);
			grap.DrawPath(&pen, &path);

			DWORD dwColor1 = textDesc.textColor;
			DWORD dwColor2 = textDesc.textColor1;
			if (dwColor2 == 0)
				dwColor2 = dwColor1;
			Gdiplus::LinearGradientBrush linGrBrush(
				Gdiplus::PointF(rc.left, rc.top),
				Gdiplus::PointF(rc.right, rc.bottom),
				dwColor1,
				dwColor2
				);

			grap.FillPath(&linGrBrush, &path);
			return ;
		}

		Pen pen(textDesc.textColor);
		grap.DrawPath(&pen, &path);
	}

	void BRenderEngineGdiPlus::DrawImage(HDC hdc, LPCTSTR lpstrFileName, const RECT& rcDst, const RECT& rcPaint)
	{
		Image image(lpstrFileName);

		Graphics grap(hdc);
		Gdiplus::RectF rcfDst(rcPaint.left, rcPaint.top, rcPaint.right - rcPaint.left, rcPaint.bottom - rcPaint.top);
		rcfDst.Width = min(image.GetWidth(), rcfDst.Width);
		rcfDst.Height = min(image.GetHeight(), rcfDst.Height);

		Gdiplus::RectF rcfPaint(rcPaint.left, rcPaint.top, rcPaint.right - rcPaint.left, rcPaint.bottom - rcPaint.top);
		Gdiplus::RectF rcfImage(rcDst.left, rcDst.top, rcDst.left + image.GetWidth(), rcDst.top + image.GetHeight());
		rcfPaint.Intersect(rcfImage);
		rcfDst.Intersect(rcfImage);
		grap.DrawImage(&image, rcfDst, rcfPaint.GetLeft() - rcfImage.GetLeft(), rcfPaint.GetTop() - rcfImage.GetTop(), rcfPaint.GetRight() - rcfPaint.GetLeft(), rcfPaint.GetBottom() - rcfPaint.GetTop(), UnitPixel);
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