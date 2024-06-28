#include <iostream>

#include "device/Color.h"

using namespace std;
class X {
	int a;
	int b;
	union {
		int c;
		char d[4];
		int e;
	};
public:
	int getb() { return b; }
	int getc() { return c; }
	int gete() { return e; }
};


	


int main()
{
	
	Color c;

	std::cout << c << std::endl;
	

	std::cout << c << std::endl;
	getchar();

	return 0;
}