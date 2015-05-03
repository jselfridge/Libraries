
##============================================================
##  makefile - Debug RotLib
##  Justin M Selfridge
##============================================================


CC     = gcc
CFLAGS = -c -Wall


all : Debug

Debug : RotDebug.o
	$(CC) ../libRot.a -o $@ $<

RotDebug.o : RotDebug.c RotDebug.h
	$(CC) $(CFLAGS) -o $@ $< 

clean :
	rm RotDebug.o Debug

