#include <iostream> 
#include <fstream>
#include <cstdio>
#include <string.h> 
#include <stdio.h> 
#include <cstdlib>

using namespace std;

enum Modes{
	oneG,
	moreG
};
	

class Maze{
	private : // 設定變數 
	char maze[100][100];
	char firsthandMaze[100][100];
	int column, row, amo = 0;
	Modes modes;
	
 	public :
	char Readmaze( int x, int y ){ // 儲存迷宮資料的矩陣 
 		return maze[x][y];
	}

	void SetMaze( int i, int j, char x ){ // 更改迷宮矩陣內的資料 
		maze[i][j] = x;
	}

	bool load( string filename, Modes mode ){
		string name = "input" + filename + ".txt";
		char fileName[50];
		strcpy( fileName, name.c_str() );
		ifstream file;
		file.open( fileName );
		if ( mode == moreG ) {
			cout << "N=";
			cin >> amo;
		}
		else 
		 	amo = 1;
		if ( file.fail() ) { //檔案開啟失敗就回傳false 
			return false;
		}	
		else{ //檔案能開啟 
			string r, c;
			char site;			
			file >> c >> r; // 讀取長寬 
			column = atoi( c.c_str() ); //string型態換成char 
			row = atoi( r.c_str() ); 

			
			file >> site ; 
			int i, j;
			for( i = 0; i < row; i++ ) { //將檔案內的資料讀入二維矩陣內 
				for( j = 0; j < column; j++ ) {
					if ( site != '\n' ) { // 如果不是換行就接著讀 
	 					maze[i][j] = site;
	 					file >> site;
	   				}
	   				else{ //是換行就再讀一個 
	   					file >> site;
					}
				}
			}
			
			file.close(); // 檔案關閉 
			
			for ( int i = 0; i < row; i++ ){
				for ( int j = 0; j < column; j++ ){
					firsthandMaze[i][j] = maze[i][j];
				}
			}
		

		 	return true;
		}
	}
	
	bool findGoals( Maze &vMaze ){

		int i = 0, j = 0, direction = 1; // 位子跟方向 
		return visitmaze( i, j, direction, vMaze ) ;

	}

	bool visitmaze( int i, int j, int direction, Maze &vMaze ){
        
		if ( vMaze.maze[i][j] == 'G' ) { // 讀到G就把計數器減ㄧ 
			amo--;
			if ( amo == 0 ) { //沒目標了就回傳true 
		 		return true;
			}
		}

		vMaze.SetMaze( i, j, 'V' ); // 走過就換成V(vmaze) 
		maze[i][j] = 'R'; // 走過就換成R(amaze) 
       	if ( direction == 1 ){ // 向右走 
       		if ( vMaze.maze[i][j+1] == 'O' || vMaze.maze[i][j+1] == 'V' || j + 1 == column ){ // 如果撞到障礙物、邊界或走過了 
        		if (vMaze.maze[i-1][j] == 'O' && vMaze.maze[i+1][j] == 'O' 
				 	 || vMaze.maze[i+1][j] == 'V' && vMaze.maze[i-1][j] == 'V' 
					 || vMaze.maze[i+1][j] == 'O' && vMaze.maze[i-1][j] == 'V' 
					 || vMaze.maze[i+1][j] == 'V' && vMaze.maze[i-1][j] == 'O' ){
					direction = 3; // 方向變左 
					if ( backmaze( i, j, direction, vMaze ) )
						return visitmaze( i, j, direction, vMaze );
				} 
				else { // 左右兩邊還有路就順時針轉
        			direction = 2;
        			return visitmaze( i, j, direction, vMaze );
        		} 
			}
			else if( vMaze.maze[i][j+1] == 'E' || vMaze.maze[i][j+1] == 'G' ){ // 如果下一格的路可以走 
        		return visitmaze( i, j + 1, direction, vMaze );		
			}
		}
		
		else if ( direction == 2 ){ // 向下走 
       		if ( vMaze.maze[i+1][j] == 'O' || vMaze.maze[i+1][j] == 'V' || i + 1 == row ){ // 如果撞到障礙、邊際或走過了 
				if ( vMaze.maze[i][j+1] == 'O' && vMaze.maze[i][j-1] == 'O'   
				 	 || vMaze.maze[i][j+1] == 'V' && vMaze.maze[i][j-1] == 'V' 
					 || vMaze.maze[i][j+1] == 'O' && vMaze.maze[i][j-1] == 'V' 
					 || vMaze.maze[i][j+1] == 'V' && vMaze.maze[i][j-1] == 'O' ){ // 左右兩邊也不能走 
					direction = 4; // 方向變上 
					if ( backmaze( i, j, direction, vMaze ) ) {
						return visitmaze( i, j, direction, vMaze );	 
					}
				}
				else { // 左右兩邊還有路就順時針轉 
					direction = 3;
        			return visitmaze( i, j, direction, vMaze );
        		}
			}
			else if ( vMaze.maze[i+1][j] == 'E' || vMaze.maze[i+1][j] == 'G' ){ // 如果下一格的路可以走 
        		return visitmaze( i + 1, j, direction, vMaze );		
			}
		}
		
		else if ( direction == 3 ){ // 向左走 
			if ( vMaze.maze[i][j-1] == 'O' || vMaze.maze[i][j-1] == 'V' || j - 1 < 0 ){ // 如果撞到障礙、邊際或走過了  
				if ( vMaze.maze[i+1][j] == 'O' && vMaze.maze[i-1][j] == 'O' 
				 	 || vMaze.maze[i+1][j] == 'V' && vMaze.maze[i-1][j] == 'V' 
					 || vMaze.maze[i+1][j] == 'O' && vMaze.maze[i-1][j] == 'V' 
					 || vMaze.maze[i+1][j] == 'V' && vMaze.maze[i-1][j] == 'O'){
					direction = 1; // 方向變右
					if ( backmaze( i, j, direction, vMaze ) ) { 
						return visitmaze( i, j, direction, vMaze );	
					} 
				} 
				else { // 左右兩邊還有路就順時針轉 
        			direction = 4;
        			return visitmaze( i, j, direction, vMaze );
        		}
			}
			else if( vMaze.maze[i][j-1] == 'E' || vMaze.maze[i][j-1] == 'G' ){ // 如果下一格的路可以走 
        		return visitmaze( i, j - 1, direction, vMaze );		
			}		
		}

		else if ( direction == 4 ){ // 向上走   
			if ( vMaze.maze[i-1][j] == 'O' || vMaze.maze[i-1][j] == 'V' || i - 1 < 0 ){ // 如果撞到障礙、邊際或走過了  
				if ( vMaze.maze[i][j+1] == 'O' && vMaze.maze[i][j-1] == 'O' 
				 	 || vMaze.maze[i][j+1] == 'V' && vMaze.maze[i][j-1] == 'V' 
					 || vMaze.maze[i][j+1] == 'O' && vMaze.maze[i][j-1] == 'V' 
					 || vMaze.maze[i][j+1] == 'V' && vMaze.maze[i][j-1] == 'O'){
					direction = 2; // 方向變下 
					if ( backmaze( i, j, direction, vMaze ) ) {
						return visitmaze( i, j, direction, vMaze );	 
					}
				}
				else { // 左右兩邊還有路就順時針轉  
        			direction = 1;
        			return visitmaze( i, j, direction, vMaze );
        		}
			}
			else if ( vMaze.maze[i-1][j] == 'E' || vMaze.maze[i-1][j] == 'G' ){ // 如果下一格的路可以走 
        		return visitmaze( i - 1, j, direction, vMaze );	
			}	
		} 
		
		return false;
	}
	
	bool backmaze( int &i, int &j, int &direction, Maze &vMaze ) {
       	if ( direction == 1 ){ // 向右走 
       		if ( maze[i][j+1] == 'R' ) { // 往前是R的話 
       			if ( vMaze.maze[i+1][j] == 'E' ){ // 兩側有E往E走  
					direction = 2;
					return true;
				}
				else if ( vMaze.maze[i-1][j] == 'E' ){
					direction = 4;
					return true;
				}
				else{ //沒有E往R走 
					maze[i][j] = 'E';
					j++;
 					return backmaze( i, j, direction, vMaze );
				}
			}
			else if ( maze[i][j+1] == 'E' && vMaze.maze[i][j+1] != 'O' ){  
				return true;      			
			}
			else if ( maze[i+1][j] == 'R' ) { // 如果兩側是就往R走 
				direction = 2;
				i++;
 				return backmaze( i, j, direction, vMaze );
			}
			else if ( maze[i-1][j] == 'R' ) {
				direction = 4;
				i--;
 				return backmaze( i, j, direction, vMaze );
			}
		}
		
		else if ( direction == 2 ){ // 向下走 
       		if ( maze[i+1][j] == 'R' ) { // 往前是R的話
				if ( vMaze.maze[i][j-1] == 'E' ){ // 兩側有E往E走
					direction = 3;
					return true;
				}
				else if ( vMaze.maze[i][j+1] == 'E' ){
					direction = 1;
					return true;
				}
				else{ //沒有E往R走 
					maze[i][j] = 'E';
					i++;
 					return backmaze( i, j, direction, vMaze );
				}
			} 
			else if ( vMaze.maze[i+1][j] == 'E' && vMaze.maze[i+1][j] != 'O' ) 
				return true;
			else if ( maze[i][j+1] == 'R' ) { // 如果兩側是就往R走 
				direction = 1;
				j++;
 				return backmaze( i, j, direction, vMaze );
			}
			else if ( maze[i][j-1] == 'R' ) {
				direction = 3;
				j--;
 				return backmaze( i, j, direction, vMaze );
			}
		}
		
		else if ( direction == 3 ){ // 向左走 
			if ( maze[i][j-1] == 'R' ) {
				if ( vMaze.maze[i+1][j] == 'E' ){ // 兩側有E往E走
					direction = 4;
					return true;
				}
				else if ( vMaze.maze[i-1][j] == 'E' ){
					direction = 2;
					return true;
				}
				else{ //沒有E往R走 
					maze[i][j] = 'E';
					j--;
 					return backmaze( i, j, direction, vMaze );
				}
			} 
			else if ( maze[i][j-1] == 'E' && vMaze.maze[i][j-1] != 'O' ){ 
				return true;
			} 
			else if ( maze[i+1][j] == 'R' ) { // 如果兩側是就往R走 
				i++;
				direction = 2;
				return backmaze( i, j, direction, vMaze );
			}
			else if ( maze[i-1][j] == 'R' ) {
				direction = 4;
				i--;
 				return backmaze( i, j, direction, vMaze );
			}
		}
		
		else if ( direction == 4 ){ // 向上走 
			if ( maze[i-1][j] == 'R' ){
				if ( vMaze.maze[i][j+1] == 'E' ){ // 兩側有E往E走
					direction = 1;
					return true;
				}
				else if ( vMaze.maze[i][j-1] == 'E' ){
					direction = 3;
					return true;
				}
				else{ //沒有E往R走 
					maze[i][j] = 'E';
					i--;
 					return backmaze( i, j, direction, vMaze );
				}
			} 
			else if ( maze[i-1][j] == 'E' && vMaze.maze[i-1][j] != 'O' ){ 
				return true;
			} 
			else if ( maze[i][j+1] == 'R' ){ // 如果兩側是就往R走 
				direction = 1;
				j++;
 				return backmaze( i, j, direction, vMaze );
			}
			else if ( maze[i][j-1] == 'R' ){
				direction = 3;
				j--;
 				return backmaze( i, j, direction, vMaze );
			}
		}
		return false;
	}
	
	void show() {
		cout << endl;
 
		for ( int i = 0; i < row; i++ ){ // 如果跟原始圖比，把maze原本該是G的位子 
			for ( int j = 0; j < column; j++ ){
				if ( firsthandMaze[i][j] == 'G' )
					 maze[i][j] = 'G';
			}
		}
		
		for( int i = 0; i < row; i++ ){ // 一個一個印出來 
			for( int j = 0; j < column; j++ ){
				cout << maze[i][j];
			}
			cout << endl;
		}
	}
	
	void clr() {
		for ( int i = 0; i < row; i++ ){ // 清空陣列 
			for ( int j = 0; j < column; j++ ){
				maze[i][j] = '\0';
			}
		}	
	}
} ;

int main( void ) {
	int command = 0;         // user command 
  
  	do {
    	Maze aMaze;            // a matrix
    	char x = aMaze.Readmaze( 0, 0 );
    	string fileName;       // a file name
    	Modes mode = oneG;     // default: one goal
    
    	cout << endl<< "*** Path Finding ***";
    	cout << endl << "* 0. Quit          *";
   	 	cout << endl << "* 1. One goal      *";
    	cout << endl << "* 2. More goals    *";
    	cout << endl << "********************";
    	cout << endl << "Input a command(0, 1, 2):";
    	cin >> command;                     // get the command
    	if ( ( command == 1 ) || ( command == 2 ) ) {
      		if ( command == 2 ) 
        		mode = moreG;                   // one or more goals
      		cout << endl << "Input a file number (e.g.,201,202,...)";
      		cin >> fileName;
      		if ( aMaze.load( fileName, mode ) ) {       // load the original matrix
    			Maze vMaze( aMaze );                      // a copy to keep the visited cells
     			bool success = aMaze.findGoals( vMaze );  // find a path to goal(s)

     			mode = oneG;            // reset to default
     			vMaze.show();           // show on screen the visited cells
    			if ( success )          // to check if the goal is rea
      			 	aMaze.show();         // clear up the copy
    		 	vMaze.clr(); 
   			} // end inner-if 
   
      		aMaze.clr();            // '0':stop the program
 		} // end outer-if   
   		else if ( !command )
      		break;
    	else 
      		cout << endl << "Command does not exist!" << endl;

  	} while ( true );
  	system( "pause" );            // pause the execution
  	return 0;
} // end of main
