// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 BUI_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// BUI_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifndef __BUI_H__
#define __BUI_H__

#ifdef BUI_EXPORTS
#define BUI_API __declspec(dllexport)
#else
#define BUI_API __declspec(dllimport)
#endif

#include <string>
#include <map>
#include <vector>
#include <list>
using namespace std;

#ifdef UNICODE
#define bstring wstring
#else
#define bstring string
#endif

#include <objbase.h>
#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>

#include "BSmartPointer.h"
#include "BSingleton.h"
#include "BEncodingTranslation.h"

#include "BUIDef.h"
#include "BMsgDef.h"
#include "BUIWidgetDef.h"

#include "BApplication.h"
#include "BUIManager.h"
#include "BRenderEngineDef.h"
#include "BRenderEngineGdiPlus.h"
#include "BRenderEngineManager.h"
#include "BUIMarkup.h"
#include "BUIWidgetBuilder.h"
#include "BUIWidgetFactory.h"

#include "BUIObject.h"
#include "BUIWindow.h"
#include "BUIWidget.h"
#include "BUILabel.h"
#include "BUIPanel.h"


#endif