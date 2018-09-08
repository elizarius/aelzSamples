# For now just command line
#g++  -L/usr/lib/x86_64-linux-gnu simple.cpp -o db -lpq -lm
################################################################
#
#       Makefile for dbclient
#
################################################################

CXX      = g++
CXXFLAGS = -g
INCLUDES = -I.

LIBS = -L/usr/lib/x86_64-linux-gnu -lpq -lm

#################### Objects ###################################


OBJECTS = simple.o \
	SqlConnection.o

#OBJECTS := $(wildcard *.o)
################### Target #####################################


all: dbclient

dbclient: $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f  *.o \
	rm -f dbclient




