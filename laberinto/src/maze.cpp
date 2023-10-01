// #include "maze/maze.hpp"
// #include <cstdlib>
// #include <ctime>
// #include <iostream>

// namespace maze{

// const unsigned char Maze::WALL  = '@';
// const unsigned char Maze::EMPTY = '-';
// const int Maze::NORTH= 0;
// const int Maze::SOUTH= 1;
// const int Maze::EAST= 2;
// const int Maze::WEST= 3;
// Maze::Maze(int h, int w):
// 		height(h),
// 		width(w),
// 		grid(nullptr){
// 	dir[0] = NORTH;
// 	dir[1] = SOUTH;
// 	dir[2] = EAST;
// 	dir[3] = WEST;
// 	std::srand(time(0));
// 	generate_maze(h, w);

// }

// void Maze::reset_maze(int h, int w){
// 	delete_maze();
// 	height = h;
// 	width= w;
// 	grid = new uchar*[height];
// 	for (int i = 0; i < height; i++){
// 		grid[i] = new uchar[width];
// 		for (int j = 0; j < width; j++){
// 			grid[i][j] = 1;
// 		}
// 	}
// }

// void Maze::generate_maze(int h, int w){
// 	reset_maze(h, w);
// 	visit(0,0);
// }

// void Maze::delete_maze(){
// 	if (grid != nullptr){
// 		for (int i = 0; i < height; i++){
// 			delete[] grid[i];
// 		}
// 		delete[] grid;
// 	}
// }

// void Maze::shuffle_dir(){
// 	for (int i = 0; i < 4; i++){
// 		int r = std::rand() & 3;
// 		int aux = dir[r];
// 		dir[r] = dir[i];
// 		dir[i] = aux;
// 	 }
// }
// bool Maze::inRange(int i, int j){
// 	return ((i >= 0) && (i< height) && (j >= 0) && (j< width));
// }

// void Maze::visit(int i, int j){

// 	int dx  = 0;
// 	int dy = 0;
// 	int i_next = 0;
// 	int j_next = 0;
// 	grid[i][j] = 0;
// 	shuffle_dir();
// 	//std::cout << dir[0] << " " << dir[1] << " " << dir[2] << " "<< dir[3] << std::endl;
// 	for(int k = 0; k <  4; k++){
// 		//std::cout << dir[k] << std::endl;
// 		if (dir[k] == NORTH){
// 			dy = -1;
// 			dx = 0;
// 		}
// 		else if (dir[k] == SOUTH){
// 			dy = 1;
// 			dx = 0;
// 		}
// 		else if (dir[k] == EAST){
// 			dy = 0;
// 			dx = 1;
// 		}
// 		else if (dir[k] == WEST){
// 			dy = 0;
// 			dx = -1;
// 		}
// 		i_next = i + (dy<<1);
// 		j_next = j + (dx<<1);
// 		if (inRange(i_next, j_next) && grid[i_next][j_next] == 1){
// 			grid[i_next - dy][j_next - dx] = 0;
// 			visit(i_next, j_next);

// 		}
// 	}
// }

// void Maze::print(){
// 	char LIMIT = '=';
// 	std::cout << " Maze ( "<< height << " x " << width << " ) " << std::endl;
// 	std::cout << " ";
// 	for (int j = 0; j < width; j++){
// 		std::cout << LIMIT;
// 	}
// 	std::cout << " ";
// 	std::cout << std::endl;
// 	for (int i = 0; i < height; i++){
// 		std::cout << "|";
// 		for (int j = 0; j < width; j++){
// 			if (grid[i][j] == 0) {
// 				std::cout << EMPTY;
// 			}
// 			else {
// 				std::cout << WALL;
// 			}
// 		}
// 		std::cout << "|";
// 		std::cout << std::endl;
// 	}
// 	std::cout << " ";
// 	for (int j = 0; j < width; j++){
// 		std::cout << LIMIT;
// 	}
// 	std::cout << " ";
// 	std::cout << std::endl;
// }

// }

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
                std::cout << EMPTY;
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
    std::vector<std::pair<int, int>> solution;

    // Matriz para marcar las celdas visitadas
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    // Definición de movimientos posibles (arriba, abajo, izquierda, derecha)
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    pila.push(std::make_pair(f1, c1));
    visited[f1][c1] = true;

    while (!pila.empty()) {
        std::pair<int, int> current = pila.top();
        pila.pop();

        // Comprobar si hemos llegado al punto de destino (f2, c2)
        if (current.first == f2 && current.second == c2) {
            while (!pila.empty()) {
                solution.push_back(pila.top());
                pila.pop();
            }
            solution.push_back(current);
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nextRow = current.first + dy[i];
            int nextCol = current.second + dx[i];

            if (inRange(nextRow, nextCol) && mazeData[nextRow][nextCol] == 0 && !visited[nextRow][nextCol]) {
                pila.push(std::make_pair(nextRow, nextCol));
                visited[nextRow][nextCol] = true;
            }
        }
    }

    return solution;
    }

std::vector<std::pair<int, int>> Maze::solve_cola(int f1, int c1, int f2, int c2) {
    std::queue<std::pair<int, int>> cola;
    std::vector<std::pair<int, int>> solution;

    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    cola.push(std::make_pair(f1, c1));
    visited[f1][c1] = true;

    while (!cola.empty()) {
        std::pair<int, int> current = cola.front();
        cola.pop();
        if (current.first == f2 && current.second == c2) {
            // Construir la solución siguiendo el camino desde la matriz de visitados
            std::pair<int, int> backtrack = current;
            while (backtrack != std::make_pair(f1, c1)) {
                solution.push_back(backtrack);
                int nextRow = backtrack.first;
                int nextCol = backtrack.second;
                for (int i = 0; i < 4; i++) {
                    int newRow = nextRow + dy[i];
                    int newCol = nextCol + dx[i];
                    if (inRange(newRow, newCol) && visited[newRow][newCol] && mazeData[newRow][newCol] == 0) {
                        backtrack = std::make_pair(newRow, newCol);
                        break;
                    }
                }
            }
            solution.push_back(std::make_pair(f1, c1));
            std::reverse(solution.begin(), solution.end());
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nextRow = current.first + dy[i];
            int nextCol = current.second + dx[i];

            if (inRange(nextRow, nextCol) && mazeData[nextRow][nextCol] == 0 && !visited[nextRow][nextCol]) {
                cola.push(std::make_pair(nextRow, nextCol));
                visited[nextRow][nextCol] = true;
            }
        }
    }

    return solution;
}

} // namespace maze

