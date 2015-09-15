#include "rgbapixel.h"

RGBAPixel::RGBAPixel(unsigned char r,unsigned char g,unsigned char b) {
	red = r; green = g; blue = b; alpha = 255;
};
RGBAPixel::RGBAPixel() {
	red = 0; green = 0; blue = 255; alpha = 255;
}
	
