#ifndef __BUILABEL_H__
#define __BUILABEL_H__

#pragma once

namespace BUI{
	class BUI_API BUILabel : public BUIWidget
	{
	public:
		DEFINE_CREATEWIDGET(BUILabel)
		
		BUILabel();
		virtual ~BUILabel();

		LPCTSTR GetType() const;
		LPVOID GetInterface(LPCTSTR name);
	};
} // namespace BUI

#endif