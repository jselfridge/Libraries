
##============================================================
##  makefile - optLib Library
##  Justin M Selfridge
##============================================================

CC     = gcc
CFLAGS = -Wall -g -c

INC    = -I../matLib
LIB    = libopt.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), obj/$(o).o )

all : $(OBJ)
	ar -cvq $(LIB) obj/*.o

obj/%.o : %.c optLib.h
	$(CC) $(INC) $(CFLAGS) -o $@ $< 

clean :
	rm $(OBJ) $(LIB)

