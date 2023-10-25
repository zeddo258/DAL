// 11127206 陳奕帆
#include <iostream>
#include <fstream>

using namespace std;

enum Moves { Right, Down, Left, Up };// 列舉四個移動方向

class Solve {
public:
    Solve() {
      numCol = 0;
      numRow = 0;
      foundPath = false;
      startRow = 0;
      startCol = 0;
      total = 0;
    }

    void run() {
        int command = 0;

        do {
            string fileName;

            cout << "\n" << "*** Path Finding ***";
            cout << "\n" << "* 0. Quit          *";
            cout << "\n" << "* 1. One goal      *";
            cout << "\n" << "* 2. More goals    *";
            cout << "\n" << "********************";
            cout << "\n" << "Input a command (0, 1, 2): ";
            cin >> command;

            if (command == 1 || command == 2) {
                if (command == 2) {
                    int num;
                    cout << "Input the number of goals (N): ";
                    cin >> num;
                    total = num;
                }

                cout << "\n" << "Input a file number (e.g.201.202.203... ";
                cin >> fileName;
                fileName = "input" + fileName + ".txt";
                openMaze(fileName);

                if (exploreMaze(startRow, startCol, Right)) {
                    printMaze(maze);
                    cout << "\n";
                    printMaze(ans);
                } else {
                    cout << "No path found!" << "\n";
                }
            } else if (command == 0) {
                break;
            } else {
                cout << "\n" << "Command does not exist!" << "\n";
            }
            for (int i = 0; i < numRow; i++) {
              for (int j = 0; j < numCol; j++) {
                maze[i][j] = ' ';       // 清空地圖
                ans[i][j] = ' ';
                original[i][j] = ' ';
              }
            }


        } while (true); // 一直重複直到return false
    }

private:
    char maze[100][100];
    char ans[100][100]; // 存R圖
    char original[100][100]; // 存原始圖
    int numCol;
    int numRow;
    bool foundPath;
    int startRow;
    int startCol;
    int total;

    bool isValidMove(int row, int col) {
        if (row >= 0 && row < numRow && col >= 0 && col < numCol &&
            (maze[row][col] == 'G' || maze[row][col] == 'E'))
            return true;
        return false;
    }

    bool exploreMaze(int row, int col, Moves prevMove) {
    if (!isValidMove(row, col)) {
        return false;
    }

    if (maze[row][col] == 'G') {

        if (total >= 1) {
            total--;
        }
        if (total == 0 ) foundPath = true ;
    }

    if (foundPath) {
        return true;
    }

    maze[row][col] = 'V'; // 標記成已訪問

    Moves moves[] = { Right, Down, Left, Up }; // 迷宮探索會循環遍歷這四個方向尋找路徑
    Moves nextMove = prevMove;

    for (int i = 0; i < 4; i++) {
        if (i > 0) {
            nextMove = static_cast<Moves>((nextMove + 1) % 4); // 確保方向一定在這四個裡面並強制換成Moves
        }

        int newRow = row, newCol = col;

        if (nextMove == Right) {
            newCol++;
        } else if (nextMove == Down) {
            newRow++;
        } else if (nextMove == Left) {
            newCol--;
        } else if (nextMove == Up) {
            newRow--;
        }

        if (isValidMove(newRow, newCol)) {
            if (maze[newRow][newCol] == 'O') {
                Moves altMove[] = { Down, Left, Up, Right };
                bool moved = false;
                for (int j = 0; j < 4; ++j) {
                    int altRow = newRow, altCol = newCol;
                    if (altMove[j] == Right) {
                        altCol++;
                    } else if (altMove[j] == Down) {
                        altRow++;
                    } else if (altMove[j] == Left) {
                        altCol--;
                    } else if (altMove[j] == Up) {
                        altRow--;
                    }
                    if (isValidMove(altRow, altCol) && maze[altRow][altCol] == 'E') {
                        nextMove = altMove[j];
                        newRow = altRow;
                        newCol = altCol;
                        moved = true;
                        break;
                    }
                }
                if (moved == false ) {
                    newRow = row;
                    newCol = col;
                }
            }
        }

        if (exploreMaze(newRow, newCol, nextMove)) {
            ans[row][col] = 'R';
            return true;
        }
    }


    return false;
}


   int openMaze(const string &name) {
       // const string &name將檔案名稱作為參數傳給函數
    ifstream inputFile(name);
    if (!inputFile.is_open()) {
        cout << "無法打開文件" << endl;
        return 1;
    }

    inputFile >> numCol >> numRow;

    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            inputFile >> maze[i][j];
            original[i][j] = maze[i][j]; // 保存原始地圖
            ans[i][j] = maze[i][j];
        }
    }

    startRow = 0;
    startCol = 0;
    inputFile.close();
    foundPath = false;

    return 0;
}


    void printMaze(char array[100][100]) {
        for (int i = 0; i < numRow; ++i) {
            for (int j = 0; j < numCol; ++j) {
                if (original[i][j] == 'G') {
                    cout << 'G'; // 如果原始地圖是 'G'，則輸出 'G'
                } else {
                    cout << array[i][j];
                }
            }
            cout << "\n";
        }
    }

};
int main() {
    Solve Solve;//建立物件後透過此來呼叫Solve類別中的函式
    Solve.run();

    return 0;
}
