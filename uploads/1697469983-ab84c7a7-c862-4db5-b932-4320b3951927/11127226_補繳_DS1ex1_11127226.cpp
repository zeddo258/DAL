// 11127226 李奕層
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class MazeClass {
    private:
        char maze[100][100];

    public:
        int length = 0, width = 0; // 迷宮長寬宣告
        bool load(string fileName){ // 導入檔案
            ifstream in ;
            string file = "input" + fileName + ".txt"; // 合成檔名
            in.open(file); // 開啟檔案

            if(in.fail()){ // 確認檔案是否正常開啟
                cout << endl << "input file opening failed or does not exist";
                return false ; // 開啟異常則回傳 false
            }

            in >> width >> length ; // 設定迷宮長寬

            for(int i = 0 ; i < length ; i++) { // 設定迷宮資訊
                for(int j = 0 ; j < width ; j++){
                    in >> maze[i][j] ;
                }
            }

            return true; // 設定完成則回傳 true

        }

        bool findGoals(MazeClass &vMaze, int x, int y, int direction, int & num_goals){ // 記住每次vMaze所改變的資訊, x、y代表目前位置, direction代表目前行徑方向, num_goals為目前還需要找的目標數量
            vMaze.changeV(0, 0); // 將初始地設為已走過

            for (int i = direction; i < direction + 4; i++) { // 將i設為目前方向, 並依照順序右、下、左、上輪迴跑過至少4次, 相對應方向所代表的數值為0、1、2、3, 舉例: i = 2, 目前方向為左, 而他接下來會依左、上、右、下去判斷是否移動
                if (i%4 == 0) { // 確認目前方向向右
                    if((vMaze.locationData(x, y+1) == 'E' || vMaze.locationData(x, y+1) == 'G')){ // 確認右邊是否能通行
                        if(vMaze.locationData(x, y+1) == 'G'){ // 如果右邊為目標, 先將該位置資訊換為Q, 以利後續判斷, 同時將需要尋找的目標數-1
                            vMaze.changeQ(x, y+1);
                            num_goals--;
                            if(num_goals == 0){ // 如果找到了全部目標, 則將回傳true, 同時一步步記錄回傳到初始位置之間的路徑於aMaze裡
                                maze[x][y] = 'R';
                                return true ;
                            }
                        }
                        else // 如果右邊可通行且不是目標則記錄為已行經
                            vMaze.changeV(x, y+1);

                        if(findGoals(vMaze, x, y+1, i, num_goals)){ // 往右邊進行遞迴, 如果後續遞迴有找到目標, 則將目前位置設為到目標的路徑之一
                            if(maze[x][y] != 'G')
                                maze[x][y] = 'R';
                            if(num_goals == 0) // 如果找到全部目標則進行回傳true
                                return true ;
                        }

                    }
                }
                else if (i%4 == 1) { // 此處所做行為同上, 但方向為向下
                    if((vMaze.locationData(x+1, y) == 'E' || vMaze.locationData(x+1, y) == 'G')){
                        if(vMaze.locationData(x+1, y) == 'G'){
                            vMaze.changeQ(x+1, y);
                            num_goals--;
                            if(num_goals == 0){
                                maze[x][y] = 'R';
                                return true ;
                            }
                        }
                        else
                            vMaze.changeV(x+1, y);

                        if(findGoals(vMaze, x+1, y, i, num_goals)){
                            if(maze[x][y] != 'G')
                                maze[x][y] = 'R';
                            if(num_goals == 0)
                                return true ;
                        }

                    }
                }
                else if (i%4 == 2 ) { // 此處所做行為同上, 但方向為向左
                    if((vMaze.locationData(x, y-1) == 'E' || vMaze.locationData(x, y-1) == 'G')){ // 2
                        if(vMaze.locationData(x, y-1) == 'G'){
                            vMaze.changeQ(x, y-1);
                            num_goals--;
                            if(num_goals == 0){
                                maze[x][y] = 'R';
                                return true ;
                            }
                        }
                        else
                            vMaze.changeV(x, y-1);

                        if(findGoals(vMaze, x, y-1, i, num_goals)){
                            if(maze[x][y] != 'G')
                                maze[x][y] = 'R';
                            if(num_goals == 0)
                                return true ;
                        }

                    }
                }
                else if (i%4 == 3) { // 此處所做行為同上, 但方向為向上
                     if((vMaze.locationData(x-1, y) == 'E' || vMaze.locationData(x-1, y) == 'G')){ // 3
                        if(vMaze.locationData(x-1, y) == 'G'){
                            vMaze.changeQ(x-1, y);
                            num_goals--;
                            if(num_goals == 0){
                                maze[x][y] = 'R';
                                return true ;
                            }
                        }
                        else
                            vMaze.changeV(x-1, y);

                        if(findGoals(vMaze, x-1, y, i, num_goals)){
                            if(maze[x][y] != 'G')
                                maze[x][y] = 'R';
                            if(num_goals == 0)
                                return true ;
                        }

                    }
                }

            }

            if (num_goals == 0) { // 全數目標找到則回傳ture
                return true;
            }

            return false; // 無法找到任何目標回傳false
        }

        void changeV(int x, int y){ // 將所傳入的位置資訊換成'V'
            maze[x][y] = 'V';
        }

        void changeQ(int x, int y){ // 將所傳入的位置資訊換成'Q'
            maze[x][y] = 'Q';
        }

        char locationData(int x, int y){ // 用以取得迷宮位置的資訊
            return maze[x][y] ;
        }

        void show(){ // 使用迴圈將迷宮給列印出來
            cout << endl;
            for( int i = 0 ; i < length ; i++ ) {
                for( int j = 0 ; j < width ; j++ ){
                    if(maze[i][j] == 'Q')
                        cout << 'G' ;
                    else
                        cout << maze[i][j] ;
                }
                cout << endl;
            }
        }

        void clr(){ // 使用迴圈將迷宮各位置設為'\0'
            for( int i = 0 ; i < length ; i++ ) {
                for( int j = 0 ; j < width ; j++ ){
                    maze[i][j] = '\0' ;
                }
            }
        }
};

int main()
{
    int command = 0 ;

    do{
        string fileName ; // 宣告檔名的存取
        MazeClass aMaze ; // 宣告一個迷宮Class, 用來存取到目標的路徑資訊
        int num_goals = 1 ; // 宣告迷宮目標數量
        cout << endl << "*** Path Finding *****";
        cout << endl << "* 0. Quit            *";
        cout << endl << "* 1. One goal        *";
        cout << endl << "* 2. More gloals     *";
        cout << endl << "**********************";
        cout << endl << "Input a Command(0, 1, 2): ";
        cin >> command ;
        if (command == 1 || command == 2){
            cout << endl << "Input a file number(e.g.,101, 102...): ";
            cin >> fileName ; // 輸入檔名
            if(command == 2){ // 如果有多個目標則多讀取目標數量
                cout << endl << "Number of G (goals): ";
                cin >> num_goals ;
            }

            if(aMaze.load(fileName)){ // 導入檔案並確認有無正常開啟
                MazeClass vMaze(aMaze); // 宣告一個迷宮Class, 用以存取行經路徑

                bool success = aMaze.findGoals(vMaze, 0, 0, 0, num_goals); // 進入找尋目標的函式, 有找到目標則將success設為true, 無則false

                vMaze.show(); // 將行經路徑展示
                if(success){ // 如果找到目標則將到目標的路徑資訊展示
                    aMaze.show();
                }
                vMaze.clr(); // 清除迷宮資訊
            }
            aMaze.clr(); // 清除迷宮資訊
        }
        else if(command == 0){ // 依照指令離開迴圈
            break;
        }
        else{ // 無此指令
            cout << endl << "Command does not exist!" << endl;
        }

    }while(true);


    return 0;
}
