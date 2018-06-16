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

public:
	Context(const Window& window);
	~Context();

private:
	void InitD3D(const Window& window);
};