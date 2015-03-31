
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
##  makefile - MatLib Library
##  Justin M Selfridge
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

EXEC   = Debug
CC     = gcc
CFLAGS = -c -Wall
DEP    = MatLib.h

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), $(o).o )

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $@

%.o : %.c $(DEP)
	$(CC) $(CFLAGS) -c -o $@ $< 

clean :
	rm $(OBJ) $(EXEC)
