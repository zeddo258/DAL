// 11127140 姜義新
#include <iostream>
#include <fstream>
#include <vector>
// 因為一開始建立vector時搞錯了 所以y跟x row col 是反的 y是左右 x是上下
using namespace std;

class Maze {
public:
    Maze(const string& filePath) {
        if (!openFile(filePath)) {
            cerr << "Can't open the file." << endl;
            exit(1);
        }
    }

    bool openFile(const string& filePath) {
        inputFile.open(filePath);
        return inputFile.is_open();
    }

    void readMatrix() {
        inputFile >> cols >> rows; // 讀取行數列數

        // 創建有行與列的vector，並在外圈包一圈0
        mazeVector.assign(rows + 2, vector<char>(cols + 2, '0'));

        // 讀取字母存進vector
        for (int i = 1; i <= rows; i++) {
            string rowStr;
            inputFile >> rowStr;

            for (int j = 1; j <= cols; j++) {
                mazeVector[i][j] = rowStr[j - 1];
            }
        }
        mazeVectorR = mazeVector ;
        mazeVectorV = mazeVector ;
        mazeVectorB = mazeVector ;
    }
    void printMatrixB() {
        // 打印
        for (int i = 1; i < mazeVectorB.size() - 1; i++) {
            for (int j = 1; j < mazeVectorB[0].size() - 1; j++) {
                cout << mazeVectorB[i][j] ;
            }
            cout << endl;
        }
    }


    void printMatrixV() {
        // 打印
        for (int i = 1; i < mazeVectorV.size() - 1; i++) {
            for (int j = 1; j < mazeVectorV[0].size() - 1; j++) {
                cout << mazeVectorV[i][j] ;
            }
            cout << endl;
        }
    }

    void solveMazeCaseOne( int n ) {

        // 從 (1,1) 開始，因為有包0當邊界
        dfs(1, 1, firstDir, 1) ;
        if (find){
            printMatrixV();
            cout << endl ;
            printMatrixB();
            cout << "Shortest path length = " << shortest << endl ;
        }
        else {
            // 沒有找到所有的G 因此輸出V圖
            printMatrixV();
            cout << endl ;
        }
    }

private:
    ifstream inputFile;
    int rows, cols;
    vector<vector<char>> mazeVector;
    vector<vector<char>> mazeVectorB;
    vector<vector<char>> mazeVectorV;
    vector<vector<char>> mazeVectorR;
    vector<vector<char>> xy ;

    int xynum = 2147483646 ;


    int firstDir = 0 ;
    int number = 0 ;
    int numberi = 0 ;
    int shortest = 1 ;
    bool find = false ;

    bool isValidMove(int x, int y) {
        // 判斷是否可以移動
        // 除了 0 O V 其餘都可以走
        return mazeVector[x][y] != '0' && mazeVector[x][y] != 'O' && mazeVector[x][y] != 'V' ;
    }

    void dfs( int x, int y, int dir, int xynumi ) {
        // 利用 dfs 函式的概念去遞迴 但根據上一次的移動和順位
        if ( mazeVector[x][y] == 'G') {
            xynum = xynumi ;
            mazeVectorB = mazeVectorR ;
            shortest = xynumi ;
            find = true ;
            return ;
        }

        int i = 0 ;
        // 用while 和switch 處理根據上一次的移動和順位右下左上
        // 確定可以移動並且小於目前最小就把點位打V
        // return 回去的時候要在原圖把V清掉變成E
        // return 走到死路的時候要把這條路的R清掉變成E
        while ( i < 4 ){
            switch (dir%4) {
                case 0 :
                    if (isValidMove(x, y+1)&& xynumi + 1< xynum){
                        mazeVector[x][y] = 'V' ;
                        mazeVectorV[x][y] = 'V' ;
                        mazeVectorR[x][y] = 'R' ;
                        dfs( x, y+1, dir, xynumi+1) ;
                    }
                    break;
                case 1 :
                    if (isValidMove(x+1, y)&& xynumi + 1 < xynum){
                        mazeVector[x][y] = 'V' ;
                        mazeVectorV[x][y] = 'V' ;
                        mazeVectorR[x][y] = 'R' ;
                        dfs( x+1, y, dir, xynumi+1 ) ;

                    }
                    break;
                case 2 :
                    if (isValidMove(x, y-1)&& xynumi + 1 < xynum){
                        mazeVector[x][y] = 'V' ;
                        mazeVectorV[x][y] = 'V' ;
                        mazeVectorR[x][y] = 'R' ;
                        dfs( x, y-1, dir, xynumi+1 ) ;

                    }
                    break;
                case 3 :
                    if (isValidMove(x-1, y)&& xynumi + 1 < xynum){
                        mazeVector[x][y] = 'V' ;
                        mazeVectorV[x][y] = 'V' ;
                        mazeVectorR[x][y] = 'R' ;
                        dfs( x-1, y, dir, xynumi+1 ) ;
                    }
                    break;
            }
            i++ ;
            dir++ ;
        }

        // 走到死路因此打V return回去
        mazeVectorV[x][y] = 'V' ;
        mazeVector[x][y] = 'E' ;
        mazeVectorR[x][y] = 'E' ;
        return ;
    }
};

int main() {
    int command = -1 ;

    do {
        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit *";
        cout << endl << "* 1. One goal *";
        cout << endl << "********************";
        cout << endl << "Input a command(0, 1): ";
        cin >> command ;
        if (command==0)
            break;
        cout << endl << "Input a file number (e.g., input101.txt, input102.txt, ...): ";
        string fileName ;
        cin >> fileName ;
        ifstream file(fileName.c_str());
        if (!file.good()) {
            // 找不到文件
            cout << "Can't open the file." << endl ;
            continue;
        }

        Maze handler(fileName);
        if (command == 1) {
            handler.readMatrix();
            handler.solveMazeCaseOne(1);
        }

    }while(true) ;

    return 0;
}