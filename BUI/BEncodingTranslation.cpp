#include "stdafx.h"
#include "BEncodingTranslation.h"

wstring BEncodingTranslation::MultiByteToWideChar(char* szText, UINT codePage/* = CP_ACP*/)
{
	wstring wstrTranslated;
	if (szText == NULL || strlen(szText) == 0)
		return wstrTranslated;

	int length = ::MultiByteToWideChar(codePage, 0, szText, -1, NULL, 0);
	if (length == 0)
		return wstrTranslated;
	wchar_t* wszText = new wchar_t[length];
	if (wszText != NULL)
	{
		length = ::MultiByteToWideChar(codePage, 0, szText, -1, wszText, length);
		if (length != 0)
			wstrTranslated = wszText;
		delete[] wszText;
	}
	return wstrTranslated;
}

string BEncodingTranslation::WideCharToMultiByte(wchar_t* wszText, UINT codePage/* = CP_ACP*/)
{
	string strTranslated;
	if (wszText == NULL || wcslen(wszText) == 0)
		return strTranslated;

	int length = ::WideCharToMultiByte(codePage, 0, wszText, -1, NULL, 0, NULL, NULL);
	if (length == 0)
		return strTranslated;

	char* szText = new char[length];
	if (szText != NULL)
	{
		length = ::WideCharToMultiByte(codePage, 0, wszText, -1, szText, length, NULL, NULL);
		if (length != 0)
			strTranslated = szText;
		delete[] szText;
	}
	return strTranslated;
}