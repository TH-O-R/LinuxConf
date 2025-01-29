# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g  # Enable C++17, all warnings, and debugging symbols

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# File names
TARGET = open_world_rpg

# Sources and objects
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
HEADERS = $(wildcard $(INC_DIR)/*.h)

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each source file to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)  # Ensure the object directory exists
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean object files and the executable
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Phony targets (not actual files)
.PHONY: all clean

