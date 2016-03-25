#ifndef __BUIVERTICALLAYOUT_H__
#define __BUIVERTICALLAYOUT_H__

#pragma once

namespace BUI {
	class BUIContainer;
	class BUI_API BUIVerticalLayout : public BUIContainer
	{
	public:
		DEFINE_CREATEWIDGET(BUIVerticalLayout)
		DEFINE_WIDGETTYPE(BUIVerticalLayout)

	public:
		BUIVerticalLayout(void);
		~BUIVerticalLayout(void);

	public:
		void DoEvent(TEventUI& event);
		void SetPos(RECT rc, bool bNeedInvalidate = true);
	};
}
#endif