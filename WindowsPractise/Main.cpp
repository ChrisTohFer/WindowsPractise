
#include <Windows.h>
#include "Utils/Notifications.h"
#include "DefaultWindow.h"
#include "Utils/LifetimeObjects.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int nCmdShow)
{
	//Initialise COM library
	COINITIALIZE_SINGLE_THREADED comLibraryInitialized;
	if (!comLibraryInitialized)
	{
		OutputDebugStringW(L"Failed to initialize COM library");
		return 1;
	}

	//Create a window wrapper object and then create/show the window
	DefaultWindow example;
	example.Create(L"WindowName");
	ShowWindow(example.Window(), nCmdShow);


	//Windows message loop (with error output)
	output_previous_windows_error(L"Pre-Message Loop:");
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		output_previous_windows_error(L"Message Loop", false, false);
	}

	return 0;
}