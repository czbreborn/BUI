#ifndef __BUIWIDGETFACTORY_H__
#define __BUIWIDGETFACTORY_H__
#pragma once

namespace BUI{
	class BUIWidget;
	class BUIWidgetFactory
	{
	protected:
		BUIWidgetFactory();
		~BUIWidgetFactory();
		
	public:
		static BUIWidgetFactory* GetInstance();

	public:
		BUIWidget* CreateWidget(LPCTSTR className);
		void RegisterCreateWidget(LPCTSTR className, PCreateWidget func);

	private:
		static CREATEWIDGETFUNCMAP s_createWidgetMap;
		static BUIWidgetFactory	s_uiWidgetFactory;
	};
}

#endif