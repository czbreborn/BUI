#include "stdafx.h"
#include "BUIWidget.h"
#include "BUIWidgetDef.h"

BUIWidget::BUIWidget()
	: m_widgetName(L"")
{
}


BUIWidget::~BUIWidget()
{
}

bstring BUIWidget::GetName() const
{
	return m_widgetName;
}
void BUIWidget::SetName(LPCTSTR name)
{
	m_widgetName = name;
}

LPCTSTR BUIWidget::GetType() const
{
	return BUI_WIN_WIDGET;
}

LPVOID BUIWidget::GetInterface(LPCTSTR name)
{
	return this;
}

bstring BUIWidget::GetText() const
{
	return m_strText;
}
void BUIWidget::SetText(LPCTSTR text)
{
	m_strText = text;
}

// 图形相关
DWORD BUIWidget::GetBkColor() const
{
	return m_bkColor;
}

void BUIWidget::SetBkColor(DWORD bkColor)
{
	m_bkColor = bkColor;
}

DWORD BUIWidget::GetBkColor2() const
{
	return m_bkColor2;
}

void BUIWidget::SetBkColor2(DWORD bkColor)
{
	m_bkColor2 = bkColor;
}

LPCTSTR BUIWidget::GetBkImage() const
{
	return m_imageFileName.c_str();
}

void BUIWidget::SetBkImage(LPCTSTR pstrImage)
{
	m_imageFileName = pstrImage;
}

// 位置相关
const RECT& BUIWidget::GetPos() const
{
	return m_rcItem;
}

RECT BUIWidget::GetClientPos() const
{
	return m_rcItem;
}

void BUIWidget::SetPos(RECT rc)
{
	m_rcItem = rc;
}

int BUIWidget::GetWidth() const
{
	return  m_rcItem.right - m_rcItem.left;
}

int BUIWidget::GetHeight() const
{
	return m_rcItem.bottom - m_rcItem.top;
}

int BUIWidget::GetX() const
{
	return m_xy.cx;
}

int BUIWidget::GetY() const
{
	return m_xy.cy;
}

// 提示信息
LPCTSTR BUIWidget::GetToolTip() const
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

}