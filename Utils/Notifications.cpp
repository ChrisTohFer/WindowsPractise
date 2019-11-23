#include "Notifications.h"
#include <Windows.h>
#include <shobjidl.h>
#include "PCOM.h"

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

const TCHAR* get_user_file_selection(HWND owner)
{
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

	//Return chosen filepath
	wchar_t *str;
	if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &str)))
	{
		return str;
	}
	else
		return L"";
}