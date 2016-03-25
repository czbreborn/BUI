#ifndef __BUIEDIT_H__
#define __BUIEDIT_H__

#pragma once

namespace BUI{
	class BUILabel;
	class BUI_API BUIEdit :	public BUILabel
	{
	public:
		DEFINE_WIDGETTYPE(BUIEdit)
		DEFINE_CREATEWIDGET(BUIEdit)

	public:
		BUIEdit(void);
		virtual ~BUIEdit(void);		
	};
}

#endif