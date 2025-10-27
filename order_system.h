#ifndef ORDER_SYSTEM_H
#define ORDER_SYSTEM_H

#include <iostream>
#include <string>
#include <queue>

// Linked List Node for Package
class PackageNode {
public:
    int orderID;
    std::string customerName;
    std::string address;
    std::string destination;
    std::string status;
    PackageNode* next;
    
    PackageNode(int id, std::string name, std::string addr, std::string dest);
};

// Linked List for Package Management
class PackageList {
private:
    PackageNode* head;
    int count;
    
public:
    PackageList();
    ~PackageList();
    void addPackage(int id, std::string name, std::string addr, std::string dest);
    void updateStatus(int id, std::string status);
    PackageNode* search(int id);
    void displayAll();
    void displayPending();
    bool isEmpty();
    int getCount();
};

// Queue for Order Management
class OrderQueue {
private:
    std::queue<int> orderQueue;  // Queue to maintain FIFO order
    PackageList* packageList;    // Linked list to store package details
    
    static int nextOrderID;
    
public:
    OrderQueue();
    ~OrderQueue();
    int createOrder(std::string name, std::string addr, std::string dest);
    int getNextOrder();
    void processNextOrder();
    void displayQueue();
    void trackPackage(int orderID);
    PackageNode* getPackage(int orderID);
    bool hasOrders();
};

#endif

