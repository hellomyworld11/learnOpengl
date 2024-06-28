#pragma once
#include <windows.h>

typedef struct st_window window_t;
enum class keycode_t { KEY_A, KEY_D, KEY_S, KEY_W, KEY_SPACE, KEY_NUM } ;
enum class button_t { BUTTON_L, BUTTON_R, BUTTON_NUM } ;
typedef struct {
	void(*key_callback)(window_t *window, keycode_t key, int pressed);
	void(*button_callback)(window_t *window, button_t button, int pressed);
	void(*scroll_callback)(window_t *window, float offset);
} callbacks_t;

struct st_window {
	HWND handle;
	HDC memory_dc;
	//image_t *surface;
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
	Window();
	~Window();

	bool Create();

//	bool DrawBuffer(window_t *window, frame);

	const char *const WINDOW_CLASS_NAME = "Class";
private:
	bool Register_Window();

	void UnRegister_Window();

	void Init_Path();

	HWND Create_Window(const char *title, int width, int height);
};

