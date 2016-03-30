#ifndef __BUIHORIZONTALLAYOUT_H__
#define __BUIHORIZONTALLAYOUT_H__

#pragma once

namespace BUI {
	class BUIHorizontalLayout :	public BUIContainer
	{
	public:
		DEFINE_CREATEWIDGET(BUIHorizontalLayout)
		DEFINE_WIDGETTYPE(BUIHorizontalLayout)

	public:
		BUIHorizontalLayout(void);
		~BUIHorizontalLayout(void);

	public:
		void Event(TEventUI& event);
		void SetPos(RECT rc);
	};
}
#endif