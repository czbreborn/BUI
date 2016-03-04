#pragma once
#include "BUI.h"
#include "BUIDef.h"
#include "BSmartPointer.h"

template<typename T>
class BUI_API BSingleton :	public BNoCopy
{
public:
	static T* Instance();

private:
	static T* m_instance;
};


