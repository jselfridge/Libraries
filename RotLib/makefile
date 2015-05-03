
##============================================================
##  makefile - RotLib Library
##  Justin M Selfridge
##============================================================

CC     = gcc
CFLAGS = -Wall -g -c

INC    = -I../MatLib
LIB    = libRot.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), Obj/$(o).o )

all : $(OBJ)
	ar -cvq $(LIB) Obj/*.o  

Obj/%.o : %.c RotLib.h
	$(CC) $(INC) $(CFLAGS) -o $@ $< 

clean :
	rm $(OBJ) $(LIB)

