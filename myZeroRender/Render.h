#pragma once
#include "mdl/geometry.h"
#include <iostream>
#include <vector>
#include "device/Window.h"
class FrameBuffer;
class Color;
class Model;

class Render
{
public:
	Render(FrameBuffer *buffer = nullptr);

	~Render();

	void Show(Model *model);
	//对外设的响应
	//键盘
	void On_key_down(keycode_t key, bool pressed);
	//鼠标
	void On_Mouse_down();
	//滚轮
	void On_Wheel_scroll();
private:
	void Line(int x0, int y0, int x1, int y1, Color color);

	void Line(Vec2i p1, Vec2i p2, Color color);
	
	bool IsPtInTriangle(Vec2i p, Vec2i t0, Vec2i t1, Vec2i t2);

	void Triangle(Vec2i t0, Vec2i t1, Vec2i t2, Color color);

	void TriangleWithZbuffer(Vec3f t0, Vec3f t1, Vec3f t2, Color color);

	//网格绘制
	void Wireframe(Model *model);
	//随机颜色绘制
	void RandomColorShader(Model *model);
	//三角形填充
	void TriangleFill();
	//光照下渲染  面法向和光照反向因为看不到而被剔除
	void lightShader(Model *model, Vec3f lightdir);
	//y buffer 2D
	void YBufferTest2D();
	//
	void rasterize2D(Vec2i p0, Vec2i p1, Color color, int ybuffer[]);
	//z buffer 3D
	void lightShaderWithZbuffer(Model *model, Vec3f lightdir);

	//with camera
	void Draw();
private:
	FrameBuffer *frame;

	std::vector< std::vector<float> > zbuffer;
};

