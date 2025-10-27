#include "truck_route.h"
#include <iostream>
#include <algorithm>

// TruckRoute Constructor
TruckRoute::TruckRoute() : truckCapacity(10), currentLoad(0) {}

// Add a single delivery address to the stack
void TruckRoute::addDelivery(std::string address) {
    if (!isFull()) {
        deliveryStack.push(address);
        currentLoad++;
    } else {
        std::cout << "Truck is full! Cannot add more deliveries." << std::endl;
    }
}

// Load multiple packages onto the truck
void TruckRoute::loadPackages(std::vector<std::string> addresses) {
    for (const std::string& addr : addresses) {
        if (!isFull()) {
            deliveryStack.push(addr);
            currentLoad++;
        } else {
            std::cout << "Truck is full after loading " << currentLoad << " packages." << std::endl;
            break;
        }
    }
}

// Get the delivery route (stack converted to vector)
std::vector<std::string> TruckRoute::getDeliveryRoute() {
    std::vector<std::string> route;
    std::stack<std::string> temp = deliveryStack;
    
    // Since stack is LIFO, we need to reverse it to show the route
    while (!temp.empty()) {
        reverseStack.push(temp.top());
        temp.pop();
    }
    
    while (!reverseStack.empty()) {
        route.push_back(reverseStack.top());
        reverseStack.pop();
    }
    
    return route;
}

// Simulate the delivery process
void TruckRoute::simulateDelivery() {
    std::cout << "\n========== DELIVERY SIMULATION (STACK) ==========" << std::endl;
    std::cout << "Truck starting with " << currentLoad << " packages..." << std::endl;
    std::cout << "Delivering packages in reverse order (Stack - LIFO):\n" << std::endl;
    
    int deliveryNum = 1;
    while (!deliveryStack.empty()) {
        std::string address = deliveryStack.top();
        deliveryStack.pop();
        currentLoad--;
        
        std::cout << deliveryNum << ". Delivering to: " << address << std::endl;
        std::cout << "   [Status: Delivered ✓]" << std::endl;
        completedDeliveries.push_back(address);
        deliveryNum++;
    }
    
    std::cout << "\nAll deliveries completed! Truck is empty." << std::endl;
    std::cout << "\n===============================================\n" << std::endl;
}

// Display the planned route
void TruckRoute::displayRoute() {
    if (deliveryStack.empty()) {
        std::cout << "No packages loaded on truck." << std::endl;
        return;
    }
    
    std::cout << "\n========== TRUCK ROUTE (STACK - LIFO) ==========" << std::endl;
    std::cout << "Truck Load: " << currentLoad << "/" << truckCapacity << " packages" << std::endl;
    std::cout << "\nDelivery order (will be delivered in REVERSE order):" << std::endl;
    
    std::stack<std::string> temp = deliveryStack;
    std::vector<std::string> displayOrder;
    
    // Copy to show loading order
    while (!temp.empty()) {
        displayOrder.push_back(temp.top());
        temp.pop();
    }
    
    std::reverse(displayOrder.begin(), displayOrder.end());
    
    for (size_t i = 0; i < displayOrder.size(); i++) {
        std::cout << "  [" << (i + 1) << "] " << displayOrder[i] 
                  << " [Delivered " << (displayOrder.size() - i) << "]" << std::endl;
    }
    
    std::cout << "\n================================================\n" << std::endl;
}

// Check if truck is full
bool TruckRoute::isFull() {
    return currentLoad >= truckCapacity;
}

// Get current load
int TruckRoute::getCurrentLoad() {
    return currentLoad;
}

// Get capacity
int TruckRoute::getCapacity() {
    return truckCapacity;
}

// Empty the truck
void TruckRoute::emptyTruck() {
    while (!deliveryStack.empty()) {
        deliveryStack.pop();
    }
    currentLoad = 0;
    completedDeliveries.clear();
}

