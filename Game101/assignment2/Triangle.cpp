//
// Created by LEI XU on 4/11/19.
//

#include "Triangle.hpp"
#include <algorithm>
#include <array>


Triangle::Triangle() {
    v[0] << 0,0,0;
    v[1] << 0,0,0;
    v[2] << 0,0,0;

    color[0] << 0.0, 0.0, 0.0;
    color[1] << 0.0, 0.0, 0.0;
    color[2] << 0.0, 0.0, 0.0;

    tex_coords[0] << 0.0, 0.0;
    tex_coords[1] << 0.0, 0.0;
    tex_coords[2] << 0.0, 0.0;
}

void Triangle::setVertex(int ind, Vector3f ver){
    v[ind] = ver;
}
void Triangle::setNormal(int ind, Vector3f n){
    normal[ind] = n;
}
void Triangle::setColor(int ind, float r, float g, float b) {
    if((r<0.0) || (r>255.) ||
       (g<0.0) || (g>255.) ||
       (b<0.0) || (b>255.)) {
        fprintf(stderr, "ERROR! Invalid color values");
        fflush(stderr);
        exit(-1);
    }

    color[ind] = Vector3f((float)r/255.,(float)g/255.,(float)b/255.);
    return;
}
void Triangle::setTexCoord(int ind, float s, float t) {
    tex_coords[ind] = Vector2f(s,t);
}

std::array<Vector4f, 3> Triangle::toVector4() const
{
    std::array<Eigen::Vector4f, 3> res;
    std::transform(std::begin(v), std::end(v), res.begin(), [](auto& vec) { return Eigen::Vector4f(vec.x(), vec.y(), vec.z(), 1.f); });
    return res;
}


std::array<Eigen::Vector2f, 2> Triangle::boundingBox(std::array<Eigen::Vector4f, 3>& pnts)const
{
	float aabb_minx = 0;
	float aabb_miny = 0;
	float aabb_maxx = 0;
	float aabb_maxy = 0;
	for (size_t i = 0; i < pnts.size(); i++)
	{
		const Eigen::Vector4f& p = pnts[i];
		if (i == 0)
		{
			aabb_minx = aabb_maxx = p.x();
			aabb_miny = aabb_maxy = p.y();
			continue;
		}

		aabb_minx = p.x() < aabb_minx ? p.x() : aabb_minx;
		aabb_miny = p.y() < aabb_miny ? p.y() : aabb_miny;

		aabb_maxx = p.x() > aabb_maxx ? p.x() : aabb_maxx;
		aabb_maxy = p.y() > aabb_maxy ? p.y() : aabb_maxy;
	}

	Eigen::Vector2f ptmin{ aabb_minx, aabb_miny };
	Eigen::Vector2f ptMax{ aabb_maxx, aabb_maxy };
	std::array<Eigen::Vector2f, 2> res{ ptmin, ptMax };
	return res;
}