#include "stdafx.h"

namespace BUI{
	IMPLEMENT_CREATEWIDGET(BUILabel)
	IMPLEMENT_WIDGETTYPE(BUILabel, BUIWidget)

	BUILabel::BUILabel()
		: m_textColor(-1),
		m_textStyle(FontStyleRegular)
	{

	}

	BUILabel::~BUILabel()
	{
	}

	void BUILabel::SetTextStyle(int style)
	{
		m_textStyle = style;
	}

	int BUILabel::GetTextStyle() const
	{
		return m_textStyle;
	}

	void BUILabel::SetTextColor(DWORD textColor)
	{
		m_textColor = textColor;
	}

	DWORD BUILabel::GetTextColor() const
	{
		return m_textColor;
	}

	void BUILabel::PaintText(HDC hDC)
	{
		BRenderEngineManager::GetInstance()->RenderEngine()->DrawText(hDC, m_rcPaint, GetText(), m_textColor, 12, NULL, m_textStyle);
	}
	void BUILabel::Event(TEventUI& event)
	{

	}
}