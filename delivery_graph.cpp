#include "delivery_graph.h"
#include <iostream>
#include <algorithm>

// Constructor
DeliveryGraph::DeliveryGraph() {
    // Initialize with some default locations
    addLocation("Warehouse");
    addLocation("Distribution Center");
    addLocation("Hub-1");
    addLocation("Hub-2");
    addLocation("Hub-3");
    
    // Create initial connections
    addEdge("Warehouse", "Distribution Center", 30);
    addEdge("Distribution Center", "Hub-1", 15);
    addEdge("Distribution Center", "Hub-2", 20);
    addEdge("Distribution Center", "Hub-3", 25);
    addEdge("Hub-1", "Hub-2", 10);
    addEdge("Hub-2", "Hub-3", 12);
}

// Add a location to the graph
void DeliveryGraph::addLocation(std::string location) {
    if (!exists(location)) {
        locations.push_back(location);
        graph[location] = std::vector<Edge>();
    }
}

// Check if location exists
bool DeliveryGraph::exists(std::string location) {
    return graph.find(location) != graph.end();
}

// Add an edge (bidirectional)
void DeliveryGraph::addEdge(std::string from, std::string to, int weight) {
    if (!exists(from)) addLocation(from);
    if (!exists(to)) addLocation(to);
    
    Edge edge1, edge2;
    edge1.destination = to;
    edge1.weight = weight;
    edge2.destination = from;
    edge2.weight = weight;
    
    graph[from].push_back(edge1);
    graph[to].push_back(edge2);
}

// Display the graph structure
void DeliveryGraph::displayGraph() {
    std::cout << "\n========== DELIVERY NETWORK (GRAPH) ==========" << std::endl;
    
    for (auto& pair : graph) {
        std::cout << pair.first << " -> ";
        if (pair.second.empty()) {
            std::cout << "No connections";
        } else {
            for (size_t i = 0; i < pair.second.size(); i++) {
                std::cout << pair.second[i].destination 
                          << "(" << pair.second[i].weight << " km)";
                if (i < pair.second.size() - 1) std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    
    std::cout << "\n==============================================\n" << std::endl;
}

// Get all locations
std::vector<std::string> DeliveryGraph::getAllLocations() {
    return locations;
}

// Find shortest path using BFS (simplified)
std::vector<std::string> DeliveryGraph::shortestPath(std::string from, std::string to) {
    std::vector<std::string> path;
    
    if (!exists(from) || !exists(to)) {
        path.push_back("Path not found");
        return path;
    }
    
    if (from == to) {
        path.push_back(from);
        return path;
    }
    
    std::queue<std::string> q;
    std::map<std::string, bool> visited;
    std::map<std::string, std::string> parent;
    
    visited[from] = true;
    q.push(from);
    
    while (!q.empty()) {
        std::string current = q.front();
        q.pop();
        
        for (const Edge& edge : graph[current]) {
            if (!visited[edge.destination]) {
                visited[edge.destination] = true;
                parent[edge.destination] = current;
                q.push(edge.destination);
                
                if (edge.destination == to) {
                    // Build path
                    std::string node = to;
                    while (node != from) {
                        path.push_back(node);
                        node = parent[node];
                    }
                    path.push_back(from);
                    std::reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
    }
    
    path.push_back("No path exists");
    return path;
}

