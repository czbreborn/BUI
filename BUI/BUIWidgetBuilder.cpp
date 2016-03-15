#include "stdafx.h"

namespace BUI{
	RESOURCEPARSEMAP BUIWidgetBuilder::s_resoureParseMap;
	BUIWidgetBuilder::BUIWidgetBuilder()
	{
#define PARSEFUNCTION(func) (&func)
#define PARSEBIND(restype, func) \
	s_resoureParseMap.insert(make_pair(restype, PARSEFUNCTION(func)))
		PARSEBIND(_T("Image"), BUIWidgetBuilder::parseImageAttributes);
		PARSEBIND(_T("Font"), BUIWidgetBuilder::parseFontAttributes);
		PARSEBIND(_T("Window"), BUIWidgetBuilder::parseWindowAttributes);
	}


	BUIWidgetBuilder::~BUIWidgetBuilder()
	{
	}

	BUIWidget* BUIWidgetBuilder::CreateWidget(LPCTSTR xmlName, LPCTSTR type/* = NULL*/, BIWidgetBuilderCallBack* callback/* = NULL*/)
	{
		if (!m_xml.LoadFromFile(xmlName))
			return NULL;

		m_builderCallBack = callback;
		create(NULL);
	}

	BUIWidget* BUIWidgetBuilder::create(BUIWidget* parent)
	{
		CMarkupNode& root = m_xml.GetRoot();
		LPCTSTR lpstrName;
		// 解析图片，字体等相关资源属性
		for (CMarkupNode node = root.GetChild(); node.IsValid(); node = node.GetSibling())
		{
			lpstrName = node.GetName();
			RESPARSEMAPIT it = s_resoureParseMap.find(lpstrName);
			if (it != s_resoureParseMap.end())
			{
				PARSE parseFunc = static_cast<PARSE>(it->second);
				(this->*parseFunc)(&node);
			}
		}

		// 解析window属性
		lpstrName = root.GetName();
		RESPARSEMAPIT it = s_resoureParseMap.find(lpstrName);
		if (it != s_resoureParseMap.end())
		{
			PARSE parseFunc = static_cast<PARSE>(it->second);
			(this->*parseFunc)(&root);
		}

		return parse(&root, parent);
	}

	BUIWidget* BUIWidgetBuilder::parse(CMarkupNode* pRoot, BUIWidget* parent)
	{
		return NULL;
	}

	void BUIWidgetBuilder::parseImageAttributes(CMarkupNode* node)
	{

	}

	void BUIWidgetBuilder::parseFontAttributes(CMarkupNode* node)
	{

	}

	void BUIWidgetBuilder::parseWindowAttributes(CMarkupNode* node)
	{

	}
}