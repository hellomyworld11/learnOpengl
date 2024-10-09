#include <iostream>
#include "device/Color.h"
#include "device/Window.h"
#include "device/FrameBuffer.h"
#include <minwindef.h>
#include "mdl/Model.h"
#include "device/config.h"
#include "Render.h"
#include "util/Logger.h"



int main(int argc, char *argv[])
{
	Window mainwin;

	window_t *window;

	window = mainwin.Create(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

	FrameBuffer* frame_buffer = new FrameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	Model *model = new Model("obj/african_head.obj");

	Vec3f light_dir(0, 0, -1);

	Render render(frame_buffer);

	mainwin.SetRenderSecene(&render);
//	LOG("hello:%s", "log init");

	while (!mainwin.Should_Close(window))
	{
//		frame_buffer->SetColor(500, 100, 50, 50, Color(255, 255, 255, 0));
		render.Show(model);

		mainwin.DrawBuffer(window, frame_buffer);

		frame_buffer->FrameBufferClearColor(Color(0, 0, 0, 0));

		frame_buffer->FrameBufferClearDepth(DBL_MAX);

		mainwin.Input_PollEvents();
	}

	delete model;

	delete frame_buffer;

	mainwin.Window_Destroy(window);

	getchar();

	return 0;
}