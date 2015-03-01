
##============================================================
##  makefile - Debug matLib
##  Justin M Selfridge
##============================================================

EXEC   = debug
CC     = gcc
CFLAGS = -Wall -g -c

INC    = -I../../matLib
LIB    = -lm -lmat

OBJ    = matDebug.o

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $< -L.. $(LIB)

%.o : %.c %.h
	$(CC) $(INC) $(CFLAGS) -o $@ $<

clean :
	rm $(EXEC) $(OBJ)

