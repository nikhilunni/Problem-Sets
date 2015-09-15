#include "rgbapixel.h"
#include "png.h"

int main() {
	PNG in;
	in.readFromFile("in.png");
	
	PNG out(in.width(), in.height());
	for(size_t x = 0; x < in.width(); x++) {
		for(size_t y = 0; y < in.height(); y++) {
			RGBAPixel* outPixel = out(in.width()-1-x,in.height()-1-y);
			RGBAPixel* inPixel = in(x,y);
			outPixel->red = inPixel->red;
			outPixel->blue = inPixel->blue;
			outPixel->green = inPixel->green;
			outPixel->alpha = inPixel->alpha;
		}


	}
	out.writeToFile("out.png");	
}
