
#include <Windows.h>
#include "DefaultWindow.h"
#include "WindowsUtils/LifetimeObjects.h"
#include "WindowsUtils/DebugTools.h"

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
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		OutputPreviousWindowsError(L"Windows error in main loop: ");
		SetLastError(0);
	}

	return 0;
}