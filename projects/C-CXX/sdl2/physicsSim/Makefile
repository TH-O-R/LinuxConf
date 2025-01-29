CC = gcc
CFLAGS = -g -Wall
LIBS = -lSDL2 -lm

SRC = src/main.c src/physics.c
OBJ = $(SRC:.c=.o)
EXEC = physics_sim

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
