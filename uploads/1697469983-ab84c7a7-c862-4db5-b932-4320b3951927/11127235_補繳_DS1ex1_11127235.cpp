// 11127235 許倚菁 
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>

using namespace std;

class Maze {
public:
    vector<vector<char> > maze; // 使用二維vector儲存迷宮 
    int rows; // 迷宮的行數 
    int cols; // 迷宮的列數 

    // 構造函數，初始化迷宮為空
    Maze(int rows, int cols) : rows(rows), cols(cols), maze(rows, vector<char>(cols, ' ')) {};

    // 載入迷宮資料 
    bool loadMaze(string fileName) {
        ifstream inFile(fileName.c_str()); // 創建一文件流對象'inFile'，打開與讀取指定文件內容 
        if (!inFile) {                     //  '.c_str()'將字符串轉換成C風格字符串     
            cout << fileName << " doesn't exist!" << endl;
            return false;
        }

        inFile >> cols >> rows; // 讀取迷宮的行數和列數 

        // 重新分配迷宮大小
        maze = vector<vector<char> >(rows, vector<char>(cols, ' '));

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                char cell;
                inFile >> cell;
                maze[row][col] = cell;
                if (inFile.peek() == '\n') { // 檢查文件下一字符是否為換行符 ，'inFile.peek()' 返回下一個字符而不從流中移除它 
                    inFile.get(); // 讀取並呼略換行符
                }
            }
        }
        inFile.close(); //關閉文件流'inFile' 
    }

    bool findV(int x, int y, int direction) {
        if (x < 0 || x >= rows || y < 0 || y >= cols) {
            return false; // 超出迷宮邊界，返回false
        }

        // 如果當前位置是障礙物 'O' 或已經走過的 'V'，返回false
        if (maze[x][y] == 'O' || maze[x][y] == 'V') {
            return false;
        }

        // 如果找到目標 'G'，返回true
        if (maze[x][y] == 'G') {
            return true;
        }

        // 標示此位置已走過 
        maze[x][y] = 'V';


        // 定義四個移動方向的偏移量，(dx, dy) 分別表示右、下、左、上四個方向
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};

        // 嘗試正在使用的方向
        int newX = x + dx[direction];
        int newY = y + dy[direction];
        if (findV(newX, newY, direction)) {
            return true; // 如果找到通路，返回true
        }

        // 嘗試下一個方向 
        for (int newD = (direction + 1) % 4; newD != direction; newD = (newD + 1) % 4) { //(direction + 1) % 4 當前方向的下一個方向 
            newX = x + dx[newD];
            newY = y + dy[newD];
            if (findV(newX, newY, newD)) {
                return true; // 如果找到通路，返回true
            }
        }

        // 如果四個方向都沒有找到路，返回false
        return false;
    }
    
    bool findMoreV(int x, int y, int direction, int numOfG ) {
        if (x < 0 || x >= rows || y < 0 || y >= cols) {
            return false; // 超出迷宮邊界，返回false
        }

        // 如果當前位置是障礙物 'O' 或已經走過的 'V'，返回false
        if (maze[x][y] == 'O' || maze[x][y] == 'V') {
            return false;
        }

        // 如果找到目標 'G'，返回true
        if (maze[x][y] == 'G') {
        	numOfG -- ;
        	if ( numOfG == 0 ) {			
              return true;
            }
        }

        // 標示此位置已走過 
        if ( maze[x][y] != 'G') {
          maze[x][y] = 'V';
        }

        // 定義四個移動方向的偏移量，(dx, dy) 分別表示右、下、左、上四個方向
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};

        // 嘗試正在使用的方向
        int newX = x + dx[direction];
        int newY = y + dy[direction];
        if (findMoreV(newX, newY, direction, numOfG)) {
            return true; // 如果找到通路，返回true
        }

        // 嘗試下一個方向 
        for (int newD = (direction + 1) % 4; newD != direction; newD = (newD + 1) % 4) {
            newX = x + dx[newD];
            newY = y + dy[newD];
            if (findMoreV(newX, newY, newD, numOfG)) {
                return true; // 如果找到通路，返回true
            }
        }

        // 如果四個方向都沒有找到路，返回false
        return false;
    }

    // 印出迷宮 
    void printMaze() {
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                cout << maze[row][col];
            }
            cout << endl;
        }
    }

    //找出哪些V需標記成R或是E 
    bool findR(int x, int y) {
        if (x < 0 || x >= rows || y < 0 || y >= cols || maze[x][y] == 'O' || maze[x][y] == 'E' ) {
            return false; // 超出邊界或不是該走的位置
        }

        // 如果是目標 'G'，返回true表示已找到路
        if (maze[x][y] == 'G') {
            return true;
        }
        
        // 已經檢查過此位置了 
        if (maze[x][y] == 'R') {
            return false;
        }
        // 標記當前位置已走過 
        maze[x][y] = 'R';

       
        // 向右走
        if (findR(x, y + 1)) {
            return true;
        }
        // 向下走
        if (findR(x + 1, y)) {
            return true;
        }

         // 向左走
        if (findR(x, y - 1)) {
            return true;
        }
        
        // 向上走
        if (findR(x - 1, y)) {
            return true;
        }


        // 如果四個方向都沒有找到路，回溯，標記為 'E'
        maze[x][y] = 'E';
        return false;
    }
    
    bool findMoreR(int x, int y, int numOfG) {
        if (x < 0 || x >= rows || y < 0 || y >= cols || maze[x][y] == 'O' || maze[x][y] == 'E' ) {
            return false; // 超出邊界或不是該走的位置
        }

        // 如果是目標 'G'，返回true表示已找到路
        if (maze[x][y] == 'G') {
        	numOfG -- ;
        	if ( numOfG == 0) {
              return true;
            }
        }
        
        // 已經檢查過此位置了 
        if (maze[x][y] == 'R') {
            return false;
        }
        
        // 標記當前位置已走過 
        if (maze[x][y] != 'G') {
          maze[x][y] = 'R';
        }

        // 向右走
        if (findMoreR(x, y + 1, numOfG)) {
            return true;
        }

        // 向下走
        if (findMoreR(x + 1, y, numOfG)) {
            return true;
        }


        // 向左走
        if (findMoreR(x, y - 1, numOfG)) {
            return true;
        }
        
        // 向上走
        if (findMoreR(x - 1, y, numOfG)) {
            return true;
        }

        
        // 如果四個方向都沒有找到路，回溯，標記為 'E'
        maze[x][y] = 'E';
        return false;
    }
};

int main() {
	char command = '0'; // 用於指令輸入 
    do  {
      
	  int fileNumber = 0;
      cout << endl ;
      cout << "*** Path Finding ***\n";
      cout << "* 0.Quit           *\n";
      cout << "* 1.One goal       *\n";
      cout << "* 2.More goals     *\n";
      cout << "********************\n";
      cout << "Input a command(0,1,2):";
      cin >> command;
	  if (command == '1' || command == '2') {
        int x = 0, y = 0, startDirection = 0; // 初始位置為左上角(0, 0)
        cout << endl << "Input a file number:";
        cin >> fileNumber;
        string fileName;  
        stringstream ss; //創建一個字符串流 
        ss << "input" << fileNumber << ".txt"; //將輸入檔案號碼拼接成檔案名 
        fileName = ss.str();  //調用'ss.str()將檔案名稱存在'fileName'中 
        Maze maze(0, 0); // 創建一個Maze類對象，並初始化 
        if (maze.loadMaze(fileName)) { //檢查是否有此檔案，有則將內容儲存進maze 
            if (command == '1') { // 找一個'G' 
                if (maze.findV(x, y, startDirection)) { //是否有找到'G' 
                    x = 0, y = 0; //重新初始化位置至左上角(0,0) 
                    Maze vMaze(maze); //創建一個Maze類對象vMaze用來儲存含有'V'的位置且成功找到'G' 
                    cout << endl;
                    if (maze.findR(x, y)) { // 找出成功路徑'R' 
                        vMaze.printMaze(); //輸出所有經過位置的迷宮 
                        cout << endl;
                        maze.printMaze(); // 輸出含成功路徑的迷宮 
                        cout << endl;
                    } 
                }
                else {
                	cout << endl;
                    maze.printMaze();
                    cout << endl;
				}
            } else if (command == '2') {
                cout << endl << "Number of G (goals):";
                int numOfG;
                cin >> numOfG; //輸入想要找幾個'G' 
                x = 0, y = 0, startDirection = 0; 
                if (maze.findMoreV(x, y, startDirection, numOfG)) {
                	x = 0, y = 0; //重新初始化位置至左上角(0,0) 
                    Maze vMaze(maze); //創建一個Maze類對象vMaze用來儲存含有'V'的位置且成功找到'G' 
                    cout << endl;
                    if (maze.findMoreR(x, y, numOfG)){ // 找出成功路徑'R' 
                        vMaze.printMaze(); //輸出所有經過位置的迷宮 
                        cout << endl;
                        maze.printMaze(); // 輸出含成功路徑的迷宮 
                        cout << endl;
                    } 
                }
                else {
                	cout << endl;
                    maze.printMaze();  //輸出走過位置的迷宮 
                    cout << endl;
				}
			  }
            }
          
        
      } 
      else if (command == '0') {
        break;
      }
      else {
        cout << endl << "Command does not exist!" << endl;
      }
    } while (true);
	system("pause");
    return 0;
}















