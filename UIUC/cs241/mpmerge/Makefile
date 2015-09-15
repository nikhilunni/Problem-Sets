
CC = gcc
INC = -I.
FLAGS = -W -Wall -g -std=c99 -Wno-unused-variable -Wno-unused-parameter
FLAGS_OPT = -O3 -std=c99 -Wno-unused-variable  -Wno-unused-parameter
LINKOPTS = -pthread
BIGTHREADCOUNT=4
THREADCOUNT=4
SOURCE = multithreadedsort.c baseline_nothread_mergesort.c main.c mpsortutil.c streamingsort.c blocking_ring_buffer.c

all: copyright-check testqueue mpsort mpsort_opt gen testsmall 

# test1mil test10mil timemulti timestream would be good candidates to add to "all"

mpsort: $(SOURCE)
	$(CC) $(INC) $(FLAGS) $(LINKOPTS) $(SOURCE) -o mpsort

mpsort_opt: $(SOURCE)
	$(CC) $(INC) $(FLAGS_OPT) $(LINKOPTS) $(SOURCE) -o mpsort_opt


copyright-check:
	if grep -q -F "Copyright (C) [Full name] ([netid]) 2015" multithreadedsort.c ; \
	then echo ">>> Fix copyright - see multithreadedsort.c comments <<<" && false; \
	else echo ">>> Copyright set <<" ; \
	fi
	if grep -q -F "Copyright (C) [Full name] ([netid]) 2015" streamingsort.c ; \
	then echo ">>> Fix copyright - see streamingsort.c comments <<<" && false; \
	else echo ">>> Copyright set <<" ; \
	fi
	if grep -q -F "Copyright (C) [Full name] ([netid]) 2015" blocking_ring_buffer.c ; \
	then echo ">>> Fix copyright - see blocking_ring_buffer.c comments <<<" && false; \
	else echo ">>> Copyright set <<" ; \
	fi


testqueue: blocking_ring_buffer.c   testqueue.c 
	$(CC) $(INC) $(FLAGS) $(LINKOPTS) blocking_ring_buffer.c testqueue.c -o runtestqueue
	./runtestqueue 1
	./runtestqueue 2
	./runtestqueue 3
	./runtestqueue 4

part1test: testqueue testsmall test1mil test10mil timemulti
  
part2test: timestream

gen: gen.c
	$(CC) $(INC) $(FLAGS) gen.c -o gen

clean:
	rm -rf runtestqueue mpsort mpsort_opt gen out.txt *.dSYM your_out.txt original_out.txt verbose.txt your_verbose.txt your_verbose_sorted.txt original_verbose.txt orig_verbose_sorted.txt data/rnd10mil.txt  data/rnd8192.txt your_stream_verbose_sorted.txt your_stream_out.txt your_stream_verbose.txt


#Generate 8192 values
data/rnd8192.txt: gen
	./gen --min 1 --max  8192 --seed 1 8192 > data/rnd8192.txt

#Generate 10^7 values
data/rnd10mil.txt: gen
	./gen --min 1 --max  100000000 --seed 1 10000000 > data/rnd10mil.txt


# Check the output of your multi-threaded mergesort for a small data set (N=8192)
testsmall: mpsort data/rnd8192.txt
	./mpsort -v -$(BIGTHREADCOUNT) data/rnd8192.txt your_out.txt > your_verbose.txt
	./mpsort -v data/rnd8192.txt original_out.txt > original_verbose.txt
	sort -n original_verbose.txt  > orig_verbose_sorted.txt
	sort -n your_verbose.txt > your_verbose_sorted.txt
	diff your_out.txt original_out.txt
	diff your_verbose_sorted.txt orig_verbose_sorted.txt
	rm your_verbose.txt your_verbose_sorted.txt original_verbose.txt orig_verbose_sorted.txt your_out.txt original_out.txt 

# Check the output of your multi-threaded mergesort for 10^6 integers
test1mil: gen mpsort
	./mpsort -v -$(THREADCOUNT) data/million.txt your_out.txt > your_verbose.txt
	./mpsort -v data/million.txt original_out.txt > original_verbose.txt
	sort -n original_verbose.txt  > orig_verbose_sorted.txt
	sort -n your_verbose.txt > your_verbose_sorted.txt
	diff your_out.txt original_out.txt
	diff your_verbose_sorted.txt orig_verbose_sorted.txt
	rm your_verbose.txt your_verbose_sorted.txt original_verbose.txt orig_verbose_sorted.txt your_out.txt original_out.txt 

# Check the output of your multi-threaded mergesort for 10^7 integers
test10mil: mpsort data/rnd10mil.txt
	time ./mpsort -v -$(BIGTHREADCOUNT) data/rnd10mil.txt your_out.txt > your_verbose.txt
	time ./mpsort -v data/rnd10mil.txt original_out.txt > original_verbose.txt
	sort -n original_verbose.txt  > orig_verbose_sorted.txt
	sort -n your_verbose.txt > your_verbose_sorted.txt
	diff your_out.txt original_out.txt
	diff your_verbose_sorted.txt orig_verbose_sorted.txt
	rm your_verbose.txt your_verbose_sorted.txt original_verbose.txt orig_verbose_sorted.txt your_out.txt original_out.txt 

# Compare the timing of your multi-threaded version with the original single threaded version
# Note this uses the optimized build of your program
timemulti: mpsort_opt data/rnd10mil.txt
	time ./mpsort_opt -v -$(THREADCOUNT) data/rnd10mil.txt /dev/null >/dev/null 
	time ./mpsort_opt -v data/rnd10mil.txt /dev/null > /dev/null 

# Compare the timing of your multi-threaded version with your streaming version
# Note this uses the optimized build of your program
timestream: gen mpsort_opt data/rnd10mil.txt
	time ./mpsort_opt -v -s -$(BIGTHREADCOUNT) data/8192.txt your_stream_out.txt > your_stream_verbose.txt
	time ./mpsort_opt -v -s -1 data/8192.txt your_out.txt > your_verbose.txt
	sort -n your_stream_verbose.txt  > your_stream_verbose_sorted.txt
	sort -n your_verbose.txt > your_verbose_sorted.txt
	diff your_out.txt your_stream_out.txt
	diff your_verbose_sorted.txt your_stream_verbose_sorted.txt
	rm your_out.txt your_stream_out.txt your_stream_verbose.txt your_stream_verbose_sorted.txt your_verbose.txt your_verbose_sorted.txt 
