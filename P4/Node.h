#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include "Edge.h"  // Include the Edge header to avoid circular dependency

class Node {
private:
    std::string identifier;
    std::string name;
    std::string type;
    std::vector<Edge*> adjacentEdges;  // Pointers to adjacent edges (instead of their IDs)
    double distance;  // Stores the distance from a node (initialized to -inf for max heap)
    Node* parent;  // Pointer to parent node 

public:
    Node(const std::string& id, const std::string& nm, const std::string& tp);
    ~Node();  // Destructor

    // Getter and Setter methods
    std::string getIdentifier() const;
    void setIdentifier(const std::string& id);
    
    std::string getName() const;
    void setName(const std::string& nm);

    std::string getType() const;
    void setType(const std::string& tp);

    // Add an adjacent edge by its pointer
    void addAdjacentEdge(Edge* adjacentEdge);

    // Getter for adjacent edges
    const std::vector<Edge*>& getAdjacentEdges() const;

    // Getter to edit adjacency list directly
    std::vector<Edge*>& getAdjacentEdgesEdit();

    // Getter and setter for distance (used in Dijkstra's algorithm)
    double getDistance() const;
    void setDistance(double dist);

    // Getter and setter for parent (used in Dijkstra's algorithm)
    Node* getParent() const;
    void setParent(Node* p);

    // Print method to display node details, for debug
    std::string toString() const;
};

#endif // NODE_H
