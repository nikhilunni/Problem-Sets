__kernel void matmul(__global float *Y, __global float *A, __global float *B, 
	 int n)
{
    int i = get_global_id(0);
    int j = get_global_id(1);
    if(i < n && j < n) {
        for(int k = 0; k < n; k++) {
	    Y[i*n + j] += A[i*n + k] * B[k*n + j];
	}
    }
}
