#pragma once

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class Window
{
private:
	const char* m_Title;
	int m_Width, m_Height;

	HWND m_hWnd;

public:
	Window(const char* title, int width, int height, HINSTANCE& hInstance, int nCmdShow);
	~Window();

private:
	void CreateAndRegisterWindowClass(HINSTANCE& hInstance);
	void CreateAndShowWindow(HINSTANCE& hInstance, int nCmdShow);
};