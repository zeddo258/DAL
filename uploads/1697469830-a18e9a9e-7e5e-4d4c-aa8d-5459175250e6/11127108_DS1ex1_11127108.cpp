// 11127108 陳柏蓁

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std ; 

class Maze {  // 一個row*column矩陣 
	int row ;
	int column ; 
	char maze[100][100] ;

	// 往(右or下or左or上)移動 
	int dx[4] = { 0, 1, 0, -1 } ;
	int dy[4] = { 1, 0, -1, 0 } ;
	
public:
	int goalX, goalY ;  // 紀錄目標的位置
	
	void input( string fileName ){  // 讀檔
		fileName = "input" + fileName + ".txt" ; 
		FILE *file = NULL ;
		file = fopen( fileName.c_str(), "r") ;
	
		if ( file == NULL ) {  // 找不到檔案 
			cout << fileName << " does not exist!" << endl ; 		
			return ;
		}
		
		fscanf( file, "%d", &column ) ;   
		fscanf( file, "%d", &row ) ;
		char ch ; 
		
		for ( int i = 0 ; i < row ; i++ ) {
			fscanf( file, "%c", &ch ) ;  // 讀換行符號 
			for ( int j = 0 ; j < column ; j++ ) {
				fscanf( file, "%c", &maze[i][j] ) ; 
			}	 
		}
	} // input()
	
	
	bool One( int x, int y, int d ) {  // 找一個目標 ，並記錄走過的位置 
		bool find = false ;   
		
		if ( maze[x][y] == 'G' ) { // 抵達目標 
			goalX = x ;
			goalY = y ;
			return true ;
		}
		else if ( x >= row || x < 0 || y >= column || y < 0 )  // 超出矩陣 
			return false ;
			
		else if ( maze[x][y] == 'O' || maze[x][y] == 'V' )   // 遇到障礙物或走過的路 
			return false ; 
	
		else  // 將當前位置紀錄為已走過 
			maze[x][y] = 'V' ;
		
		find = One( x + dx[d], y + dy[d], d ) ;  // 往當前方向走一步 
		
		if ( ! find )  // 如果無法繼續前進，則依序逆時針朝其他方向尋找路徑 
			find = One( x + dx[( d + 1 ) % 4 ], y + dy[( d + 1 ) % 4 ], ( d + 1 ) % 4 )   
					|| One( x + dx[( d + 2 ) % 4 ], y + dy[( d + 2 ) % 4 ], ( d + 2 ) % 4 ) 
					|| One( x + dx[( d + 3 ) % 4 ], y + dy[( d + 3 ) % 4 ], ( d + 3 ) % 4 ) 
					|| One( x + dx[d], y + dy[d], d ) ;
		
		return find ;
	
	} // One()
	
	void Remove() {  // 移除非路徑的紀錄 "V" 
		for ( int i = 0 ; i < row ; i++ ) {
			for ( int j = 0 ; j < column ; j++ ) {
				//cout << maze[i][j] << endl ;
				if ( maze[i][j] == 'V' ) {
					//cout << "111" << endl ;
					maze[i][j] = 'E' ;
				}
			}
		}
	}
	
	void Print() {  // 印出迷宮矩陣 
		for ( int i = 0 ; i < row ; i++ ) {
			for ( int j = 0 ; j < column ; j++ ) 
				cout << maze[i][j] ;
			
			cout << endl ;
		}
		
		cout << endl ;
	}
	
	
	bool Route( int x, int y, int d ) {  // 尋找並紀錄路徑 
		bool b = false ;

		if ( x == 0 && y == 0 ) { // 抵達目標 
			maze[x][y] = 'R' ;
			return true ;
		}
		else if ( x >= row || x < 0 || y >= column || y < 0 )  // 超出矩陣 
			return false ;
	
		else if ( maze[x][y] == 'O' || maze[x][y] == 'R' || maze[x][y] == 'E' )  // 遇到障礙物or已記錄的路徑or沒走過的路 
			return false ;
		
		else {
			if ( maze[x][y] != 'G' )
				maze[x][y] = 'R' ;
		}
		
		b = Route( x + dx[d], y + dy[d], d ) ;  // 當前方向往前一步 
		if ( ! b ) { // 如果無法繼續前進，則依序順時針朝其他方向尋找路徑 
			b = Route( x + dx[( d + 3 ) % 4 ], y + dy[( d + 3 ) % 4 ], ( d + 3 ) % 4 ) 
					|| Route( x + dx[( d + 2 ) % 4 ], y + dy[( d + 2 ) % 4 ], ( d + 2 ) % 4 ) 
					|| Route( x + dx[( d + 1 ) % 4 ], y + dy[( d + 1 ) % 4 ], ( d + 1 ) % 4 ) ;
		}
		
		if ( !b ) {  // 如果沒辦法走到目標，就不列入路徑 
			if ( maze[x][y] == 'R' )
				maze[x][y] = 'E' ;
		}
		
		return b ;		
	} 
};


int main(){
	Maze maze ;
	Maze visited ;
	Maze route ;
	int goalX, goalY ;  // 紀錄目標的位置
	
	string command ;  
	string fileName ;  
	char fileNumber ;
	bool end = false ;
	while ( command != "0" ){   
		cout << endl << "*** Path Finding ***" ;
		cout << endl << "* 0. Quit          *" ;
		cout << endl << "* 1. One goal      *" ;
		cout << endl << "* 2. More goals    *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2): " ;
		cin >> command ;   // 獲取指令 
			
		if ( command == "0" )
			break ;
		
		else if ( command == "1" ) {
			cout << endl << "Input a file number: " ;
			cin >> fileName ;
			maze.input( fileName ) ;  // 讀檔 
			visited = maze ;  // 複製迷宮矩陣 
			
			if ( visited.One( 0, 0, 0 ) ) {  // 從左上角開始向右尋找目標 
				goalX = visited.goalX ;
				goalY = visited.goalY ;
				route = visited ;  // 複製紀錄過拜訪路徑的矩陣 
			}
			
			visited.Print() ;   
			
			if ( route.Route( goalX, goalY, 3 ) ) {  // 如果有找到路徑 
				route.Remove() ;  // 移除非路徑的紀錄 "V" 
				route.Print() ;
			}
		}
		else if ( command == "2" )
			cout << "..." << endl ;
		else
			cout << "Command does not exist!" << endl ;
			
	} //while() ;
	
	return 0 ;
}
