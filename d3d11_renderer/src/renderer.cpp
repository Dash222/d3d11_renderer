#include "renderer.hpp"

Renderer::Renderer(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&swap,
		&device,
		nullptr,
		&context
	);

	ID3D11Resource* backBuffer = nullptr;
	swap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&backBuffer));
	device->CreateRenderTargetView(
		backBuffer,
		nullptr,
		&target);

	backBuffer->Release();
}

Renderer::~Renderer()
{
	if (context != nullptr)
		context->Release();

	if (device != nullptr)
		device->Release();

	if (swap != nullptr)
		swap->Release();

	if (target != nullptr)
		target->Release();

}


void Renderer::EndFrame()
{
	swap->Present(1u, 0u);
}

void Renderer::ClearBuffer(const float r, const float g, const float b, const float a)
{
	const float color[]{r, g, b, a};
	context->ClearRenderTargetView(target, color);
}
