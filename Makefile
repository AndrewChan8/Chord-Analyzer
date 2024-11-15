# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

# Source files
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/linkedlist.c $(SRC_DIR)/chord.c $(SRC_DIR)/utils.c

# Object files (compiled .o files)
OBJ = $(SRC:.c=.o)

# Output executable
EXEC = chord_analyzer

# Default target: compile the program
all: $(EXEC)

# Link the object files into an executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(EXEC)

# Run the program
run: $(EXEC)
	./$(EXEC)

