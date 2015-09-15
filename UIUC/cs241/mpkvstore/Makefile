# CS 241
# University of Illinois

CC = gcc
INC = -I. -Ilibs
FLAGS = -D_GNU_SOURCE -g -W -Wall
LIBS = -lpthread

all: server

server: jsmn.o libdictionary.o libhttp.o queue.o libjsonparse.o datastore_control.o datastore.o server.c
	$(CC) $(FLAGS) $(INC) $^ -o $@ $(LIBS)

libdictionary.o: libs/libdictionary.c libs/libdictionary.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

libjsonparse.o: libjsonparse.c libjsonparse.h jsmn.o datastore_control.o
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

libhttp.o: libs/libhttp.c libs/libhttp.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

jsmn.o: jsmn/jsmn.c jsmn/jsmn.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

queue.o: queue.c queue.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

datastore_control.o: datastore_control.c datastore_control.h datastore.o
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

datastore.o: datastore.c datastore.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@ $(LIBS)

clean:
	-rm -rf *.o server doc/html
