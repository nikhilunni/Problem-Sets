Multi-threaded merge sort MP

Oh no! You're lucid dreaming! You're trapped inside a dream world and the only way out is to win the manic merge sort competition and beat my single-threaded implementation.

Your challenge is to create a fast, multi-threaded integer merge-sort program that employs worker threads and a fixed sized ring buffer to implement a task queue. You should complete this assignment by yourself.


Simplest example use:

This is the simplest way that users use the program:

./mpsort data/example.txt

The above program might yield the following output:
1
2
3
4
4

You can assume the data file contains one integer value per line.

Assignment Overview: 

By default the program will use my original single-threaded merge sort implementation. 
However, when the user specifies the number of threads to use, then your multi-threaded merge sort will be used.

In part 1 of this assignment, you will implement a special fixed-sized, blocking ring buffer queue and use it to complete a multi-threaded merge sort.
Several useful functions are provided in mpsortutil.c (e.g. simple_merge and functions to print statistics) that may be useful to you.

In part 2 of this assignment, your challenge is to create a fast streaming merge sort that begins to sort the data before the entire data set is loaded into memory.
You may decide that the provided functions in mpsortutil.c are non-optimal and create your own faster implementations.

A reminder about Academic Integrity:

Please see the computer science department's policy, using the link below. The short version: You must write all of the code yourself. You may not leave your solution in plain sight (this includes sharing it with friends or posting in a public place on the Internet). Copying other student's solutions or providing solutions to other students is a violation of academic integrity. If in doubt, ask. Your code must include your name and netid.

https://cs.illinois.edu/current-students/undergraduates/policies-and-procedures-0/honor-code-and-academic-integrity


Worker threads and usage:

The user specifies the number of threads when invoking your program. For example, -8 means you will create and use an additional 7 threads (to give 8 usable threads in total). Here are the options that you will support:

./mpsort -h
Usage ./mpsort <options> inputfile [outputfile]
  -N  number of threads that can be created including original thread (min 1, max 9)
  -s  fast streaming merge sort
  -v  verbose output (always printed to standard out)
  -h  print this information to stdout and exit

msort -v8   in.txt out.txt
msort -v -8 in.txt out.txt

Print out your own debugging information to stderr because output to stdout will be validated against expected output for grading.


Week 1: i) Getting started with the queue - Part 1 (30 points)

Before working on the mpsort itself, complete the fixed-sized blocking ring buffer.
Write all of your code for this inside blocking_ring_buffer.c (and add your name and netid). 
	(do not use additional .h or .c files; all changes to the Makefile and other files will be ignored when we grade your work)

Use condition variables and mutex locks so that threads that call dequeue or enqueue will be blocked if the task queue is empty or full respectively
Your blocked threads will not consume any CPU resources, i.e. busy waiting is not allowed.


Some non-exhaustive tests (see testqueue.c) are provided, and can be run with
make testqueue

Note dequeueing (not enqueueing) a NULL pointer poisons the queue; all future dequeue calls immediately return NULL. Any waiting consumers will also immediately return at this point. Thus returning a NULL task signifies that there will never be any more tasks and the program can finish.

When your ring buffer is working, and you satisfied that you have no race conditions or deadlocks then you can use it to complete mpsort

I encourage to add your own tests and test on a machine with a large number of cores.


Week 1 ii) Implementing a multi-threaded mergesort using a task queue. (30 points)

Review the given code.

Write all of your code inside multithreadedsort.c
	(do not use additional .h or .c files; all changes to the Makefile and other files will be ignored when we grade your work)

Your implementation will use a thread pool: Create a limited number of threads during initialization. Your threads will then pull tasks from a queue until the merge has finished (indicated by a pulling NULL from the queue).  We do not claim that this is the fastest parallel merge sort but it is the most instructive for this course.

Before starting the merge sort algorithm, create the additional threads. During the actual sort and merge, do not create any threads i.e. you will need to re-use a thread for each queued task.

Sorting tasks greater than 256 integers must be split (see the single-thread implementation). Problem sizes equal to or smaller than 256 can be solved immediately (for example by calling clib's qsort() or by implementing your own sort). In verbose mode, after each sort or merge, print out the unique-count statistics to standard out. (Hint: see useful functions in mpsortutil.c)

Use the following to run all provided part1 tests.
make part1test

Week 2 Streaming merge sort competition (40 points)

The competition is similar to the last MP; you will need to set your name inside NICKNAME.txt. The competition will not be available immediately; we will post on Piazza when it is ready.

Use the following to run the provided part 2 benchmark. In the second week you may also wish to modify the makefile so that the part 1 tests use your streaming code.
make part2test

I encourage to add your own tests and test on a machine with a large number of cores.


Grading criteria:
Part 1:
  Fixed-sized Ring buffer passes all tests (note these tests may be more rigorous than the provided tests) (30 points)
  Multi-threaded worker-queue merge sort which is faster than single-threaded implementation and generates correct output (30 points)
  
Part 2:
  Streaming merge sort (40 points):
  Implementations that are no faster than the single-threaded version or do not generate correct output earn 0 points
  To earn 20 points you need to beat the TA simple solution
  To earn 30 points you need to be in the top 40% of students
  To earn 35 points you need to be in the top 20% of students
  To earn 37 points you need to be in the top 10% of students
  To earn 39 points you need to be in the top 5%  of students
  To earn 40 points you need to be in the top 2%  of students


Important: How to earn zero points:
* If, for example, your program is started with -5 then you may only call pthread_create four(4) times. You may not fork or use another process to do the work!
* Single-threaded or submissions that do not adhere to the requirements (for example sorting on the GPU, using a different sorting algorithm, or using external libraries) will result in *zero points*. In short earn your points by mastering the assignment.
* Solutions that are no faster than the single threaded example will earn zero points.

We expect to grade this using a multi-core (N>=4) machine. Our expectation is to pass in a thread value that is equal to the number of available cores on the grading machine (e.g. ./mpsort -4 ).





Appendix (for those students that wish to re-implement their own count_unique/verbose output function)

Short version: Your output should match the verbose output in the original single-threaded implementation.
When verbose output is enabled, your program will print out the following verbose information at each merge step (one per line) to stdout:

[0,255,39]

The first and second numbers indicate the merge range (i.e. the left hand chunk lowest index and the right-hand chunk highest index inclusive). The third number represents the number of unique values.

[1,2,4,9][4,4,6,8]
would print
[0,7,5] because 5 values are unique (1,2,6,8,9).

and
[1,2,7,7][1,2,3,9]
would print 
[0,7,2] because 2 values are unique (3,9)

Sorting tasks 256 entries or smaller should not be split. These can be sorted by quicksort and their statistics immediately printed.


Generating random data sets & Testing:

See the Makefile for examples of generating random data. We included gen.c to help generate random data. For example,

./gen --min 1 --max 99999 1000000 >data/million.txt

Generates a text file with one million entries. Each line includes one random integer between 1 and 99999 inclusive

Validating verbose output:

Your multi-threaded program may not print verbose lines in the same order as the example output.
However, the number of unique entries for any particular range should be identical for a given range. thus by sorting and 'diffing' the output can be validated agains other successful prior sorts.

For the example dataset 'data/million.txt' the verbose output was generated using 
./mpsort  -v data/million.txt output.txt > data/million_stdout.txt

Bugs:
If there are clarifications or revisions to the given code we will announce changes on Piazza

