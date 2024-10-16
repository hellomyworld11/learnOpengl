#include "Color.h"
#include <assert.h>


Color::Color()
{
}


Color::Color(const TGAColor& tagColor)
{
	r_ = tagColor.bgra[2];
	g_ = tagColor.bgra[1];
	b_ = tagColor.bgra[0];
	a_ = tagColor.bgra[3];
}

Color::Color(float r, float g, float b, float a /*= 255*/):
	r_(r),
	g_(g),
	b_(b),
	a_(a)
{

}

Color::Color(Type type)
{
	r_ = 0;
	g_ = 0;
	b_ = 0;
	a_ = 255;
	switch (type)
	{
	case Color::Black:
		r_ = 0;
		g_ = 0;
		b_ = 0;
		a_ = 255;
		break;
	case Color::White:
		r_ = 255;
		g_ = 255;
		b_ = 255;
		a_ = 255;
		break;
	case Color::Red:
		r_ = 255;
		g_ = 0;
		b_ = 0;
		a_ = 255;
		break;
	case Color::Green:
		r_ = 0;
		g_ = 255;
		b_ = 0;
		a_ = 255;
		break;
	case Color::Blue:
		r_ = 0;
		g_ = 0;
		b_ = 255;
		a_ = 255;
		break;
	default:
		break;
	}
}

Color::~Color()
{
}

float& Color::operator[](const size_t i)
{
	//TO DO RECORD
	//https://blog.csdn.net/doubleintfloat/article/details/111088990
	//https://blog.csdn.net/henan_lujun/article/details/8965038
	//TO DO DELETE
	//  #define GET(A , m)  (int)(&((A*)0)->m)
	//	float Color::* offsetg = &Color::g_;
	//	int nOffset = reinterpret_cast<int>(*(void**)(&offsetg));

	//	int valoff = i * nOffset;
	//	float* p = (float*)((this + valoff));
	//	return *p;

	assert(i >= 0 && i <= 3);

	float* p = (float*)(this) + i;
	
	return *p;
}
