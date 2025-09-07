#Makefile is for compiling and running a C++ program with arbitrary compiler
#I'll use clang++
CXX = clang++
# Compiler flags:
# -std=c++17   → Use C++17 standard
# -Wall        → Enable common warnings
# -Wextra      → Enable extra warnings
# -pedantic    → Enforce strict standard compliance
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Name of the final executable (the program we will run)
TARGET = main

# Collect all .cpp files in current directory
SRC = $(wildcard *.cpp)

#turn each .cpp into a corresponding .o object file
OBJ = $(SRC:.cpp=.o)
# Default target: when you just type "make"
# This will build the executable by depending on $(TARGET)
all: $(TARGET)

# Rule to build the target executable
# Takes the source file(s) and compiles them with clang++
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Run target: builds (if necessary) and then runs the program
run: $(TARGET)
	./$(TARGET)

# Clean target: remove compiled files (clean slate)
clean:
	rm -f $(TARGET) $(OBJ)
#make -> compiles main.cpp into 'main'
#make run -> compiles (if needed) and runs './main'
#make clean -> deletes 'main' executable
