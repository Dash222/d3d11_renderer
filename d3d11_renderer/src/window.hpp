#pragma once

#include <Windows.h>
#include <memory>

#include "renderer.hpp"

class Window
{
public:
	Window();
	~Window();

	void Update();
	int End();

private:
	static constexpr wchar_t className[] = L"hw3dhello";
	HWND hWnd;
	HINSTANCE hInstance;
	HRESULT hr;

	MSG msg;
	BOOL gResult;

	std::unique_ptr<Renderer> renderer;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};