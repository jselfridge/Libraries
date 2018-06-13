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
EXEC        := mat

CC          := gcc
CFLAGS      := -c -Wall -O2
LFLAGS      := -L. -lm -lrt -lmat

PREFIX      := /usr
RM          := rm -f
INSTALL     := install -o root -g root -m 4755
INSTALLDIR  := install -d -m 755




$(LIB) : matManip.o
	ar -cvq $@ $<
	@echo "Finished compiling library."
	@echo " "

$(EXEC) : matDebug.o libmat.a
	$(CC) -o $@ $< $(LFLAGS)

matManip.o : matManip.c matLib.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

matDebug.o : matDebug.c matLib.h
	$(CC) $(CFLAGS) -I. -c $< -o $@




debug:
	$(MAKE) $(EXEC) --no-print-directory
	@echo "Finished compiling debug program."
	@echo " "

install:
	@$(MAKE) --no-print-directory
	@$(INSTALLDIR) $(DESTDIR)$(PREFIX)/lib
	@$(INSTALL) $(LIB) $(DESTDIR)$(PREFIX)/lib
	@echo "$Library installation complete."

clean:
	@$(RM) $(EXEC) $(LIB) matDebug.o matManip.o
	@echo "Finished cleaning directory."
	@echo " "



