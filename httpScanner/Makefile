################################################################
#
#       Makefile for http_scan
#
################################################################

#export BASE_DIR=/home/aelz/repa/aelzSamples
export BASE_DIR=../
CXX      = g++
CXXFLAGS = -g -std=c++11
INCLUDES =	-I. \
			-I${BASE_DIR}/include \
			-I../../HTTPRequest/include/


LIBS =	-lpthread

#################### Objects ###################################


OBJECTS =	main.o \
			api.o


#OBJECTS := $(wildcard *.o)
################### Target #####################################


all: http_scan

http_scan: $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f  *.o \
	rm http_scan


