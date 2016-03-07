#pragma once
#include "BUI.h"
#include "BUIDef.h"

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


