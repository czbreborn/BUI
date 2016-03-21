#include "stdafx.h"

namespace BUI{
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

	LPCTSTR BUIButton::GetType() const
	{
		return BUI_WIN_BUTTON;
	}

	LPVOID BUIButton::GetInterface(LPCTSTR name)
	{
		if (_tcscmp(name, _T("Button")) == 0) return static_cast<BUIButton*>(this);
		return BUILabel::GetInterface(name);
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

	void BUIButton::PaintStatusImage(HDC hDC)
	{

	}
}