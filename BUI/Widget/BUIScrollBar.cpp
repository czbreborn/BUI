#include "stdafx.h"

namespace BUI {
	IMPLEMENT_CREATEWIDGET(BUIScrollBar)
	IMPLEMENT_WIDGETTYPE(BUIScrollBar, BUIWidget)

	BUIScrollBar::BUIScrollBar(void)
	{
	}

	BUIScrollBar::~BUIScrollBar(void)
	{
	}

	BUIContainer* BUIScrollBar::GetOwner() const
	{
		return m_pOwner;
	}
	void BUIScrollBar::SetOwner(BUIContainer* pOwner)
	{
		m_pOwner = pOwner;
	}

	bool BUIScrollBar::IsHorizontal()
	{
		return m_bHorizontal;
	}

	void BUIScrollBar::SetHorizontal(bool horizontal/* = true*/)
	{
		if (m_bHorizontal == horizontal)
			return;

		m_bHorizontal = horizontal;
		if (m_bHorizontal) 
		{
			if (GetFixedHeight() == 0)
			{
				SIZE szXY = {0, scrollbar_defaultsize};
				SetFixedXY(szXY);
			}
		}
		else
		{
			if (GetFixedWidth() == 0)
			{
				SIZE szXY = {scrollbar_defaultsize, 0};
				SetFixedXY(szXY);
			}
		}
	}

	int BUIScrollBar::GetScrollRange() const
	{
		return m_nRange;
	}

	void BUIScrollBar::SetScrollRange(int nRange)
	{
		if (m_nRange == nRange)
			return;

		m_nRange = nRange;
		if (m_nRange < 0)
			m_nRange = 0;
		if (m_nScrollPos > m_nRange)
			m_nScrollPos = m_nRange;

		SetPos(m_rcItem);
	}

	int BUIScrollBar::GetScrollPos() const
	{
		return m_nScrollPos;
	}

	void BUIScrollBar::SetScrollPos(int nPos)
	{
		if (m_nScrollPos == nPos)
			return ;

		m_nScrollPos = nPos;
		if (m_nScrollPos < 0)
			m_nScrollPos = 0;
		if (m_nScrollPos > m_nRange)
			m_nScrollPos = m_nRange;
		SetPos(m_rcItem);
	}

	int BUIScrollBar::GetLineSize() const
	{
		return m_nLineSize;
	}

	void BUIScrollBar::SetLineSize(int nSize)
	{
		m_nLineSize = nSize;
	}

	bool BUIScrollBar::GetShowFrontButton()
	{
		return m_showFrontButton;
	}

	void BUIScrollBar::SetShowFrontButton(bool bShow)
	{
		if (m_showFrontButton == bShow)
			return;

		m_showFrontButton = bShow;
		SetPos(m_rcItem);
	}

	DWORD BUIScrollBar::GetFrontButtonColor() const
	{
		return m_frontButtonColor;
	}

	void BUIScrollBar::SetFrontButtonColor(DWORD color)
	{
		if (m_frontButtonColor == color)
			return ;

		m_frontButtonColor = color;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetFrontButtonNormalImage()
	{
		return m_frontButtonNormalImage.c_str();
	}

	void BUIScrollBar::SetFrontButtonNormalImage(LPCTSTR image)
	{
		m_frontButtonNormalImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetFrontButtonHotImage()
	{
		return m_frontButtonHotImage.c_str();
	}

	void BUIScrollBar::SetFrontButtonHotImage(LPCTSTR image)
	{
		m_frontButtonHotImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetFrontButtonPushedImage()
	{
		return m_frontButtonPushedImage.c_str();
	}

	void BUIScrollBar::SetFrontButtonPushedImage(LPCTSTR image)
	{
		m_frontButtonPushedImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetFrontButtonDisabledImage()
	{
		return m_frontButtonDisabledImage.c_str();
	}

	void BUIScrollBar::SetFrontButtonDisabledImage(LPCTSTR image)
	{
		m_frontButtonDisabledImage = image;
		Invalidate();
	}

	bool BUIScrollBar::GetShowBackButton()
	{
		return m_showBackButton;
	}

	void BUIScrollBar::SetShowBackButton(bool bShow)
	{
		if (m_showBackButton == bShow)
			return;

		m_showBackButton = bShow;
		SetPos(m_rcItem);
	}

	DWORD BUIScrollBar::GetBackButtonColor() const
	{
		return m_backButtonColor;
	}

	void BUIScrollBar::SetBackButtonColor(DWORD color)
	{
		if (m_backButtonColor == color)
			return ;

		m_backButtonColor = color;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetBackButtonNormalImage()
	{
		return m_backButtonNormalImage.c_str();
	}

	void BUIScrollBar::SetBackButtonNormalImage(LPCTSTR image)
	{
		m_backButtonNormalImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetBackButtonHotImage()
	{
		return m_backButtonHotImage.c_str();
	}

	void BUIScrollBar::SetBackButtonHotImage(LPCTSTR image)
	{
		m_backButtonHotImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetBackButtonPushedImage()
	{
		return m_backButtonPushedImage.c_str();
	}

	void BUIScrollBar::SetBackButtonPushedImage(LPCTSTR image)
	{
		m_backButtonPushedImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetBackButtonDisabledImage()
	{
		return m_backButtonDisabledImage.c_str();
	}

	void BUIScrollBar::SetBackButtonDisabledImage(LPCTSTR image)
	{
		m_backButtonDisabledImage = image;
		Invalidate();
	}

	DWORD BUIScrollBar::GetThumbColor() const
	{
		return m_thumbColor;
	}

	void BUIScrollBar::SetThumbColor(DWORD color)
	{
		if (m_thumbColor == color)
			return;
		m_thumbColor = color;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetThumbNormalImage()
	{
		return m_thumbNormalImage.c_str();
	}

	void BUIScrollBar::SetThumbNormalImage(LPCTSTR image)
	{
		if (m_thumbNormalImage == image)
			return;

		m_thumbNormalImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetThumbHotImage()
	{
		return m_thumbHotImage.c_str();
	}

	void BUIScrollBar::SetThumbHotImage(LPCTSTR image)
	{
		if (m_thumbHotImage == image)
			return;

		m_thumbHotImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetThumbPushedImage()
	{
		return m_thumbPushedImage.c_str();
	}

	void BUIScrollBar::SetThumbPushedImage(LPCTSTR image)
	{
		if (m_thumbPushedImage == image)
			return;

		m_thumbPushedImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetThumbDisabledImage()
	{
		return m_thumbDisabledImage.c_str();
	}

	void BUIScrollBar::SetThumbDisabledImage(LPCTSTR image)
	{
		if (m_thumbDisabledImage == image)
			return;

		m_thumbDisabledImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetRailNormalImage()
	{
		return m_railNormalImage.c_str();
	}

	void BUIScrollBar::SetRailNormalImage(LPCTSTR image)
	{
		if (m_railNormalImage == image)
			return;

		m_railNormalImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetRailHotImage()
	{
		return m_railHotImage.c_str();
	}

	void BUIScrollBar::SetRailHotImage(LPCTSTR image)
	{
		if (m_railHotImage == image)
			return;

		m_railHotImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetRailPushedImage()
	{
		return m_railPushedImage.c_str();
	}

	void BUIScrollBar::SetRailPushedImage(LPCTSTR image)
	{
		if (m_railPushedImage == image)
			return;

		m_railPushedImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetRailDisabledImage()
	{
		return m_railDisabledImage.c_str();
	}

	void BUIScrollBar::SetRailDisabledImage(LPCTSTR image)
	{
		if (m_railDisabledImage == image)
			return;

		m_railDisabledImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetBkNormalImage()
	{
		return m_bkNormalImage.c_str();
	}

	void BUIScrollBar::SetBkNormalImage(LPCTSTR image)
	{
		if (m_bkNormalImage == image)
			return;

		m_bkNormalImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetBkHotImage()
	{
		return m_bkHotImage.c_str();
	}

	void BUIScrollBar::SetBkHotImage(LPCTSTR image)
	{
		if (m_bkHotImage == image)
			return;

		m_bkHotImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetBkPushedImage()
	{
		return m_bkPushedImage.c_str();
	}

	void BUIScrollBar::SetBkPushedImage(LPCTSTR image)
	{
		if (m_bkPushedImage == image)
			return;

		m_bkPushedImage = image;
		Invalidate();
	}

	LPCTSTR BUIScrollBar::GetBkDisabledImage()
	{
		return m_bkDisabledImage.c_str();
	}

	void BUIScrollBar::SetBkDisabledImage(LPCTSTR image)
	{
		if (m_bkDisabledImage == image)
			return;

		m_bkDisabledImage = image;
		Invalidate();
	}

	void BUIScrollBar::SetPos(RECT rc)
	{
		BUIWidget::SetPos(rc);
		RECT rcPos = m_rcItem;

		if (m_bHorizontal)
		{
			int horizontalLength = rcPos.right - rcPos.left;
			if (m_showFrontButton)
				horizontalLength -= m_cxyFixed.cy;
			if (m_showBackButton)
				horizontalLength -= m_cxyFixed.cy;
			if (horizontalLength > m_cxyFixed.cy)
			{
				SetFrontButtonPos(rcPos, m_cxyFixed.cy);
				SetBackButtonPos(rcPos, m_cxyFixed.cy);
			
				m_rcThumb.top = rcPos.top;
				m_rcThumb.bottom = rcPos.top + m_cxyFixed.cy;
				if (m_nRange > 0)
				{
					int cxThumb = horizontalLength * (rc.right - rc.left) / (m_nRange + rcPos.right - rcPos.left);
					if (cxThumb < m_cxyFixed.cy)	// 保证不能小于按钮的宽度
						cxThumb = m_cxyFixed.cy;

					m_rcThumb.left = m_nScrollPos * (horizontalLength - cxThumb) / m_nRange + m_rcFrontButton.right;
					m_rcThumb.right = m_rcThumb.left + cxThumb;
					if (m_rcThumb.right > m_rcBackButton.left)
					{
						m_rcThumb.left = m_rcBackButton.left - cxThumb;
						m_rcThumb.right = m_rcBackButton.left;
					}
				}
				else
				{
					m_rcThumb.left = m_rcFrontButton.right;
					m_rcThumb.right = m_rcBackButton.left;
				}
			}
			else
			{
				int cxButton = (rcPos.right - rcPos.left) / 2;
				if (cxButton > m_cxyFixed.cy)
					cxButton = m_cxyFixed.cy;
				SetFrontButtonPos(rcPos, m_cxyFixed.cy);
				m_rcFrontButton.right += cxButton - m_cxyFixed.cy;
				SetBackButtonPos(rcPos, m_cxyFixed.cy);
				m_rcBackButton.left -= cxButton - m_cxyFixed.cy;

				::ZeroMemory(&m_rcThumb, sizeof(m_rcThumb));
			}
		}
		else
		{
			int verticalLength = rcPos.right - rcPos.left;
			if (m_showFrontButton)
				verticalLength -= m_cxyFixed.cx;
			if (m_showBackButton)
				verticalLength -= m_cxyFixed.cx;
			if (verticalLength > m_cxyFixed.cx)
			{
				SetFrontButtonPos(rcPos, m_cxyFixed.cx);
				SetBackButtonPos(rcPos, m_cxyFixed.cx);

				m_rcThumb.left = rcPos.left;
				m_rcThumb.right = rcPos.left + m_cxyFixed.cx;
				if (m_nRange > 0)
				{
					int cyThumb = verticalLength * (rc.bottom - rc.top) / (m_nRange + rcPos.bottom - rcPos.top);
					if (cyThumb < m_cxyFixed.cx)	// 保证不能小于按钮的宽度
						cyThumb = m_cxyFixed.cx;

					m_rcThumb.top = m_nScrollPos * (verticalLength - cyThumb) / m_nRange + m_rcFrontButton.bottom;
					m_rcThumb.bottom = m_rcThumb.left + cyThumb;
					if (m_rcThumb.bottom > m_rcBackButton.top)
					{
						m_rcThumb.top = m_rcBackButton.top - cyThumb;
						m_rcThumb.bottom = m_rcBackButton.top;
					}
				}
				else
				{
					m_rcThumb.top = m_rcFrontButton.bottom;
					m_rcThumb.bottom = m_rcBackButton.top;
				}
			}
			else
			{
				int cyButton = (rcPos.bottom - rcPos.top) / 2;
				if (cyButton > m_cxyFixed.cx)
					cyButton = m_cxyFixed.cx;
				SetFrontButtonPos(rcPos, m_cxyFixed.cx);
				m_rcFrontButton.bottom += cyButton - m_cxyFixed.cx;
				SetBackButtonPos(rcPos, m_cxyFixed.cx);
				m_rcBackButton.top -= cyButton - m_cxyFixed.cx;

				::ZeroMemory(&m_rcThumb, sizeof(m_rcThumb));
			}
		}
	}

	void BUIScrollBar::Event(TEventUI& event)
	{

	}

	void BUIScrollBar::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if (_tcscmp(pstrName, _T("fbtncolor")) == 0) 
		{
			BUIAttributeParser::SkipSpecifySymbol(pstrName, _T('\0'), _T(' '));
			BUIAttributeParser::SkipOneHashSymbol(pstrName);

			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetFrontButtonColor(clrColor);
		}
		else if (_tcscmp(pstrName, _T("fbtnnormalimage")) == 0)
		{
			SetFrontButtonNormalImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("fbtnhotimage")) == 0)
		{
			SetFrontButtonHotImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("fbtnpushedimage")) == 0)
		{
			SetFrontButtonPushedImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("fbtndisabledimage")) == 0) 
		{
			SetFrontButtonDisabledImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("bbtncolor")) == 0)
		{
			BUIAttributeParser::SkipSpecifySymbol(pstrName, _T('\0'), _T(' '));
			BUIAttributeParser::SkipOneHashSymbol(pstrName);

			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetBackButtonColor(clrColor);
		}
		else if (_tcscmp(pstrName, _T("bbtnnormalimage")) == 0)
		{
			SetBackButtonNormalImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("bbtnhotimage")) == 0)
		{
			SetBackButtonHotImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("bbtnpushedimage")) == 0)
		{
			SetBackButtonPushedImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("bbtndisabledimage")) == 0)
		{
			SetBackButtonDisabledImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("thumbcolor")) == 0)
		{
			BUIAttributeParser::SkipSpecifySymbol(pstrName, _T('\0'), _T(' '));
			BUIAttributeParser::SkipOneHashSymbol(pstrName);

			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetThumbColor(clrColor);
		}
		else if (_tcscmp(pstrName, _T("thumbnormalimage")) == 0)
		{
			SetThumbNormalImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("thumbhotimage")) == 0)
		{
			SetThumbHotImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("thumbpushedimage")) == 0)
		{
			SetThumbPushedImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("thumbdisabledimage")) == 0) 
		{
			SetThumbDisabledImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("railnormalimage")) == 0)
		{
			SetRailNormalImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("railhotimage")) == 0)
		{
			SetRailHotImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("railpushedimage")) == 0) 
		{
			SetRailPushedImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("raildisabledimage")) == 0)
		{
			SetRailDisabledImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("bknormalimage")) == 0)
		{
			SetBkNormalImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("bkhotimage")) == 0)
		{
			SetBkHotImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("bkpushedimage")) == 0) 
		{
			SetBkPushedImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("bkdisabledimage")) == 0)
		{
			SetBkDisabledImage(pstrValue);
		}
		else if (_tcscmp(pstrName, _T("hor")) == 0 )
		{
			SetHorizontal(_tcscmp(pstrValue, _T("true")) == 0);
		}
		else if (_tcscmp(pstrName, _T("linesize")) == 0)
		{
			SetLineSize(_ttoi(pstrValue));
		}
		else if (_tcscmp(pstrName, _T("range")) == 0)
		{
			SetScrollRange(_ttoi(pstrValue));
		}
		else if (_tcscmp(pstrName, _T("value")) == 0)
		{
			SetScrollPos(_ttoi(pstrValue));
		}
		else if (_tcscmp(pstrName, _T("showfbtn")) == 0)
		{
			SetShowFrontButton(_tcscmp(pstrValue, _T("true")) == 0);
		}
		else if (_tcscmp(pstrName, _T("showbbtn")) == 0)
		{
			SetShowBackButton(_tcscmp(pstrValue, _T("true")) == 0);
		}
		else
		{
			BUIWidget::SetAttribute(pstrName, pstrValue);
		}
	}

	void BUIScrollBar::DoPaint(HDC hDC, const RECT& rcPaint)
	{
		if (!::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem))
			return;

		// 更新状态，绘制时根据状态绘制不同的效果
		UpdateThumbState();
		UpdateButtonState();

		PaintBkColor(hDC);
		PaintBkImage(hDC);
		PaintBk(hDC);
		PaintFrontButton(hDC);
		PaintBackButton(hDC);
		PaintThumb(hDC);
		PaintRail(hDC);
	}

	void BUIScrollBar::PaintBk(HDC hDC)
	{
		bstring bkimage;
		if ((m_uThumbState & UISTATE_DISABLED) != 0)
		{
			bkimage = m_bkDisabledImage;
		}
		else if ((m_uThumbState & UISTATE_PUSHED) != 0)
		{
			bkimage = m_bkPushedImage;
		}
		else if ((m_uThumbState & UISTATE_HOT) != 0)
		{
			bkimage = m_bkHotImage;
		}
		else
		{
			bkimage = m_bkNormalImage;
		}
		ImageDescription imageDesc;
		imageDesc.imageFile = bkimage;
		imageDesc.rcSrc = m_rcItem;
		imageDesc.rcPaint = m_rcPaint;
		imageDesc.bScale = 0;
		BRenderEngineManager::GetInstance()->RenderEngine()->DrawImage(hDC, imageDesc);
		//BRenderEngineManager::GetInstance()->RenderEngine()->DrawImage(hDC, bkimage.c_str(), m_rcItem, m_rcPaint);
	}

	void BUIScrollBar::PaintFrontButton(HDC hDC)
	{
		bstring fbtnImage;
		if ((m_frontButtonState & UISTATE_DISABLED) != 0)
		{
			fbtnImage = m_frontButtonDisabledImage;
		}
		else if ((m_frontButtonState & UISTATE_PUSHED) != 0)
		{
			fbtnImage = m_frontButtonPushedImage;
		}
		else if ((m_frontButtonState & UISTATE_HOT) != 0)
		{
			fbtnImage = m_frontButtonHotImage;
		}
		else
		{
			fbtnImage = m_frontButtonNormalImage;
		}
		ImageDescription imageDesc;
		imageDesc.imageFile = fbtnImage;
		imageDesc.rcSrc = m_rcFrontButton;
		imageDesc.rcPaint = m_rcPaint;
		imageDesc.bScale = 0;
		BRenderEngineManager::GetInstance()->RenderEngine()->DrawImage(hDC, imageDesc);
		//BRenderEngineManager::GetInstance()->RenderEngine()->DrawImage(hDC, fbtnImage.c_str(), m_rcFrontButton, m_rcPaint);
	}

	void BUIScrollBar::PaintBackButton(HDC hDC)
	{
		bstring bbtnImage;
		if ((m_backButtonState & UISTATE_DISABLED) != 0)
		{
			bbtnImage = m_backButtonDisabledImage;
		}
		else if ((m_backButtonState & UISTATE_PUSHED) != 0)
		{
			bbtnImage = m_backButtonPushedImage;
		}
		else if ((m_backButtonState & UISTATE_HOT) != 0)
		{
			bbtnImage = m_backButtonHotImage;
		}
		else
		{
			bbtnImage = m_backButtonNormalImage;
		}
		ImageDescription imageDesc;
		imageDesc.imageFile = bbtnImage;
		imageDesc.rcSrc = m_rcBackButton;
		imageDesc.rcPaint = m_rcPaint;
		imageDesc.bScale = 0;
		BRenderEngineManager::GetInstance()->RenderEngine()->DrawImage(hDC, imageDesc);
		// BRenderEngineManager::GetInstance()->RenderEngine()->DrawImage(hDC, bbtnImage.c_str(), m_rcBackButton, m_rcPaint);
	}

	void BUIScrollBar::PaintThumb(HDC hDC)
	{
		bstring thumbImage;
		if ((m_uThumbState & UISTATE_DISABLED) != 0)
		{
			thumbImage = m_thumbDisabledImage;
		}
		else if ((m_uThumbState & UISTATE_PUSHED) != 0)
		{
			thumbImage = m_thumbPushedImage;
		}
		else if ((m_uThumbState & UISTATE_HOT) != 0)
		{
			thumbImage = m_thumbHotImage;
		}
		else
		{
			thumbImage = m_thumbNormalImage;
		}
		ImageDescription imageDesc;
		imageDesc.imageFile = thumbImage;
		imageDesc.rcSrc = m_rcThumb;
		imageDesc.rcPaint = m_rcPaint;
		imageDesc.bScale = 0;
		BRenderEngineManager::GetInstance()->RenderEngine()->DrawImage(hDC, imageDesc);
		// BRenderEngineManager::GetInstance()->RenderEngine()->DrawImage(hDC, thumbImage.c_str(), m_rcThumb, m_rcPaint);
	}

	void BUIScrollBar::PaintRail(HDC hDC)
	{
		bstring railImage;
		RECT rc = {0};
		if( !m_bHorizontal ) {
			rc.left = m_rcThumb.left - m_rcItem.left;
			rc.top = (m_rcThumb.top + m_rcThumb.bottom) / 2 - m_rcItem.top - m_cxyFixed.cx / 2;
			rc.right = m_rcThumb.right - m_rcItem.left;
			rc.bottom = (m_rcThumb.top + m_rcThumb.bottom) / 2 - m_rcItem.top + m_cxyFixed.cx - m_cxyFixed.cx / 2;
		}
		else {
			rc.left = (m_rcThumb.left + m_rcThumb.right) / 2 - m_rcItem.left - m_cxyFixed.cy / 2;
			rc.top = m_rcThumb.top - m_rcItem.top;
			rc.right = (m_rcThumb.left + m_rcThumb.right) / 2 - m_rcItem.left + m_cxyFixed.cy - m_cxyFixed.cy / 2;
			rc.bottom = m_rcThumb.bottom - m_rcItem.top;
		}

		if ((m_uThumbState & UISTATE_DISABLED) != 0)
		{
			railImage = m_railDisabledImage;
		}
		else if ((m_uThumbState & UISTATE_PUSHED) != 0)
		{
			railImage = m_railPushedImage;
		}
		else if ((m_uThumbState & UISTATE_HOT) != 0)
		{
			railImage = m_railHotImage;
		}
		else
		{
			railImage = m_railNormalImage;
		}
		ImageDescription imageDesc;
		imageDesc.imageFile = railImage;
		imageDesc.rcSrc = rc;
		imageDesc.rcPaint = m_rcPaint;
		imageDesc.bScale = 0;
		BRenderEngineManager::GetInstance()->RenderEngine()->DrawImage(hDC, imageDesc);
		// BRenderEngineManager::GetInstance()->RenderEngine()->DrawImage(hDC, railImage.c_str(), rc, m_rcPaint);
	}

	void BUIScrollBar::SetFrontButtonPos(const RECT& rc, int width)
	{
		m_rcFrontButton.left = rc.left;
		m_rcFrontButton.top = rc.top;
		if (m_showFrontButton)
		{
			m_rcFrontButton.right = rc.left + width;
			m_rcFrontButton.bottom = rc.top + width;
		}
		else
		{
			m_rcFrontButton.right = m_rcFrontButton.left;
			m_rcFrontButton.bottom = m_rcFrontButton.top;
		}
	}

	void BUIScrollBar::SetBackButtonPos(const RECT& rc, int width)
	{
		m_rcBackButton.right = rc.right;
		m_rcBackButton.top = rc.top;
		if (m_showFrontButton)
		{
			m_rcBackButton.left = rc.right - width;
			m_rcBackButton.bottom = rc.top + width;
		}
		else
		{
			m_rcBackButton.left = m_rcBackButton.right;
			m_rcBackButton.bottom = m_rcBackButton.top;
		}
	}

	void BUIScrollBar::UpdateThumbState()
	{
		if (!IsEnabled())
			m_uThumbState |= UISTATE_DISABLED;
		else
			m_uThumbState &= ~UISTATE_DISABLED;
	}

	void BUIScrollBar::UpdateButtonState()
	{
		if (!IsEnabled())
		{
			m_frontButtonState |= UISTATE_DISABLED;
			m_backButtonState |= UISTATE_DISABLED;
		}
		else
		{
			m_frontButtonState &= ~UISTATE_DISABLED;
			m_backButtonState &= ~UISTATE_DISABLED;
		}
	}
}