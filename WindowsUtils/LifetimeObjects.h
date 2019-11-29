#pragma once

#include <Windows.h>

//Class initializes the COM library on construction, and Uninitializes it on destruction
class COINITIALIZE_SINGLE_THREADED
{
public:
	COINITIALIZE_SINGLE_THREADED()
	{
		success = SUCCEEDED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE));
	}
	~COINITIALIZE_SINGLE_THREADED()
	{
		CoUninitialize();
	}
	operator bool()
	{
		return success;
	}

private:
	bool success = false;
};

class COINITIALIZE_MULTI_THREADED
{
public:
	COINITIALIZE_MULTI_THREADED()
	{
		success = SUCCEEDED(CoInitializeEx(NULL, COINIT_MULTITHREADED | COINIT_DISABLE_OLE1DDE));
	}
	~COINITIALIZE_MULTI_THREADED()
	{
		CoUninitialize();
	}
	operator bool()
	{
		return success;
	}

private:
	bool success = false;
};