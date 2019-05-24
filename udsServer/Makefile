################################################################
#
#       Makefile for rtclient
#
################################################################

export BASE_DIR=/home/aelz/repa/aelzSamples
CXX      = g++
CXXFLAGS = -g -std=c++11
INCLUDES = -I.\
		   -I${BASE_DIR}/include

LIBS     =


#################### Objects ###################################


OBJECTS = main.o \
	Handlers.o \
	HelpHandler.o \
	InterfaceHandler.o \
	UdsServer.o

#OBJECTS := $(wildcard *.o)
################### Target #####################################


all: rtclient

rtclient: $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f  *.o \
	rm rtclient

