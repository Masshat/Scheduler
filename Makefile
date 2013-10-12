CC      = gcc
CFLAGS  = -Wall -Werror -I$(INC) -g -ansi -DDEBUG
LDFLAGS = #

INC = include
SRC = src
OBJ = obj
BIN = bin

all: main

main: $(BIN)/main
$(BIN)/main: $(OBJ)/jmp.o $(OBJ)/tproc.o  $(OBJ)/main.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ)/tproc.o: $(SRC)/tproc.c $(INC)/tproc.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ)/jmp.o: $(SRC)/jmp.c $(INC)/jmp.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ)/*.o
	rm -rf $(BIN)/*
	rm -rf $(SRC)/*~
	rm -rf $(INC)/*~
