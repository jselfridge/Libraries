
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
##  makefile - Debug the library directory
##  Justin M Selfridge
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

EXEC   = Debug
CC     = gcc
CFLAGS = -c -Wall

#FILE := $(shell ls | grep -F ".c" )
#NAME := $(patsubst %.c, %, $(FILE) )
#OBJ  := $(foreach o, $(NAME), $(o).o )

all : $(EXEC)

#$(EXEC) : $(OBJ)
#	$(CC) $(OBJ) -o $@
$(EXEC) :     LibDebug.o  MatDebug.o
	$(CC) LibDebug.o  MatDebug.o  -o $@  ../MatLib/libMat.a

#%.o : %.c $(DEP)
#	$(CC) $(CFLAGS) -c -o $@ $< 
LibDebug.o : LibDebug.c LibDebug.h
	$(CC) $(CFLAGS) -c -o $@ $< 
MatDebug.o : MatDebug.c MatDebug.h
	$(CC) $(CFLAGS) -c -o $@ $< 

clean :
	rm LibDebug.o MatDebug.o $(EXEC)

