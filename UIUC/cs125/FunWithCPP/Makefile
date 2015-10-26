#
# USING THIS MAKEFILE:
#
# Type 'make' to compile your program. Use
# 'make clean' to start the process from scratch.
# This Makefile is originally from CS225.

#
# Object (binary) files are listed here
#
OBJS = hello.o

#
# The program name here
#
EXENAME = hello

#
# Recognize these macro assignments (like g++), but leave them alone.
#
CC = g++
CCOPTS = -c -g -O0 -Wall
LINK = g++
LINKOPTS = -o

all : $(EXENAME)

#
# The main compiling step, using all macros.
#
$(EXENAME) : $(OBJS)
	$(LINK) $(LINKOPTS) $(EXENAME) $(OBJS)

hello.o : hello.cpp 
	$(CC) $(CCOPTS) hello.cpp


clean : 
	rm -f *.o $(EXENAME) 2>/dev/null

