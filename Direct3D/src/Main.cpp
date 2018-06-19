#include <Windows.h>

#include "System/Window.h"
#include "Graphics/Context.h"
#include "Graphics/Shader.h"
#include "Graphics/Buffers/VertexBuffer.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window("Direct3D", 800, 600, hInstance, nCmdShow);
	Context context(window);
	Shader shader(context);

	VERTEX OurVertices[] =
	{
		{  0.0f,   0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
		{  0.45f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ -0.45f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f }
	};

	VertexBuffer vb(context, shader);
	vb.SetData(OurVertices, sizeof(VERTEX) * 3);

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