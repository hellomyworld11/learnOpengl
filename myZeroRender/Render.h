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
	
	bool IsPtInTriangle(Vec2i p, Vec2i t0, Vec2i t1, Vec2i t2);

	void Triangle(Vec2i t0, Vec2i t1, Vec2i t2, Color color);
	//网格绘制
	void Wireframe(Model *model);
	//随机颜色绘制
	void RandomColorShader(Model *model);
	//三角形填充
	void TriangleFill();
	//光照下渲染
	void lightShader(Model *model, Vec3f lightdir);
private:
	FrameBuffer *frame;
};

