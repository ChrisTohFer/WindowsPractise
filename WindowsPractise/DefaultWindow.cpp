#include "DefaultWindow.h"
#include "Utils/Notifications.h"

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
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, get_user_file_selection(hwnd), L"Test", MB_OK);
	}

	//Carry out default action if no specific action is required
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

const wchar_t* DefaultWindow::ClassName() const
{
	return L"ExampleWindow";
}