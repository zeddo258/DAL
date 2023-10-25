// 11127133 陳乙菁
# include <stdio.h>
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <cstdlib>
using namespace std;

class Maze {

    public: 
        int a, b ; // 地圖大小
        int way = 3 ; // 是任務一還是任務二
        int numofgoals = 0 ; // 有幾個G
        int c = 0 ; 
        bool getG = false ; // 有無走到G
        std::string waytemp ; // 是任務一還是任務二
        std::string numofgoaltemp ; // 有幾個G
    private: 
        int direc = 0 ; // 控制右下左上
        int atemp = 0, btemp = 0 ; // 下一個可能要走的點
        vector<vector<char>> maze ; // 讀入地圖
        vector<vector<char>> vmaze ; // 存V的地圖
        vector<vector<char>> rmaze ; // 存R的地圖
        vector<vector<int>> place ; // 存G的位置

    void init(){
        maze = vector<vector<char>>(b,vector<char>(a, ' '));
        vmaze = vector<vector<char>>(b,vector<char>(a, ' '));
        rmaze = vector<vector<char>>(b,vector<char>(a, ' '));
        place = vector<vector<int>>(100,vector<int>(2,0)) ; 
    }
    public:
        void load(){ // 讀入
            ifstream in ;
            string filename ;
            bool success = false ;
            while ( success == false) {
                try { // command的防呆
                    cin >> waytemp ;
                    if ( stoi(waytemp) == 0 || stoi(waytemp) == 1 || stoi(waytemp) == 2 )  {
                        way = stoi(waytemp) ;
                        success = true ;
                    }
                    else throw runtime_error("") ;
                }
                catch ( exception e ) {
                    cout << "Input is wrong,please input again! " << "\n" ;
                }
            }
            if ( way == 0 ) exit(0) ;

            cout << "Input a filename" << "\n" ;
            
            cin >> filename ;
            in.open(filename);
            while ( in.fail() ) { // file的防呆
                cout << "Open a wrong file, please open again! " << "\n" ;
                cin >> filename ;
                in.open(filename);
            }
            
            if ( way == 2 ) { 
                cout << "Input num of goals." << "\n" ;
                while ( numofgoals < 1 ) { // numofgoals的防呆
                    try {
                        cin >> numofgoaltemp ;
                        if ( stoi(numofgoaltemp) < 100 && stoi(numofgoaltemp) > 0 )  numofgoals = stoi(numofgoaltemp) ;
                    }
                    catch ( exception e ) {
                        cout << "Input wrong, please input again! " << "\n" ;
                        cin >> numofgoaltemp ;
                    }
                }
            }
            else numofgoals = 1 ;

            in >> a >> b;
            init();
            int c = 0 ;
            for ( int count = 0; count < b; count++ ) { // 把地圖上所有G的位置存起來
                for( int count2 = 0; count2 < a; count2++ ){
                    in >> maze[count][count2] ;
                    if ( maze[count][count2] == 'G' ) {
                        place[c][0] = count ;
                        place[c][1] = count2 ;
                        c++ ;
                    }
                }
            }

            for ( int count = 0; count < b; count++ ) { // 複製原地圖進V地圖
                for( int count2 = 0; count2 < a; count2++ ){
                    vmaze[count][count2] = maze[count][count2] ;
                }
            }

            for ( int count = 0; count < b; count++ ) { // 複製原地圖進R地圖
                for( int count2 = 0; count2 < a; count2++ ) 
                    rmaze[count][count2] = maze[count][count2] ;
            }

            vmaze[0][0] = 'V' ;
            in.close();
        }

    bool findGoals(int atemp, int btemp) { // 0 0
        bool legal = false ; // 有無走到G
        bool stop = false ; // 是否超出地圖範圍或遇到O或遇到V
        int x = atemp, y = btemp ; // x y 是目前的點,btemp atemp是上下左右的點
        int sum = 0 ; // 是否四周的點都無法走了

        while ( legal == false ) {
            stop = false ;
            if ( direc%4 == 0 ) atemp = x + 1 ; // 右
            else if ( direc%4 == 1 ) btemp = y + 1; // 下
            else if ( direc%4 == 2 ) atemp = x - 1 ; // 左
            else btemp = y - 1 ; // 上

            if ( atemp >= a || btemp >= b || atemp < 0 || btemp < 0 ) {
                stop = true ; // 超出地圖範圍
                sum++ ;
            }
            else if ( maze[btemp][atemp] == 'O' ) {
                stop = true ; // 路障
                sum++ ;
            }
            else if ( vmaze[btemp][atemp] == 'V' ) {
                stop = true ; // 走過
                sum++ ;
            }

            if ( sum == 4 ) {
                if ( getG == false ) rmaze[y][x] = 'E' ;
                return false ; // 四周都不能走了
            }
            
            if ( stop == true ) {
                atemp = x ;
                btemp = y ;
            }
            else if ( stop == false ) {
                getG = false ;
                rmaze[btemp][atemp] = 'R' ; // 存入走過的地方
                vmaze[btemp][atemp] = 'V' ; // 存入路徑
            
                if ( maze[btemp][atemp] == 'G' ) {
                    numofgoals-- ;
                    getG = true ;
                    if ( numofgoals == 0 ) return true ;
                } // 走到終點
                
                legal = findGoals( atemp, btemp ) ;
            }
            direc++ ; // 轉向
        }
        return true ;
    }

    void show() {
        int c = 0 ;
        for ( int count = 0; count < b; count++ ) { // 把R地圖和V地圖的G補回去
            for( int count2 = 0; count2 < a; count2++ ){
                if( count == place[c][0] && count2 == place[c][1] ) {
                    vmaze[count][count2] = 'G' ;
                    rmaze[count][count2] = 'G' ;
                    c++ ;
                }
            }
        }

        rmaze[0][0] = 'R' ;
        for ( int count = 0; count < b; count++ ) { // 印出V地圖
            for( int count2 = 0; count2 < a; count2++ ){
                cout << vmaze[count][count2] ;
            }
            cout << "\n" ;
        }

        cout << "\n" ;
        if ( numofgoals == 0 ) {
            for ( int count = 0; count < b; count++ ) { // 印出R地圖
                for( int count2 = 0; count2 < a; count2++ ){
                    cout << rmaze[count][count2] ;
                }
                cout << "\n" ;
            }
        }
        
    }

    void clear() { // 清空前一個地圖的紀錄
        way = 3 ;
        numofgoals = 0 ;
        maze.clear() ;
        rmaze.clear() ;
        vmaze.clear() ;
        place.clear() ;
        int c = 0 ;
        bool getG = false ;
    }
};

int main() {
    Maze maze ;
    while(true){
        cout << endl << "***Path Finding***" ;
        cout << endl << "*0.Quit          *" ;
        cout << endl << "*1.One goal      *" ;
        cout << endl << "*2 More goals    *" ;
        cout << endl << "******************" ;
        cout << endl << "Input a command(0,1,2)" ;
        maze.load() ;
        maze.findGoals( 0, 0) ;
        maze.show() ;
        maze.clear() ;
    }
}