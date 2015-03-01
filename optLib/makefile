
##============================================================
##  makefile - optLib Library
##  Justin M Selfridge
##============================================================

CC     = gcc
CFLAGS = -Wall -g -c

LIBS   = -lm
IDIR   = ../inc
LDIR   = ../lib

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), obj/$(o).o )

all : $(OBJ)
	ar -cvq $(LDIR)/libopt.a obj/*.o

obj/%.o : %.c ../inc/optLib.h
	$(CC) $(CFLAGS) -I$(IDIR) -o $@ $< 

clean :
	rm $(OBJ) $(LIB)

