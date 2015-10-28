# Author: Jeremy Griffith

IDIR = ../include
CC = gcc
CFLAGS = -I$(IDIR)
ODIR = obj

# Contains the list of header files
_DEPS = as4.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

# Contains the list of object files to be linked
_OBJ = main.o semaphores.o linked_list.o deposit.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

# If any of the .c files or .h files change, run this section
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# If any of the .o file change, run this section
as4: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# A make command for cleaning the object files from the obj directory
.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
