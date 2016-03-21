#ifndef __BUIBUTTON_H__
#define __BUIBUTTON_H__

#pragma once

namespace BUI{
	class BUIButton : public BUILabel
	{
	public:
		BUIButton();
		virtual ~BUIButton();

		LPCTSTR GetType() const;
		LPVOID GetInterface(LPCTSTR name);

	public:
		LPCTSTR GetNormalImage();
		void SetNormalImage(LPCTSTR imageName);
		LPCTSTR GetHotImage();
		void SetHotImage(LPCTSTR imageName);
		LPCTSTR GetPushedImage();
		void SetPushedImage(LPCTSTR imageName);
		LPCTSTR GetDisabledImage();
		void SetDisabledImage(LPCTSTR imageName);

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