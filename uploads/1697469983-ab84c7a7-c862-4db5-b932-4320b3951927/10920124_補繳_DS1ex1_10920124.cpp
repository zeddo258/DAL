// 10920124 林雅琪 
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<fstream>
#define MAX_LEN 255
using namespace std;

class maze{
	
	private:
		
		int x ; // x for 橫 
		int y ; // y for 直 
		char **mazeData ;
		
	public:
		
		void setNum( string firstLine ) {
			int a = 0 ;
			x = 0 ;
			y = 0 ;
			while( firstLine[a] >= '0' and firstLine[a] <= '9' ) {
				x = firstLine[a] - '0' + x*10 ;
				a++ ;
			}
			a++ ;
			while( firstLine[a] >= '0' and firstLine[a] <= '9' ) {
				y = firstLine[a] - '0' + y*10 ;
				a++ ;
			}
		}
		
		void readMaze() {
			
			string fileName ;
    		cin >> fileName ;
			
			string inFileName = "input" + fileName + ".txt" ;
    		const char *tempFile = inFileName.c_str() ;
    		
    		ifstream ifs ;
			ifs.open( tempFile ) ; 
			
			if( !ifs.is_open() ) {
				cout << endl << tempFile << " is not exist!" ;
			}
			else{
				string firstLine ;
				getline( ifs, firstLine ) ;
				setNum( firstLine ) ;
				
				mazeData = new char*[y] ;
				for( int a = 0 ; a < y ; a++ ){
					mazeData[a] = new char[x] ;
					for( int b = 0 ; b < x ; b++ ) {
						ifs >> mazeData[a][b] ;
					}
				}
				ifs.close() ;
			}
    		
		}
		
		void walkMazeVRoad(int a, int b, char **temp, int count, int &finds, int prev) {	
			if( b < x-1 and temp[a][b+1] == 'G' ) finds+=1 ;
			if( a < y-1 and temp[a+1][b] == 'G' ) finds+=1 ;
			if( b > 0 and temp[a][b-1] == 'G' ) finds+=1 ;
			if( a > 0 and temp[a-1][b] == 'G' ) finds+=1 ;
			
			if( temp[a][b] == 'G' ) finds+=1 ;
			
			if( finds == count ) {
				if( temp[a][b] == 'E' ) temp[a][b] = 'V' ;
				return ;
			}
			
			if( temp[a][b] == 'O' ) return ;
			
			if( temp[a][b] == 'E' ) {
				temp[a][b] = 'V' ;
				if(prev == 1) {
					if( b < x-1 and temp[a][b+1] != 'O' ) walkMazeVRoad( a, b+1, temp, count, finds, 1 ) ;
					else if( a < y-1 and temp[a+1][b] != 'O' ) walkMazeVRoad( a+1, b, temp, count, finds, 2 ) ;
					else if( b > 0 and temp[a][b-1] != 'O' ) walkMazeVRoad( a, b-1, temp, count, finds, 3 ) ;
					else if( a > 0 and temp[a-1][b] != 'O' ) walkMazeVRoad( a-1, b, temp, count, finds, 4 ) ;		
				}
				else if(prev == 2) {
					if( a < y-1 and temp[a+1][b] != 'O' ) walkMazeVRoad( a+1, b, temp, count, finds, 2 ) ;
					else if( b < x-1 and temp[a][b+1] != 'O' ) walkMazeVRoad( a, b+1, temp, count, finds, 1 ) ;
					else if( b > 0 and temp[a][b-1] != 'O' ) walkMazeVRoad( a, b-1, temp, count, finds, 3 ) ;
					else if( a > 0 and temp[a-1][b] != 'O' ) walkMazeVRoad( a-1, b, temp, count, finds, 4 ) ;
				}
				else if(prev == 3) {
					if( b > 0 and temp[a][b-1] != 'O' ) walkMazeVRoad( a, b-1, temp, count, finds, 3 ) ;
					else if( b < x-1 and temp[a][b+1] != 'O' ) walkMazeVRoad( a, b+1, temp, count, finds, 1 ) ;
					else if( a < y-1 and temp[a+1][b] != 'O' ) walkMazeVRoad( a+1, b, temp, count, finds, 2 ) ;
					else if( a > 0 and temp[a-1][b] != 'O' ) walkMazeVRoad( a-1, b, temp, count, finds, 4 ) ;		
				}
				else if(prev == 4) {
					if( a > 0 and temp[a-1][b] != 'O' ) walkMazeVRoad( a-1, b, temp, count, finds, 4 ) ;		
					else if( b < x-1 and temp[a][b+1] != 'O' ) walkMazeVRoad( a, b+1, temp, count, finds, 1 ) ;
					else if( a < y-1 and temp[a+1][b] != 'O' ) walkMazeVRoad( a+1, b, temp, count, finds, 2 ) ;
					else if( b > 0 and temp[a][b-1] != 'O' ) walkMazeVRoad( a, b-1, temp, count, finds, 3 ) ;
				}
			}
			else return ;
			// 先看上下左右 後走 
        }


		
		void walkMazeRRoad( int a, int b, char **temp ){
			
			if( temp[a][b] == 'G' ) return ;
			if( temp[a][b] == 'V' ) {
				temp[a][b] = 'R' ;
				if( b < x-1 ) walkMazeRRoad( a, b+1, temp ) ;
				if( a < y-1 ) walkMazeRRoad( a+1, b, temp ) ;
				if( b > 0 ) walkMazeRRoad( a, b-1, temp ) ;
				if( a > 0 ) walkMazeRRoad( a-1, b, temp ) ;
			}
			else return ;
			
		}
		
		void outMaze(){
			for( int a = 0 ; a < y ; a++ ) {
				for( int b = 0 ; b < x ; b++ ) {
					cout << mazeData[a][b] ;
				}
				cout << endl ;
			}
		}
		
		void missionWalkMazeRoad() {
			walkMazeRRoad( 0, 0, mazeData ) ;
			
			outMaze() ;
		}
		
		void missionWalkMazeVisit( int num ) {
			
			int a = 0 ;
			walkMazeVRoad( 0, 0, mazeData, num, a, 1) ;
			if( a == 0 ) {
				cout << endl << "There's no road" ;
			}
			else {
				outMaze() ;
			}
		} 
		
		void cleanMaze() {
			delete [] mazeData ;
		}
		
};

void mission1(){
	
	maze Maze ;
    
    Maze.readMaze() ;
	Maze.missionWalkMazeVisit( 1 ) ;
	cout << endl ;
	Maze.missionWalkMazeRoad() ;
	
	Maze.cleanMaze() ;
}

void mission2(){
	
	int num ;
	
	maze Maze ;
	
	Maze.readMaze() ;
	
	cout << endl << "Num of Goals:" ;
	cin >> num ;
	
	Maze.missionWalkMazeVisit( num ) ;
	cout << endl ;
	Maze.missionWalkMazeRoad() ;
	Maze.cleanMaze() ;
}

int main() {
	int command = 0 ;
    do{
    	cout << endl ;
    	cout << endl << "*** Path Finding ***" ;
    	cout << endl << "* 0. Quit          *" ;
    	cout << endl << "* 1. One goal      *" ;
    	cout << endl << "* 2. More goals    *" ;
    	cout << endl << "********************" ;
    	cout << endl << "Input a command(0, 1, 2): "  ;
	    cin >> command ;

	    cin.ignore(MAX_LEN, '\n' ) ;
	    // 清掉在buffer的指令

	    if ( command == 1 ) {
	    	cout << endl << "Input a file number:" ;
	    	mission1() ;
		} // 跑練習一

		else if ( command == 2 ) {
			cout << endl << "Input a file number:"  ;
	    	mission2() ;
		} // 跑練習二 

		else if( !command ) break ;

		else cout << endl << "Command does not exist!" << endl ;

	}while(true) ;

    system("pause") ;
    return 0 ;
	
} // main

