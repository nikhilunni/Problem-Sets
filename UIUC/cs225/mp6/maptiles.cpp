/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;
MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
	MosaicCanvas* out = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
	vector< Point<3> > tiles;
	map<Point<3>, TileImage> map;
	for(int i = 0; i < theTiles.size(); i++)
	{
		RGBAPixel tileCol = theTiles[i].getAverageColor();
		Point<3> pointCol(tileCol.red,tileCol.green,tileCol.blue);
		map[pointCol] = theTiles[i];
		tiles.push_back(pointCol);
	}
	KDTree<3> tree(tiles);
	for(int i = 0; i < theSource.getRows(); i++)
	{
		for(int j = 0; j < theSource.getColumns(); j++)
		{
			RGBAPixel localPixel = theSource.getRegionColor(i,j);
			Point<3> localPoint(localPixel.red,localPixel.green,localPixel.blue);
			out->setTile(i,j,map[tree.findNearestNeighbor(localPoint)]);
		}
	}
	return out;
}
