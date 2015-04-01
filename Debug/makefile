
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
##  makefile - Debug the library directory
##  Justin M Selfridge
##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

EXEC   = Debug
CC     = gcc
CFLAGS = -c -Wall

MATDIR = ../MatLib/
MATLIB = libMat.a
MATINC = MatLib.h
MATOBJ = MatIO.o MatManip.o MatArith.o MatProp.o MatDecomp.o
MATSRC = MatIO.c MatManip.c MatArith.c MatProp.c MatDecomp.c

#FILE := $(shell ls | grep -F ".c" )
#NAME := $(patsubst %.c, %, $(FILE) )
#OBJ  := $(foreach o, $(NAME), $(o).o )

all : $(EXEC)

$(EXEC) : LibDebug.o  MatDebug.o  ../MatLib/MatProp.o
	$(CC) LibDebug.o  MatDebug.o  -o $@ $(MATDIR)$(MATLIB)

LibDebug.o : LibDebug.c LibDebug.h
	$(CC) $(CFLAGS) -o $@ $< 

MatDebug.o : MatDebug.c MatDebug.h
	$(CC) $(CFLAGS) -o $@ $< 

../MatLib/MatProp.o :  ../MatLib/MatProp.c  $(MATDIR)$(MATINC)
	$(CC) $(CFLAGS) -o $@ $< ; \
	cd $(MATDIR); \
	rm libMat.a; \
	ar -cvq libMat.a *.o;

clean :
	rm LibDebug.o MatDebug.o $(EXEC)

