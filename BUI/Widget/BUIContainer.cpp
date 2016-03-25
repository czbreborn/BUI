#include "stdafx.h"

namespace BUI {
	IMPLEMENT_CREATEWIDGET(BUIContainer)
	IMPLEMENT_WIDGETTYPE(BUIContainer, BUIWidget)

	BUIContainer::BUIContainer(void)
	: m_iPadding(0)
	{
		::ZeroMemory(&m_rcInset, sizeof(m_rcInset));
	}

	BUIContainer::~BUIContainer(void)
	{
	}

	BUIWidget* BUIContainer::GetItem(int index) const
	{
		BUIWidget* widget = NULL;
		if (index >=0 && (unsigned int)index < m_itemWidget.size())
			widget = m_itemWidget[index];

		return widget;
	}

	int BUIContainer::GetCount() const
	{
		return m_itemWidget.size();
	}

	bool BUIContainer::SetItem(BUIWidget* widget, int index)
	{
		bool bRemove = Remove(widget);
		if (!bRemove)
			return false;

		return AddAt(widget, index);
	}

	bool BUIContainer::Add(BUIWidget* widget)
	{
		m_itemWidget.push_back(widget);
		return true;
	}

	bool BUIContainer::AddAt(BUIWidget* widget, int index)
	{
		if (index >= 0 && (unsigned int)index < m_itemWidget.size())
		{
			int pos = index - 1;
			m_itemWidget.insert(m_itemWidget.begin() + pos, widget);
			return true;
		}
		return false;
	}

	bool BUIContainer::Remove(BUIWidget* widget)
	{
		vector<BUIWidget*>::iterator it = std::find(m_itemWidget.begin(), m_itemWidget.end(), widget);
		if (it != m_itemWidget.end())
		{
			m_itemWidget.erase(it);
			return true;
		}

		return false;
	}

	bool BUIContainer::RemoveAt(int index)
	{
		BUIWidget* widget = GetItem(index);
		if (widget == NULL)
			return false;

		return Remove(widget);
	}

	void BUIContainer::RemoveAll()
	{
		m_itemWidget.clear();
	}

	void BUIContainer::Event(TEventUI& event)
	{

	}

	void BUIContainer::SetVisible(bool bVisible)
	{
		for (unsigned int index = 0; index < m_itemWidget.size(); index++ )
		{
			static_cast<BUIWidget*>(m_itemWidget[index])->SetVisible(bVisible);
		}

		BUIWidget::SetVisible(bVisible);
	}

	void BUIContainer::SetPos(RECT rc)
	{
		BUIWidget::SetPos(rc);
	}

	void BUIContainer::DoPaint(HDC hDC, const RECT& rcPaint)
	{
		RECT rcTemp = { 0 };
		if (!::IntersectRect(&rcTemp, &rcPaint, &GetPos())) 
			return;

		for (unsigned int index = 0; index < m_itemWidget.size(); index++ ) {
			BUIWidget* pWidget = static_cast<BUIWidget*>(m_itemWidget[index]);
			if (!pWidget->IsVisible()) 
				continue;

			if (!::IntersectRect(&rcTemp, &rcPaint, &pWidget->GetPos())) 
				continue;

			if (!::IntersectRect(&rcTemp, &GetPos(), &pWidget->GetPos())) 
				continue;
			
			pWidget->DoPaint(hDC, rcPaint);
		}
	}

	void BUIContainer::SetInset(SIZE szInset)
	{
		m_rcInset.left = m_rcInset.right = szInset.cx;
		m_rcInset.top = m_rcInset.bottom = szInset.cy;
	}

	void BUIContainer::SetInset(RECT rcInset)
	{
		m_rcInset = rcInset;
	}

	void BUIContainer::SetPadding(int iPadding)
	{
		m_iPadding = iPadding;
	}

}