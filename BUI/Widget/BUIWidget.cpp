#include "stdafx.h"

namespace BUI{
	BUIWidget::BUIWidget()
		: m_pUIManager(NULL),
		m_parent(NULL),
		m_widgetName(_T("")),
		m_strText(_T("")),
		m_toolTip(_T("")),
		m_bkColor(0),
		m_bkColor2(0),
		m_imageFileName(_T("")),
		m_bVisible(true),
		m_bEnabled(true),
		m_bFocused(false)
		
	{
		m_rcItem.left = m_rcItem.right = m_rcItem.top = m_rcItem.bottom = 0;
		m_xy.cx = m_xy.cy = 0;
		m_rcPaint.left = m_rcPaint.right = m_rcPaint.top = m_rcPaint.bottom = 0;
	}


	BUIWidget::~BUIWidget()
	{
	}

	bstring BUIWidget::GetName()
	{
		return m_widgetName;
	}
	void BUIWidget::SetName(LPCTSTR name)
	{
		m_widgetName = name;
	}

	LPCTSTR BUIWidget::GetType()
	{
		return BUI_WIN_WIDGET;
	}

	LPVOID BUIWidget::GetInterface(LPCTSTR name)
	{
		if (_tcscmp(name, _T("Widget")) == 0) return this;
		return NULL;
	}

	LPCTSTR BUIWidget::GetText()
	{
		return m_strText.c_str();
	}
	void BUIWidget::SetText(LPCTSTR text)
	{
		m_strText = text;
	}

	// 图形相关
	DWORD BUIWidget::GetBkColor()
	{
		return m_bkColor;
	}

	void BUIWidget::SetBkColor(DWORD bkColor)
	{
		m_bkColor = bkColor;
	}

	DWORD BUIWidget::GetBkColor2()
	{
		return m_bkColor2;
	}

	void BUIWidget::SetBkColor2(DWORD bkColor)
	{
		m_bkColor2 = bkColor;
	}

	LPCTSTR BUIWidget::GetBkImage()
	{
		return m_imageFileName.c_str();
	}

	void BUIWidget::SetBkImage(LPCTSTR pstrImage)
	{
		m_imageFileName = pstrImage;
	}

	// 位置相关
	const RECT& BUIWidget::GetPos()
	{
		return m_rcItem;
	}

	RECT BUIWidget::GetClientPos()
	{
		return m_rcItem;
	}

	void BUIWidget::SetPos(RECT rc)
	{
		m_rcItem = rc;
	}

	int BUIWidget::GetWidth()
	{
		return  m_rcItem.right - m_rcItem.left;
	}

	int BUIWidget::GetHeight()
	{
		return m_rcItem.bottom - m_rcItem.top;
	}

	int BUIWidget::GetX()
	{
		return m_xy.cx;
	}

	int BUIWidget::GetY()
	{
		return m_xy.cy;
	}

	// 提示信息
	LPCTSTR BUIWidget::GetToolTip()
	{
		return m_toolTip.c_str();
	}

	void BUIWidget::SetToolTip(LPCTSTR tip)
	{
		m_toolTip = tip;
	}

	// 绘制相关
	void BUIWidget::Paint(HDC hDC, const RECT& rcPaint)
	{
		DoPaint(hDC, rcPaint);
	}

	void BUIWidget::DoPaint(HDC hDC, const RECT& rcPaint)
	{
		if (!::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem))
			return;

		PaintBkColor(hDC);
		PaintBkImage(hDC);
		PaintStatusImage(hDC);
		PaintText(hDC);
		PaintBorder(hDC);
	}

	void BUIWidget::PaintBkColor(HDC hDC)
	{
		BRenderEngineManager::GetInstance()->RenderEngine()->DrawGradient(hDC, m_rcPaint, 0xFFFF0000, 0xFF0000FF);
	}

	void BUIWidget::PaintBkImage(HDC hDC)
	{

	}

	void BUIWidget::PaintStatusImage(HDC hDC)
	{

	}

	void BUIWidget::PaintText(HDC hDC)
	{
		BRenderEngineManager::GetInstance()->RenderEngine()->DrawText(hDC, m_rcPaint, GetText(), 0xFFFFFFFF, 12, NULL, 0);
	}

	void BUIWidget::PaintBorder(HDC hDC)
	{

	}

	void BUIWidget::Invalidate()
	{
		m_pUIManager->Invalidate(m_rcItem);
	}

	void BUIWidget::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		
	}

	void BUIWidget::Event(TEventUI& event)
	{
		if (event.type == uievent_setcursor)
		{
			::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
			return ;
		}

		if (event.type == uievent_setfocus)
		{
			Invalidate();
			m_bFocused = true;
			return;
		}

		if (event.type == uievent_killfocus)
		{
			Invalidate();
			m_bFocused = false;
			return;
		}
	}

	BUIManager* BUIWidget::GetManager() const
	{
		return m_pUIManager;
	}

	void BUIWidget::SetManager(BUIManager* uiManager, BUIWidget* parent)
	{
		m_pUIManager = uiManager;
		m_parent = parent;

	}

	BUIWidget* BUIWidget::GetParent() const
	{
		return m_parent;
	}

	BUIWidget* BUIWidget::FindControl(FINDWIDGET Proc, LPVOID pData, UINT uFlags)
	{
		if( (uFlags & UIFIND_VISIBLE) != 0 && !IsVisible() ) return NULL;
		if( (uFlags & UIFIND_ENABLED) != 0 && !IsEnabled() ) return NULL;
		if( (uFlags & UIFIND_HITTEST) != 0 && !::PtInRect(&m_rcItem, * static_cast<LPPOINT>(pData)) ) return NULL;
		return Proc(this, pData);
	}

	bool BUIWidget::IsVisible() const
	{
		return m_bVisible;
	}

	bool BUIWidget::IsEnabled() const
	{
		return m_bEnabled;
	}

	bool BUIWidget::IsFocused() const
	{
		return m_bFocused;
	}

	void BUIWidget::SetVisible(bool bVisible/* = true*/)
	{
		m_bVisible = bVisible;
	}

	void BUIWidget::SetEnabled(bool bEnable/* = true*/)
	{
		m_bEnabled = bEnable;

		Invalidate();
	}

	void BUIWidget::SetFocus()
	{
		// coding...........
	}
}
