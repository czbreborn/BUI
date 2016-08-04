#include "stdafx.h"

namespace BUI{
	IMPLEMENT_CREATEWIDGET(BUIWidget)

	BUIWidget::BUIWidget()
		: m_pUIManager(NULL),
		m_parent(NULL),
		m_widgetName(_T("")),
		m_strText(_T("")),
		m_toolTip(_T("")),
		m_bkColor(0),
		m_bkColor2(0),
		m_borderColor(0),
		m_focusBorderColor(0),
		m_borderStyle(PS_SOLID),
		
		m_imageFileName(_T("")),
		m_bVisible(true),
		m_bEnabled(true),
		m_bFocused(false)
		
	{
		m_borderRound.cx = m_borderRound.cy = 0;
		m_cXY.cx = m_cXY.cy = 0;
		m_cxyFixed.cx = m_cxyFixed.cy = 0;
		
		::ZeroMemory(&m_borderSize, sizeof(RECT));
		::ZeroMemory(&m_rcPadding, sizeof(RECT));
		::ZeroMemory(&m_rcItem, sizeof(RECT));
		::ZeroMemory(&m_rcPaint, sizeof(RECT));
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

	LPCTSTR BUIWidget::GetType() const
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

	DWORD BUIWidget::GetBorderColor() const
	{
		return m_borderColor;
	}

	void BUIWidget::SetBorderColor(DWORD borderColor)
	{
		m_borderColor = borderColor;
		Invalidate();
	}

	DWORD BUIWidget::GetFocusBorderColor() const
	{
		return m_focusBorderColor;
	}

	void BUIWidget::SetFocusBorderColor(DWORD focusBorderColor)
	{
		m_focusBorderColor = focusBorderColor;
		Invalidate();
	}

	SIZE BUIWidget::GetBorderRound() const
	{
		return m_borderRound;
	}

	void BUIWidget::SetBorderRound(SIZE cxyRound)
	{
		m_borderRound  = cxyRound;
		Invalidate();
	}

	RECT BUIWidget::GetBorderSize() const
	{
		return m_borderSize;
	}

	void BUIWidget::SetBorderSize(RECT rc)
	{
		m_borderSize = rc;
		Invalidate();
	}

	void BUIWidget::SetBorderSize(int size)
	{
		m_borderSize.left = m_borderSize.top = m_borderSize.right = m_borderSize.bottom = size;
		Invalidate();
	}

	int BUIWidget::GetBorderStyle() const
	{
		return m_borderStyle;
	}

	void BUIWidget::SetBorderStyle(int style)
	{
		m_borderStyle = style;
		Invalidate();
	}

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
		return m_rcItem.left;
	}

	int BUIWidget::GetY()
	{
		return m_rcItem.top;
	}
	RECT BUIWidget::GetPadding() const
	{
		return m_rcPadding;
	}

	void BUIWidget::SetPadding(RECT rcPadding)
	{
		m_rcPadding = rcPadding;
	}

	SIZE BUIWidget::GetFixedXY() const
	{
		return m_cXY;
	}

	void BUIWidget::SetFixedXY(SIZE szXY)
	{
		m_cXY.cx = szXY.cx;
		m_cXY.cy = szXY.cy;
	}

	int BUIWidget::GetFixedWidth() const
	{
		return m_cxyFixed.cx;
	}

	void BUIWidget::SetFixedWidth(int cx)
	{
		if (cx < 0)
			return ;

		m_cxyFixed.cx = cx;
	}

	int BUIWidget::GetFixedHeight() const
	{
		return m_cxyFixed.cy;
	}

	void BUIWidget::SetFixedHeight(int cy)
	{
		if (cy < 0)
			return ;

		m_cxyFixed.cy = cy;
	}

	SIZE BUIWidget::EstimateSize(SIZE szAvailable)
	{
		return m_cxyFixed;
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
		DWORD bkColor2 = m_bkColor2;
		if (m_bkColor2 == 0)
			bkColor2 = m_bkColor;

		if (m_borderRound.cx > 0 || m_borderRound.cy > 0)	// 绘制圆角矩形
			BRenderEngineManager::GetInstance()->RenderEngine()->DrawRoundGradient(hDC, m_rcPaint, m_borderRound.cx, m_borderRound.cy, m_bkColor, bkColor2);
		else
			BRenderEngineManager::GetInstance()->RenderEngine()->DrawGradient(hDC, m_rcPaint, m_bkColor, bkColor2);
	}

	void BUIWidget::PaintBkImage(HDC hDC)
	{	
		if (!m_imageFileName.empty())
		{
			bstring filePath = BApplication::GetInstance()->GetApplicationPath();
			filePath += m_imageFileName;
			ImageDescription imageDesc;
			imageDesc.imageFile = filePath;
			imageDesc.rcSrc = m_rcItem;
			imageDesc.rcPaint = m_rcPaint;
			imageDesc.bScale = 1;
			imageDesc.rcCorner.left = imageDesc.rcCorner.right = m_borderRound.cx;
			imageDesc.rcCorner.top = imageDesc.rcCorner.bottom = m_borderRound.cy;
			BRenderEngineManager::GetInstance()->RenderEngine()->DrawImage(hDC, imageDesc);
			// BRenderEngineManager::GetInstance()->RenderEngine()->DrawImage(hDC, filePath.c_str(), m_rcItem, m_rcPaint);
		}
	}

	void BUIWidget::PaintStatusImage(HDC hDC)
	{
		return ;
	}

	void BUIWidget::PaintText(HDC hDC)
	{
		return ;
	}

	void BUIWidget::PaintBorder(HDC hDC)
	{
		DWORD borderColor = m_borderColor;
		if (IsFocused() && m_focusBorderColor != 0)
			borderColor = m_focusBorderColor;

		if (m_borderRound.cx > 0 || m_borderRound.cy > 0)	// 绘制圆角矩形
		{
			BRenderEngineManager::GetInstance()->RenderEngine()->DrawRoundRect(hDC, m_rcPaint, m_borderSize.left, m_borderRound.cx, m_borderRound.cy, borderColor, m_borderStyle);
		}
		else	// 绘制直角矩形
		{
			BRenderEngineManager::GetInstance()->RenderEngine()->DrawRect(hDC, m_rcPaint, m_borderSize, borderColor, m_borderStyle);
		}
	}

	void BUIWidget::Invalidate()
	{
		if (m_pUIManager != NULL)
			m_pUIManager->Invalidate(m_rcItem);
	}

	void BUIWidget::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if (_tcscmp(pstrName, _T("pos")) == 0)
		{
			RECT rcPos = { 0 };
			LPTSTR pstr = NULL;
			rcPos.left = _tcstol(pstrValue, &pstr, 10);
			rcPos.top = _tcstol(pstr + 1, &pstr, 10);
			rcPos.right = _tcstol(pstr + 1, &pstr, 10);
			rcPos.bottom = _tcstol(pstr + 1, &pstr, 10);
			SIZE szXY = {rcPos.left, rcPos.top};
			SetFixedXY(szXY);
			SetFixedWidth(rcPos.right - rcPos.left);
			SetFixedHeight(rcPos.bottom - rcPos.top);
		}
		else if(_tcscmp(pstrName, _T("padding")) == 0)
		{
			RECT rcPadding = { 0 };
			LPTSTR pstr = NULL;
			rcPadding.left = _tcstol(pstrValue, &pstr, 10); 
			rcPadding.top = _tcstol(pstr + 1, &pstr, 10); 
			rcPadding.right = _tcstol(pstr + 1, &pstr, 10); 
			rcPadding.bottom = _tcstol(pstr + 1, &pstr, 10);
			SetPadding(rcPadding);
		}
		else if (_tcscmp(pstrName, _T("bkcolor")) == 0 || _tcscmp(pstrName, _T("bkcolor1")) == 0) 
		{
			while (*pstrValue > _T('\0') && *pstrValue <= _T(' ')) 
				pstrValue = ::CharNext(pstrValue);

			if (*pstrValue == _T('#')) 
				pstrValue = ::CharNext(pstrValue);

			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetBkColor(clrColor);
		}
		else if (_tcscmp(pstrName, _T("bkcolor2")) == 0) 
		{
			while (*pstrValue > _T('\0') && *pstrValue <= _T(' ')) 
				pstrValue = ::CharNext(pstrValue);

			if (*pstrValue == _T('#')) 
				pstrValue = ::CharNext(pstrValue);

			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetBkColor2(clrColor);
		}
		else if (_tcscmp(pstrName, _T("bkimage")) == 0)
		{
			SetBkImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("bordercolor")) == 0)
		{
			if (*pstrValue == _T('#')) 
				pstrValue = ::CharNext(pstrValue);

			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetBorderColor(clrColor);
		}
		else if (_tcscmp(pstrName, _T("focusbordercolor")) == 0)
		{
			if (*pstrValue == _T('#')) 
				pstrValue = ::CharNext(pstrValue);

			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetFocusBorderColor(clrColor);
		}
		else if (_tcscmp(pstrName, _T("bordersize")) == 0)
		{
			bstring strBorderSize = pstrValue;
			if (strBorderSize.find(',') < 0)
			{
				SetBorderSize(_ttoi(strBorderSize.c_str()));
			}
			else
			{
				RECT rcBorder = { 0 };
				LPTSTR pstr = NULL;
				rcBorder.left = _tcstol(pstrValue, &pstr, 10);
				rcBorder.top = _tcstol(pstr + 1, &pstr, 10);  
				rcBorder.right = _tcstol(pstr + 1, &pstr, 10);
				rcBorder.bottom = _tcstol(pstr + 1, &pstr, 10);
				SetBorderSize(rcBorder);
			}
		}
		else if (_tcscmp(pstrName, _T("borderstyle")) == 0) 
		{
			SetBorderStyle(_ttoi(pstrValue));
		}
		else if (_tcscmp(pstrName, _T("borderround")) == 0)
		{
			SIZE cxyRound = { 0 };
			LPTSTR pstr = NULL;
			cxyRound.cx = _tcstol(pstrValue, &pstr, 10);
			cxyRound.cy = _tcstol(pstr + 1, &pstr, 10);
			SetBorderRound(cxyRound);
		}
		else if (_tcscmp(pstrName, _T("name")) == 0) SetName(pstrValue);
		else if (_tcscmp(pstrName, _T("width")) == 0) SetFixedWidth(_ttoi(pstrValue));
		else if (_tcscmp(pstrName, _T("height")) == 0) SetFixedHeight(_ttoi(pstrValue));
		else if (_tcscmp(pstrName, _T("text")) == 0) SetText(pstrValue);
		else if (_tcscmp(pstrName, _T("tooltip")) == 0) SetToolTip(pstrValue);
		else if (_tcscmp(pstrName, _T("enabled")) == 0) SetEnabled(_tcscmp(pstrValue, _T("true")) == 0);
		else if (_tcscmp(pstrName, _T("visible")) == 0) SetVisible(_tcscmp(pstrValue, _T("true")) == 0);
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
		if ((uFlags & UIFIND_VISIBLE) != 0 && !IsVisible()) 
			return NULL;

		if ((uFlags & UIFIND_ENABLED) != 0 && !IsEnabled()) 
			return NULL;

		POINT point = *static_cast<LPPOINT>(pData);
		if ((uFlags & UIFIND_HITTEST) != 0 && 
			!::PtInRect(&m_rcItem, point)) 
			return NULL;

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
