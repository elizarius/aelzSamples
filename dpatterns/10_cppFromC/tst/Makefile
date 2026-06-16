# Makefile for the cppFrom programming example
#

BASE_DIR=/home/user/myCpp
INCLUDES =	-I$(BASE_DIR)/cppFromC/ \
		-I.

TARGET	:= myExample 
SRCS 	:= test.c
OBJS    := ${SRCS:.c=.o} 
DEPS    := ${SRCS:.c=.dep} 
XDEPS   := $(wildcard ${DEPS}) 

CCFLAGS = -Wall -Werror -ggdb $(INCLUDES)
LDFLAGS = -L$(BASE_DIR)/cppFromC -Bstatic 
LIBS    = -lmySimple -lstdc++

.PHONY: all clean distclean 
all:: ${TARGET} 

ifneq (${XDEPS},) 
include ${XDEPS} 
endif 

${TARGET}: ${OBJS} 
	${CC} ${LDFLAGS} -o $@ $^ ${LIBS} 

${OBJS}: %.o: %.c %.dep 
	${CC} ${CCFLAGS} -o $@ -c $< 

${DEPS}: %.dep: %.c Makefile 
	${CC} ${CCFLAGS} -MM $< > $@ 

clean::
	rm -f *~ *.o *.dep  ${TARGET} 

distclean:: clean

