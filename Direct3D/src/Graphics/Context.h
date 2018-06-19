#pragma once

#include <d3d11.h>

#include "../System/Window.h"

class Context
{
public:
	IDXGISwapChain* swapchain;
	ID3D11Device* dev;
	ID3D11DeviceContext* devcon;

private:
	ID3D11RenderTargetView* m_BackBuffer;
	D3D11_VIEWPORT m_ScreenViewport;

public:
	Context(const Window& window);
	~Context();

	void Clear() const;
	void Present() const;

private:
	void InitD3D(const Window& window);

};