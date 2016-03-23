#ifndef __BUIWIDGETDEF_H__
#define __BUIWIDGETDEF_H__

#pragma once

namespace BUI{

#define BUI_WIN_WIDGET		_T("BUIWidget")
#define BUI_WIN_LABEL		_T("BUILabel")
#define BUI_WIN_BUTTON		_T("BUIButton")

class BUIWidget;
typedef BUIWidget* (*PCreateWidget)();
typedef map<LPCTSTR, PCreateWidget> CREATEWIDGETFUNCMAP;
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