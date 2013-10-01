CC      = gcc
CFLAGS  = -Wall -Werror -I$(INC)
LDFLAGS = #

INC = include
SRC = src
OBJ = obj
BIN = bin

all: tproc

tproc: $(BIN)/tproc
$(BIN)/tproc: $(OBJ)/tproc.o $(OBJ)/jmp.o
		$(CC) -o $@ $< $(LDFLAGS)
$(OBJ)/tproc.o: $(SRC)/tproc.c $(INC)/tproc.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ)/jmp.o:	$(SRC)/jmp.c $(INC)/jmp.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ)/*.o
	rm -rf $(BIN)/*
	rm -rf $(SRC)/*~
	rm -rf $(INC)/*~
