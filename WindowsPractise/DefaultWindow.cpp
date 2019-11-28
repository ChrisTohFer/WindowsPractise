#include "DefaultWindow.h"
#include "WindowsUtils/Notifications.h"

LRESULT DefaultWindow::HandleMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//Determine type of message
	switch (msg)
	{
	case WM_DESTROY:
		DiscardResources();
		factory.SafeRelease();
		PostQuitMessage(0);
		return 0;

	case WM_CREATE:
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, factory.operator ID2D1Factory **())))
		{
			return -1;
		}
		return 0;

	case WM_PAINT:
		HandlePaint();
		return 0;

	case WM_SIZE:
		HandleResize();
		return 0;
	}

	//Carry out default action if no specific action is required
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

const wchar_t* DefaultWindow::ClassName() const
{
	return L"ExampleWindow";
}

void DefaultWindow::HandlePaint()
{
	if (FAILED(InitializeResources()))
	{
		OutputDebugStringW(L"Failed to initialize resources\n");
		return;
	}

	PAINTSTRUCT ps;
	BeginPaint(window, &ps);

	renderTarget->BeginDraw();

	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
	renderTarget->FillEllipse(ellipse, brush);

	HRESULT hr = renderTarget->EndDraw();
	if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		DiscardResources();

	EndPaint(window, &ps);
}

void DefaultWindow::HandleResize()
{
	if (renderTarget.IsValid())
	{
		RECT rec;
		GetClientRect(window, &rec);

		renderTarget->Resize(D2D1::SizeU(rec.right, rec.bottom));

		CalculateLayout();
		InvalidateRect(window, nullptr, false);
	}
}

HRESULT DefaultWindow::InitializeResources()
{
	HRESULT hr = S_OK;
	if (renderTarget.IsValid())
		return hr;

	//Create rendertarget with dimensions of window
	RECT rec;
	GetClientRect(window, &rec);
	D2D1_SIZE_U size = D2D1::SizeU(rec.right, rec.bottom);
	
	hr = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(window, size),
		renderTarget
	);
	if (FAILED(hr))
		return hr;

	//Create brush
	const D2D1_COLOR_F color = D2D1::ColorF(1.f, 1.f, 0.f);
	hr = renderTarget->CreateSolidColorBrush(color, brush);
	if (FAILED(hr))
		return hr;

	//Update ellipse
	CalculateLayout();

	return hr;
}

void DefaultWindow::DiscardResources()
{
	renderTarget.SafeRelease();
	brush.SafeRelease();
}

void DefaultWindow::CalculateLayout()
{
	if (renderTarget.IsValid())
	{
		D2D1_SIZE_F rec = renderTarget->GetSize();
		const float x = rec.width / 2.f;
		const float y = rec.height / 2.f;
		ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), x, y);
	}
}
