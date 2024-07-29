#pragma once
#include "mdl/geometry.h"

class FrameBuffer;
class Color;
class Model;

class Render
{
public:
	Render(FrameBuffer *buffer = nullptr);

	~Render();

	void Show(Model *model);

private:
	void Line(int x0, int y0, int x1, int y1, Color color);

	void Line(Vec2i p1, Vec2i p2, Color color);
	
	bool IsPtInTriangle(Vec2i p, Vec2i t0, Vec2i t1, Vec2i t2);

	void Triangle(Vec2i t0, Vec2i t1, Vec2i t2, Color color);
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

	void rasterize2D(Vec2i p0, Vec2i p1, Color color, int ybuffer[]);
private:
	FrameBuffer *frame;
};

