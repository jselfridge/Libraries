
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
##  makefile - RotLib Library
##  Justin M Selfridge
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CC     = gcc
CFLAGS = -c -Wall
INC    = RotLib.h
LIB    = libRot.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), $(o).o )

all : $(OBJ)
	rm $(LIB); \
	ar -cvq $(LIB) *.o

%.o : %.c $(INC)
	$(CC) $(CFLAGS) -o $@ $< 

clean :
	rm $(OBJ)

