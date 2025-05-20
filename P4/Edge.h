#ifndef EDGE_H
#define EDGE_H

#include <string>

class Edge {
private:
    std::string sourceID;      // Identifier for the source node
    std::string destID;        // Identifier for the destination node
    std::string label;         // Label describing the relationship
    double weight;             // Weight of the edge (strength of the relationship)

public:
    // Constructor
    Edge(const std::string& src, const std::string& dest, const std::string& lbl, double w);

    // Destructor (optional for future memory management)
    ~Edge();

    // Getter for sourceID
    std::string getSourceID() const;

    // Getter for destID
    std::string getDestID() const;

    // Getter for label
    std::string getLabel() const;

    // Getter for weight
    double getWeight() const;

    // Setter for label
    void setLabel(const std::string& lbl);

    // Setter for weight
    void setWeight(double w);
};

#endif // EDGE_H
