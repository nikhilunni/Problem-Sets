// Original file by Lawrence Angrave 2015
// Changes to this file will be ignored when your project is graded

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "mpsortutil.h"


//defined in main.c
extern int nthreads;
extern int verbose;

static int baseline_compare_fn(const void *arg1, const void *arg2) {
  return (*((int*)arg1)) - (*((int*)arg2)); 
}

static void baseline_nothread_mergesort(int * data , int start, int end_exclusive) { 
  int len = end_exclusive - start;
  if(len <= 256) {
    qsort(data +start,len,sizeof(int), baseline_compare_fn);
    if(verbose) print_stat(data,start,end_exclusive);  
    return;
  }
  int midpt = (start + end_exclusive)/2;
  baseline_nothread_mergesort(data, start,midpt);
  baseline_nothread_mergesort(data, midpt,end_exclusive);

  int * scratch =  malloc(sizeof(int) * len);
  simple_merge(data, scratch, start, midpt, end_exclusive);
  free(scratch);
  
  if(verbose) 
    print_stat(data,start, end_exclusive);
}


// Public API: 
void baseline_nonthreaded_mergesort(int* data,int nitems) {
  assert(data);
  assert(nitems>=0);
  baseline_nothread_mergesort(data, 0,nitems);
}