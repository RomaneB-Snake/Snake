CC=gcc
CFLAGS=-W -Wall -std=c99 -pedantic
LDFLAGS=-lMLV
EXEC=game
SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=bin/%.o)
BIN_DIR=bin

all: $(BIN_DIR) $(EXEC)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

bin/game.o: game.c grid.h getopt_long.h snake.h
	@$(CC) $(CFLAGS) -c game.c -o $@

bin/grid.o: grid.c grid.h
	@$(CC) $(CFLAGS) -c grid.c -o $@

bin/getopt_long.o: getopt_long.c getopt_long.h
	@$(CC) $(CFLAGS) -c getopt_long.c -o $@

bin/snake.o: snake.c snake.h grid.h
	@$(CC) $(CFLAGS) -c snake.c -o $@

.PHONY: clean mrproper

clean:
	@rm -rf $(BIN_DIR)

mrproper: clean
	@rm -rf $(EXEC)

