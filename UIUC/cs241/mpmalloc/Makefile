# Copyright Orighinal authors (CS241 UIUC staff)

# Note debugging is turned on. Once your code is debugger consider enabling optimization (-O3) and turnning off debugging
# For the competition server your code is compiled using our own makefile

CC = gcc
INC = -I.
FLAGS += -g -Wextra -Wall -Werror
FLAGS += -Wno-unused
TESTERS = $(patsubst %.c, %, $(wildcard testers/*))

all: copyright-check alloc.so contest-alloc.so mreplace mcontest tester-agents

copyright-check:
	if grep -q -F "Copyright (C) [Full name] ([netid]) 2015" alloc.c ; \
	then echo ">>> Fix copyright - see alloc.c comments <<<" && false; \
	else echo ">>> Copyright set <<" ; \
	fi

alloc.so: alloc.c
	$(CC) $^ $(FLAGS) -o $@ -shared -fPIC

contest-alloc.so: contest-alloc.c
	$(CC) $^ $(FLAGS) -o $@ -shared -fPIC -ldl

mreplace: mreplace.c
	$(CC) $^ $(FLAGS) -o $@

mcontest: mcontest.c
	$(CC) $^ $(FLAGS) -o $@ -ldl -lpthread

tester-agents: part1 part2

part1: part1/tester-1 part1/tester-2 part1/tester-3 part1/tester-4

part2: $(subst testers, part2, $(TESTERS))

part1/%: testers/%.c
	$(CC) $^ $(FLAGS) -o $@

part2/%: testers/%.c
	$(CC) $^ $(FLAGS) -DPART2 -o $@

.PHONY : clean
clean:
	-rm -f *.o *.so mreplace mcontest part1/* part2/*
