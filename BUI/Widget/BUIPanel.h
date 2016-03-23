#ifndef __BUIPANEL_H__
#define __BUIPANEL_H__

#pragma once

namespace BUI{
	class BUIWidget;
	class BUI_API BUIPanel : public BUIWidget
	{
	public:
		BUIPanel();
		virtual ~BUIPanel();
	};
}

#endif