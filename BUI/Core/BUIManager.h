#ifndef __BUIMANAGER_H__
#define __BUIMANAGER_H__

#pragma once

namespace BUI{
	class BUIWidget;
	class BUI_API BUIManager
	{
	public:
		BUIManager();
		~BUIManager();

		void Init(HWND hwnd, LPCTSTR name = NULL);
		HDC GetPaintDC();

	public:
		bool IsUpdateNeeded() const;
		void NeedUpdate();
		void Invalidate();
		void Invalidate(RECT& rcItem);

		bool AttachWidget(BUIWidget* root);

	public:
		LRESULT MessageRouting(UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:
		void OnPaint();

	private:
		HWND m_hWndPaint;
		HDC  m_hdcPaint;
		bstring m_name;

		bool m_bUpdateNeeded;

		BUIWidget* m_rootWidget;
	};
}

#endif