# Assignment 6 Makefile

IDIR = ../include
CC = gcc
CFLAGS = -I$(IDIR)
ODIR = obj

# Moves listed header files to IDIR
# The first line supplies the dependency list
# The second line searches the current directory for
# the dependencies and moves them to the IDIR
_DEPS = as6.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS)) 

# Moves the listed object files to ODIR
# The first line supplies the object file list
# The second line searches the current directory for
# the object files and moves them to ODIR
_OBJ = main.o client.o server.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

# If any of the .c files or .h files change, recompile them
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# If any of the .o files change, relink them
as6: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# A clean command for emptying the obj directory
.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
