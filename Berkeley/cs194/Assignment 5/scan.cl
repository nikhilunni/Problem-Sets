
//Updates each triangle with information from the triangle prior
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

//Actually generates the triange sums
__kernel void scan(__global int *in, 
		   __global int *out, 
		   __global int *bout,
		   __local int *buf,
		   int n)
{
  size_t idx = get_global_id(0);
  size_t tid = get_local_id(0);
  size_t dim = get_local_size(0);
  size_t gid = get_group_id(0);
  
  buf[tid] = in[idx];
  barrier(CLK_LOCAL_MEM_FENCE); //Make sure we copy everything into local memory

  out[idx] = 0; //Zero the array again

  //Do scan for the partial array
  for(int i = 0; i <= tid; i++)
    out[idx] += buf[i];

  if(tid == dim - 1)
    bout[gid] = out[idx]; //Update for the next kernel
}



