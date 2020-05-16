#*******************************************************************************
# 
# Justin M Selfridge, PhD
# Gradient Consulting, LLC
# jselfridge@gmail.com
# 
# Makefile (Libraries)
# 
#******************************************************************************/


all: demo

lib: libmat.a

demo: obj/matDemo.o
	gcc -o demo obj/matDemo.o

obj/matDemo.o: src/matDemo.c
	gcc -c src/matDemo.c -o obj/matDemo.o

obj/matManip.o: src/matManip.c inc/matManip.h inc/matLib.h
	gcc -c src/matManip.c -o obj/matManip.o

libmat.a: obj/matManip.o
	ar cvr libmat.a obj/matManip.o

clean:
	rm -f demo libmat.a obj/matDemo.o obj/matManip.o






#all: myProgram

#myProgram: main.o libmylib.a #libmylib.a is the dependency for the executable
#        gcc -lm -o myProgram main.o -L. -lmylib

#main.o: main.c
#        gcc -O -c main.c main.h

#addSorted.o: addSorted.c addSorted.h
#        gcc -O -c addSorted.c

#freeLinks.o: freeLinks.c freeLinks.h
#        gcc -O -c freeLinks.c

#libmylib.a: addSorted.o freeLinks.o #let's link library files into a static library
#        ar rcs libmylib.a addSorted.o freeLinks.o

#libs: libmylib.a

#clean:
#        rm -f myProgram *.o *.a *.gch #This way is cleaner than your clean






#LIB         := libmat.a
#EXEC        := debug

#CC          := gcc
#CFLAGS      := -c -Wall -Wconversion -fsingle-precision-constant -O2
#LFLAGS      := -L. -lm -lrt -lmat

#PREFIX      := /usr
#RM          := rm -f
#INSTALL     := install -o root -g root -m 4755
#INSTALLDIR  := install -d -m 755

#OBJ :=  matManip.o  matComplex.o  matVec.o  matArith.o  matRoot.o  matDecomp.o




#$(EXEC) : matDebug.o $(LIB)
#	$(CC) -o $@ $< $(LFLAGS)
#	@echo "Finished compiling debug program."
#	@echo " "

#$(LIB) : $(OBJ)
#	ar -cvq $@ $(OBJ)
#	@echo "Finished compiling matrix library."
#	@echo " "




#matManip.o : matManip.c matLib.h
#	$(CC) $(CFLAGS) -I. -c $< -o $@

#matComplex.o : matComplex.c matLib.h
#	$(CC) $(CFLAGS) -I. -c $< -o $@

#matVec.o : matVec.c matLib.h
#	$(CC) $(CFLAGS) -I. -c $< -o $@

#matArith.o : matArith.c matLib.h
#	$(CC) $(CFLAGS) -I. -c $< -o $@

#matRoot.o : matRoot.c matLib.h
#	$(CC) $(CFLAGS) -I. -c $< -o $@

#matDecomp.o : matDecomp.c matLib.h
#	$(CC) $(CFLAGS) -I. -c $< -o $@

#matDebug.o : matDebug.c matLib.h $(LIB)
#	$(CC) $(CFLAGS) -I. -c $< -o $@




#lib:
#	$(MAKE) $(LIB) --no-print-directory

#install:
#	@$(MAKE) --no-print-directory
#	@$(INSTALLDIR) $(DESTDIR)$(PREFIX)/lib
#	@$(INSTALL) $(LIB) $(DESTDIR)$(PREFIX)/lib
#	@echo "$Library installation complete."

#clean:
#	@$(RM) $(EXEC) $(LIB) $(OBJ) matDebug.o
#	@echo "Finished cleaning directory."
#	@echo " "



