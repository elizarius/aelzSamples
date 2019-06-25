################################################################
#
#       Makefile for demo
#
################################################################

export BASE_DIR=/home/aelz/repa/aelzSamples
CXX      = g++
CXXFLAGS = -g -std=c++11
INCLUDES =	-I. \
			-I${BASE_DIR}/include \
			-I${BASE_DIR}/udsServer \
			-I${BASE_DIR}/es/08_dom


LIBS =	-lpthread


#################### Objects ###################################


OBJECTS =	main.o \
			Loader.o \
			UdsSocketDemo.o \
			FwdList.o \
			DomWorker.o \
			${BASE_DIR}/udsServer/UdsServer.o \
			${BASE_DIR}/udsServer/InterfaceHandler.o \
			${BASE_DIR}/es/08_dom/BinarySearchTree.o


#OBJECTS := $(wildcard *.o)
################### Target #####################################


all: demo

demo: $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f  *.o \
	rm demo \
	rm -f uds_socket

