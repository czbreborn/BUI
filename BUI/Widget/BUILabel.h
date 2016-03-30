#ifndef __BUILABEL_H__
#define __BUILABEL_H__

#pragma once

namespace BUI{
	class BUI_API BUILabel : public BUIWidget
	{
	public:
		DEFINE_CREATEWIDGET(BUILabel)
		DEFINE_WIDGETTYPE(BUILabel)

	public:				
		BUILabel();
		virtual ~BUILabel();

	public:
		// 文字样式，粗体、斜体等
		void SetTextStyle(int style);
		int GetTextStyle() const;
		// color和color1用于文字渐变
		void SetTextColor(DWORD textColor);
		DWORD GetTextColor() const;
		void SetTextColor1(DWORD textColor);
		DWORD GetTextColor1() const;
		// 文字位置
		void SetTextAlign(UINT align);
		UINT GetTextAlign();

		// 发光字体
		void SetEnabledGlow(bool enabledGlow);
		bool GetEnabledGlow();
		void SetGlowColor(DWORD glowColor);
		DWORD GetGlowColor();

		// 文字描边
		void SetEnabledStroke(bool enabledStroke);
		bool GetEnabledStroke();
		void SetStrokeColor(DWORD strokeColor);
		DWORD GetStrokeColor();
		void SetStrokeColor1(DWORD strokeColor);
		DWORD GetStrokeColor1();

		// 控件属性相关
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	public:
		void PaintText(HDC hDC);
		void Event(TEventUI& event);

	protected:
		TextDescription m_textDesc;
	};
} // namespace BUI

#endif