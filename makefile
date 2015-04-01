
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
##  makefile - DEBUGGING
##  Justin M Selfridge
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

EXEC   = RunDebug
CC     = gcc
CFLAGS = -c -Wall
LIB    = libMat/libMat.a
DEP    = MatLib.h

#FILE := $(shell ls | grep -F ".c" )
#NAME := $(patsubst %.c, %, $(FILE) )
#OBJ  := $(foreach o, $(NAME), $(o).o )

all : RunDebug

#gcc -o RunDebug Debug.c MatLib.h libMat.a

RunDebug : Debug.o
	$(CC) Debug.o -o $@ $(LIB)

Debug.o : Debug.c $(DEP)
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm Debug.o RunDebug
