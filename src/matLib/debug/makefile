
##============================================================
##  makefile - Debug matLib
##  Justin M Selfridge
##============================================================

EXEC   = debug
CC     = gcc
CFLAGS = -Wall -g -c

LIBS   = -lmat -lm
IDIR   = ../../../inc
LDIR   = ../../../lib

OBJ    = matDebug.o

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $< -L$(LDIR) $(LIBS)

%.o : %.c %.h
	$(CC) $(CFLAGS) -I$(IDIR) -o $@ $<

clean :
	rm $(EXEC) $(OBJ)

