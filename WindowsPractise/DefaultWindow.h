#pragma once

#include "Utils/BaseWindow.h"

class DefaultWindow : public BaseWindow<DefaultWindow>
{
public:
	LRESULT HandleMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	virtual const wchar_t* ClassName() const override;
};