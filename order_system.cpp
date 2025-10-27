#include "order_system.h"
#include <iostream>
#include <iomanip>

// Static variable initialization
int OrderQueue::nextOrderID = 1001;

// PackageNode Constructor
PackageNode::PackageNode(int id, std::string name, std::string addr, std::string dest) 
    : orderID(id), customerName(name), address(addr), destination(dest), status("Pending"), next(nullptr) {}

// PackageList Constructor
PackageList::PackageList() : head(nullptr), count(0) {}

// PackageList Destructor
PackageList::~PackageList() {
    PackageNode* current = head;
    while (current != nullptr) {
        PackageNode* next = current->next;
        delete current;
        current = next;
    }
}

// Add a package to the linked list
void PackageList::addPackage(int id, std::string name, std::string addr, std::string dest) {
    PackageNode* newNode = new PackageNode(id, name, addr, dest);
    
    if (head == nullptr) {
        head = newNode;
    } else {
        PackageNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    count++;
}

// Search for a package by ID
PackageNode* PackageList::search(int id) {
    PackageNode* current = head;
    while (current != nullptr) {
        if (current->orderID == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Update package status
void PackageList::updateStatus(int id, std::string status) {
    PackageNode* pkg = search(id);
    if (pkg) {
        pkg->status = status;
    }
}

// Display all packages
void PackageList::displayAll() {
    if (head == nullptr) {
        std::cout << "No packages in system." << std::endl;
        return;
    }
    
    std::cout << "\n========== ALL PACKAGES ==========" << std::endl;
    std::cout << std::left << std::setw(10) << "Order ID" 
              << std::setw(20) << "Customer" 
              << std::setw(20) << "Destination" 
              << std::setw(15) << "Status" << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
    
    PackageNode* current = head;
    while (current != nullptr) {
        std::cout << std::setw(10) << current->orderID
                  << std::setw(20) << current->customerName
                  << std::setw(20) << current->destination
                  << std::setw(15) << current->status << std::endl;
        current = current->next;
    }
    std::cout << "===================================\n" << std::endl;
}

// Display only pending packages
void PackageList::displayPending() {
    if (head == nullptr) {
        std::cout << "No pending orders." << std::endl;
        return;
    }
    
    std::cout << "\n========== PENDING ORDERS (QUEUE) ==========" << std::endl;
    std::cout << std::left << std::setw(10) << "Order ID" 
              << std::setw(20) << "Customer" 
              << std::setw(25) << "Address" 
              << std::setw(20) << "Destination" 
              << std::setw(15) << "Status" << std::endl;
    std::cout << "-----------------------------------------------------------------------" << std::endl;
    
    PackageNode* current = head;
    while (current != nullptr) {
        if (current->status == "Pending") {
            std::cout << std::setw(10) << current->orderID
                      << std::setw(20) << current->customerName
                      << std::setw(25) << current->address
                      << std::setw(20) << current->destination
                      << std::setw(15) << current->status << std::endl;
        }
        current = current->next;
    }
    std::cout << "\n=============================================\n" << std::endl;
}

// Check if list is empty
bool PackageList::isEmpty() {
    return head == nullptr;
}

// Get count
int PackageList::getCount() {
    return count;
}

// OrderQueue Constructor
OrderQueue::OrderQueue() {
    packageList = new PackageList();
}

// OrderQueue Destructor
OrderQueue::~OrderQueue() {
    delete packageList;
}

// Create a new order (add to queue and linked list)
int OrderQueue::createOrder(std::string name, std::string addr, std::string dest) {
    int orderID = nextOrderID++;
    orderQueue.push(orderID);
    packageList->addPackage(orderID, name, addr, dest);
    return orderID;
}

// Get the next order ID without processing
int OrderQueue::getNextOrder() {
    if (orderQueue.empty()) {
        return -1;
    }
    return orderQueue.front();
}

// Process the next order from queue
void OrderQueue::processNextOrder() {
    if (!orderQueue.empty()) {
        int orderID = orderQueue.front();
        orderQueue.pop();
        packageList->updateStatus(orderID, "Processing");
    }
}

// Display the order queue
void OrderQueue::displayQueue() {
    packageList->displayPending();
}

// Track a specific package
void OrderQueue::trackPackage(int orderID) {
    PackageNode* pkg = packageList->search(orderID);
    if (pkg) {
        std::cout << "\n========== PACKAGE TRACKING ==========" << std::endl;
        std::cout << "Order ID: " << pkg->orderID << std::endl;
        std::cout << "Customer: " << pkg->customerName << std::endl;
        std::cout << "Address: " << pkg->address << std::endl;
        std::cout << "Destination: " << pkg->destination << std::endl;
        std::cout << "Status: " << pkg->status << std::endl;
        std::cout << "=====================================\n" << std::endl;
    } else {
        std::cout << "Order ID " << orderID << " not found!" << std::endl;
    }
}

// Get package by ID
PackageNode* OrderQueue::getPackage(int orderID) {
    return packageList->search(orderID);
}

// Check if queue has orders
bool OrderQueue::hasOrders() {
    return !orderQueue.empty();
}

