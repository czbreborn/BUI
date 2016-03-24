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

// ʹ��stlģ��û�е��������ľ���
#pragma warning(disable:4251)

#include <sstream>
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

#include "BUIDef.h"

#include "Utils\BEncodingTranslation.h"
#include "Utils\BSingleton.h"
#include "Utils\BUIAssist.h"
#include "Utils\BUIMarkup.h"

#include "Core\BApplication.h"
#include "Core\BMsgDef.h"
#include "Core\BSmartPointer.h"
#include "Core\BUIManager.h"
#include "Core\BUIObject.h"
#include "Core\BUIWidgetBuilder.h"
#include "Core\BUIWindow.h"

#include "Render\BRenderEngineDef.h"
#include "Render\BRenderEngineGdiPlus.h"
#include "Render\BRenderEngineManager.h"

#include "Widget\BUIWidgetDef.h"
#include "Widget\BUIWidget.h"
#include "Widget\BUILabel.h"
#include "Widget\BUIButton.h"
#include "Widget\BUIPanel.h"
#include "Widget\BUIWidgetFactory.h"

#endif