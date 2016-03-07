#pragma once
#include "BUI.h"
class BEncodingTranslation
{
public:
	static wstring MultiByteToWideChar(char* szText, UINT codePage = CP_ACP);
	static string WideCharToMultiByte(wchar_t* szText, UINT codePage = CP_ACP);
};

