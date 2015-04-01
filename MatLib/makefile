
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
##  makefile - MatLib Library
##  Justin M Selfridge
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

EXEC   = DebugMatLib
CC     = gcc
CFLAGS = -c -Wall
DEP    = MatLib.h
LIB    = libMat.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), $(o).o )

all : $(EXEC) $(LIB)

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $@

%.o : %.c $(DEP)
	$(CC) $(CFLAGS) -c -o $@ $< 

$(LIB) :
	ar -cvq $(LIB) *.o

clean :
	rm $(OBJ) $(EXEC)
