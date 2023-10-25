//11127202 郭立綸

#include <iostream>
#include <fstream>

using namespace std;

class Maze {

    private:
        int x, y, target, shortpath = -1;   //X和Y為矩陣的行列 target為目標數
        char **maze;                        //maze是存放迷宮的二維陣列

    public:
        void Load( string fileName, int goals){     //Load為讀入資料的函式 fileName代表檔案名稱 goals代表要找的目標數量

            ifstream in;                            //開啟要讀取的檔案並輸入進此class裡
            in.open( fileName );
            in >> x >> y;
            target = goals;

            maze = new char *[y];
            for ( int i = 0; i < y; i++ ){
                maze[i] = new char[x];
            }

            for ( int i = 0; i < y; i++ ){
                for ( int j = 0; j < x; j++ ){
                    in >> maze[i][j];
                }
            }
        }

        bool FindGoals( int way, int row, int col, bool success ){    //FindGoals為尋找目標的函式 way代表上次走的方向 row和col代表陣列的行和列 success則代表是否有找到所有目標
            bool isFind = false;                                       //isFind代表有無找到G walk代表行走方向
            int walk = 0;

            if ( maze[row][col] == 'E' ){                               //若當前位置為E 則改成V
                maze[row][col] = 'V';
            }

            else if ( maze[row][col] == 'G' ){                          //若當前位置為G 則將目標數-1 並且把當前位置改成g 方便判斷是否走過
                maze[row][col] = 'g';                                   //如果目標數減至0 則直接回傳true
                target -= 1;
                if ( target == 0 )
                    return true;
            }

            else if ( maze[row][col] == 'O' || maze[row][col] == 'V' || maze[row][col] == 'R' || maze[row][col] == 'g' ){    //若當前位置為O、V、R、g 則代表此路不通 且會回傳false
                return false;
            }


            for ( int i = 0; i < 4; i++ ){                                  //此for迴圈是負責往當前位置的4個方位走
                walk = way + i;                                             //walk代表行走的方向

                if ( walk % 4 == 0 ){                                       //這邊是判斷要往哪個方向去做移動 如果walk除4的餘數為0、1、2、3 就分別往右、下、左、上走
                    if ( col + 1 != x )                                     //若碰到邊界 則直接進入下一次的for
                        if ( FindGoals( walk, row , col + 1, success ) )    //如果有找到目標 isFind就會變為true
                            isFind = true;
                }

                if ( walk % 4 == 1 ){
                    if ( row + 1 != y )
                        if ( FindGoals( walk, row + 1, col, success ) )
                            isFind  = true;
                }

                if ( walk % 4 == 2 ){
                    if ( col - 1 != -1 )
                        if ( FindGoals( walk, row, col - 1, success ) )
                            isFind  = true;
                }

                if ( walk % 4 == 3 ){
                    if ( row - 1 != -1 )
                        if ( FindGoals( walk, row - 1, col, success ) )
                            isFind = true;
                }

                if ( isFind ){                                              //如果找到目標但未達到所需目標數 則繼續尋找 並將不是g的位置改成R
                    if ( success )
                        if ( maze[row][col] != 'g' )
                            maze[row][col] = 'R';
                }


                if ( target == 0 && isFind ){                               //如果目標數為0且找到目標 則終止尋找 並回傳true
                    return true;
                }
            }

            if ( !isFind && maze[row][col] == 'g'  )                        //如果沒找到目標但該位置是g 則回傳true
                return true;

            return isFind;
        }

        void FindV( int way, int row, int col,int walkcount ){
            int walk = 0;

            if ( walkcount >= shortpath && shortpath != -1 )
                return;

            if ( maze[row][col] == 'G' ) {
                if ( walkcount < shortpath || shortpath == -1 )
                    shortpath = walkcount;
                return;
            }

            if ( shortpath == -1 ){
                if ( maze[row][col] == 'E' )
                    maze[row][col] = 'V';
                else if ( maze[row][col] == 'V' || maze[row][col] == 'O' )
                    return;
            }

            else {
                if ( maze[row][col] == 'E' || maze[row][col] == 'V' )
                    maze[row][col] = 'V';
                else if ( maze[row][col] == 'O' )
                    return;
            }


            for ( int i = 0; i < 4; i++ ){
                walk = way + i;
                if ( walk % 4 == 0 ){
                    if ( col + 1 != x )
                        FindV( walk, row , col + 1, walkcount + 1 );
                }

                if ( walk % 4 == 1 ){
                    if ( row + 1 != y )
                        FindV( walk, row + 1, col, walkcount + 1 );

                }

                if ( walk % 4 == 2 ){
                    if ( col - 1 != -1 )
                        FindV( walk, row, col - 1, walkcount + 1 );

                }

                if ( walk % 4 == 3 ){
                    if ( row - 1 != -1 )
                        FindV( walk, row - 1, col, walkcount + 1 );

                }

            }

            return ;

        }

        void FindShortest( int way, int row, int col,int walkcount ){
            int walk = 0;


            if ( walkcount >= shortpath && shortpath != -1 )
                return ;

            if ( maze[row][col] == 'E' )
                maze[row][col] = 'V';

            else if ( maze[row][col] == 'O' || maze[row][col] == 'V')
                return ;

            else if ( maze[row][col] == 'G' ) {
                if ( walkcount < shortpath || shortpath == -1 ) {
                    shortpath = walkcount;
                    Refresh();
                    return ;
                }

                else
                    return ;
            }


            for ( int i = 0; i < 4; i++ ){
                walk = way + i;

                if ( walk % 4 == 0 ){
                    if ( col + 1 != x )
                        FindShortest( walk, row , col + 1, walkcount + 1 );
                }

                if ( walk % 4 == 1 ){
                    if ( row + 1 != y )
                        FindShortest( walk, row + 1, col, walkcount + 1 );

                }

                if ( walk % 4 == 2 ){
                    if ( col - 1 != -1 )
                        FindShortest( walk, row, col - 1, walkcount + 1 );

                }

                if ( walk % 4 == 3 ){
                    if ( row - 1 != -1 )
                        FindShortest( walk, row - 1, col, walkcount + 1 );

                }

            }

            maze[row][col] = 'E';

            return ;
        }

        bool ChoosePath( int way, int row, int col,int walkcount ){
            bool isFind = false;
            int walk = 0;

            if ( walkcount > shortpath )
                return false;

            if ( maze[row][col] == 'E' ){
                maze[row][col] = 'V';
            }

            else if ( maze[row][col] == 'G' ){
                return true;
            }

            else if ( maze[row][col] == 'O' || maze[row][col] == 'V' || maze[row][col] == 'R'){
                return false;
            }


            for ( int i = 0; i < 4; i++ ){
                walk = way + i;

                if ( walk % 4 == 0 ){
                    if ( col + 1 != x )
                        if ( ChoosePath( walk, row , col + 1, walkcount + 1 ) )
                            isFind = true;
                }

                if ( walk % 4 == 1 ){
                    if ( row + 1 != y )
                        if ( ChoosePath( walk, row + 1, col, walkcount + 1 ) )
                            isFind  = true;
                }

                if ( walk % 4 == 2 ){
                    if ( col - 1 != -1 )
                        if ( ChoosePath( walk, row, col - 1, walkcount + 1 ) )
                            isFind  = true;
                }

                if ( walk % 4 == 3 ){
                    if ( row - 1 != -1 )
                        if ( ChoosePath( walk, row - 1, col, walkcount + 1 ) )
                            isFind = true;
                }

                if ( isFind ){
                    maze[row][col] = 'R';
                    return true;
                }
            }

            if ( !isFind )
                maze[row][col] = 'E';

            return isFind;
        }

        void Refresh(){
            for ( int i = 0; i < y; i++ ){
                for ( int j = 0; j < x; j++ ){
                    if ( maze[i][j] == 'R' || maze[i][j] == 'V')
                        maze[i][j] = 'E';
                    if ( maze[i][j] == 'g' )
                        maze[i][j] = 'G';
                }
            }

            return;
        }

        int GetTarget(){                                                    //回傳target的數量
            return  target;
        }

        int GetShort(){
            return shortpath;
        }

        void PrintV(){                                                      //印出經過的路徑
            for ( int i = 0; i < y; i++ ){                                  //用兩個for迴圈分別跑行和列 印出迷宮 且將g印為G
                for ( int j = 0; j < x; j++ ){
                    if ( maze[i][j] == 'g' )
                        cout << 'G';
                    else
                        cout << maze[i][j];
                }
                cout << endl;
            }
        }

        void PrintR(){                                                      //印出走到目標的路徑
            for ( int i = 0; i < y; i++ ){                                  //用兩個for迴圈分別跑行和列 印出迷宮 且將g印為G V印為E
                for ( int j = 0; j < x; j++ ){
                    if ( maze[i][j] == 'g' )
                        cout << 'G';
                    else if ( maze[i][j] == 'V' ) {
                        cout << 'E';
                    }
                    else
                        cout << maze[i][j];
                }
                cout << endl;
            }
        }
};

int main()
{
    do{
        Maze aMaze;                                                             //aMaze為紀錄走到目標的路徑 vMaze為記錄經過的路徑
        Maze vMaze;
        string fileName ;                                                       //fileName為要讀入檔案的名稱 command為使用者的指令 0是退出 1代表一個目標 2代表多個目標
        int x, y;
        string command;
        bool success = false;                                                   //x和y代表行和列 用來記錄讀入資料的行列 success是判斷是否有找完所有目標

        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit          *";
        cout << endl << "* 1. One goal      *";
        cout << endl << "* 2. More goals    *";
        cout << endl << "********************";
        cout << endl << "Input a command(0, 1, 2, 3):";
        cin >> command;

        if ( command == "1" || command == "2" ){                                //若command為1或2 則需輸入檔案名稱並開啟相對應的檔案

            cout << endl << "Input a file number:";
            cin >> fileName;

            fileName = "input" + fileName + ".txt";

            ifstream in;
            in.open( fileName );

            if ( in.fail() )                                                    //若無相對應的檔案 則印出檔案不存在
                cout << endl << fileName << " does not exist!" << endl;

            else {
                int goals;                                                      //若command為2 則需輸入要找的目標數
                if ( command == "2" ){
                    cout << endl << "Number of G (goals):";
                    cin >> goals;
                }
                else                                                            //若command為1 設目標數為1
                    goals = 1;

                in >> x >> y;

                vMaze.Load(fileName, goals);                                    //讀入檔案 分別以vMaze和aMaze紀錄
                aMaze.Load(fileName, goals);

                if ( vMaze.FindGoals( 0, 0, 0, success) && !vMaze.GetTarget() )  //若vMaze找到全部目標 則將success改為true
                    success = true;
                vMaze.PrintV();                                                 //印出所有經過的路徑
                if ( success ) {                                                //若成功找到所有路徑 則將走到目標的路徑印出來
                    cout << endl;
                    aMaze.FindGoals(0, 0, 0, success);
                    aMaze.PrintR();
                }
            }
        }

        else if ( command == "3" ){

            cout << endl << "Input a file number:";
            cin >> fileName;

            fileName = "input" + fileName + ".txt";

            ifstream in;
            in.open( fileName );

            if ( in.fail() )                                                    //若無相對應的檔案 則印出檔案不存在
                cout << endl << fileName << " does not exist!" << endl;

            else {
                vMaze.Load( fileName, 1 );
                aMaze.Load( fileName, 1 );

                if ( vMaze.FindGoals( 0, 0, 0, success) )
                    success = true;

                if ( success ) {
                    vMaze.Refresh();
                    vMaze.FindV( 0, 0, 0, 1 );
                    vMaze.PrintV();
                    cout << endl;

                    aMaze.FindShortest( 0, 0, 0, 1 );
                    aMaze.ChoosePath( 0, 0, 0, 1 );
                    aMaze.PrintR();

                    cout << endl << "Shortest path length = " << aMaze.GetShort() << endl;
                }

                else{
                    vMaze.PrintV();
                    cout << endl << "### There is no path to find a goal! ###" << endl ;
                }
            }
        }

        else if ( command == "0" )                                              //若command為0 則結束程式
            break;

        else                                                                    //若command為其他東西 則印出指令不存在
            cout << endl << "Command does not exist!" << endl;

    }while(true);
    system( "pause" );
    return 0;
}
