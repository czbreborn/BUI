#include "stdafx.h"

namespace BUI{
	BUIWidget::BUIWidget()
		: m_widgetName(_T("")),
		m_strText(_T("")),
		m_bkColor(0),
		m_bkColor2(0),
		m_imageFileName(_T("")),
		m_toolTip(_T(""))
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
		return this;
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

	void BUIWidget::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		
	}
}
