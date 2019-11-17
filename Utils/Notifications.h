#pragma once

#include <Windows.h>

/*
	Creates a messagebox and returns true if previous windows error was not 0
*/
inline bool output_previous_windows_error(const wchar_t* windowName = L"Previous windows error", bool showIfNoError = false)
{
	DWORD errorCode = GetLastError();

	if (errorCode != 0)
	{
		//Error
		wchar_t buffer[30];
		wsprintf(buffer, L"Error code: %lu", errorCode);
		MessageBox(NULL, buffer, windowName, MB_OK);

		return true;
	}
	else if (showIfNoError)
	{
		//No error but create window anyway
		MessageBox(NULL, L"No error", windowName, MB_OK);
	}

	return false;
}