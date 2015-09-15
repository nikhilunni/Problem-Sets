SOURCES=$(wildcard *.c)
EXECS=$(SOURCES:.c=)
CC = gcc
FLAGS = -W -Wall -g -std=gnu99 -Wno-unused-variable -Wno-unused-parameter  

all: filelist webserver

style:
	astyle  -n *.c  

filelist: filelist.c
	$(CC) $(FLAGS) filelist.c -o filelist

webserver: webserver.c
	$(CC) $(FLAGS) webserver.c -o webserver

clean:
	rm -rf $(EXECS) setup webserver *.dSYM   