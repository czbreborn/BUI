#pragma once
#include "BUI.h"

class BUI_API BUIWidget
{
public:
	BUIWidget();
	virtual ~BUIWidget();

public:
	// ���͡�ʶ�����
	virtual bstring GetName() const;
	virtual void SetName(LPCTSTR name);

	virtual LPCTSTR GetType() const;
	virtual LPVOID GetInterface(LPCTSTR name);

	// �ı����
	virtual bstring GetText() const;
	virtual void SetText(LPCTSTR text);

	// ͼ�����
	DWORD GetBkColor() const;
	void SetBkColor(DWORD bkColor);
	DWORD GetBkColor2() const;
	void SetBkColor2(DWORD bkColor);
	LPCTSTR GetBkImage() const;
	void SetBkImage(LPCTSTR pstrImage);

	// λ�����
	virtual const RECT& GetPos() const;
	virtual RECT GetClientPos() const;

	virtual void SetPos(RECT rc);
	virtual int GetWidth() const;
	virtual int GetHeight() const;
	virtual int GetX() const;
	virtual int GetY() const;

	// ��ʾ��Ϣ
	virtual bstring GetToolTip() const;
	virtual void SetToolTip(LPCTSTR tip);

	// �������
	virtual void Paint(HDC hDC, const RECT& rcPaint);

private:
	bstring m_widgetName;

	bstring m_strText;

	DWORD m_bkColor;
	DWORD m_bkColor2;
	bstring m_imageFileName;

	RECT m_rcItem;
	SIZE m_xy;

	bstring m_toolTip;
};

