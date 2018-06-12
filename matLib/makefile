#*******************************************************************************
# 
# Justin M Selfridge, PhD
# Gradient Consulting, LLC
# jselfridge@gmail.com
# 
# Makefile (Libraries)
# 
#******************************************************************************/

DEBUG       := mat
LIB         := libmat.a

CC          := gcc
CFLAGS      := -c -Wall -O2
LFLAGS      := -L -lm -lrt -lmat




$(DEBUG) : matDebug.o
	$(CC) -L. -o $@ $< $(LFLAGS)

matDebug.o : matDebug.c matLib.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(LIB) : matManip.o
	ar -cvq $@ $<

matManip.o : matManip.c matLib.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

all:
#	$(DEBUG)
	@echo "Make all"

lib :
	$(MAKE) $(LIB)
	@echo "Make lib"

debug:
	$(MAKE) $(DEBUG)
	@echo "Make debug"

install:
	@echo "Make install"

uninstall:
	@echo "Make uninstall"

clean:
	rm $(DEBUG) matDebug.o
	@echo "Make clean"

test:
	@echo "Make test"



