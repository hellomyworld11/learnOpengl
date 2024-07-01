#include "FrameBuffer.h"
#include <assert.h>


FrameBuffer::FrameBuffer(int width, int height)
{
	assert(width > 0 && height > 0);

	width_ = width;
	height_ = height;

	std::vector<float> depthcolarr(width);
	depth_buffer_.resize(height_, depthcolarr);

	std::vector<Color> colorcolarr(width);
	color_buffer_.resize(height_, colorcolarr);

	Color defaultcolor = { 0, 0, 0, 1 };
	float defaultdepth = 1;

	this->FrameBufferClearColor(defaultcolor);
	this->FrameBufferClearDepth(defaultdepth);
}


FrameBuffer::~FrameBuffer()
{
	color_buffer_.clear();
	depth_buffer_.clear();
}

void FrameBuffer::SetDepth(int x, int y, float depth)
{
	size_t rownum = depth_buffer_.size();

	if ( 0 <= x && x < rownum)
	{
		size_t colnum = depth_buffer_[x].size();

		if ( 0 <= y && y < colnum)
		{
			depth_buffer_[x][y] = depth;
		}
	}
}

float FrameBuffer::GetDepth(int x, int y)
{
	size_t rownum = depth_buffer_.size();

	if (0 <= x && x < rownum)
	{
		size_t colnum = depth_buffer_[x].size();

		if (0 <= y && y < colnum)
		{
			return depth_buffer_[x][y];
		}
	}
	return std::numeric_limits<float>::max();
}

void FrameBuffer::SetColor(int x, int y, Color color)
{
	size_t rownum = color_buffer_.size();

	if (0 <= x && x < rownum)
	{
		size_t colnum = color_buffer_[x].size();

		if (0 <= y && y < colnum)
		{
			color_buffer_[x][y] = color;
		}
	}
}

void FrameBuffer::SetColor(int x, int y, int width, int height, Color color)
{
	for (int row = y; row < y + height; row++)
	{
		for (int col = x; col < x + width; col++)
		{
			SetColor(col, row, color);
		}
	}
}

Color FrameBuffer::GetColor(int x, int y)
{
	size_t rownum = color_buffer_.size();

	if (0 <= x && x < rownum)
	{
		size_t colnum = color_buffer_[x].size();

		if (0 <= y && y < colnum)
		{
			return color_buffer_[x][y];
		}
	}
	return Color();
}

void FrameBuffer::FrameBufferRelease()
{
	depth_buffer_.clear();
	color_buffer_.clear();
	delete this;
}

void FrameBuffer::FrameBufferClearColor(Color color)
{
	for (auto& rowData : color_buffer_)
	{
		for (auto& data : rowData)
		{
			data = color;
		}
	}
}

void FrameBuffer::FrameBufferClearDepth(float depth)
{
	for (auto& rowData : depth_buffer_)
	{
		for (auto& data : rowData)
		{
			data = depth;
		}
	}
}
