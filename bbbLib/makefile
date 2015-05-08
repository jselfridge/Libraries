
##============================================================
##  makefile - bbbLib Library
##  Justin M Selfridge
##============================================================

CC     = gcc
CFLAGS = -Wall -g -c

INC    = -I../matLib  -I../rotLib
LIB    = libbbb.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), obj/$(o).o )

all : $(OBJ)
	ar -cvq $(LIB) obj/*.o

obj/%.o : %.c bbbLib.h
	$(CC) $(INC) $(CFLAGS) -o $@ $< 

clean :
	rm $(OBJ) $(LIB)

