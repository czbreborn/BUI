#ifndef __BUIWIDGETDEF_H__
#define __BUIWIDGETDEF_H__

#pragma once

namespace BUI{
class BUIWidget;

	typedef struct tagTEventUI
	{
		int type;				// 类型
		BUIWidget* pSender;		// 发送者
		DWORD dwTimestamp;		// 发送时间
		POINT ptMouse;			// 触发的坐标点
		TCHAR chKey;			// 对应的按键
		WORD wKeyState;			// 按键状态
		WPARAM wParam;			// 参数1
		LPARAM lParam;			// 参数2
	} TEventUI;
	
	// 事件类型
	typedef enum EVENTTYPE
	{
		uievent__first = 0,
		uievent_mousemove,
		uievent_mouseleave,
		uievent_mouseenter,
		uievent_mousehover,
		uievent_keydown,
		uievent_keyup,
		uievent_char,
		uievent_syskey,
		uievent_killfocus,
		uievent_setfocus,
		uievent_buttondown,
		uievent_buttonup,
		uievent_dblclick,
		uievent_contextmenu,
		uievent_vscroll,
		uievent_hscroll,
		uievent_scrollwheel,
		uievent_windowsize,
		uievent_setcursor,
		uievent_measureitem,
		uievent_drawitem,
		uievent_timer,
		uievent_notify,
		uievent_command,
		uievent__last
	};

	// 控件标识名称
	#define BUI_WIN_WIDGET		_T("BUIWidget")
	#define BUI_WIN_LABEL		_T("BUILabel")
	#define BUI_WIN_BUTTON		_T("BUIButton")

	#define UIFLAG_TABSTOP       0x00000001
	#define UIFLAG_SETCURSOR     0x00000002
	#define UIFLAG_WANTRETURN    0x00000004

	// Flags for FindControl()
	#define UIFIND_ALL           0x00000000
	#define UIFIND_VISIBLE       0x00000001
	#define UIFIND_ENABLED       0x00000002
	#define UIFIND_HITTEST       0x00000004
	#define UIFIND_ME_FIRST      0x80000000

	// Flags used for controlling the paint
	#define UISTATE_FOCUSED      0x00000001
	#define UISTATE_SELECTED     0x00000002
	#define UISTATE_DISABLED     0x00000004
	#define UISTATE_HOT          0x00000008
	#define UISTATE_PUSHED       0x00000010
	#define UISTATE_READONLY     0x00000020
	#define UISTATE_CAPTURED     0x00000040

	// 控件类型定义
	#define DEFINE_WIDGETTYPE(classtype)				\
		LPCTSTR GetType() const;						\
		LPVOID GetInterface(LPCTSTR name);

	#define IMPLEMENT_WIDGETTYPE(classtype, baseclass)	\
		class baseclass;								\
		LPCTSTR classtype::GetType() const				\
		{												\
			return _T(#classtype);						\
		}												\
		LPVOID classtype::GetInterface(LPCTSTR name)	\
		{												\
			bstring strType = GetType();				\
			if (strType.length() > 3)					\
			if (_tcscmp(name, strType.c_str() + 3) == 0)\
				return static_cast<classtype*>(this);	\
			return baseclass::GetInterface(name);		\
		}

	// 控件工厂相关定义
	typedef BUIWidget* (*PCreateWidget)();
	typedef map<bstring, PCreateWidget> CREATEWIDGETFUNCMAP;
	typedef CREATEWIDGETFUNCMAP::iterator CREATEWIDGETFUNCMAPIT;
	#define DEFINE_CREATEWIDGET(classtype)	\
		static BUIWidget* Create##classtype();	\

	#define IMPLEMENT_CREATEWIDGET(classtype)	\
		BUIWidget* classtype::Create##classtype()	\
			{ \
			return new classtype;\
			}	\

	#define REGISTER_CREATEWIDGET(classtype)	\
		BUIWidgetFactory::RegisterCreateWidget(_T(#classtype), classtype::Create##classtype);

	
}

#endif // !__BUIWIDGETDEF_H__