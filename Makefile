CC=g++
CFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -I $(IDIR)

IDIR = include
ODIR = obj
SDIR = src

_DEPS = ant.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ant.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o ants $(SDIR)/main.cpp $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
