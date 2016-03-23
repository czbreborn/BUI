#ifndef __BMSGDEF_H__
#define __BMSGDEF_H__

#pragma once

namespace BUI{

#define MSG2STR(msg) _T(#msg)
#define MSGFUNCTION(function) (&function)

	// 预处理消息
	class BIPreTranslateMessage{
		virtual BOOL PreTranslateMessage(LPMSG pMsg) = 0;
	};
	
	// 翻译加速键（快捷键）
	class BITranslateAccelerator{
		virtual int TranslateAccelerator(HWND hWnd, HACCEL hAccTable, LPMSG lpMsg) = 0;
	};
}

#endif