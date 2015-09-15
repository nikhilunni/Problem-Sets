/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 * 
 * @author Chase Geigle
 * @date Fall 2012
 */
#include "filler.h"
#include <iostream>
using namespace std;
animation filler::dfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
		animation anim();
	solidColorPicker solid(fillColor);
	return filler::fill<Stack>(img,x,y,solid,tolerance,frameFreq);		
}

animation filler::dfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
	gridColorPicker grid(gridColor,gridSpacing);
	return filler::fill<Stack>(img,x,y,grid,tolerance,frameFreq);	
}

animation filler::dfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
	gradientColorPicker grad(fadeColor1, fadeColor2, radius, x, y);
	return filler::fill<Stack>(img,x,y,grad,tolerance,frameFreq);
}

animation filler::dfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
	return filler::fill<Stack>(img,x,y,fillColor, tolerance, frameFreq);
}

animation filler::bfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
	solidColorPicker solid(fillColor);
	return filler::fill<Queue>(img,x,y,solid,tolerance,frameFreq); 
}

animation filler::bfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
	gridColorPicker grid(gridColor, gridSpacing);
	return filler::fill<Queue>(img,x,y,grid,tolerance,frameFreq);
}

animation filler::bfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
	gradientColorPicker grad(fadeColor1,fadeColor2,radius,x,y);
	return filler::fill<Queue>(img,x,y,grad,tolerance,frameFreq);
}

animation filler::bfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
	return filler::fill<Queue>(img,x,y,fillColor,tolerance,frameFreq); 
}

template <template <class T> class OrderingStructure>
animation filler::fill( PNG & img, int x, int y,
        colorPicker & fillColor, int tolerance, int frameFreq ) {
	animation anim;
	bool processed[img.width()][img.height()];
	for(int i = 0; i < img.width(); i++)
	{
		for(int j = 0; j < img.height(); j++)
		{
			processed[i][j] = false;
		}
	}

	int pixelsProcessed = 0;
	OrderingStructure<int> xCoord, yCoord;
	xCoord.add(x); yCoord.add(y);
	RGBAPixel origPixel = *img(x,y);
	while(!xCoord.isEmpty()) 
	{
		int xCurr = xCoord.remove();
		int yCurr = yCoord.remove();
		RGBAPixel * currPixel = img(xCurr,yCurr);
		int rgbDistance = pow((int)(origPixel.red) - (int)(currPixel->red),2)
						 +pow((int)(origPixel.blue)- (int)(currPixel->blue),2)
					 	 +pow((int)(origPixel.green) - (int)(currPixel->green),2);
		if(!processed[xCurr][yCurr] && rgbDistance <= tolerance)
		{
		//	cout << xCurr << "," << yCurr << endl;
		//	cout << "dist:" << rgbDistance << endl;
			processed[xCurr][yCurr] = true;
			*(img(xCurr,yCurr)) = fillColor(xCurr,yCurr);
			pixelsProcessed++;
			if(xCurr+1 < img.width())
			{
				xCoord.add(xCurr+1);
				yCoord.add(yCurr);
			}
			if(yCurr+1 < img.height())
			{
				xCoord.add(xCurr);
				yCoord.add(yCurr+1);
			}
			if(xCurr-1 >= 0)
			{
				xCoord.add(xCurr-1);
				yCoord.add(yCurr);
			}
			if(yCurr-1 >= 0)
			{
				xCoord.add(xCurr);
				yCoord.add(yCurr-1);
			}
			if(pixelsProcessed % frameFreq == 0)
				anim.addFrame(img);
		}
	}
	return anim;
}
