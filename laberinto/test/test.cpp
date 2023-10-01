// #include <iostream>
// #include "maze/maze.hpp"
// #include "graph/graph.hpp"

// int main(int nargs, char** vargs){
// 	maze::Maze laberinto(21,21);
// 	laberinto.print();


// 	return 0;
// }
/*
#include <iostream>
#include "maze/maze.hpp"
#include "graph/graph.hpp"

int main(int nargs, char** vargs) {
    // Create a maze
    maze::Maze laberinto(21, 21);

    // Print the maze
    std::cout << "Maze:" << std::endl;
    laberinto.print();

    // Transform the maze into a graph
    Graph graph;

    // Extract maze data and populate the graph (assuming a method to do this)
    // For example:
    const std::vector<std::vector<unsigned char>>& mazeData = laberinto.getMazeData();
    for (int i = 0; i < mazeData.size(); i++) {
        for (int j = 0; j < mazeData[i].size(); j++) {
            if (mazeData[i][j] == maze::Maze::EMPTY) {
                // Add edges based on maze structure, e.g., connecting adjacent empty cells
                // Example:
                int nodeIndex = i * laberinto.getWidth() + j;

                // Connect to the cell above
                if (i > 0 && mazeData[i - 1][j] == maze::Maze::EMPTY) {
                    int neighborIndex = (i - 1) * laberinto.getWidth() + j;
                    graph.addEdge(nodeIndex, neighborIndex);
                }

                // Connect to the cell below, left, and right similarly
            }
        }
    }

    // Print the adjacency list of the graph
    const std::unordered_map<int, std::vector<int>>& adjacencyList = graph.getAdjacencyList();
    std::cout << "\nAdjacency List of the Graph:" << std::endl;
    for (const auto& [node, neighbors] : adjacencyList) {
        std::cout << "Node " << node << " is connected to: ";
        for (int neighbor : neighbors) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
*/

#include "maze/maze.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <queue>

int main(int nargs, char** vargs) {
    // Resto de tu código
    // Crear un laberinto
    maze::Maze laberinto(21, 21);

    // Imprimir el laberinto
    std::cout << "Laberinto:" << std::endl;
    laberinto.print();

    // Llamar a la función solve_pila para encontrar el camino
    std::vector<std::pair<int, int>> solutionPila = laberinto.solve_pila(0, 0, laberinto.getHeight() - 1, laberinto.getWidth() - 1);

    // Marcar y mostrar el camino en el laberinto
    laberinto.markPath(solutionPila); // Marcar el camino de la pila

    // Imprimir el laberinto con el camino marcado
    std::cout << "Laberinto con Solución (Pila):" << std::endl;
    laberinto.print();

    return 0;
}
