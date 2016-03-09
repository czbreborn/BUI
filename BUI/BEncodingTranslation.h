#ifndef __BENCODINGTRANSLATION_H__
#define __BENCODINGTRANSLATION_H__

#pragma once

namespace BUI{
	class BEncodingTranslation
	{
	public:
		static wstring MultiByteToWideChar(char* szText, UINT codePage = CP_ACP);
		static string WideCharToMultiByte(wchar_t* szText, UINT codePage = CP_ACP);
	};
}

#endif