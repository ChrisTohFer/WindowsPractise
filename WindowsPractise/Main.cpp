
#include <Windows.h>
#include "DefaultWindow.h"
#include "WindowsUtils/LifetimeObjects.h"
#include "WindowsUtils/DebugTools.h"

int WindowMain(HINSTANCE, HINSTANCE, PWSTR, int nCmdShow)
{
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


int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, PWSTR cmdline, int nCmdShow)
{
	//Initialise COM library
	COINITIALIZE_OBJECT comLibraryInitialized(COINIT_APARTMENTTHREADED);
	if (!comLibraryInitialized)
	{
		OutputDebugStringW(L"Failed to initialize COM library");
		return 1;
	}

	

	return WindowMain(instance, prevInstance, cmdline, nCmdShow);
}