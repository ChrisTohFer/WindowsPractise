#pragma once

#include <Windows.h>
#include <string>

/*
	Creates a file selection box which blocks until user selects a file.
	Returns L"" if no file selected
*/
extern std::wstring get_user_file_selection(HWND owner = NULL);