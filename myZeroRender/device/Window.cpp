#include "Window.h"
//#include <stdlib.h>
#include <assert.h>

LRESULT CALLBACK _wind_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

Window::Window()
{
}


Window::~Window()
{
}

bool Window::Register_Window()
{
	WNDCLASS winClass;
	winClass.style = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = _wind_Proc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = GetModuleHandle(NULL);
	winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = WINDOW_CLASS_NAME;
}

void Window::UnRegister_Window()
{
	UnregisterClass(WINDOW_CLASS_NAME, GetModuleHandle(nullptr));
}

void Window::Init_Path()
{
	char path[MAX_PATH];
	GetModuleFileName(nullptr, path, MAX_PATH);
	*strrchr(path, '\\') = '\0';
	
}

HWND Window::Create_Window(const char *title, int width, int height)
{
	DWORD style = WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX;
	RECT rect;
	HWND handle;

	rect.left = 0;
	rect.top = 0;
	rect.right = width;
	rect.bottom = height;

	AdjustWindowRect(&rect, style, VARIANT_FALSE);
	
	width = rect.right - rect.left;
	height = rect.bottom = rect.top;

	handle = CreateWindow(WINDOW_CLASS_NAME, title, style, CW_USEDEFAULT, CW_USEDEFAULT,
		width, height, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);

	assert(handle != nullptr);

	return handle;
}

LRESULT CALLBACK _wind_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
