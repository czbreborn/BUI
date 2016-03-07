#pragma once
#include "BUI.h"

class BUI_API BRefCount
{
public:
	BRefCount();
	LONG GetRefCount() const;
	LONG AddRefCount();
	LONG RemoveRefCount();
	void ResetRefCount();

private:
	LONG m_shareRefCount;
};

template<typename T>
class BUI_API BShareRefPtr 
{
public:
	BShareRefPtr();
	virtual ~BShareRefPtr();

	BShareRefPtr(T* object);
	BShareRefPtr(const BShareRefPtr<T>& src);
	template<typename U>
	BShareRefPtr(const BShareRefPtr<U>& src);

	BShareRefPtr<T>& operator=(T* object);
	BShareRefPtr<T>& operator=(const BShareRefPtr<T>& src);
	template<typename U>
	BShareRefPtr<T>& operator=(const BShareRefPtr<U>& src);

	void Reset();
	T* GetObject() const;

public:
	T* operator->() const;
	operator bool() const;

	bool operator==(T* object) const;
	bool operator==(const BShareRefPtr<T>& right) const;
	template<typename U>
	bool operator==(U* object) const;
	bool operator!=(T* object) const;
	bool operator!=(const BShareRefPtr<T>& right) const;
	template<typename U>
	bool operator!=(U* object) const;

private:
	BShareRefPtr<T>& assign(T* object);
	void release();

private:
	BRefCount	m_refCount;
	T*			m_object;
};

template<typename T, typename U>
bool operator==(const BShareRefPtr<T>& t, const BShareRefPtr<U>& u);
template<typename T, typename U>
bool operator!=(const BShareRefPtr<T>& t, const BShareRefPtr<U>& u);

