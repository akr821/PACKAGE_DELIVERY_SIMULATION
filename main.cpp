#include "region_tree.h"
#include "delivery_graph.h"
#include "order_system.h"
#include "truck_route.h"
#include <iostream>
#include <string>
#include <vector>

// Function to display main menu
void displayMenu() {
    std::cout << "\nPACKAGE DELIVERY SIMULATION (Amazon Logistics Clone)" << std::endl;
    std::cout << "\n1.  Add Order" << std::endl;
    std::cout << "2.  View Pending Orders" << std::endl;
    std::cout << "3.  Dispatch Truck" << std::endl;
    std::cout << "4.  Track Package" << std::endl;
    std::cout << "5.  View Region Tree" << std::endl;
    std::cout << "6.  Show Delivery Network" << std::endl;
    std::cout << "7.  View All Data Structures" << std::endl;
    std::cout << "8.  Exit" << std::endl;
    std::cout << "\nSelect an option: ";
}

// Function to clear screen (works on Windows and Unix)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    // Initialize all data structures
    RegionTree* regionTree = new RegionTree();
    DeliveryGraph* deliveryGraph = new DeliveryGraph();
    OrderQueue* orderQueue = new OrderQueue();
    TruckRoute* truckRoute = new TruckRoute();
    
    // Initialize some sample data
    std::cout << "Initializing Delivery System..." << std::endl;
    
    // Add sample regions to tree
    regionTree->addRegion("India", "Maharashtra", "Mumbai");
    regionTree->addRegion("India", "Maharashtra", "Pune");
    regionTree->addRegion("India", "Karnataka", "Bangalore");
    regionTree->addRegion("India", "Delhi", "New Delhi");
    regionTree->addRegion("India", "Gujarat", "Ahmedabad");
    regionTree->addRegion("USA", "California", "Los Angeles");
    regionTree->addRegion("USA", "California", "San Francisco");
    regionTree->addRegion("USA", "New York", "New York City");
    
    // Add sample orders to queue
    orderQueue->createOrder("Rajesh Kumar", "123 MG Road", "Mumbai");
    orderQueue->createOrder("Priya Sharma", "456 Park Avenue", "Pune");
    orderQueue->createOrder("Amit Patel", "789 Main Street", "Bangalore");
    
    std::cout << "System initialized successfully!" << std::endl;
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
    
    int choice;
    bool running = true;
    
    while (running) {
        clearScreen();
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                // Add Order - Uses Queue and Linked List
                std::string name, address, destination;
                std::cin.ignore(); // Clear buffer
                
                std::cout << "\n=== ADD NEW ORDER ===" << std::endl;
                std::cout << "Customer Name: ";
                std::getline(std::cin, name);
                std::cout << "Address: ";
                std::getline(std::cin, address);
                std::cout << "Destination: ";
                std::getline(std::cin, destination);
                
                int orderID = orderQueue->createOrder(name, address, destination);
                std::cout << "\n✓ Order created successfully!" << std::endl;
                std::cout << "Order ID: " << orderID << std::endl;
                
                // Add to region tree if needed
                if (destination.find("Mumbai") != std::string::npos) {
                    regionTree->addRegion("India", "Maharashtra", "Mumbai");
                } else if (destination.find("Pune") != std::string::npos) {
                    regionTree->addRegion("India", "Maharashtra", "Pune");
                } else if (destination.find("Bangalore") != std::string::npos) {
                    regionTree->addRegion("India", "Karnataka", "Bangalore");
                }
                
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            }
            
            case 2: {
                // View Pending Orders - Queue
                orderQueue->displayQueue();
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            }
            
            case 3: {
                // Dispatch Truck - Stack
                if (!orderQueue->hasOrders()) {
                    std::cout << "\nNo pending orders to dispatch!" << std::endl;
                    std::cout << "Press Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }
                
                std::cout << "\n=== DISPATCHING TRUCK ===" << std::endl;
                
                // Load packages onto truck (using stack)
                std::vector<std::string> addresses;
                int count = std::min(5, static_cast<int>(orderQueue->hasOrders() ? 5 : 0));
                
                for (int i = 0; i < count && orderQueue->hasOrders(); i++) {
                    int orderID = orderQueue->getNextOrder();
                    if (orderID != -1) {
                        PackageNode* pkg = orderQueue->getPackage(orderID);
                        if (pkg) {
                            addresses.push_back(pkg->address + ", " + pkg->destination);
                            orderQueue->processNextOrder();
                        }
                    }
                }
                
                truckRoute->loadPackages(addresses);
                truckRoute->displayRoute();
                truckRoute->simulateDelivery();
                
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            }
            
            case 4: {
                // Track Package - Linked List
                int orderID;
                std::cout << "\nEnter Order ID to track: ";
                std::cin >> orderID;
                orderQueue->trackPackage(orderID);
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            }
            
            case 5: {
                // View Region Tree - Tree Traversal
                regionTree->displayTree();
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            }
            
            case 6: {
                // Show Delivery Network - Graph
                deliveryGraph->displayGraph();
                
                std::cout << "Example: Finding path from Warehouse to Hub-1..." << std::endl;
                std::vector<std::string> path = deliveryGraph->shortestPath("Warehouse", "Hub-1");
                std::cout << "Path: ";
                for (size_t i = 0; i < path.size(); i++) {
                    std::cout << path[i];
                    if (i < path.size() - 1) std::cout << " -> ";
                }
                std::cout << std::endl;
                
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            }
            
            case 7: {
                // View All Data Structures
                std::cout << "\n\n";
                regionTree->displayTree();
                deliveryGraph->displayGraph();
                std::cout << "\n=== ORDER SYSTEM (Queue + Linked List) ===" << std::endl;
                orderQueue->displayQueue();
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            }
            
            case 8: {
                running = false;
                std::cout << "\nShutting down delivery system..." << std::endl;
                break;
            }
            
            default:
                std::cout << "\nInvalid option! Please try again." << std::endl;
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
        }
    }
    
    // Cleanup
    delete regionTree;
    delete deliveryGraph;
    delete orderQueue;
    delete truckRoute;
    
    std::cout << "Thank you for using Package Delivery Simulation!" << std::endl;
    return 0;
}

