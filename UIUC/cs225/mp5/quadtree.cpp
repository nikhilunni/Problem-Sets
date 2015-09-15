// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"

Quadtree::Quadtree()
{
	root = NULL;
	resolution = 0;
}

Quadtree::Quadtree(const PNG & source, int res)
{
	root = NULL;
	buildTree(source, res);
}

Quadtree::Quadtree(Quadtree const & other)
{
	root = NULL;
	_copy(other);
}
Quadtree::~Quadtree()
{
	_clear();
}
Quadtree const & Quadtree::operator=(Quadtree const & other)
{
	if(&other != this)
	{
		_clear();
		_copy(other);
	}
	return *this;
}

void Quadtree::_copy(Quadtree const & other)
{
	resolution = other.resolution;
	PNG otherImage = other.decompress();
	buildTree(otherImage, resolution);
}

/**void Quadtree::_copyTree(QuadtreeNode * subroot, QuadtreeNode * otherroot)
{
	if(subroot->nwChild != NULL) 
	{
		_copyTree(subroot->nwChild,otherroot->nwChild);
		_copyTree(subroot->neChild,otherroot->neChild);
		_copyTree(subroot->swChild,otherroot->swChild);
		_copyTree(subroot->seChild,otherroot->seChild);
	}	
	else
	{
		subroot->element = otherroot->element;
		subroot->x = otherroot->x; subroot->y = otherroot->y;
	}
}**/
void Quadtree::_clear()
{
	_clearTree(root);
	root = NULL;
	resolution = 0;
}
void Quadtree::_clearTree(QuadtreeNode * subroot)
{
	if(subroot != NULL)
	{
		_clearTree(subroot->nwChild);
		_clearTree(subroot->neChild);
		_clearTree(subroot->swChild);
		_clearTree(subroot->seChild);
		delete subroot;
	}
}

void Quadtree::buildTree(PNG const & source, int res)
{
	_clearTree(root);
	root = _buildTree(0,0,source,res);
	resolution = res;
}
Quadtree::QuadtreeNode* Quadtree::_buildTree(int xOffset, int yOffset, PNG const & source, int res)
{
	if(res > 1)
	{
		QuadtreeNode * nw = _buildTree(xOffset, yOffset, source, res/2);
		QuadtreeNode * ne = _buildTree(xOffset + res/2, yOffset, source, res/2);
		QuadtreeNode * sw = _buildTree(xOffset, yOffset + res/2, source, res/2);
		QuadtreeNode * se = _buildTree(xOffset + res/2, yOffset + res/2, source, res/2);
		QuadtreeNode * subroot = new QuadtreeNode();
		subroot->nwChild = nw; subroot->neChild = ne; subroot->swChild = sw; subroot->seChild = se;
		return subroot;
	}
	else
	{
		QuadtreeNode * leaf = new QuadtreeNode();
		leaf->nwChild = NULL; leaf->neChild = NULL; leaf->swChild = NULL; leaf->seChild = NULL;
		leaf->element = *(source(xOffset,yOffset));
		leaf->x = xOffset; leaf->y = yOffset;
		return leaf;
	}
}
RGBAPixel Quadtree::getPixel(int x, int y) const
{
	return _getPixel(root,x,y,resolution,0,0);
}
RGBAPixel Quadtree::_getPixel(QuadtreeNode * subroot, int x, int y, int res, int xOffset, int yOffset) const
{
	if(subroot->nwChild == NULL && subroot->neChild == NULL && subroot->swChild == NULL && subroot->seChild == NULL)
	{
		return subroot->element;
	}
	else
	{
		if(x < xOffset+res/2 && y < yOffset+res/2)
			return _getPixel(subroot->nwChild,x,y,res/2,xOffset,yOffset);
		else if(x >= xOffset+res/2 && y < yOffset+res/2)
			return _getPixel(subroot->neChild,x,y,res/2,xOffset+res/2,yOffset);
		else if(x < xOffset+res/2 && y >= yOffset+res/2)
			return _getPixel(subroot->swChild,x,y,res/2,xOffset,yOffset+res/2);
		else
			return _getPixel(subroot->seChild,x,y,res/2,xOffset+res/2,yOffset+res/2);
	}
}

PNG Quadtree::decompress() const
{
	PNG image(resolution, resolution);
	if(root == NULL)
		return image;
	_decompress(root, image);
	return image;
}
void Quadtree::_decompress(QuadtreeNode * subroot, PNG & image) const
{	
	if(subroot->nwChild == NULL && subroot->neChild == NULL && subroot->swChild == NULL && subroot->seChild == NULL)
	{
		*(image(subroot->x,subroot->y)) = subroot->element;
	}
	else
	{
		_decompress(subroot->nwChild, image);
		_decompress(subroot->neChild, image);
		_decompress(subroot->swChild, image);
		_decompress(subroot->seChild, image);
	}
}

void Quadtree::clockwiseRotate()
{

}

void Quadtree::prune(int tolerance) const
{

}

int Quadtree::pruneSize(int tolerance) const
{
	return 0;
}

int Quadtree::idealPrune(int numLeaves) const
{
	return 0;
}



