#include "stdafx.h"

namespace BUI {
	IMPLEMENT_CREATEWIDGET(BUIHorizontalLayout)
	IMPLEMENT_WIDGETTYPE(BUIHorizontalLayout, BUIContainer)

	BUIHorizontalLayout::BUIHorizontalLayout(void)
	{
	}

	BUIHorizontalLayout::~BUIHorizontalLayout(void)
	{
	}

	void BUIHorizontalLayout::Event(TEventUI& event)
	{
		BUIContainer::Event(event);
	}

	void BUIHorizontalLayout::SetPos(RECT rc)
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
		int cxFixed = 0;
		for (int index = 0; index < GetCount(); index++)
		{
			BUIWidget* pWidget = GetItem(index);
			if (pWidget == NULL)
				continue;
			if (!pWidget->IsVisible())
				continue;

			SIZE sz = pWidget->EstimateSize(szAvailable);
			if( sz.cx == 0 ) 
				nAdjustables++;

			cxFixed += sz.cx + m_iPadding;
		}

		// Place elements
		int cxNeeded = 0;
		int cxExpand = 0;
		if (nAdjustables > 0) 
			cxExpand = max(0, (szAvailable.cx - cxFixed) / nAdjustables);

		// Position the elements
		SIZE szRemaining = szAvailable;
		int	xPos = rc.left;
		int iAdjustable = 0;
		for (int index = 0; index < GetCount(); index++)
		{
			BUIWidget* pWidget = GetItem(index);
			if (pWidget == NULL)
				continue;
			if (!pWidget->IsVisible())
				continue;

			SIZE sz = pWidget->EstimateSize(szRemaining);
			if( sz.cx == 0 ) 
			{
				iAdjustable++;
				sz.cx = cxExpand;
				// Distribute remaining to last element (usually round-off left-overs)
				if (iAdjustable == nAdjustables)	// 分配最后剩下的高度给最后一个元素
					sz.cx += max(0, szAvailable.cx - (cxExpand * nAdjustables) - cxFixed);
			}

			RECT rcPos = { xPos, rc.top, xPos + sz.cx, rc.bottom};
			pWidget->SetPos(rcPos);
			xPos += sz.cx + m_iPadding;
			cxNeeded += sz.cx + m_iPadding;
			szRemaining.cx -= sz.cx + m_iPadding;
		}
	}
}
