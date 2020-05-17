#*******************************************************************************
# 
# Justin M Selfridge, PhD
# Gradient Consulting, LLC
# jselfridge@gmail.com
# 
# Makefile (Libraries)
# 
#******************************************************************************/


LIB     :=  libmat.a
EXEC    :=  demo

CC      :=  gcc
CFLAGS  :=  -Wall -Wconversion -fsingle-precision-constant -O2
LFLAGS  :=  -L. -lm -lrt -lmat

NAME    :=  $(shell ls ./src | grep -F ".c" )
SRC     :=  $(patsubst %.c, src/%.c, $(NAME) )
OBJ     :=  $(patsubst %.c, obj/%.o, $(NAME) )


all: $(EXEC)

lib: $(LIB)


$(EXEC): bin/matDemo.o $(LIB)
	$(CC) -o $@ $< $(LFLAGS)
	@echo "Finished linking demo program."
	@echo " "

$(LIB): $(OBJ)
	ar cvr $@ $(OBJ)
	@echo "Finished packing matrix library."
	@echo " "


bin/matDemo.o: bin/matDemo.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/%.c inc/%.h inc/matCommon.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(LIB) $(OBJ) bin/matDemo.o
	@echo "Finished cleaning directory."
	@echo " "




#PREFIX      := /usr
#INSTALL     := install -o root -g root -m 4755
#INSTALLDIR  := install -d -m 755

#install:
#	@$(MAKE) --no-print-directory
#	@$(INSTALLDIR) $(DESTDIR)$(PREFIX)/lib
#	@$(INSTALL) $(LIB) $(DESTDIR)$(PREFIX)/lib
#	@echo "$Library installation complete."



