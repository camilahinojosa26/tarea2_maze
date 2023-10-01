// /**
//  * Classe Maze
//  */

// namespace maze {
// 	typedef unsigned char uchar;


// 	class Maze{
// 	private:
// 		uchar**  grid;
// 		int width;
// 		int height;
// 		int dir[4];
// 		void shuffle_dir();
// 		void delete_maze();
// 		void visit(int i, int j);
// 	public:
// 		static const unsigned char WALL;
// 		static const unsigned char EMPTY;
// 		static const int NORTH;
// 		static const int SOUTH;
// 		static const int EAST;
// 		static const int WEST;
// 		Maze(int h, int  w);
// 		void generate_maze(int h, int w);
// 		void reset_maze(int h, int w);
// 		bool inRange(int i, int j);
// 		void print();

// 	};
// }

#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>  // Include the vector header for maze data storage
#include <unordered_map>  // Include the unordered_map header for the adjacency list

namespace maze {
    typedef unsigned char uchar;

    class Maze {
    private:
        std::vector<std::vector<uchar>> mazeData;  // Use a vector of vectors to store maze data
        int width;
        int height;
        int dir[4];
        void shuffle_dir();
        void delete_maze();
        void visit(int i, int j);
        std::unordered_map<int, std::vector<int>> adjacencyList;  // Adjacency list for the graph representation

    public:
        static const unsigned char WALL;
        static const unsigned char EMPTY;
        static const int NORTH;
        static const int SOUTH;
        static const int EAST;
        static const int WEST;

        Maze(int h, int w);
        void generate_maze(int h, int w);
        void reset_maze(int h, int w);
        bool inRange(int i, int j);
        void print();

        // Getter methods for maze data, width, height, and adjacency list
        const std::vector<std::vector<uchar>>& getMazeData() const;
        int getWidth() const;
        int getHeight() const;
        const std::unordered_map<int, std::vector<int>>& getAdjacencyList() const;
    };
}

#endif // MAZE_HPP

