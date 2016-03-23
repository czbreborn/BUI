#include "stdafx.h"

namespace BUI{
	template<typename T>
	BShareRefPtr<T> BSingleton<T>::m_instance;

	template<typename T>
	BShareRefPtr<T> BSingleton<T>::Instance()
	{
		if (m_instance == NULL)
		{
			BShareRefPtr<T> temp(new BSingleton<T>);
			if (m_instance == NULL)
			{
				m_instance = temp;
			}
		}

		return m_instance;
	}
}