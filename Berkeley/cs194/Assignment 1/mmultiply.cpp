#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>
#include "counters.h"

void opt_simd_sgemm(float *Y, float *A, float *B, int n);
void opt_scalar1_sgemm(float *Y, float *A, float *B, int n);
void opt_scalar0_sgemm(float *Y, float *A, float *B, int n);
void naive_sgemm(float *Y, float *A, float *B, int n);

int main(int argc, char *argv[])
{
  struct timeval start_tv, end_tv;
  hwCounter_t c;
  c.init = false;
  initInsns(c);
  initTicks(c);


  int n = (1<<10);
  float* A = new float[n*n];
  float* B = new float[n*n];
  float* Y = new float[n*n];
 
  long long count_start, count_end;
  long long ticks_start, ticks_end;

  gettimeofday(&start_tv, 0);
  ticks_start = getTicks(c);   
  count_start = getInsns(c);
  opt_scalar1_sgemm(Y, A, B, n);
  count_end = getInsns(c);
  ticks_end = getTicks(c);
  gettimeofday(&end_tv, 0);
  
  long double flops = (count_end-count_start) / (end_tv.tv_sec + 1e-6*end_tv.tv_usec - start_tv.tv_sec - 1e-6*start_tv.tv_usec);
  long double ipc = (long double)((count_end-count_start) / (ticks_end-ticks_start));

  printf("Flops : %Lf\n", flops);
  printf("IPCs : %Lf\n", ipc);
  printf("Delta Count : %lld\n", count_end-count_start);
  printf("Delta Ticks : %lld\n", ticks_end-ticks_start);
  delete [] A;
  delete [] B;
  delete [] Y;
}
