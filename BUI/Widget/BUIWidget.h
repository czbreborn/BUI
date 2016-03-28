#ifndef __BUIWIDGET_H__
#define __BUIWIDGET_H__

#pragma once

namespace BUI {
	typedef BUIWidget* (CALLBACK *FINDWIDGET)(BUIWidget*, LPVOID);

	class BUI_API BUIWidget
	{
	public:
		DEFINE_CREATEWIDGET(BUIWidget)

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

		// �߿����
		DWORD GetBorderColor() const;
		void SetBorderColor(DWORD borderColor);
		DWORD GetFocusBorderColor() const;
		void SetFocusBorderColor(DWORD focusBorderColor);
		SIZE GetBorderRound() const;
		void SetBorderRound(SIZE cxyRound);
		RECT GetBorderSize() const;
		void SetBorderSize(RECT rc);
		void SetBorderSize(int size);
		int GetBorderStyle() const;
		void SetBorderStyle(int style);

		// λ�����
		virtual const RECT& GetPos();
		virtual RECT GetClientPos();
		virtual void SetPos(RECT rc);
		virtual int GetWidth();
		virtual int GetHeight();
		virtual int GetX();
		virtual int GetY();
		virtual RECT GetPadding() const;
		virtual void SetPadding(RECT rcPadding); 		// ������߾࣬���ϲ㴰�ڻ���
		virtual SIZE GetFixedXY() const;         		// ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
		virtual void SetFixedXY(SIZE szXY);      		// ��floatΪtrueʱ��Ч
		virtual int GetFixedWidth() const;       		// ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
		virtual void SetFixedWidth(int cx);      		// Ԥ��Ĳο�ֵ
		virtual int GetFixedHeight() const;      		// ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
		virtual void SetFixedHeight(int cy);     		// Ԥ��Ĳο�ֵ
		virtual SIZE EstimateSize(SIZE szAvailable);	// Ԥ���ؼ���С

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

	protected:
		BUIManager*	m_pUIManager;
		BUIWidget*	m_parent;
		bstring m_widgetName;

		bstring m_strText;
		bstring m_toolTip;

		DWORD m_bkColor;
		DWORD m_bkColor2;
		DWORD m_borderColor;
		DWORD m_focusBorderColor;
		int m_borderStyle;
		SIZE m_borderRound;
		RECT m_borderSize;
		bstring m_imageFileName;

		SIZE m_cXY;
		SIZE m_cxyFixed;
		RECT m_rcPadding;
		RECT m_rcItem;
		RECT m_rcPaint;

		bool m_bVisible;
		bool m_bEnabled;
		bool m_bFocused;
	};
}
#endif