IDIR=include
SDIR=src
CC=gcc
CFLAGS=-I$(IDIR) -Wall -Werror -g -lpthread

ODIR=$(SDIR)/obj
LDIR =lib

LIBS= -pthread

# Add .h include files here
_DEPS = global.h matchsim.h person.h zones.h utils.h

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Add .o include file deps here
_OBJ = q2.o matchsim.o person.o zones.o utils.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS)

# make shell
q2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# make clean
.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

# https://users.cs.cf.ac.uk/Dave.Marshall/C/node32.html