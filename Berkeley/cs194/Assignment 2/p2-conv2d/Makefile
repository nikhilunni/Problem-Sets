OBJS=conv2d.o readjpeg.o

%.o: %.cpp readjpeg.h
	g++ -O2 -c $<

all: $(OBJS)
	g++ $(OBJS) -fopenmp -o conv2d -ljpeg
