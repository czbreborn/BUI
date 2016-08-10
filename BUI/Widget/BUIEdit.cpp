#include "stdafx.h"

namespace BUI {
	IMPLEMENT_WIDGETTYPE(BUIEdit, BUILabel)
	IMPLEMENT_CREATEWIDGET(BUIEdit)

	BUIEdit::BUIEdit(void)
	: m_mouseState(false),
	m_caretState(false),
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
		m_borderSize.left = 1;
		m_borderColor = customcolor_red;
	}

	BUIEdit::~BUIEdit(void)
	{
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
			m_caretState = false;
			m_selectedBeginPalce = 0;
			m_selectedEndPlace = 0;
			Invalidate();
		}

		if (event.type == uievent_killfocus) {
			m_pUIManager->DestroyCaret();
			m_caretState = false;
			m_selectedBeginPalce = 0;
			m_selectedEndPlace = 0;
			Invalidate();
		}

		if (event.type == uievent_buttondown) {
			m_selectedBeginPalce = 0;
			m_selectedEndPlace = 0;
			if (::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled()) {
				m_caretPlace = locateCaretPlace(event.ptMouse.x);
				if (m_caretPlace == m_beginDrawPlace) {
					m_pUIManager->SetCaretPos(getContentRect().left, getContentRect().top);
				} else {
					SizeF szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace));
					m_pUIManager->SetCaretPos(getContentRect().left + ceil(szText.Width), getContentRect().top);
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

		if (event.type == uievent_mouseenter) {
			if (!m_mouseState) {
				SetClassLong(m_pUIManager->GetPaintWindow(), GCL_HCURSOR, (LONG)LoadCursor(NULL,IDC_IBEAM));
				m_mouseState = true;
			}
		}

		if (event.type == uievent_mousemove) {
			if (::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled()) {
				if (::GetKeyState(VK_LBUTTON) < 0) {
					m_selectedBeginPalce = m_caretPlace;
					m_selectedEndPlace = locateCaretPlace(event.ptMouse.x);
					if (m_selectedBeginPalce > m_selectedEndPlace) {
						UINT caretPlace = m_selectedBeginPalce;
						m_selectedBeginPalce = m_selectedEndPlace;
						m_selectedEndPlace = caretPlace;
					}

					if (m_selectedBeginPalce < m_selectedEndPlace) {
						if (m_caretState) {
							m_pUIManager->HideCaret();
							m_caretState = false;
						}
					}
				}

				Invalidate();
			}
		}

		if (event.type == uievent_mouseleave) {
			if (m_mouseState) {
				SetClassLong(m_pUIManager->GetPaintWindow(), GCL_HCURSOR, (LONG)LoadCursor(NULL,IDC_ARROW));
				m_mouseState = false;
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
		RECT rcPaint;
		if (IntersectRect(&rcPaint, &m_rcPaint, &getContentRect())) {
			m_textDesc.content = m_strText.substr(m_beginDrawPlace);
			m_textDesc.selectedBegin = m_selectedBeginPalce - m_beginDrawPlace;
			m_textDesc.selectedCount = m_selectedEndPlace - m_selectedBeginPalce;
			RectF rcf(rcPaint.left, rcPaint.top, rcPaint.right - rcPaint.left, rcPaint.bottom - rcPaint.top);
			m_textDesc.selectedBkColor = 0xAACC6600;
			BRenderEngineManager::GetInstance()->RenderEngine()->DrawText(hDC, rcf, m_textDesc);
		}
	}

	void BUIEdit::onMouseMove(LONG mouseXPos)
	{
		
	}

	void BUIEdit::onKeyDown(TCHAR chKey)
	{
		bstringstream woss;
		woss << L"buiedit::onKeyDown --" << chKey << endl;
		::OutputDebugString(woss.str().c_str());
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
								m_pUIManager->SetCaretPos(getContentRect().left + ceil(szDrawText.Width), getContentRect().top);
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
				// 选择内容
				if ((GetKeyState(VK_SHIFT) & 0x8000) != 0) {
					if (m_selectedEndPlace == 0) {
						if (m_caretPlace != 0) {
							m_selectedEndPlace = m_caretPlace;
							m_selectedBeginPalce = m_caretPlace - 1;
						}
					} else {
						if (m_selectedBeginPalce == m_caretPlace) {
							m_selectedEndPlace--;
							if (m_selectedBeginPalce == m_selectedEndPlace) {
								m_selectedBeginPalce = m_selectedEndPlace = 0;
								if (!m_caretState) {
									m_pUIManager->ShowCaret();
									m_caretState = true;
								}
							}
						} else {
							if (m_selectedBeginPalce != 0) {
								if (m_selectedBeginPalce == m_beginDrawPlace) {
									if (m_beginDrawPlace > 5) {
										m_beginDrawPlace -= 5;
									} else {
										m_beginDrawPlace = 0;
									}
								}
								m_selectedBeginPalce--;
							}
						}
					}

					if (m_selectedBeginPalce < m_selectedEndPlace) {
						if (m_caretState) {
							m_pUIManager->HideCaret();
							m_caretState = false;
						}
					}
				} else { // 移动光标
					if (m_selectedBeginPalce < m_selectedEndPlace) {
						if (!m_caretState) {
							m_pUIManager->ShowCaret();
							m_caretState = true;
						}
						m_caretPlace = m_selectedBeginPalce;
					}
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
						m_pUIManager->SetCaretPos(getContentRect().left + ceil(szText.Width), getContentRect().top);
					} else {
						m_pUIManager->SetCaretPos(getContentRect().right, getContentRect().top);
					}

					m_selectedBeginPalce = m_selectedEndPlace = 0;
				}
			}
			break;

		case VK_RIGHT:
			// 选择内容
			if ((GetKeyState(VK_SHIFT) & 0x8000) != 0) {
				if (m_selectedEndPlace == 0) {
					if (m_caretPlace != m_strText.length()) {
						m_selectedEndPlace = m_caretPlace + 1;
						m_selectedBeginPalce = m_caretPlace;
					}
				} else {
					if (m_selectedEndPlace == m_caretPlace) {
						m_selectedBeginPalce++;
						if (m_selectedBeginPalce == m_selectedEndPlace) {
							m_selectedBeginPalce = m_selectedEndPlace = 0;
							if (!m_caretState) {
								m_pUIManager->ShowCaret();
								m_caretState = true;
							}
						}
					} else {
						if (m_selectedEndPlace < m_strText.length()) {
							m_selectedEndPlace++;
							SizeF szDrawText = getTextSize(m_strText.substr(m_beginDrawPlace, m_selectedEndPlace - m_beginDrawPlace + 1));
							if (szDrawText.Width > getContentRect().right - getContentRect().left) {
								if (m_beginDrawPlace + 5 < m_strText.length()) {
									m_beginDrawPlace += 5;
								} else {
									m_beginDrawPlace += m_strText.length() - m_beginDrawPlace;
								}
							}
						}
					}
				}

				if (m_selectedBeginPalce < m_selectedEndPlace) {
					if (m_caretState) {
						m_pUIManager->HideCaret();
						m_caretState = false;
					}
				}
			} else {	// 移动光标
				if (m_selectedBeginPalce < m_selectedEndPlace) {
					if (!m_caretState) {
						m_pUIManager->ShowCaret();
						m_caretState = true;
					}
					m_caretPlace = m_selectedEndPlace;
				}
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
				}

				SizeF szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace));
				if (szText.Width < getContentRect().right - getContentRect().left) {
					m_pUIManager->SetCaretPos(getContentRect().left + ceil(szText.Width), getContentRect().top);
				} else {
					m_pUIManager->SetCaretPos(getContentRect().right, getContentRect().top);
				}

				m_selectedBeginPalce = m_selectedEndPlace = 0;
			}

			break;

		case VK_TAB:
			//PostMessageW(GetParent(hWnd), WM_NEXTDLGCTL, GetKeyState(VK_SHIFT) & 0x8000, FALSE);
			break;

		default:
			break;
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
						m_pUIManager->SetCaretPos(getContentRect().left + ceil(szText.Width), getContentRect().top);
					} else {
						m_pUIManager->SetCaretPos(getContentRect().right, getContentRect().top);
					}
				}
				break;

			case VK_TAB:
				break;

			default:
				{
					if (m_caretPlace == m_strText.length()) {
						m_strText.append(1, chKey);
					} else {
						m_strText.insert(m_caretPlace, 1, chKey);
					}
					m_caretPlace++;
					SizeF szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace));
					if (szText.Width > getContentRect().right - getContentRect().left) {
						if (m_caretPlace == m_strText.length()) {
							m_beginDrawPlace++;
						} else {
							m_beginDrawPlace += (m_strText.length() - m_caretPlace < 5) ? m_strText.length() - m_caretPlace : 5;
						}
					}

					szText = getTextSize(m_strText.substr(m_beginDrawPlace, m_caretPlace - m_beginDrawPlace));
					if (szText.Width < getContentRect().right - getContentRect().left) {
						m_pUIManager->SetCaretPos(getContentRect().left + ceil(szText.Width), getContentRect().top);
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
			if (hight < 0) {
				return m_beginDrawPlace + low;
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
		RectF rcf(getContentRect().left, getContentRect().top, getContentRect().right - getContentRect().left + 100, getContentRect().bottom - getContentRect().top);
		return BRenderEngineManager::GetInstance()->RenderEngine()->GetTextSize(m_pUIManager->GetPaintDC(), rcf, m_textDesc);
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