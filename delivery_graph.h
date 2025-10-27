#ifndef DELIVERY_GRAPH_H
#define DELIVERY_GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <limits>

// Edge structure for graph
struct Edge {
    std::string destination;
    int weight;  // Time or distance
};

// Graph class using adjacency list representation
class DeliveryGraph {
private:
    std::map<std::string, std::vector<Edge>> graph;  // Adjacency list
    std::vector<std::string> locations;
    
public:
    DeliveryGraph();
    void addLocation(std::string location);
    void addEdge(std::string from, std::string to, int weight);
    void displayGraph();
    std::vector<std::string> shortestPath(std::string from, std::string to);
    bool exists(std::string location);
    std::vector<std::string> getAllLocations();
};

#endif

