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
	m_BackBuffer->Release();
	m_DepthBuffer->Release();
}

void Context::InitD3D(const Window& window)
{
	// Init Swapchain, Device, and Device Context
	DXGI_SWAP_CHAIN_DESC scd;
	memset(&scd, 0, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;										// One backbuffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			// 32-bit colour
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;			// the swapchain is to be used
	scd.OutputWindow = window.GetHandle();						// window to output to
	scd.SampleDesc.Count = 4;									// how many multisamples
	scd.Windowed = true;										// is windowed?

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

	// Create Z-Buffer (Depth Buffer)
	D3D11_TEXTURE2D_DESC textd;
	memset(&textd, 0, sizeof(D3D11_TEXTURE2D_DESC));

	textd.Width = (unsigned int)window.GetWidth();
	textd.Height = (unsigned int)window.GetHeight();
	textd.ArraySize = 1;
	textd.MipLevels = 1;
	textd.SampleDesc.Count = 4;
	textd.Format = DXGI_FORMAT_D32_FLOAT;
	textd.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	ID3D11Texture2D* pDepthBuffer;
	dev->CreateTexture2D(&textd, NULL, &pDepthBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	memset(&dsvd, 0, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

	dev->CreateDepthStencilView(pDepthBuffer, &dsvd, &m_DepthBuffer);
	pDepthBuffer->Release();

	// Set Render Target
	ID3D11Texture2D* pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	dev->CreateRenderTargetView(pBackBuffer, NULL, &m_BackBuffer);
	pBackBuffer->Release();

	devcon->OMSetRenderTargets(1, &m_BackBuffer, m_DepthBuffer);

	// Set Viewport
	memset(&m_ScreenViewport, 0, sizeof(D3D11_VIEWPORT));

	m_ScreenViewport.TopLeftX = 0;
	m_ScreenViewport.TopLeftY = 0;
	m_ScreenViewport.Width = (float)window.GetWidth();
	m_ScreenViewport.Height = (float)window.GetHeight();
	m_ScreenViewport.MinDepth = 0;
	m_ScreenViewport.MaxDepth = 1;

	devcon->RSSetViewports(1, &m_ScreenViewport);
}

void Context::Clear() const
{
	float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	devcon->ClearRenderTargetView(m_BackBuffer, clearColor);

	devcon->ClearDepthStencilView(m_DepthBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Context::Present() const
{
	swapchain->Present(1, 0);
}