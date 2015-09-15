#include <cstdlib>
#include "png.h"

// sets up the output image
PNG * setupOutput(int w, int h);

// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity);
using namespace std;
int main()
{
	// Load in.png
	PNG* original = new PNG();
	original->readFromFile("in.png");

	int width  = original->width();
	int height = original->height();

	// Create out.png
	PNG * output = setupOutput(width,height); 

	// Loud our favorite color to color the outline
	RGBAPixel * myPixel = myFavoriteColor(192);

	// Go over the whole image, and if a pixel differs from that to its upper
	// left, color it my favorite color in the output
	RGBAPixel* prev;
	RGBAPixel* curr;
	RGBAPixel* currOutPixel;
	for(int y = 1; y < height; y++)
	{
		for(int x = 1; x < width; x++)
		{
			// Calculate the pixel difference

			prev = (*original)(x-1, y-1);
			curr = (*original)(x  , y  );
			int diff = abs(curr->red   - prev->red  ) +
					   abs(curr->green - prev->green) +
					   abs(curr->blue  - prev->blue );
			
			// If the pixel is an edge pixel,
			// color the output pixel with my favorite color
			currOutPixel = (*output)(x,y);
			if (diff > 100)
				*currOutPixel = *myPixel;
	
		}
	}
	
	// Save the output file
	output->writeToFile("out.png");

	// Clean up memory
	delete myPixel;
	delete output;
	delete original;
	return 0;
}


// sets up the output image
PNG * setupOutput(int w, int h)
{
	PNG * image = new PNG(w, h);
	return image;
}


// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity)
{
	RGBAPixel *color = new RGBAPixel(0, intensity/2, intensity);
	return color;
}
