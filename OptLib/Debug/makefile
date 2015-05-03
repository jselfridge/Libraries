
##============================================================
##  makefile - Debug OptLib
##  Justin M Selfridge
##============================================================

EXEC   = Debug
CC     = gcc
CFLAGS = -Wall -g -c

INC    =  -I..           -I../../MatLib
LIB    =    ../libOpt.a    ../../MatLib/libMat.a

OBJ    = OptDebug.o

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(LIB) -o $@ $< 

%.o : %.c %.h
	$(CC) $(INC) $(CFLAGS) -o $@ $< 

clean :
	rm $(EXEC) $(OBJ)

