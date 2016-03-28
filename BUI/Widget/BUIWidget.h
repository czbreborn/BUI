#ifndef __BUIWIDGET_H__
#define __BUIWIDGET_H__

#pragma once

namespace BUI {
	typedef BUIWidget* (CALLBACK *FINDWIDGET)(BUIWidget*, LPVOID);

	class BUI_API BUIWidget
	{
	public:
		DEFINE_CREATEWIDGET(BUIWidget)

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

		// 边框相关
		DWORD GetBorderColor() const;
		void SetBorderColor(DWORD borderColor);
		DWORD GetFocusBorderColor() const;
		void SetFocusBorderColor(DWORD focusBorderColor);
		SIZE GetBorderRound() const;
		void SetBorderRound(SIZE cxyRound);
		RECT GetBorderSize() const;
		void SetBorderSize(RECT rc);
		void SetBorderSize(int size);
		int GetBorderStyle() const;
		void SetBorderStyle(int style);

		// 位置相关
		virtual const RECT& GetPos();
		virtual RECT GetClientPos();
		virtual void SetPos(RECT rc);
		virtual int GetWidth();
		virtual int GetHeight();
		virtual int GetX();
		virtual int GetY();
		virtual RECT GetPadding() const;
		virtual void SetPadding(RECT rcPadding); 		// 设置外边距，由上层窗口绘制
		virtual SIZE GetFixedXY() const;         		// 实际大小位置使用GetPos获取，这里得到的是预设的参考值
		virtual void SetFixedXY(SIZE szXY);      		// 仅float为true时有效
		virtual int GetFixedWidth() const;       		// 实际大小位置使用GetPos获取，这里得到的是预设的参考值
		virtual void SetFixedWidth(int cx);      		// 预设的参考值
		virtual int GetFixedHeight() const;      		// 实际大小位置使用GetPos获取，这里得到的是预设的参考值
		virtual void SetFixedHeight(int cy);     		// 预设的参考值
		virtual SIZE EstimateSize(SIZE szAvailable);	// 预估控件大小

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

	protected:
		BUIManager*	m_pUIManager;
		BUIWidget*	m_parent;
		bstring m_widgetName;

		bstring m_strText;
		bstring m_toolTip;

		DWORD m_bkColor;
		DWORD m_bkColor2;
		DWORD m_borderColor;
		DWORD m_focusBorderColor;
		int m_borderStyle;
		SIZE m_borderRound;
		RECT m_borderSize;
		bstring m_imageFileName;

		SIZE m_cXY;
		SIZE m_cxyFixed;
		RECT m_rcPadding;
		RECT m_rcItem;
		RECT m_rcPaint;

		bool m_bVisible;
		bool m_bEnabled;
		bool m_bFocused;
	};
}
#endif