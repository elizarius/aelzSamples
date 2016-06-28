################################################################
#
#       Makefile for rtclient
# 
################################################################

CXX      = g++
CXXFLAGS = -g
INCLUDES = -I. \
	   -I/home/user/lsiZebos/ZebOS/hal \
	   -I/home/user/lsiZebos/ZebOS/lib

LIBS     =   

#LIBS    = L/usr/X11R6/lib -lX11 # Contains libraries we need to link in.    

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



