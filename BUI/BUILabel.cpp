#include "stdafx.h"

namespace BUI{
	IMPLEMENT_CREATEWIDGET(BUILabel)

	BUILabel::BUILabel()
	{

	}


	BUILabel::~BUILabel()
	{
	}

	LPCTSTR BUILabel::GetType() const
	{
		return BUI_WIN_BUTTON;
	}

	LPVOID BUILabel::GetInterface(LPCTSTR name)
	{
		if (_tcscmp(name, _T("Label")) == 0) return static_cast<BUILabel*>(this);
		return BUIWidget::GetInterface(name);
	}
}