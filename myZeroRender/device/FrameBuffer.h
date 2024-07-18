#pragma once
#include <iostream>
#include "Color.h"


class FrameBuffer
{
public:
	explicit FrameBuffer(int width, int height);

	~FrameBuffer();

	void SetDepth(int x, int y, float depth);

	float GetDepth(int x, int y);

	void SetColor(int x, int y, Color color);

	void SetColor(int x, int y, int width, int height, Color color);

	Color GetColor(int x, int y);

	void FrameBufferRelease();

	void FrameBufferClearColor(Color color);

	void FrameBufferClearDepth(float depth);

	int width_ = 0;  //x 列数
	int height_ = 0; //y 行数
	std::vector<std::vector<Color>> color_buffer_;
	std::vector<std::vector<float>>    depth_buffer_;
};

