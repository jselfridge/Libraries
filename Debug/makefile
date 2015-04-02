
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
##  makefile - Debug the library directory
##  Justin M Selfridge
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

EXEC   = Debug
CC     = gcc
CFLAGS = -c -Wall

MATLIB = ../MatLib/libMat.a
ROTLIB = ../RotLib/libRot.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), $(o).o )

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $@ $(MATLIB) $(ROTLIB)

%.o : %.c %.h
	$(CC) $(CFLAGS) -o $@ $< 

clean :
	rm $(OBJ) $(EXEC)

