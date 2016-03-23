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
		// ���͡�ʶ�����
		virtual bstring GetName();
		virtual void SetName(LPCTSTR name);

		virtual LPCTSTR GetType();
		virtual LPVOID GetInterface(LPCTSTR name);

		// �ı����
		virtual LPCTSTR GetText();
		virtual void SetText(LPCTSTR text);

		// ͼ�����
		DWORD GetBkColor();
		void SetBkColor(DWORD bkColor);
		DWORD GetBkColor2();
		void SetBkColor2(DWORD bkColor);
		LPCTSTR GetBkImage();
		void SetBkImage(LPCTSTR pstrImage);

		// λ�����
		virtual const RECT& GetPos();
		virtual RECT GetClientPos();

		virtual void SetPos(RECT rc);
		virtual int GetWidth();
		virtual int GetHeight();
		virtual int GetX();
		virtual int GetY();

		// ��ʾ��Ϣ
		virtual LPCTSTR GetToolTip();
		virtual void SetToolTip(LPCTSTR tip);

		// �������
		virtual void Paint(HDC hDC, const RECT& rcPaint);
		virtual void DoPaint(HDC hDC, const RECT& rcPaint);
		virtual void PaintBkColor(HDC hDC);
		virtual void PaintBkImage(HDC hDC);
		virtual void PaintStatusImage(HDC hDC);
		virtual void PaintText(HDC hDC);
		virtual void PaintBorder(HDC hDC);

		// �ؼ��������
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