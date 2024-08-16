#pragma once
#include "../mdl/geometry.h"
#include "../device/config.h"

int compare(float a, float b);


//world -> screen
Vec3f worldtoscreen(Vec3f v, float w = WINDOW_WIDTH, float h = WINDOW_HEIGHT);

Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P);