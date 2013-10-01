CC      = gcc
CFLAGS  = -Wall -Werror -I$(INC)
LDFLAGS = #

INC = include
SRC = src
OBJ = obj
BIN = bin

all: tproc

# Ex 1:
tproc: $(BIN)/tproc
$(BIN)/tproc: $(OBJ)/tproc.o
		$(CC) -o $@ $< $(LDFLAGS)
$(OBJ)/tproc.o: $(SRC)/tproc.c $(INC)/tproc.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ)/*.o
	rm -rf $(BIN)/*
	rm -rf $(SRC)/*~
	rm -rf $(INC)/*~
