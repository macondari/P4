#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"  // Assuming you have a Graph class header

using namespace std;

int main() 
{
    string cmd;
    Graph graph;  // Create an instance of the Graph class

    // Start reading commands
    while (cin >> cmd) 
    {
        if (cmd == "LOAD") 
        {
            string filename, type;
            cin >> filename;  // Read the filename to load entities from
            cin >> type;      // Read the type of data (should be "entities")
            

            if (type == "relationships") 
            {
                // Load relationships (edges) from file
                ifstream file(filename);
                string line;
                while (getline(file, line)) 
                {
                    stringstream ss(line);
                    string sourceID, destID, label;
                    double weight;
                    ss >> sourceID >> label >> destID >> weight;

                    // Add the relationship (edge) to the graph
                    graph.addEdge(sourceID, destID, label, weight);
                }
                file.close();
            }
            else if (type == "entities")
            {
                // Open the file
                ifstream file(filename);
                string line;
                while (getline(file, line)) 
                {
                    stringstream ss(line);
                    string id, name, nodeType;
                    ss >> id >> name >> nodeType;

                    // Create a new Node object
                    Node newNode(id, name, nodeType);

                    // Insert the node into the graph
                    graph.addNode(newNode);
                }
                file.close();
            }
            cout << "success" << endl; // always outputs success no matter what
        }
        else if (cmd == "ENTITY")
        {
            string id;
            string name;
            string type;
            std::cin >> id >> name >> type;
            graph.Entity(id, name, type);
            std::cout << "success" << std::endl; // always prints success
        }
        else if (cmd == "RELATIONSHIP")
        {
            string srcID;
            string label;
            string destID;
            double w;
            std::cin >> srcID >> label >> destID >> w ;
            graph.Relationship(srcID, destID, label, w);

        }
        else if (cmd == "PRINT") 
        {
            string id;
            std::cin >> id; // Read the ID to print adjacent vertices for
            graph.printAdjacent(id);
        }
        else if (cmd == "DELETE") 
        {
            string id;
            std::cin >> id;
            graph.deleteNode(id);
        }
        else if (cmd == "PATH") 
        {
            string id1;
            string id2;
            std::cin >> id1 >> id2;
            graph.printPath(id1,id2);
        }
        else if (cmd == "HIGHEST") 
        {
            graph.HighestPath();
        }
        else if (cmd == "FINDALL") 
        {
            string Field_type;
            string Field_string;
            std::cin >> Field_type >> Field_string;
            graph.findAll(Field_type, Field_string);
        }
        else if (cmd == "EXIT") 
        {
            return 0;
        }
    }

    return 0;
}
