#pragma once
#include "mdl/geometry.h"

class Camera
{
public:
	Camera(Vec3f position, Vec3f target, float aspect);
	~Camera();

	void SetTransform(Vec3f position, Vec3f target);

	void UpdateTransform();

private:
	Vec3f pos;
	Vec3f target;	
	float aspect;
};

