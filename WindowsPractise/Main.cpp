
#include <Windows.h>
#include "Utils/Notifications.h"
#include "DefaultWindow.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int nCmdShow)
{
	DefaultWindow example;
	example.Create(L"WindowName");
	ShowWindow(example.Window(), nCmdShow);

	output_previous_windows_error(L"Pre-Message Loop:");

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		output_previous_windows_error(L"Message Loop");
	}
}