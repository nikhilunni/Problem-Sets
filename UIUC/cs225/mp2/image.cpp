#include "image.h"

/**
 *Flips the image about a vertical line through its center by swapping pixels. 
 * */ 
void Image::flipleft() {
	for(size_t y = 0; y < height(); y++)
	{
		for(size_t x = 0; x < width()/2; x++)
		{
			RGBAPixel* curr = (*this)(x,y);
			RGBAPixel* end = (*this)(width()-1-x,y);
			int red = curr->red; int green = curr->green; int blue = curr->blue; int alpha = curr->alpha;
			curr->red=end->red; curr->green=end->green;curr->blue=end->blue;curr->alpha=end->alpha;
			end->red=red;end->green=green;end->blue=blue;end->alpha=alpha;
		}
	}
}
/**
 * Adds to the red, green, and blue parts of each pixel in the image. 
 * */
void Image::adjustbrightness(int r, int g, int b) 
{
	for(size_t y = 0; y < height(); y++)
	{
		for(size_t x = 0; x < width(); x++)
		{
			RGBAPixel* curr = (*this)(x,y);
			unsigned char red = curr->red;
			unsigned char green = curr->green;
			unsigned char blue = curr->blue;

			if((int)red+r > 255)
				red = 255;
			else if((int)red+r < 0)
				red = 0;
			else
				red += r;
			
			if((int)blue+b > 255)
				blue = 255;
			else if((int)blue+b < 0)
				blue = 0;
			else
				blue += b;
			
			if((int)green+g > 255)
				green = 255;
			else if((int)green+g < 0)
				green = 0;
			else
				green += g;

			curr->red = red;
			curr->green = green;
			curr->blue = blue;
		}
	}
}
/**
 *Makes each RGB component of each pixel equal to 255 minus its original value. 
**/
void Image::invertcolors()
{
	for(size_t y = 0; y < height(); y++)
	{
		for(size_t x = 0; x < width(); x++) 
		{
			RGBAPixel* curr = (*this)(x,y); 
			curr->red = 255 - curr->red;
			curr->green = 255 - curr->green;
			curr->blue = 255 - curr->blue;
		}
	}
}
