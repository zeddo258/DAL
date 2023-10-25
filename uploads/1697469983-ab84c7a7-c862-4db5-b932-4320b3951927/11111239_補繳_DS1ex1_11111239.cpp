//11111239 高于喬
#include <iostream>
#include <string>
#include <cstdio>
#define MAX_ROWS 100
#define MAX_COLS 100
using namespace std;

class Maze {
public:
    const int RIGHT = 0;
    const int DOWN = 1;
    const int LEFT = 2;
    const int UP = 3;
    int N;
    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {1, 0, -1, 0};
    bool pathFound = false; //初始化為未成功.
    Maze() {
        arg1 = 0;
        arg2 = 0;
    }

    bool readFromFile(const string& fileName) {
        //開唯讀檔.
        FILE *infile = fopen(fileName.c_str(), "r");
        if (infile == NULL) {
            cout << fileName << " does not exist" << endl;
            return 0;
        }

        fscanf(infile, "%d%d\n", &arg1, &arg2);
        //把迷宮存入array陣列.
        for (int i = 0; i < arg2; i++) {
            fgets(array[i], MAX_COLS, infile);
            array[i][arg1] = '\0';
        }

        fclose(infile);
        return 1;
    }

    bool findPath(int x, int y, int direction) {
        //printf("%d %d a=%c v=%d N=%d\n",x, y, array[x][y], visited[x][y], N);
        if (array[x][y] == 'G' && !visited[x][y]) {
            N--;
        }
        if (N == 0) {
            pathFound = true;
            return true; // 找完目標.
        }
        if (array[x][y] != 'O' && !visited[x][y]) {
            visited[x][y] = true; // 設置位置為已訪問.
            if(array[x][y] != 'G')
                array[x][y] = 'V'; // 已走過,G維持原樣.
            for (int i = 0; i <= 3; i++) {
                int newDirection = (direction + i) % 4;
                int newX = x + dx[newDirection];
                int newY = y + dy[newDirection];
                if (isInside(arg2, arg1, newX, newY)){
                    if(!visited[newX][newY]){
                        ans_path[x][y] = findPath(newX, newY, newDirection) || ans_path[x][y];
                        if(N == 0)
                            return true;
                    }
                }
            }
        }
        return array[x][y] == 'G' || ans_path[x][y];
    }

    bool printMaze() {
        for (int i = 0; i < arg2; i++) {
            for (int j = 0; j < arg1; j++) {
                cout << array[i][j] << ' ';
            }
            cout << endl;
        }
    }

    bool printAnsMaze() {
        printf("\n");
        for (int i = 0; i < arg2; i++) {
            for (int j = 0; j < arg1; j++) {
                if(array[i][j] == 'V'){
                    if(ans_path[i][j])
                        array[i][j] = 'R';
                    else
                        array[i][j] = 'E';
                }
                cout << array[i][j] << ' ';
            }
            cout << endl;
        }
    }

private:
    int arg1;
    int arg2;
    char array[MAX_ROWS][MAX_COLS];
    bool visited[MAX_ROWS][MAX_COLS] = {false}; // 記錄訪問過的位置
    bool ans_path[MAX_ROWS][MAX_COLS] = {false};
    bool isInside(int row, int col, int x, int y) {
        return x >= 0 && x < row && y >= 0 && y < col;
    }
};

int main() {
    int command = 0;
    do {
        Maze maze;
        cout << "*** Path Finding ***" << endl;
        cout << "* 0. Quit" << endl;
        cout << "* 1. One goal" << endl;
        cout << "* 2. More goals " << endl ;
        cout << "********************" << endl;
        cout << "Input a command (0, 1, 2): ";
        cin >> command;

        if ((command == 1) || (command == 2)) {
            string fileName;
            cout << "Input a file name (e.g., 201, 202): ";
            cin >> fileName;
            fileName = "input" + fileName + ".txt";
            //呼叫開檔函式.
            if(maze.readFromFile(fileName)){
                //maze.printMaze();
                cout<<endl;
                int startX = 0;
                int startY = 0;
                int N;
                int startDirection = maze.RIGHT; // 初始方向：右.
                if (command == 1) {
                    maze.N = 1; // 只需找到一個目標.
                    maze.findPath(startX, startY, startDirection);
                } else if (command == 2) {
                    cout << "Number of G (goals):" << endl;
                    cin >> maze.N;
                    maze.findPath(startX, startY, startDirection);
                }
                // 印迷宫.
                maze.printMaze();
                if(maze.pathFound){
                    maze.printAnsMaze();}
            }
        } else if (command != 0) {
            cout << "Command does not exist!" << endl;
        }

    } while (command != 0);

    return 0;
}
