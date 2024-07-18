#include <iostream>

#include "device/Color.h"
#include "device/Window.h"
#include "device/FrameBuffer.h"
#include <minwindef.h>

static const char* const WINDOW_TITLE = "ZeroRender";

static const int WINDOW_WIDTH = 1000;

static const int WINDOW_HEIGHT = 600;

//ªÊ÷∆÷±œﬂ
void line(FrameBuffer* frame, int x0, int y0, int x1, int y1, Color color)
{
	int k = (y1 - y0) / (x1 - x0);
	for (int x = x0; x < x1; x++)
	{
		int y = (x - x0) * k + y0;

		frame->SetColor(x, y, color);
	}

}


int main()
{
	Window mainwin;

	window_t *window;

	window = mainwin.Create(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

	FrameBuffer* frame_buffer = new FrameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	while (!mainwin.Should_Close(window))
	{

//		frame_buffer->SetColor(500, 100, 50, 50, Color(255, 255, 255, 0));

		line(frame_buffer, 100, 100, 200, 200, Color(255, 255, 255, 0));

		mainwin.DrawBuffer(window, frame_buffer);

		frame_buffer->FrameBufferClearColor(Color(0, 0, 0, 0));

		frame_buffer->FrameBufferClearDepth(DBL_MAX);

		mainwin.Input_PollEvents();
	}

	delete frame_buffer;

	mainwin.Window_Destroy(window);

	getchar();

	return 0;
}