#include "stdafx.h"

namespace BUI{
	IMPLEMENT_CREATEWIDGET(BUIButton)
	IMPLEMENT_WIDGETTYPE(BUIButton, BUILabel)

	BUIButton::BUIButton()
		: m_normalImage(_T("")),
		m_hotImage(_T("")),
		m_pushedImage(_T("")),
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

	LPCTSTR BUIButton::GetDisabledImage()
	{
		return m_disabledImage.c_str();
	}

	void BUIButton::SetDisabledImage(LPCTSTR imageName)
	{
		m_disabledImage = imageName;
	}

	void BUIButton::Event(TEventUI& event)
	{
		if (event.type == uievent_buttondown)
		{
			Invalidate();
		}

		BUILabel::Event(event);
	}

	void BUIButton::PaintStatusImage(HDC hDC)
	{
		
	}
}