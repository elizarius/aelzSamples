# Makefile for the socket programming example
#
OBJECTS = Simple.o \
	  wrapper.o 	 

all : simple

simple: $(OBJECTS)
	ar -cvq libmySimple.a $(OBJECTS)

clean:
	rm -f *.o *.*~ *.a
