#pragma once
#include <iostream>
#include "../third/tgaimage.h"



class Color 
{
public:
	Color();
	
	Color(const TGAColor& tagColor);

	Color(float r, float g, float b, float a = 255);

	~Color();

	float& operator[](const size_t i);

	friend std::ostream& operator<<(std::ostream &out, const Color &c)
	{
		out << "rgba: [" << c.r_ << "," << c.g_ << "," << c.b_ << "," << c.a_ << "]";
		return out;
	}


public:

	float r_ = 0;

	float g_ = 0;

	float b_ = 0;

	float a_ = 0;
};

