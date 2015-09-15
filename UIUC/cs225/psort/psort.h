/**
 * @file psort.h
 */

#ifndef _PSORT_H_
#define _PSORT_H_

#include <iostream>
#include <vector>
#include <omp.h>

using std::vector;

namespace ParallelSort
{
    /**
     * Public wrapper for the parallel sort implementation.
     * @param array The structure to sort
     */
    template <class T>
    void psort(vector<T>* array);

	template <class T>
	void swap(T& a, T& b);
	
	template <class T>
	int* partition(T* array, int lo, int hi);

	template <class T>
	void reverse(T* array, int size);

	template <class T>
	int inOrder(T* array, int size);

	template <class T>
	void quicksort(T* array, int lo, int hi);

	template <class T>
	void pquicksort(T* array, int lo, int hi);

	template <class T>
	void partition(T* array, int lo, int hi, int & newLo, int & newHi);

	template <class T>
	void insertion_sort(T* array, int start, int end);



}

#include "psort.cpp"
#endif
