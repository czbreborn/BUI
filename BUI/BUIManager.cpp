#include "stdafx.h"

namespace BUI{
	BUIManager::BUIManager()
		: m_hWndPaint(NULL),
		m_hdcPaint(NULL),
		m_name(_T("")),
		m_bUpdateNeeded(false),
		m_rootWidget(NULL)
	{
	}


	BUIManager::~BUIManager()
	{
	}

	void BUIManager::Init(HWND hwnd, LPCTSTR name/* = NULL*/)
	{
		if (m_name.empty())
			m_name = name;

		if (m_hWndPaint != hwnd)
		{
			m_hWndPaint = hwnd;
			m_hdcPaint = GetDC(hwnd);
		}
	}


	HDC BUIManager::GetPaintDC()
	{
		return m_hdcPaint;
	}

	bool BUIManager::IsUpdateNeeded() const
	{
		return m_bUpdateNeeded;
	}

	void BUIManager::NeedUpdate()
	{
		m_bUpdateNeeded = true;
	}

	void BUIManager::Invalidate()
	{
		::InvalidateRect(m_hWndPaint, NULL, false);
	}

	void BUIManager::Invalidate(RECT& rcItem)
	{
		if (rcItem.left < 0)
			rcItem.left = 0;
		if (rcItem.top < 0)
			rcItem.top = 0;
		if (rcItem.right < rcItem.left)
			rcItem.right = rcItem.left;
		if (rcItem.bottom < rcItem.top)
			rcItem.bottom = rcItem.top;
		::InvalidateRect(m_hWndPaint, &rcItem, FALSE);
	}

	bool BUIManager::AttachWidget(BUIWidget* root)
	{
		m_rootWidget = root;
		return true;
	}

	LRESULT BUIManager::MessageRouting(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_PAINT:
			OnPaint();
			break;
		default:
			break;
		}
		return true;
	}

	void BUIManager::OnPaint()	
	{
		PAINTSTRUCT ps = { 0 };
		BeginPaint(m_hWndPaint, &ps);
		if (m_rootWidget != NULL)
		{
			RECT rcClient = { 0 };

			::GetClientRect(m_hWndPaint, &rcClient);
			m_rootWidget->SetPos(rcClient);
			m_rootWidget->Paint(m_hdcPaint, rcClient);
		}
		EndPaint(m_hWndPaint, &ps);
	}
}