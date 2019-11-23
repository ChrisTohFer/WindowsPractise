#pragma once

#include <Windows.h>

/*
	Creates a messagebox and returns true if previous windows error was not 0
*/
extern bool output_previous_windows_error(const wchar_t* windowName = L"Previous windows error", bool showIfNoError = false, bool show = true);

/*
	Creates a file selection box which blocks until user selects a file.
	Returns L"" if no file selected
*/
extern const TCHAR* get_user_file_selection(HWND owner = NULL);