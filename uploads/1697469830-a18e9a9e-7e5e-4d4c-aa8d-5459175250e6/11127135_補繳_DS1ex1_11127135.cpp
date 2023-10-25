// 學號:11127135,姓名:李廷宇 
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>
using namespace std;

class Maze {
	
	public:
		
		int row, column;
		char matrix[100][100]; // the original map
		char copyMatrix[100][100]; // copyMatrix is a copy of matrix, but it converts E and G into V
		int Rpath[10000][3], k = 0; // Rpath records the coordinate related to the real path, k represents its k-1th coordinate
		vector<vector<vector<int> > > path; // store the coordinate of R
		bool fileNameExist = false; // if file name exists return true,else return false
		
		bool setMaze( char command[] ) {
			cout << endl << "Input a file name: ";
			string fileNumber, fileName;
			
			if ( strlen( command ) == 1 ) {
				cin >> fileNumber;
				fileName = "input" + fileNumber + ".txt";
			} // end if
			else {
				fileNumber = command;
				fileName = "input" + fileNumber.substr( 1, strlen( command ) - 1 ) + ".txt";
			} // end else
			
			ifstream inputfile( fileName ); // 以輸入方式開啟檔案 
			if ( !inputfile.is_open() ) {
				cout << endl << fileName << " does not exist!" << endl;
				fileNameExist = false;
			} // end if
			else {
				fileNameExist = true;
				inputfile >> column >> row; // get row and column
						
				for ( int i = 0 ; i < row ; i++ ) { // get maze
					for ( int j = 0 ; j < column ; j++ ) {
						inputfile >> matrix[i][j];
					} // end for
				} // end for
			} // end else
				
			inputfile.close();
							
			for ( int i = 0 ; i < row ; i++ ) {
				for ( int j = 0 ; j < column ; j++ ) {
					copyMatrix[i][j] = matrix[i][j];
				} // end for
			} // end for 
			
			for ( int i = 0 ; i < 10000 ; i++ ) {
				Rpath[i][0] = '\0';
				Rpath[i][1] = '\0';
				Rpath[i][2] = '\0'; 
			} // end for
			
			return true;
		} // end setMaze
		
		bool findGoals( int y, int x, int & direction, int goalNumber, int & count ) {
			// direction represents the forward direction, 1 means right, 2 means down, 3 means left, 4 means up
			// goalNumber means the number of goals have to travel
			// count means the number of goals already passed
			
			if ( goalNumber == count ) return true;
		
	        if ( copyMatrix[y][x] == 'G' ) { // 在copyMatrix中，走過的路徑皆會變成'V' 
	        	count++;
				copyMatrix[y][x] = 'V';
	    		Rpath[k][0] = y;
	    		Rpath[k][1] = x;
	    		Rpath[k][2] = direction;
				k++;
				
				vector<vector<int> > p( k, vector<int>(3) );
				for ( int i = 0 ; i < k ; i++ ) {
					for ( int j = 0 ; j < 3 ; j++ ) {
						p[i][j] = Rpath[i][j];
					} // end for
				} // end for
				
				path.push_back( p );
	        } // end if
			else if ( k == 0 ) {
				copyMatrix[y][x] = 'V';
	    		Rpath[k][0] = y;
	    		Rpath[k][1] = x;
	    		Rpath[k][2] = direction;
				k++;
			} // end if
    		else if ( k != 0 && ( Rpath[k-1][0] != y || Rpath[k-1][1] != x ) ) { // 與前一點的座標不同才存進Rpath中 
	    		Rpath[k][0] = y;
	    		Rpath[k][1] = x;
	    		Rpath[k][2] = direction;
				k++;
			} // end else if
			
			copyMatrix[y][x] = 'V';
			
			int i = 0;
			while ( i < 4 ) {
				if ( direction == 1 ) { // 右 
					if ( x + 1 < column && ( copyMatrix[y][x+1] == 'E' || copyMatrix[y][x+1] == 'G' ) )
						findGoals( y, x + 1, direction, goalNumber, count );					
					direction = direction % 4 + 1;
				} // end if
				else if ( direction == 2 ) { // 下 
					if ( y + 1 < row && ( copyMatrix[y+1][x] == 'E' || copyMatrix[y+1][x] == 'G' ) )
						findGoals( y + 1, x, direction, goalNumber, count );
					direction = direction % 4 + 1;
				} // end else if
				else if ( direction == 3 ) { // 左 
					if ( x - 1 >= 0 && ( copyMatrix[y][x-1] == 'E' || copyMatrix[y][x-1] == 'G' ) ) 
						findGoals( y, x - 1, direction, goalNumber, count );					
					direction = direction % 4 + 1;
				} // end else if
				else if ( direction == 4 ) { // 上
					if ( y - 1 >= 0 && ( copyMatrix[y-1][x] == 'E' || copyMatrix[y-1][x] == 'G' ) ) 
						findGoals( y - 1, x, direction, goalNumber, count );
					direction = direction % 4 + 1;
				} // end else if
				
				i++;
			} // end while 
				
			k--;
			return goalNumber == count;
		} // end findGoals
	
		void printMaze( bool findSuccess ) {
			for ( int i = 0 ; i < row ; i++ ) {
				for ( int j = 0 ; j < column ; j++ ) {
					if ( matrix[i][j] == 'G' && copyMatrix[i][j] == 'V' ) copyMatrix[i][j] = matrix[i][j]; // 把copyMatrix中的'V'改回'G' 
				} // end for
			} // end for
			
			for ( int i = 0 ; i < row ; i++ ) {
				for ( int j = 0 ; j < column ; j++ ) {
					cout << copyMatrix[i][j];
				} // end for
				
				cout << endl;
			} // end for
			
			if ( findSuccess ) {
				for ( int i = 0 ; i < path.size() ; i++ ) {
					for ( int j = 0 ; j < path[i].size() ; j++ ) {
						if ( matrix[path[i][j][0]][path[i][j][1]] != 'G' )
							matrix[path[i][j][0]][path[i][j][1]] = 'R';
					} // end for
				} // end for
				
				cout << endl;
				for ( int i = 0 ; i < row ; i++ ) {
					for ( int j = 0 ; j < column ; j++ ) {
						cout << matrix[i][j];
					} // end for
					
					cout << endl;
				} // end for
			} // end if
			
			cout << endl;
		} // end printMaze
}; // end Maze

int main() {
	char command[100]; // user command
	for ( int i = 0 ; i < 100 ; i++ ) command[i] = '\0'; // initialize

	while ( true ) {
		Maze maze; // declare a instance of Maze
		bool findSuccess = false; // whether successfully find the route or not
		
		cout << endl << "*** Path Finding ***";
		cout << endl << "* 0. Quit          *";
		cout << endl << "* 1. One goal      *";
		cout << endl << "* 2. More goals    *";
		cout << endl << "********************";
		cout << endl << "Input a command(0, 1, 2): ";
		
		if ( strlen( command ) == 0 ) cin >> command;
		
		if ( command[0] < 48 || command[0] > 50 ) {
			cout << endl << "Command does not exist!" << endl;
			if ( strlen( command ) == 1 ) command[0] = '\0'; 
			else {
				char c[100];  
				for ( int i = 0 ; i < 100 ; i++ ) c[i] = '\0';
				for ( int i = 1 ; i < strlen( command ) ; i++ ) c[i-1] = command[i]; // 把command去掉第0位
				for ( int i = 0 ; i < strlen( c ) ; i++ ) command[i] = c[i];
				for ( int i = strlen( c ) ; i < 100 ; i++ ) command[i] = '\0';
			} // end else
		} // end if
		else if ( command[0] == 48 ) break;
		else {
			int dir = 1, count = 0;
			
			if ( command[0] == 49 && maze.setMaze( command ) ) { // only one goal
				findSuccess = maze.findGoals( 0, 0, dir, 1, count );
				if ( maze.fileNameExist ) maze.printMaze( findSuccess );
				if ( strlen( command ) == 1 ) command[0] = '\0';
				else {
					char c[100];
					for ( int i = 0 ; i < 100 ; i++ ) c[i] = '\0';
					for ( int i = 1 ; i < strlen( command ) ; i++ ) c[i-1] = command[i];
					for ( int i = 0 ; i < strlen( c ) ; i++ ) command[i] = c[i];
					for ( int i = strlen( c ) ; i < 100 ; i++ ) command[i] = '\0';
				} // end else
			} // end if
			else if ( command[0] == 50 && maze.setMaze( command ) ) { // more than one goal
				char goalNumber[100];
				for ( int i = 0 ; i < 100 ; i++ ) goalNumber[i] = '\0';
				int len = 0;
				
				while ( maze.fileNameExist ) {
					cout << endl << "Number of G (goals): ";
					cin >> goalNumber;
					
					for ( int i = 0 ; i < strlen( goalNumber ) ; i++ )
						if ( isdigit( goalNumber[i] ) ) len++;
					
					if ( len == strlen( goalNumber ) ) {
						if ( 0 >= atoi( goalNumber ) || atoi( goalNumber ) > 100 ) cout << endl << "### The number must be in [1,100] ###" << endl;
						else break;
					} // end if
					
					for ( int i = 0 ; i < 100 ; i++ ) goalNumber[i] = '\0';
					len = 0; 
				} // end while
				
				findSuccess = maze.findGoals( 0, 0, dir, atoi( goalNumber ), count );
				if ( maze.fileNameExist ) maze.printMaze( findSuccess );
				for ( int i = 0 ; i < 100 ; i++ ) command[i] = '\0';
			} // end else if
		} // end else
	} // end while
	
	return 0;
} // end main()
