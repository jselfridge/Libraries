
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
##  makefile - MatLib Library
##  Justin M Selfridge
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CC     = gcc
CFLAGS = -c -Wall
HEAD   = MatLib.h
LIB    = libMat.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), $(o).o )

all : $(OBJ) $(LIB)

%.o : %.c $(HEAD)
	$(CC) $(CFLAGS) -c -o $@ $< 

$(LIB) :
	ar -cvq $(LIB) *.o

clean :
	rm $(OBJ)

