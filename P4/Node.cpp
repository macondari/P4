#include "Node.h"
#include <cmath>

// Constructor
Node::Node(const std::string& id, const std::string& nm, const std::string& tp)
    : identifier(id), name(nm), type(tp), distance(-INFINITY), parent(nullptr) {}

// Destructor
Node::~Node() 
{
    adjacentEdges.clear();  // Simply clear the vector to release the pointers (no ownership here)
    parent = nullptr;  // Nullify the parent pointer
}

// Getter and Setter methods
std::string Node::getIdentifier() const 
{
    return identifier;
}

void Node::setIdentifier(const std::string& id) 
{
    identifier = id;
}

std::string Node::getName() const 
{
    return name;
}

void Node::setName(const std::string& nm) 
{
    name = nm;
}

std::string Node::getType() const 
{
    return type;
}

void Node::setType(const std::string& tp) 
{
    type = tp;
}

// Add an adjacent edge by its pointer
void Node::addAdjacentEdge(Edge* adjacentEdge) 
{
    // Avoid adding duplicate adjacent edges
    for (const auto& edge : adjacentEdges) 
    {
        if (edge == adjacentEdge) 
        {
            return;  // Edge is already adjacent, no need to add again
        }
    }
    adjacentEdges.push_back(adjacentEdge);  // Add the pointer to the adjacency list
}

// Getter for adjacent edges (constant for debugging)
const std::vector<Edge*>& Node::getAdjacentEdges() const 
{
    return adjacentEdges;
}

// Getter to edit adjacency list directly
std::vector<Edge*>& Node::getAdjacentEdgesEdit() 
{
    return adjacentEdges;
}

// Getter and setter for distance (used in Dijkstra's algorithm)
double Node::getDistance() const 
{
    return distance;
}

void Node::setDistance(double dist) 
{
    distance = dist;
}

// Getter and setter for parent (used in Dijkstra's algorithm)
Node* Node::getParent() const { return parent; }

void Node::setParent(Node* p) { parent = p; }

// Print method to display node details, for debug
std::string Node::toString() const 
{
    return "ID: " + identifier + ", Name: " + name + ", Type: " + type;
}
