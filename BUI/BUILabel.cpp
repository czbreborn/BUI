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
		return BUI_WIN_LABEL;
	}

	LPVOID BUILabel::GetInterface(LPCTSTR name)
	{
		return this;
	}
}