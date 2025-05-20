#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "Node.h"
#include "illegal_exception.h"

class Graph {
private:
    std::vector<Node> nodes;  // A collection of nodes in the graph.
    std::vector<Edge*> edges;  // A collection of edges in the graph.
    bool Invalid(const std::string& str) const;
    void removeFromAdjacencyList(std::vector<Edge*>& adjList, const std::string& id);
    void removeEdgesWithID(const std::string& id);
    void printPathRecursive(Node* currentNode);
    void Path_ModifiedDijkstra(const std::string& startID);

public:
    Graph();
    ~Graph();
    
    void addNode(const Node& newNode);
    void addEdge(const std::string& sourceID, const std::string& destID, const std::string& label, double weight);
    void Entity(const std::string& id, const std::string& name, const std::string& type);
    void Relationship(const std::string& sourceID, const std::string& destID, const std::string& label, double weight);
    void printAdjacent(const std::string& id) const;
    void deleteNode(const std::string& id);
    void findAll(const std::string& fieldType, const std::string& fieldString);
    void printPath(const std::string& startID, const std::string& endID);
    void HighestPath();
};

#endif // GRAPH_H
