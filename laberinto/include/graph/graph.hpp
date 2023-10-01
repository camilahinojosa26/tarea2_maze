#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>

class Graph {
private:
    std::unordered_map<int, std::vector<int>> adjacencyList;

public:
    Graph(); // Constructor
    void addEdge(int source, int destination);
    const std::unordered_map<int, std::vector<int>>& getAdjacencyList() const;
};

#endif // GRAPH_HPP
