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
		Description: ��һ���ַ���Ϊ#�ţ����ַ��������һλ�����򷵻�ԭ�ַ���
		Paramter:
			[in_out] content: �ַ�������
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
		Description: ��������ָ���ַ���Χ�ڵ��ַ�,ֱ����һ�����ٷ�Χ�ڵ��ַ�Ϊֹ��
		Paramter:
			[in_out] content: �ַ�������
			[in] begin: ��Χ��ʼ�ַ�
			[in] end: ��Χ�����ַ�
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