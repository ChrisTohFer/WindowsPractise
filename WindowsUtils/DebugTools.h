#pragma once

#include <Windows.h>
#include <string>

//Print out previous window error (if any) with a message
inline void OutputPreviousWindowsError(const wchar_t* message = L"Previous Windows Error:")
{
	DWORD lastError = GetLastError();
	if (lastError != 0)
	{
		std::wstring msg(message);
		msg += std::to_wstring(lastError);
		msg += L"\n";
		OutputDebugString(msg.c_str());
	}
}