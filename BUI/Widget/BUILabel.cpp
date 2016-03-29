#include "stdafx.h"

namespace BUI{
	IMPLEMENT_CREATEWIDGET(BUILabel)
	IMPLEMENT_WIDGETTYPE(BUILabel, BUIWidget)

	BUILabel::BUILabel()
		: m_textColor(-1),
		m_textStyle(FontStyleRegular),
		m_textAlign(ALIGNMENTMIDDLE)
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
	
	void BUILabel::SetTextAlign(UINT align)
	{
		m_textAlign = align;
	}

	UINT BUILabel::GetTextAlign()
	{
		return m_textAlign;
	}

	void BUILabel::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if (_tcscmp(pstrName, _T("align")) == 0) 
		{
			UINT align = GetTextAlign();
			if (_tcsstr(pstrValue, _T("left")) != NULL)
			{
				align |= textalignment_left;
			}
			if (_tcsstr(pstrValue, _T("center")) != NULL)
			{
				align |= textalignment_center;
			}
			if (_tcsstr(pstrValue, _T("right")) != NULL)
			{
				align |= textalignment_right;
			}
			SetTextAlign(align);
		}
		else if (_tcscmp(pstrName, _T("valign")) == 0)
		{
			UINT align = GetTextAlign();
			if (_tcsstr(pstrValue, _T("top")) != NULL)
			{
				align |= textalignment_top;
			}
			if (_tcsstr(pstrValue, _T("vcenter")) != NULL)
			{
				align |= textalignment_vcenter;
			}
			if (_tcsstr(pstrValue, _T("bottom")) != NULL)
			{
				align |= textalignment_bottom;
			}
			SetTextAlign(align);
		}
		else if (_tcscmp(pstrName, _T("textcolor")) == 0)
		{
			if (*pstrValue == _T('#')) 
				pstrValue = ::CharNext(pstrValue);

			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetTextColor(clrColor);
		}
		else 
		{
			BUIWidget::SetAttribute(pstrName, pstrValue);
		}
	}

	void BUILabel::PaintText(HDC hDC)
	{
		BRenderEngineManager::GetInstance()->RenderEngine()->DrawText(hDC, m_rcPaint, GetText(), m_textColor, 12, NULL, m_textStyle);
	}

	void BUILabel::Event(TEventUI& event)
	{

	}
}