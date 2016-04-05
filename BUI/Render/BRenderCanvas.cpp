#include "stdafx.h"

namespace BUI {
	BCanvas::BCanvas(HDC hdc, const RECT& rc)
	{
		m_hdc = hdc;
		m_rect = rc;
		m_bmp = new Bitmap(rc.right - rc.left, rc.bottom - rc.top);
	}

	BCanvas::~BCanvas()
	{
		delete m_bmp;
	}

	HDC	BCanvas::GetDC()
	{
		return m_hdc;
	}

	Bitmap* BCanvas::GetCanvas()
	{
		return m_bmp;
	}

	RECT BCanvas::GetRect()
	{
		return m_rect;
	}

	BRenderCanvas BRenderCanvas::s_renderCanvas;
	BRenderCanvas::BRenderCanvas(void)
	{
	}

	BRenderCanvas::~BRenderCanvas(void)
	{
		for (DCCanvasIt it = m_dcCanvas.begin(); it != m_dcCanvas.end(); it++)
		{
			BCanvas* canvas = it->second;
			delete canvas;
			canvas = NULL;
		}
		m_dcCanvas.clear();
	}

	BRenderCanvas* BRenderCanvas::GetInstance()
	{
		return &s_renderCanvas;
	}

	BCanvas* BRenderCanvas::GenDCCanvas(HDC hdc, const RECT& rc)
	{
		BCanvas* canvas = new BCanvas(hdc, rc);
		DelDCCanvas(hdc);

		m_dcCanvas.insert(make_pair(hdc, canvas));
		return canvas;
	}

	void BRenderCanvas::DelDCCanvas(HDC hdc)
	{
		DCCanvasIt it = m_dcCanvas.find(hdc);
		if (it != m_dcCanvas.end())
		{
			BCanvas* canvas = it->second;
			m_dcCanvas.erase(it);
			delete canvas;
		}
	}

	BCanvas* BRenderCanvas::GetDCCanvas(HDC hdc)
	{
		BCanvas* canvas = NULL;
		DCCanvasIt it = m_dcCanvas.find(hdc);
		if (it != m_dcCanvas.end())
		{
			canvas = it->second;
		}

		return canvas;
	}
}