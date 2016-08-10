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

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>

// 使用stl模板没有导出而报的警告
#pragma warning(disable:4251)

#include <math.h>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <algorithm> 
using namespace std;

#ifdef UNICODE
#define bstring wstring
#define bstringstream wstringstream
#else
#define bstring string
#define bstringstream stringstream
#endif

const bstring k_empty_string(_T(""));

// 渲染引擎gdiplus
#include <comdef.h>
#include <gdiplus.h>
#include <gdiplusenums.h>

#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

#include "BUIDef.h"

#include "Utils\BEncodingTranslation.h"
#include "Utils\BSingleton.h"
#include "Utils\BUIAssist.h"
#include "Utils\BUIMarkup.h"
#include "Utils\BUIAttributeParser.h"

#include "Core\BApplication.h"
#include "Core\BMsgDef.h"
#include "Core\BSmartPointer.h"
#include "Core\BUIManager.h"
#include "Core\BUIObject.h"
#include "Core\BUIWidgetBuilder.h"
#include "Core\BUIWindow.h"

#include "Render\BRenderEngineDef.h"
#include "Render\BRenderEngineAssist.h"
#include "Render\BRenderCanvas.h"
#include "Render\BRenderEngineGdiPlus.h"
#include "Render\BRenderEngineManager.h"

#include "Widget\BUIWidgetDef.h"
#include "Widget\BUIWidget.h"
#include "Widget\BUILabel.h"
#include "Widget\BUIButton.h"
#include "Widget\BUIEdit.h"
#include "Widget\BUIScrollBar.h"
#include "Widget\BUIContainer.h"
#include "Widget\BUIHorizontalLayout.h"
#include "Widget\BUIVerticalLayout.h"
#include "Widget\BUIPanel.h"
#include "Widget\BUIWidgetFactory.h"

#endif