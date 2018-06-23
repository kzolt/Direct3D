#include <Windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXMathMatrix.inl>

#include "System/Window.h"
#include "Graphics/Context.h"
#include "Graphics/Shader.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/ConstantBuffer.h"

using namespace DirectX;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window("Direct3D", 800, 600, hInstance, nCmdShow);
	Context context(window);
	Shader shader(context);

	VertexData OurVertices[] =
	{
		{  0.0f,   0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
		{  0.45f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ -0.45f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f }
	};

	VertexBuffer vb(context);
	BufferLayout layout;
	layout.Push<float>("POSITION", 3);
	layout.Push<float>("COLOR", 4);

	vb.SetData(OurVertices, sizeof(VertexData) * 3);
	vb.SetLayout(layout, shader);

	ConstantBuffer cbuffer(context, 64);
	cbuffer.Bind();

	// Main Loop

	MSG msg = { 0 };

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}

		context.Clear();

		static float time = 0.0f; 
		time += 0.01f;

		// World Matrix (Model)
		XMMATRIX world = XMMatrixRotationY(time);

		// View Matrix
		XMMATRIX view = XMMatrixLookAtLH({ 1.5f, 0.5f, 1.5f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });

		// Projection Matrix
		XMMATRIX proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0f), (float)window.GetWidth() / (float)window.GetHeight(), 1.0f, 100.0f);

		// Model View Projection Matrix
		XMMATRIX wvp = world * view * proj;

		// Render here

		// Update The Constant Buffer
		cbuffer.UpdateBuffer(wvp);

		// Bind
		vb.Bind();

		// Draw
		context.devcon->Draw(3, 0);


		context.Present();
	}
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProcA(hWnd, message, wParam, lParam);
}