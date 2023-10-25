// 11127239 陳映銓

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream> // 匯入資料

using namespace std ;

class Maze {
public:
    int x_lin = 0 ;          // 陣列長
    int y_lin = 0 ;          // 陣列寬
    char map[50][50] ;       // 原地圖

    int work_x = 0 ;         // 行徑中的x
    int work_y = 0 ;         // 行徑中的y
    char map_cpy[50][50] ;   // V地圖(複製原地圖)
    char map_Rcpy[50][50] ;  // R地圖(複製原地圖)

    int g_times = 0 ;        // 有幾個G
    int loop = 0 ;           // 計算四個方向接走過了

    bool yn_g = false ;      // 是否有走到G

    bool load(int fileName_number,int mode);  // 是否有此檔案及讀檔進x_lin、y_lin、map[][]

    void work();   // 一開始起步時行走方向, (0, 0)在左上方
    void right();  // 往右走(x+1)
    void down();   // 往下走(y+1)
    void left();   // 往左走(x-1)
    void up();     // 往上走(y-1)

    void show() ;  // 印出 V & R 地圖

};



bool Maze :: load( int fileName_number, int mode ){

    // 設定g有幾個
    g_times = mode ;

    // 匯入資料

    char txt_name[15] ;  // 為了合併名稱

    sprintf( txt_name, "input%d.txt", fileName_number ) ;

    ifstream inputfile(txt_name);

    inputfile >> x_lin ;
    inputfile >> y_lin ;

    for ( int i = 0 ; i < y_lin ; i ++ ){
        for ( int j = 0 ; j < x_lin ; j ++ ){
            inputfile >> map[j][i];
        }
    }

    // 複製兩份迷宮( V, R )
    for (int r = 0; r < y_lin; r++) {
        for (int c = 0; c < x_lin; c++) {
            map_cpy[c][r] = map[c][r] ;
            map_Rcpy[c][r] = map[c][r] ;
        }
    }

    return true ;

} // load()


void Maze :: work(){
// 一開始出發要走右邊or下面(左邊及上面沒路)

    /*一開始右邊有路時*/
    if( (map_cpy[work_x + 1][work_y] == 'E' ||
        map_cpy[work_x + 1][work_y] == 'G') &&
        (work_x + 1) < x_lin ){ // 往右 && 不能大於邊界

        Maze :: right() ;

    } // if

    /*一開始右邊沒路時*/
    else if( (map_cpy[work_x][work_y + 1] == 'E' ||
             map_cpy[work_x][work_y + 1] == 'G') &&
             (work_y + 1) < y_lin ){ // 往下 && 不能大於邊界

        Maze :: down() ;

    } // else if

} // work()

void Maze :: right(){ 
// 如果右邊一直有路，就一直往前走

    int worked_x = -1 ; // 遇到交叉口記住此位置
    int worked_y = -1 ; // 遇到交叉口記住此位置
    int x = 0 ;  // 原路返回把R改回E使用
    int y = 0 ;  // 原路返回把R改回E使用

    int rdlu[4] = {-1, -1 , -1, -1} ; // 1:右, 2:下, 3:左, 4:上
    
    if( (work_x + 1) < x_lin && 
        (map_cpy[work_x + 1][work_y] == 'E' || map_cpy[work_x + 1][work_y] == 'G') 
        ){  // 往右 && 不能大於邊界

        x = work_x ;
        y = work_y ;
        loop = 0 ;
    
        // 修改地圖
        if ( map_cpy[work_x][work_y] != 'G' && map_cpy[work_x][work_y] != 'Q' ) {
            map_cpy[work_x][work_y] = 'V' ;
            map_Rcpy[work_x][work_y] = 'R' ;
        } // if

        // 檢測剩下幾個目標G
        if ( map_cpy[work_x + 1][work_y] == 'G' || map_cpy[work_x + 1][work_y] == 'Q' ) {
            yn_g = true ;
            map_cpy[work_x + 1][work_y] = 'Q';
            g_times -- ;
        }

        // 如果目標剩0個時，結束
        if ( g_times <= 0 ) return ;

        /*檢測其他兩個方位是否有路*/
        if ( (work_y + 1) < y_lin &&
            ( map_cpy[work_x][work_y + 1] == 'E' || map_cpy[work_x][work_y + 1] == 'G') 
            ) { // 下
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i] == -1 ) {
                    rdlu[i] = 2 ;
                    break;
                }  // if
            } // for
        } // if

        if ( (work_y - 1) >= 0 && 
                ( map_cpy[work_x][work_y - 1]  == 'E' || map_cpy[work_x][work_y - 1]  == 'G')
            ) { // 上
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i] = 4 ;
                    break;
                }  // if
            } // for
        } // if

        // 前進
        work_x = work_x + 1 ; 

        /*目的 : G 後面有路 g_times = false */
        if ( map_cpy[work_x][work_y] == 'G' || map_cpy[work_x][work_y] == 'Q' ) {
            if ( (work_x + 1) < x_lin && 
                (map_cpy[work_x + 1][work_y] == 'E' || map_cpy[work_x + 1][work_y] == 'G') ) 
                // 右
                yn_g = false ;
            if ( (work_y + 1) < y_lin && 
                (map_cpy[work_x][work_y + 1] == 'E' || map_cpy[work_x][work_y + 1] == 'G') )
                // 下
                yn_g = false ;
            if ( (work_y - 1) >= 0 && 
                (map_cpy[work_x][work_y - 1] == 'E' || map_cpy[work_x][work_y - 1] == 'G') )
                // 上
                yn_g = false ;
        } // if


        Maze :: right() ;
        if (g_times <= 0) return ;

        /*走到死路後開始往回走*/

        if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[x][y] = 'E' ;
        
        if ( worked_x != -1 && worked_y != -1 ){
            yn_g = false ;
            work_x = worked_x ;
            work_y = worked_y ;
            for ( int i = 0 ; i < 4 ; i ++ ) {
                if ( rdlu[i] == -1 ) break;
                if ( rdlu[i] == 2 ) Maze :: down() ;
                if ( rdlu[i] == 4 ) Maze :: up() ;
                if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[work_x][work_y] = 'E' ;
                return ;
            } // for

        } // if

    } // if

    /*碰壁*/
    else {

        x = work_x ;
        y = work_y ;
        // 踩過死路(V)
        if ( map_cpy[work_x][work_y] == 'E' ) {
            yn_g = false ;
            map_cpy[work_x][work_y] = 'V' ;
        } // if

        /*(走到邊界)檢測其他兩個方位是否有路*/
        if ( (work_y + 1) < y_lin &&
             ( map_cpy[work_x][work_y + 1] == 'E' || map_cpy[work_x][work_y + 1] == 'G') 
            ) { // 下
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i] == -1 ) {
                    rdlu[i] = 2 ;
                    break;
                }  // if
            } // for
        } // if
        if ( (work_y - 1) >= 0 && 
             ( map_cpy[work_x][work_y - 1]  == 'E' || map_cpy[work_x][work_y - 1]  == 'G')
            ) { // 上
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i] = 4 ;
                    break;
                }  // if
            } // for
        } // if

        loop++ ;

        if( loop == 4 ) {
            loop = 0 ;
            return ;
        } // if
        
        Maze :: down() ;

        /*走到死路後開始往回走*/
        
        if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[x][y] = 'E' ;

        if ( worked_x != -1 && worked_y != -1 ){
            work_x = worked_x ;
            work_y = worked_y ;
            for ( int i = 0 ; i < 4 ; i ++ ) {
                if ( rdlu[i] == -1 ) break;
                if ( rdlu[i] == 2 ) Maze :: down() ;
                if ( rdlu[i] == 4 ) Maze :: up() ;
                if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[work_x][work_y] = 'E' ;
                return ;
            } // for

        } // if
        
    } // else


} // right()

void Maze :: down() { // 如果下面一直有路，就一直往前走

    int worked_x = -1 ; // 遇到交叉口記住此位置
    int worked_y = -1 ; // 遇到交叉口記住此位置
    int x = 0 ;  // 原路返回把R改回E使用
    int y = 0 ;  // 原路返回把R改回E使用

    int rdlu[4] = {-1, -1 , -1, -1} ; // 1:右, 2:下, 3:左, 4:上

    if( (map_cpy[work_x][work_y + 1] == 'E' ||
        map_cpy[work_x][work_y + 1] == 'G') &&
        (work_y + 1) < y_lin ){  // 往下 && 不能大於邊界


        x = work_x ;
        y = work_y ;
        loop = 0 ;
    
        // 修改地圖
        if ( map_cpy[work_x][work_y] != 'G' && map_cpy[work_x][work_y] != 'Q' ) {
            map_cpy[work_x][work_y] = 'V' ;
            map_Rcpy[work_x][work_y] = 'R' ;
        } // if

        // 檢測剩下幾個目標G
        if ( map_cpy[work_x][work_y + 1] == 'G' || map_cpy[work_x][work_y + 1] == 'Q' ) {
            yn_g = true ;
            map_cpy[work_x][work_y + 1] = 'Q';
            g_times -- ;
        }

        // 如果目標剩0個時，結束
        if ( g_times <= 0 ) return ;

        /*檢測其他兩個方位是否有路*/
        if ( ( map_cpy[work_x - 1][work_y]  == 'E' ||
             map_cpy[work_x - 1][work_y]  == 'G' ) &&
             (work_x - 1) >= 0 ) { // 左
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i]=3 ;
                    break;
                } // if
            } // for
        } // if
        if ( ( map_cpy[work_x + 1][work_y] == 'E' ||
             map_cpy[work_x + 1][work_y] == 'G' ) &&
             (work_x + 1) < x_lin ) { // 右
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i]=1 ;
                    break;
                } // if
            } // for
        } // if

        // 前進
        work_y = work_y + 1 ; 

        /*目的 : G 後面有路 g_times = false */
        if ( map_cpy[work_x][work_y] == 'G' || map_cpy[work_x][work_y] == 'Q' ) {

            if ( (work_y + 1) < y_lin && 
                (map_cpy[work_x][work_y + 1] == 'E' || map_cpy[work_x][work_y + 1] == 'G') )
                // 下
                yn_g = false ;
            if ( (work_x - 1) >= 0 && 
                (map_cpy[work_x - 1][work_y] == 'E' || map_cpy[work_x - 1][work_y] == 'G') )
                // 左
                yn_g = false ;
            if ( (work_x + 1) < x_lin && 
                (map_cpy[work_x + 1][work_y] == 'E' || map_cpy[work_x + 1][work_y] == 'G') )
                // 右
                yn_g = false ;
        } // if

        Maze :: down() ;
        if (g_times <= 0) return ;

        /*走到死路後開始往回走*/

        if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[x][y] = 'E' ;
        
        if ( worked_x != -1 && worked_y != -1 ){
            yn_g = false ;
            work_x = worked_x ;
            work_y = worked_y ;
            for ( int i = 0 ; i < 4 ; i ++ ) {
                if ( rdlu[i] == -1 ) break;
                if ( rdlu[i] == 3 ) Maze :: left() ;
                if ( rdlu[i] == 1 ) Maze :: right() ;
                if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[work_x][work_y] = 'E' ;
                return ;
            } // for

        } // if

    } // if

    /*碰壁*/
    else {

        x = work_x ;
        y = work_y ;
        // 踩過死路(V)
        if ( map_cpy[work_x][work_y] == 'E' ){
            yn_g = false ;
            map_cpy[work_x][work_y] = 'V' ;
        } // if

        /*(走到邊界)檢測其他兩個方位是否有路*/
        if ( ( map_cpy[work_x - 1][work_y]  == 'E' ||
             map_cpy[work_x - 1][work_y]  == 'G' ) &&
             (work_x - 1) >= 0 ) { // 左
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i]=3 ;
                    break;
                } // if
            } // for
        } // if

        if ( ( map_cpy[work_x + 1][work_y] == 'E' ||
             map_cpy[work_x + 1][work_y] == 'G' ) &&
             (work_x + 1) < x_lin ) { // 右
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i]=1 ;
                    break;
                } // if
            } // for
        } // if

        loop++ ;

        if( loop == 4 ) {
            loop = 0 ;
            return ;
        } // if

        
        Maze :: left() ;


        /*走到死路後開始往回走*/
        
        if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[x][y] = 'E' ;

        if ( worked_x != -1 && worked_y != -1 ){
            work_x = worked_x ;
            work_y = worked_y ;
            for ( int i = 0 ; i < 4 ; i ++ ) {
                if ( rdlu[i] == -1 ) break;
                if ( rdlu[i] == 3 ) Maze :: left() ;
                if ( rdlu[i] == 1 ) Maze :: right() ;
                if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[work_x][work_y] = 'E' ;
                return ;
            } // for

        } // if

    } // else

} // down()

void Maze :: left() { // 如果左邊一直有路，就一直往前走

    int worked_x = -1 ; // 遇到交叉口記住此位置
    int worked_y = -1 ; // 遇到交叉口記住此位置
    int x = 0 ;  // 原路返回把R改回E使用
    int y = 0 ;  // 原路返回把R改回E使用

    int rdlu[4] = {-1, -1 , -1, -1} ; // 1:右, 2:下, 3:左, 4:上

    if( ( map_cpy[work_x - 1][work_y] == 'E' ||
          map_cpy[work_x - 1][work_y] == 'G' )  &&
          (work_x - 1) >= 0 ){ // 往左 && 不能小於邊界

        x = work_x ;
        y = work_y ;
        loop = 0 ;
        // 修改地圖
        if ( map_cpy[work_x][work_y] != 'G' && map_cpy[work_x][work_y] != 'Q' ) {
            map_cpy[work_x][work_y] = 'V' ;
            map_Rcpy[work_x][work_y] = 'R' ;
        } // if

        // 檢測剩下幾個目標G
        if ( map_cpy[work_x - 1][work_y] == 'G' || map_cpy[work_x - 1][work_y] == 'Q' ) {
            yn_g = true ;
            map_cpy[work_x - 1][work_y] = 'Q';
            g_times -- ;
        }
        // 如果目標剩0個時，結束

        if ( g_times <= 0 ) return ;

        /*檢測其他兩個方位是否有路*/
        if ( ( map_cpy[work_x][work_y - 1]  == 'E' ||
            map_cpy[work_x][work_y - 1]  == 'G' ) &&
            (work_y - 1) >= 0 ) { // 上
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i]=4 ;
                    break;
                } // if
            } // for
        } // if

        if ( ( map_cpy[work_x][work_y + 1] == 'E' ||
            map_cpy[work_x][work_y + 1] == 'G' ) &&
            (work_y + 1) < y_lin ) { // 下
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i]=2 ;
                    break;
                } // if
            } // for
        } // if

        // 前進
        work_x = work_x - 1 ; 

        /*目的 : G 後面有路 g_times = false */
        if ( map_cpy[work_x][work_y] == 'G' || map_cpy[work_x][work_y] == 'Q' ) {

            if ( (work_x - 1) >= 0 && 
                (map_cpy[work_x - 1][work_y] == 'E' || map_cpy[work_x - 1][work_y] == 'G') )
                // 左
                yn_g = false ;
            if ( (work_y - 1) >= 0 && 
                (map_cpy[work_x][work_y - 1] == 'E' || map_cpy[work_x][work_y - 1] == 'G') )
                // 上
                yn_g = false ;
            if ( (work_y + 1) < y_lin && 
                (map_cpy[work_x][work_y + 1] == 'E' || map_cpy[work_x][work_y + 1] == 'G') )
                // 下
                yn_g = false ;
        } // if

        Maze :: left() ;
        if (g_times <= 0) return ;

        /*走到死路後開始往回走*/

        if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[x][y] = 'E' ;

        if ( worked_x != -1 && worked_y != -1 ){
            yn_g = false ;
            work_x = worked_x ;
            work_y = worked_y ;
            for ( int i = 0 ; i < 4 ; i ++ ) {
                if ( rdlu[i] == -1 ) break;
                if ( rdlu[i] == 4 ) Maze :: up() ;
                if ( rdlu[i] == 2 ) Maze :: down() ;
                if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[work_x][work_y] = 'E' ;
                return ;
            } // for

        } // if
    } // if

    /*碰壁*/
    else {

        x = work_x ;
        y = work_y ;
        // 踩過死路(V)
        if ( map_cpy[work_x][work_y] == 'E' ){
            yn_g = false ;
            map_cpy[work_x][work_y] = 'V' ;
        } // if

        /*(走到邊界)檢測其他兩個方位是否有路*/
        if ( ( map_cpy[work_x][work_y - 1]  == 'E' ||
            map_cpy[work_x][work_y - 1]  == 'G' ) &&
            (work_y - 1) >= 0 ) { // 上
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i]=4 ;
                    break;
                } // if
            } // for
        } // if

        if ( ( map_cpy[work_x][work_y + 1] == 'E' ||
            map_cpy[work_x][work_y + 1] == 'G' ) &&
            (work_y + 1) < y_lin ) { // 下
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i]=2 ;
                    break;
                } // if
            } // for
        } // if

        loop++ ;
        if( loop == 4 ) {
            loop = 0 ;
            return ;
        } // if

        Maze :: up() ;

        /*走到死路後開始往回走*/

        if ( worked_x != -1 && worked_y != -1 ){
            work_x = worked_x ;
            work_y = worked_y ;
            for ( int i = 0 ; i < 4 ; i ++ ) {
                if ( rdlu[i] == -1 ) break;
                if ( rdlu[i] == 4 ) Maze :: up() ;
                if ( rdlu[i] == 2 ) Maze :: down() ;
                if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[work_x][work_y] = 'E' ;
                return ;
            } // for

        } // if
        
    }  // else

} // left()

void Maze :: up() { // 如果上面一直有路，就一直往前走

    int worked_x = -1 ; // 遇到交叉口記住此位置
    int worked_y = -1 ; // 遇到交叉口記住此位置
    int x = 0 ;  // 原路返回把R改回E使用
    int y = 0 ;  // 原路返回把R改回E使用

    int rdlu[4] = {-1, -1 , -1, -1} ; // 1:右, 2:下, 3:左, 4:上

    if( (map_cpy[work_x][work_y - 1 ] == 'E' ||
        map_cpy[work_x][work_y - 1 ] == 'G' ) &&
        (work_y - 1) >= 0){ //往上 && 不能小於邊界

        x = work_x ;
        y = work_y ;
        loop = 0 ;

        // 修改地圖
        if ( map_cpy[work_x][work_y] != 'G' && map_cpy[work_x][work_y] != 'Q' ) {
            map_cpy[work_x][work_y] = 'V' ;
            map_Rcpy[work_x][work_y] = 'R' ;
        } // if

        // 檢測剩下幾個目標G
        if ( map_cpy[work_x][work_y - 1 ] == 'G' || map_cpy[work_x][work_y - 1 ] == 'Q' ){
            yn_g = true ;
            map_cpy[work_x][work_y - 1] = 'Q';
            g_times -- ;
        }

        // 如果目標剩0個時，結束
        if ( g_times <= 0 ) return ;

        /*檢測其他兩個方位是否有路*/
        if ( ( map_cpy[work_x + 1 ][work_y] == 'E' ||
            map_cpy[work_x + 1 ][work_y] == 'G' ) &&
            (work_x + 1) < x_lin ) { // 右
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i]=1 ;
                    break;
                } // if
            } // for
        } // if

        if ( ( map_cpy[work_x - 1][work_y]  == 'E' ||
            map_cpy[work_x - 1][work_y]  == 'G' ) &&
            (work_x - 1) >= 0 ) { // 左
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i]=3 ;
                    break;
                } // if
            } // for
        } // if
    
        // 前進
        work_y = work_y - 1 ; 

        /*目的 : G 後面有路 g_times = false */
        if ( map_cpy[work_x][work_y] == 'G' || map_cpy[work_x][work_y] == 'Q' ) {

            if ( (work_y - 1) >= 0 && 
                (map_cpy[work_x][work_y - 1] == 'E' || map_cpy[work_x][work_y - 1] == 'G') )
                // 上
                yn_g = false ;
            if ( (work_x + 1) < x_lin && 
                (map_cpy[work_x + 1][work_y] == 'E' || map_cpy[work_x + 1][work_y] == 'G') )
                // 右
                yn_g = false ;
            if ( (work_x - 1) >= 0 && 
                (map_cpy[work_x - 1][work_y] == 'E' || map_cpy[work_x - 1][work_y] == 'G') )
                // 左
                yn_g = false ;

        } // if

        Maze :: up() ;
        if (g_times <= 0) return ;

        /*走到死路後開始往回走*/

        if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[x][y] = 'E' ; 

        if ( worked_x != -1 && worked_y != -1 ){
            yn_g = false ;
            work_x = worked_x ;
            work_y = worked_y ;
            for ( int i = 0 ; i < 5 ; i ++ ) {
                if ( rdlu[i] == -1 ) break;
                if ( rdlu[i] == 1 ) Maze :: right() ;
                if ( rdlu[i] == 3 ) Maze :: left() ;
                if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[work_x][work_y] = 'E' ;
                return ;
            } // for

        } // if

    } // if

    /*碰壁*/
    else {

        x = work_x ;
        y = work_y ;
        // 踩過死路(V)
        if ( map_cpy[work_x][work_y] == 'E' ) {
            yn_g = false ;
            map_cpy[work_x][work_y] = 'V' ;

        } // if

        /*(走到邊界)檢測其他兩個方位是否有路*/
        if ( ( map_cpy[work_x + 1 ][work_y] == 'E' ||
            map_cpy[work_x + 1 ][work_y] == 'G' ) &&
            (work_x + 1) < x_lin ) { // 右
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i]=1 ;
                    break;
                } // if
            } // for
        } // if
        if ( ( map_cpy[work_x - 1][work_y]  == 'E' ||
            map_cpy[work_x - 1][work_y]  == 'G' ) &&
            (work_x - 1) >= 0 ) { // 左
            worked_x = work_x ;
            worked_y = work_y ;
            for ( int i = 0 ; i < 4 ; i++ ) {
                if ( rdlu[i]== -1 ) {
                    rdlu[i]=3 ;
                    break;
                } // if
            } // for
        } // if

        loop++ ;
        if( loop == 4 ) {
            loop = 0 ;
            return ;
        } // if
        
        Maze :: right() ;

        /*走到死路後開始往回走*/

        if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[x][y] = 'E' ;

        if ( worked_x != -1 && worked_y != -1 ){
            work_x = worked_x ;
            work_y = worked_y ;
            for ( int i = 0 ; i < 5 ; i ++ ) {
                if ( rdlu[i] == -1 ) break;
                if ( rdlu[i] == 1 ) Maze :: right() ;
                if ( rdlu[i] == 3 ) Maze :: left() ;
                if ( yn_g != true && map_Rcpy[x][y] != 'G' ) map_Rcpy[work_x][work_y] = 'E' ;
                return ;
            } // for

        } // if

    } // else

} // up()

void Maze :: show() {

    // 防止G被吃掉的壯況
    for (int r = 0; r < y_lin; r++) {
        for (int c = 0; c < x_lin; c++) {
            if (map[c][r] == 'G') {
                // cout << "eat\n" ;
                map_cpy[c][r] = 'G' ;
                map_Rcpy[c][r] = 'G' ;
            } // if
        } // for
    } // for

    /*最終R的處理*/
    int R_times = 0 ;
    for (int r = 0; r < y_lin; r++) {
        for (int c = 0; c < x_lin; c++) {
            if (map_Rcpy[c][r] == 'R') R_times ++ ;
        } // for
    } // for

    /*最終V*/
    for (int r = 0; r < y_lin; r++) {
        for (int c = 0; c < x_lin; c++) {
            if ( map_cpy[c][r] == 'Q' ) cout << 'G' << " ";
            else cout << map_cpy[c][r] ;
        } // for
        cout<<"\n";
    } // for

    cout << endl ;

    /*最終R*/
    if (R_times != 0 && g_times <= 0) {
        map_Rcpy[0][0] = 'R' ;
        for (int r = 0; r < y_lin; r++) {
            for (int c = 0; c < x_lin; c++) {
                cout << map_Rcpy[c][r] ;
            } // for
            cout<<"\n";
        } // for
    } // if
    

} // show()

int main(){

    int command = 0 ; // 詢問( 0, 1, 2 )

    do {
        Maze aMaze ;
        int fileName_number = 0 ; // 檔名中的編號(ex. 101, 102)
        int mode = 0 ; // 單目標 or 多目標

        cout << endl << "*** Path Finding ***" ;
        cout << endl << "* 0. Quit          *" ;
        cout << endl << "* 1. One goal      *" ;
        cout << endl << "* 2. More goals    *" ;
        cout << endl << "********************" ;
        cout << endl << "Input a command(0, 1, 2):" ;
        cin >> command; // 最後目標 g 是單個 or 多個 ( == 0 時跳離 )
        mode = command ;

        if( (command == 1) || (command == 2) ){

            cout << endl << "Input a file number:" ;
            cin >> fileName_number;

            if (command == 2) {
                cout << endl << "Number of G (goals):" ;
                cin >> mode ;
            } // if

            if( aMaze.load( fileName_number, mode ) ){
                aMaze.work();
                aMaze.show();
            } // if
        } // if

        else if ( command == 0 ) break ;

        else cout << endl << "Command does not exist" << endl ;
    } // do
    
    while (true);

    system("pause");
    return 0 ;


} //main()
