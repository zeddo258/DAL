// 11127136 彭晨維
//*************************************************************/
// Exercise 01: Path finding in a Maze by 11127136@CyCU 2023/09
//*************************************************************/

#include <cstdio>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

// Enumerates different move directions
typedef enum
{
    Copy = -1,
    Right, Down, Left, Up
} Moves;

// Enumerates the modes of the maze
enum Modes {
    oneG,  // Single goal mode
    moreG  // Multiple goals mode
};

// Class for representing coordinates (x, y)
class CoXY {
    int y;
    int x;

public:
    CoXY() : y(0), x(0) {};

    CoXY(int py, int px) {
        y = py;
        x = px;
    }

    CoXY(const CoXY& pt) : y(pt.y), x(pt.x) {}

    void setXY(const int py, const int px) {
        y = py;
        x = px;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    CoXY nextXY(Moves dir) const {
        CoXY pt(y, x);

        switch (dir) {
            case Right:
                pt.x++;
                break;
            case Down:
                pt.y++;
                break;
            case Left:
                pt.x--;
                break;
            case Up:
                pt.y--;
                break;
            default:
                break;
        }
        return pt;
    }

    bool match(const CoXY& pt) const {
        if (y == pt.y && x == pt.x)
            return true;
        return false;
    }

    bool inRange(const CoXY& maxLimit) const {
        if (y >= 0 && y < maxLimit.y && x >= 0 && x < maxLimit.x)
            return true;
        return false;
    }
};

// Class for representing the maze
class Maze {
public:
    bool load(string fileName, Modes); // Load the maze from a text file
    bool show( bool showVisited ); // Display the maze on the screen
    bool clr(); // Clear up the maze
    bool findGoals(Maze& maze); // Find goals in the maze

private:
    int rows;
    int cols;
    char** mArray;
    char** rArray;

    bool dfs(const CoXY& current, bool** visited);
};

// Load the maze from a file
bool Maze::load(string fileName, Modes) {
    FILE* infile = NULL;
    bool success = false;
    CoXY coMax(0, 0);
    char** mArray;

    fileName = "input" + fileName + ".txt";
    infile = fopen(fileName.c_str(), "r");
    if (infile == NULL)
        cout << "\n" << fileName << " does not exist!" << "\n";
    else {
        int arg1 = 0, arg2 = 0;

        fscanf(infile, "%d %d", &arg1, &arg2);
        coMax.setXY(arg2, arg1);
        if (coMax.getY() > 0 && coMax.getX() > 0) {
            int line = 0;
            char* temp = new char[coMax.getX() + 1];

            mArray = new char*[coMax.getY()];
            while (fscanf(infile, "%s", temp) != EOF) {
                mArray[line] = new char[coMax.getX() + 1];
                strcpy(mArray[line++], temp);
            }

            if (line == coMax.getY())
                success = true;
        }
        fclose(infile);
    }
    this->rows = coMax.getY();
    this->cols = coMax.getX();
    this->mArray = mArray;
    return success;
}

// Find goals in the maze
bool Maze::findGoals(Maze& maze) {
    bool** visited = new bool*[rows];
    for (int i = 0; i < rows; i++) {
        visited[i] = new bool[cols];
        memset(visited[i], false, sizeof(bool) * cols);
    }

    CoXY start(0, 0);
    while (mArray[start.getY()][start.getX()] != 'E') {
        start.setXY(start.getY(), start.getX() + 1);
    }

    bool found = dfs(start, visited);

    return found;
}

// Perform depth-first search to find goals
bool Maze::dfs(const CoXY& current, bool** visited) {
    if (mArray[current.getY()][current.getX()] == 'G') {
        return true;
    }

    if (mArray[current.getY()][current.getX()] == 'O' || visited[current.getY()][current.getX()]) {
        return false;
    }

    visited[current.getY()][current.getX()] = true;

    Moves directions[] = { Right, Down, Left, Up };

    for (int i = 0; i < 4; i++) {
        CoXY nextPos = current.nextXY(directions[i]);

        if (nextPos.inRange(CoXY(cols, rows))) {
            if (dfs(nextPos, visited)) {
                if (mArray[current.getY()][current.getX()] != 'G') {
                    mArray[current.getY()][current.getX()] = 'R';
                }
                return true;
            }
        }
    }

    return false;
}


// 修改 Maze 類別中的 show 函式
bool Maze::show(bool showVisited) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (showVisited && mArray[i][j] == 'R') {
                cout << 'V'; // 顯示已訪問的路徑為 'V'
            } else {
                cout << mArray[i][j]; // 顯示迷宮內容
            }
        }
        cout << endl;
    }
    return true;
}

// Clear the maze
bool Maze::clr() {
    if (mArray) {
        for (int i = 0; i < rows; i++) {
            delete[] mArray[i];
        }
        delete[] mArray;
        mArray = nullptr;
    }
    return true;
}

// Main function
int main(void) {
    int command = 0;

    do {
        Maze aMaze;
        string fileName;
        Modes mode = oneG;

        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit          *";
        cout << endl << "* 1. One goal      *";
        cout << endl << "* 2. More goals    *";
        cout << endl << "********************";
        cout << endl << "Input a command (0, 1, 2): ";
        cin >> command;
        if (command == 1 || command == 2) {
            if (command == 2)
                mode = moreG;
            cout << endl << "Input a file number (e.g., 201, 202, ...): ";
            cin >> fileName;
            if (aMaze.load(fileName, mode)) {
                Maze vMaze(aMaze);
                bool success = aMaze.findGoals(vMaze);

                mode = oneG;
                vMaze.show( true );
                if (success)
                {
                    cout << endl ;
                    aMaze.show( false );                    
                }
            }
        } else if (!command)
            break;
        else
            cout << endl << "Command does not exist!" << endl;

    } while (true);

    return 0;
}
