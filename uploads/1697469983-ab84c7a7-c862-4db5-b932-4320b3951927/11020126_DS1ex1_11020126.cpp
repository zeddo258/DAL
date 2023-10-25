// 電資三 11020126 鄭祐昀
// 使用C++11

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

// Print the menu and read in the command and handle the case where the command is wrong
void GetCommand(int &command)
{
    cout << "\n";
    cout << "*** Path Finding **\n";
    cout << "* 0. Quit         *\n";
    cout << "* 1. One Goal     *\n";
    cout << "* 2. More Goals   *\n";
    cout << "*******************\n";
    cout << "Input a command(0, 1, 2): ";
    cin >> command;

    // Invalid command, re-enter
    if (command != 0 && command != 1 && command != 2) {
        printf("Command does not exist!\n");
        GetCommand(command);
    } else {
        return;
    }
}

void Inputtxt(ifstream &inputFile, int &x, int &y)
{
    string filename;
    cout << "Please enter the file number: ";
    cin >> filename;
    filename = "input" + filename + ".txt";
    inputFile.open(filename);
    if (!inputFile) {
        cout << "Unable to open file " << filename << endl;
        exit(1);
    } else {
        inputFile >> x >> y;
    }
}

// MazwCell class
class MazeCell
{
    char cellType;
    bool visited;
    bool path;
    public:
        MazeCell(char cellType='E'): cellType(cellType), visited(false), path(false){}
        char getCellType() { return this->cellType; }
        bool isVisited() { return this->visited; }
        void setVisited() { this->visited = true; }

        void setPath() { this->path = true; }
        bool isPath() { return this->path; }
};

// Maze class
class Maze
{
    MazeCell **maze;
    int width, height;
    public:
        Maze(int w, int h): width(w), height(h) {
            maze = new MazeCell *[h];
            for(int i = 0; i < h; i++) maze[i] = new MazeCell [w];
        }
    void setMazeCell(int x, int y, char type) { maze[x][y] = MazeCell(type); }
    MazeCell& getMazeCell(int x, int y) { return maze[y][x]; }
    bool findPath(int x, int y, int dir = 0);
    bool findMultiPath(int x, int y, int &remainingGoals, int dir = 0);
    void printMaze(bool visitedOnly = false);
};

bool Maze::findPath(int x, int y, int dir)
{
    if(x < 0 || y < 0 || y >= this->height || x >= this->width) return false;
    if(getMazeCell(x, y).getCellType() == 'O' || getMazeCell(x, y).isVisited()) return false;
    getMazeCell(x, y).setVisited();
    if(getMazeCell(x, y).getCellType() == 'G') return true;

    // Define the four directions, 0 is to the right, 1 is down, 2 is left, and 3 is up.
    static const int dx[4] = { 1, 0, -1, 0 };
    static const int dy[4] = { 0, 1, 0, -1 };

    for(int i = 0; i < 4; i++) {
        dir = (dir + i) % 4;
        if(findPath(x + dx[dir], y + dy[dir], dir)) {
            getMazeCell(x, y).setPath();
            return true;
        }
    }

    return false;
}

bool Maze::findMultiPath(int x, int y, int &remainingGoals, int dir)
{
    if(x < 0 || y < 0 || y >= this->height || x >= this->width) return false;
    if(getMazeCell(x, y).getCellType() == 'O' || getMazeCell(x, y).isVisited()) return false;

    getMazeCell(x, y).setVisited();

    if(getMazeCell(x, y).getCellType() == 'G') {
        remainingGoals--;
        if(remainingGoals == 0) return true;
    }

    static const int dx[4] = { 1, 0, -1, 0 };
    static const int dy[4] = { 0, 1, 0, -1 };

    for(int i = 0; i < 4; i++) {
        dir = (dir + i) % 4;
        if(findMultiPath(x + dx[dir], y + dy[dir], remainingGoals, dir)) {
            getMazeCell(x, y).setPath();
            return true;
        }
    }

    return remainingGoals == 0;
}

void Maze::printMaze(bool visitedOnly)
{
    cout << "=========" << "\n";
    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {

            // If it is a target point, output 'G'
            if(maze[i][j].getCellType() == 'G') {cout << 'G'; continue;}

            // Prioritize the path taken (whether it is the correct path or not)
            if(maze[i][j].isVisited()) {cout << 'V'; continue;}

            // Finally, determine whether it is an obstacle, and treat other cases as spaces
            maze[i][j].getCellType() == 'O' ? cout << 'O' : cout << 'E';
        }
        cout << "\n";
    }

    // Return here if only the path taken needs to be output
    if(visitedOnly) return;

    cout << "=========" << "\n";

    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {

            // If it is a target point or on the correct path, output the corresponding character
            if(maze[i][j].getCellType() == 'G') {cout << 'G'; continue;}
            if(maze[i][j].isPath()) {cout << 'R'; continue;}

            // Other cases are treated as spaces or obstacles
            maze[i][j].getCellType() == 'O' ? cout << 'O' : cout << 'E';
        }
        cout << "\n";
    }
}

int main()
{
    while(true)
    {
        int command;
        GetCommand(command);
        if(command == 0) break;

        ifstream inputFile;
        int w, h;
        Maze* maze;

        switch(command) {
            case 1: // One Goal
                // Read the file
                Inputtxt(inputFile, w, h);
                maze = new Maze(w, h); // Initialize the maze
                cout << "Maze size: " << w << " x " << h << "\n";

                // Read the contents of the .txt file into the maze
                for (int y = 0; y < h; y++) {
                    for (int x = 0; x < w; x++) {
                        char ch;
                        inputFile >> ch;
                        maze->setMazeCell(y, x, ch);
                    }
                }
                inputFile.close();

                // Print the maze and find the path
                if (maze->findPath(0, 0)) {
                    maze->printMaze(false);
                } else {
                    maze->printMaze(true);
                }
                delete maze;
                break;
            case 2: // More Goals
                int N; // number of goals
                cout << "Please enter the number of goals: ";
                cout << "N = ";
                cin >> N;
                Inputtxt(inputFile, w, h);
                maze = new Maze(w, h); // Initialize the maze
                cout << "Maze size: " << w << " x " << h << "\n";

                // Read the contents of the .txt file into the maze
                for (int y = 0; y < h; y++) {
                    for (int x = 0; x < w; x++) {
                        char ch;
                        inputFile >> ch;
                        maze->setMazeCell(y, x, ch);
                    }
                }
                inputFile.close();

                // Print the maze and find the path
                if (maze->findMultiPath(0, 0, N)) {
                    maze->printMaze(false);
                } else {
                    maze->printMaze(true);
                }
                delete maze;
                break;
            default:
                std::cout << "Invalid command";
                return 1;
        }
    }

    return 0;
}
