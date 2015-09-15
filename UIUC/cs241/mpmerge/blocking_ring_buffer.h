// Original file by Lawrence Angrave 2015
// Changes to this file will be ignored when your project is graded

#define QUEUE_SIZE (64)

typedef struct task_ {
  int start, end;

  struct task_ *parent;
  int completed_child_tasks; 
} task_t;


/**
 * Enqueue a pointer onto the queue. If the queue is full (contains 64 items) then this call will block until a dequeue call completes.
 * Note a NULL pointer can be added to the queue. However NULL values are treated differently when dequeued (see below).
 */
void enqueue(task_t*task);


/**
 * If the queue is empty, then this call will block until an enqueue call completes.
 * Once NULL is returned, dequeue will always return NULL for future calls and dequeue will never block.
 */
task_t* dequeue();