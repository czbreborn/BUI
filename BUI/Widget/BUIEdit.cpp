#include "stdafx.h"

namespace BUI {
	IMPLEMENT_WIDGETTYPE(BUIEdit, BUILabel)
	IMPLEMENT_CREATEWIDGET(BUIEdit)

	BUIEdit::BUIEdit(void)
	: m_caretState(false),
	m_uMaxChar(0xFF),
	m_readOnly(false),
	m_numberOnly(false),
	m_passwordMode(false),
	m_passwordChar(_T('*')),
	m_normalImage(k_empty_string),
	m_hotImage(k_empty_string),
	m_focusedImage(k_empty_string),
	m_disabledImage(k_empty_string),
	m_editBkColor(customcolor_white),
	m_caretPlace(0),
	m_beginDrawPlace(0),
	m_drawString(k_empty_string),
	m_tipsString(k_empty_string)
	{
		::ZeroMemory(&m_rcPadding, sizeof(m_rcPadding));
	}

	BUIEdit::~BUIEdit(void)
	{
	}

	void BUIEdit::SetPadding(const LONG& padding)
	{
		RECT rcPadding = {padding, padding, padding, padding};
		SetPadding(rcPadding);
	}

	void BUIEdit::SetPadding(const SIZE& szPadding)
	{
		RECT rcPadding = {szPadding.cx, szPadding.cy, szPadding.cx, szPadding.cy};
		SetPadding(rcPadding);
	}

	void BUIEdit::SetPadding(const RECT& rcPadding)
	{
		m_rcPadding = rcPadding;
	}

	RECT BUIEdit::GetPadding() const
	{
		return m_rcPadding;
	}

	void BUIEdit::SetMaxChar(UINT uMax)
	{
		m_uMaxChar = uMax;
	}

	UINT BUIEdit::GetMaxChar()
	{
		return m_uMaxChar;
	}

	void BUIEdit::SetReadOnly(bool bReadOnly)
	{
		m_readOnly = bReadOnly;
	}

	bool BUIEdit::IsReadOnly() const
	{
		return m_readOnly;
	}

	void BUIEdit::SetNumberOnly(bool bNumberOnly)
	{
		m_numberOnly = bNumberOnly;
	}

	bool BUIEdit::IsNumberOnly() const
	{
		return m_numberOnly;
	}

	void BUIEdit::SetPasswordMode(bool bPasswordMode)
	{
		m_passwordMode = bPasswordMode;
	}

	bool BUIEdit::IsPasswordMode() const
	{
		return m_passwordMode;
	}

	void BUIEdit::SetPasswordChar(TCHAR passwordChar)
	{
		m_passwordChar = passwordChar;
	}

	TCHAR BUIEdit::GetPasswordChar() const
	{
		return m_passwordChar;
	}

	LPCTSTR BUIEdit::GetNormalImage()
	{
		return m_normalImage.c_str();
	}

	void BUIEdit::SetNormalImage(LPCTSTR imageName)
	{
		m_normalImage = imageName;
	}

	LPCTSTR BUIEdit::GetHotImage()
	{
		return m_hotImage.c_str();
	}

	void BUIEdit::SetHotImage(LPCTSTR imageName)
	{
		m_hotImage = imageName;
	}

	LPCTSTR BUIEdit::GetFocusedImage()
	{
		return m_focusedImage.c_str();
	}

	void BUIEdit::SetFocusedImage(LPCTSTR imageName)
	{
		m_focusedImage = imageName;
	}

	LPCTSTR BUIEdit::GetDisabledImage()
	{
		return m_disabledImage.c_str();
	}

	void BUIEdit::SetDisabledImage(LPCTSTR imageName)
	{
		m_disabledImage = imageName;
	}

	void BUIEdit::SetNativeEditBkColor(DWORD bkColor)
	{
		m_editBkColor = bkColor;
	}

	DWORD BUIEdit::GetNativeEditBkColor() const
	{
		return m_editBkColor;
	}

	void BUIEdit::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if (_tcscmp(pstrName, _T("readonly")) == 0) {
			SetReadOnly(_tcscmp(pstrValue, _T("true")) == 0);
		} else if (_tcscmp(pstrName, _T("numberonly")) == 0) {
			SetNumberOnly(_tcscmp(pstrValue, _T("true")) == 0);
		} else if (_tcscmp(pstrName, _T("password")) == 0) {
			SetPasswordMode(_tcscmp(pstrValue, _T("true")) == 0);
		} else if (_tcscmp(pstrName, _T("maxchar")) == 0) {
			SetMaxChar(_ttoi(pstrValue));
		} else if ( _tcscmp(pstrName, _T("normalimage")) == 0) {
			SetNormalImage(pstrValue);
		} else if (_tcscmp(pstrName, _T("hotimage")) == 0) {
			SetHotImage(pstrValue);
		} else if (_tcscmp(pstrName, _T("focusedimage")) == 0) {
			SetFocusedImage(pstrValue);
		} else if (_tcscmp(pstrName, _T("disabledimage")) == 0) {
			SetDisabledImage(pstrValue);
		} else if (_tcscmp(pstrName, _T("nativebkcolor")) == 0) {
			if (*pstrValue == _T('#')) 
				pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetNativeEditBkColor(clrColor);
		}

		BUILabel::SetAttribute(pstrName, pstrValue);
	}

	void BUIEdit::Event(TEventUI& event)
	{
		if (event.type == uievent_setfocus) {
			m_pUIManager->CreateCaret(1, getContentRect().bottom - getContentRect().top);
			Invalidate();
		}

		if (event.type == uievent_killfocus) {
			m_pUIManager->DestroyCaret();
			Invalidate();
		}

		if (event.type == uievent_buttondown) {
			if (::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled()) {
				m_pUIManager->SetCaretPos(locateCaretXPos(event.ptMouse.x), getContentRect().top);

				if (!m_caretState) {
					m_pUIManager->ShowCaret();
					m_caretState = true;
				}
			} else {
				m_pUIManager->HideCaret();
				m_caretState = false;
			}

			Invalidate();
		}

		if (event.type == uievent_mousemove) {
			
		}

		if (event.type == uievent_char) {
			onChar(event.chKey);
			Invalidate();
		}

		BUILabel::Event(event);
	}

	void BUIEdit::PaintStatusImage(HDC hDC)
	{
		if (IsFocused())
			m_buttonState |= UISTATE_FOCUSED;
		else
			m_buttonState &= ~UISTATE_FOCUSED;

		if (!IsEnabled())
			m_buttonState |= UISTATE_DISABLED;
		else
			m_buttonState &= ~UISTATE_DISABLED;

		bstring filePath = BApplication::GetInstance()->GetApplicationPath();
		if ((m_buttonState & UISTATE_DISABLED) != 0) {
			filePath += m_disabledImage;
		} else if ((m_buttonState & UISTATE_HOT) != 0) {
			filePath += m_hotImage;
		} else if ((m_buttonState & UISTATE_FOCUSED) != 0) {
			filePath += m_focusedImage;
		} else {
			filePath += m_normalImage;	
		}

		ImageDescription imageDesc;
		imageDesc.imageFile = filePath;
		imageDesc.rcSrc = m_rcItem;
		imageDesc.rcPaint = m_rcPaint;
		BRenderEngineManager::GetInstance()->RenderEngine()->DrawImage(hDC, imageDesc);
	}

	void BUIEdit::PaintText(HDC hDC)
	{
		m_textDesc.content = m_strText.substr(m_beginDrawPlace);
		BRenderEngineManager::GetInstance()->RenderEngine()->DrawText(hDC, m_rcPaint, m_textDesc);
	}

	void BUIEdit::onChar(TCHAR chKey)
	{
		if (m_caretState) {
			switch (chKey) {
			case VK_BACK:
				break;

			case VK_DELETE:
				break;

			default:
				if (m_caretPlace == m_strText.length()) {
					m_strText.append(1, chKey);
					m_caretPlace++;
					SIZE szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace));
					if (szText.cx > getContentRect().right - getContentRect().left) {
						m_beginDrawPlace++;
					}
				} else {
					m_strText.insert(m_caretPlace, 1, chKey);
					m_caretPlace++;
				}

				SIZE szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace));
				if (szText.cx < getContentRect().right) {
					m_pUIManager->SetCaretPos(getContentRect().left + szText.cx, getContentRect().top);
				} else {
					m_pUIManager->SetCaretPos(getContentRect().right, getContentRect().top);
				}
				break;
			}
		}
	}

	LONG BUIEdit::locateCaretXPos(LONG mouseXPos)
	{
		LONG caretXPos = m_rcItem.left + m_rcPadding.left;
		if (m_strText.length() == 0) {
			return caretXPos;
		}

		SIZE szText = getTextSize(m_strText);
		// Êó±êÔÚ×î×ó²à
		if (szText.cx < m_rcItem.right - m_rcItem.left - m_rcPadding.left - m_rcPadding.right &&
			mouseXPos < caretXPos) {
			m_caretPlace = m_beginDrawPlace;
			return caretXPos;
		} else {
			LONG lastPointx  = caretXPos;
			LONG leftTextLength = m_strText.length() - m_beginDrawPlace;

			LONG low = 0;
			LONG hight = leftTextLength - 1;
			while (low <= hight) {
				LONG mid = (low + hight) / 2;
				bstring leftString = m_strText.substr(m_beginDrawPlace, mid);
				szText = getTextSize(leftString);
				caretXPos = m_rcItem.left + m_rcPadding.left + szText.cx;
				if (caretXPos > mouseXPos) {
					hight = mid - 1;
				} else if (caretXPos < mouseXPos) {
					low = mid + 1;
				} else {
					m_caretPlace = m_beginDrawPlace + mid;
					return caretXPos;
				}
			}
			bstring hightString = m_strText.substr(m_beginDrawPlace, hight);
			SIZE szTextHight = getTextSize(hightString);
			bstring lowString = m_strText.substr(m_beginDrawPlace, low);
			SIZE szTextLow = getTextSize(lowString);
			if (mouseXPos > (szTextLow.cx + szTextHight.cx) / 2) {
				m_caretPlace = m_beginDrawPlace + low;
				return szTextLow.cx;
			} else {
				m_caretPlace = m_beginDrawPlace + hight;
				return szTextHight.cx;
			}
		}
		return caretXPos;
	}

	SIZE BUIEdit::getTextSize(const bstring text)
	{
		return BRenderEngineManager::GetInstance()->RenderEngine()->GetTextSize(text, m_textDesc.fontFamily, m_textDesc.fontSize, m_textDesc.style);
	}

	RECT BUIEdit::getContentRect()
	{
		RECT rcContent;
		rcContent.left = m_rcItem.left + m_rcPadding.left;
		rcContent.top = m_rcItem.top + m_rcPadding.top;
		rcContent.right = m_rcItem.right - m_rcPadding.right;
		rcContent.bottom = m_rcItem.bottom - m_rcPadding.bottom;
		return rcContent;
	}
}