CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = `pkg-config --cflags --libs gtk+-3.0`

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = app

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean