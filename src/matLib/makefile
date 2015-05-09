
##============================================================
##  makefile - matLib Library
##  Justin M Selfridge
##============================================================

CC     = gcc
CFLAGS = -Wall -g -c

LIBS   = -lm
IDIR   = ../../inc 
LDIR   = ../../lib

FILE  := $(shell ls | grep -F ".c" )
NAME  := $(patsubst %.c, %, $(FILE) )
OBJ   := $(foreach o, $(NAME), obj/$(o).o )

all : $(OBJ)
	ar -cvq $(LDIR)/libmat.a obj/*.o

obj/%.o : %.c ../../inc/matLib.h
	$(CC) $(CFLAGS) -I$(IDIR) -o $@ $< 

clean :
	rm $(OBJ) $(LDIR)/libmat.a

