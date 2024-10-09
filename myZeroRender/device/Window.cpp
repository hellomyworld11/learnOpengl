#include "Window.h"
//#include <stdlib.h>
#include <assert.h>
#include "../util/Logger.h"
#include "../Render.h"

static const char *const WINDOW_ENTRY_NAME = "MainWindow";
static const char *const CURWINDOW_OBJ = "WindowObj";

LRESULT CALLBACK _wind_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

Window::Window()
{
	Register_Window();
}


Window::~Window()
{
}

window_t* Window::Create(const char *title, int width, int height)
{
	window_t *window;
	HWND handle;
	image_t *surface;
	HDC memory_dc;
	
	assert(width > 0 && height > 0);

	//创建窗口
	handle = Create_Window(title, width, height);

	//创建窗口内的图像
	Create_Surface(handle, width, height, &surface, &memory_dc);

	window = (window_t*)malloc(sizeof(window_t));
	memset(window, 0, sizeof(window_t));
	window->handle = handle;
	window->memory_dc = memory_dc;
	window->surface = surface;

	SetProp(handle, WINDOW_ENTRY_NAME, window);
	SetProp(handle, CURWINDOW_OBJ, this);
	ShowWindow(handle, SW_SHOW);
	return window;
}

bool Window::DrawBuffer(window_t *window, FrameBuffer *buffer)
{
	int width = window->surface->width;
	int height = window->surface->height;
	int r, c;

	assert(buffer->width_ == window->surface->width && buffer->height_ == window->surface->height);
	assert(window->surface->format == FORMAT_LDR && window->surface->channels == 4);

	for (r = 0; r < height; r++) {
		for (c = 0; c < width; c++) {
			int flipped_r = height - 1 - r;
			int src_index = (r * width + c) * 4;
			int dst_index = (flipped_r * width + c) * 4;
			//unsigned char* src_pixel = &buffer->color_buffer_[src_index];
			Color& src_pixel = buffer->color_buffer_[r][c];
			unsigned char* dst_pixel = &window->surface->ldr_buffer[dst_index];
			dst_pixel[0] = src_pixel[2];  /* blue */
			dst_pixel[1] = src_pixel[1];  /* green */
			dst_pixel[2] = src_pixel[0];  /* red */
		}
	}

	Present_Surface(window);
	return true;
}

int Window::Should_Close(window_t *window)
{
	return window->should_close;
}

void Window::Set_UserData(window_t *window, void *userdata)
{
	window->userdata = userdata;
}

void* Window::Get_UserData(window_t *window)
{
	return window->userdata;
}

void Window::Input_PollEvents()
{
	MSG message;
	while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

bool Window::Register_Window()
{
	ATOM class_atom;
	WNDCLASS winClass;
	winClass.style = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = _wind_Proc; // _wind_Proc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = GetModuleHandle(NULL);
	winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = WINDOW_CLASS_NAME;
	class_atom = RegisterClass(&winClass);
	assert(class_atom != 0);
	return true;
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
	
//	width = rect.right - rect.left;
//	height = rect.bottom - rect.top;

 	handle = CreateWindow(WINDOW_CLASS_NAME, title, style, CW_USEDEFAULT, CW_USEDEFAULT,
		width, height, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);

	assert(handle != nullptr);

	return handle;
}

void Window::Create_Surface(HWND handle, int width, int height, image_t **out_surface, HDC *out_memory_dc)
{
	BITMAPINFOHEADER bi_header;
	HBITMAP dib_bitmap;
	HBITMAP old_bitmap;
	HDC window_dc;
	HDC memory_dc;
	image_t *surface;

	surface = Create_Image(width, height, 4, FORMAT_LDR);
	free(surface->ldr_buffer);
	surface->ldr_buffer = NULL;

	window_dc = GetDC(handle);
	memory_dc = CreateCompatibleDC(window_dc);
	ReleaseDC(handle, window_dc);

	memset(&bi_header, 0, sizeof(BITMAPINFOHEADER));
	bi_header.biSize = sizeof(BITMAPINFOHEADER);
	bi_header.biWidth = width;
	bi_header.biHeight = -height;  /* top-down */
	bi_header.biPlanes = 1;
	bi_header.biBitCount = 32;
	bi_header.biCompression = BI_RGB;
	dib_bitmap = CreateDIBSection(memory_dc, (BITMAPINFO*)&bi_header,
		DIB_RGB_COLORS, (void**)&surface->ldr_buffer,
		NULL, 0);
	assert(dib_bitmap != NULL);
	old_bitmap = (HBITMAP)SelectObject(memory_dc, dib_bitmap);
	DeleteObject(old_bitmap);

	*out_surface = surface;
	*out_memory_dc = memory_dc;
}

image_t * Window::Create_Image(int width, int height, int channels, format_t format)
{
	int num_elems = width * height * channels;
	image_t* image;

	assert(width > 0 && height > 0 && channels >= 1 && channels <= 4);
	assert(format == FORMAT_LDR || format == FORMAT_HDR);

	image = (image_t*)malloc(sizeof(image_t));
	image->format = format;
	image->width = width;
	image->height = height;
	image->channels = channels;
	image->ldr_buffer = NULL;
	image->hdr_buffer = NULL;

	if (format == FORMAT_LDR) {
		int size = sizeof(unsigned char) * num_elems;
		image->ldr_buffer = (unsigned char*)malloc(size);
		memset(image->ldr_buffer, 0, size);
	}
	else {
		int size = sizeof(float) * num_elems;
		image->hdr_buffer = (float*)malloc(size);
		memset(image->hdr_buffer, 0, size);
	}

	return image;
}

void Window::Present_Surface(window_t* window)
{
	HDC window_dc = GetDC(window->handle);
	HDC memory_dc = window->memory_dc;
	image_t *surface = window->surface;
	int width = surface->width;
	int height = surface->height;

	BitBlt(window_dc,0, 0, width, height, memory_dc, 0, 0, SRCCOPY);
	BitBlt(window_dc, 0, 0, width, height, memory_dc, 0, 0, SRCCOPY);
	ReleaseDC(window->handle, window_dc);
}

void Window::Image_Release(image_t* image)
{
	free(image->ldr_buffer);
	free(image->hdr_buffer);
	free(image);
}

void Window::Window_Destroy(window_t *window)
{
	ShowWindow(window->handle, SW_HIDE);
	RemoveProp(window->handle, WINDOW_ENTRY_NAME);

	DeleteDC(window->memory_dc);
	DestroyWindow(window->handle);

	window->surface->ldr_buffer = NULL;
	Image_Release(window->surface);
	free(window);
}

bool Window::SetRenderSecene(Render* prender)
{
	curRender_ = prender;
}

void Window::On_key_message(Window* winobj, window_t *window, WPARAM virtual_key, bool pressed)
{
	keycode_t key;
	switch (virtual_key)
	{
	case 'A':
		key = keycode_t::KEY_A;
		break;
	case 'D':
		key = keycode_t::KEY_D;
		break;
	case 'W':
		key = keycode_t::KEY_W;
		break;
	case 'S':
		key = keycode_t::KEY_S;
		break;
	case 'Q':
		key = keycode_t::KEY_Q;
		break;
	case 'E':
		key = keycode_t::KEY_E;
		break;
	case VK_SPACE:
		key = keycode_t::KEY_SPACE;
		break;
	default:
		key = keycode_t::KEY_NUM;
		break;
	}
	if (key < keycode_t::KEY_NUM)
	{
		if (winobj->curRender_)
		{
			winobj->curRender_->On_key_down(key, pressed);
		}
	}
}

LRESULT CALLBACK _wind_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
 	window_t *window = (window_t*)GetProp(hWnd, WINDOW_ENTRY_NAME);
	Window *winObj = (Window*)GetProp(hWnd, CURWINDOW_OBJ);
 	if (window == NULL) return DefWindowProc(hWnd, uMsg, wParam, lParam);
	if (winObj == NULL) return DefWindowProc(hWnd, uMsg, wParam, lParam);

	if (uMsg == WM_CLOSE) {
		UINT ret =  MessageBox(NULL, "确认关闭当前窗口吗", "提示", MB_YESNO);
//		window->should_close = 1;
		window->should_close = (ret == IDYES);
		return 0;
	}
	else if (uMsg == WM_KEYDOWN) {
		LOG("WM_KEYDOWN");
		Window::On_key_message(winObj, window, wParam, true);
		return 0;
	}
	else if (uMsg == WM_KEYUP) {
		LOG("WM_KEYUP");
		Window::On_key_message(winObj, window, wParam, 0);
		return 0;
	}
	else if (uMsg == WM_LBUTTONDOWN) {
		LOG("WM_LBUTTONDOWN");
	//	handle_button_message(window, BUTTON_L, 1);
		return 0;
	}
	else if (uMsg == WM_RBUTTONDOWN) {
		LOG("WM_RBUTTONDOWN");
	//	handle_button_message(window, BUTTON_R, 1);
		return 0;
	}
	else if (uMsg == WM_LBUTTONUP) {
		LOG("WM_LBUTTONUP");
	//	handle_button_message(window, BUTTON_L, 0);
		return 0;
	}
	else if (uMsg == WM_RBUTTONUP) {
		LOG("WM_RBUTTONUP");
	//	handle_button_message(window, BUTTON_R, 0);
		return 0;
	}
	else if (uMsg == WM_MOUSEWHEEL) {
		LOG("WM_MOUSEWHEEL");
		float offset = GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
	//	handle_scroll_message(window, offset);
		return 0;
	}
	else {
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
