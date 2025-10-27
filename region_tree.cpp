#include "region_tree.h"
#include <iostream>
#include <functional>

// RegionNode Constructor
RegionNode::RegionNode(std::string n, std::string t) : name(n), type(t) {}

// RegionNode Destructor - recursively delete children
RegionNode::~RegionNode() {
    for (RegionNode* child : children) {
        delete child;
    }
}

// Add a child node to this region
void RegionNode::addChild(RegionNode* child) {
    children.push_back(child);
}

// Display the tree using pre-order traversal
void RegionNode::display(int level) {
    // Print indentation based on level
    for (int i = 0; i < level; i++) {
        std::cout << "  ";
    }
    
    // Print node with type indicator
    std::cout << "|-- " << name << " (" << type << ")" << std::endl;
    
    // Recursively display all children (DFS traversal)
    for (RegionNode* child : children) {
        child->display(level + 1);
    }
}

// RegionTree Constructor
RegionTree::RegionTree() {
    root = new RegionNode("Global", "root");
}

// RegionTree Destructor
RegionTree::~RegionTree() {
    if (root) {
        delete root;
    }
}

// Helper function for recursive search
RegionNode* searchRegion(RegionNode* node, std::string name, std::string type) {
    if (node->name == name && node->type == type) {
        return node;
    }
    for (RegionNode* child : node->children) {
        RegionNode* result = searchRegion(child, name, type);
        if (result) return result;
    }
    return nullptr;
}

// Find a region node by name and type
RegionNode* RegionTree::findRegion(std::string name, std::string type) {
    if (!root) return nullptr;
    return searchRegion(root, name, type);
}

// Add a region to the tree hierarchy
void RegionTree::addRegion(std::string country, std::string state, std::string city) {
    if (!root) return;
    
    // Find or create country
    RegionNode* countryNode = findRegion(country, "country");
    if (!countryNode) {
        countryNode = new RegionNode(country, "country");
        root->addChild(countryNode);
    }
    
    // If state is provided
    if (!state.empty()) {
        RegionNode* stateNode = nullptr;
        for (RegionNode* child : countryNode->children) {
            if (child->name == state && child->type == "state") {
                stateNode = child;
                break;
            }
        }
        
        if (!stateNode) {
            stateNode = new RegionNode(state, "state");
            countryNode->addChild(stateNode);
        }
        
        // If city is provided
        if (!city.empty()) {
            bool cityExists = false;
            for (RegionNode* child : stateNode->children) {
                if (child->name == city && child->type == "city") {
                    cityExists = true;
                    break;
                }
            }
            
            if (!cityExists) {
                RegionNode* cityNode = new RegionNode(city, "city");
                stateNode->addChild(cityNode);
            }
        }
    }
}

// Display the entire tree
void RegionTree::displayTree() {
    if (!root) {
        std::cout << "Region tree is empty!\n" << std::endl;
        return;
    }
    
    std::cout << "\n========== REGION HIERARCHY (TREE) ==========" << std::endl;
    root->display();
    std::cout << "\n=============================================\n" << std::endl;
}

