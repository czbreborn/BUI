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