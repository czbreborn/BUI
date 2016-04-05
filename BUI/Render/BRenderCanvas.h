#ifndef __BRENDERCANVAS_H__
#define __BRENDERCANVAS_H__

#pragma once

namespace BUI {
	typedef map<HDC, BCanvas*> DCCanvas;
	typedef DCCanvas::iterator DCCanvasIt;

	class BCanvas
	{
	public:
		BCanvas(HDC hdc, const RECT& rc);
		~BCanvas();

	public:
		HDC	GetDC();
		Bitmap* GetCanvas();
		RECT GetRect();

	private:
		HDC m_hdc;
		RECT m_rect;
		Bitmap* m_bmp;
	};

	class BRenderCanvas
	{
	protected:
		BRenderCanvas(void);
		~BRenderCanvas(void);

	public:
		static BRenderCanvas* GetInstance();

	public:
		BCanvas* GenDCCanvas(HDC hdc, const RECT& rc);
		void DelDCCanvas(HDC hdc);
		BCanvas* GetDCCanvas(HDC hdc);

	private:
		static BRenderCanvas s_renderCanvas;
		DCCanvas	m_dcCanvas;
	};
}

#endif