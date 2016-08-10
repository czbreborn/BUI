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

	enum TEXTALIGNMENT
	{
		textalignment_left = 0x01,		 // 1
		textalignment_right = 0x02,		 // 2
		textalignment_center = 0x04,	 // 4
		textalignment_top = 0x10,		 // 8
		textalignment_vcenter = 0x20,	 // 16
		textalignment_bottom = 0x40,	 // 32        
	};

	enum CUSTOMCOLOR {
		customcolor_black = 0xff000000,
		customcolor_white = 0xffffffff,
		customcolor_red = 0xffff0000,
		customcolor_green = 0xff00ff00,
		customcolor_blue = 0xff0000ff,

	};

	#define ALIGNMENTDEFAULT (textalignment_left | textalignment_vcenter)
	#define ALIGNMENTMIDDLE (textalignment_center | textalignment_vcenter)
	#define ALIGNMENTLEFTTOP (textalignment_left | textalignment_top)

	typedef struct tagTextDescription
	{
		bstring content;
		DWORD textColor;
		DWORD textColor1;
		DWORD fontSize;
		bstring fontFamily;
		UINT style;
		UINT align;
		UINT formatFlags;
		bool bGlow;				// �Ƿ񷢹�
		DWORD glowColor;		// ������ɫ
		bool bStroke;			// �Ƿ����
		DWORD singleColor;		// ��ߵĵ�����ɫ
		DWORD doubleColor;		// ��ߵ�˫����ɫ
		UINT  selectedBegin;	// ѡ�����ݵ���ʼλ��
		UINT  selectedCount;	// ѡ�����ݵĽ���λ��
		DWORD selectedBkColor;	// ѡ�����ݵı���ɫ
		DWORD contentBkColor;	// ���ֵı���ɫ������ȡ��ѡ�����ݵı���ɫ��
		tagTextDescription() 
		{
			textColor = customcolor_black;
			textColor1 = customcolor_black;
			fontSize = 12;
			style = FontStyleRegular;
			align = ALIGNMENTDEFAULT;
			formatFlags = StringFormatFlagsNoWrap;
			bGlow = false;
			glowColor = customcolor_green;
			bStroke = false;
			singleColor = customcolor_green;
			doubleColor = customcolor_blue;
			selectedBegin = -1;
			selectedCount = 0;
			selectedBkColor = 0x663399ff;
		}
	} TextDescription;

	typedef struct tagImageDescription
	{
		tagImageDescription()
		{
			ZeroMemory(&rcSrc, sizeof(RECT));
			ZeroMemory(&rcCorner, sizeof(RECT));
			ZeroMemory(&rcPaint, sizeof(RECT));
			bScale = true;
		}
		bstring imageFile;		// ͼ���ļ���
		RECT rcSrc;				// ͼ����������
		RECT rcCorner;			// ͼ��߽Ǵ�С
		RECT rcPaint;			// ���Ƶ�����
		bool bScale;			// �Ƿ�����
	} ImageDescription;

	class BCanvas;
	class BIRenderEngine
	{
	public:
		virtual ~BIRenderEngine() = 0 {}

	public:
		virtual void DrawLine(HDC hdc, const POINT& startP, const POINT& endP, int size, DWORD penColor, int style = penstyle_solid) = 0;
		virtual void DrawRect(HDC hdc, const RECT& rc, int size, DWORD penColor, int style = penstyle_solid) = 0;
		virtual void DrawRect(HDC hdc, const RECT& rc, RECT borderSize, DWORD penColor, int style = penstyle_solid) = 0;
		virtual void DrawRoundRect(HDC hdc, const RECT& rc, int size, int width, int height, DWORD penColor, int style = penstyle_solid) = 0;
		virtual void DrawText(HDC hdc, const RectF& rc, const TextDescription& textDesc) = 0;
		virtual void DrawImage(HDC hdc, const ImageDescription& imageDesc) = 0;
		virtual void DrawGradient(HDC hdc, const RECT& rc, DWORD dwColor1, DWORD dwColor2) = 0;
		virtual void DrawRoundGradient(HDC hdc, const RECT& rc, int width, int height, DWORD dwColor1, DWORD dwColor2) = 0;
		virtual bool DrawWindowRgn(HWND hwnd, const RECT& rc) = 0;
		virtual bool DrawWindowRoundRgn(HWND hwnd, const RECT& rc, int width, int height) = 0;
		virtual void DrawCanvas(BCanvas* canvas, const RECT& rc) = 0;

		virtual SizeF GetTextSize(HDC hdc, const RectF& rc, const TextDescription& textDesc) = 0;
		virtual SizeF GetTextSize(const bstring text, const bstring& fontFamily, const DWORD fontSize, UINT style) = 0;
	};
}

#endif