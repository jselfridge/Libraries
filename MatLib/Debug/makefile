
##============================================================
##  makefile - Debug MatLib
##  Justin M Selfridge
##============================================================

EXEC   = Debug
CC     = gcc
CFLAGS = -Wall -g -c

INC    = -I../../matLib
LIB    = ../libmat.a

OBJ    = matDebug.o

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(LIB) -o $@ $<

%.o : %.c %.h
	$(CC) $(INC) $(CFLAGS) -o $@ $< 

clean :
	rm $(EXEC) $(OBJ)

