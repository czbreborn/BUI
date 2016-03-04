#include "stdafx.h"
#include "BSingleton.h"

template<typename T>
T* BSingleton<T>::m_instance;

template<typename T>
T* BSingleton<T>::Instance()
{
	if (m_instance == NULL)
	{
		T* temp = new BSingleton<T>;
		m_instance = temp;
	}

	return m_instance;
}