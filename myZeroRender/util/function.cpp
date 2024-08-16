#include "function.h"
#include <limits>

int compare(float a, float b)
{
	float gap = std::fabs(a - b);
	if (gap < std::numeric_limits<float>::epsilon())
	{
		return 0;
	}
	else if (a > b)
	{
		return 1;
	}
	else {
		return -1;
	}
}

Vec3f worldtoscreen(Vec3f v, float w, float h)
{
	return Vec3f((int)((v.x + 1.)*w / 2.), int((v.y + 1.)*h / 2.), v.z);
}

Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P) {
	Vec3f s[2];
	for (int i = 2; i--; ) {
		s[i][0] = C[i] - A[i];
		s[i][1] = B[i] - A[i];
		s[i][2] = A[i] - P[i];
	}
	Vec3f u = s[0] ^ s[1];
	if (std::abs(u[2]) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
		return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
	return Vec3f(-1, 1, 1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}