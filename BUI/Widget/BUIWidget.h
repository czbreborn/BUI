#ifndef __BUIWIDGET_H__
#define __BUIWIDGET_H__

#pragma once

namespace BUI {
	typedef BUIWidget* (CALLBACK *FINDWIDGET)(BUIWidget*, LPVOID);

	class BUI_API BUIWidget
	{
	public:
		BUIWidget();
		virtual ~BUIWidget();

	public:
		// 类型、识别相关
		virtual bstring GetName();
		virtual void SetName(LPCTSTR name);

		virtual LPCTSTR GetType();
		virtual LPVOID GetInterface(LPCTSTR name);

		// 文本相关
		virtual LPCTSTR GetText();
		virtual void SetText(LPCTSTR text);
		// 提示信息
		virtual LPCTSTR GetToolTip();
		virtual void SetToolTip(LPCTSTR tip);

		// 图形相关
		DWORD GetBkColor();
		void SetBkColor(DWORD bkColor);
		DWORD GetBkColor2();
		void SetBkColor2(DWORD bkColor);
		LPCTSTR GetBkImage();
		void SetBkImage(LPCTSTR pstrImage);

		// 位置相关
		virtual const RECT& GetPos();
		virtual RECT GetClientPos();
		virtual void SetPos(RECT rc);
		virtual int GetWidth();
		virtual int GetHeight();
		virtual int GetX();
		virtual int GetY();

		// 绘制相关
		virtual void Paint(HDC hDC, const RECT& rcPaint);
		virtual void DoPaint(HDC hDC, const RECT& rcPaint);
		virtual void PaintBkColor(HDC hDC);
		virtual void PaintBkImage(HDC hDC);
		virtual void PaintStatusImage(HDC hDC);
		virtual void PaintText(HDC hDC);
		virtual void PaintBorder(HDC hDC);

		void Invalidate();

		// 控件属性相关
		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		
		// 控件事件处理
		virtual void Event(TEventUI& event);

		// 控件管理
		virtual BUIManager* GetManager() const;
		virtual void SetManager(BUIManager* uiManager, BUIWidget* parent);
		virtual BUIWidget* GetParent() const;

		// 查找控件
		virtual BUIWidget* FindControl(FINDWIDGET Proc, LPVOID pData, UINT uFlags);

		// 控件状态
		virtual bool IsVisible() const;
		virtual bool IsEnabled() const;
		virtual bool IsFocused() const;
		virtual void SetVisible(bool bVisible = true);
		virtual void SetEnabled(bool bEnable = true);
		virtual	void SetFocus();

	private:
		BUIManager*	m_pUIManager;
		BUIWidget*	m_parent;
		bstring m_widgetName;

		bstring m_strText;
		bstring m_toolTip;

		DWORD m_bkColor;
		DWORD m_bkColor2;
		bstring m_imageFileName;

		RECT m_rcItem;
		SIZE m_xy;
		RECT m_rcPaint;
		bool m_bVisible;
		bool m_bEnabled;
		bool m_bFocused;
	};
}
#endif