#include <xmmintrin.h>
#include "mv-mult.h"

// Matrix-Vector multiplication
// mat is a SIZE by SIZE matrix, that is arranged in row-column, format,
// That is, you first select a particular row, and then a particular column.
// Each row is laid out as a one-dimensional, array, so if you wanted
// to select a particular row, you would use mat[row].  You can
// also select smaller intervals, by using &mat[row][col].
// The vector is also laid out as a one-dimensional arrow, similar to a row.
// M-V multiplication proceeds by taking the dot product of a matrix row
// with the vector, and doing this for each row in the matrix

// vectorize the below code using SIMD intrinsics
float *
mv_mult_vector(float mat[SIZE][SIZE], float vec[SIZE]) {
  static float ret[SIZE];
  __m128 acc[SIZE], MAT, VEC;

  for (int i = 0 ; i < SIZE ; i++) {
    int j = 0;
    acc[i] = _mm_set1_ps(0.0);
    for (j = 0 ; j < SIZE-3 ; j+=4) {
      MAT = _mm_loadu_ps(&mat[i][j]);
      VEC = _mm_loadu_ps(&vec[j]);
      acc[i] = _mm_add_ps(acc[i],_mm_mul_ps(MAT,VEC));
    }
    float temp[4];
    _mm_storeu_ps(temp, acc[i]);
    ret[i] = temp[0]+temp[1]+temp[2]+temp[3];
    for(; j < SIZE; j++)
      ret[i] += mat[i][j]*vec[j];
  }

  return ret;
}
