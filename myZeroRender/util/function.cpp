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
