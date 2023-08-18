#include "window.hpp"

#include <string>
#include <sstream>

Window::Window() : hInstance{GetModuleHandle(nullptr)}
{
	// register window class
	WNDCLASS wc{ 0 };
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = className;

	RegisterClass(&wc);

	// create window instance
	hWnd = CreateWindow(className,
		L"DirectX Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		0, 0, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);

	/*
	// Example of init COM
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);// Single thread
	//hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);// Multithread
	if (SUCCEEDED(hr))
	{
		// The function succeeded.
	}
	else if (FAILED(hr))
	{
		// The function failed.
	}
	CoUninitialize();// Close
	*/

	ShowWindow(hWnd, SW_SHOW);
	renderer = std::make_unique<Renderer>(hWnd);
}

Window::~Window()
{
	UnregisterClass(className, hInstance);
}

void Window::Update()
{
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		
		renderer->ClearBuffer(0.2f, 0.2f, 0.2f, 1.0f);
		renderer->EndFrame();
	}
}

int Window::End()
{
	if (gResult == -1)
		return -1;
	
	return msg.wParam;
}

LRESULT Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		//if (MessageBox(hWnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
		//{
		//	DestroyWindow(hWnd);
		//}
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == 'F')
			SetWindowText(hWnd, L":D");
		break;

	case WM_KEYUP:
		if (wParam == 'F')
			SetWindowText(hWnd, L":(");
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);
		std::wostringstream oss;
		oss << "(" << pt.x << ", " << pt.y << ")";
		SetWindowText(hWnd, oss.str().c_str());
	}
	break;
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
