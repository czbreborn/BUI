#ifndef __BUIWIDGETBUILDER_H__
#define __BUIWIDGETBUILDER_H__

#pragma once

namespace BUI{
	class BIWidgetBuilderCallBack
	{
	public:
		virtual BUIWidget* CreateWidget(LPCTSTR className) = 0;
	};

	class BUIWidgetBuilder;
	typedef void(BUIWidgetBuilder::*PARSE)(CMarkupNode* node);
	typedef map<LPCTSTR, PARSE> RESOURCEPARSEMAP;
	typedef RESOURCEPARSEMAP::iterator RESPARSEMAPIT;
	
	class BUIWidgetBuilder
	{
	public:
		BUIWidgetBuilder();
		~BUIWidgetBuilder();

		BUIWidget* CreateWidget(LPCTSTR xmlName, LPCTSTR type = NULL, BIWidgetBuilderCallBack* callback = NULL);

	private:
		BUIWidget* create(BUIWidget* parent);
		BUIWidget* parse(CMarkupNode* pRoot, BUIWidget* parent);

		void parseImageAttributes(CMarkupNode* node);
		void parseFontAttributes(CMarkupNode* node);
		void parseWindowAttributes(CMarkupNode* node);

	private:
		BIWidgetBuilderCallBack* m_builderCallBack;
		CMarkup m_xml;
		static RESOURCEPARSEMAP s_resoureParseMap;
	};
}

#endif