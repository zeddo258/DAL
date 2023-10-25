#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

class MazeCell {
public:
    char type;
    bool visited;
    bool path;

    MazeCell(char cellType = 'E') : type(cellType), visited(false), path(false) {}
};

class Maze {
public:
    vector<vector<MazeCell>> maze;

    Maze(int w, int h) : maze(h, vector<MazeCell>(w)) {}

    void setMazeCell(int x, int y, char type) {
        maze[y][x].type = type;
    }

    const MazeCell& getMazeCell(int x, int y) const {
        return maze[y][x];
    }

    bool findPath(int x, int y);
    bool findMultiPath(int x, int y, int &remainingGoals);
    int findShortestPath();
    void printMaze(bool visitedOnly = false) const;
};

bool Maze::findPath(int x, int y) {
    if (x < 0 || y < 0 || y >= maze.size() || x >= maze[0].size()) return false;
    if (maze[y][x].type == 'O' || maze[y][x].visited) return false;
    maze[y][x].visited = true;
    if (maze[y][x].type == 'G') return true;

    static const int dx[4] = {1, 0, -1, 0};
    static const int dy[4] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++) {
        if (findPath(x + dx[i], y + dy[i])) {
            maze[y][x].path = true;
            return true;
        }
    }

    return false;
}

bool Maze::findMultiPath(int x, int y, int &remainingGoals) {
    if (x < 0 || y < 0 || y >= maze.size() || x >= maze[0].size()) return false;
    if (maze[y][x].type == 'O' || maze[y][x].visited) return false;

    maze[y][x].visited = true;

    if (maze[y][x].type == 'G') {
        remainingGoals--;
        if (remainingGoals == 0) return true;
    }

    static const int dx[4] = {1, 0, -1, 0};
    static const int dy[4] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++) {
        if (findMultiPath(x + dx[i], y + dy[i], remainingGoals)) {
            maze[y][x].path = true;
            return true;
        }
    }

    return remainingGoals == 0;
}


void Maze::printMaze(bool visitedOnly) const {
    cout << "=========\n";
    for (const auto &row : maze) {
        for (const auto &cell : row) {
            if (cell.type == 'G') {
                cout << 'G';
            } else if (cell.visited) {
                cout << 'V';
            } else {
                cell.type == 'O' ? cout << 'O' : cout << 'E';
            }
        }
        cout << "\n";
    }

    if (visitedOnly) return;

    cout << "=========\n";

    for (const auto &row : maze) {
        for (const auto &cell : row) {
            if (cell.type == 'G') {
                cout << 'G';
            } else if (cell.path) {
                cout << 'R';
            } else {
                cell.type == 'O' ? cout << 'O' : cout << 'E';
            }
        }
        cout << "\n";
    }
}

int main() {
    while (true) {
        int command;
        cout << "\n*** Path Finding ***\n";
        cout << "* 0. Quit          *\n";
        cout << "* 1. One Goal      *\n";
        cout << "* 2. More Goals    *\n";
        cout << "* 3. Shortest Path *\n";
        cout << "********************\n";
        cout << "Input a command(0, 1, 2, 3): ";
        cin >> command;

        if (command == 0) break;

        ifstream inputFile;
        int w, h;
        Maze maze(0, 0);

        switch (command) {
        case 1:
        case 2: {
            cout << "Please enter the file number: ";
            string filename;
            cin >> filename;
            filename = "input" + filename + ".txt";
            inputFile.open(filename.c_str());
            if (!inputFile) {
                cout << "Unable to open file " << filename << endl;
                return 1;
            }
            inputFile >> w >> h;
            maze = Maze(w, h);
            cout << "Maze size: " << w << " x " << h << "\n";

            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    char ch;
                    inputFile >> ch;
                    maze.setMazeCell(x, y, ch);
                }
            }
            inputFile.close();

            if (command == 1) {
                if (maze.findPath(0, 0)) {
                    maze.printMaze(false);
                } else {
                    maze.printMaze(true);
                }
            } else if (command == 2) {
                int N;
                cout << "Please enter the number of goals: ";
                cin >> N;
                if (maze.findMultiPath(0, 0, N)) {
                    maze.printMaze(false);
                } else {
                    maze.printMaze(true);
                }
            } 
        }
        break;
        default:
            cout << "Invalid command";
            return 1;
        }
    }

    return 0;
}

