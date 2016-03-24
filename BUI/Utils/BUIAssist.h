#ifndef __BUIASSIST_H__
#define __BUIASSIST_H__

#pragma once

namespace BUI {
	class BUIWidget;
	class BUIAssist
	{
	private:
		BUIAssist(void);
		~BUIAssist(void);

	public:
		static BUIWidget* CALLBACK FindWidgetFromPoint(BUIWidget* widget, LPVOID point);

		// µ±Ç°°´¼ü×´Ì¬
		static UINT CurKeyState();
	};
}

#endif