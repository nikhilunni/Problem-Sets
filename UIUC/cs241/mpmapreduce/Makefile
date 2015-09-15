# CS 241
# University of Illinois

CC = gcc
INC = -I. -Ilibdslocal/
FLAGS = -g -W -Wall -std=c99
LIBS = -lpthread

OBJECTS = libds.o libmapreduce.o

all: alice.txt test1 test2 test3 test4 test5 test6 part2

alice.txt:
	wget https://courses.engr.illinois.edu/cs241/mp/alice.txt

test1: $(OBJECTS) test1.c
	$(CC) $(FLAGS) $^ -o $@ $(LIBS)

test2: $(OBJECTS) test2.c
	$(CC) $(FLAGS) $^ -o $@ $(LIBS)

test3: $(OBJECTS) test3.c
	$(CC) $(FLAGS) $^ -o $@ $(LIBS)

test4: $(OBJECTS) test4.c
	$(CC) $(FLAGS) $^ -o $@ $(LIBS)

test5: $(OBJECTS) test5.c
	$(CC) $(FLAGS) $^ -o $@ $(LIBS)

test6: $(OBJECTS) test6.c
	$(CC) $(FLAGS) $^ -o $@ $(LIBS)

part2: $(OBJECTS) sql.o part2.o part2main.c
	$(CC) $(FLAGS) $^ -o $@ $(LIBS)

libds.o: libds/libds.c libds/libds.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

part2.o: part2.c part2.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

libmapreduce.o: libmapreduce.c libmapreduce.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

sql.o: sql.c sql.h 
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

clean:
	rm -rf *.o *.d test1 test2 test3 test4 test5 test6 part2 *~
