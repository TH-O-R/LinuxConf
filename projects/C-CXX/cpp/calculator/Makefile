# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -g

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/calculator.cpp

# Object files
OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/calculator.o

# Executable
EXEC = calc

# Targets
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)

.PHONY: all clean
