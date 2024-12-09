#pragma once
#include <glad/glad.h>

class Texture2D
{
public:
	Texture2D();

	void generate(unsigned int width, unsigned int height, unsigned char *data);

	void bind() const;

	unsigned int id_;

	unsigned int width_;

	unsigned int height_;

	unsigned int interal_format_;

	unsigned int image_format_;

	unsigned int wrap_s_;

	unsigned int warp_t_;

	unsigned int filter_min_;  //过滤类型

	unsigned int filter_max_;	//过滤类型
};

