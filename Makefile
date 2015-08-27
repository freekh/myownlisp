CC = cc
ODIR = target
IDIR = .
CFLAGS = -I$(IDIR) -g -Wall -std=c99 

###

LIBS = -ledit -lm

###

_DEPS = mpc/mpc.c
_OBJ = eval.o prompt.o

###

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

###

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

frispy: $(OBJ)
	$(CC) $(DEPS) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

clean-all: clean
	rm -rf frispy frispy.dSYM
