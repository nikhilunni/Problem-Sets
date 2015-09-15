#include <xmmintrin.h>
#include "mandelbrot.h"

// mandelbrot() takes a set of SIZE (x,y) coordinates - these are actually
// complex numbers (x + yi), but we can also view them as points on a plane.
// It then runs 200 iterations of f, using the (x,y) point, and checks
// the magnitude of the result.  If the magnitude is over 2.0, it assumes
// that the function will diverge to infinity.

// vectorize the below code using SIMD intrinsics
int *
mandelbrot_vector(float x[SIZE], float y[SIZE]) {
  static int ret[SIZE];
  __m128 x1, y1, x2, y2;

  __m128 TWO = _mm_set1_ps(2.0);
  __m128 M_MAG_SSE = _mm_set1_ps(M_MAG);
  for (int i = 0 ; i < SIZE ; i += 4) {
    x1 = _mm_set1_ps(0.0);
    y1 = _mm_set1_ps(0.0);

    // Run M_ITER iterations
    for (int j = 0 ; j < M_ITER ; j ++) {
		  
      // Calculate the real part of (x1 + y1 * i)^2 + (x + y * i)
      //      x2 = (x1 * x1) - (y1 * y1) + x[i];
      x2 = _mm_add_ps(
		      _mm_sub_ps(_mm_mul_ps(x1,x1), _mm_mul_ps(y1,y1)),
		      _mm_loadu_ps(&x[i]));

      // Calculate the imaginary part of (x1 + y1 * i)^2 + (x + y * i)
      //      y2 = 2 * (x1 * y1) + y[i];
      y2 = _mm_add_ps(_mm_mul_ps(_mm_mul_ps(x1,y1), TWO),
		      _mm_loadu_ps(&y[i]));


      // Use the new complex number as input for the next iteration
      x1 = x2;
      y1 = y2;
    }

    // caculate the magnitude of the result
    // We could take the square root, but instead we just
    // compare squares
    __m128 result =  _mm_cmplt_ps(
				  _mm_add_ps( _mm_mul_ps(x2,x2), _mm_mul_ps(y2,y2)),
				  _mm_mul_ps(M_MAG_SSE,M_MAG_SSE));
    float out[4];
    _mm_storeu_ps(out, result);
    ret[i]=out[0];
    ret[i+1]=out[1];
    ret[i+2]=out[2];
    ret[i+3]=out[3];
    //    ret[i] = ((x2 * x2) + (y2 * y2)) < (M_MAG * M_MAG);
  }

  return ret;
}
