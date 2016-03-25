#include "stdafx.h"

namespace BUI{
	CREATEWIDGETFUNCMAP BUIWidgetFactory::s_createWidgetMap;
	BUIWidgetFactory	BUIWidgetFactory::s_uiWidgetFactory;

	BUIWidgetFactory::BUIWidgetFactory()
	{
		REGISTER_CREATEWIDGET(BUILabel)
		REGISTER_CREATEWIDGET(BUIButton)
		REGISTER_CREATEWIDGET(BUIVerticalLayout);
	}


	BUIWidgetFactory::~BUIWidgetFactory()
	{

	}

	BUIWidgetFactory* BUIWidgetFactory::GetInstance()
	{
		return &s_uiWidgetFactory;
	}

	BUIWidget* BUIWidgetFactory::CreateWidget(LPCTSTR className)
	{
		BUIWidget* pWidget = NULL;
		CREATEWIDGETFUNCMAPIT it = s_createWidgetMap.find(className);
		if (it != s_createWidgetMap.end())
		{
			pWidget = static_cast<BUIWidget*>((it->second)());
		}
		return pWidget;
	}

	void BUIWidgetFactory::RegisterCreateWidget(LPCTSTR className, PCreateWidget func)
	{
		CREATEWIDGETFUNCMAPIT it = s_createWidgetMap.find(className);
		if (it == s_createWidgetMap.end())
		{
			s_createWidgetMap.insert(make_pair(className, func));
		}
	}
}