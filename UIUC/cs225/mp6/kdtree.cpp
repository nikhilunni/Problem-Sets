/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <algorithm>
#include <iostream>
template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
	if(first[curDim] < second[curDim])
		return true;
	else if(first[curDim] == second[curDim])
		return (first < second);
	else
		return false;
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
	double d1 = 0, d2 = 0;
	for(int i = 0 ; i < Dim; i++)
	{
		d1 += (currentBest[i] - target[i])*(currentBest[i] - target[i]);
		d2 += (potential[i] - target[i])*(potential[i] - target[i]);
	}
	if(d2 < d1)
		return true;
	else if(d2 == d1)
		return (potential < currentBest);
	else
		return false;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
	if(newPoints.size()==0)
		return;
	points = newPoints;
	_construct(0, newPoints.size()-1, 0);
}


template<int Dim>
void KDTree<Dim>::swap(Point<Dim> & a, Point<Dim> & b)
{
	Point<Dim> tmp = a;
	a = b;
	b = tmp;
}

template<int Dim>
void KDTree<Dim>::_construct(int lo, int hi, int dim)
{
	if(lo != hi)
	{
		int median = (lo+hi)/2;
		sort(lo, hi, median, dim);
		if(lo < median)
			_construct(lo,median-1,(dim+1)%Dim);
		if(hi > median)
			_construct(median+1,hi,(dim+1)%Dim);
	}
}


template<int Dim>
void KDTree<Dim>::sort(int lo, int hi, int idx, int dim)
{
	while(lo < hi)
	{
		int med = lo + (hi-lo)/2;
		int pivIdx = partition(lo,hi,idx,dim);
		if(idx == pivIdx)
			return;
		else if(idx < pivIdx)
			hi = pivIdx-1;
		else
			lo = pivIdx+1;
		
	}
}

template<int Dim>
int KDTree<Dim>::partition(int lo, int hi, int idx, int dim)
{
	Point<Dim> pivot = points[idx];
	swap(points[hi],points[idx]);
	int out = lo;
	for(int i = lo; i < hi; i++)
	{
		if(smallerDimVal(points[i],pivot,dim) || points[i] == pivot)
		{
			swap(points[out],points[i]);
			out++;
		}
	}		
	swap(points[hi],points[out]);
	return out;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
	Point<Dim> best = points[0];
	for(int i = 0; i < points.size(); i++)
		best = (shouldReplace(query, best, points[i]) ? points[i] : best);
	return best;
}
