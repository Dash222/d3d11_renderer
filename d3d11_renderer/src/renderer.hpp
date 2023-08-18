#pragma once
#include <d3d11.h>

class Renderer
{
public:
	Renderer(HWND hWnd);
	~Renderer();

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	void EndFrame();
	void ClearBuffer(const float r, const float g, const float b, const float a);

private:
	//HWND hWnd;
	ID3D11Device* device = nullptr;
	IDXGISwapChain* swap = nullptr;
	ID3D11DeviceContext* context = nullptr;
	ID3D11RenderTargetView* target = nullptr;
};