
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
##  makefile - MatLib Library
##  Justin M Selfridge
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CC     = gcc
CFLAGS = -c -Wall
INC    = MatLib.h
LIB    = libMat.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), $(o).o )

all : $(OBJ)
	ar -cvq $(LIB) *.o

%.o : %.c $(INC)
	$(CC) $(CFLAGS) -o $@ $< 

clean :
	rm $(OBJ)

