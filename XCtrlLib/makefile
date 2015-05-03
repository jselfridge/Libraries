
##============================================================
##  makefile - CtrlLib Library
##  Justin M Selfridge
##============================================================

CC     = gcc
CFLAGS = -Wall -g -c
INC    = CtrlLib.h
LIB    = libCtrl.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), Obj/$(o).o )

all : $(OBJ)
	ar -cvq $(LIB) Obj/*.o  

Obj/%.o : %.c $(INC)
	$(CC) $(CFLAGS) -o $@ $<

clean :
	rm $(OBJ) $(LIB)

