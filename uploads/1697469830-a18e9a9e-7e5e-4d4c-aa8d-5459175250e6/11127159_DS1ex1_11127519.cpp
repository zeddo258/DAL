//11127159 廖為宥
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>


using namespace std;



typedef vector<string> vecString;

void printStart() ;                 //印出開始時的話

int makeCommand( char ch ) ;                    //輸入執行的任務

void checkFile( string &filename, string str1, bool &theresFile ) ;                 //輸入檔名，並確認是否有這個檔案

void readFile( vecString &stringOfLine, string filename ) ;                     //輸入檔案，並存於vector中

bool missionOne( vecString &strMap, int row, int column )  ;                    //任務一

bool solveMissionOne( vecString &strMap, int x, int y, int direction ) ;                    //執行任務一的尋找路徑

bool isMove( vecString strMap, int x, int y ) ;                         //測試下一步是否可行

void printMap( vecString strMap ) ;                         //印出二維迷宮

void printMapForR( vecString strMap ) ;                          //印出二維迷宮R的路徑

int checkGoalNum( string str1 ) ;                       //輸入要找到的G的數量

bool missionTwo( vecString &strMap, int gnum ) ;                                //任務二

bool solveMissionTwo( vecString &strMap, int x, int y, int direction ) ;                    //執行任務二的尋找路徑







const int moveX[] = {1, 0, -1, 0} ;                 //依座標 向右走(1,0),  向下走(0,1)
const int moveY[] = {0, 1, 0, -1} ;                 //       向左走(-1,0), 向上走(0,-1)

int length = 0;             //迷宮的長
int height = 0;             //迷宮的高

int preX = 0;               //前一步的x座標
int preY = 0;               //前一步的y座標





int main() {
    bool theresFile = false;
    char ch = '\0';
    string str1;
    string filename;
    vecString stringOfLine;
    int x = 0, y = 0;
    int gnum = 0;

    printStart();                    //印出開始時的話

    int command = makeCommand( ch ) ;               //輸入執行任務的代號

    while ( command != 0 ) {
        checkFile( filename, str1, theresFile ) ;           //確認檔案是否存在


        if ( theresFile ) {
            readFile( stringOfLine, filename ) ;            //輸入檔案中的地圖

            if ( command == 1 ) {                      //任務一
                x = y = 0;
                if ( missionOne( stringOfLine, x, y ) ) {           //執行任務一
                    printMap( stringOfLine ) ;    //找到終點並印出
                    cout << endl;
                    printMapForR( stringOfLine ) ;
                } // if
                else {
                    printMap( stringOfLine ) ;                  //沒找到終點

                } // else

            } // if


            else if ( command == 2 ) {                  //任務二
                gnum = checkGoalNum( str1 ) ;                   //確認要求的終點數量
                if ( missionTwo( stringOfLine, gnum ) ) {
                    printMap( stringOfLine ) ;               //找到終點並印出
                    cout << endl;
                    printMapForR( stringOfLine ) ;
                } // if
                else {
                    printMap( stringOfLine ) ;              //沒找到終點
                } // else

            } // else if

        } // if


        cout << endl;
        ch = '\0' ;
        command = -1;
        length = 0;
        height = 0;

        printStart() ;                      //從頭再一次
        command  = makeCommand( ch ) ;
    } // while

    cout << "請按任意鍵繼續 . . . " ;      //若輸入是零



} // main()















void printStart() {
    cout << "*** Path Finding ***" << endl  ;
    cout << "* 0. Quit          *" << endl  ;
    cout << "* 1. One goal      *" << endl  ;
    cout << "* 2. More goals    *" << endl  ;
    cout << "********************" << endl  ;
} // printStart()







int makeCommand( char ch ) {
    ch = '\0' ;
    cout << "Input a command(0, 1, 2): " ;
    cin >> ch ;
    cout << endl ;


    if ( ch != '0' && ch != '1' && ch != '2' ) {                    //確認是否為0,1,2
        cout << "\nCommand does not exist!" << endl << endl;
        printStart() ;
        makeCommand( ch ) ;
    } // if

    else if ( ch == '0' )
        return 0;
    else if ( ch == '1' )
        return 1;
    else if ( ch == '2' )
        return 2;


} // makeCommand()








void checkFile( string &filename, string str1, bool &theresFile ) {
    cout << "Input a file number: " ;
    cin >> str1;                                //輸入檔名
    cout << endl;
    filename = "input" + str1 + ".txt" ;        //做成txt檔名

    ifstream inputfile( filename ) ;            //打開文件檔

    if ( ! inputfile.is_open() ) {              //若是打不開
        cout << filename << " does not exist!" << endl ;
        theresFile = false;
    } // if

    else {
        theresFile = true;
    } // else



} // checkFile()







void readFile( vecString &stringOfLine, string filename ) {
    ifstream txt;
    txt.open( filename ) ;              //打開文件檔

    string templine;
    stringOfLine.clear() ;              //清除vector中的內容


    while ( getline( txt, templine ) ) {                //一行一行輸入
        stringOfLine.push_back( templine ) ;            //並接在vector後面
    } // while

    stringOfLine.erase( stringOfLine.begin() ) ;        //清除第一行數字

    length = stringOfLine[0].size() ;                   //設定地圖的長
    height = stringOfLine.size() ;                      //設定地圖的高

//    for ( int i = 0 ; i < stringOfLine.size() ; i++ )
//        cout << stringOfLine[i] << endl ;

    txt.close() ;


} // readFile()







bool missionOne( vecString &strMap, int x, int y ) {

    if ( solveMissionOne( strMap, x, y, 0 ) ) {            //是否找到終點
        return true;
    } // if
    else {
        return false;
    } // else


} // missionOne()







bool solveMissionOne( vecString &strMap, int x, int y, int direction ) {
    if ( strMap[x][y] == 'G' )                  //找到終點
        return true;

    strMap[x][y] = 'V';                 //設定走過的路徑為V

    for ( int i = 0; i < 4; i++ ) {                 //上下左右方向確認
        int nextX = x + moveX[ ( direction + i ) % 4 ] ;
        int nextY = y + moveY[ ( direction + i ) % 4 ] ;

        if ( isMove( strMap, nextX, nextY ) ) {             //下一步是否可行

            if ( solveMissionOne( strMap, nextX, nextY, ( direction + i ) % 4 ) )           //遞迴
                return true;

        } // if

    } // for

//    strMap[x][y] = 'E';

    return false;

} // solveMissionOne()







bool isMove( vecString strMap, int x, int y ) {
    if ( ( x >= 0 && x < height ) && ( y >= 0 && y < length ) ) {           //是否超出邊界
        if ( strMap[x][y] == 'E' || strMap[x][y] == 'G' )                   //是否為空(E)或終點(G)
            return true;

        else
            return false;

    } // if

    else
        return false;

} // isMove()







void printMap( vecString strMap ) {
    for ( int i = 0 ; i < strMap.size() ; i++ )                 //輸出地圖
        cout << strMap[i] << endl ;

} // printMap()





void printMapForR( vecString strMap ) {
    for ( int i = 0 ; i < strMap.size() ; i++ ) {
        for ( int j = 0 ; j < strMap[i].size() ; j++ ) {
            if ( strMap[i][j] == 'V' )
                strMap[i][j] = 'R' ;

        } // for

        cout << strMap[i] << endl;

    } // for


} // printMapForR








int checkGoalNum( string str1 ) {
    cout << "Number of G (goals): " ;
    cin >> str1 ;
    cout << endl;

    int num = stoi(str1) ;              //字串轉數字
    while ( num < 0 || num > 100 ) {
        cout << "### The number must be in [1,100] ###" << endl << endl;
        cout << "Number of G (goals): " ;
        cin >> str1;
        cout << endl;
        num = stoi(str1) ;
    } // while

    return num;                 //回傳要找到的G的數量


} // checkGoalNum()





bool missionTwo( vecString &strMap, int gnum ) {
    int x[20], y[20] ;
    int a = 0;


    //紀錄G的位置
    for ( int i = 1 ; i < strMap.size() ; i++ ) {
        for ( int j = 0 ; j < strMap[i].size() ; j++ ) {
            if ( strMap[i][j] == 'G' ) {
                x[a] = i;
                y[a] = j;
                a++ ;
            } // if

        } // for

    } // for


    preX = preY = 0;
    while ( gnum > 0 && solveMissionTwo( strMap, preX, preY, 0 ) ) {       //帶入solveMissionTwo()中
        gnum--;
    } // while



    for ( int b = 0 ; b < a ; b++ ) {                   //將G放回原位
        strMap[x[b]][y[b]] = 'G' ;
    } // for


    if ( gnum != 0 )                    //若是沒找到或是要求的大於地圖中有的G，則回傳false
        return false;


    return true;                    //任務達成

} // missionTwo()








bool solveMissionTwo( vecString &strMap, int x, int y, int direction ) {
    if ( strMap[x][y] == 'G' ) {                 //找到終點
        strMap[x][y] = 'E';                 //將G暫定為E，使之後可通過
        return true;
    } // if

    strMap[x][y] = 'V';                 //設定走過的路徑為V

    for ( int i = 0; i < 4; i++ ) {                 //上下左右方向確認
        int nextX = x + moveX[ ( direction + i ) % 4 ] ;
        int nextY = y + moveY[ ( direction + i ) % 4 ] ;

        preX = x;
        preY = y;

        if ( isMove( strMap, nextX, nextY ) ) {             //下一步是否可行

            if ( solveMissionTwo( strMap, nextX, nextY, ( direction + i ) % 4 ) ) {          //遞迴
                return true;

            } // if


        } // if

    } // for

    return false;


} // solveMissionTwo()




