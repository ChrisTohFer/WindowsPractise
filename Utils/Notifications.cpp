#include "Notifications.h"
#include <Windows.h>
#include <shobjidl.h>
#include "PCOM.h"
#include <atlbase.h>

bool output_previous_windows_error(const wchar_t* windowName, bool showIfNoError, bool show)
{
	DWORD errorCode = GetLastError();

	if (errorCode != 0)
	{
		//Error
		wchar_t buffer[100];
		if (show)
		{
			wsprintf(buffer, L"Error code: %lu", errorCode);
			MessageBox(NULL, buffer, windowName, MB_OK);
		}
		else
		{
			wsprintf(buffer, L"%s:Error code: %lu", windowName, errorCode);
			OutputDebugString(buffer);
		}

		return true;
	}
	else if (showIfNoError)
	{
		//No error but create window anyway
		MessageBox(NULL, L"No error", windowName, MB_OK);
	}

	return false;
}

std::wstring get_user_file_selection(HWND owner)
{
	//Version 1 is custom smart pointers, version 2 is windows smart pointers
#if 1
	//Create the fileOpenDialog box
	PCOM<IFileOpenDialog> fileOpenDialog;
	if (FAILED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, fileOpenDialog)))
		return L"";

	//Show dialog
	if (FAILED(fileOpenDialog->Show(owner)))
		return L"";

	//Get result object
	PCOM<IShellItem> pItem;
	if (FAILED(fileOpenDialog->GetResult(pItem)))
		return L"";
#else
	//Create the fileOpenDialog box
	CComPtr<IFileOpenDialog> fileOpenDialog;
	if (FAILED(fileOpenDialog.CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL)))
		return L"";

	//Show dialog
	if (FAILED(fileOpenDialog->Show(owner)))
		return L"";

	//Get result object
	CComPtr<IShellItem> pItem;
	if (FAILED(fileOpenDialog->GetResult(&pItem)))
		return L"";
#endif // 1

	//Return chosen filepath
	wchar_t *str;
	if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &str)))
	{
		std::wstring value(str);
		CoTaskMemFree(str);			//GetDisplayName allocates memory to str using CoTaskMemAlloc - we must free that memory
		return value;
	}
	else
		return std::wstring();
}