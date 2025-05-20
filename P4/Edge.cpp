#include "Edge.h"

// Constructor
Edge::Edge(const std::string& src, const std::string& dest, const std::string& lbl, double w)
    : sourceID(src), destID(dest), label(lbl), weight(w) {}

// Destructor (optional for future memory management)
Edge::~Edge() {}

// Getter for sourceID
std::string Edge::getSourceID() const {
    return sourceID;
}

// Getter for destID
std::string Edge::getDestID() const {
    return destID;
}

// Getter for label
std::string Edge::getLabel() const {
    return label;
}

// Getter for weight
double Edge::getWeight() const {
    return weight;
}

// Setter for label
void Edge::setLabel(const std::string& lbl) {
    label = lbl;
}

// Setter for weight
void Edge::setWeight(double w) {
    weight = w;
}
