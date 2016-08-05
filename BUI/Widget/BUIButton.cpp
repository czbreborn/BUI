#include "stdafx.h"

namespace BUI{
	IMPLEMENT_CREATEWIDGET(BUIButton)
	IMPLEMENT_WIDGETTYPE(BUIButton, BUILabel)

	BUIButton::BUIButton()
		: m_buttonState(0),
		m_normalImage(_T("")),
		m_hotImage(_T("")),
		m_pushedImage(_T("")),
		m_focusedImage(_T("")),
		m_disabledImage(_T(""))
	{
	}


	BUIButton::~BUIButton()
	{
	}

	LPCTSTR BUIButton::GetNormalImage()
	{
		return m_normalImage.c_str();
	}

	void BUIButton::SetNormalImage(LPCTSTR imageName)
	{
		m_normalImage = imageName;
	}

	LPCTSTR BUIButton::GetHotImage()
	{
		return m_hotImage.c_str();
	}

	void BUIButton::SetHotImage(LPCTSTR imageName)
	{
		m_hotImage = imageName;
	}

	LPCTSTR BUIButton::GetPushedImage()
	{
		return m_pushedImage.c_str();
	}

	void BUIButton::SetPushedImage(LPCTSTR imageName)
	{
		m_pushedImage = imageName;
	}

	LPCTSTR BUIButton::GetFocusedImage()
	{
		return m_focusedImage.c_str();
	}

	void BUIButton::SetFocusedImage(LPCTSTR imageName)
	{
		m_focusedImage = imageName;
	}

	LPCTSTR BUIButton::GetDisabledImage()
	{
		return m_disabledImage.c_str();
	}

	void BUIButton::SetDisabledImage(LPCTSTR imageName)
	{
		m_disabledImage = imageName;
	}

	void BUIButton::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if (_tcscmp(pstrName, _T("normalimage")) == 0) 
		{
			SetNormalImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("hotimage")) == 0)
		{
			SetHotImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("pushedimage")) == 0) 
		{
			SetPushedImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("focusedimage")) == 0) 
		{
			SetFocusedImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("disabledimage")) == 0)
		{
			SetDisabledImage(pstrValue);
		}
		else 
		{
			BUILabel::SetAttribute(pstrName, pstrValue);
		}
	}

	void BUIButton::Event(TEventUI& event)
	{
		if (event.type == uievent_setfocus) {
			Invalidate();
		}
		
		if (event.type == uievent_killfocus) {
			Invalidate();
		}

		if (event.type == uievent_buttondown) {
			if (::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled()) {
				m_buttonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
				Invalidate();
			}
			return;
		}

		if( event.type == uievent_buttonup) {
			if ((m_buttonState & UISTATE_CAPTURED) != 0) {
				m_buttonState &= ~(UISTATE_PUSHED | UISTATE_CAPTURED);
				Invalidate();
			}
			return;
		}

		if (event.type == uievent_mousemove) {
			if ((m_buttonState & UISTATE_CAPTURED) != 0) {
				if (::PtInRect(&m_rcItem, event.ptMouse)) 
					m_buttonState |= UISTATE_PUSHED;
				else 
					m_buttonState &= ~UISTATE_PUSHED;
				Invalidate();
			}
			return;
		}

		if (event.type == uievent_mouseenter) {
			if (IsEnabled()) {
				m_buttonState |= UISTATE_HOT;
				Invalidate();
			}
		}

		if (event.type == uievent_mouseleave){
			if( IsEnabled() ) {
				m_buttonState &= ~UISTATE_HOT;
				Invalidate();
			}
		}

		BUILabel::Event(event);
	}

	void BUIButton::PaintStatusImage(HDC hDC)
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
		} else if ((m_buttonState & UISTATE_PUSHED) != 0) {
			filePath += m_pushedImage;
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
}