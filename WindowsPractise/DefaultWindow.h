#pragma once

#include "WindowsUtils/BaseWindow.h"
#include "WindowsUtils/PCOM.h"
#include <d2d1.h>
#pragma comment(lib, "d2d1")

class DefaultWindow : public BaseWindow<DefaultWindow>
{
public:
	LRESULT HandleMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	virtual const wchar_t* ClassName() const override;

	void HandlePaint();
	void HandleResize();
	HRESULT InitializeResources();
	void DiscardResources();
	void CalculateLayout();

private:
	PCOM<ID2D1HwndRenderTarget> renderTarget;
	PCOM<ID2D1SolidColorBrush>	brush;
	PCOM<ID2D1Factory>			factory;
	D2D1_ELLIPSE				ellipse;
};