//11120411 陳瀚傑
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <limits>
#include <set>      //set<pair<int, int>>

using namespace std;

class ReadFile      //開檔程式
{
    private:

    ifstream mymap;

    public:

int ChooseFile() {      //呼叫使用者輸入字串
        int choice;
        cout << "Input a file number: ";
        cin >> choice;
        cout << endl;

        return choice;
    }

    vector<string> OpenFile() {
        int choice = ChooseFile();
        string filename = "input" + to_string(choice) + ".txt";    //把使用者的輸入結合成完整的檔案 

        mymap.open(filename);       //開啟使用者所選擇的檔案

        if (!mymap.is_open()) {     //如果檔案開不了就回傳空的vector
            cout << filename << " does not exist!" << endl;
            cout << endl;
            vector<string> emptyVector;
            return emptyVector;
        }

        int a, b; //得到我需要的陣列大小(地圖大小)
        mymap >> a >> b;
        mymap.ignore(); // 忽略換行符號

        int max_lines = b + 1; // 修正地圖高度

        vector<string> lines;

        for (int i = 1; i < max_lines; i++) {
            string line;
            getline(mymap, line);   //擷取第i行的資訊
            lines.push_back(line);  //將讀到的資料放進lines vector中
        }

        mymap.close();  //關閉檔案

        return lines;   //回傳所擷取到的地圖
    }

};
    
/*
符號定義:
作業定義的
'E': 空路(可走的路)
'V': 走過的路
'O': 牆壁(不可走的路)
'G': 終點
'R':最終可成功行經的路徑

額外定義的
'H': 當前走過的終點(如果要走過很多個G的話，我現在踩的這個G要可以通過，因此把現在踩著的G寫成另一個變數H。)類似E
'P': 之前走過的終點(之前如果走過G的話，那就不能再走一次，所以把它寫成P。)類似V
'D': 走過的死路
'S': 確定可以到G的路線。由於還要繼續找其他G，因此先寫成S作為記號，以免被洗掉
*/
class DoMaze{       //處理有關作業的地圖的問題

private:

    // 定義方向：右、下、左、上
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    int countG = 0;

    set<pair<int, int>> visited;

public:

    // 印出迷宮
    void printMaze(vector<string> maze) {
        for (const string& line : maze) {
            cout << line << endl;
        }
        cout << endl;
    }

    // 在迷宮中尋找路徑的遞迴函數
    bool findPath(vector<string>& maze, int x, int y, int dir, int Gnum) {
        // 如果已經走到目標位置 'G'，則找到一條路徑，返回true
        if (maze[x][y] == 'G') { 
            SetRoute(maze);
            maze[x][y] = 'H';   //H為走過的G
            countG++;
            if(countG == Gnum){
                return true;
            }
        }

        // 如果當前位置不是空格 'E'，或走過的'H'，則返回false表示無法通過
        if ((maze[x][y] != 'E') && (maze[x][y] != 'H')) {
            return false;
        }

        // 標記當前位置為已走過 標示為'V'
        if((maze[x][y] != 'H') && (maze[x][y] != 'P')){
            maze[x][y] = 'V';
        }
        // 如果是'H'的話，則標記當前目標(G)已走過 標示為'P'
        if(maze[x][y] == 'H'){
            maze[x][y] = 'P';
        }
        
         // 嘗試四個方向的移動
        int count = 0;  //紀錄是不是轉一圈都沒有路
        for (dir;count < 4 ;dir = (dir+1) % 4) {     //轉換方向
            int newX = x + dx[dir];
            int newY = y + dy[dir];
            count++;
            // 檢查新位置是否在合法範圍內
            if (newX >= 0 && newX < maze.size() && newY >= 0 && newY < maze[0].size()) {
                // 遞迴嘗試移動，如果找到路徑，返回true
                if (findPath(maze, newX, newY, dir, Gnum)) {
                    if((maze[x][y] != 'P') && (maze[x][y] != 'H') && (maze[x][y] != 'G')){
                        // 標記成功的路徑 'R'
                        maze[x][y] = 'R';
                    }
                    
                    return true;
                }
            }
        }
        // 如果所有方向都無法找到路徑，回到上一步並返回false
        if((maze[x][y] != 'S') && (maze[x][y] != 'P') && (maze[x][y] != 'H')){
            maze[x][y] = 'D'; // 標記為走過的死路
        }
        return false;
    }
    
    //將走過確定是正確的路線印出來先表示成S(Sure)
    void SetRoute(vector<string> &maze){     
        for (int i = 0; i < maze.size(); i++) {
            for (int j = 0; j < maze[i].size(); j++) {
               if(maze[i][j] == 'V'){
                    maze[i][j] = 'S';
               }
            }
        }
    }

    //列印曾走過的路徑
    void printTraveldPath(vector<string> maze) {
        for (int i = 0; i < maze.size(); i++) {
            for (int j = 0; j < maze[i].size(); j++) {
               if(maze[i][j] == 'D'){   //曾經走過的死路
                    maze[i][j] = 'V';
               }
               if(maze[i][j] == 'R'){   //正確的路(曾走過)
                    maze[i][j] = 'V';
               }
               if(maze[i][j] == 'S'){   //正確的路(曾走過)
                    maze[i][j] = 'V';
               }
               if(maze[i][j] == 'P'){   //曾經走過的終點
                    maze[i][j] = 'G';
               }
               if(maze[i][j] == 'H'){   //曾經走過的終點
                    maze[i][j] = 'G';
               }
            }
        }
        printMaze(maze); // 印出曾經走過
    }

    //列印最終路徑
    void printFinalPath(vector<string> maze) {
        for (int i = 0; i < maze.size(); i++) {
            for (int j = 0; j < maze[i].size(); j++) {
               if(maze[i][j] == 'D'){   //曾經走過的死路印成空格
                    maze[i][j] = 'E';
               }
               if(maze[i][j] == 'V'){
                    maze[i][j] = 'E';
               }
               if(maze[i][j] == 'S'){  
                    maze[i][j] = 'R';
               }
               if(maze[i][j] == 'P'){
                    maze[i][j] = 'G';
               }
               if(maze[i][j] == 'H'){
                    maze[i][j] = 'G';
               }
            }
        }
        printMaze(maze); // 印出最終結果
    }

};


void mission_1(){       //任務1
    ReadFile map;
    vector<string> maze = map.OpenFile();

    if (maze.empty()) { //如果是空的代表檔案沒正確開啟，因此回到主選單
        return;
    }

    DoMaze go;

    // 從左上角開始尋找路徑
    bool found = go.findPath(maze, 0, 0, 0, 1);
    

    if (found) {//如果找到
        go.printTraveldPath(maze);//列印曾走過的路徑
        go.printFinalPath(maze);//列印最終路徑
    }
    if (!found) {//如果沒找到
        go.printTraveldPath(maze);//列印曾走過的路徑
    }

}

void mission_2(){       //任務2
    ReadFile map;
    vector<string> maze = map.OpenFile();

    if (maze.empty()) { //如果是空的代表檔案沒正確開啟，因此回到主選單
        return;
    }

    DoMaze go;

    int Gnum = 0;

    while (true) {

        cout << "Number of G (goals): ";   //輸入值
        
        if (!(cin >> Gnum)) {   //如果輸入無效值的話除錯

            cin.clear(); // 清除 cin 的錯誤狀態
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除之前的輸入
            cout << endl;
            cout << "Invalid input. Please enter a valid number." << endl << endl;

        } else if (Gnum >= 1 && Gnum <= 100) {

            break; // 如果輸入有效且在範圍內，退出迴圈

        } else {    //超過範圍也印錯誤字樣

            cout << "### The number must be in [1, 100] ###" << endl;
            cout << endl;

        }
    }

    // 從左上角開始尋找路徑
    int found = go.findPath(maze, 0, 0, 0, Gnum);

    if (found) {    //如果找到路了，就印出曾走過的路和最終結果
        go.printTraveldPath(maze);
        go.printFinalPath(maze);
    }
    if (!found) {   //如果沒找到，就只印出曾走過的路
        go.printTraveldPath(maze);
    }
}

int main()
{
    char startnum = 0;
   
    while (1) {
        cout <<"*** Path Finding ***" << endl;
        cout <<"* 0. Quit          *" << endl;
        cout <<"* 1. One goal      *" << endl;
        cout <<"* 2. More goals    *" << endl;
        cout <<"********************" << endl;
        cout <<"Input a command(0, 1, 2):  ";
        startnum = getchar();   //擷取字串
        if(startnum == '\n'){   //以防緩存區存到enter
            startnum = getchar();
        }
        cout << endl;
        switch (startnum)
        {
        case '0':     //0的話直接結束
            exit(0);
        case '1':     //1進入任務1
            mission_1();
            break;
        case '2':     //2進入任務2
            mission_2();
            break;
        default:    //其他顯示錯誤
            cout << "Command does not exist!" << endl << endl;
            break;
        }
    }
    return 0;
}
