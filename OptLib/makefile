
##============================================================
##  makefile - OptLib Library
##  Justin M Selfridge
##============================================================

CC     = gcc
CFLAGS = -Wall -g -c

INC    = -I../MatLib
LIB    = libOpt.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), Obj/$(o).o )

all : $(OBJ)
	ar -cvq $(LIB) Obj/*.o

Obj/%.o : %.c OptLib.h
	$(CC) $(INC) $(CFLAGS) -o $@ $< 

clean :
	rm $(OBJ) $(LIB)

