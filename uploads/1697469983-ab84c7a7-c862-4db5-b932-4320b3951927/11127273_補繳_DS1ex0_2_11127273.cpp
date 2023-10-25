#include <iostream>   //任務2
#include <vector>
#include <fstream>

using namespace std;

void printMaze(const vector<vector<char>>& maze) {
    for (const auto& row : maze) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

bool solveMaze(vector<vector<char>>& maze, int N) {
    int currentTargets = 0;
    int row = 0, col = 0;

    while (currentTargets < N) {
        while (col < maze[0].size() && maze[row][col] != 'R') {
            if (maze[row][col] != 'V') {
                maze[row][col] = 'V';
                currentTargets++;
            }
            col++;
        }

        if (currentTargets == N) {
            maze[row][col - 1] = 'R';
            printMaze(maze);
            return true;
        }

        row++;
        while (row < maze.size() && maze[row][col - 1] != 'R') {
            if (maze[row][col - 1] != 'V') {
                maze[row][col - 1] = 'V';
                currentTargets++;
            }
            row++;
        }

        if (currentTargets == N) {
            maze[row - 1][col - 1] = 'R';  
            printMaze(maze);
            return true;
        }

        col--;
        while (col >= 0 && maze[row - 1][col] != 'R') {
            if (maze[row - 1][col] != 'V') {
                maze[row - 1][col] = 'V';
                currentTargets++;
            }
            col--;
        }

        if (currentTargets == N) {
            maze[row - 1][col + 1] = 'R';  
            printMaze(maze);
            return true;
        }

        row--;
        while (row >= 0 && maze[row][col + 1] != 'R') {
            if (maze[row][col + 1] != 'V') {
                maze[row][col + 1] = 'V';
                currentTargets++;
            }
            row--;
        }

        if (currentTargets == N) {
            maze[row + 1][col + 1] = 'R';  
            printMaze(maze);
            return true;
        }
    }

    return false;
}

int main() {
    int N;
    string mazeFileName;

    cout << "Enter a natural number N: ";
    cin >> N;

    cout << "Enter the maze file name: ";
    cin >> mazeFileName;

    ifstream inFile(mazeFileName);

    if (!inFile) {
        cerr << "Error opening file: " << mazeFileName << endl;
        return 1;
    }

    vector<vector<char>> maze;
    char cell;

    while (inFile >> cell) {
        if (cell == '\n') {
            continue; 
        }
        maze.push_back(vector<char>{cell});
    }

    if (!solveMaze(maze, N)) {
        cout << "No path found!" << endl;
    }

    inFile.close();
    return 0;
}
