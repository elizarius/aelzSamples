################################################################
#
#       Makefile for demo
#
################################################################

#export BASE_DIR=/home/aelz/repa/aelzSamples
export BASE_DIR=../../
CXX      = g++
CXXFLAGS = -g -std=c++11
INCLUDES =	-I. \
			-I${BASE_DIR}/include \
			-I${BASE_DIR}/movieTickets


LIBS =	-lpthread


#################### Objects ###################################


OBJECTS =	test_main.o \
			${BASE_DIR}/movieTickets/Schema.o \
			${BASE_DIR}/movieTickets/TheatersDb.o \
			${BASE_DIR}/movieTickets/api.o


#OBJECTS := $(wildcard *.o)
################### Target #####################################


all: test_tickets

test_tickets: $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f  *.o \
	rm -f ${BASE_DIR}/movieTickets/*.o \
	rm test_tickets


