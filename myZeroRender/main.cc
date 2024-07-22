#include <iostream>

#include "device/Color.h"
#include "device/Window.h"
#include "device/FrameBuffer.h"
#include <minwindef.h>
#include "mdl/Model.h"

static const char* const WINDOW_TITLE = "ZeroRender";

static const int WINDOW_WIDTH = 800;

static const int WINDOW_HEIGHT = 800;

//绘制直线
void line(FrameBuffer* frame, int x0, int y0, int x1, int y1, Color color)
{
// 	int k = (y1 - y0) / (x1 - x0);
// 	for (int x = x0; x < x1; x++)
// 	{
// 		int y = (x - x0) * k + y0;
// 
// 		frame->SetColor(x, y, color);
// 	}

//	for (float t = 0.; t < 1.; t+=.1)
//	{
//		int x = x0 + (x1 - x0) * t;
//		int y = y0 + (y1 - y0) * t;
//		frame->SetColor(x, y, color);
//	}

	//y的变化速度和x不一样
 	bool steep = false;
 	if (abs(x1 - x0) < abs(y1 - y0))
 	{
 		std::swap(x0, y0);
 		std::swap(x1, y1);
 		steep = true;
 	}
 
 	if (x0 > x1)  //如果x0 大于x1 ，则需要交换 ，始终使x从小到大
 	{
 		std::swap(x0, x1); 
 		std::swap(y0, y1);
 	}
 
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = std::abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {
		if (steep) {
			frame->SetColor(y, x, color);
		}
		else {
			frame->SetColor(x, y, color);
		}
		error2 += derror2;
		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
	
}


int main()
{
	Window mainwin;

	window_t *window;

	window = mainwin.Create(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

	FrameBuffer* frame_buffer = new FrameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	Model *model = new Model("obj/african_head.obj");

	while (!mainwin.Should_Close(window))
	{
//		frame_buffer->SetColor(500, 100, 50, 50, Color(255, 255, 255, 0));
		for (int i = 0; i < model->nfaces(); i++) {
			std::vector<int> face = model->face(i);
			for (int j = 0; j < 3; j++) {
				Vec3f v0 = model->vert(face[j]);
				Vec3f v1 = model->vert(face[(j + 1) % 3]);
				int x0 = (v0.x + 1.) * WINDOW_WIDTH  / 2.;
				int y0 = (v0.y + 1.) * WINDOW_HEIGHT / 2.;
				int x1 = (v1.x + 1.) * WINDOW_WIDTH  / 2.;
				int y1 = (v1.y + 1.) * WINDOW_HEIGHT / 2.;
				line(frame_buffer, x0, y0, x1, y1, Color(255, 255, 255, 0));
			}
		}

//		line(frame_buffer, 13, 20, 80, 40, Color(255, 255, 255, 0));
//		line(frame_buffer, 20, 13, 40, 80, Color(255, 0, 0, 0));
//		line(frame_buffer, 80, 40, 13, 20, Color(255, 0, 0, 0));

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