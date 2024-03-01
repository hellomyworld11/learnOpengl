#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include <iostream>
#include <algorithm>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(0, 0, 255, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(255, 0, 0, 255);
Model *model = NULL;
const int width = 800;
const int height = 800;

//画线
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	for (int x = x0; x <= x1; x++) {
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0*(1. - t) + y1*t;
		if (steep) {
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color);
		}
	}
}
void line(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color) {
	bool steep = false;
	if (std::abs(p0.x - p1.x) < std::abs(p0.y - p1.y)) {
		std::swap(p0.x, p0.y);
		std::swap(p1.x, p1.y);
		steep = true;
	}
	if (p0.x > p1.x) {
		std::swap(p0, p1);
	}

	for (int x = p0.x; x <= p1.x; x++) {
		float t = (x - p0.x) / (float)(p1.x - p0.x);
		int y = p0.y*(1. - t) + p1.y*t;
		if (steep) {
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color);
		}
	}
}

//获取boundingbox
void getboundingbox(std::vector<Vec2i>& pts, std::vector<Vec2i>& box)
{
	int minx = pts[0].x;
	int miny = pts[0].y;
	int maxx = pts[0].x;
	int maxy = pts[0].y;
	for (size_t i = 1; i < pts.size(); i++)
	{
		auto & aPt = pts[i];
		if ( aPt.x < minx)
		{
			minx = aPt.x;
		}
		if (aPt.x > maxx )
		{
			maxx = aPt.x;
		}
		if (aPt.y < miny)
		{
			miny = aPt.y;
		}
		if (aPt.y > maxy)
		{
			maxy = aPt.y;
		}
	}

	box.push_back(Vec2i(minx, miny));
	box.push_back(Vec2i(maxx, maxy));
	std::cout << "box: " << minx << " " << miny << " " << maxx << " " << maxy << std::endl;
}

//判断点是否在三角形内
bool isInsideTriangle(Vec2i pt, std::vector<Vec2i> triangle)
{
	Vec3f v01(triangle[1].x - triangle[0].x, triangle[1].y - triangle[0].y, 0),
		  v12(triangle[2].x - triangle[1].x, triangle[2].y - triangle[1].y, 0), 
		  v20(triangle[0].x - triangle[2].x, triangle[0].y - triangle[2].y, 0);

//	std::cout << "v01before: " << v01 << " " << v12 << " " << v20 << " " << std::endl;

	v01.normalize();
	v12.normalize();
	v20.normalize();

//	std::cout << "v01end: " << v01 << " " << v12 << " " << v20 << " " <<  std::endl;

	Vec3f v0p(pt.x - triangle[0].x, pt.y - triangle[0].y, 0);
	Vec3f v1p(pt.x - triangle[1].x, pt.y - triangle[1].y, 0);
	Vec3f v2p(pt.x - triangle[2].x, pt.y - triangle[2].y, 0);

	v0p.normalize();
	v1p.normalize();
	v2p.normalize();

	Vec3f z1 = cross(v0p, v01);
	Vec3f z2 = cross(v1p, v12);
	Vec3f z3 = cross(v2p, v20);
	if ( (z1*z2)&&(z2*z3) < 0 )
	{
		return false;
	}
	return true;
}

//绘制三角形
void triangle(Vec2i p1, Vec2i p2, Vec2i p3, TGAImage &image, TGAColor color)
{

	if (p1.y > p2.y) std::swap(p1, p2);
	if (p1.y > p3.y) std::swap(p1, p3);
	if (p2.y > p3.y) std::swap(p2, p3);

	line(p1, p2, image, color);
	line(p2, p3, image, color);
	line(p3, p1, image, color);

	std::vector<Vec2i> pts = {p1, p2, p3};
	//fill
	//get boundingbox
	std::vector<Vec2i> box;
	getboundingbox(pts, box);
	//
	for (int x = box[0].x; x < box[1].x; x++)
	{
		for (int y = box[0].y; y < box[1].y; y++)
		{
			if (isInsideTriangle(Vec2i(x, y), pts))
			{
	//			image.set(x, y, color);
			}
		}
	}
}

//点在区域内 质心坐标法
Vec3f barycentric(Vec2i *pts, Vec2i P) {
	Vec3f u = cross( Vec3f(pts[2].x - pts[0].x, pts[1].x - pts[0].x, pts[0].x - P.x) , Vec3f(pts[2].y - pts[0].y, pts[1].y - pts[0].y, pts[0].y - P.y));
	/* `pts` and `P` has integer value as coordinates
	so `abs(u[2])` < 1 means `u[2]` is 0, that means
	triangle is degenerate, in this case return something with negative coordinates */
	if (std::abs(u.z)<1) return Vec3f(-1, 1, 1);
	return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

//绘制三角形
void triangle(Vec2i *pts, TGAImage &image, TGAColor color) {
	Vec2i bboxmin(image.width() - 1, image.height() - 1);
	Vec2i bboxmax(0, 0);
	Vec2i clamp(image.width() - 1, image.height() - 1);
	for (int i = 0; i<3; i++) {
		bboxmin.x = std::max(0, std::min(bboxmin.x, pts[i].x));
		bboxmin.y = std::max(0, std::min(bboxmin.y, pts[i].y));

		bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
		bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
	}
	Vec2i P;
	for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
		for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
			Vec3f bc_screen = barycentric(pts, P);
			if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue;
			image.set(P.x, P.y, color);
		}
	}
}


Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P) {
	Vec3f s[2];
	for (int i = 2; i--; ) {
		s[i][0] = C[i] - A[i];
		s[i][1] = B[i] - A[i];
		s[i][2] = A[i] - P[i];
	}
	Vec3f u = cross(s[0], s[1]);
	if (std::abs(u[2]) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
		return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
	return Vec3f(-1, 1, 1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}

void triangle(Vec3f *pts, float *zbuffer, TGAImage &image, TGAColor color) {
	Vec2f bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	Vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
	Vec2f clamp(image.width() - 1, image.height() - 1);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			bboxmin[j] = std::max(0.f, std::min(bboxmin[j], pts[i][j]));
			bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
		}
	}
	Vec3f P;
	for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
		for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
			Vec3f bc_screen = barycentric(pts[0], pts[1], pts[2], P);
			if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
			P.z = 0;
			for (int i = 0; i < 3; i++) P.z += pts[i][2] * bc_screen[i];
			if (zbuffer[int(P.x + P.y*width)] < P.z) {
				zbuffer[int(P.x + P.y*width)] = P.z;
				image.set(P.x, P.y, color);
			}
		}
	}
}

Vec3f world2screen(Vec3f v) {
	return Vec3f(int((v.x + 1.)*width / 2. + .5), int((v.y + 1.)*height / 2. + .5), v.z);
}



//加载模型并用三角形绘制
void lession1()
{
	model = new Model("obj/african_head.obj");

	TGAImage image(width, height, TGAImage::RGB);
	for (int i = 0; i < model->nfaces(); i++) {
		std::vector<int> face = model->face(i);
		Vec2i screen_coords[3];
		for (int j = 0; j < 3; j++) {
			Vec3f world_coords = model->vert(face[j]);
			screen_coords[j] = Vec2i((world_coords.x + 1.)*width / 2., (world_coords.y + 1.)*height / 2.);
		}
		triangle(screen_coords, image, 
			TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
	}

	//	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	delete model;
	getchar();
	return ;
}

//绘制三角形并光栅化三角形
void lession2()
{
	TGAImage image(200, 200, TGAImage::RGB);
	
//	triangle(Vec2i(10, 10), Vec2i(10, 50), Vec2i(50, 10), image, red);
	Vec2i t0[3] = { Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80) };
	Vec2i t1[3] = { Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180) };
	Vec2i t2[3] = { Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180) };

	//Vec2i pts[3] = { Vec2i(10,10), Vec2i(100, 30), Vec2i(190, 160) };
	triangle(t0, image, red);
	triangle(t1, image, white);
	triangle(t2, image, green);
	//triangle(t1[0], t1[1], t1[2], image, white);
	//triangle(t2[0], t2[1], t2[2], image, green);

	//	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	delete model;
	getchar();
	return;
}

//背面剔除
void lession2_lightTest()
{
	model = new Model("obj/african_head.obj");

	TGAImage image(width, height, TGAImage::RGB);
	Vec3f light_dir(0, 0, -1); // define light_dir

	for (int i = 0; i < model->nfaces(); i++) {
		std::vector<int> face = model->face(i);
		Vec2i screen_coords[3];
		Vec3f world_coords[3];
		for (int j = 0; j < 3; j++) {
			Vec3f v = model->vert(face[j]);
			screen_coords[j] = Vec2i((v.x + 1.)*width / 2., (v.y + 1.)*height / 2.);
			world_coords[j] = v;
		}
		Vec3f n = cross( (world_coords[2] - world_coords[0]) , (world_coords[1] - world_coords[0]));
		n.normalize();
		std::cout << "vn: " << n << std::endl;
		float intensity = n*light_dir;
		if (intensity > 0) {
			triangle(screen_coords, image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
		//	std::cout << "绘制" << std::endl;
		}
		else {
		//	std::cout << "剔除掉" << std::endl;
			;
		}
	}
	image.write_tga_file("output.tga");
	delete model;
	getchar();
}

//深度缓存
void lession3()
{
	model = new Model("obj/african_head.obj");

	float *zbuffer = new float[width*height];
	for (int i = width*height; i--; zbuffer[i] = -std::numeric_limits<float>::max());

	TGAImage image(width, height, TGAImage::RGB);
	for (int i = 0; i < model->nfaces(); i++) {
		std::vector<int> face = model->face(i);
		Vec3f pts[3];
		for (int i = 0; i < 3; i++) pts[i] = world2screen(model->vert(face[i]));
		triangle(pts, zbuffer, image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
		//triangle(pts, zbuffer, image, white);
	}

//	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	delete model;
}

int main(int argc, char** argv) {
	
	lession3();

}