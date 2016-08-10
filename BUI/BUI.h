// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� BUI_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// BUI_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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

// ʹ��stlģ��û�е��������ľ���
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

// ��Ⱦ����gdiplus
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