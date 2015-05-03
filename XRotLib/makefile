
##============================================================
##  makefile - RotLib Library
##  Justin M Selfridge
##============================================================

CC     = gcc
CFLAGS = -c -Wall
INC    = RotLib.h
LIB    = libRot.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), Obj/$(o).o )

all : $(OBJ)
	ar -cvq $(LIB) Obj/*.o  

Obj/%.o : %.c $(INC)
	$(CC) $(CFLAGS) -o $@ $< 

clean :
	rm $(OBJ) $(LIB)

