#include <iostream>

#include "device/Color.h"
#include "device/Window.h"
#include "device/FrameBuffer.h"
#include <minwindef.h>
#include "mdl/Model.h"
#include <algorithm>

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


int vecCross(Vec2i v1, Vec2i v2)
{
	return  v1.x*v2.y - v1.y*v2.x;
}

int vecdot(Vec2i v1, Vec2i v2)
{
	return (v1.x*v2.x + v1.y*v2.y);
}

bool IsPtInTriangle(Vec2i p, Vec2i t0, Vec2i t1, Vec2i t2)
{
	Vec2i v01 = t1 - t0;
	Vec2i v12 = t2 - t1;
	Vec2i v20 = t0 - t2;

	Vec2i v0p = p - t0;
	Vec2i v1p = p - t1;
	Vec2i v2p = p - t2;

	if ((vecCross(v01, v0p) * vecCross(v12, v1p) > 0) && 
		(vecCross(v12, v1p) * vecCross(v20, v2p) > 0))
	{
		return true;
	}
	return false;
}

//绘制三角形
void triangle(FrameBuffer* frame, Vec2i t0, Vec2i t1, Vec2i t2, Color color)
{
	line(frame, t0.x, t0.y, t1.x, t1.y, color);
	line(frame, t1.x, t1.y, t2.x, t2.y, color);
	line(frame, t2.x, t2.y, t0.x, t0.y, color);

	//填充
	//获取最大x ， y
	std::vector<int> vecx = { t0.x, t1.x, t2.x };
	std::vector<int> vecy = { t0.y, t1.y, t2.y };
	int maxx = *max_element(vecx.begin(), vecx.end());
	int minx = *min_element(vecx.begin(), vecx.end());

	int maxy = *max_element(vecy.begin(), vecy.end());
	int miny = *min_element(vecy.begin(), vecy.end());

	for (int i = minx; i <= maxx; i++)
	{
		for (int j = miny; j <= maxy; j++)
		{
			Vec2i pt(i, j);
			if (IsPtInTriangle(pt, t0, t1, t2))
			{
				frame->SetColor(i, j, color);
			}
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


	Vec2i t0[3] = { Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80) };
	Vec2i t1[3] = { Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180) };
	Vec2i t2[3] = { Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180) };
	

	while (!mainwin.Should_Close(window))
	{
//		frame_buffer->SetColor(500, 100, 50, 50, Color(255, 255, 255, 0));
		//网格化绘制模型
// 		for (int i = 0; i < model->nfaces(); i++) {
// 			std::vector<int> face = model->face(i);
// 			for (int j = 0; j < 3; j++) {
// 				Vec3f v0 = model->vert(face[j]);
// 				Vec3f v1 = model->vert(face[(j + 1) % 3]);
// 				int x0 = (v0.x + 1.) * WINDOW_WIDTH  / 2.;
// 				int y0 = (v0.y + 1.) * WINDOW_HEIGHT / 2.;
// 				int x1 = (v1.x + 1.) * WINDOW_WIDTH  / 2.;
// 				int y1 = (v1.y + 1.) * WINDOW_HEIGHT / 2.;
// 				line(frame_buffer, x0, y0, x1, y1, Color(255, 255, 255, 0));
// 			}
// 		}
		//画三角形
		triangle(frame_buffer, t0[0], t0[1], t0[2], Color(255, 0, 0, 0));
		triangle(frame_buffer, t1[0], t1[1], t1[2], Color(0, 255, 0, 0));
 		triangle(frame_buffer, t2[0], t2[1], t2[2], Color(0, 0, 255, 0));
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