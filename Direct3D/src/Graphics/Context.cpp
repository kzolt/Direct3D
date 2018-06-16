#include "Context.h"

Context::Context(const Window& window)
{
	InitD3D(window);
}

Context::~Context()
{
	swapchain->Release();
	dev->Release();
	devcon->Release();
}

void Context::InitD3D(const Window& window)
{
	DXGI_SWAP_CHAIN_DESC scd;
	memset(&scd, 0, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;			
	scd.OutputWindow = window.GetHandle();
	scd.SampleDesc.Count = 4;
	scd.Windowed = true;

	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon);
}