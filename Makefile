# Makefile for Package Delivery Simulation
# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Executable name
TARGET = delivery_system.exe

# Source files
SOURCES = main.cpp region_tree.cpp delivery_graph.cpp order_system.cpp truck_route.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = region_tree.h delivery_graph.h order_system.h truck_route.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "======================================"
	@echo "Build successful! Run with: ./$(TARGET)"
	@echo "======================================"

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Cleaned build files!"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Help
help:
	@echo "Available targets:"
	@echo "  make       - Build the project"
	@echo "  make run   - Build and run the project"
	@echo "  make clean - Remove build files"
	@echo "  make help  - Show this help"

.PHONY: all clean run help

