#pragma once

#include <Windows.h>

//Class initializes the COM library on construction, and Uninitializes it on destruction
class COINITIALIZE_OBJECT
{
public:
	COINITIALIZE_OBJECT(tagCOINIT tag)
	{
		success = SUCCEEDED(CoInitializeEx(NULL, tag | COINIT_DISABLE_OLE1DDE));
	}
	~COINITIALIZE_OBJECT()
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
