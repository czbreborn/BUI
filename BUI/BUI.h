// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� BUI_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// BUI_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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

#include "BProcessResources.h"
#include "BRenderEngineManager.h"
#include "BMsgDef.h"

#include "BUIObject.h"
#include "BUIWindow.h"