
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
##  makefile - Debug the library directory
##  Justin M Selfridge
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

EXEC   = Debug
CC     = gcc
CFLAGS = -c -Wall

MATLIB  = ../MatLib/libMat.a
ROTLIB  = ../RotLib/libRot.a
OPTLIB  = ../OptLib/libOpt.a
CTRLLIB = ../CtrlLib/libCtrl.a

FILE := $(shell ls | grep -F ".c" )
NAME := $(patsubst %.c, %, $(FILE) )
OBJ  := $(foreach o, $(NAME), $(o).o )

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $@ $(MATLIB) $(ROTLIB) $(OPTLIB) $(CTRLLIB)

%.o : %.c %.h
	$(CC) $(CFLAGS) -o $@ $< 

clean :
	rm $(OBJ) $(EXEC)

