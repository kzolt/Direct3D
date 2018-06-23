#include <Windows.h>

#include "System/Window.h"
#include "Graphics/Context.h"
#include "Graphics/Shader.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/ConstantBuffer.h"

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

	ConstantBuffer cbuffer(context);
	cbuffer.Bind();

	CBufferPerFrame perFrame = {
		0.5f, 0.5f, 0.5f, 1.0f,  // Color
		0.5f, 0.2f, 0.7f		 // Position
	};

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

		// Render here

		// Bind
		vb.Bind();
		cbuffer.UpdateBuffer(perFrame);

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