#include <iostream>

#include "device/Color.h"
#include "device/Window.h"
#include "device/FrameBuffer.h"
#include <minwindef.h>

static const char* const WINDOW_TITLE = "ZeroRender";

static const int WINDOW_WIDTH = 1000;

static const int WINDOW_HEIGHT = 600;



int main()
{
	Window mainwin;

	window_t *window;

	window = mainwin.Create(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

	FrameBuffer* frame_buffer = new FrameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	while (!mainwin.Should_Close(window))
	{

		frame_buffer->SetColor(100, 100, 50, 50, Color(255, 255, 255, 0));

		mainwin.DrawBuffer(window, frame_buffer);

		frame_buffer->FrameBufferClearColor(Color(255, 0, 255, 0));

		frame_buffer->FrameBufferClearDepth(DBL_MAX);

		mainwin.Input_PollEvents();
	}

	delete frame_buffer;

	mainwin.Window_Destroy(window);

	getchar();

	return 0;
}