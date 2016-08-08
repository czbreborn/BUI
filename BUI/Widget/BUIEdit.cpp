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
	m_selectString(k_empty_string),
	m_tipsString(k_empty_string)
	{
		m_rcPadding.left = m_rcPadding.right = m_rcPadding.top = m_rcPadding.bottom = 2;
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
				m_caretPlace = locateCaretPlace(event.ptMouse.x);
				if (m_caretPlace == m_beginDrawPlace) {
					m_pUIManager->SetCaretPos(getContentRect().left, getContentRect().top);
				} else {
					SizeF szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace));
					m_pUIManager->SetCaretPos(getContentRect().left + szText.Width, getContentRect().top);
				}

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
			if (::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled()) {
				if (::GetKeyState(VK_LBUTTON) < 0) {
					UINT leftCaretPlace = m_caretPlace;
					UINT rightCaretPlace = locateCaretPlace(event.ptMouse.x);
					if (leftCaretPlace > rightCaretPlace) {
						UINT caretPlace = leftCaretPlace;
						leftCaretPlace = rightCaretPlace;
						rightCaretPlace = caretPlace;
					}

					m_selectString = m_strText.substr(leftCaretPlace, rightCaretPlace - leftCaretPlace);
					if (!m_selectString.empty()) {
						SizeF szLeftCaret = getTextSize(m_strText.substr(m_beginDrawPlace, leftCaretPlace - m_beginDrawPlace));
						SizeF szRightCaret= getTextSize(m_strText.substr(m_beginDrawPlace, rightCaretPlace - m_beginDrawPlace));
						m_rcSelectString.X = getContentRect().left + szLeftCaret.Width;
						m_rcSelectString.Width = szRightCaret.Width - szLeftCaret.Width;
						m_rcSelectString.Y = getContentRect().top;
						m_rcSelectString.Height = getContentRect().bottom - getContentRect().top;

						if (m_caretState) {
							m_pUIManager->HideCaret();
							m_caretState = false;
						}
					}
				}

				Invalidate();
			}
		}

		if (event.type == uievent_char) {
			onChar(event.chKey);
			Invalidate();
		}

		if (event.type == uievent_keydown) {
			onKeyDown(event.chKey);
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
		// select前面部
		m_textDesc.content = m_strText.substr(m_beginDrawPlace);
		if (!m_selectString.empty()) {
			bstring::size_type findPlace = m_strText.find(m_selectString);
			if (findPlace != bstring::npos) {
				m_textDesc.content = m_strText.substr(m_beginDrawPlace, findPlace - m_beginDrawPlace);
			}
		}
		RectF rcf(m_rcPaint.left, m_rcPaint.top, m_rcPaint.right - m_rcPaint.left, m_rcPaint.bottom - m_rcPaint.top);
		BRenderEngineManager::GetInstance()->RenderEngine()->DrawText(hDC, rcf, m_textDesc);

		// select部分
		if (!m_selectString.empty()) {
			TextDescription textDesc;
			memset(&textDesc, 0, sizeof(TextDescription));
			textDesc.textColor = customcolor_red;
			textDesc.textColor1 = customcolor_red;
			textDesc.fontSize = 14;
			textDesc.style = FontStyleRegular;
			textDesc.align = ALIGNMENTDEFAULT;
			textDesc.formatFlags = (StringFormatFlagsNoWrap | StringFormatFlagsLineLimit | StringFormatFlagsNoFitBlackBox);
			textDesc.content = m_selectString;

			BRenderEngineManager::GetInstance()->RenderEngine()->DrawText(hDC, m_rcSelectString, textDesc);
		}
		// select后面部分
		if (!m_selectString.empty()) {
			bstring::size_type findPlace = m_strText.find(m_selectString);
			if (findPlace != bstring::npos && findPlace + m_selectString.length() < m_strText.length()) {
				SizeF szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_selectString.length() + findPlace - m_beginDrawPlace));
				if (szText.Width < getContentRect().right - getContentRect().left) {
					m_textDesc.content = m_strText.substr(findPlace + m_selectString.length());
					RectF rcPaint;
					rcPaint.X = getContentRect().left + szText.Width;
					rcPaint.Width = getContentRect().right - rcPaint.X;
					rcPaint.Y = getContentRect().top;
					rcPaint.Height = getContentRect().bottom - getContentRect().top;
					BRenderEngineManager::GetInstance()->RenderEngine()->DrawText(hDC, rcPaint, m_textDesc);
				}
			}
		}
	}

	void BUIEdit::onMouseMove(LONG mouseXPos)
	{
		
	}

	void BUIEdit::onKeyDown(TCHAR chKey)
	{
		if (m_caretState) {
			switch (chKey) {
			case VK_DELETE:
				{
					if (m_caretPlace != m_strText.length()) {
						m_strText.erase(m_caretPlace, 1);
						SizeF szText = getTextSize(m_strText);
						if (szText.Width > getContentRect().right - getContentRect().left) {
							SizeF szDrawText = getTextSize(m_strText.substr(m_beginDrawPlace, m_strText.length() - m_beginDrawPlace));
							if (szDrawText.Width > getContentRect().right - getContentRect().left) {
								m_beginDrawPlace--;
								szDrawText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace));
								if (szDrawText.Width < getContentRect().right - getContentRect().left) {
									m_pUIManager->SetCaretPos(getContentRect().left + szDrawText.Width, getContentRect().top);
								} else {
									m_pUIManager->SetCaretPos(getContentRect().right, getContentRect().top);
								}
							}
						}
					}
				}
				break;

			case VK_LEFT:
				{
					if (m_caretPlace != 0) {
						if (m_beginDrawPlace == m_caretPlace) {
							if (m_beginDrawPlace > 5) {
								m_beginDrawPlace -= 5;
							} else {
								m_beginDrawPlace = 0;
							}
						}
						m_caretPlace--;
					}

					SizeF szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace));
					if (szText.Width < getContentRect().right - getContentRect().left) {
						m_pUIManager->SetCaretPos(getContentRect().left + szText.Width, getContentRect().top);
					} else {
						m_pUIManager->SetCaretPos(getContentRect().right, getContentRect().top);
					}
				}
				break;

			case VK_RIGHT:
				if (m_caretPlace < m_strText.length()) {
					SizeF szDrawText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace + 1));
					if (szDrawText.Width > getContentRect().right - getContentRect().left) {
						if (m_caretPlace + 5 <= m_strText.length()) {
							m_beginDrawPlace += 5;
						} else {
							m_beginDrawPlace += m_strText.length() - m_caretPlace;
						}
					}
					m_caretPlace++;

					SizeF szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace));
					if (szText.Width < getContentRect().right - getContentRect().left) {
						m_pUIManager->SetCaretPos(getContentRect().left + szText.Width, getContentRect().top);
					} else {
						m_pUIManager->SetCaretPos(getContentRect().right, getContentRect().top);
					}
				}
				break;

			default:
				break;
			}
		}
	}

	void BUIEdit::onChar(TCHAR chKey)
	{
		if (m_caretState) {
			switch (chKey) {
			case VK_BACK:
				{
					if (m_caretPlace == 0) {
						if (m_beginDrawPlace == 0) {
							return;
						}
					} else {
						m_strText.erase(m_caretPlace - 1, 1);
						m_caretPlace--;
					}
					SizeF szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace));
					if (szText.Width < getContentRect().right - getContentRect().left) {
						m_pUIManager->SetCaretPos(getContentRect().left + szText.Width, getContentRect().top);
					} else {
						m_pUIManager->SetCaretPos(getContentRect().right, getContentRect().top);
					}
				}
				break;

			default:
				{
					if (m_caretPlace == m_strText.length()) {
						m_strText.append(1, chKey);
						m_caretPlace++;
						SizeF szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace));
						if (szText.Width > getContentRect().right - getContentRect().left) {
							m_beginDrawPlace++;
						}
					} else {
						m_strText.insert(m_caretPlace, 1, chKey);
						m_caretPlace++;
						SizeF szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_strText.length() - m_beginDrawPlace));
						if (szText.Width > getContentRect().right - getContentRect().left) {
							m_beginDrawPlace++;
						}
					}

					SizeF szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace));
					if (szText.Width < getContentRect().right - getContentRect().left) {
						m_pUIManager->SetCaretPos(getContentRect().left + szText.Width, getContentRect().top);
					} else {
						m_pUIManager->SetCaretPos(getContentRect().right, getContentRect().top);
					}
				}
				break;
			}
		}
	}

	UINT BUIEdit::locateCaretPlace(LONG mouseXPos)
	{
		UINT caretPlace = m_beginDrawPlace;
		LONG caretXPos = getContentRect().left;
		if (m_strText.length() == 0) {
			return caretPlace;
		}

		SizeF szText = getTextSize(m_strText);
		// 鼠标在最左侧
		if (szText.Width < getContentRect().right - getContentRect().left &&
			mouseXPos < caretXPos) {
			return caretPlace;
		} else {
			LONG lastPointx  = caretXPos;
			LONG leftTextLength = m_strText.length() - m_beginDrawPlace;

			LONG low = 0;
			LONG hight = leftTextLength - 1;
			while (low <= hight) {
				LONG mid = (low + hight) / 2;
				bstring leftString = m_strText.substr(m_beginDrawPlace, mid);
				szText = getTextSize(leftString);
				caretXPos = m_rcItem.left + m_rcPadding.left + szText.Width;
				if (caretXPos > mouseXPos) {
					hight = mid - 1;
				} else if (caretXPos < mouseXPos) {
					low = mid + 1;
				} else {
					return m_beginDrawPlace + mid;
				}
			}
			bstring hightString = m_strText.substr(m_beginDrawPlace, hight);
			SizeF szTextHight = getTextSize(hightString);
			bstring lowString = m_strText.substr(m_beginDrawPlace, low);
			SizeF szTextLow = getTextSize(lowString);
			if (mouseXPos > (szTextLow.Width + szTextHight.Width) / 2) {
				return m_beginDrawPlace + low;
			} else {
				return m_beginDrawPlace + hight;
			}
		}
		return caretPlace;
	}

	SizeF BUIEdit::getTextSize(const bstring text)
	{
		m_textDesc.content = text;
		SizeF szText = BRenderEngineManager::GetInstance()->RenderEngine()->GetTextSize(m_pUIManager->GetPaintDC(), m_textDesc);
		return szText;
		//return BRenderEngineManager::GetInstance()->RenderEngine()->GetTextSize(text, m_textDesc.fontFamily, m_textDesc.fontSize, m_textDesc.style);
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