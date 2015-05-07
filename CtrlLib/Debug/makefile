
##============================================================
##  makefile - Debug ctrlLib
##  Justin M Selfridge
##============================================================

EXEC   = Debug
CC     = gcc
CFLAGS = -Wall -g -c

INC    =  -I..            -I../../matLib
LIB    =    ../libctrl.a    ../../matLib/libmat.a

OBJ    = ctrlDebug.o

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(LIB) -o $@ $< 

%.o : %.c %.h
	$(CC) $(INC) $(CFLAGS) -o $@ $< 

clean :
	rm $(EXEC) $(OBJ)

