#include "stdafx.h"

namespace BUI {
	BUIAssist::BUIAssist(void)
	{
	}

	BUIAssist::~BUIAssist(void)
	{
	}

	BUIWidget* BUIAssist::FindWidgetFromPoint(BUIWidget* widget, LPVOID point)
	{
		BUIWidget* resWidget = NULL;
		LPPOINT pPoint = static_cast<LPPOINT>(point);
		if (::PtInRect(&widget->GetPos(), *pPoint))
			resWidget = widget;

		return resWidget;
	}

	UINT BUIAssist::CurKeyState()
	{
		UINT uState = 0;
		if( ::GetKeyState(VK_CONTROL) < 0 ) uState |= MK_CONTROL;
		if( ::GetKeyState(VK_RBUTTON) < 0 ) uState |= MK_LBUTTON;
		if( ::GetKeyState(VK_LBUTTON) < 0 ) uState |= MK_RBUTTON;
		if( ::GetKeyState(VK_SHIFT) < 0 ) uState |= MK_SHIFT;
		if( ::GetKeyState(VK_MENU) < 0 ) uState |= MK_ALT;
		return uState;
	}
}