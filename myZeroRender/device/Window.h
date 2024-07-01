#pragma once
#include <windows.h>

#include "FrameBuffer.h"

typedef struct st_window window_t;

enum class keycode_t { KEY_A, KEY_D, KEY_S, KEY_W, KEY_SPACE, KEY_NUM } ;

enum class button_t { BUTTON_L, BUTTON_R, BUTTON_NUM } ;

typedef struct {
	void(*key_callback)(window_t *window, keycode_t key, int pressed);

	void(*button_callback)(window_t *window, button_t button, int pressed);

	void(*scroll_callback)(window_t *window, float offset);
} callbacks_t;

typedef enum {
	FORMAT_LDR,
	FORMAT_HDR
} format_t;

typedef struct {
	format_t format;
	int width, height, channels;
	unsigned char *ldr_buffer;
	float *hdr_buffer;
} image_t;

struct st_window {
	HWND handle;
	HDC memory_dc;
	image_t *surface;
	/* common data */
	int should_close;
	char keys[(unsigned short)keycode_t::KEY_NUM];
	char buttons[(unsigned short)button_t::BUTTON_NUM];
	callbacks_t callbacks;
	void *userdata;
};

class Window
{
public:
	const char *const WINDOW_CLASS_NAME = "Class";

	explicit Window();

	~Window();

	window_t* Create(const char *title, int width, int height);

	bool DrawBuffer(window_t *window, FrameBuffer *buffer);

	int Should_Close(window_t *window);

	void Set_UserData(window_t *window, void *userdata);

	void* Get_UserData(window_t *window);

	void Input_PollEvents();

	void Window_Destroy(window_t *window);
private:
	bool Register_Window();

	void UnRegister_Window();

	void Init_Path();

	HWND Create_Window(const char *title, int width, int height);

	void Create_Surface(HWND handle, int width, int height, image_t **out_surface, HDC *out_memory_dc);

	image_t * Create_Image(int width, int height, int channels, format_t format);

	void Present_Surface(window_t* window);

	// Õ∑≈

	void Image_Release(image_t* image);
	
};

