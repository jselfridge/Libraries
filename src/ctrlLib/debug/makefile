
##============================================================
##  makefile - Debug ctrlLib
##  Justin M Selfridge
##============================================================

EXEC   = debug
CC     = gcc
CFLAGS = -Wall -g -c

LIBS   = -lctrl -lmat -lm
IDIR   = ../../inc
LDIR   = ../../lib

OBJ    = ctrlDebug.o

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $< -L$(LDIR) $(LIBS)

%.o : %.c %.h
	$(CC) $(CFLAGS) -I$(IDIR) -o $@ $< 

clean :
	rm $(EXEC) $(OBJ)

