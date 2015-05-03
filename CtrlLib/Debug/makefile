
##============================================================
##  makefile - Debug CtrlLib
##  Justin M Selfridge
##============================================================


CC     = gcc
CFLAGS = -c -Wall


all : Debug

Debug : CtrlDebug.o
	$(CC) -o $@ $< ../libCtrl.a ../../MatLib/libMat.a  

CtrlDebug.o : CtrlDebug.c CtrlDebug.h
	$(CC) $(CFLAGS) -o $@ $< 

clean :
	rm CtrlDebug.o Debug

