#include "Render.h"
#include "device/FrameBuffer.h"
#include "device/Color.h"
#include "mdl/Model.h"
#include <algorithm>
#include "device/config.h"
#include "util/function.h"

Render::Render(FrameBuffer *buffer):frame(buffer)
{
}

Render::~Render()
{
}

void Render::Show(Model *model)
{
	int num = rand() % 3 + 1;

	if (model == nullptr) return;

	Vec3f light_dir(0, 0, -1); // define light_dir

	lightShader(model, light_dir);
	return;
	if (num == 1)
	{
		Wireframe(model);
	}
	if (num == 2)
	{
		RandomColorShader(model);
	}
	if (num == 3)
	{
		TriangleFill();
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

//绘制直线
void Render::Line(int x0, int y0, int x1, int y1, Color color)
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

bool Render::IsPtInTriangle(Vec2i p, Vec2i t0, Vec2i t1, Vec2i t2)
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
void Render::Triangle(Vec2i t0, Vec2i t1, Vec2i t2, Color color)
{
	Line(t0.x, t0.y, t1.x, t1.y, color);
	Line(t1.x, t1.y, t2.x, t2.y, color);
	Line(t2.x, t2.y, t0.x, t0.y, color);

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

void Render::Wireframe(Model *model)
{
	//网格化绘制模型
	for (int i = 0; i < model->nfaces(); i++) {
		std::vector<int> face = model->face(i);
		for (int j = 0; j < 3; j++) {
			Vec3f v0 = model->vert(face[j]);
			Vec3f v1 = model->vert(face[(j + 1) % 3]);
			int x0 = (v0.x + 1.) * WINDOW_WIDTH / 2.;
			int y0 = (v0.y + 1.) * WINDOW_HEIGHT / 2.;
			int x1 = (v1.x + 1.) * WINDOW_WIDTH / 2.;
			int y1 = (v1.y + 1.) * WINDOW_HEIGHT / 2.;
			Line(x0, y0, x1, y1, Color(255, 255, 255, 0));
		}
	}
}

void Render::RandomColorShader(Model *model)
{
	for (int i = 0; i < model->nfaces(); i++) {
		std::vector<int> face = model->face(i);
		Vec2i screen_coords[3];
		for (int j = 0; j < 3; j++) {
			Vec3f world_coords = model->vert(face[j]);
			screen_coords[j] = Vec2i((world_coords.x + 1.)*WINDOW_WIDTH / 2., (world_coords.y + 1.)*WINDOW_HEIGHT / 2.);
		}
		Triangle(screen_coords[0], screen_coords[1], screen_coords[2], Color(rand() % 255, rand() % 255, rand() % 255, 0));
	}
}

void Render::TriangleFill()
{
	//画三角形
	Vec2i t0[3] = { Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80) };
	Vec2i t1[3] = { Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180) };
	Vec2i t2[3] = { Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180) };
	Triangle(t0[0], t0[1], t0[2], Color(255, 0, 0, 0));
	Triangle(t1[0], t1[1], t1[2], Color(0, 255, 0, 0));
	Triangle(t2[0], t2[1], t2[2], Color(0, 0, 255, 0));
//	Line(13, 20, 80, 40, Color(255, 255, 255, 0));
//	Line(20, 13, 40, 80, Color(255, 0, 0, 0));
//	Line(80, 40, 13, 20, Color(255, 0, 0, 0));
}

void Render::lightShader(Model *model, Vec3f lightdir)
{
	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		Vec2i screen_coords[3];
		Vec3f world_coords[3];
		for (int j = 0; j < 3; j++)
		{
			Vec3f v = model->vert(face[j]);
			screen_coords[j] = Vec2i((v.x + 1.)*WINDOW_WIDTH / 2., (v.y + 1.)*WINDOW_HEIGHT / 2.);
			world_coords[j] = v;
		}

		//获取光照方向和 面的法向的角度 得出 明亮强度
		Vec3f srfnormal = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);

		srfnormal.normalize();

		//点乘获取是否同向
		float internsity = srfnormal * lightdir;
		if (compare(internsity, 0) > 0)
		{
			Triangle(screen_coords[0], screen_coords[1], screen_coords[2], Color(internsity * 255, internsity * 255, internsity * 255, 255));
		}
	}
}
