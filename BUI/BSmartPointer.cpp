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

template<typename T>
BShareRefPtr<T>::BShareRefPtr()
	: m_object(NULL)
{
	m_refCount.ResetRefCount();
}

template<typename T>
BShareRefPtr<T>::~BShareRefPtr()
{
	release();
}

template<typename T>
BShareRefPtr<T>::BShareRefPtr(T* object)
	: m_object(NULL)
{
	m_refCount.ResetRefCount();
	assign(object);
}

template<typename T>
BShareRefPtr<T>::BShareRefPtr(const BShareRefPtr<T>& src)
	: m_object(NULL)
{
	m_refCount.ResetRefCount();
	assign(src.GetObject());
}

template<typename T>
template<typename U>
BShareRefPtr<T>::BShareRefPtr(const BShareRefPtr<U>& src)
	: m_object(NULL)
{
	assign(dynamic_cast<T*>(src.GetObject()));
}

template<typename T>
BShareRefPtr<T>& BShareRefPtr<T>::operator=(T* object)
{
	return assign(object);
}

template<typename T>
BShareRefPtr<T>& BShareRefPtr<T>::operator=(const BShareRefPtr<T>& src)
{
	assign(src.GetObject());
}

template<typename T>
template<typename U>
BShareRefPtr<T>& BShareRefPtr<T>::operator=(const BShareRefPtr<U>& src)
{
	assign(dynamic_cast<T*>(src.GetObject()));
}

template<typename T>
void BShareRefPtr<T>::Reset()
{
	assign(NULL);
}

template<typename T>
T* BShareRefPtr<T>::GetObject() const
{
	return m_object;
}

template<typename T>
T* BShareRefPtr<T>::operator->() const
{
	return m_object;
}

template<typename T>
BShareRefPtr<T>::operator bool() const
{
	if (m_refCount > 0)
	{
		return true;
	}

	return false;
}

template<typename T>
bool BShareRefPtr<T>::operator==(T* object) const
{
	return m_object == object;
}

template<typename T>
bool BShareRefPtr<T>::operator==(const BShareRefPtr<T>& right) const
{
	return m_object == right.GetObject();
}

template<typename T>
template<typename U>
bool BShareRefPtr<T>::operator==(U* object) const
{
	return m_object == object;
}

template<typename T>
bool BShareRefPtr<T>::operator!=(T* object) const
{
	return m_object != object;
}

template<typename T>
bool BShareRefPtr<T>::operator!=(const BShareRefPtr<T>& right) const
{
	return !(m_object == right.GetObject())
}

template<typename T>
template<typename U>
bool BShareRefPtr<T>::operator!=(U* object) const
{
	return !(m_object == object);
}

template<typename T>
BShareRefPtr<T>& BShareRefPtr<T>::assign(T* object)
{
	m_object = object;
	return m_object;
}

template<typename T>
void BShareRefPtr<T>::release()
{
	LONG refCount = m_refCount.RemoveRefCount();
	if (refCount == 0)
	{
		delete m_object;
		m_object = NULL;
		m_refCount.ResetRefCount();
	}
}

template<typename T, typename U>
bool operator==(const BShareRefPtr<T>& t, const BShareRefPtr<U>& u)
{
	return t.GetObject() == u.GetObject();
}

template<typename T, typename U>
bool operator!=(const BShareRefPtr<T>& t, const BShareRefPtr<U>& u)
{
	return t.GetObject() != u.GetObject();
}