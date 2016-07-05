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


################### Target #####################################


all: rtclient

rtclient: $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f  *.o \
	rm rtclient



