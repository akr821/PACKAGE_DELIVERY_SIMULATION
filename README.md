# Package Delivery Simulation (Amazon Logistics Clone)

A comprehensive C++ terminal-based simulation project demonstrating all major Data Structures and Algorithms (DSA) concepts through a real-world package delivery system.

## Project Structure

This project is divided into 4 modules (one per team member):

1. **region_tree.cpp** - Tree data structure for hierarchical region management (Country → State → City)
2. **delivery_graph.cpp** - Graph (adjacency list) for delivery network and shortest path finding
3. **order_system.cpp** - Queue and Linked List for order management
4. **truck_route.cpp** - Stack data structure for truck loading and delivery routing

## Features

### Data Structures Used

- **Tree**: Region hierarchy with Country → State → City levels (using traversal algorithms)
- **Graph**: Delivery network with adjacency list representation and BFS for shortest path
- **Queue**: FIFO order management system for package processing
- **Stack**: LIFO truck loading system for reverse delivery routing
- **Linked List**: Package storage and tracking system

### Functionality

1. **Add Order**: Queue-based order creation with Linked List storage
2. **View Pending Orders**: Display orders in Queue order (FIFO)
3. **Dispatch Truck**: Stack-based delivery simulation (LIFO - last loaded, first delivered)
4. **Track Package**: Linked List search and status tracking
5. **View Region Tree**: Display hierarchical region structure with traversal
6. **Show Delivery Network**: Display graph connections and find shortest paths

## Compilation and Running

### Using Make (Recommended)

```bash
# Build the project
make

# Run the simulation
make run

# Clean build files
make clean
```

### Manual Compilation

```bash
# Compile all files
g++ -std=c++11 -Wall -o delivery_system.exe *.cpp

# Run the executable
./delivery_system.exe
```

## Usage

1. Run the executable to start the terminal-based interface
2. Select options from the menu (1-8)
3. Follow the prompts to:
   - Add new delivery orders
   - View pending orders in queue
   - Dispatch trucks with stack-based routing
   - Track packages using linked list search
   - View region hierarchies and delivery networks
4. Exit using option 8

## Requirements

- C++11 or higher
- G++ compiler (or any C++11 compatible compiler)
- Terminal/Command Prompt
- Make (optional, for easier compilation)

## Learning Outcomes

- Understanding of fundamental DSA concepts
- Implementation of 5 major data structures
- Real-world application of algorithms
- Terminal-based user interface design
- Object-oriented programming in C++
- File organization and modular code structure

