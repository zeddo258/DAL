// 11127252, 雷國裕
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std ;

enum Face { UP, DOWN, LEFT, RIGHT } ; // 設定行走方向的常數
enum Modes { ONE, MORE, SHORT } ;     // 設定尋找目標的模式
const int FILE_NOT_EXIST = -2132 ;    // 檔案不存在代號

class Maze { // 迷宮類別
    public:
        void MazePlay() {
            /*
            迷宮的開始，負責呼叫迷宮執行、列印迷宮等函數
            輸入：無
            輸出：無
            */
            bool found = false ;
            if ( findShortest ) {
                findShortest = false ;
                int goal = goals ;
                if ( MazeRun( 0,0, RIGHT, goals, false, 1 ) ) {
                    MazeReset( goal ) ;
                    found = MazeRun( 0,0, RIGHT, goals, false, 1 ) ;
                } // if

                findShortest = true ;
            } // if
            else {
                found = MazeRun( 0,0, RIGHT, goals, false, 1 ) ; // 從(0,0)朝向右邊開始走迷宮並得到是否達成所有目標
            } // else

            MazePrint( found ) ;                           // 列印經過的地方與達成路徑
        } // MazePlay()

        int MazeSetup( string fileName, Modes mode ) {
            /*
            整理檔案名稱、呼叫迷宮創建函數、設定目標數量
            輸入：檔案代號(fileName)、目標數量模式(mode)
            輸出：0代表運作正常，接收到開檔失敗就回傳exception
            */
            string file = "input" ;                        // 設定檔名開頭
            file += fileName ;                             // 將檔名加上檔案代號
            file += ".txt" ;                               // 將檔名加上附檔名
            goals = 1 ;                                    // 預設目標數量為1
            findShortest = false ;                         // 預設不是最短路徑模式
            shortestPath = -1 ;                            // 預設還沒有最短路徑
            foundPath = false ;
            if ( MazeCreate( file ) == FILE_NOT_EXIST ) {  // 讀檔並創建迷宮，如果接收到exception就
                return FILE_NOT_EXIST ;                    // 往上丟
            } // if ( MazeCreate( file ) == FILE_NOT_EXIST )

            if ( mode == MORE ) {                          // 如果是多重目標模式就
                cout << endl << "Number of G (goals): " ;
                cin >> goals ;                             // 輸入目標數量
                while ( goals < 1 || goals > 100 ) {       // 持續輸入直到目標數量在[1, 100]
                    cout << endl << "### The number must be in [1,100] ###" << endl ;
                    cout << endl << "Number of G (goals): " ;
                    cin >> goals ;
                } // while ( goals < 1 || goals > 100 )
            } // if ( mode == MORE )
            else if ( mode == SHORT ) {                    // 如果是最短路徑模式就
                findShortest = true ;                      // 開啟最短路徑模式
            } // if ( mode == SHORT )

            return 0 ;                                     // 正常執行
        } // MazeSetup( string fileName, Modes mode )

    private:
        int length ;                // 迷宮的長度
        int height ;                // 迷宮的高度
        int goals ;                 // 目標數量
        bool findShortest ;
        int shortestPath ;
        bool foundPath ;
        vector<string> mazeWalk ;   // 要走的迷宮
        vector<string> maze ;       // 迷宮主體
        vector<string> mazeFound ;  // 儲存找到的目標位置
        vector<string> mazeRoute ;  // 儲存達成路徑

        void MazeReset( int goal ) {
            goals = goal ;
            mazeFound = maze ;
            mazeRoute = maze ;
            mazeWalk = maze ;
            findShortest = true ;
        } // MazeReset()

        void MazePrint( bool found ) {
            /*
            負責列印走過的地方、檢測是否達成所有目標並列印達成路徑
            輸入：是否達成所有目標(found)
            輸出：無
            */
            cout << endl ;
            for ( int i = 0 ; i < height ; i++ ) {      // 列印所有經過的地方
                cout << mazeWalk[i] << endl ;
            } // for ( int i = 0 ; i < height ; i++ )

            cout << endl ;

            if ( found || foundPath ) {                              // 如果達成所有目標就
                for ( int i = 0 ; i < height ; i++ ) {  // 列印達成目標的路徑
                    cout << mazeRoute[i] << endl ;
                } // for ( int i = 0 ; i < height ; i++ )

                if ( findShortest ) {                   // 如果是最短路徑模式就印出長度
                    cout << endl << "Shortest path length = " << shortestPath ;
                } // if ( findShortest )
            } // if ( found || foundPath )
            else if ( !foundPath && findShortest ) {
                cout << endl << "### There is no path to find a goal! ###" ;
            } // if
        } // MazePrint( bool found )

        int MazeCreate( string file ) {
            /*
            依讀入檔案內容創建一個迷宮
            輸入：檔案名稱(file)
            輸出：0代表運作正常，開檔失敗就回傳exception
            附加效果：讀入的資料會存在length, height, maze, mazeFound, mazeRoute
            */
            ifstream f ;                                     // 創造讀檔系統
            string line ;                                    // 預備讀入的字串
            f.open( file ) ;                                 // 開起檔案
            if ( f.fail() ) {                                // 如果開檔失敗就
                return FILE_NOT_EXIST ;                      // 丟出excetpion
            } // if ( f.fail() )

            f >> length ;                                    // 讀入迷宮長度
            f >> height ;                                    // 讀入迷宮高度
            while ( !f.eof() ) {                             // 不斷讀取直到目前為檔案末
                f >> line ;                                  // 讀入迷宮每一行
                if ( !f.fail() ) {                           // 如果讀取成功就
                    maze.push_back( line ) ;                 // 把讀取內容放入迷宮
                } // if ( !f.fail() )
            } // while ( !f.eof() )

            f.close() ;                                      // 關閉檔案
            mazeFound = maze ;                               // 把迷宮內容複製儲存到
            mazeRoute = maze ;                               // 3種不同用途的資料預備
            mazeWalk = maze ;
            return 0 ;
        } // MazeCreate( string file )

        bool MazeRun( int h, int l, Face facing, int & goal, bool found, int step ) {
            /*
            使用遞迴方法來走迷宮
            輸入：現在座標(l,h)，面對方向(facing)，剩餘目標數量(goal)
            輸出：是否找到目標(found)
            附加效果：每找到一個目標，剩餘目標數量(goal)會減少一個
            */
            if ( findShortest ) {
                if ( shortestPath != -1 && step >= shortestPath ) {
                    return false ;
                } // if ( shortestPath != -1 && step >= shortestPath )
            } // if ( findShortest )

            if ( mazeWalk[h][l] == 'G' && mazeFound[h][l] != 'F' ) {                 // 如果找到沒有重複找過的目標就
                found = true ;                                                       // 設定為找到目標
                mazeFound[h][l] = 'F' ;                                              // 設定當前位置為找過的目標
                if ( goal == 1 ) {                                                   // 如果這是最後一個目標就
                    if ( findShortest ) {
                        if ( shortestPath == -1 || step < shortestPath ) {
                            mazeRoute = maze ;
                            mazeFound = maze ;
                            shortestPath = step ;
                            foundPath = true ;
                        } // if ( shortestPath == -1 || step < shortestPath )
                    } // if ( findShortest )
                    else {
                        goal-- ;                                                     // 目標數量-1
                    } // else

                    return found ;                                                   // 終止條件，逐步將遞迴收起來
                } // if ( goal == 1 )
                else {                                                               // 如果這不是最後一個目標就
                    goal-- ;                                                         // 目標數量-1並繼續尋找
                } // else
            } // if ( maze[h][l] == 'G' && mazeFound[h][l] != 'F' )
            else if ( mazeWalk[h][l] != 'G' ) {                                      // 如果當前位置不是目標就
                mazeWalk[h][l] = 'V' ;                                               // 紀錄走過的位置
            } // else if ( maze[h][l] != 'G' )

            int turn = 0 ;                                                           // 設定轉彎次數預設為0
            while ( turn < 3 && goal != 0 ) {                                        // 如果轉彎3次或找完所有目標就離開迴圈
                if ( facing == RIGHT ) {                                             // 如果現在朝向右邊
                    if ( l + 1 < mazeWalk[h].size() && mazeWalk[h][l + 1] != 'O' && ( findShortest || mazeWalk[h][l + 1] != 'V' ) ) {
                                                                                     // 如果可往右走
                        if ( found && findShortest ) {
                            MazeRun( h, l + 1, facing, goal, false, step + 1 ) ; // 遞迴呼叫往右走並取得是否找到目標
                        } // if
                        else {
                            found = MazeRun( h, l + 1, facing, goal, false, step + 1 ) ; // 遞迴呼叫往右走並取得是否找到目標
                        } // else
                    } // if ( l + 1 < maze[h].size() && maze[h][l + 1] != 'O' && maze[h][l + 1] != 'V' )

                    facing = DOWN ;                                                  // 轉彎朝向下面
                    if ( turn == 1 ) {                                               // 如果已經轉過一次就
                        facing = LEFT ;                                              // 再轉一次
                    } // if ( turn == 1 )

                    turn++ ;                                                         // 轉彎次數+1
                } // if ( facing == RIGHT )

                if ( turn >= 3 || goal == 0 )                                        // 如果轉彎3次或找完所有目標就離開迴圈
                    break ;

                if ( facing == DOWN ) {                                              // 如果現在朝向下面
                    if ( h + 1 < mazeWalk.size() && mazeWalk[h + 1][l] != 'O' && ( findShortest || mazeWalk[h + 1][l] != 'V' ) ) {
                                                                                     // 如果可往下走
                        if ( found && findShortest ) {
                            MazeRun( h + 1, l, facing, goal, false, step + 1 ) ; // 遞迴呼叫往下走並取得是否找到目標
                        } // if
                        else {
                            found = MazeRun( h + 1, l, facing, goal, false, step + 1 ) ; // 遞迴呼叫往下走並取得是否找到目標
                        }
                    } // if ( h + 1 < maze.size() && maze[h + 1][l] != 'O' && maze[h + 1][l] != 'V' )

                    facing = LEFT ;                                                  // 轉彎朝向左邊
                    if ( turn == 1 ) {                                               // 如果已經轉過一次就
                        facing = UP ;                                                // 再轉一次
                    } // if ( turn == 1 )

                    turn++ ;                                                         // 轉彎次數+1
                } // if ( facing == DOWN )

                if ( turn >= 3 || goal == 0 )                                        // 如果轉彎3次或找完所有目標就離開迴圈
                    break ;

                if ( facing == LEFT ) {                                              // 如果現在朝向左邊
                    if ( l - 1 >= 0 && mazeWalk[h][l - 1] != 'O' && ( findShortest || mazeWalk[h][l - 1] != 'V' ) ) {
                                                                                     // 如果可往左走
                        if ( found && findShortest ) {
                            MazeRun( h, l - 1, facing, goal, false, step + 1 ) ; // 遞迴呼叫往左走並取得是否找到目標
                        } // if
                        else {
                            found = MazeRun( h, l - 1, facing, goal, false, step + 1 ) ; // 遞迴呼叫往左走並取得是否找到目標
                        }
                    } // if ( l - 1 >= 0 && maze[h][l - 1] != 'O' && maze[h][l - 1] != 'V' )

                    facing = UP ;                                                    // 轉彎朝向上面
                    if ( turn == 1 ) {                                               // 如果已經轉過一次就
                        facing = RIGHT ;                                             // 再轉一次
                    } // if ( turn == 1 )

                    turn++ ;                                                         // 轉彎次數+1
                } // if ( facing == LEFT )

                if ( turn >= 3 || goal == 0 )                                        // 如果轉彎3次或找完所有目標就離開迴圈
                    break ;

                if ( facing == UP ) {                                                // 如果現在朝向上面
                    if ( h - 1 >= 0 && mazeWalk[h - 1][l] != 'O' && ( findShortest || mazeWalk[h - 1][l] != 'V' ) ) {
                                                                                     // 如果可往上走
                        if ( found && findShortest ) {
                            MazeRun( h - 1, l, facing, goal, false, step + 1 ) ;
                        } // if
                        else {
                            found = MazeRun( h - 1, l, facing, goal, false, step + 1 ) ; // 遞迴呼叫往上走並取得是否找到目標
                        } // else
                    } // if ( h - 1 >= 0 && maze[h - 1][l] != 'O' && maze[h - 1][l] != 'V' )

                    facing = RIGHT ;                                                 // 轉彎朝向右邊
                    if ( turn == 1 ) {                                               // 如果已經轉過一次就
                        facing = DOWN ;                                              // 再轉一次
                    } // if ( turn == 1 )

                    turn++ ;                                                         // 轉彎次數+1
                } // if ( facing == UP )
            } // while ( turn < 3 && goal != 0 )

            if ( found && mazeWalk[h][l] != 'G' ) {                                  // 如果先前找到目標就
                mazeRoute[h][l] = 'R' ;                                              // 紀錄走到這個目標的路徑
            } // if ( found && maze[h][l] != 'G' )

            return found ;                                                           // 回傳是否找到目標
        } // MazeRun( int h, int l, Face facing, int & goal, bool found, int step )
} ; // class Maze

int main() {
    char command = 0 ;                                 // 指令種類
    while ( true ) {                                   // 無限執行輸入指令
        Maze aMaze ;                                   // 創造一個迷宮物件
        string fileName ;                              // 檔案名稱代號
        Modes mode = ONE ;                             // 預設模式目標為1個目標

        cout << endl << "*** Path Finding ***" ;
        cout << endl << "* 0. Quit          *" ;
        cout << endl << "* 1. One goal      *" ;
        cout << endl << "* 2. More goals    *" ;
        cout << endl << "* 3. Shortest path *" ;
        cout << endl << "********************" ;
        cout << endl << "Input a command(0, 1, 2, 3): " ;
        cin >> command ;                               // 使用者輸入指令
        if ( command == '0' ) {                          // 輸入指令為0則退出程式
            break ;
        } // if ( command == '0' )
        else if ( command == '1' || command == '2' || command == '3' ) {     // 輸入指令為其他有效指令
            if ( command == '2' ) {                      // 輸入指令為2時設定成多重目標模式
                mode = MORE ;
            } // if ( command == '2' )
            else if ( command == '3' ) {
                mode = SHORT ;
            } // if ( command == '3' )

            cout << endl << "Input a file number (e.g., 201, 202, ...): " ;
            cin >> fileName ;                          // 輸入檔案代號
            if ( aMaze.MazeSetup( fileName, mode ) == FILE_NOT_EXIST ) {
                                                       // 創建迷宮地圖，如果接收到exception就
                cout << endl << "input" << fileName << ".txt does not exist!" ;
                continue ;                             // 重新輸入指令
            } // if ( aMaze.MazeSetup( fileName, mode ) == FILE_NOT_EXIST )

            aMaze.MazePlay() ;                         // 開始走迷宮
            mode = ONE ;                               // 執行完重新設定預設目標數量
        } // if ( command == '1' || command == '2' || command == '3' )
        else {                                         // 輸入指令為無效指令
            cout << endl << "Command does not exist!" ;
        } // else
    } // while ( true )

    system( "pause" ) ;                                // 暫停動作以確認執行結果
    return 0 ;
} // main()
