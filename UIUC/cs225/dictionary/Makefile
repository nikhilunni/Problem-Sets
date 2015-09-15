CC = g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
CC_OPTS = -O0 -g $(WARNINGS)
LINKER = g++

DICT = test_dict
DICT_OBJS = tester.o

all: $(DICT)

$(DICT): $(DICT_OBJS)
	$(LINKER) -o $(DICT) $(DICT_OBJS)

tester.o: tester.cpp dictionary.h dictionary.cpp
	$(CC) $(CC_OPTS) -c tester.cpp

clean:
	-rm -rf *.o $(DICT)

tidy:
	-rm -rf doc
