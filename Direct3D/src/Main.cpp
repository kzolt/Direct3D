#include <Windows.h>

#include "System/Window.h"
#include "Graphics/Context.h"
#include "Graphics/Shader.h"

struct VERTEX
{
	float x, y, z;
	float r, g, b, a;
};

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

	// Vertex Buffer setup
	ID3D11Buffer* pVertexBuffer;
	D3D11_BUFFER_DESC bd;
	memset(&bd, 0, sizeof(D3D11_BUFFER_DESC));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX) * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	context.dev->CreateBuffer(&bd, NULL, &pVertexBuffer);

	// Fill Vertex Buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	context.devcon->Map(pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, OurVertices, sizeof(OurVertices));
	context.devcon->Unmap(pVertexBuffer, NULL);

	// Input Layout - TODO: Move this code
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	context.dev->CreateInputLayout(ied, 2, shader.GetVSBlob()->GetBufferPointer(), shader.GetVSBlob()->GetBufferSize(), &context.layout);
	context.devcon->IASetInputLayout(context.layout);

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

		// Bind Vertex Buffers
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		context.devcon->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

		// Set the primitive we're using
		context.devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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