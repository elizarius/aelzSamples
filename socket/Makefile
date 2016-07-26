################################################################
#
#       Makefile for rtclient
#
################################################################

CXX      = g++
CXXFLAGS = -g
INCLUDES = -I. \
           -I../include

LIBS     =

#################### Objects ###################################


OBJECTS = Socket.o \
    SocketReader.o \
    SocketWriter.o \
    UdsSocket.o


#OBJECTS := $(wildcard *.o)
################### Target #####################################


#all: rtclient

all: $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f  *.o
