#ifndef __BRENDERENGINEASSIST_H__
#define __BRENDERENGINEASSIST_H__

#pragma once

namespace BUI {
	class BRenderEngineAssist
	{
	protected:
		BRenderEngineAssist(void);
		~BRenderEngineAssist(void);

	public:
		/*
		Description: �ԾŹ���ʽ����ͼƬ
		Paramter:
			[in] imageFilePath: ԭʼͼƬ·��
			[in] szImage: ���ɵ�ͼƬ��С
			[in] rcCorner: �Ź����ĸ��ǵĴ�С 
		return: һ���µ�Image������Ҫ�ⲿ�ͷ���Դ
		Demo:
			content = "#123"
			SkipOneHashSymbol(content);
			Result: content 123
			content = "1#23"
			SkipOneHashSymbol(content);
			Result: content 1#23
		*/
		static Image* genScaleImage(LPCTSTR imageFilePath, const SIZE& szImage, const RECT& rcCorner);
	};
}

#endif 