
##============================================================
##  makefile - Debug rotLib
##  Justin M Selfridge
##============================================================

EXEC   = debug
CC     = gcc
CFLAGS = -Wall -g -c

INC    =  -I..           -I../../matLib
LIB    =    ../librot.a    ../../matLib/libmat.a

OBJ    = rotDebug.o

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(LIB) -o $@ $<

%.o : %.c %.h
	$(CC) $(INC) $(CFLAGS) -o $@ $< 

clean :
	rm $(EXEC) $(OBJ)

