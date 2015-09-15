EXE = testimage
OBJS = png.o rgbapixel.o image.o

COMPILER = g++
COMPILER_OPTS = -c -g -O0 -Wall -Werror
LINKER = g++
LINKER_OPTS = -lpng

all : $(EXE) testscene

testscene: $(OBJS) testscene.o scene.o
	$(LINKER) $(OBJS) testscene.o scene.o $(LINKER_OPTS) -lpng -o testscene

$(EXE) : $(OBJS) testimage.o
	$(LINKER) $(OBJS) testimage.o $(LINKER_OPTS) -o $(EXE)

testscene.o : testscene.cpp scene.h png.h rgbapixel.h image.h
	$(COMPILER) $(COMPILER_OPTS) testscene.cpp

scene.o: scene.cpp scene.h png.h rgbapixel.h image.h
	$(COMPILER) $(COMPILER_OPTS) scene.cpp

testimage.o : testimage.cpp png.h rgbapixel.h image.h 
	$(COMPILER) $(COMPILER_OPTS) testimage.cpp

png.o : png.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) rgbapixel.cpp

image.o : image.cpp image.h png.h rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) image.cpp

clean :
	-rm -f *.o 
