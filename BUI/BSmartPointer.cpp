#include "stdafx.h"
#include "BSmartPointer.h"


BRefCount::BRefCount()
{
	m_shareRefCount = 0;
}

LONG BRefCount::GetRefCount() const
{
	return m_shareRefCount;
}

LONG BRefCount::AddRefCount()
{
	return InterlockedIncrement(&m_shareRefCount);
}

LONG BRefCount::RemoveRefCount() 
{
	return InterlockedDecrement(&m_shareRefCount);
}

void BRefCount::ResetRefCount()
{
	m_shareRefCount = 0;
}
