
##============================================================
##  makefile - Debug CtrlLib
##  Justin M Selfridge
##============================================================

EXEC   = Debug
CC     = gcc
CFLAGS = -Wall -g -c

INC    =  -I..            -I../../MatLib
LIB    =    ../libCtrl.a    ../../MatLib/libMat.a

OBJ    = CtrlDebug.o

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(LIB) -o $@ $< 

%.o : %.c %.h
	$(CC) $(INC) $(CFLAGS) -o $@ $< 

clean :
	rm $(EXEC) $(OBJ)

