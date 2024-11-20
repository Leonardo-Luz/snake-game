# Compiler and flags
CC=gcc                # Use GCC as the compiler
CFLAGS=-Wall -g       # Compiler flags (enable warnings, include debug info)

# Libraries
LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11  # Raylib and system libraries

# Source and output
SRC=./src/game.c ./src/player.c ./src/food.c ./src/score.c           # Source file
OBJ=$(SRC:.c=.o)     # Object file (game.c -> game.o)
EXEC=game            # Name of the executable

# Default target (build the executable)
all: $(EXEC)

# Link the object files into the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

# Compile the source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJ) $(EXEC)

# Run the program
run: $(EXEC)
	./$(EXEC)
