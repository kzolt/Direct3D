#include <Windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXMathMatrix.inl>

#include "System/Window.h"
#include "Graphics/Context.h"
#include "Graphics/Shader.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/ConstantBuffer.h"

using namespace DirectX;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window("Direct3D", 800, 600, hInstance, nCmdShow);
	Context context(window);
	Shader shader(context);

	VertexData Cube[] =
	{
		{ -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f },
		{  1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f },
		{ -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f },
		{  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f },
		{ -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 1.0f },
		{  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 1.0f },
		{ -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 0.0f },
		{  1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f },
	};

	unsigned int CubeIndices[] =
	{
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 0, 6,    // side 2
		6, 0, 2,
		7, 5, 6,    // side 3
		6, 5, 4,
		3, 1, 7,    // side 4
		7, 1, 5,
		4, 5, 0,    // side 5
		0, 5, 1,
		3, 7, 2,    // side 6
		2, 7, 6,
	};

	VertexBuffer vb(context);
	BufferLayout layout;
	layout.Push<float>("POSITION", 3);
	layout.Push<float>("NORMAL", 3);

	vb.SetData(Cube, sizeof(VertexData) * 8);
	vb.SetLayout(layout, shader);

	ConstantBuffer cbuffer(context, 176);
	cbuffer.Bind();

	IndexBuffer ib(3 * 12, context);
	ib.SetData(CubeIndices);

	CBuffer cbufferData;
	cbufferData.lightvec = { 1.0f, 1.0f, 1.0f, 0.0f };
	cbufferData.lightcol = { 0.5f, 0.5f, 0.5f, 1.0f };
	cbufferData.ambientcol = { 0.2f, 0.2f, 0.2f, 1.0f };

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
		XMMATRIX view = XMMatrixLookAtLH({ 0.0f, 2.0f, 8.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });

		// Projection Matrix
		XMMATRIX proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0f), (float)window.GetWidth() / (float)window.GetHeight(), 1.0f, 100.0f);

		// Model View Projection Matrix
		cbufferData.matrix = world * view * proj;
		cbufferData.rotation = world;

		// Render here

		// Update The Constant Buffer
		cbuffer.UpdateBuffer(cbufferData);

		// Bind
		vb.Bind();
		ib.Bind();

		// Draw
		context.devcon->DrawIndexed(ib.GetCount(), 0, 0);


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