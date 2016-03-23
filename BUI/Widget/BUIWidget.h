#ifndef __BUIWIDGET_H__
#define __BUIWIDGET_H__

#pragma once

namespace BUI {
	class BUI_API BUIWidget
	{
	public:
		BUIWidget();
		virtual ~BUIWidget();

	public:
		// 类型、识别相关
		virtual bstring GetName();
		virtual void SetName(LPCTSTR name);

		virtual LPCTSTR GetType();
		virtual LPVOID GetInterface(LPCTSTR name);

		// 文本相关
		virtual LPCTSTR GetText();
		virtual void SetText(LPCTSTR text);

		// 图形相关
		DWORD GetBkColor();
		void SetBkColor(DWORD bkColor);
		DWORD GetBkColor2();
		void SetBkColor2(DWORD bkColor);
		LPCTSTR GetBkImage();
		void SetBkImage(LPCTSTR pstrImage);

		// 位置相关
		virtual const RECT& GetPos();
		virtual RECT GetClientPos();

		virtual void SetPos(RECT rc);
		virtual int GetWidth();
		virtual int GetHeight();
		virtual int GetX();
		virtual int GetY();

		// 提示信息
		virtual LPCTSTR GetToolTip();
		virtual void SetToolTip(LPCTSTR tip);

		// 绘制相关
		virtual void Paint(HDC hDC, const RECT& rcPaint);
		virtual void DoPaint(HDC hDC, const RECT& rcPaint);
		virtual void PaintBkColor(HDC hDC);
		virtual void PaintBkImage(HDC hDC);
		virtual void PaintStatusImage(HDC hDC);
		virtual void PaintText(HDC hDC);
		virtual void PaintBorder(HDC hDC);

		// 控件属性相关
		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	private:
		bstring m_widgetName;

		bstring m_strText;

		DWORD m_bkColor;
		DWORD m_bkColor2;
		bstring m_imageFileName;

		RECT m_rcItem;
		SIZE m_xy;

		bstring m_toolTip;

		RECT m_rcPaint;
	};
}
#endif