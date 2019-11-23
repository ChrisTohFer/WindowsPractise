
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
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE); hr;

	//Windows message loop (with error output)
	output_previous_windows_error(L"Pre-Message Loop:");
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		output_previous_windows_error(L"Message Loop", false, false);
	}

	//
	CoUninitialize();

	output_previous_windows_error(L"Uninitializing Com Library");
}