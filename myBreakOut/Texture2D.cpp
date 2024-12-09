#include "Texture2D.h"



Texture2D::Texture2D() :
	width_(0),
	height_(0),
	interal_format_(GL_RGB),
	image_format_(GL_RGB),
	wrap_s_(GL_REPEAT),
	warp_t_(GL_REPEAT),
	filter_min_(GL_LINEAR),
	filter_max_(GL_LINEAR)
{
	glGenTextures(1, &id_);
}


void Texture2D::generate(unsigned int width, unsigned int height, unsigned char *data)
{
	width_ = width;
	height_ = height;

	bind();

	glTexImage2D(GL_TEXTURE_2D, 0, interal_format_, width_, height_, 0, image_format_, GL_UNSIGNED_BYTE,
		data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, warp_t_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max_);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, id_);
}
