#ifndef __BUILABEL_H__
#define __BUILABEL_H__

#pragma once

namespace BUI{
	class BUI_API BUILabel : public BUIWidget
	{
	public:
		DEFINE_CREATEWIDGET(BUILabel)
		DEFINE_WIDGETTYPE(BUILabel)

	public:		
		
		BUILabel();
		virtual ~BUILabel();

		void Event(TEventUI& event);
	};
} // namespace BUI

#endif