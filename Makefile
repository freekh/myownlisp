CC=cc
LIBS=-ledit -lm
ODIR=target
IDIR=.
CFLAGS=-I$(IDIR) -g -Wall -std=c99 

_DEPS = mpc/mpc.c
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = eval.o prompt.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

frispy: $(OBJ)
	$(CC) $(DEPS) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

clean-all: clean
	rm -rf frispy frispy.dSYM
