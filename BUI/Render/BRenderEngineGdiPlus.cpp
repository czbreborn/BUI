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

	void BRenderEngineGdiPlus::drawGlowText(Graphics& grap, const RECT& rc, const TextDescription& textDesc)
	{
		bstring strfamily(_T("Î¢ÈíÑÅºÚ"));
		if (!textDesc.fontFamily.empty())
			strfamily = textDesc.fontFamily;
		FontFamily fontFamily(strfamily.c_str());
		StringFormat stringFormat;
		stringFormat.SetAlignment(convertAlignment(textDesc.align));
		stringFormat.SetLineAlignment(convertLineAlignment(textDesc.align));
		stringFormat.SetFormatFlags(textDesc.formatFlags);

		RectF rcf(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
		GraphicsPath path;
		path.AddString(textDesc.content.c_str(), textDesc.content.length(), &fontFamily, textDesc.style, textDesc.fontSize, rcf, &stringFormat);

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
	}

	void BRenderEngineGdiPlus::drawStrokeText(Graphics& grap, const RECT& rc, const TextDescription& textDesc)
	{
		bstring strfamily(_T("Î¢ÈíÑÅºÚ"));
		if (!textDesc.fontFamily.empty())
			strfamily = textDesc.fontFamily;
		FontFamily fontFamily(strfamily.c_str());
		StringFormat stringFormat;
		stringFormat.SetAlignment(convertAlignment(textDesc.align));
		stringFormat.SetLineAlignment(convertLineAlignment(textDesc.align));
		stringFormat.SetFormatFlags(textDesc.formatFlags);

		RectF rcf(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
		GraphicsPath path;
		path.AddString(textDesc.content.c_str(), textDesc.content.length(), &fontFamily, textDesc.style, textDesc.fontSize, rcf, &stringFormat);

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
	}

	void BRenderEngineGdiPlus::DrawLine(HDC hdc, const POINT& startP, const POINT& endP, int size, DWORD penColor, int style/* = penstyle_solid*/)
	{
		Pen pen(penColor, size);
		pen.SetDashStyle(convertStyle(style));

		BCanvas* canvas = BRenderCanvas::GetInstance()->GetDCCanvas(hdc);
		assert(canvas);
		Graphics grap(canvas->GetCanvas());
		Gdiplus::PointF startPF(startP.x, startP.y);
		Gdiplus::PointF endPF(endP.x, endP.y);
		grap.SetSmoothingMode(SmoothingModeAntiAlias);
		grap.DrawLine(&pen, startPF, endPF);
	}

	void BRenderEngineGdiPlus::DrawRect(HDC hdc, const RECT& rc, int size, DWORD penColor, int style/* = penstyle_solid*/)
	{
		Pen pen(penColor, size);
		pen.SetDashStyle(convertStyle(style));

		BCanvas* canvas = BRenderCanvas::GetInstance()->GetDCCanvas(hdc);
		assert(canvas);
		Graphics grap(canvas->GetCanvas());
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
		BCanvas* canvas = BRenderCanvas::GetInstance()->GetDCCanvas(hdc);
		assert(canvas);
		Graphics grap(canvas->GetCanvas());
		grap.SetSmoothingMode(SmoothingModeAntiAlias);
		grap.DrawPath(&pen, pPath);
		delete pPath;
	}

	void BRenderEngineGdiPlus::DrawText(HDC hdc, const RECT& rc, const TextDescription& textDesc)
	{
		BCanvas* canvas = BRenderCanvas::GetInstance()->GetDCCanvas(hdc);
		assert(canvas);
		Graphics grap(canvas->GetCanvas());
		grap.SetSmoothingMode(SmoothingModeAntiAlias);
		grap.SetTextRenderingHint(TextRenderingHintAntiAlias);
		if (textDesc.bGlow)
		{
			drawGlowText(grap, rc, textDesc);
			return;
		}

		if (textDesc.bStroke)
		{
			drawStrokeText(grap, rc, textDesc);
			return;
		}

		bstring strfamily(_T("Î¢ÈíÑÅºÚ"));
		if (!textDesc.fontFamily.empty())
			strfamily = textDesc.fontFamily;
		FontFamily fontFamily(strfamily.c_str());
		StringFormat stringFormat;
		stringFormat.SetAlignment(convertAlignment(textDesc.align));
		stringFormat.SetLineAlignment(convertLineAlignment(textDesc.align));
		stringFormat.SetFormatFlags(textDesc.formatFlags);

		RectF rcf(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
		Gdiplus::Font font(&fontFamily, textDesc.fontSize, textDesc.style, UnitPixel);
		SolidBrush solidBrush(textDesc.textColor);
		grap.DrawString(textDesc.content.c_str(), -1, &font, rcf, &stringFormat, &solidBrush);
	}

	void BRenderEngineGdiPlus::DrawImage(HDC hdc, const ImageDescription& imageDesc)
	{
		Image image(imageDesc.imageFile.c_str());
		Image* realImage = NULL;
		if (imageDesc.bScale)
		{
			SIZE szImage = {imageDesc.rcSrc.right - imageDesc.rcSrc.left, imageDesc.rcSrc.bottom - imageDesc.rcSrc.top};
			realImage = BRenderEngineAssist::genScaleImage(imageDesc.imageFile.c_str(), szImage, imageDesc.rcCorner);
		}
		else
		{
			realImage = image.Clone();
		}

		BCanvas* canvas = BRenderCanvas::GetInstance()->GetDCCanvas(hdc);
		assert(canvas);
		Graphics grap(canvas->GetCanvas());

		Gdiplus::RectF rcfDst(imageDesc.rcPaint.left, imageDesc.rcPaint.top, imageDesc.rcPaint.right - imageDesc.rcPaint.left, imageDesc.rcPaint.bottom - imageDesc.rcPaint.top);
		rcfDst.Width = min(realImage->GetWidth(), rcfDst.Width);
		rcfDst.Height = min(realImage->GetHeight(), rcfDst.Height);

		Gdiplus::RectF rcfPaint(imageDesc.rcPaint.left, imageDesc.rcPaint.top, imageDesc.rcPaint.right - imageDesc.rcPaint.left, imageDesc.rcPaint.bottom - imageDesc.rcPaint.top);
		Gdiplus::RectF rcfImage(imageDesc.rcSrc.left, imageDesc.rcSrc.top, imageDesc.rcSrc.left + realImage->GetWidth(), imageDesc.rcSrc.top + realImage->GetHeight());
		rcfPaint.Intersect(rcfImage);
		rcfDst.Intersect(rcfImage);
		grap.DrawImage(realImage, rcfDst, rcfPaint.GetLeft() - rcfImage.GetLeft(), rcfPaint.GetTop() - rcfImage.GetTop(), rcfPaint.GetRight() - rcfPaint.GetLeft(), rcfPaint.GetBottom() - rcfPaint.GetTop(), UnitPixel);
		delete realImage;
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

		BCanvas* canvas = BRenderCanvas::GetInstance()->GetDCCanvas(hdc);
		assert(canvas);
		Graphics grap(canvas->GetCanvas());
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

		BCanvas* canvas = BRenderCanvas::GetInstance()->GetDCCanvas(hdc);
		assert(canvas);
		Graphics grap(canvas->GetCanvas());
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

	void BRenderEngineGdiPlus::DrawCanvas(BCanvas* canvas, const RECT& rc)
	{
		HDC dc = canvas->GetDC();
		Graphics grap(dc);
		CachedBitmap cacheBmp(canvas->GetCanvas(), &grap);
		grap.SetClip(Rect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top));
		grap.DrawCachedBitmap(&cacheBmp, 0, 0);
	}

	SIZE BRenderEngineGdiPlus::GetTextSize(const bstring text, const bstring& fontFamily, const DWORD fontSize, UINT style)
	{
		bstring strfamily(_T("Î¢ÈíÑÅºÚ"));
		if (!fontFamily.empty())
			strfamily = fontFamily;
		FontFamily family(strfamily.c_str());
		StringFormat stringFormat;
		stringFormat.SetFormatFlags(StringFormatFlagsNoWrap);

		PointF point(0, 0);
		GraphicsPath path;
		path.AddString(text.c_str(), text.length(), &family, style, fontSize, point, &stringFormat);
		Rect rcText;
		path.GetBounds(&rcText);
		
		SIZE szText = { rcText.Width, rcText.Height };
		return szText;
	}
}