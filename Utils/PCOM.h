#pragma once

#include <Windows.h>

/*
	Class wraps a pointer to a COM object and automatically updates reference count to prevent memory leaks
*/
template<typename COM_TYPE>
class PCOM
{
public:
	//Construction
	PCOM() {}
	PCOM(const PCOM<COM_TYPE>& rhs)
		:ptr(rhs)
	{
		if (ptr)
			ptr->AddRef();
	}
	
	//Destruction
	~PCOM()
	{
		SafeRelease();
	}
	
	//Assignment
	PCOM<COM_TYPE>& operator=(const PCOM<COM_TYPE>& rhs)
	{
		if (ptr == rhs.ptr)
			return *this;

		//Release old ptr if relevant
		if (ptr)
			ptr->Release();

		ptr = rhs;
		if (ptr)
			ptr->AddRef();

		return *this;
	}

	//Operators
	COM_TYPE* operator->() const
	{
		return ptr;
	}

	//Conversions
	operator void** ()
	{
		return reinterpret_cast<void**>(&ptr);
	}
	operator COM_TYPE** ()
	{
		return &ptr;
	}

	//Member functions
	void SafeRelease()
	{
		if (ptr)
			ptr->Release();
	}

private:
	COM_TYPE* ptr = nullptr;
};

