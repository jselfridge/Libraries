
##============================================================
##  makefile - ctrlLib Library
##  Justin M Selfridge
##============================================================

CC     = gcc
CFLAGS = -Wall -g -c

INC    = -I../matLib
LIB    = libctrl.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), obj/$(o).o )

all : $(OBJ)
	ar -cvq $(LIB) Obj/*.o  

obj/%.o : %.c ctrlLib.h
	$(CC) $(INC) $(CFLAGS) -o $@ $<

clean :
	rm $(OBJ) $(LIB)

