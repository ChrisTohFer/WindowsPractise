
#include <Windows.h>
#include "Utils/Notifications.h"
#include "DefaultWindow.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int nCmdShow)
{
	//Create a window wrapper object and then create/show the window
	DefaultWindow example;
	example.Create(L"WindowName");
	ShowWindow(example.Window(), nCmdShow);

	//Initialise COM library
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	hr;

	//Experimenting with HRESULT error handling
	if (SUCCEEDED(hr))
	{
		MessageBox(NULL, L"Initializing the COM library succeeded!", L"Result", MB_OK);
	}
	else
	{
		MessageBox(NULL, L"Initializing the COM library FAILED!", L"Result", MB_OK);
	}

	//Windows message loop (with error output)
	output_previous_windows_error(L"Pre-Message Loop:");
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		output_previous_windows_error(L"Message Loop");
	}

	//
	CoUninitialize();

	output_previous_windows_error(L"Uninitializing Com Library");
}