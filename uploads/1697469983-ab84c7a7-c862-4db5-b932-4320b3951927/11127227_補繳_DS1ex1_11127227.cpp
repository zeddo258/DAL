// 11127227 王筠翔

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum Modes {
    oneG, moreG
};

class Maze {
    private:
        char maze[100][100];
        int firstNum, secondNum;

    public:

    bool load(string fileNum, Modes mode) {
        string fileName = "input" + fileNum + ".txt";
        ifstream file;
        file.open(fileName.c_str());

        if (!file.is_open()) {
            cout << "檔案無法讀取" << endl;
            return false;
        }

        file >> firstNum >> secondNum; // 讀第一行的兩個數字

        for (int i = 0; i < secondNum; i++) { // 讀迷宮
            for (int j = 0; j < firstNum; j++) {
                file >> maze[i][j];
            }
        }

        return true;
    }

    void show() {
        for (int i = 0; i < secondNum; i++) {
            for (int j = 0; j < firstNum; j++) {
                cout << maze[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }

    bool findGoal(int x, int y, Maze& visitedMaze, int direction, int n) {
        if (x < 0 || x >= firstNum || y < 0 || y >= secondNum) {
            return false; // 超出迷宫範圍
        }

        if (visitedMaze.maze[y][x] == 'V' ||maze[y][x] == 'O') {
            return false; // 已經走過或是障礙物
        }

        visitedMaze.maze[y][x] = 'V'; // 標記為已走過

        if (maze[y][x] == 'G') {
            visitedMaze.maze[y][x] = 'G' ;

            if ( n > 0 ) n-- ;
            else return true;
        }

        // 沿著當前方向前進
        int newX = x, newY = y;
        if (direction == 0) newX++; // 向右
        else if (direction == 1) newY++; // 向下
        else if (direction == 2) newX--; // 向左
        else if (direction == 3) newY--; // 向上

        maze[y][x] = 'R' ;

        // 如果下一個位置是空格或目標，繼續朝當前方向前進
        if (newX >= 0 && newX < firstNum && newY >= 0 && newY < secondNum && maze[newY][newX] == 'E' || maze[newY][newX] == 'G') {
            maze[y][x] = 'R' ;
            return findGoal(newX, newY, visitedMaze, direction, n);
        }



        // 如果下一個位置是障礙物或到達邊界，按照右、下、左、上的順時針次序尋找下一個方向

        int obstacle = 0, num = 0;
        int newDirection = 0 ;

        for (int i = 0; i < 4; i++) {
            newDirection = (direction + i) % 4; // 計算下一個方向


            newX = x, newY = y;
            if (newDirection == 0) newX++; // 向右
            else if (newDirection == 1) newY++; // 向下
            else if (newDirection == 2) newX--; // 向左
            else if (newDirection == 3) newY--; // 向上

            maze[y][x] = 'R' ;

            // 如果下一個位置是空格，繼續朝當前方向前進
            if (newX >= 0 && newX < firstNum && newY >= 0 && newY < secondNum && maze[newY][newX] == 'E') {
                maze[y][x] = 'R' ;
                return findGoal(newX, newY, visitedMaze, newDirection, n);
            }



        } // for


        return false ;
    }

    void clr() {
        for (int i = 0; i < secondNum; i++) {
            for (int j = 0; j < firstNum; j++) {
                if (maze[i][j] == 'V' || maze[i][j] == 'R') {
                    maze[i][j] = 'E';
                }
            }
        }
    }
};

int main() {
    int command = 0;

    do {
        Maze aMaze;
        string fileName;
        Modes mode = oneG;
        int n = 0 ;

        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit          *";
        cout << endl << "* 1. One goal      *";
        cout << endl << "* 2. More goals    *";
        cout << endl << "********************";
        cout << endl << "Input a command (0, 1, 2): ";
        cin >> command;

        if ((command == 1) || (command == 2)) {
            if (command == 2) {
                mode = moreG;
                cout << "N = " ;
                cin >> n ;
            }
            cout << endl << "Input a file number (e.g., 201, 202, ...): ";
            cin >> fileName;


            if (aMaze.load(fileName, mode)) {
                int initialDirection = 0;
                Maze vMaze(aMaze);
                bool success = aMaze.findGoal(0, 0, vMaze, initialDirection, n);

                vMaze.show();

                if (success) {
                    aMaze.show();
                }
                vMaze.clr();
            }
            aMaze.clr();
        }
        else if (!command)
            break;
        else
            cout << endl << "Command does not exist!" << endl;

    } while (true);

    return 0;
}

