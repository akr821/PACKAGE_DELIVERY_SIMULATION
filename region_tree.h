#ifndef REGION_TREE_H
#define REGION_TREE_H

#include <iostream>
#include <string>
#include <vector>

// Tree Node Structure for Region Hierarchy
class RegionNode {
public:
    std::string name;              // Region name (Country/State/City)
    std::string type;              // "country", "state", or "city"
    std::vector<RegionNode*> children; // Children nodes
    
    RegionNode(std::string n, std::string t);
    ~RegionNode();
    void addChild(RegionNode* child);
    void display(int level = 0);
};

// Tree Class for Region Management
class RegionTree {
private:
    RegionNode* root;
    
public:
    RegionTree();
    ~RegionTree();
    void addRegion(std::string country, std::string state = "", std::string city = "");
    void displayTree();
    RegionNode* findRegion(std::string name, std::string type);
};

#endif

