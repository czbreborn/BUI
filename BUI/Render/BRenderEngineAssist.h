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
		Description: 以九宫格方式缩放图片
		Paramter:
			[in] imageFilePath: 原始图片路径
			[in] szImage: 生成的图片大小
			[in] rcCorner: 九宫格四个角的大小 
		return: 一个新的Image对象，需要外部释放资源
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