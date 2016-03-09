#ifndef __BSINGLETON_H__
#define __BSINGLETON_H__

#pragma once

namespace BUI{
	template<typename T>
	class BShareRefPtr;

	template<typename T>
	class BUI_API BSingleton : public BNoCopy
	{
	public:
		static BShareRefPtr<T> Instance();

	private:
		static BShareRefPtr<T> m_instance;
	};
}

#endif