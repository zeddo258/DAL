// 11127108 ���f�

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std ; 

class Maze {  // �@��row*column�x�} 
	int row ;
	int column ; 
	char maze[100][100] ;

	// ��(�kor�Uor��or�W)���� 
	int dx[4] = { 0, 1, 0, -1 } ;
	int dy[4] = { 1, 0, -1, 0 } ;
	
public:
	int goalX, goalY ;  // �����ؼЪ���m
	
	void input( string fileName ){  // Ū��
		fileName = "input" + fileName + ".txt" ; 
		FILE *file = NULL ;
		file = fopen( fileName.c_str(), "r") ;
	
		if ( file == NULL ) {  // �䤣���ɮ� 
			cout << fileName << " does not exist!" << endl ; 		
			return ;
		}
		
		fscanf( file, "%d", &column ) ;   
		fscanf( file, "%d", &row ) ;
		char ch ; 
		
		for ( int i = 0 ; i < row ; i++ ) {
			fscanf( file, "%c", &ch ) ;  // Ū����Ÿ� 
			for ( int j = 0 ; j < column ; j++ ) {
				fscanf( file, "%c", &maze[i][j] ) ; 
			}	 
		}
	} // input()
	
	
	bool One( int x, int y, int d ) {  // ��@�ӥؼ� �A�ðO�����L����m 
		bool find = false ;   
		
		if ( maze[x][y] == 'G' ) { // ��F�ؼ� 
			goalX = x ;
			goalY = y ;
			return true ;
		}
		else if ( x >= row || x < 0 || y >= column || y < 0 )  // �W�X�x�} 
			return false ;
			
		else if ( maze[x][y] == 'O' || maze[x][y] == 'V' )   // �J���ê���Ψ��L���� 
			return false ; 
	
		else  // �N��e��m�������w���L 
			maze[x][y] = 'V' ;
		
		find = One( x + dx[d], y + dy[d], d ) ;  // ����e��V���@�B 
		
		if ( ! find )  // �p�G�L�k�~��e�i�A�h�̧ǰf�ɰw�¨�L��V�M����| 
			find = One( x + dx[( d + 1 ) % 4 ], y + dy[( d + 1 ) % 4 ], ( d + 1 ) % 4 )   
					|| One( x + dx[( d + 2 ) % 4 ], y + dy[( d + 2 ) % 4 ], ( d + 2 ) % 4 ) 
					|| One( x + dx[( d + 3 ) % 4 ], y + dy[( d + 3 ) % 4 ], ( d + 3 ) % 4 ) 
					|| One( x + dx[d], y + dy[d], d ) ;
		
		return find ;
	
	} // One()
	
	void Remove() {  // �����D���|������ "V" 
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
	
	void Print() {  // �L�X�g�c�x�} 
		for ( int i = 0 ; i < row ; i++ ) {
			for ( int j = 0 ; j < column ; j++ ) 
				cout << maze[i][j] ;
			
			cout << endl ;
		}
		
		cout << endl ;
	}
	
	
	bool Route( int x, int y, int d ) {  // �M��ì������| 
		bool b = false ;

		if ( x == 0 && y == 0 ) { // ��F�ؼ� 
			maze[x][y] = 'R' ;
			return true ;
		}
		else if ( x >= row || x < 0 || y >= column || y < 0 )  // �W�X�x�} 
			return false ;
	
		else if ( maze[x][y] == 'O' || maze[x][y] == 'R' || maze[x][y] == 'E' )  // �J���ê��or�w�O�������|or�S���L���� 
			return false ;
		
		else {
			if ( maze[x][y] != 'G' )
				maze[x][y] = 'R' ;
		}
		
		b = Route( x + dx[d], y + dy[d], d ) ;  // ��e��V���e�@�B 
		if ( ! b ) { // �p�G�L�k�~��e�i�A�h�̧Ƕ��ɰw�¨�L��V�M����| 
			b = Route( x + dx[( d + 3 ) % 4 ], y + dy[( d + 3 ) % 4 ], ( d + 3 ) % 4 ) 
					|| Route( x + dx[( d + 2 ) % 4 ], y + dy[( d + 2 ) % 4 ], ( d + 2 ) % 4 ) 
					|| Route( x + dx[( d + 1 ) % 4 ], y + dy[( d + 1 ) % 4 ], ( d + 1 ) % 4 ) ;
		}
		
		if ( !b ) {  // �p�G�S��k����ؼСA�N���C�J���| 
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
	int goalX, goalY ;  // �����ؼЪ���m
	
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
		cin >> command ;   // ������O 
			
		if ( command == "0" )
			break ;
		
		else if ( command == "1" ) {
			cout << endl << "Input a file number: " ;
			cin >> fileName ;
			maze.input( fileName ) ;  // Ū�� 
			visited = maze ;  // �ƻs�g�c�x�} 
			
			if ( visited.One( 0, 0, 0 ) ) {  // �q���W���}�l�V�k�M��ؼ� 
				goalX = visited.goalX ;
				goalY = visited.goalY ;
				route = visited ;  // �ƻs�����L���X���|���x�} 
			}
			
			visited.Print() ;   
			
			if ( route.Route( goalX, goalY, 3 ) ) {  // �p�G�������| 
				route.Remove() ;  // �����D���|������ "V" 
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
