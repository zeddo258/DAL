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
        mazeVectorOrigin = mazeVector ;
    }

    void printMatrixR() {
        // 打印
        for (int i = 1; i < mazeVectorR.size() - 1; i++) {
            for (int j = 1; j < mazeVectorR[0].size() - 1; j++) {
                cout << mazeVectorR[i][j] << " ";
            }
            cout << endl;
        }
    }

    void printMatrixV() {
        // 打印
        for (int i = 1; i < mazeVectorV.size() - 1; i++) {
            for (int j = 1; j < mazeVectorV[0].size() - 1; j++) {
                cout << mazeVectorV[i][j] << " ";
            }
            cout << endl;
        }
    }

    void solveVForm() {
        // 把輸入進來的陣列將R改成V （整理V的圖）
        mazeVectorV = mazeVector ;
        for (int i = 0; i < mazeVectorV.size(); i++) {
            for (int j = 0; j < mazeVectorV[0].size(); j++) {
                if (mazeVectorV[i][j] == 'R'){
                    mazeVectorV[i][j] = 'V' ;
                }
            }
        }
    }

    void solveRForm() {
        // 把有R的點位寫進R的陣列 （整理R的圖）
        for (int i = 0; i < mazeVectorR.size(); i++) {
            for (int j = 0; j < mazeVectorR[0].size(); j++) {
                if (mazeVector[i][j] == 'R'){
                    mazeVectorR[i][j] = 'R' ;
                }
            }
        }
    }

    void solveGForm() {
        // 因為經過G的點會先清掉變成E，最後再加回來
        for (int i = 0; i < mazeVectorR.size(); i++) {
            for (int j = 0; j < mazeVectorR[0].size(); j++) {
                if (mazeVectorOrigin[i][j] == 'G'){
                    mazeVectorR[i][j] = 'G' ;
                    mazeVectorV[i][j] = 'G' ;
                }
            }
        }
    }

    void solveMazeCaseOne( int n ) {
        number = n ;
        // 從 (1,1) 開始，因為有包0當邊界
        if (dfs(1, 1, firstDir)){
            solveVForm();
            solveRForm();
            solveGForm();
            printMatrixV();
            cout << endl ;
            printMatrixR();
        }
        else {
            // 沒有找到所有的G 因此輸出V圖
            solveVForm();
            printMatrixV();
        }
    }

private:
    ifstream inputFile;
    int rows, cols;
    vector<vector<char>> mazeVector;
    vector<vector<char>> mazeVectorOrigin;
    vector<vector<char>> mazeVectorV;
    vector<vector<char>> mazeVectorR;
    int firstDir = 0 ;
    int number = 0 ;
    int numberi = 0 ;

    bool isValidMove(int x, int y) {
        // 判斷是否可以移動
        // 除了 0 O V 其餘都可以走
        return mazeVector[x][y] != '0' && mazeVector[x][y] != 'O' && mazeVector[x][y] != 'V' ;
    }

    bool dfs( int x, int y, int dir ) {
        // 利用 dfs 函式的概念去遞迴 但根據上一次的移動和順位
        if ( mazeVector[x][y] == 'G' ) {
            // 找到一個G則+1
            numberi++ ;
        }

        if (numberi == number){
            // 若找到所有的G 則return回去
            return true;
        }

        int i = 0 ;
        // 用while 和switch 處理根據上一次的移動和順位右下左上
        // 確定可以移動就把點位打V 走下一個
        // 如果有找到所有目標才回邊return回起點 並一邊打R
        // 因為R和V會混再一起 因此再用格式函式處理 再輸出
        while ( i < 4 ){
            switch (dir%4) {
                case 0 :
                    if (isValidMove(x, y+1)){
                        mazeVector[x][y] = 'V' ;

                        if (dfs( x, y+1, dir)){
                            mazeVector[x][y] = 'R' ;
                            return true ;
                        }
                    }
                    break;
                case 1 :
                    if (isValidMove(x+1, y)){
                        mazeVector[x][y] = 'V' ;

                        if (dfs( x+1, y, dir )){
                            mazeVector[x][y] = 'R' ;
                            return true ;
                        }
                    }
                    break;
                case 2 :
                    if (isValidMove(x, y-1)){
                        mazeVector[x][y] = 'V' ;

                        if (dfs( x, y-1, dir )){
                            mazeVector[x][y] = 'R' ;
                            return true ;
                        }
                    }
                    break;
                case 3 :
                    if (isValidMove(x-1, y)){
                        mazeVector[x][y] = 'V' ;

                        if (dfs( x-1, y, dir )){
                            mazeVector[x][y] = 'R' ;
                            return true ;
                        }
                    }
                    break;
            }
            i++ ;
            dir++ ;
        }

        // 走到死路因此打V return回去
        mazeVector[x][y] = 'V' ;
        return false ;
    }
};

int main() {
    int command = -1 ;

    do {
        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit *";
        cout << endl << "* 1. One goal *";
        cout << endl << "* 2. More goals *";
        cout << endl << "********************";
        cout << endl << "Input a command(0, 1, 2): ";
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
        else if (command == 2){
            int n ;
            cout << endl << "Input n : "  ;
            cin >> n ;
            handler.readMatrix();
            handler.solveMazeCaseOne(n);
        }

    }while(true) ;

    return 0;
}
