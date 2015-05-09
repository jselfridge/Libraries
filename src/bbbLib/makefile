
##============================================================
##  makefile - bbbLib Library
##  Justin M Selfridge
##============================================================

CC     = gcc
CFLAGS = -Wall -g -c

IDIR    = ../inc
LDIR    = ../lib

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), obj/$(o).o )

all : $(OBJ)
	ar -cvq $(LDIR)/libbbb.a obj/*.o

obj/%.o : %.c ../inc/bbbLib.h
	$(CC) $(CFLAGS) -I$(IDIR) -o $@ $< 

clean :
	rm $(OBJ)

