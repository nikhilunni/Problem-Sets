// Original file by Lawrence Angrave 2015
// Changes to this file will be ignored when your project is graded

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mpsortutil.h"

extern const char * infile_name;
extern const char * outfile_name;

FILE* open_outfile(const char * outfile) {
  FILE* file = stdout;
  if(outfile) file = fopen(outfile,"w");
  if( ! file) {
    fprintf(stderr,"Could not write to %s\n",outfile);
    exit(1);
  }
  return file;
}

FILE * open_infile(const char * infile_name) {
  FILE * file = fopen(infile_name,"r");
  if( ! file || ferror(file)) {
    
    fprintf(stderr,"Could not open file %s\n" , infile_name);
    exit(1);
  }
  return file;
}

void print_result(const char * outfile_name, int * data, int nitems) {
  
  FILE* file = open_outfile(outfile_name);
  
  for(int i=0;i < nitems;i++) 
     fprintf(file,"%d\n", data[i]);
  
  if(file != stdout) 
    fclose(file);
}

int read_file(const char * infile_name, int ** data) {
  int capacity = 1024;
  int nitems = 0;
  *data = malloc(capacity*sizeof(int));
  
  FILE * file = open_infile(infile_name);
  int value;
  while(!feof(file) && !ferror(file)) {
    
    int success = fscanf(file,"%d",&value);
    if(success != 1) break;
    if(nitems == capacity) { 
      capacity*=2; 
      *data = realloc(*data, sizeof(int) * capacity);
    }
    (*data)[nitems++] = value;
  }
  fclose(file);

  return nitems;
}

void streaming_sort() {
  int capacity = 256;
  int nitems = 0,i=0;
  int buffer[capacity];
  

  stream_init(); // GET READY
  
  FILE*file = open_infile(infile_name);

  while(!feof(file) && !ferror(file)) {
    
    int success = fscanf(file,"%d",buffer + i);
    
    if(success != 1) 
      break;
    nitems++; i++;
    
    if(i  == capacity) { 
      stream_data( buffer, i); // SOME DATA FOR YOU
      i = 0;
    } 
  }
  if(i) 
    stream_data( buffer, i); // HAVE A BIT MORE DATA

  stream_end(); // DONE
  
  fclose(file);
    
}

/** Standard merge code. Assumes [start,mid) are sorted and [mid,end) are also sorted.
  Requires (end-start)*sizeof(int) temporary space */

void simple_merge(int * data , int * scratch, int start,int mid, int end) {  
  // mid,end are exclusive when used as end-points
  assert(data && scratch && (start >=0) && (start <= mid) && (mid <= end));
  int i = start;
  int j = mid;
  int k = 0;
  while(i <mid && j < end) {
    scratch[k++] = data[i] < data[j] ? data[i++] : data[j++];
  }
  while(i <mid)
    scratch[k++] = data[i++];
  while(j <end)
    scratch[k++] = data[j++];
  
  // Copy back 
  for(i=0; i<k ; i++)
    data[start + i] = scratch[i];
  
}


int count_unique(int* data, int start, int end_exclusive) {//UNTESTED
  // Assumes data is sorted
  if(start >= end_exclusive) return 0;
  int last_value = data[start++]; // so is different from very first value
  int result =0; // unique count
  int dup = 0; // is this current value a duplicate
  while(start < end_exclusive ) {
    int value = data[start++];
    if(value == last_value ) { 
      dup = 1; 
      continue; 
    }
    last_value = value;
    if(dup) dup = 0; 
    else result ++;
  }
  
  return dup ? result : result + 1;;
}

void print_stat(int* data, int start, int end_exclusive) {//UNTESTED
  int unique_values= count_unique(data, start, end_exclusive);
  printf("[%d,%d,%d]\n",start,end_exclusive-1, unique_values);
}
