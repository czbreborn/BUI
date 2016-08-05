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
		// �������
		void SetPadding(const LONG& padding);
		void SetPadding(const SIZE& szPadding);
		void SetPadding(const RECT& rcPadding);
		RECT GetPadding() const;

		// �����������
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
		void onChar(TCHAR chKey);

		LONG locateCaretXPos(LONG mouseXPos);
		SIZE getTextSize(const bstring text);
		RECT getContentRect();

	private:
		bool m_caretState;
		RECT m_rcPadding;
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

		UINT m_caretPlace;			// λ�ڱ༭���Ǹ��ַ�����
		UINT m_beginDrawPlace;		// ��ʼ���Ƶ��ַ�λ��
		bstring m_drawString;		// ���Ƶ��ַ�
		
		bstring m_tipsString;		// ��ʾ�ַ�
	};
}

#endif