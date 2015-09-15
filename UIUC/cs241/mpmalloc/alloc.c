/* This is the file you should write your code for the CS241 malloc mp challenge
  There is malloc,realloc,calloc and free waiting for you.
  
  A reminder the University of Illinois and the department of computer science has 
  a policy about what is allowed regarding collaboration and publishing of solutions.
  
  i.e. Your score should be based on your own work and you may not publish your solutions
  or leave them in 'plain view' -

  https://cs.illinois.edu/current-students/undergraduates/policies-and-procedures-0/honor-code-and-academic-integrity
  
  For this MP, the code you submit must be your own work i.e. entirely your own work product.
  
  Getting started: See the instructions on the CS241 website

  If you have questions please use Piazza
  If your code crashes it might be a great time to learn to use a debugger!
  
  The given portions of this code are copyright the original authors (UIUC CS241 staff).
  Recent additions are copyright Lawrence Angrave 2015
  You own the copyright to your own code - however please see the above warning before choosing to publishing it.
  
  This is is a challenging assignment - and considered "Rite of passage" for any system programmer
  
  To score points you need to add your name and netid to the following line copyright line.
  
  Student code: Copyright (C) Nikhil Unni (nunni2) 2015
  
  i.e. replace "[Full name]" and "[netid]" with your full name and netid.
  */
  


/** @file alloc.c */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


/**
 * Allocate space for array in memory
 * 
 * Allocates a block of memory for an array of num elements, each of them size
 * bytes long, and initializes all its bits to zero. The effective result is
 * the allocation of an zero-initialized memory block of (num * size) bytes.
 * 
 * @param num
 *    Number of elements to be allocated.
 * @param size
 *    Size of elements.
 *
 * @return
 *    A pointer to the memory block allocated by the function.
 *
 *    The type of this pointer is always void*, which can be cast to the
 *    desired type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory, a
 *    NULL pointer is returned.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/calloc/
 */
void *calloc(size_t num, size_t size)
{
  void* out = malloc(num*size);
  size_t i;
  for(i = 0; i < num*size; i++)
    *((int*)(out+i)) = 0;
  return out;
}


/**
 * Allocate memory block
 *
 * Allocates a block of size bytes of memory, returning a pointer to the
 * beginning of the block.  The content of the newly allocated block of
 * memory is not initialized, remaining with indeterminate values.
 *
 * @param size
 *    Size of the memory block, in bytes.
 *
 * @return
 *    On success, a pointer to the memory block allocated by the function.
 *
 *    The type of this pointer is always void*, which can be cast to the
 *    desired type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory,
 *    a null pointer is returned.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/malloc/
 */

int totalSize = 0;
typedef struct chunk {
  size_t size;
  struct chunk* next;
  struct chunk* prev;
} chunk;

chunk* head = NULL;


void *malloc(size_t size) //Replace sizeof with constant!
{
  if(size == 1)
    return sbrk(size);
  
  if(head == NULL) {
    chunk* firstChunk = sbrk(sizeof(chunk) + size);
    if(firstChunk == NULL) {
      return NULL;
    }
    firstChunk->size = size;
    return ( (void*)(firstChunk) + sizeof(chunk) );
  }

  chunk* iter = head;
  chunk* min = NULL;

  while(iter != NULL && min == NULL) {
    if(iter->size >= size) {
      min = iter;
    }
    iter = iter->next;
  }

  if(min == NULL) {
    chunk* newChunk = sbrk(sizeof(chunk) + size);
    newChunk->size = size;
    newChunk->next = NULL;
    newChunk->prev = NULL;
    return ( (void*)(newChunk) + sizeof(chunk) );
  }
  else {    
    //Take me outta the game, dawg

    /**
    if(min->size - size - sizeof(chunk) > 1024) { //Cut
      chunk* newChunk = ((void*)(min))+sizeof(chunk)+size;
      newChunk->size = min->size - size - sizeof(chunk);
      newChunk->prev = NULL; newChunk->next = head;
      if(head)
	head->prev = newChunk;
      head = newChunk;
      min->size = size;
    }
    **/

    if(min->prev)
      min->prev->next = min->next;
    else
      head = min->next;
    
    if(min->next)
      min->next->prev = min->prev;
    return ( (void*)(min) + sizeof(chunk) );
  }
}


/**
 * Deallocate space in memory
 * 
 * A block of memory previously allocated using a call to malloc(),
 * calloc() or realloc() is deallocated, making it available again for
 * further allocations.
 *
 * Notice that this function leaves the value of ptr unchanged, hence
 * it still points to the same (now invalid) location, and not to the
 * null pointer.
 *
 * @param ptr
 *    Pointer to a memory block previously allocated with malloc(),
 *    calloc() or realloc() to be deallocated.  If a null pointer is
 *    passed as argument, no action occurs.
 */
void free(void *ptr)
{
  if(ptr == NULL)
    return;

  chunk* cur = (chunk*)(ptr-sizeof(chunk));
  cur->next = head;
  cur->prev = NULL;
  if(head)
    head->prev = cur;
  head = cur;
}


/**
 * Reallocate memory block
 *
 * The size of the memory block pointed to by the ptr parameter is changed
 * to the size bytes, expanding or reducing the amount of memory available
 * in the block.
 *
 * The function may move the memory block to a new location, in which case
 * the new location is returned. The content of the memory block is preserved
 * up to the lesser of the new and old sizes, even if the block is moved. If
 * the new size is larger, the value of the newly allocated portion is
 * indeterminate.
 *
 * In case that ptr is NULL, the function behaves exactly as malloc, assigning
 * a new block of size bytes and returning a pointer to the beginning of it.
 *
 * In case that the size is 0, the memory previously allocated in ptr is
 * deallocated as if a call to free was made, and a NULL pointer is returned.
 *
 * @param ptr
 *    Pointer to a memory block previously allocated with malloc(), calloc()
 *    or realloc() to be reallocated.
 *
 *    If this is NULL, a new block is allocated and a pointer to it is
 *    returned by the function.
 *
 * @param size
 *    New size for the memory block, in bytes.
 *
 *    If it is 0 and ptr points to an existing block of memory, the memory
 *    block pointed by ptr is deallocated and a NULL pointer is returned.
 *
 * @return
 *    A pointer to the reallocated memory block, which may be either the
 *    same as the ptr argument or a new location.
 *
 *    The type of this pointer is void*, which can be cast to the desired
 *    type of data pointer in order to be dereferenceable.
 *    
 *    If the function failed to allocate the requested block of memory,
 *    a NULL pointer is returned, and the memory block pointed to by
 *    argument ptr is left unchanged.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/realloc/
 */
void *realloc(void *ptr, size_t size)
{
  void* out = malloc(size);
  chunk* cur = (chunk*)(ptr-sizeof(chunk));
  size_t oldSize = cur->size;
  memcpy(out, ptr, oldSize < size ? oldSize : size);
  free(ptr);
  return out;
}
