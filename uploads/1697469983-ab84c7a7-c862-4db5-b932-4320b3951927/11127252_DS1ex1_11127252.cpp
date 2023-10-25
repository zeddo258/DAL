// 11127252, 雷國裕
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std ;

enum Face { UP, DOWN, LEFT, RIGHT } ; // 設定行走方向的常數
enum Modes { ONE, MORE } ;            // 設定是否多重目標的常數
const int FILE_NOT_EXIST = -2132 ;    // 檔案不存在代號

class Maze { // 迷宮類別
    public:
        void MazePlay() {
            /*
            迷宮的開始，負責呼叫迷宮執行、列印迷宮等函數
            輸入：無
            輸出：無
            */
            bool found = MazeRun( 0,0, RIGHT, goals ) ;    // 從(0,0)朝向右邊開始走迷宮並得到是否達成所有目標
            MazePrint( found ) ;                           // 列印經過的地方與達成路徑
        } // MazePlay()

        int MazeSetup( string fileName, Modes mode ) {
            /*
            整理檔案名稱、呼叫迷宮創建函數、設定目標數量
            輸入：檔案代號(fileName)、目標數量模式(mode)
            輸出：目標數量(goal)，如果是-1則代表exception
            */
            string file = "input" ;                        // 設定檔名開頭
            file += fileName ;                             // 將檔名加上檔案代號
            file += ".txt" ;                               // 將檔名加上附檔名
            goals = 1 ;                                    // 預設目標數量為1
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

            return 0 ;                                     // 正常執行
        } // MazeSetup( string fileName, Modes mode )

    private:
        int length ;                // 迷宮的長度
        int height ;                // 迷宮的高度
        int goals ;                 // 目標數量
        vector<string> maze ;       // 迷宮主體
        vector<string> mazeFound ;  // 儲存找到的目標位置
        vector<string> mazeRoute ;  // 儲存達成路徑

        void MazePrint( bool found ) {
            /*
            負責列印走過的地方、檢測是否達成所有目標並列印達成路徑
            輸入：是否達成所有目標(found)
            輸出：無
            */
            cout << endl ;
            for ( int i = 0 ; i < height ; i++ ) {      // 列印所有經過的地方
                cout << maze[i] << endl ;
            } // for ( int i = 0 ; i < height ; i++ )

            cout << endl ;

            if ( found ) {                              // 如果達成所有目標就
                for ( int i = 0 ; i < height ; i++ ) {  // 列印達成目標的路徑
                    cout << mazeRoute[i] << endl ;
                } // for ( int i = 0 ; i < height ; i++ )
            } // if ( found )
        } // MazePrint( bool found )

        int MazeCreate( string file ) {
            /*
            依讀入檔案內容創建一個迷宮
            輸入：檔案名稱(file)
            輸出：0代表運作正常，-1代表開檔失敗exception
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
            mazeRoute = maze ;                               // 2種不同用途的資料預備
            return 0 ;
        } // MazeCreate( string file )

        bool MazeRun( int h, int l, Face facing, int & goal ) {
            /*
            使用遞迴方法來走迷宮
            輸入：現在座標(l,h)，面對方向(facing)，剩餘目標數量(goal)
            輸出：是否找到目標(found)
            附加效果：每找到一個目標，剩餘目標數量(goal)會減少一個
            */
            bool found = false ;                                      // 預設還沒找到目標
            if ( maze[h][l] == 'G' && mazeFound[h][l] != 'F' ) {      // 如果找到沒有重複找過的目標就
                found = true ;                                        // 設定為找到目標
                mazeFound[h][l] = 'F' ;                               // 設定當前位置為找過的目標
                if ( goal == 1 ) {                                    // 如果這是最後一個目標就
                    goal-- ;                                          // 目標數量-1
                    return found ;                                    // 終止條件，逐步將遞迴收起來
                } // if ( goal == 1 )
                else {                                                // 如果這不是最後一個目標就
                    goal-- ;                                          // 目標數量-1並繼續尋找
                } // else
            } // if ( maze[h][l] == 'G' && mazeFound[h][l] != 'F' )
            else if ( maze[h][l] != 'G' ) {                           // 如果當前位置不是目標就
                maze[h][l] = 'V' ;                                    // 紀錄走過的位置
            } // if ( maze[h][l] != 'G' )

            int turn = 0 ;                                            // 設定轉彎次數預設為0
            while ( turn < 4 && goal != 0 ) {                         // 如果轉彎4次或找完所有目標就離開迴圈
                if ( facing == RIGHT ) {                              // 如果現在朝向右邊
                    if ( l + 1 < maze[h].size() && maze[h][l + 1] != 'O' && maze[h][l + 1] != 'V' ) {
                                                                      // 如果可往右走
                        found = MazeRun( h, l + 1, facing, goal ) ;   // 遞迴呼叫往右走並取得是否找到目標
                    } // if ( l + 1 < maze[h].size() && maze[h][l + 1] != 'O' && maze[h][l + 1] != 'V' )

                    facing = DOWN ;                                   // 轉彎朝向下面
                    turn++ ;                                          // 轉彎次數+1
                } // if ( facing == RIGHT )

                if ( turn >= 4 || goal == 0 )                         // 如果轉彎4次或找完所有目標就離開迴圈
                    break ;

                if ( facing == DOWN ) {                               // 如果現在朝向下面
                    if ( h + 1 < maze.size() && maze[h + 1][l] != 'O' && maze[h + 1][l] != 'V' ) {
                                                                      // 如果可往下走
                        found = MazeRun( h + 1, l, facing, goal ) ;   // 遞迴呼叫往下走並取得是否找到目標
                    } // if ( h + 1 < maze.size() && maze[h + 1][l] != 'O' && maze[h + 1][l] != 'V' )

                    facing = LEFT ;                                   // 轉彎朝向左邊
                    turn++ ;                                          // 轉彎次數+1
                } // if ( facing == DOWN )

                if ( turn >= 4 || goal == 0 )                         // 如果轉彎4次或找完所有目標就離開迴圈
                    break ;

                if ( facing == LEFT ) {                               // 如果現在朝向左邊
                    if ( l - 1 >= 0 && maze[h][l - 1] != 'O' && maze[h][l - 1] != 'V' ) {
                                                                      // 如果可往左走
                        found = MazeRun( h, l - 1, facing, goal ) ;   // 遞迴呼叫往左走並取得是否找到目標
                    } // if ( l - 1 >= 0 && maze[h][l - 1] != 'O' && maze[h][l - 1] != 'V' )

                    facing = UP ;                                     // 轉彎朝向上面
                    turn++ ;                                          // 轉彎次數+1
                } // if ( facing == LEFT )

                if ( turn >= 4 || goal == 0 )                         // 如果轉彎4次或找完所有目標就離開迴圈
                    break ;

                if ( facing == UP ) {                                 // 如果現在朝向上面
                    if ( h - 1 >= 0 && maze[h - 1][l] != 'O' && maze[h - 1][l] != 'V' ) {
                                                                      // 如果可往上走
                        found = MazeRun( h - 1, l, facing, goal ) ;   // 遞迴呼叫往上走並取得是否找到目標
                    } // if ( h - 1 >= 0 && maze[h - 1][l] != 'O' && maze[h - 1][l] != 'V' )

                    facing = RIGHT ;                                  // 轉彎朝向右邊
                    turn++ ;                                          // 轉彎次數+1
                } // if ( facing == UP )
            } // while ( turn < 4 && goal != 0 )

            if ( found && maze[h][l] != 'G' ) {                       // 如果先前找到目標就
                mazeRoute[h][l] = 'R' ;                               // 紀錄走到這個目標的路徑
            } // if ( found && maze[h][l] != 'G' )

            return found ;                                            // 回傳是否找到目標
        } // MazeRun( int h, int l, Face facing, int & goal )
} ; // class Maze

int main() {
    int command = 0 ;                                  // 指令種類
    while ( true ) {                                   // 無限執行輸入指令
        Maze aMaze ;                                   // 創造一個迷宮物件
        string fileName ;                              // 檔案名稱代號
        Modes mode = ONE ;                             // 預設目標數量為1

        cout << endl << "*** Path Finding***" ;
        cout << endl << "* 0. Quit         *" ;
        cout << endl << "* 1. One goal     *" ;
        cout << endl << "* 2. More goals   *" ;
        cout << endl << "*******************" ;
        cout << endl << "Input a command(0, 1, 2): " ;
        cin >> command ;                               // 使用者輸入指令
        if ( command == 0 ) {                          // 輸入指令為0則退出程式
            break ;
        } // if ( command == 0 )
        else if ( command == 1 || command == 2 ) {     // 輸入指令為其他有效指令
            if ( command == 2 ) {                      // 輸入指令為2時設定成多重目標模式
                mode = MORE ;
            } // if ( command == 2 )

            cout << endl << "Input a file number (e.g., 201, 202, ...): " ;
            cin >> fileName ;                          // 輸入檔案代號
            if ( aMaze.MazeSetup( fileName, mode ) == FILE_NOT_EXIST ) {
                                                       // 創建迷宮地圖，如果接收到exception就
                cout << endl << "input" << fileName << ".txt does not exist!" ;
                continue ;                             // 重新輸入指令
            } // if ( aMaze.MazeSetup( fileName, mode ) == FILE_NOT_EXIST )

            aMaze.MazePlay() ;                         // 開始走迷宮
            mode = ONE ;                               // 執行完重新設定預設目標數量
        } // if ( command == 1 || command == 2 )
        else {                                         // 輸入指令為無效指令
            cout << endl << "Command does not exist!" ;
        } // else
    } // while ( true )

    system( "pause" ) ;                                // 暫停動作以確認執行結果
    return 0 ;
} // main()
