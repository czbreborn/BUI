#ifndef __BUICONTAINER_H__
#define __BUICONTAINER_H__

#pragma once

namespace BUI {
	class BUIWidget;
	class BIContainer
	{
	public:
		virtual BUIWidget* GetItem(int index) const = 0;
		virtual int GetCount() const = 0;
		virtual bool SetItem(BUIWidget* widget, int index) = 0;
		virtual bool Add(BUIWidget* widget) = 0;
		virtual bool AddAt(BUIWidget* widget, int index) = 0;
		virtual bool Remove(BUIWidget* widget) = 0;
		virtual bool RemoveAt(int index) = 0;
		virtual void RemoveAll() = 0;
	};

	class BUI_API BUIContainer : public BUIWidget, public BIContainer
	{
	public:
		DEFINE_CREATEWIDGET(BUIContainer)
		DEFINE_WIDGETTYPE(BUIContainer)

	public:
		BUIContainer(void);
		~BUIContainer(void);

	public:
		BUIWidget* GetItem(int index) const;
		int GetCount() const;
		bool SetItem(BUIWidget* widget, int index);
		bool Add(BUIWidget* widget);
		bool AddAt(BUIWidget* widget, int index);
		bool Remove(BUIWidget* widget);
		bool RemoveAt(int index);
		void RemoveAll();

	public:
		void SetPos(RECT rc);
		void DoPaint(HDC hDC, const RECT& rcPaint);
		void Event(TEventUI& event);
		void SetVisible(bool bVisible);

		virtual void SetInset(SIZE szInset);
		virtual void SetInset(RECT rcInset);
		virtual void SetPadding(int iPadding);

		// ²éÕÒ¿Ø¼þ
		BUIWidget* FindControl(FINDWIDGET Proc, LPVOID pData, UINT uFlags);

	protected:
		vector<BUIWidget*> m_itemWidget;

		RECT m_rcInset;
		int m_iPadding;
	};
}
#endif