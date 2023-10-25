// 11127205 屈怡安
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdlib.h>
using namespace std ;

typedef struct mouse{
    int x ; // 老鼠到達G的x座標
    int y ; // 老鼠到達G的y座標
    bool success ;
} Mouse ;


class Maze {
    vector<vector<int>> maze; // 迷宮矩陣
    vector<int> g_x ; //所有G的x座標
    vector<int> g_y ; //所有G的y座標
    int goalsVisited = 0 ; // 走過多少目標
    bool beenToG = false ; // 在岔路口後是否有走到G

public:
    Maze( string fileNum ) {
        //bool inputMaze( string fileNum) { // 匯入迷宮txt.檔並轉成二元整數vector形式
        // 讀取文件第一行迷宮大小
        string line;
        ifstream in(fileNum);
        getline(in, line) ;
        // 將string轉成int
        string num1, num2 ;
        int x, y, c = 0 ;

        while ( line[c] == '0' || line[c] == '1' || line[c] == '2' || line[c] == '3' || line[c] == '4' || line[c] == '5' ||
                line[c] == '6' || line[c] == '7' || line[c] == '8' || line[c] == '9' ) {
            num1 = num1 + line[c] ;
            c ++ ;
        }

        c = c + 1 ;
        x = stoi(num1) ;

        while ( line[c] == '0' || line[c] == '1' || line[c] == '2' || line[c] == '3' || line[c] == '4' || line[c] == '5' ||
                line[c] == '6' || line[c] == '7' || line[c] == '8' || line[c] == '9' ) {
            num2 = num2 + line[c] ;
            c ++ ;
        }
        y = stoi(num2) ;

        // 逐行讀取文件内容並將每行添加到vector中
        // 加入邊界
        char ch ;
        int p, wall = 0 ; // 邊界(牆壁)
        vector<int>maze_wall ;

        for ( int k = 0; k < ( x+2 ); k ++ )
            maze_wall.push_back(wall) ;

        maze.push_back(maze_wall) ; // 加入「上邊界」

        for( int i = 0; i < y; i ++ ) {
            getline(in, line) ;
            vector<int>maze_;
            for( int j = 0; j < x; j ++ ) {
                if ( j == 0 ) {
                    maze_.push_back(wall) ;
                }
                ch = line[j] ;
                if ( ch == 'O' )
                    p = 1 ;
                else if ( ch == 'E' )
                    p = 2 ;
                else if ( ch == 'G' )
                    p = 3 ;
                maze_.push_back(p) ;
            }
            maze_.push_back(wall) ;
            maze.push_back(maze_) ;
        }
        maze.push_back(maze_wall) ; // 加入「下邊界」
        in.close(); // 關閉文件

    } // inputMaze()




    Mouse findPath( char way, int x, int y, int n, int command ) { // 老鼠走迷宮

        Mouse mouse ;

        if ( maze[x][y] == 3 ) { // 若此點為G
            if ( command == 1 ) { // command=1時一到G就return true，並紀錄結果(成功)
                mouse.success = true ;
                mouse.x = x;
                mouse.y = y;
                return mouse ;
            } // if ( command == 1 )
            else if ( command == 2 ) { // command=2時，判斷是否經過指定的G數

                beenToG = true ; // 若到達G則為true，再回到岔路口時會變為false
                if ( maze[x+1][y] == 2 || maze[x-1][y] == 2 || maze[x][y+1] == 2 || maze[x][y-1] == 2 ) // 若G前方還有路可走，重置是否到達過G的bool為false
                    beenToG = false ;

                int alreadyRecorded = 0 ; // 是否曾經過此G?
                for ( int i = 0; i < g_x.size(); i ++ ) {
                    if( x == g_x[i] && y == g_y[i] ) // 若經過，alreadyRecorded = 1
                        alreadyRecorded = 1 ;
                }
                if ( alreadyRecorded == 0 ) {  // 若第一次來此G
                    goalsVisited ++ ; // 走過的G數+1
                    g_x.push_back(x) ;
                    g_y.push_back(y) ;
                }

                if ( goalsVisited == n ) { // 若走完全部目標
                    // return true，並紀錄結果(成功)
                    mouse.success = true ;
                    mouse.x = x;
                    mouse.y = y;
                    return mouse ;
                }
            } // else if ( command == 2 )
        } // if ( maze[x][y] == 3 )

        if ( maze[x][y] == 1 || maze[x][y] == 4 || maze[x][y] == 6 || maze[x][y] == 0 ) { // 若位於「障礙」，return false
            mouse.success = false ;
            return mouse ;
        }

        else {
            maze[x][y] = 4 ; // 走過的點變為V

            if ( way == 'R' ) { // 目前行走方向為右

                // 如果在走到G後到達岔路口 // 重新紀錄是否到達G
                if ( maze[x][y+1] == 2 && ( maze[x-1][y] == 2 || maze[x+1][y] == 2 ) ) { // 若右、上或下為空，位於岔路口
                    beenToG = false ;
                }
                mouse = findPath( way, x, y + 1, n, command ) ; // 看右邊的格子是甚麼(目標or障礙)
                if ( mouse.success == true ) // 右邊為G
                    return mouse;

                // 右邊不能走
                // 依序往另外三個方向走
                // 若哪方不為障礙，變更持續行走方向
                way = 'D' ; // 往下
                mouse = findPath( way, x + 1, y, n, command ) ;
                if ( mouse.success == true )
                    return mouse ;

                // 下面不能走
                way = 'L' ; // 往左
                mouse = findPath( way, x, y - 1, n, command ) ;
                if ( mouse.success == true )
                    return mouse;

                // 左邊不能走
                way = 'U' ; // 往上
                mouse = findPath( way, x - 1, y, n, command ) ;
                if ( mouse.success == false ) {// 上面不能走 // 四個方向都不能走
                    for ( int i = 0; i < g_x.size(); i ++ ) { // 若此格為G，將紀錄是否到達過G的bool設為true(在死路中，從G返回岔路口的路上，須將此路設為R)
                        if ( x == g_x[i] && y == g_y[i] )
                            beenToG = true ;
                    }
                    if ( beenToG == false ) // 在死路往返時，在岔路口後不曾抵達G的情況下，才不將此路徑視為R
                        maze[x][y] = 6 ;
                    return mouse ;
                }
            }

            else if ( way == 'D' ) {

                // 如果在走到G後到達岔路口 // 重新紀錄是否到達G
                if ( maze[x+1][y] == 2 && ( maze[x][y-1] == 2 || maze[x][y+1] == 2 ) ) { // 若下、左或右為空，位於岔路口
                    beenToG = false ;
                }

                mouse = findPath(way, x + 1, y, n, command ) ;
                if ( mouse.success == true )
                    return mouse; // 下面為G

                // 下面不能走
                // 依序往另外三個方向走
                //  若哪方不為障礙，變更持續行走方向
                way = 'L' ;
                mouse = findPath(way, x, y - 1, n, command ) ;
                if ( mouse.success == true )
                    return mouse;

                //  左邊不能走
                //  往上
                way = 'U' ;
                mouse = findPath(way, x - 1, y, n, command ) ;
                if ( mouse.success == true )
                    return mouse;

                // 上面不能走
                // 往右
                way = 'R' ;
                mouse = findPath(way, x, y + 1, n, command ) ;
                if ( mouse.success == false ) { // 右邊不能走 // 四個方向都不能走
                    for ( int i = 0; i < g_x.size(); i ++ ) { // 若此格為G，將紀錄是否到達過G的bool設為true(在死路中，從G返回岔路口的路上，須將此路設為R)
                        if ( x == g_x[i] && y == g_y[i] )
                            beenToG = true ;
                    }
                    if ( beenToG == false ) // 在死路往返時，在岔路口後不曾抵達G的情況下，才不將此路徑視為R
                        maze[x][y] = 6 ;
                    return mouse ;
                }
            }
            else if ( way == 'L' ) {

                // 如果在走到G後(beenToG == true)到達岔路口 // 重新紀錄是否到達G
                if ( maze[x][y-1] == 2 && ( maze[x+1][y] == 2 || maze[x-1][y] == 2 ) ) { // 若左、上或下為空，位於岔路口
                    beenToG = false ;
                }

                mouse = findPath(way, x, y - 1, n, command ) ;

                if ( mouse.success == true )
                    return mouse; // 左邊為G

                //  左邊不能走
                //  依序往另外三個方向走
                //  若哪方不為障礙，變更持續行走方向
                way = 'U' ;
                mouse = findPath(way, x - 1, y, n, command ) ;
                if ( mouse.success == true )
                    return mouse;

                // 上面不能走
                // 往右
                way = 'R' ;
                mouse = findPath(way, x, y + 1, n, command ) ;
                if ( mouse.success == true )
                    return mouse;

                //  右邊不能走
                // 往下
                way = 'D' ;
                mouse = findPath(way, x + 1, y, n, command ) ;
                if  ( mouse.success == false && beenToG == false ) {  // 下面不能走 // 四個方向都不能走
                    for ( int i = 0; i < g_x.size(); i ++ ) { // 若此格為G，將紀錄是否到達過G的bool設為true(在死路中，從G返回岔路口的路上，須將此路設為R)
                        if ( x == g_x[i] && y == g_y[i] )
                            beenToG = true ;
                    }
                    if ( beenToG == false ) // 在死路往返時，在岔路口後不曾抵達G的情況下，才不將此路徑視為R
                        maze[x][y] = 6 ;
                    return mouse ;
                }
            }
            else if ( way == 'U' ) {

                if ( maze[x-1][y] == 2 && ( maze[x][y+1] == 2 || maze[x][y-1] == 2 ) ) { // 若上、左或右為空，位於岔路口
                    beenToG = false ;
                }

                mouse = findPath(way, x - 1, y, n, command ) ;

                if ( mouse.success == true )
                    return mouse; // 上面為G

                // 上面不能走
                // 依序往另外三個方向走
                // 若哪方不為障礙，變更持續行走方向
                way = 'R' ;
                mouse = findPath(way, x, y + 1, n, command ) ;
                if ( mouse.success == true )
                    return mouse;

                // 右邊不能走
                way = 'D' ; // 往下
                mouse = findPath(way, x + 1, y, n, command ) ;
                if ( mouse.success == true )
                    return mouse;

                // 下面不能走
                way = 'L' ; // 往左
                mouse = findPath(way, x, y - 1, n, command ) ;
                if ( mouse.success == false && beenToG == false ) { // 左邊不能走 // 四個方向都不能走
                    for ( int i = 0; i < g_x.size(); i ++ ) { // 若此格為G，將紀錄是否到達過G的bool設為true(在死路中，從G返回岔路口的路上，須將此路設為R)
                        if ( x == g_x[i] && y == g_y[i] )
                            beenToG = true ;
                    }
                    if ( beenToG == false ) // 在死路往返時，在岔路口後不曾抵達G的情況下，才不將此路徑視為R
                        maze[x][y] = 6 ;
                    return mouse ;
                }
            }
        } // else
    } // findPath()


    int show1( int command ) { // 所有走過的都印V

//         1: O
//         2: E
//         3: G
//         4: V
//         5: R
//         6: //走過，但不在成功路徑內

        if ( command == 2 ) { // 若command=2，將迷宮中走過的G(在過程中變4)變回3
            for ( int i = 0; i < g_x.size(); i ++ )
                maze[g_x[i]][g_y[i]] = 3 ;
        }

        for ( int i = 1; i < maze.size() - 1; i++ ) { // 不須印邊界
            for ( int j = 0; j < maze[i].size(); j++ ) {
                if ( maze[i][j] == 1 )
                    cout << 'O' ;
                if ( maze[i][j] == 2 )
                    cout << 'E' ;
                if ( maze[i][j] == 3 )
                    cout << 'G' ;
                if ( maze[i][j] == 4 || maze[i][j] == 6 ) {
                    cout << 'V' ;
                }
            }
            cout << "\n" ;
        }
        cout << endl ;
    } // show1()

    int show2( int command ) { // 除了成功路徑印R，其他走過的印E

//         1: O
//         2: E
//         3: G
//         4: V
//         5: R
//         6: //走過，但不在成功路徑內


        if ( command == 2 ) { // 若command=2，將迷宮中走過的G(在過程中變4)變回3
            for ( int i = 0; i < g_x.size(); i ++ )
                maze[g_x[i]][g_y[i]] = 3 ;
        }

        for ( int i = 1; i < maze.size() - 1; i++ ) { // 不須印邊界
            for ( int j = 0; j < maze[i].size(); j++ ) {
                if ( maze[i][j] == 1 )
                    cout << 'O' ;
                if ( maze[i][j] == 2 )
                    cout << 'E' ;
                if ( maze[i][j] == 3 )
                    cout << 'G' ;
                if ( maze[i][j] == 4 )
                    cout << 'R' ;
                if ( maze[i][j] == 6 )
                    cout << 'E' ;
            }
            cout << "\n" ;
        }
        cout << endl ;
    } // show2()
}; // Maze



int main() {
    int command ; // 指令
    string fileNum ; // file number
    bool openFile ; // 檔案是否成功打開
    char way = 'R' ; // 行走方向
    Mouse mouse ; // 老鼠

    while (true) {
        cout << endl ;
        cout << "*** Path Finding ***\n" ;
        cout << "* 0. Quit          *\n" ;
        cout << "* 1. One goal      *\n" ;
        cout << "* 2. More goals    *\n" ;
        cout << "* 3. Shortest path *\n" ;
        cout << "********************\n" ;
        cout << "Input a command(0, 1, 2): " ;
        cin >> command ; // 輸入指令
        cout << endl ;

        if (command == 0)
            break;

        if ( command != 0 && command != 1 && command != 2 ) {
            cout << "Command does not exist!" << endl ;
            continue;
        }

        cout << "Input a file number: " ;
        cin >> fileNum ; // 輸入檔名

        fileNum = "input" + fileNum + ".txt" ;
        ifstream in(fileNum);

        if (in.fail()) { // 檢查檔案是否成功打開
            cout << "\n" << fileNum << " does not exist!\n" ;
            continue ;
        }

        // 檔案成功打開，讀入、建構迷宮
        Maze step(fileNum);

        if ( command == 1 || command == 3 ) {
            //起點狀態
            mouse.x = 1 ; // x座標
            mouse.y = 1 ; // y座標
            mouse.success = false ; // 是否成功到終點

            mouse = step.findPath( way, mouse.x, mouse.y, 1, command ) ; // 走迷宮

            if ( mouse.success == true ) { // 成功到達G
                step.show1( command ) ; // 印途經路線迷宮
                step.show2( command ) ; // 印成功路線迷宮
            }
            else
                step.show1( command ) ; // 印途經路線迷宮
        } // command : 1

        else if ( command == 2 ) {
            int n = 0 ; // 目標數量
            cout << "\nNumber of G (goals): " ;
            cin >> n ;
            mouse.x = 1 ; // x座標
            mouse.y = 1 ; // y座標
            mouse.success = false ; // 是否成功到終點

            mouse = step.findPath( way, mouse.x, mouse.y, n, command ) ; // 走迷宮

            if ( mouse.success == true ) { // 成功到達指定數量的G
                step.show1( command ) ; // 印途經路線迷宮
                step.show2( command ) ; // 印成功路線迷宮
            }
            else
                step.show1( command ) ; // 印途經路線迷宮
        } // command : 2
    } // while ()
} // main()

