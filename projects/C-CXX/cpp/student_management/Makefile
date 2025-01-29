# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -g

# Directories
SRC_DIR = src
OBG_DIR = obj

# Source files
SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/student.cpp $(SRC_DIR)/studentManager.cpp

# Object files
OBJ = $(OBG_DIR)/main.o $(OBG_DIR)/student.o $(OBG_DIR)/studentManager.o

# Executable
EXEC = student_management_program

# Default target: build the program
all: $(EXEC)

# Link object files into the final executable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBG_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up object files and the executable
clean:
	rm -rf $(OBG_DIR) $(EXEC)

# .PHONY targets (to avoid conflicts with files named clean or all)
.PHONY: all clean
