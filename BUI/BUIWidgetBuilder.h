#ifndef __BUIWIDGETBUILDER_H__
#define __BUIWIDGETBUILDER_H__

#pragma once

namespace BUI{
	class BIWidgetBuilderCallBack
	{
	public:
		virtual BUIWidget* CreateWidget(LPCTSTR className) = 0;
	};

	class BUIWidgetBuilder
	{
	public:
		BUIWidgetBuilder();
		~BUIWidgetBuilder();

		BUIWidget* CreateWidget(LPCTSTR xmlName, LPCTSTR type = NULL, BIWidgetBuilderCallBack* callback = NULL);
	private:
		BIWidgetBuilderCallBack* m_builderCallBack;
	};
}

#endif