#ifndef TRUCK_ROUTE_H
#define TRUCK_ROUTE_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>

// Truck Route Manager using Stack
class TruckRoute {
private:
    std::stack<std::string> deliveryStack;  // Stack to store delivery route
    std::stack<std::string> reverseStack;   // Helper stack for reversing
    std::vector<std::string> completedDeliveries;
    int truckCapacity;
    int currentLoad;
    
public:
    TruckRoute();
    void addDelivery(std::string address);
    void loadPackages(std::vector<std::string> addresses);
    std::vector<std::string> getDeliveryRoute();
    void simulateDelivery();
    void displayRoute();
    bool isFull();
    int getCurrentLoad();
    int getCapacity();
    void emptyTruck();
};

#endif

