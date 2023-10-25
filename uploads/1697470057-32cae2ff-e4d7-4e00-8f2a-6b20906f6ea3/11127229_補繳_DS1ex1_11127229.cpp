
// 11127229 廖翊崴

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <iostream>
using namespace std ;  // 宣告一個標準系統的命名空間


// 迷宮類別, 存放變數和函數
class Maze {
public:
    int width ;
    int length ;
    char ** chartPtr = NULL ;  // 雙重指標, 為了建二元陣列
    void Set_chart( char info[100] ) ;
    void Access_data( FILE * fptr ) ;
    int Choice_path( int x, int y ) ;
    int record_path[30] ;  // 紀錄經過的方向 ( 1=右 2=下 3=左 4=上 )
    void Initialize_record_path( ) ;
    int record_path_i ;
    char ** copy_chartPtr = NULL ;  // 畫路徑會用到
    void Walk( ) ;
    int Walk_break( int x, int y ) ;
    void Print_chart( char ** ptr ) ;
    void Draw_route( ) ;
    int shortest_path ;
    int have_goal ;
};


// 處理文件內的資料, 提取出來, 結束後開始處理迷宮
void Maze::Access_data( FILE * fptr ) {
    char str[100], info[100] ;
    int str_i = 0, info_i = 0, len = 0 ;
    while ( 1 ) {
        if ( str_i == 0 ) {
            if ( fgets( str, 100, fptr ) == NULL ) break ;  // 讀取文件中的字串, 一次一行
            len = strlen( str ) ;
        }

        if ( str[str_i] != ' ' && str[str_i] != '\0' && str[str_i] != '\n' ) {  // 濾掉不要的東西
            info[info_i] = str[str_i] ;  // 將所有的字元照順序放入陣列內
            info_i++ ;
        }

        str_i++ ;

        if ( str_i == len ) {  // 一行結束
            str_i = 0 ;
        }
    }

    Set_chart( info ) ;
    Walk( ) ;
}


// 將整理好的文件資料放入建好的二元陣列內
void Maze::Set_chart( char info[100] ) {  // 用指標建二元陣列
    chartPtr = ( char ** ) malloc( sizeof( char* ) * length ) ;  // ( 轉型 ) 分配內存( 計算指標的字節 乘上 有幾個 )
    for ( int i = 0 ; i < length ; i++ ) {
        chartPtr[i] = ( char * ) malloc( sizeof( char ) * width ) ;
    }

    copy_chartPtr = ( char ** ) malloc( sizeof( char* ) * length ) ;  // 複製一份迷宮
    for ( int i = 0 ; i < length ; i++ ) {
        copy_chartPtr[i] = ( char * ) malloc( sizeof( char ) * width ) ;
    }

    int info_i = 0 ;
    for ( int i = 0 ; i < length ; i++ ) {  // 放入資料
        for ( int j = 0 ; j < width ; j++ ) {
            chartPtr[i][j] = info[info_i] ;
            copy_chartPtr[i][j] = info[info_i] ;
            info_i++ ;
        }
    }
}


// 開始行走
void Maze::Walk( ) {
    int x = 0, y = 0, goal = 1 ;
    record_path_i = 0 ;
    shortest_path = 1 ;
    have_goal = 0 ;
    while ( goal > 0 ) {
        if ( Choice_path( x, y ) == 1 ) {  // 向右
            if ( record_path[record_path_i] != 0 ) record_path_i++ ;
            record_path[record_path_i] = 1 ;
            if ( chartPtr[x][y] != 'G' ) chartPtr[x][y] = 'V' ;  // 避免誤將G改V
            while ( y + 1 < width && ( chartPtr[x][y+1] == 'E' || chartPtr[x][y+1] == 'G' ) ) {  // 走到底
                y++ ;
                shortest_path++ ;
                if ( chartPtr[x][y] == 'G' ) {
                    goal-- ;
                    have_goal = 1 ;
                    break ;
                }
                else chartPtr[x][y] = 'V' ;
            }
        }
        else if ( Choice_path( x, y ) == 2 ) {  // 向下
            if ( record_path[record_path_i] != 0 ) record_path_i++ ;
            record_path[record_path_i] = 2 ;
            if ( chartPtr[x][y] != 'G' ) chartPtr[x][y] = 'V' ;
            while ( x + 1 < length && ( chartPtr[x+1][y] == 'E' || chartPtr[x+1][y] == 'G' ) ) {
                x++ ;
                shortest_path++ ;
                if ( chartPtr[x][y] == 'G' ) {
                    goal-- ;
                    have_goal = 1 ;
                    break ;
                }
                else chartPtr[x][y] = 'V' ;
            }
        }
        else if ( Choice_path( x, y ) == 3 ) {  // 向左
            record_path_i++ ;
            record_path[record_path_i] = 3 ;
            if ( chartPtr[x][y] != 'G' ) chartPtr[x][y] = 'V' ;
            while ( y - 1 > -1 && ( chartPtr[x][y-1] == 'E' || chartPtr[x][y-1] == 'G' ) ) {
                y-- ;
                shortest_path++ ;
                if ( chartPtr[x][y] == 'G' ) {
                    goal-- ;
                    have_goal = 1 ;
                    break ;
                }
                else chartPtr[x][y] = 'V' ;
            }
        }
        else if ( Choice_path( x, y ) == 4 ) {  // 向上
            record_path_i++ ;
            record_path[record_path_i] = 4 ;
            if ( chartPtr[x][y] != 'G' ) chartPtr[x][y] = 'V' ;
            while ( x - 1 > -1 && ( chartPtr[x-1][y] == 'E' || chartPtr[x-1][y] == 'G' ) ) {
                x-- ;
                shortest_path++ ;
                if ( chartPtr[x][y] == 'G' ) {
                    goal-- ;
                    have_goal = 1 ;
                    break ;
                }
                else chartPtr[x][y] = 'V' ;
            }
        }

        if ( Choice_path( x, y ) == 0 || Walk_break( x, y ) == 0 ) break ;  // 沒有路了
    }

    Print_chart( chartPtr ) ;  // 印出走過的位置圖
    if ( have_goal == 1 ) {  // 判斷是否有經過目標
        Draw_route( ) ;
        Print_chart( copy_chartPtr ) ;  // 印出可行的路徑
        printf( "Shortest path length = %d\n\n", shortest_path ) ;
    }
}


// 選擇路徑
int Maze::Choice_path( int x, int y ) {
    if ( y + 1 < width && record_path[record_path_i] != 3 ) {  // 避免判斷超出迷宮, 並且不能走與最近一次的方向相同
        if ( chartPtr[x][y+1] == 'E' || chartPtr[x][y+1] == 'G' ) return 1 ;  // 右
    }

    if ( x + 1 < length && record_path[record_path_i] != 4 ) {
        if ( chartPtr[x+1][y] == 'E' || chartPtr[x+1][y] == 'G' ) return 2 ;  // 下
    }

    if ( y - 1 > -1 && record_path[record_path_i] != 1 ) {
        if ( chartPtr[x][y-1] == 'E' || chartPtr[x][y-1] == 'G' ) return 3 ;  // 左
    }

    if ( x - 1 > -1 && record_path[record_path_i] != 2 ) {
        if ( chartPtr[x-1][y] == 'E' || chartPtr[x-1][y] == 'G' ) return 4 ;  // 上
    }

    return 0 ;
}


// 初始化, 讓陣列所有元素為零
void Maze::Initialize_record_path( ) {
    for ( int i = 0 ; i < 30 ; i++ ) record_path[i] = 0 ;
}


// 判斷走到底後四方是否還有路
int Maze::Walk_break( int x, int y ) {
    int boo = 0, direction ;
    direction = record_path[record_path_i] ;  // 目前的方向
    if ( Choice_path( x, y ) == 1 ) boo = 1 ;  // 右
    if ( Choice_path( x, y ) == 2 ) boo = 1 ;  // 下
    if ( Choice_path( x, y ) == 3 ) boo = 1 ;  // 左
    if ( Choice_path( x, y ) == 4 ) boo = 1 ;  // 上
    return boo ;  // 1為有路, 0是沒有路
}


// 印出迷宮
void Maze::Print_chart( char ** ptr ) {
    for ( int i = 0 ; i < length ; i++ ) {
        for ( int j = 0 ; j < width ; j++ ) {
            printf( "%c ", ptr[i][j] ) ;
        }

        printf( "\n" ) ;
    }

    printf( "\n" ) ;
}


// 畫出路徑
void Maze::Draw_route( ) {
    int x = 0, y = 0, i = 0, number ;
    number = 1 ;  // 有幾個目標要找
    while ( number > 0 ) {
        if ( record_path[i] == 1 ) {  // 向右
            if ( copy_chartPtr[x][y] != 'G' ) copy_chartPtr[x][y] = 'R' ;
            while ( y + 1 < width && ( copy_chartPtr[x][y+1] == 'E' || copy_chartPtr[x][y+1] == 'G' ) ) {  // 走到底
                y++ ;
                if ( copy_chartPtr[x][y] == 'G' ) {
                    number-- ;
                    if ( number == 0 ) break ;
                }
                else copy_chartPtr[x][y] = 'R' ;
            }
        }
        else if ( record_path[i] == 2 ) {  // 向下
            if ( copy_chartPtr[x][y] != 'G' ) copy_chartPtr[x][y] = 'R' ;
            while ( x + 1 < length && ( copy_chartPtr[x+1][y] == 'E' || copy_chartPtr[x+1][y] == 'G' ) ) {
                x++ ;
                if ( copy_chartPtr[x][y] == 'G' ) {
                    number-- ;
                    if ( number == 0 ) break ;
                }
                else copy_chartPtr[x][y] = 'R' ;
            }
        }
        else if ( record_path[i] == 3 ) {  // 向左
            if ( copy_chartPtr[x][y] != 'G' ) copy_chartPtr[x][y] = 'R' ;
            while ( y - 1 > -1 && ( copy_chartPtr[x][y-1] == 'E' || copy_chartPtr[x][y-1] == 'G' ) ) {
                y-- ;
                if ( copy_chartPtr[x][y] == 'G' ) {
                    number-- ;
                    if ( number == 0 ) break ;
                }
                else copy_chartPtr[x][y] = 'R' ;
            }
        }
        else if ( record_path[i] == 4 ) {  // 向上
            if ( copy_chartPtr[x][y] != 'G' ) copy_chartPtr[x][y] = 'R' ;
            while ( x - 1 > -1 && ( copy_chartPtr[x-1][y] == 'E' || copy_chartPtr[x-1][y] == 'G' ) ) {
                x-- ;
                if ( copy_chartPtr[x][y] == 'G' ) {
                    number-- ;
                    if ( number == 0 ) break ;
                }
                else copy_chartPtr[x][y] = 'R' ;
            }
        }

        if ( i == record_path_i ) break ;  // 表示已經轉完所有方向了
        i++ ;  // 下一個方向
    }
}


// 判斷檔名是否有加上.txt
bool Detect_txt( char name[50] ) {
    int name_l = strlen( name ) ;
    if ( name[name_l - 1] == 't' && name[name_l - 2] == 'x' && name[name_l - 3] == 't' &&
         name[name_l - 4] == '.' ) return true ;
    return false ;
}


// 主程式
int main( void ) {
    while ( true ) {  // 重複執行
        FILE * fptr ;  // 宣告一個文件指標
        char file_name[50] ;
        bool have_txt = false ;
        Maze m ;  // 宣告一個迷宮類別的對象
        int error = 0 ;  // 儲存錯誤資訊

        printf( "\nPlease make sure your executable file, program and test data are in the same folder !\n" ) ;
        printf( "\nEnter your file ( remember add \".txt\" behind file's name ) : " ) ;
        scanf( "%s", file_name ) ;
        printf( "\n" ) ;
        fptr = fopen( file_name, "r" ) ;  // 打開文件, 且設為只能讀取文件內容
        fscanf( fptr, "%d", &m.width ) ;  // 從檔案中讀取格式化數據( 文件指標, 要讀取一個整數, 一個整數變量的位址 )
        fscanf( fptr, "%d", &m.length ) ;

        have_txt = Detect_txt( file_name ) ;  // 判斷是否有加.txt
        if ( have_txt == false ) {
            printf( "Please check your file's name and must have \".txt\" behind it !\n" ) ;
            error = 1 ;
        }
        else if ( fptr == NULL ) {
            printf( "Not find this file !\n" ) ;
            error = 1 ;
        }

        if ( error == 0 ) m.Access_data( fptr ) ;  // 沒有錯誤, 處理資料
        else printf( "\nPlease try again !\n\n" ) ;

        fclose( fptr ) ;  // 關閉文件

        for ( int i = 0 ; i < m.length ; i++ ) {  // 釋放指標
            free( m.chartPtr[i] ) ;
            free( m.copy_chartPtr[i] ) ;
        }

        free( m.chartPtr ) ;
        free( m.copy_chartPtr ) ;
    }

    return 0 ;
}
