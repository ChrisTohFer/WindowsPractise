
#include <Windows.h>
#include "Utils/BaseWindow.h"
#include "Utils/Notifications.h"

class ExampleWindow : public BaseWindow<ExampleWindow>
{
public:

	LRESULT HandleMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
			{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_BACKGROUND));

			EndPaint(hwnd, &ps);
			}
			return 0;
		}

		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	virtual const wchar_t* ClassName() const override
	{
		return L"ExampleWindow";
	}
};

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int nCmdShow)
{
	ExampleWindow example;
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