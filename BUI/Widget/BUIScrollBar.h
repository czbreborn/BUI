#ifndef __BUISCROLLBAR_H__
#define __BUISCROLLBAR_H__

#pragma once

namespace BUI {
	enum 
	{
		scrollbar_defaultsize = 16,
		scrollbar_defaulttimer = 20,
	};

	class BUIContainer;
	class BUIScrollBar : public BUIWidget
	{
	public:
		DEFINE_CREATEWIDGET(BUIScrollBar)
		DEFINE_WIDGETTYPE(BUIScrollBar)

	public:
		BUIScrollBar(void);
		virtual ~BUIScrollBar(void);

		BUIContainer* GetOwner() const;
		void SetOwner(BUIContainer* pOwner);

		bool IsHorizontal();
		void SetHorizontal(bool horizontal = true);
		int GetScrollRange() const;
		void SetScrollRange(int nRange);
		int GetScrollPos() const;
		void SetScrollPos(int nPos);
		int GetLineSize() const;
		void SetLineSize(int nSize);

		bool GetShowFrontButton();
		void SetShowFrontButton(bool bShow);
		DWORD GetFrontButtonColor() const;
		void SetFrontButtonColor(DWORD color);
		LPCTSTR GetFrontButtonNormalImage();
		void SetFrontButtonNormalImage(LPCTSTR image);
		LPCTSTR GetFrontButtonHotImage();
		void SetFrontButtonHotImage(LPCTSTR image);
		LPCTSTR GetFrontButtonPushedImage();
		void SetFrontButtonPushedImage(LPCTSTR image);
		LPCTSTR GetFrontButtonDisabledImage();
		void SetFrontButtonDisabledImage(LPCTSTR image);

		bool GetShowBackButton();
		void SetShowBackButton(bool bShow);
		DWORD GetBackButtonColor() const;
		void SetBackButtonColor(DWORD color);
		LPCTSTR GetBackButtonNormalImage();
		void SetBackButtonNormalImage(LPCTSTR image);
		LPCTSTR GetBackButtonHotImage();
		void SetBackButtonHotImage(LPCTSTR image);
		LPCTSTR GetBackButtonPushedImage();
		void SetBackButtonPushedImage(LPCTSTR image);
		LPCTSTR GetBackButtonDisabledImage();
		void SetBackButtonDisabledImage(LPCTSTR image);

		DWORD GetThumbColor() const;
		void SetThumbColor(DWORD color);
		LPCTSTR GetThumbNormalImage();
		void SetThumbNormalImage(LPCTSTR image);
		LPCTSTR GetThumbHotImage();
		void SetThumbHotImage(LPCTSTR image);
		LPCTSTR GetThumbPushedImage();
		void SetThumbPushedImage(LPCTSTR image);
		LPCTSTR GetThumbDisabledImage();
		void SetThumbDisabledImage(LPCTSTR image);

		LPCTSTR GetRailNormalImage();
		void SetRailNormalImage(LPCTSTR image);
		LPCTSTR GetRailHotImage();
		void SetRailHotImage(LPCTSTR image);
		LPCTSTR GetRailPushedImage();
		void SetRailPushedImage(LPCTSTR image);
		LPCTSTR GetRailDisabledImage();
		void SetRailDisabledImage(LPCTSTR image);

		LPCTSTR GetBkNormalImage();
		void SetBkNormalImage(LPCTSTR image);
		LPCTSTR GetBkHotImage();
		void SetBkHotImage(LPCTSTR image);
		LPCTSTR GetBkPushedImage();
		void SetBkPushedImage(LPCTSTR image);
		LPCTSTR GetBkDisabledImage();
		void SetBkDisabledImage(LPCTSTR image);

		void SetPos(RECT rc);
		void Event(TEventUI& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void DoPaint(HDC hDC, const RECT& rcPaint);

		void PaintBk(HDC hDC);
		void PaintFrontButton(HDC hDC);
		void PaintBackButton(HDC hDC);
		void PaintThumb(HDC hDC);
		void PaintRail(HDC hDC);

	private:
		void SetFrontButtonPos(const RECT& rc, int width);
		void SetBackButtonPos(const RECT& rc, int width);

		void UpdateThumbState();
		void UpdateButtonState();

	private:
		bool m_bHorizontal;
		int m_nRange;
		int m_nScrollPos;
		int m_nLineSize;
		BUIContainer* m_pOwner;

		bool m_showFrontButton;
		RECT m_rcFrontButton;
		UINT m_frontButtonState;
		DWORD m_frontButtonColor;
		bstring m_frontButtonNormalImage;
		bstring m_frontButtonHotImage;
		bstring m_frontButtonPushedImage;
		bstring m_frontButtonDisabledImage;

		bool m_showBackButton;
		RECT m_rcBackButton;
		UINT m_backButtonState;
		DWORD m_backButtonColor;
		bstring m_backButtonNormalImage;
		bstring m_backButtonHotImage;
		bstring m_backButtonPushedImage;
		bstring m_backButtonDisabledImage;

		bstring m_bkNormalImage;
		bstring m_bkHotImage;
		bstring m_bkPushedImage;
		bstring m_bkDisabledImage;

		RECT m_rcThumb;
		UINT m_uThumbState;
		DWORD m_thumbColor;
		bstring m_thumbNormalImage;
		bstring m_thumbHotImage;
		bstring m_thumbPushedImage;
		bstring m_thumbDisabledImage;

		bstring m_railNormalImage;
		bstring m_railHotImage;
		bstring m_railPushedImage;
		bstring m_railDisabledImage;
	};
}
#endif