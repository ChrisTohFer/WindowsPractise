#pragma once

#include <Windows.h>
#include "Notifications.h"

template<typename DERIVED_TYPE>
class BaseWindow
{
public:
	/*
		Handle windows messages by redirecting them to the DERIVED_TYPE object that created the window
	*/
	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		pState = nullptr;

		//Get or set the window pointer (pointer to the DERIVED_TYPE object)
		if (msg == WM_CREATE)
		{
			CREATESTRUCT* pcreate = (CREATESTRUCT*)lparam;
			pState = reinterpret_cast<DERIVED_TYPE*>(pcreate->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG)pState);
		}
		else
		{
			pState = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}

		//Handle the message
		if (pState)
		{
			//
			if (msg == WM_DESTROY)
			{
				pState->created = false;
			}
			return pState->HandleMessage(hwnd, msg, wparam, lparam);
		}
		else
		{
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}
	}

	/*
		Create a window and return true if successful or window already exists
	*/
	virtual bool Create(const wchar_t* windowName)
	{
		RegisterWindowClass();

		if (!created)
		{
			window = CreateWindowEx(
				0,
				this->ClassName(),
				windowName,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				NULL,
				NULL,
				GetModuleHandle(NULL),
				this
			);

			created = (window != nullptr);

			return window != nullptr;
		}
		else
		{
			MessageBox(NULL, L"Warning: Attempted to call Create() on window twice", L"Window creation", MB_OK);
			return true;
		}
	}

	HWND Window() const
	{
		return window; 
	}
	virtual const wchar_t* ClassName() const = 0;

protected:

	/*
		Register the window class and return true if no error (or if already registered)
	*/
	bool RegisterWindowClass()
	{
		if (!registered)
		{
			registered = true;

			WNDCLASS wnd = {};

			wnd.lpfnWndProc = WindowProcedure;
			wnd.hInstance = GetModuleHandle(NULL);
			wnd.lpszClassName = this->ClassName();

			RegisterClass(&wnd);
			
			return output_previous_windows_error();
		}

		return true;
	}

	bool created = false;
	HWND window = nullptr;

private:
	//Static pointer to be used by window procedure to identiy the object associated with the window
	static DERIVED_TYPE* pState;

	//Bool identifies whether the window class associated with DERIVED_TYPE has been registered
	static bool registered;
};

template<typename DERIVED_TYPE>
bool BaseWindow<DERIVED_TYPE>::registered = false;

template<typename DERIVED_TYPE>
DERIVED_TYPE* BaseWindow<DERIVED_TYPE>::pState = nullptr;