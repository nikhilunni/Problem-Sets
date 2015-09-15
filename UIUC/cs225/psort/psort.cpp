
template <class T>
void ParallelSort::swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template <class T>
void ParallelSort::partition(T* array, int lo, int hi, int & newLo, int & newHi)
{
 	newLo=lo; 
	newHi=hi;
	int mid = lo + (hi-lo)/2;
	
	if(array[lo] > array[mid])
		swap(array[lo],array[mid]);
	if(array[lo] > array[hi])
		swap(array[lo],array[hi]);
	if(array[mid] > array[hi])
		swap(array[mid],array[hi]);
	T pivot = array[mid];

	while (newLo <= newHi)
	{
		while(array[newLo] < pivot)
			newLo++;
		while(array[newHi]> pivot)
			newHi--;
		if(newLo <= newHi)
		{
			swap(array[newLo],array[newHi]);
			newLo++; newHi--;
		}		
	}
}


template <class T>
void ParallelSort::quicksort(T* array, int lo, int hi)
{
	int newLo, newHi;
	partition(array, lo, hi, newLo, newHi);
	if(lo <= newHi)
		quicksort(array, lo, newHi);
	if(newLo < hi)
		quicksort(array, newLo, hi);
}

template <class T>
void ParallelSort::pquicksort(T* array, int lo, int hi)
{
	int newLo, newHi;
	partition(array, lo, hi, newLo, newHi);
	#pragma omp task
	if(lo <= newHi)
	{
		if(newHi - lo < 4000)
			quicksort(array, lo, newHi);
		else
			pquicksort(array, lo, newHi);
	}

	#pragma omp task
	if(newLo < hi)
	{
		if(hi - newLo < 4000)
			quicksort(array, newLo, hi);
		else
			pquicksort(array, newLo, hi);
	}
}

template <class T>
void ParallelSort::reverse(T* array, int size)
{
	#pragma omp parallel for
	for(int i = 0; i < size/2; i++)
	{
		swap(array[i],array[size-1-i]);
	}
}

template <class T>
int ParallelSort::inOrder(T* array, int size)
{
	bool forward = true, backward = true;
	#pragma omp parallel for
	for(int i = 1; i < size; i++)
	{
		if(array[i] < array[i-1])
			forward = false;
		if(array[size-i-1] < array[size-i])
			backward = false;
	}
	if(forward)
		return 1;
	else if(backward)
		return 2;
	else
		return -1;
}

template <class T>
void ParallelSort::psort(vector<T> * vec)
{
	T* array = vec->data();	
	int size = vec->size();

//	int order = inOrder(array, size);
//	if(order == 1)
//		return;
//	else if(order == 2)
//		reverse(array, size);
//	else
	{
		if(size <= 15)
			insertion_sort(array, 0, size-1);
		else if(size <= 4000)
			quicksort(array, 0, size-1);
		else
		{
			#pragma omp parallel default(shared) num_threads(16)
			{
				#pragma omp single nowait
				pquicksort(array,0,size-1);
			}
		}
	}
}


template <class T>
void ParallelSort::insertion_sort(T* array, int start, int end)
{
	for(int i = start; i <= end; i++)
	{
		for(int j = start; j <= end; j++)
		{
			if(array[j] > array[i])
			{
				int k;	
				T temp = array[j];
				array[j] = array[i];
				for(k = i; k > j; k--)
					array[k] = array[k-1];
				array[k+1] = temp;
			}
		}
	}
}
