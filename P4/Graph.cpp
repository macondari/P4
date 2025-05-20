#include "Graph.h"

using namespace std;

// Constructor: Initializes the graph.
Graph::Graph() 
{
}

// Destructor: Cleans up when the graph is destroyed.
Graph::~Graph() 
{
    for (auto& edge : edges) 
    {
        delete edge;
    }
    edges.clear();
    nodes.clear();
}

//function to be used with load entity command
void Graph::addNode(const Node& newNode) 
{
        for (auto& node : nodes) //check if node already exists
        {
            if (node.getIdentifier() == newNode.getIdentifier()) 
            {
                // Update the existing node's fields
                node.setName(newNode.getName());
                node.setType(newNode.getType());
                return; // update the existing node and finish
            }
        }
        // If no existing node add new node
        nodes.push_back(newNode);
    }
    
    
    
//function that works with relationship command   
void Graph::addEdge(const std::string& sourceID, const std::string& destID, const std::string& label, double weight) 
{
    // Check if the edge already exists between the two nodes
    for (auto& edge : edges) 
    {
        if ((edge->getSourceID() == sourceID && edge->getDestID() == destID) 
            || (edge->getSourceID() == destID && edge->getDestID() == sourceID)) //must checn both ways because unditedcted graph
              {
                // If edge exists update the label and weight
                edge->setLabel(label);
                edge->setWeight(weight); 
                return;
              }
    }

    // If the edge does not exist, create and add a new edge
    Edge* newEdge = new Edge(sourceID, destID, label, weight);  //create edge instance

    // Add the pointer to the new edge to the list edges for the graph
    edges.push_back(newEdge);

    // Update adjacency lists
    Node* sourceNode = nullptr;
    Node* destNode = nullptr;

    // Find nodes in the list of nodes by searching through ids
    for (auto& node : nodes) 
    {
        if (node.getIdentifier() == sourceID) 
        {
            sourceNode = &node;
        }
        if (node.getIdentifier() == destID) 
        {
            destNode = &node;
        }
    }
    if (sourceNode && destNode) // if we find both nodes in the graph
    {
        // Add newEdge to both source and destination nodes adjacency lists
        sourceNode->addAdjacentEdge(newEdge);  
        destNode->addAdjacentEdge(newEdge);
    }
}

//function to go with the entity command
void Graph::Entity(const std::string& id, const std::string& name, const std::string& type) 
    {
        // case if node already exists
        for (auto& node : nodes) 
        {
            if (node.getIdentifier() == id) 
            {
                // Update the existing node
                node.setName(name);
                node.setType(type);
                return;
            }
        }
        //case if it doesnt exist, create a new node
        Node newNode(id, name, type);
        nodes.push_back(newNode);
    }

//function that works with relationship command
void Graph::Relationship(const std::string& sourceID, const std::string& destID, const std::string& label, double weight) 
{
    // Check if both nodes exist
    Node* sourceNode = nullptr;
    Node* destNode = nullptr;

    for (auto& node : nodes) 
    {
        if (node.getIdentifier() == sourceID) 
        {
            sourceNode = &node;
        }
        if (node.getIdentifier() == destID) 
        {
            destNode = &node;
        }
        // exit search if both nodes are found
        if (sourceNode && destNode) 
        {
            break;
        }
    }

    // If either source or destination node is missing
    if (!sourceNode || !destNode) 
    {
        std::cout << "failure" << std::endl;
        return; // ends function
    }
    
    // case where both nodes exist in graph
    
    // Check if an edge already exists between the nodes
    for (auto& edge : edges) 
    {
        if ((edge->getSourceID() == sourceID && edge->getDestID() == destID) 
            || (edge->getSourceID() == destID && edge->getDestID() == sourceID)) 
            {
              // Update the existing edge
              edge->setLabel(label);
              edge->setWeight(weight);
  
              std::cout << "success" << std::endl; // Output success for update
              return;
            }
    }

    // case where no edge exists, so create new one
     Edge* newEdge = new Edge(sourceID, destID, label, weight);  //create edge instance

    // Add the pointer to the new edge to the list edges for the graph
    edges.push_back(newEdge);
    
    // Update adjacency lists
    sourceNode->addAdjacentEdge(newEdge);  
    destNode->addAdjacentEdge(newEdge);
    std::cout << "success" << std::endl; // Output success for addition
}

//used with Print command
void Graph::printAdjacent(const std::string& id) const 
{
    try {
          if (Invalid(id)) 
          {
              throw illegal_exception(); // Throw exception if ID is invalid
          }
  
          // Iterate through nodes to find the one with the correct id
          for (const Node& node : nodes) 
          {
              if (node.getIdentifier() == id) 
              {
                  // Get the list of edges adjacent to the node
                  const std::vector<Edge*>& adjacentEdges = node.getAdjacentEdges();
  
                  // Print adjacent nodes through edges
                  bool first = true; // Flag for spaces
                  for (int i = 0; i < adjacentEdges.size(); i++) 
                  {
                      const Edge* edge = adjacentEdges[i]; // assign first edge to an edge ptr
                      // If the edge's source is the current node, print the destination ID
                      if (edge->getSourceID() == id) // case #1 when source id is the id we want the adjacent of
                      {
                          if (!first) 
                          {
                              std::cout << " "; // Print space
                          }
                          std::cout << edge->getDestID(); // Print the destination ID of the edge
                          first = false; // After first node, ensure first is false
                      } 
                      if (edge->getDestID() == id) //case#2 when the dest id is the id we want the adjacent of
                      {
                          if (!first) 
                          {
                              std::cout << " "; // Print space before subsequent identifiers
                          }
                          std::cout << edge->getSourceID(); // Print the destination ID of the edge
                          first = false;
                      } 
                  }
                  // Print a newline at the end
                  std::cout << std::endl;
                  return;
              }
          }
          // Node not found
          std::cout << "failure" << std::endl;

    } catch (const illegal_exception& e) 
      {
          //catch invalid
          std::cout << e.illegal() << std::endl; // Output "illegal argument"
      }
}

//function used in try catch
bool Graph::Invalid(const std::string& str) const
{
        for (char ch : str) 
        { // Iterate through the string of chars
            if (!( (ch >= 65 && ch <= 90)  // A-Z
                || (ch >= 97 && ch <= 122)  // a-z
                || (ch >= 48 && ch <= 57)   // 0-9
                )) //ID invalid if contains any characters other than upper/lower case English letters and numerals. Whitespace will not be tested.
            {
                return true; // Invalid character found
            }
        }
        return false; // All characters are valid
}

// Helper function to remove an ID from adjacency list
void Graph::removeFromAdjacencyList(std::vector<Edge*>& adjList, const std::string& id)
{
    for (size_t i = 0; i < adjList.size(); ) 
    {
        // Check if the edge has deleted node
        if (adjList[i]->getSourceID() == id || adjList[i]->getDestID() == id) 
        {
            adjList.erase(adjList.begin() + i); // Remove the edge
        } 
        else 
        {
            ++i; // Only increment if no edge is erased b/c when edge erased indices of adj list will shift
        }
    }
}

// helper function to remove edges by ID, almost same code as above but w/ different purpose
void Graph::removeEdgesWithID(const std::string& id) 
{
    for (int i = 0; i < edges.size(); ) 
    {
        // Check if the edge has the deleted node
        if (edges[i]->getSourceID() == id || edges[i]->getDestID() == id) 
        {
            // Delete the dynamically allocated Edge object to avoid memory leak
            delete edges[i];
            
            // Remove the edge from the vector
            edges.erase(edges.begin() + i);
        } 
        else
        {
            ++i;
        }
    }
}

// Function to delete a node from the graph
void Graph::deleteNode(const std::string& id) 
{
    try 
      {
          if (Invalid(id)) 
            {
                throw illegal_exception(); // step 1: Check for illegal ID
            }
  
          // Check if the node exists
          Node* targetNode = nullptr; // Pointer to the target node
  
          for (Node& node : nodes) 
          {
              if (node.getIdentifier() == id) 
              {
                  targetNode = &node; // Found the node
                  break;
              }
          }
  
          if (!targetNode) 
          {
              std::cout << "failure" << std::endl; // Node not found
              return;
          }
  
          // Update adjacency lists
          // Loop through all nodes and remove any edges involving the deleted node
          for (auto& node : nodes) 
          {
              // Call helper function to remove the edges from the adjacency list of each node
              removeFromAdjacencyList(node.getAdjacentEdgesEdit(), id);
          }
  
          // Remove all edges involving the deleted node from the graph edge list
          removeEdgesWithID(id);
  
          // Delete the node itself from the node list
          for (size_t i = 0; i < nodes.size(); i++) 
          {
              if (nodes[i].getIdentifier() == id) 
              {
                  // Once the node is found, erase it from the vector of nodes
                  nodes.erase(nodes.begin() + i);
                  std::cout << "success" << std::endl; // Output success after removal
                  return; // Exit function after deletion
              }
          }
      } 
    catch (const illegal_exception& e) 
    {
        std::cout << e.illegal() << std::endl; //illegal argument
    }
}


//fcn for findall command
void Graph::findAll(const std::string& fieldType, const std::string& fieldString) 
{
    std::vector<std::string> uniqueEntities;  // Vector to hold stuff

    // Loop through all nodes
    for (const Node& node : nodes) 
    {
        bool isMatch = false;

        // step1: Check if the node matches the search criteria
        if ((fieldType == "name" && node.getName() == fieldString) || 
            (fieldType == "type" && node.getType() == fieldString)) 
        {
            isMatch = true;
        }

        if (isMatch) 
        {
            //step2: Check if the ID is already in vector
            bool alreadyExists = false;
            for (size_t i = 0; i < uniqueEntities.size(); i++) 
            {
                if (uniqueEntities[i] == node.getIdentifier()) 
                {
                    alreadyExists = true;
                    break;
                }
            }

            //step3: if not in vector, add it
            if (!alreadyExists) 
            {
                uniqueEntities.push_back(node.getIdentifier());
            }
        }
    }
    if (!uniqueEntities.empty())  //list has nodes to print
    {
        for (size_t i = 0; i < uniqueEntities.size(); i++) 
        {
            std::cout << uniqueEntities[i] << " ";
        }
        std::cout << std::endl;  // Print newline @ the end
    } 
    else
    {
        std::cout << "failure" << std::endl;
    }
}

void Graph::Path_ModifiedDijkstra(const std::string& startID) 
{
    // Initialize all nodes (lines 397-409, O(n) )
    for (Node& node : nodes) 
    {
        node.setDistance(-INFINITY);  // Set distance to -inf
        node.setParent(nullptr);      // No parent initially, nullptr
    }

    // Set the start node's distance to 0
    for (Node& node : nodes) 
    {
        if (node.getIdentifier() == startID) 
        {
            node.setDistance(0);
            break;
        }
    }

    // Max-heap using a vector, put all nodes in heap (+O(n))
    std::vector<Node*> maxHeap;
    for (Node& node : nodes) 
    {
        maxHeap.push_back(&node);
    }

    // Create the heap based on distances
/*
    CITATION:
    This function was created by me with the help of chat.openai.com using the prompt:
    "Teach me how to make a lambda function that works with the <algorithm>
    class's heap property."
    The AI tool provided an explanation of how lambda functions work in C++
    and demonstrated how to use a custom comparison lambda function with
    std::make_heap for a max-heap.
*/

    std::make_heap(maxHeap.begin(), maxHeap.end(), [](Node* a, Node* b) //(+O(n))
    {
        return a->getDistance() < b->getDistance();  // Max-heap comparison
    });

    std::vector<Node*> S;  // Vector to store visited nodes 

    // Main loop
    while (!maxHeap.empty()) // +(O(n) * ( O(logn) + En) ) = O(nlogn + E*n*n) = O(nlogn + EE) 
    {
        //configure pop heap to work for distances using lambda function
        std::pop_heap(maxHeap.begin(), maxHeap.end(), [](Node* a, Node* b) // pop heap is a logn function
        {
            return a->getDistance() < b->getDistance();
        });
        Node* u = maxHeap.back();
        maxHeap.pop_back();
        S.push_back(u); // push element onto list of visited nodes

        // Relax all adjacent edges of u
        const std::vector<Edge*>& adjList = u->getAdjacentEdges(); // get the list of adjacent edges
        for (Edge* edge : adjList) //runtime E * ( n + n + n + n) 
        {
              Node* v = nullptr; 
              //case where source id is u
              if (edge->getSourceID() == u->getIdentifier()) //runtime n
              {
                  for (Node& node : nodes) //find node for other id
                  {
                      if (node.getIdentifier() == edge->getDestID()) 
                      {
                          v = &node;
                          break;
                      }
                  }
              } 
              //case where dest id is u
              else if (edge->getDestID() == u->getIdentifier()) //runtime n
              {
                  for (Node& node : nodes) 
                  {
                      if (node.getIdentifier() == edge->getSourceID()) //find node for other id
                      {
                          v = &node;
                          break;
                      }
                  }
              }
  
              // Skip if v is already visited
              if (v && std::find(S.begin(), S.end(), v) == S.end()) // runtime of up to n-1            
              {  // v is not in visited set S
                  double newDist = u->getDistance() + edge->getWeight();
                  if (newDist > v->getDistance()) 
                  {
                      v->setDistance(newDist); // update distance
                      v->setParent(u);  // Set the parent as a pointer to the current node
  
                      // Re-adjust heap after updating v's distance
                      std::make_heap(maxHeap.begin(), maxHeap.end(), [](Node* a, Node* b) // runtime of n
                      {
                          return a->getDistance() < b->getDistance();
                      });
                  }
              }
        }
    }
}
//fcn that responds to command for print
void Graph::printPath(const std::string& startID, const std::string& endID) 
{
    // Call Dijkstra w/ start id
    Path_ModifiedDijkstra(startID);

    // Find the end node by ID
    Node* endNode = nullptr;
    for (Node& node : nodes) 
    {
        if (node.getIdentifier() == endID) 
        {
            endNode = &node;
            break;
        }
    }

    if (endNode == nullptr || endNode->getParent() == nullptr) 
    {
    
        std::cout<< "failure" <<std::endl;  // No path found or no parent, exit without printing anything
        return;
    }
    // Print the path by recursively calling the parent node
    printPathRecursive(endNode);

    // After printing the path, print the total weight (distance)
    std::cout << " " << endNode->getDistance() << std::endl;  // Total weight of the path
}

// Recursive helper function to print the path
/*
  CITATION:
  This function was modified by chat.openai.com with the prompt:
  "My code is printing the path from the end node to the start node instead
  of from the start node to the end node. Can you help me fix this?"
  The AI tool adjusted the logic by ensuring the recursive function traverses
  to the parent node first before printing, correcting the order of the output.
*/
void Graph::printPathRecursive(Node* currentNode) 
{
    if (currentNode == nullptr) 
    {
        return;  // Base case; if no parent, end recursion
    }

    // Recursively call for the parent node first 
    if (currentNode->getParent() != nullptr) 
    {
        printPathRecursive(currentNode->getParent());
        std::cout << " ";  // space between node IDs
    }

    // Print the current node's identifier
    std::cout << currentNode->getIdentifier();
}

void Graph::HighestPath() 
{
    //store the highest weight node IDs to print
    double highestWeight = -INFINITY; // set as inf to start to make sure weights accurately recorded
    std::string startIDWithHighestPath;
    std::string endIDWithHighestPath;

    // Iterate through all nodes in the graph
    for (const Node& startNode : nodes) 
    {
        // Call Dijkstra from the current node
        Path_ModifiedDijkstra(startNode.getIdentifier());

        // Check all nodes to find the maximum distance that was generated from dijkstra
        for (const Node& endNode : nodes) 
        {
            if (endNode.getDistance() > highestWeight) 
            {
                // Update the highest weight and store the start and end node IDs
                highestWeight = endNode.getDistance();
                startIDWithHighestPath = startNode.getIdentifier();
                endIDWithHighestPath = endNode.getIdentifier();
            }
        }
    }

    // Print the result
    if (highestWeight > -INFINITY) 
    {
        std::cout << startIDWithHighestPath << " " << endIDWithHighestPath <<" " << highestWeight << std::endl;
    } 
    else 
    {
        std::cout << "failure";
    }
}


