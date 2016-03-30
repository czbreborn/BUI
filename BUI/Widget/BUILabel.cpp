#include "stdafx.h"

namespace BUI{
	IMPLEMENT_CREATEWIDGET(BUILabel)
	IMPLEMENT_WIDGETTYPE(BUILabel, BUIWidget)

	BUILabel::BUILabel()
	{
		memset(&m_textDesc, 0, sizeof(TextDescription));
		m_textDesc.textColor = -1;
		m_textDesc.textColor1 = -1;
		m_textDesc.fontSize = 12;
		m_textDesc.style = FontStyleRegular;
		m_textDesc.align = ALIGNMENTMIDDLE;
		m_textDesc.formatFlags = StringFormatFlagsNoWrap;
	}

	BUILabel::~BUILabel()
	{
	}

	void BUILabel::SetTextStyle(int style)
	{
		m_textDesc.style = style;
	}

	int BUILabel::GetTextStyle() const
	{
		return m_textDesc.style;
	}

	void BUILabel::SetTextColor(DWORD textColor)
	{
		m_textDesc.textColor = textColor;
	}

	DWORD BUILabel::GetTextColor() const
	{
		return m_textDesc.textColor;
	}

	void BUILabel::SetTextColor1(DWORD textColor)
	{
		m_textDesc.textColor1 = textColor;
	}

	DWORD BUILabel::GetTextColor1() const
	{
		return m_textDesc.textColor1;
	}
	
	void BUILabel::SetTextAlign(UINT align)
	{
		m_textDesc.align = align;
	}

	UINT BUILabel::GetTextAlign()
	{
		return m_textDesc.align;
	}

	void BUILabel::SetEnabledGlow(bool enabledGlow)
	{
		m_textDesc.bGlow = enabledGlow;
	}

	bool BUILabel::GetEnabledGlow()
	{
		return m_textDesc.bGlow;
	}

	void BUILabel::SetGlowColor(DWORD glowColor)
	{
		m_textDesc.glowColor = glowColor;
	}

	DWORD BUILabel::GetGlowColor()
	{
		return m_textDesc.glowColor;
	}

	void BUILabel::SetEnabledStroke(bool enabledStroke)
	{
		m_textDesc.bStroke = enabledStroke;
	}

	bool BUILabel::GetEnabledStroke()
	{
		return m_textDesc.bStroke;
	}

	void BUILabel::SetStrokeColor(DWORD strokeColor)
	{
		m_textDesc.singleColor = strokeColor;
	}

	DWORD BUILabel::GetStrokeColor()
	{
		return m_textDesc.singleColor;
	}

	void BUILabel::SetStrokeColor1(DWORD strokeColor)
	{
		m_textDesc.doubleColor = strokeColor;
	}

	DWORD BUILabel::GetStrokeColor1()
	{
		return m_textDesc.doubleColor;
	}

	void BUILabel::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if (_tcscmp(pstrName, _T("align")) == 0) 
		{
			UINT align = GetTextAlign();
			align &= 0xF0;
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
			align &= 0x0F;
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
		else if (_tcscmp(pstrName, _T("textcolor1")) == 0) 
		{
			if (*pstrValue == _T('#')) 
				pstrValue = ::CharNext(pstrValue);

			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetTextColor1(clrColor);
		}
		else 
		{
			BUIWidget::SetAttribute(pstrName, pstrValue);
		}
	}

	void BUILabel::PaintText(HDC hDC)
	{
		m_textDesc.content = GetText();
		BRenderEngineManager::GetInstance()->RenderEngine()->DrawText(hDC, m_rcPaint, m_textDesc);
	}

	void BUILabel::Event(TEventUI& event)
	{

	}
}