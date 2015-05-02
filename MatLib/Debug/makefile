
##============================================================
##  makefile - Debug MatLib
##  Justin M Selfridge
##============================================================


CC     = gcc
CFLAGS = -c -Wall


all : Debug

Debug : MatDebug.o
	$(CC) ../libMat.a -o $@ $<

MatDebug.o : MatDebug.c MatDebug.h
	$(CC) $(CFLAGS) -o $@ $< 

clean :
	rm MatDebug.o Debug

