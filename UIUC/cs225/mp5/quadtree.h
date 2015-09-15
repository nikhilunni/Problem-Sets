// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
	Quadtree();
	Quadtree(const PNG & source, int resolution);
	Quadtree(Quadtree const & other);
	~Quadtree();
	void buildTree(PNG const & source, int resolution);
	RGBAPixel getPixel(int x, int y) const;
	PNG decompress() const;
	Quadtree const & operator=(Quadtree const & other);
	void clockwiseRotate();
	void prune(int tolerance) const;
	int pruneSize(int tolerance) const;
	int idealPrune(int numLeaves) const;
	
	
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
		int x,y;
	};	
	void _copy(Quadtree const & other);
	void _copyTree(QuadtreeNode * subroot, QuadtreeNode * otherroot);
	void _clearTree(QuadtreeNode * subroot);
	void _clear();
	QuadtreeNode * _buildTree(int xOffset, int yOffset, PNG const & source, int resolution);
	RGBAPixel _getPixel(QuadtreeNode * subroot, int x, int y, int res, int xOffset, int yOffset) const;
	void _decompress(QuadtreeNode * subroot, PNG & image) const;
	QuadtreeNode* root;    // pointer to root of quadtree
	int resolution;
	
	
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
