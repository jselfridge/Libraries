
##============================================================
##  makefile - Debug rotLib
##  Justin M Selfridge
##============================================================

EXEC   = debug
CC     = gcc
CFLAGS = -Wall -g -c

INC    =  -I../../../matLib  -I../../rotLib
LIB    =  -lm -lmat -lrot

OBJ    = rotDebug.o

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $< -L.. -lrot -L../../../matLib -lmat -lm

%.o : %.c %.h
	$(CC) $(INC) $(CFLAGS) -o $@ $< 

clean :
	rm $(EXEC) $(OBJ)

