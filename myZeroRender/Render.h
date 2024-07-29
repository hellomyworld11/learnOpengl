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
	//�������
	void Wireframe(Model *model);
	//�����ɫ����
	void RandomColorShader(Model *model);
	//���������
	void TriangleFill();
	//��������Ⱦ
	void lightShader(Model *model, Vec3f lightdir);
private:
	FrameBuffer *frame;
};

