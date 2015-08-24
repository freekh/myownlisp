CC=cc
CFLAGS=

ODIR=obj

LIBS=-lm -ledit

_DEPS = mpc/mpc.c
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = eval.o prompt.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

frispy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
