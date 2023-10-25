# include <stdio.h>
# include <iostream>
# include <vector>
# include <cstdio>
# include <string>
# include <fstream>
#include <cctype>
#include <cstdlib>

using namespace std;

typedef vector<vector<char>> Place ;


class Data
{

    int x_num = 0;
    int y_num = 0;
    int shortpath = 0 ;
    int current_x = 0 ;
    int current_y = 0 ;
    int current_routine = 1 ;
    int goal = 1 ;
    // int tempnum = 200;

    //宣告兩個vector，可以放置char的vector
    Place root ; // 走過的路
    Place place;  // 走過的地圖結果(保留G)
    Place result; // 成功後的結果
    Place temp ; // 起始地圖

    // 小老鼠 右x+1, 下y+1, 左x-1, 上y-1

    // 方向以1,2,3,4分別為右下左上表示

    // O障礙物,E空格,G目標,V曾經走過的路徑,R可行路徑
    // O不可走,程式上來說V不可走,R只是一個執行結果

    // 判定前方是否可以走


    bool Can_walk( char ch )
    {
        if ( ch == 'E' || ch == 'G')
        {
            return true ;
        }

        return false ;

    } // Can_walk


    // 走路遞迴主程式
    // return 0回去時，會繼續找下一個方向，直到找到路徑或是沒找到路徑而在Run()返回0
    // return 1時就一直return 1, 算是程式計算(找路徑)已經結束
    int Mouse_walk( int routine, int x, int y )
    {


        int find_times = 0 ; // 判定轉向的方向以及，確認是否已經沒路可走，最多轉向三次
        int resultt = -1 ; // return 1是找到路徑, return 0 是沒找到路徑
        int Is_r = 0 ; // 因為resultt會變所以要記錄這個點是R





        while ( find_times != 5 && root[x][y] != 'G') {




            if ( place[x][y] != 'G' ) // 找過的目標可走，但顯示時必須為G
                place[x][y] = 'V' ;

            root[x][y] = 'V' ; // 走路



            if ( routine == 2 ) {

                if ( x+1 < x_num )  {
                    if ( Can_walk( root[x+1][y] ) ) {

                        resultt = Mouse_walk( 2, x+1, y) ; // 確定可走所以return
                        if ( resultt == 1 ) { // 當迴圈返回確認有找到路徑，替換R
                            if ( result[x][y] != 'G' ) // 找過的目標可走，但顯示時必須為G
                                result[x][y] = 'R' ;


                            return 1 ; // 迴圈繼續返回跟上一個說這是找到的路徑
                        } // if()
                        else if ( resultt == 2 ) {
                            if ( result[x][y] != 'G' ) // 找過的目標可走，但顯示時必須為G
                                result[x][y] = 'R' ;

                             Is_r = 2 ;
                        }
                        else {
                            routine = 3 ;
                        }
                    } // if()
                    else {
                        routine = 3 ;
                    }

                }  // if() 預防撞牆所以加條件
                else {
                    routine = 3 ;
                }

            } // if() 往下

            // 剩下的註解同往下
            else if ( routine == 1 ) {

                if ( y+1 < y_num ) {
                    if ( Can_walk( root[x][y+1] ) ) {
                        resultt = Mouse_walk( 1, x, y+1 ) ;
                        if ( resultt == 1 ) {
                            if ( result[x][y] != 'G' )
                                result[x][y] = 'R' ;
                            return 1 ;
                        } // if()
                        else if ( resultt == 2 ) {
                            if ( result[x][y] != 'G' ) {
                                result[x][y] = 'R' ;
                            }// 找過的目標可走，但顯示時必須為G

                             Is_r = 2 ;


                        }
                        else {
                            routine = 2 ;
                        }

                    } // if() 預防撞牆所以加條件
                    else {
                        routine = 2 ;
                    }

                } // if()
                else {
                    routine = 2 ;
                }

            } // else if()往右
            else if (  routine == 4 ) {

                if ( x-1 >= 0 ) {
                    if ( Can_walk( root[x-1][y] ) ) {
                        resultt = Mouse_walk( 4, x-1, y ) ;
                        if ( resultt == 1 ) {
                            if ( result[x][y] != 'G' )
                              result[x][y] = 'R' ;
                            return 1 ;
                        } // if()
                        else if ( resultt == 2 ) {
                            if ( result[x][y] != 'G' ) // 找過的目標可走，但顯示時必須為G
                                result[x][y] = 'R' ;

                                 Is_r = 2 ;

                        }
                        else {
                            routine = 1 ;
                        }

                    } // if()
                    else {
                        routine = 1 ;
                    }


                } // if()預防撞牆
                else {
                    routine = 1 ;
                }

            } // else if()往上，預防撞牆所以加條件
            else if ( routine == 3 ) {
                if( y-1 >= 0 ) {
                    if ( Can_walk( root[x][y-1] ) ) {
                        resultt = Mouse_walk( 3, x, y-1 ) ;
                        if ( resultt == 1  ) {
                            if ( result[x][y] != 'G' )
                              result[x][y] = 'R' ;
                            return 1 ;
                        } // if()
                        else if ( resultt == 2 ) {
                            if ( result[x][y] != 'G' ) // 找過的目標可走，但顯示時必須為G
                                result[x][y] = 'R' ;
                                 Is_r = 2 ;
                        } // else if
                        else {
                            routine = 4 ;
                        } // else
                    } // if()
                    else {
                        routine = 4 ;
                    }

                } // if()預防撞牆
                else {
                    routine = 4 ;
                }

            } // else if()往左，預防撞牆所以加條件

            find_times++ ;

        } // while()

        if ( root[x][y] == 'G' ){ // 找到G


            goal-- ;
            root[x][y] = 'E' ;
            if ( goal == 0 ) {
                return 1 ;
            }
            else {
                return 2 ;
            }
        } // if()
        else if ( find_times == 5 ){ // 轉到走過的路徑的方向，確定沒路了，返回0
            if ( Is_r == 2  ) {
                result[x][y] = 'R' ;
                return 2 ;
            }

            return 0 ;
        } // else()

        return 0 ;

    } // Mouse_Walk()

    // path:最小路徑之值
    // path_num:紀錄這條找到路徑之值
    // path_root:當前這條的路徑圖(不會回傳)
    // path_find:是否找到一路徑

    Place findPath( int routine, int x, int y, int &path, Place path_root, int &path_num, bool &path_find ) {

        int find_times = 0 ; // 判定轉向的方向以及，確認是否已經沒路可走，最多轉向三次
        Place temp_root ; // 記錄回傳回來的地圖



        while ( find_times != 5 && place[x][y] != 'G' ) {




            // 找過的目標可走，但顯示時必須為G
            path_num++ ; // 走路當前path值加一
            if ( place[x][y] != 'G' && path_root[x][y] != 'G') {

                place[x][y] = 'V' ;
                path_root[x][y] = 'R' ; // 當前這條的路徑圖

            } // if


            if ( routine == 2 ) {

                if ( x+1 < x_num )  {
                    if ( Can_walk( path_root[x+1][y] ) ) {
                        if ( path_num < path ){
                            temp_root = findPath( 2, x+1, y, path, path_root, path_num, path_find )  ; // 確定可走
                            path_num-- ; // 遞迴回來減一

                        }
                        else {
                            path_num-- ; // 沒有走
                        }
                        // 回傳來的temp_root是走到底的地圖(無論有沒有找到G)
                        if ( path_num < path && path_find == true ) { // 更新最小路徑
                            result.assign(temp_root.begin(), temp_root.end());
                            path = path_num ; // 更新最小路徑數
                            path_find = false ; // 繼續找下一個G點

                        } //if

                        routine = 3 ;

                    } // if
                    else{
                        routine = 3 ;
                        path_num-- ; // 沒有走
                    } //else
                } // if()
                else {
                    routine = 3 ;
                    path_num-- ; // 沒有走
                }//else

            } // if() 往下

            // 剩下的註解同往下
            else if ( routine == 1 ) {

                if ( y+1 < y_num ) {
                    if ( Can_walk( path_root[x][y+1] ) ) {
                        if ( path_num < path ){
                            temp_root = findPath( 1, x, y+1, path, path_root, path_num, path_find )  ; // 確定可走
                            path_num-- ;

                        }
                        else {
                            path_num-- ;
                        }
                        if ( path_num < path && path_find == true ) {
                            result.assign(temp_root.begin(), temp_root.end());
                            path = path_num ;
                            path_find = false ;


                        } // if

                        routine = 2 ;

                    } // if() 預防撞牆所以加條件
                    else {
                        routine = 2 ;
                        path_num-- ;
                    }//else
                } // if

                 // if()
                else {
                    routine = 2 ;
                    path_num-- ;
                }//else

            } // else if()往右
            else if (  routine == 4 ) {

                if ( x-1 >= 0 ) {
                    if ( Can_walk( path_root[x-1][y] ) ) {
                        if ( path_num < path ){
                            temp_root = findPath( 4, x-1, y, path, path_root, path_num, path_find )  ; // 確定可走
                            path_num-- ;

                        }
                        else{
                            path_num-- ;
                        }
                        if ( path_num < path && path_find == true ) {
                            result.assign(temp_root.begin(), temp_root.end());
                            path = path_num ;
                            path_find = false ;

                        } // if

                        routine = 1 ;
                    }
                    else {
                        routine = 1 ;
                        path_num-- ;
                    }//else

                } // if

                else {
                    routine = 1 ;
                    path_num-- ;
                }//else

            } // else if()往上，預防撞牆所以加條件
            else if ( routine == 3 ) {
                if( y-1 >= 0 ) {
                    if ( Can_walk( path_root[x][y-1] ) ) {
                        if ( path_num < path ){
                            temp_root = findPath( 3, x, y-1, path, path_root, path_num, path_find )  ; // 確定可走
                            path_num-- ;

                        }
                        else{
                            path_num-- ;
                        }
                        if ( path_num < path && path_find == true ) {
                            result.assign(temp_root.begin(), temp_root.end());
                            path = path_num ;
                            path_find = false ;

                        } // if

                        routine = 4 ;
                    } // if
                    else {
                        routine = 4 ;
                        path_num-- ;
                    }//else


                } // if()預防撞牆
                else {
                    routine = 4 ;
                    path_num-- ;
                }//else

            } // else if()往左，預防撞牆所以加條件

            find_times++ ;

        } // while()

        if ( place[x][y] == 'G' ){
            path_find = true ; // 找到G點
            return path_root ;
        } // if()
        else {
            path_find = false ; // 沒找到G
            return path_root ;
        }


}



public:

    void Set_num ( int x, int y )   // 設定axa
    {
        x_num = x ;
        y_num = y ;
        place.resize(x) ;
        result.resize(x) ;
        root.resize(x) ;
        temp .resize(x) ;
    } // Set_num()



    void Set_place( vector<vector<char>> a )   // 設定地圖
    {

        char tempp ;
        for( int i = 0 ; i < x_num ; i++ )
        {
            for( int j = 0 ; j < y_num ; j++ )
            {
                tempp = a[i][j];
                place[i].push_back(tempp) ;
                result[i].push_back(tempp) ;
                root[i].push_back(tempp) ;
                temp[i].push_back(tempp) ;
            } // for()
        } // for()
        cout << endl ;

    }  // Set_place()
    void Set_goal( int a )   // 設定地圖
    {
        if ( a == 2 ) {
            cout << "enter N:" ;
            cin >> goal ;
        } // if()
        else {
            goal = -1 ;
        }

    }  // Set_place()

    void Print_place()
    {
        for( int i = 0 ; i < x_num ; i++ )
        {
            for( int j = 0 ; j < y_num ; j++ )
            {
                cout << place[i][j] ;
            } // for()
            cout << "\n" ;
        } // for()
        cout << endl ;

    } // Print_place()

    void Print_result()
    {

        for( int i = 0 ; i < x_num ; i++ )
        {
            for( int j = 0 ; j < y_num ; j++ )
            {
                cout << result[i][j] ;
            } // for()
            cout << "\n" ;
        } // for()

    } // Print_result()
    void Print_root() {

        for( int i = 0 ; i < x_num ; i++ )
        {
            for( int j = 0 ; j < y_num ; j++ )
            {
                cout << root[i][j] ;
            } // for()
            cout << "\n" ;
        } // for()
        cout << endl ;


    } // Print_root()()

    void Run( int command )
    {
        int path = 10000 ;
        int path_num = 0 ;
        int findpath = 0 ;
        bool tempp = false ;

        // 起點不是障礙物，EXCEPTION
        if ( place[0][0] != 'O' )
        {
            if (  command != 3 )
                Mouse_walk( 1, 0, 0 ) ;
            else{
                findPath( 1, 0, 0, path, temp, path_num, tempp ) ;
            }


        } // if

        if ( goal == 0 ) // N個都找到了
        {
               Print_place() ;
               Print_result() ;
        }
        else if ( goal = -1 ) { // command == 3

            if ( path !=  10000){
               Print_place() ;
               Print_result() ;
               path = path + 2 ; // 頭尾沒計算到
               cout << "Short path:" << path << endl ;

            } // if()
            else{
                Print_place() ;
                cout << "Didn't find path" << endl ;
            }
        }
        else // 沒找到N個
        {
               Print_place() ;
        }
    } // Run()


}; // data

int ModelInput() ;
bool DataInput() ;
string change( string num, int &i ) ;
bool checkChar( char line ) ;
void findNum( string line, int &x, int &y ) ;

int main()
{
    int command = -1;
    vector<vector<char>> place;
    string fileName = "input101.txt";
    string num;
    string line;
    ifstream in ;
    vector<vector<char>> a ;
    int x = 0  ;
    int y = 0  ;
    do
    {
        Data Mouse;
        command = ModelInput();
        bool haveFile = true ;

        if (command != 0) {
            cout << "Input file number: ";
            cin >> num;
            fileName = "input" + num + ".txt";
            ifstream in(fileName);

            if (in.fail()) {
                cout << fileName << " doesn't exist " << endl;
                haveFile  = false ;
            }
            else {
                getline(in, line) ;
                findNum( line, x, y ) ;
                place.clear(); // 清空向量
                place.resize(x);
                getline(in, line) ;

                for (int i = 0; i < x; i++) {
                    for (int j = 0; j < y; j++) {
                        if ( checkChar( line[j] ) ){
                            place[i].push_back(line[j]) ;
                        }
                        else {
                            j-- ;
                        }
                    }
                    getline(in, line) ;
                }

            }

            in.close(); // 關閉文件


        }


        if ( command == 1 && haveFile )
        {
            Mouse.Set_num ( x, y ) ;
            Mouse.Set_place( place ) ;
            Mouse.Run( command ) ;
        } // if()
        else if ( command == 2 && haveFile  )
        {
            Mouse.Set_goal( command ) ;
            Mouse.Set_num ( x, y ) ;
            Mouse.Set_place( place ) ;
            Mouse.Run( command ) ;
        } // else if()
        else if ( command == 3 && haveFile ) {
            Mouse.Set_goal( command ) ;
            Mouse.Set_num ( x, y ) ;
            Mouse.Set_place( place ) ;
            Mouse.Run( command ) ;
        }
    }
    while( command != 0 );

    cout << "---------------system end----------------" ;
} // main()
void findNum( string line, int &x, int &y ) {


    int num = 0 ;
    int place = 0 ;

    string snum ;

    for ( int i = 0 ; i < line.length() ; i++ ) {
        if ( num == 0 ) {
            y = stoi( change( line, place ) ) ;
            num++ ;
        }
        else {
            x = stoi( change( line, place ) ) ;
            i = line.length() ;
        }

    }
}

bool checkChar( char line ){

    if ( line != ' ' || line != '\n' ){
        return true ;
    }
    else {
        return false ;
    }

    return false ;

}




string change( string num, int &i ) {

    string endd = "" ;

  while( num[i] == '1' || num[i] == '2' || num[i] == '3' || num[i] == '4' || num[i] == '5' || num[i] == '6' || num[i] == '7' || num[i] == '8' || num[i] == '9' || num[i] == '0' ) {
    endd = endd + num[i] ;
    i++ ;
  }


  i++ ;
  return endd ;

}

int ModelInput()
{
    int command = 5 ;
    cout << endl << "*** Path Finding ***" ;
    cout << endl << "*0. Quit           *" ;
    cout << endl << "*1. One goal       *" ;
    cout << endl << "*2. More goals     *" ;
    cout << endl << "********************" ;
    cout << endl << "Input a command(0, 1, 2, 3): " ;
    cin >> command ;
    while ( command > 3 || command < 0  )
    {
        cout << "Wrong input! Please try again:" ;
        cin >> command ;
    }
    return command ;
} // ModelInput()

