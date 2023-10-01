#include "graph/graph.hpp"

// Constructor to initialize the graph
Graph::Graph() {
    adjacencyList.clear();
}

// Method to add an edge to the graph
void Graph::addEdge(int source, int destination) {
    adjacencyList[source].push_back(destination);
    adjacencyList[destination].push_back(source); // For an undirected graph
}

// Method to retrieve the adjacency list
const std::unordered_map<int, std::vector<int>>& Graph::getAdjacencyList() const {
    return adjacencyList;
}
