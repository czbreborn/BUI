#ifndef __BUIWIDGET_H__
#define __BUIWIDGET_H__

#pragma once

namespace BUI {
	typedef BUIWidget* (CALLBACK *FINDWIDGET)(BUIWidget*, LPVOID);

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
		// ��ʾ��Ϣ
		virtual LPCTSTR GetToolTip();
		virtual void SetToolTip(LPCTSTR tip);

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

		// �������
		virtual void Paint(HDC hDC, const RECT& rcPaint);
		virtual void DoPaint(HDC hDC, const RECT& rcPaint);
		virtual void PaintBkColor(HDC hDC);
		virtual void PaintBkImage(HDC hDC);
		virtual void PaintStatusImage(HDC hDC);
		virtual void PaintText(HDC hDC);
		virtual void PaintBorder(HDC hDC);

		void Invalidate();

		// �ؼ��������
		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		
		// �ؼ��¼�����
		virtual void Event(TEventUI& event);

		// �ؼ�����
		virtual BUIManager* GetManager() const;
		virtual void SetManager(BUIManager* uiManager, BUIWidget* parent);
		virtual BUIWidget* GetParent() const;

		// ���ҿؼ�
		virtual BUIWidget* FindControl(FINDWIDGET Proc, LPVOID pData, UINT uFlags);

		// �ؼ�״̬
		virtual bool IsVisible() const;
		virtual bool IsEnabled() const;
		virtual bool IsFocused() const;
		virtual void SetVisible(bool bVisible = true);
		virtual void SetEnabled(bool bEnable = true);
		virtual	void SetFocus();

	private:
		BUIManager*	m_pUIManager;
		BUIWidget*	m_parent;
		bstring m_widgetName;

		bstring m_strText;
		bstring m_toolTip;

		DWORD m_bkColor;
		DWORD m_bkColor2;
		bstring m_imageFileName;

		RECT m_rcItem;
		SIZE m_xy;
		RECT m_rcPaint;
		bool m_bVisible;
		bool m_bEnabled;
		bool m_bFocused;
	};
}
#endif