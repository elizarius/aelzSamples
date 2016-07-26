################################################################
#
#       Makefile for rtclient
#
################################################################

CXX      = g++
CXXFLAGS = -g
INCLUDES = -I.

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



