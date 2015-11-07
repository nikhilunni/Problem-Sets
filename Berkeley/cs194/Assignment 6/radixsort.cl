__kernel void update(__global int *in,
		     __global int *block,
		     int n)
{
  size_t idx = get_global_id(0);
  size_t tid = get_local_id(0);
  size_t dim = get_local_size(0);
  size_t gid = get_group_id(0);

  if(idx < n && gid > 0)
    {
      in[idx] = in[idx] + block[gid-1];
    }
}

__kernel void scan(__global int *in, 
		   __global int *out, 
		   __global int *bout,
		   /* dynamically sized local (private) memory */
		   __local int *buf, 
		   int v,
		   int k,
		   int n)
{
  size_t idx = get_global_id(0);
  size_t tid = get_local_id(0);
  size_t dim = get_local_size(0);
  size_t gid = get_group_id(0);
  int t, r = 0, w = dim;

  if(idx<n)
    {
      t = in[idx];
      /* CS194: v==-1 used to signify 
       * a "normal" additive scan
       * used to update the partial scans */
      t = (v==-1) ? t : (v==((t>>k)&0x1)); 
      buf[tid] = t;
    }
  else
    {
      buf[tid] = 0;
    }
  
  barrier(CLK_LOCAL_MEM_FENCE);

  /* CS194: Your scan code from HW 5 
   * goes here */

  __local int buffer2[128];
  for (int offset = 1; offset < dim; offset *= 2) {
    if (tid >= offset) {
       buffer2[tid - offset] = buf[tid - offset];
    }
    barrier(CLK_LOCAL_MEM_FENCE);
    if (tid >= offset) {
      buf[tid] = buffer2[tid - offset] + buf[tid];
    }
    barrier(CLK_LOCAL_MEM_FENCE);
  }
  
  /* CS194: Store partial scans */
  if(idx < n)
    {
      out[idx] = buf[r+tid];
    }

  /* CS194: one work-item stores the
   * work group's total partial
   * "reduction" */
  if(tid==0)
    {
      bout[gid] = buf[r+dim-1];
    }
}


__kernel void reassemble(__global int *in,
	      	         __global int *out,
			 __global int *zeros,
			 __global int *ones,
			 __local int *buf,
			 int k,
			 int n)
{
  size_t idx = get_global_id(0);
  size_t tid = get_local_id(0);
  int t, index;

  if(idx<n)
  {
    t = in[idx];
    buf[tid] = ((t >> k) & 0x1);
  } else {
    buf[tid] = 0;
  }
  barrier(CLK_LOCAL_MEM_FENCE);

  if (idx<n)
  {
    if (buf[tid] == 1)
    {
      index = zeros[n - 1] + ones[idx] - 1;
    } else {
      index = zeros[idx] - 1;
    }
    if(index < n) 
	out[index] = in[idx];
  }  
}


