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

	public:
		void SetTextStyle(int style);
		int GetTextStyle() const;
		void SetTextColor(DWORD dwTextColor);
		DWORD GetTextColor() const;

		void PaintText(HDC hDC);
		void Event(TEventUI& event);

	protected:
		DWORD m_textColor;
		int m_textStyle;
	};
} // namespace BUI

#endif