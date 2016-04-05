#include "stdafx.h"

namespace BUI {
	BUIAttributeParser::BUIAttributeParser(void)
	{
	}

	BUIAttributeParser::~BUIAttributeParser(void)
	{
	}
	
	void BUIAttributeParser::SkipOneHashSymbol(LPCTSTR content)
	{
		if (*content == _T('#'))
			content = ::CharNext(content);
	}

	void BUIAttributeParser::SkipSpecifySymbol(LPCTSTR content, TCHAR begin, TCHAR end)
	{
		while (*content >= begin && *content <= end)
		{
			assert(*content == _T('\0'));
			if (*content == _T('\0'))
				break;
			content = ::CharNext(content);
		}
	}
}
