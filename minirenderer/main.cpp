#include "tgaimage.h"
#include <iostream>
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);


//Bresenham¡¯s algorithm 
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	for (float t = 0.; t < 1.; t += .1) {
		int x = x0 + (x1 - x0)*t;
		int y = y0 + (y1 - y0)*t;
		std::cout << "t: " << t <<" x: " << x << " y: " << y << std::endl;
		image.set(x, y, color);
	}
}

int main(int argc, char** argv) {
	TGAImage image(40, 40, TGAImage::RGB);
	line(2, 2, 8, 8, image, white);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");

	getchar();
	return 0;
}