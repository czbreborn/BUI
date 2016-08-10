#ifndef __BUIEDIT_H__
#define __BUIEDIT_H__

#pragma once

namespace BUI{
	class BUILabel;
	class BUI_API BUIEdit :	public BUILabel
	{
	public:
		DEFINE_WIDGETTYPE(BUIEdit)
		DEFINE_CREATEWIDGET(BUIEdit)

	public:
		BUIEdit(void);
		virtual ~BUIEdit(void);

	public:
		// 文字相关限制
		void SetMaxChar(UINT uMax);
		UINT GetMaxChar();
		void SetReadOnly(bool bReadOnly);
		bool IsReadOnly() const;
		void SetNumberOnly(bool bNumberOnly);
		bool IsNumberOnly() const;
		void SetPasswordMode(bool bPasswordMode);
		bool IsPasswordMode() const;
		void SetPasswordChar(TCHAR passwordChar);
		TCHAR GetPasswordChar() const;

		LPCTSTR GetNormalImage();
		void SetNormalImage(LPCTSTR imageName);
		LPCTSTR GetHotImage();
		void SetHotImage(LPCTSTR imageName);
		LPCTSTR GetFocusedImage();
		void SetFocusedImage(LPCTSTR imageName);
		LPCTSTR GetDisabledImage();
		void SetDisabledImage(LPCTSTR imageName);
		void SetNativeEditBkColor(DWORD bkColor);
		DWORD GetNativeEditBkColor() const;

	public:
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void Event(TEventUI& event);

		void PaintStatusImage(HDC hDC);
		void PaintText(HDC hDC);

	private:
		void onMouseMove(LONG mouseXPos);
		void onKeyDown(TCHAR chKey);
		void onChar(TCHAR chKey);

		UINT locateCaretPlace(LONG mouseXPos);
		SizeF getTextSize(const bstring text);
		RECT getContentRect();

	private: 
		bool m_mouseState;
		bool m_caretState;
		UINT m_uMaxChar;
		bool m_readOnly;
		bool m_passwordMode;
		bool m_numberOnly;
		TCHAR m_passwordChar;

		UINT m_buttonState;
		bstring m_normalImage;
		bstring m_hotImage;
		bstring m_focusedImage;
		bstring m_disabledImage;
		DWORD m_editBkColor;

		UINT m_selectedBeginPalce;	// 选中内容的其实位置
		UINT m_selectedEndPlace;	// 选中内容的结束位置
		UINT m_caretPlace;			// 位于编辑框那个字符后面
		UINT m_beginDrawPlace;		// 开始绘制的字符位置
		
		RectF m_rcSelectString;		// 选中文字对应的绘制窗口
		bstring m_selectString;		// 选中的文字

		bstring m_tipsString;		// 提示字符
	};
}

#endif