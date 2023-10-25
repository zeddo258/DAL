#include <iostream>
#include <fstream>
#include <vector>
#include <set>  // Add set to keep track of visited goal nodes

using namespace std;

class Maze {

    private:

        vector<vector<char>> maze;
        vector<vector<char>> visitedMaze;
        vector<vector<char>> pathMaze;
        int numRows;
        int numCols;
        int numGoals;
        int foundGoals;
        set<pair<int, int>> visitedGoals;  // Store visited goal nodes
        // stores 3 matrices, original maze, visited node display, and path display
        // in the form of 2D vectors

    public:

        Maze(const string & filename) { // Maze constructor

            ifstream inputFile(filename); // reads the input test data
            if (!inputFile) {

                cerr << "Error: Cannot open file." << endl;
                exit(1);
            }

        // reads value of N, then column and row, lastly the maze
        // inputFile works similarly to cin
        // read data is stored into 3 maze vectors

        inputFile >> numGoals;
        inputFile >> numCols >> numRows;
        maze.resize(numRows, vector<char>(numCols));
        visitedMaze.resize(numRows, vector<char>(numCols));
        pathMaze.resize(numRows, vector<char>(numCols));
        // rows and columns is set in each matrix

        for (int i = 0; i < numRows; ++i) {

            for (int j = 0; j < numCols; ++j) {

                inputFile >> maze[i][j];
                visitedMaze[i][j] = maze[i][j];
                pathMaze[i][j] = maze[i][j];
                // Initialize both matrices with original maze's nodes

            }
        }

        inputFile.close(); // initialization done
        foundGoals = 0;
    }

    void printMaze(const vector<vector<char>>& maze) {

        for (int i = 0; i < numRows; ++i) {

            for (int j = 0; j < numCols; ++j)
                cout << maze[i][j] ;

            cout << endl;
        }

    } // displays the matrix

    void solveMaze() {

        /* cout << "Initial Maze:" << endl;
        printMaze(maze); */

        findGoals(0, 0);
        // cout << "Visited Maze:" << endl;
        cout << "\n" ;
        printMaze(visitedMaze);

        if (foundGoals == numGoals) {

            foundGoals = 0;
            // cout << "Path Maze:" << endl;
            cout << "\n" ;
            findPaths(0, 0);
            printMaze(pathMaze);

        }

    } // displays each matrix when the process is done

private:

    bool isSafe(int x, int y) {
        return (x >= 0 && x < numRows && y >= 0 && y < numCols && maze[x][y] != 'O');
    } // if the node is walkable

    void findGoals(int x, int y) {

        if (foundGoals == numGoals)
            return; // stops when N goals are found

        /* if (visitedMaze[x][y] != 'V' && maze[x][y] == 'G')
            foundGoals++; // found a goal */

        if ( visitedMaze[x][y] == 'G' && visitedGoals.find({x, y}) == visitedGoals.end()) {
            foundGoals++;
            visitedGoals.insert({x, y});  // Mark the goal node as visited
        }

        if ( visitedMaze[x][y] != 'G') // mark non-goal nodes as visited
            visitedMaze[x][y] = 'V';

        int dx[] = {0, 1, 0, -1};  // direction to right, down, left, up
        int dy[] = {1, 0, -1, 0};

        for (int i = 0; i < 4; ++i) {

            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isSafe(newX, newY) && visitedMaze[newX][newY] != 'V') // walkable and not visited yet
                findGoals(newX, newY);

        } // turn directions when blocked

    } // for marking all possible visited nodes

    bool findPaths(int x, int y) {

        if (x == numRows - 1 && y == numCols - 1)
            return true; // every node is visited

        if ( pathMaze[x][y] != 'G' )
            pathMaze[x][y] = 'R' ;

        int dx[] = {0, 1, 0, -1}; // direction to right, down, left, up
        int dy[] = {1, 0, -1, 0};

        for (int i = 0; i < 4; ++i) {

            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols &&
                maze[newX][newY] != 'O' && pathMaze[newX][newY] != 'R') {

                if (findPaths(newX, newY))
                    return true;

            }
        }

        if ( pathMaze[x][y] != 'G' )
            pathMaze[x][y] = 'E';

        return false;
    }
};

int main() {

    Maze maze("C:\\Users\\jin08\\Documents\\input103.txt");
    maze.solveMaze();
    return 0;
    // read the input data, being the solution process, then display the result
}
