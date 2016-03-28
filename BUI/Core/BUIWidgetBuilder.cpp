#include "stdafx.h"

namespace BUI{
	RESOURCEPARSEMAP BUIWidgetBuilder::s_resoureParseMap;
	BUIWidgetBuilder::BUIWidgetBuilder()
	{
#define PARSEBIND(restype, func) \
	s_resoureParseMap.insert(make_pair(restype, SELECTOR(func)))
		PARSEBIND(_T("Image"), BUIWidgetBuilder::parseImageAttributes);
		PARSEBIND(_T("Font"), BUIWidgetBuilder::parseFontAttributes);
		PARSEBIND(_T("Window"), BUIWidgetBuilder::parseWindowAttributes);
	}


	BUIWidgetBuilder::~BUIWidgetBuilder()
	{
	}

	BUIWidget* BUIWidgetBuilder::CreateWidget(LPCTSTR xmlName, BUIManager* pWindowManager, BUIWidget* parent/* = NULL*/, LPCTSTR type/* = NULL*/, BIWidgetBuilderCallBack* callback/* = NULL*/)
	{
		if (!m_xml.LoadFromFile(xmlName))
			return NULL;

		m_builderCallBack = callback;
		m_pWindowManager = pWindowManager;
		return create(parent);
	}

	BUIWidget* BUIWidgetBuilder::create(BUIWidget* parent)
	{
		CMarkupNode& root = m_xml.GetRoot();
		// 解析图片，字体等相关资源属性
		for (CMarkupNode node = root.GetChild(); node.IsValid(); node = node.GetSibling())
		{
			itemParse(&node);
		}

		// 解析window相关属性
		itemParse(&root);

		return parse(&root, parent);
	}

	BUIWidget* BUIWidgetBuilder::parse(CMarkupNode* pRoot, BUIWidget* parent)
	{
		BUIWidget* pWidget = NULL;
		for (CMarkupNode node = pRoot->GetChild(); node.IsValid(); node = node.GetSibling())
		{
			LPCTSTR nodeName = node.GetName();
			// 资源解析已完成，这里直接跳过
			RESPARSEMAPIT it = s_resoureParseMap.find(nodeName);
			if (it != s_resoureParseMap.end())
			{
				continue;
			}

			bstring className = _T("BUI");
			className.append(nodeName);
			BUIWidget* newWidget = BUIWidgetFactory::GetInstance()->CreateWidget(className.c_str());
			assert(newWidget);

			// Init default attributes
			if (m_pWindowManager)
			{
				newWidget->SetManager(m_pWindowManager, NULL);
				/*LPCTSTR pDefaultAttributes = m_pWindowManager->GetDefaultAttributeList(pstrClass);
				if( pDefaultAttributes ) {
					pControl->ApplyAttributeList(pDefaultAttributes);
				}*/
			}

			if (node.HasAttributes())
			{
				int nAttributes = node.GetAttributeCount();
				for (int i = 0; i < nAttributes; i++) 
				{
					newWidget->SetAttribute(node.GetAttributeName(i), node.GetAttributeValue(i));
				}
			}

			if (node.HasChildren())
			{
				parse(&node, newWidget);
			}

			if (parent != NULL ) {
				BUIContainer* pContainer = static_cast<BUIContainer*>(parent->GetInterface(_T("Container")));
				assert(pContainer);
				if (pContainer == NULL)
					return NULL;

				if(!pContainer->Add(newWidget))
				{
					delete newWidget;
					continue;
				}
			}

			if (pWidget == NULL) 
				pWidget = newWidget;
		}
		return pWidget;
	}

	void BUIWidgetBuilder::itemParse(CMarkupNode* node)
	{
		LPCTSTR lpstrName = node->GetName();
		RESPARSEMAPIT it = s_resoureParseMap.find(lpstrName);
		if (it != s_resoureParseMap.end())
		{
			PARSE parseFunc = static_cast<PARSE>(it->second);
			(this->*parseFunc)(node);
		}
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