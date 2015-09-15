/* Original version by Lawrence Angrave 2015 for CS 241 @ Illinois edu */

#include <stdio.h>
#include <jni.h>
#include <string.h>
#include <pthread.h>
#include <math.h> /*cos */
#include <float.h> /*FLT_MAX */

/* In my testing, 2 threads seems to be optimal for this particular benchmark problem.
I was able to achieve a speed up of ~9 times faster than Java
 and ~5 times faster with 3 threads but with much more variability
 */

// If you start with 1 thread, then this code does not call pthread_create
// It should calculate the entire result just on the calling thread
#define NTHREADS (1)


JNIEXPORT jstring JNICALL Java_edu_illinios_cs241_javavsandroidthreads_MultithreadedNativeBenchmark_hello
          (JNIEnv *env, jclass clas)
{
    char* mesg = malloc(1024);

    snprintf(mesg,1024,"Built %s %s\nUsing %d threads\n",__DATE__,__TIME__ , NTHREADS);
    mesg[1023] = 0;

    return (*env)->NewStringUTF(env,mesg);
}

/* We pass each thread one of these structs */
struct task_t {
  pthread_t tid; /* The thread's identify for this bit of work */
  int num; /* Process array[0] upto array[num-1] */
  float* array; /* May not point to the beginning of the array */
  float result;
};


/* Function that each thread will run */
void* process_array(void* arg) {
  // TODO: extract num and array from the argument
  // First, cast the pointer to a pointer to a struct
  struct task_t* taskptr = _______

  const int num = _____
  const float* array = _______

  float result = FLT_MAX;

  for(int i=0 ; i <num; i ++) {
     float val = (float) cos(array[i]);
     // Assume val is used e.g. written into an array somwehere
     // Otherwise we can optimize as we know the range and could calculate cosine after the loop

     if(val < result)
         result = val;
  }

   _____ //put result back into the struct

  return NULL;
}



JNIEXPORT jfloat JNICALL Java_edu_illinios_cs241_javavsandroidthreads_MultithreadedNativeBenchmark_calculate
  (JNIEnv * env, jclass clas, jfloatArray javaArray) {

        float* values = (float *) (*env)->GetFloatArrayElements(env,javaArray, 0);
        int len = (*env)->GetArrayLength(env,javaArray);
        if(len <1 || !values) return -1;

        // Make a local array. That's OK because the lifetime of this array 
        // is longer than the threads
        struct task_t tasks[NTHREADS];

        // Divide up the work. The last thread may get a bit more work if
        // len is not divisible by NTHREADS
        int i = 0;
        int num_per_thread = len / NTHREADS;
        int num_per_last_thread = len - (NTHREADS-1) * num_per_thread;

        for(i =0; i < NTHREADS; i++) {
          // Hurray for pointer arithmetic
          tasks[i].array = values + num_per_thread * i ;

          tasks[i].num = (i <  NTHREADS -1 ) ? num_per_thread : num_per_last_thread  ;
          // Don't start a new thread for the first task, as we will run that work on this calling thread
          if(i>0) {
            pthread_create(&tasks[i].tid, NULL, process_array, &tasks[i]);
          }
          return NULL;
        }

        ____ // complete task[0] work on this thread
        
        // Why do we sandwhich the above call BETWEEN pthread_create and pthread join for the other threads!?
        float result= tasks[0].result;
        
        // Wait for other threads to finish
        for(i =1; i < NTHREADS; i++) { 
           ______ // Hint Not pthread_exit! Hint: We don't need the return NULL value
          float partial = tasks[i].result;
          if(result > partial ) result =  partial ;
        }
        
        // We are finished so don't need the heap memory of the Java array to be fixed anymore
        (*env)->ReleaseFloatArrayElements(env,javaArray,values,0);
        return  result;

  }
// Once you have this working try with #define NTHREADS (2)