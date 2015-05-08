
##============================================================
##  makefile - Debug bbbLib
##  Justin M Selfridge
##============================================================

EXEC   = debug
CC     = gcc
CFLAGS = -Wall -g -c

INC    =  -I..           -I../../matLib            -I../../rotLib   
LIB    =    ../libbbb.a    ../../matLib/libmat.a     ../../rotLib/librot.a

OBJ    = bbbDebug.o

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(LIB) -o $@ $<

%.o : %.c %.h
	$(CC) $(INC) $(CFLAGS) -o $@ $< 

clean :
	rm $(EXEC) $(OBJ)

