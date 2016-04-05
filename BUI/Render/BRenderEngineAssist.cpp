#include "stdafx.h"

namespace BUI {
	BRenderEngineAssist::BRenderEngineAssist(void)
	{
	}

	BRenderEngineAssist::~BRenderEngineAssist(void)
	{
	}

	Image* BRenderEngineAssist::genScaleImage(LPCTSTR imageFilePath, const SIZE& szImage, const RECT& rcCorner)
	{
		Image image(imageFilePath);
		Bitmap bmp(szImage.cx, szImage.cy);
		Graphics grap(&bmp);
		// 绘制上部
		grap.DrawImage(&image, RectF(0, 0, bmp.GetWidth(), bmp.GetHeight()), 0, 0, rcCorner.left, rcCorner.top, UnitPixel);
		grap.DrawImage(&image, RectF(0, 0, bmp.GetWidth(), bmp.GetHeight()), rcCorner.left, 0, image.GetWidth() - rcCorner.left - rcCorner.right, rcCorner.top, UnitPixel);
		grap.DrawImage(&image, RectF(0, 0, bmp.GetWidth(), bmp.GetHeight()), image.GetWidth() - rcCorner.right, 0, rcCorner.right, rcCorner.top, UnitPixel);
		
		// 绘制中部
		grap.DrawImage(&image, RectF(0, 0, bmp.GetWidth(), bmp.GetHeight()), 0, rcCorner.top, rcCorner.left, image.GetHeight() - rcCorner.top - rcCorner.bottom, UnitPixel);
		grap.DrawImage(&image, RectF(0, 0, bmp.GetWidth(), bmp.GetHeight()), rcCorner.left, rcCorner.top, image.GetWidth() - rcCorner.left - rcCorner.right, image.GetHeight() - rcCorner.top - rcCorner.bottom, UnitPixel);
		grap.DrawImage(&image, RectF(0, 0, bmp.GetWidth(), bmp.GetHeight()), image.GetWidth() - rcCorner.right, rcCorner.top, rcCorner.right, image.GetHeight() - rcCorner.top - rcCorner.bottom, UnitPixel);
		
		// 绘制下部
		grap.DrawImage(&image, RectF(0, 0, bmp.GetWidth(), bmp.GetHeight()), 0, image.GetHeight() - rcCorner.bottom, rcCorner.left, rcCorner.bottom, UnitPixel);
		grap.DrawImage(&image, RectF(0, 0, bmp.GetWidth(), bmp.GetHeight()), rcCorner.left, image.GetHeight() - rcCorner.bottom, image.GetWidth() - rcCorner.left - rcCorner.right, rcCorner.bottom, UnitPixel);
		grap.DrawImage(&image, RectF(0, 0, bmp.GetWidth(), bmp.GetHeight()), image.GetWidth() - rcCorner.right, image.GetHeight() - rcCorner.bottom, rcCorner.right, rcCorner.bottom, UnitPixel);

		return bmp.Clone(0, 0, bmp.GetWidth(), bmp.GetHeight(), PixelFormat32bppARGB);
	}
}