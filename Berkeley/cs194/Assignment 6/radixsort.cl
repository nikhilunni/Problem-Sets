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
  

  /*COPIED FROM ASSIGNMENT 5*/  
  out[idx] = 0; //Zero the array again

  //Do scan for the partial array
  for(int i = 0; i <= tid; i++)
    out[idx] += buf[i];

  if(tid == dim - 1)
    bout[gid] = out[idx]; //Update for the next kernel  
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

  if(idx<n) 
  {
    buf[tid] = ((in[idx] >> k) & 0x1);
  } 
  else 
  {
    buf[tid] = 0;
  }
  barrier(CLK_LOCAL_MEM_FENCE); //Wait for all indices in buf to be loaded

  if (idx<n)
  {
    int finalIndex;
    if (buf[tid] == 1)
    {
      finalIndex = zeros[n - 1] + ones[idx] - 1;
    } else {
      finalIndex = zeros[idx] - 1;
    }
    if(finalIndex < n) 
	out[finalIndex] = in[idx];
  }  
}


