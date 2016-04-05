#ifndef __BUIATTRIBUTEPARSER_H__
#define __BUIATTRIBUTEPARSER_H__

#pragma once

namespace BUI {
	class BUIAttributeParser
	{
	protected:
		BUIAttributeParser(void);
		~BUIAttributeParser(void);

	public:
		/*
		Description: 第一个字符串为#号，则字符串向后移一位。否则返回原字符串
		Paramter:
			[in_out] content: 字符串内容
		Demo:
			content = "#123"
			SkipOneHashSymbol(content);
			Result: content 123
			content = "1#23"
			SkipOneHashSymbol(content);
			Result: content 1#23
		*/
		static void SkipOneHashSymbol(LPCTSTR content);
		/*
		Description: 依次跳过指定字符范围内的字符,直到第一个不再范围内的字符为止。
		Paramter:
			[in_out] content: 字符串内容
			[in] begin: 范围起始字符
			[in] end: 范围结束字符
		Demo:
			content = "123abc"
			SkipSpecifySymbol(content, '0', '9');
			Result: content abc
			content = "12a3bc"
			SkipSpecifySymbol(content, '0', '9');
			Result: content a3bc
		*/
		static void SkipSpecifySymbol(LPCTSTR content, TCHAR begin, TCHAR end);
	};
}

#endif