# CS 241
# University of Illinois

CC = gcc
PP = g++
INC = -I. -Ilibs
FLAGS = -D_GNU_SOURCE -g
LIBS = -lpthread
RM = -rm -f

all:
	make quietrun --quiet	

quietrun: copying building testing clean

testing: building
	./tester

copying:
	cp ../datastore* .

building: copying tester

tester: tester.o datastore_control.o datastore.o test_utility.o
	$(PP) $(FLAGS) $(INC) $^ -o $@ $(LIBS)

tester.o: tester.cpp test_utility.o datastore_control.o datastore.o
	$(PP) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

test_utility.o: test_utility.c  test_utility.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

datastore_control.o: datastore_control.c datastore_control.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

datastore.o: datastore.c datastore.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

clean:
	$(RM)  *.o datastore*
