#include "DefaultWindow.h"

LRESULT DefaultWindow::HandleMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//Determine type of message
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
	}

	//Carry out default action if no specific action is required
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

const wchar_t* DefaultWindow::ClassName() const
{
	return L"ExampleWindow";
}