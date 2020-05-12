#*******************************************************************************
# 
# Justin M Selfridge, PhD
# Gradient Consulting, LLC
# jselfridge@gmail.com
# 
# Makefile (Libraries)
# 
#******************************************************************************/


LIB         := libmat.a
EXEC        := debug

CC          := gcc
CFLAGS      := -c -Wall -O2
LFLAGS      := -L. -lm -lrt -lmat

PREFIX      := /usr
RM          := rm -f
INSTALL     := install -o root -g root -m 4755
INSTALLDIR  := install -d -m 755

OBJ :=  matManip.o  matComplex.o  matVec.o  matArith.o




$(EXEC) : matDebug.o libmat.a
	$(CC) -o $@ $< $(LFLAGS)
	@echo "Finished compiling debug program."
	@echo " "

$(LIB) : $(OBJ)
	ar -cvq $@ $(OBJ)
	@echo "Finished compiling matrix library."
	@echo " "




matManip.o : matManip.c matLib.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

matComplex.o : matComplex.c matLib.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

matVec.o : matVec.c matLib.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

matArith.o : matArith.c matLib.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

matDebug.o : matDebug.c matLib.h
	$(CC) $(CFLAGS) -I. -c $< -o $@




lib:
	$(MAKE) $(LIB) --no-print-directory

install:
	@$(MAKE) --no-print-directory
	@$(INSTALLDIR) $(DESTDIR)$(PREFIX)/lib
	@$(INSTALL) $(LIB) $(DESTDIR)$(PREFIX)/lib
	@echo "$Library installation complete."

clean:
	@$(RM) $(EXEC) $(LIB) $(OBJ) matDebug.o
	@echo "Finished cleaning directory."
	@echo " "



