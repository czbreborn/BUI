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
		// ������ʽ�����塢б���
		void SetTextStyle(int style);
		int GetTextStyle() const;
		// color��color1�������ֽ���
		void SetTextColor(DWORD textColor);
		DWORD GetTextColor() const;
		void SetTextColor1(DWORD textColor);
		DWORD GetTextColor1() const;
		// ����λ��
		void SetTextAlign(UINT align);
		UINT GetTextAlign();

		// ��������
		void SetEnabledGlow(bool enabledGlow);
		bool GetEnabledGlow();
		void SetGlowColor(DWORD glowColor);
		DWORD GetGlowColor();

		// �������
		void SetEnabledStroke(bool enabledStroke);
		bool GetEnabledStroke();
		void SetStrokeColor(DWORD strokeColor);
		DWORD GetStrokeColor();
		void SetStrokeColor1(DWORD strokeColor);
		DWORD GetStrokeColor1();

		// �ؼ��������
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	public:
		void PaintText(HDC hDC);
		void Event(TEventUI& event);

	protected:
		TextDescription m_textDesc;
	};
} // namespace BUI

#endif