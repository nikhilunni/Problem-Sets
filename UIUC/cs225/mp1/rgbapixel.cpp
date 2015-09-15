#include "rgbapixel.h"

RGBAPixel::RGBAPixel(unsigned char r,unsigned char g,unsigned char b) {
	red = r; green = g; blue = b; alpha = 255;
};
RGBAPixel::RGBAPixel() {
	red = 255; green = 255; blue = 255; alpha = 255;
}
	
