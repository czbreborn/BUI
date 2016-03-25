#include "stdafx.h"

namespace BUI{
	IMPLEMENT_CREATEWIDGET(BUIVerticalLayout)
	IMPLEMENT_WIDGETTYPE(BUIVerticalLayout, BUIContainer)

	BUIVerticalLayout::BUIVerticalLayout(void)
	{
	}

	BUIVerticalLayout::~BUIVerticalLayout(void)
	{
	}

	void BUIVerticalLayout::DoEvent(TEventUI& event)
	{

	}

	void BUIVerticalLayout::SetPos(RECT rc, bool bNeedInvalidate/* = true*/)
	{
		BUIContainer::SetPos(rc);
		// 调整内边距
		rc.left += m_rcInset.left;
		rc.top += m_rcInset.top;
		rc.right -= m_rcInset.right;
		rc.bottom -= m_rcInset.bottom;

		// Determine the minimum size
		SIZE szAvailable = { rc.right - rc.left, rc.bottom - rc.top };
		int nAdjustables = 0;
		int cyFixed = 0;
		for (int index = 0; index < GetCount(); index++)
		{
			BUIWidget* pWidget = GetItem(index);
			if (pWidget == NULL)
				continue;
			if (pWidget->IsVisible())
				continue;

			SIZE sz = pWidget->EstimateSize(szAvailable);
			if( sz.cy == 0 ) 
				nAdjustables++;

			cyFixed += sz.cy + m_iPadding;
		}

		// Place elements
		int cyNeeded = 0;
		int cyExpand = 0;
		if (nAdjustables > 0) 
			cyExpand = max(0, (szAvailable.cy - cyFixed) / nAdjustables);

		// Position the elements
		SIZE szRemaining = szAvailable;
		int	yPos = rc.top;
		int iAdjustable = 0;
		for (int index = 0; index < GetCount(); index++)
		{
			BUIWidget* pWidget = GetItem(index);
			if (pWidget == NULL)
				continue;
			if (pWidget->IsVisible())
				continue;

			SIZE sz = pWidget->EstimateSize(szRemaining);
			if( sz.cy == 0 ) 
			{
				iAdjustable++;
				sz.cy = cyExpand;
				// Distribute remaining to last element (usually round-off left-overs)
				if (iAdjustable == nAdjustables)	// 分配最后剩下的高度给最后一个元素
					sz.cy += max(0, szAvailable.cy - (cyExpand * nAdjustables) - cyFixed);
			}

			RECT rcPos = { rc.left, yPos, rc.right, yPos + sz.cy };
			pWidget->SetPos(rcPos);
			yPos += sz.cy + m_iPadding;
			cyNeeded += sz.cy + m_iPadding;
			szRemaining.cy -= sz.cy + m_iPadding;
		}
	}
}