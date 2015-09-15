// Original file by Lawrence Angrave 2015
// Changes to this file will be ignored when your project is graded
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "mpsortutil.h"

// Program name
char* progname;
// number of threads in the thread pool
// If this is unset then the baseline version (i.e. the implementation we provide) is used
int nthreads= -1;
// verbose flag
int verbose;
// the input file, which contains a number each line
char*infile_name;
// the output file, to which your output is directed
char*outfile_name;
// Nonzero if using special streaming version
int streaming_mode;

void usage() {
  printf("Usage %s <options> inputfile [outputfile]\n",progname);
  puts("  -N  number of threads that can be created including original thread (1-9)");
  puts("  -s  fast streaming merge sort");
  puts("  -v  verbose output (always printed to standard out)");
  puts("  -h  print this information to stdout");
  exit(1);
}


void parse_args(int argc, char ** argv) {
  progname = argv[0];
  
  int i;
  for(i=1;i < argc;i++) {
    if(*argv[i]!='-') {
      if(outfile_name) usage();
      else if(infile_name) outfile_name=argv[i];
      else infile_name=argv[i];
    }
    else {
      char*p = argv[i] +1;
      while(*p) {
        char c = *p++;
        if(c >='1' && c <='9') nthreads = c -'0';
        else if(c =='v') verbose = 1;
        else if(c == 's') streaming_mode = 1;
        else usage();
      }
    }
  }
  if(!infile_name) usage();

}

int main(int argc, char**argv) {

  parse_args(argc, argv);
  
  if(streaming_mode) {
    streaming_sort();
    return 0;
  }

  int *data;
  int nitems = read_file(infile_name, &data);
  
  if(nthreads == -1)
    baseline_nonthreaded_mergesort(data,nitems); 
  else
    my_threaded_mergesort(data,nitems);
    
  print_result(outfile_name, data, nitems);

  return 0;

}

