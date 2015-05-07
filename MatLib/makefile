
##============================================================
##  makefile - matLib Library
##  Justin M Selfridge
##============================================================

CC     = gcc
CFLAGS = -Wall -g -c
INC    = matLib.h
LIB    = libmat.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), obj/$(o).o )

all : $(OBJ)
	ar -cvq $(LIB) obj/*.o

obj/%.o : %.c $(INC)
	$(CC) $(CFLAGS) -o $@ $< 

clean :
	rm $(OBJ) $(LIB)

