#include "maze/maze.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <queue>

namespace maze {

const unsigned char Maze::WALL = '@';
const unsigned char Maze::EMPTY = '-';
const int Maze::NORTH = 0;
const int Maze::SOUTH = 1;
const int Maze::EAST = 2;
const int Maze::WEST = 3;

Maze::Maze(int h, int w) : height(h), width(w), mazeData(h, std::vector<uchar>(w, WALL)) {
    dir[0] = NORTH;
    dir[1] = SOUTH;
    dir[2] = EAST;
    dir[3] = WEST;
    std::srand(time(0));
    generate_maze(h, w);
}

void Maze::reset_maze(int h, int w) {
    delete_maze();
    height = h;
    width = w;
    mazeData = std::vector<std::vector<uchar>>(h, std::vector<uchar>(w, WALL));
    adjacencyList.clear(); // Clear the adjacency list when resetting the maze
}

void Maze::generate_maze(int h, int w) {
    reset_maze(h, w);
    visit(0, 0);
}

void Maze::delete_maze() {
    // No need to delete mazeData; it's managed by std::vector
}

void Maze::shuffle_dir() {
    for (int i = 0; i < 4; i++) {
        int r = std::rand() & 3;
        int aux = dir[r];
        dir[r] = dir[i];
        dir[i] = aux;
    }
}

bool Maze::inRange(int i, int j) {
    return ((i >= 0) && (i < height) && (j >= 0) && (j < width));
}

void Maze::visit(int i, int j) {
    int dx = 0;
    int dy = 0;
    int i_next = 0;
    int j_next = 0;
    mazeData[i][j] = EMPTY; // Update mazeData to mark this cell as empty

    shuffle_dir();

    for (int k = 0; k < 4; k++) {
        if (dir[k] == NORTH) {
            dy = -1;
            dx = 0;
        } else if (dir[k] == SOUTH) {
            dy = 1;
            dx = 0;
        } else if (dir[k] == EAST) {
            dy = 0;
            dx = 1;
        } else if (dir[k] == WEST) {
            dy = 0;
            dx = -1;
        }

        i_next = i + (dy << 1);
        j_next = j + (dx << 1);

        if (inRange(i_next, j_next) && mazeData[i_next][j_next] == WALL) {
            mazeData[i_next - dy][j_next - dx] = EMPTY; // Update mazeData to mark the wall cell as empty
            visit(i_next, j_next);

            // Update the adjacency list to represent the graph
            int current_node = i * width + j;
            int next_node = i_next * width + j_next;

            adjacencyList[current_node].push_back(next_node);
            adjacencyList[next_node].push_back(current_node);
        }
    }
}

void Maze::print() {
    char LIMIT = '=';
    std::cout << "Laberinto:" << std::endl;
    std::cout << " Maze ( " << height << " x " << width << " ) " << std::endl;
    std::cout << " ";
    for (int j = 0; j < width; j++) {
        std::cout << LIMIT;
    }
    std::cout << " ";
    std::cout << std::endl;
    for (int i = 0; i < height; i++) {
        std::cout << "|";
        for (int j = 0; j < width; j++) {
            if (mazeData[i][j] == EMPTY) {
                std::cout << '-'; // Use 'x' to mark the path
            } else {
                std::cout << WALL;
            }
        }
        std::cout << "|";
        std::cout << std::endl;
    }
    std::cout << " ";
    for (int j = 0; j < width; j++) {
        std::cout << LIMIT;
    }
    std::cout << " ";
    std::cout << std::endl;
}


// Implement the getter methods
const std::vector<std::vector<uchar>>& Maze::getMazeData() const {
    return mazeData;
}

int Maze::getWidth() const {
    return width;
}

int Maze::getHeight() const {
    return height;
}

const std::unordered_map<int, std::vector<int>>& Maze::getAdjacencyList() const {
    return adjacencyList;
}

std::vector<std::pair<int, int>> Maze::solve_pila(int f1, int c1, int f2, int c2) {
    std::stack<std::pair<int, int>> pila;
    pila.push(std::make_pair(f1, c1));

    std::vector<std::vector<int>> visited(height, std::vector<int>(width, 0));
    visited[f1][c1] = 1;

    std::vector<std::pair<int, int>> path; // Store the path

    while (!pila.empty()) {
        std::pair<int, int> coord = pila.top();
        int row = coord.first;
        int col = coord.second;

        if (row == f2 && col == c2) {
            // We reached the destination, reconstruct the path
            while (!(row == f1 && col == c1)) {
                path.push_back(std::make_pair(row, col));
                int next_row = row - dir[visited[row][col]];
                int next_col = col - dir[(visited[row][col] + 1) % 4];
                row = next_row;
                col = next_col;
            }
            path.push_back(std::make_pair(f1, c1));
            std::reverse(path.begin(), path.end()); // Reverse the path to start from (f1, c1)
            break;
        }

        bool found = false;
        for (int i = 0; i < 4; i++) {
            int newRow = row + dir[i];
            int newCol = col + dir[(i + 1) % 4];

            if (inRange(newRow, newCol) && mazeData[newRow][newCol] == EMPTY && visited[newRow][newCol] == 0) {
                pila.push(std::make_pair(newRow, newCol));
                visited[newRow][newCol] = (i + 2) % 4; // Store the direction to backtrack
                found = true;
                break; // Only move in one direction
            }
        }

        if (!found) {
            // Backtrack if no forward path is available
            pila.pop();
        }
    }

    return path;
}



/*
std::vector<std::pair<int, int>> Maze::solve_cola(int f1, int c1, int f2, int c2) {
    std::queue<std::pair<int, int>> cola;
    cola.push(std::make_pair(f1, c1));

    std::vector<std::pair<int, int>> path; // Store the path

    // Create a copy of the maze to work on without modifying the original
    std::vector<std::vector<uchar>> mazeCopy = mazeData;

    while (!cola.empty()) {
        std::pair<int, int> coord = cola.front();
        int row = coord.first;
        int col = coord.second;

        if (row == f2 && col == c2) {
            // We reached the destination, add the step to the path
            path.push_back(std::make_pair(row, col));
            break;
        }

        for (int i = 0; i < 4; i++) {
            int newRow = row + dir[i];
            int newCol = col + dir[(i + 1) % 4];

            if (inRange(newRow, newCol) && mazeCopy[newRow][newCol] == EMPTY) {
                cola.push(std::make_pair(newRow, newCol));
                mazeCopy[newRow][newCol] = 'x'; // Mark the path in the maze copy
            }
        }

        cola.pop();
    }

    // Mark the path in the original maze
    markPath(path);

    return path;
}
*/

void Maze::markPath(const std::vector<std::pair<int, int>>& path) {
    for (const auto& step : path) {
        int row = step.first;
        int col = step.second;
        mazeData[row][col] = EMPTY; // Mark the path with 'x'
    }
}



} // namespace maze

