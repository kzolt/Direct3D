#include "Window.h"

Window::Window(const char* title, int width, int height, HINSTANCE& hInstance, int nCmdShow)
	: m_Title(title), m_Width(width), m_Height(height)
{
	CreateAndRegisterWindowClass(hInstance);
	CreateAndShowWindow(hInstance, nCmdShow);
}

Window::~Window()
{

}

void Window::CreateAndRegisterWindowClass(HINSTANCE& hInstance)
{
	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "WindowClass";

	RegisterClassEx(&wc);
}

void Window::CreateAndShowWindow(HINSTANCE& hInstance, int nCmdShow)
{
	m_hWnd = CreateWindowEx(NULL, 
		"WindowClass",					// WindowClass
		m_Title,						// Title
		WS_OVERLAPPEDWINDOW,			// Window Style
		10,								// X-Location
		10,								// Y-Location
		m_Width,						// Width of window
		m_Height,						// Height of window
		NULL,							// No Parent
		NULL,							// Not using menus
		hInstance,						// Instance
		NULL);
	
	ShowWindow(m_hWnd, nCmdShow);
}