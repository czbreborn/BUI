#ifndef __BUIBUTTON_H__
#define __BUIBUTTON_H__

#pragma once

namespace BUI{
	class BUI_API BUIButton : public BUILabel
	{
	public:
		DEFINE_CREATEWIDGET(BUIButton)
		DEFINE_WIDGETTYPE(BUIButton)

	public:
		BUIButton();
		virtual ~BUIButton();

	public:
		LPCTSTR GetNormalImage();
		void SetNormalImage(LPCTSTR imageName);
		LPCTSTR GetHotImage();
		void SetHotImage(LPCTSTR imageName);
		LPCTSTR GetPushedImage();
		void SetPushedImage(LPCTSTR imageName);
		LPCTSTR GetDisabledImage();
		void SetDisabledImage(LPCTSTR imageName);

		void Event(TEventUI& event);

	protected:
		void PaintStatusImage(HDC hDC);

	private:
		bstring m_normalImage;
		bstring m_hotImage;
		bstring m_pushedImage;
		bstring m_disabledImage;
	};
}

#endif