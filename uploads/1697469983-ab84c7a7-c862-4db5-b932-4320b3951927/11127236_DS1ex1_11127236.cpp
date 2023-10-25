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
	private : // �]�w�ܼ� 
	char maze[100][100];
	char firsthandMaze[100][100];
	int column, row, amo = 0;
	Modes modes;
	
 	public :
	char Readmaze( int x, int y ){ // �x�s�g�c��ƪ��x�} 
 		return maze[x][y];
	}

	void SetMaze( int i, int j, char x ){ // ���g�c�x�}������� 
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
		if ( file.fail() ) { //�ɮ׶}�ҥ��ѴN�^��false 
			return false;
		}	
		else{ //�ɮׯ�}�� 
			string r, c;
			char site;			
			file >> c >> r; // Ū�����e 
			column = atoi( c.c_str() ); //string���A����char 
			row = atoi( r.c_str() ); 

			
			file >> site ; 
			int i, j;
			for( i = 0; i < row; i++ ) { //�N�ɮפ������Ū�J�G���x�}�� 
				for( j = 0; j < column; j++ ) {
					if ( site != '\n' ) { // �p�G���O����N����Ū 
	 					maze[i][j] = site;
	 					file >> site;
	   				}
	   				else{ //�O����N�AŪ�@�� 
	   					file >> site;
					}
				}
			}
			
			file.close(); // �ɮ����� 
			
			for ( int i = 0; i < row; i++ ){
				for ( int j = 0; j < column; j++ ){
					firsthandMaze[i][j] = maze[i][j];
				}
			}
		

		 	return true;
		}
	}
	
	bool findGoals( Maze &vMaze ){

		int i = 0, j = 0, direction = 1; // ��l���V 
		return visitmaze( i, j, direction, vMaze ) ;

	}

	bool visitmaze( int i, int j, int direction, Maze &vMaze ){
        
		if ( vMaze.maze[i][j] == 'G' ) { // Ū��G�N��p�ƾ�� 
			amo--;
			if ( amo == 0 ) { //�S�ؼФF�N�^��true 
		 		return true;
			}
		}

		vMaze.SetMaze( i, j, 'V' ); // ���L�N����V(vmaze) 
		maze[i][j] = 'R'; // ���L�N����R(amaze) 
       	if ( direction == 1 ){ // �V�k�� 
       		if ( vMaze.maze[i][j+1] == 'O' || vMaze.maze[i][j+1] == 'V' || j + 1 == column ){ // �p�G�����ê���B��ɩΨ��L�F 
        		if (vMaze.maze[i-1][j] == 'O' && vMaze.maze[i+1][j] == 'O' 
				 	 || vMaze.maze[i+1][j] == 'V' && vMaze.maze[i-1][j] == 'V' 
					 || vMaze.maze[i+1][j] == 'O' && vMaze.maze[i-1][j] == 'V' 
					 || vMaze.maze[i+1][j] == 'V' && vMaze.maze[i-1][j] == 'O' ){
					direction = 3; // ��V�ܥ� 
					if ( backmaze( i, j, direction, vMaze ) )
						return visitmaze( i, j, direction, vMaze );
				} 
				else { // ���k�����٦����N���ɰw��
        			direction = 2;
        			return visitmaze( i, j, direction, vMaze );
        		} 
			}
			else if( vMaze.maze[i][j+1] == 'E' || vMaze.maze[i][j+1] == 'G' ){ // �p�G�U�@�檺���i�H�� 
        		return visitmaze( i, j + 1, direction, vMaze );		
			}
		}
		
		else if ( direction == 2 ){ // �V�U�� 
       		if ( vMaze.maze[i+1][j] == 'O' || vMaze.maze[i+1][j] == 'V' || i + 1 == row ){ // �p�G�����ê�B��کΨ��L�F 
				if ( vMaze.maze[i][j+1] == 'O' && vMaze.maze[i][j-1] == 'O'   
				 	 || vMaze.maze[i][j+1] == 'V' && vMaze.maze[i][j-1] == 'V' 
					 || vMaze.maze[i][j+1] == 'O' && vMaze.maze[i][j-1] == 'V' 
					 || vMaze.maze[i][j+1] == 'V' && vMaze.maze[i][j-1] == 'O' ){ // ���k����]���ਫ 
					direction = 4; // ��V�ܤW 
					if ( backmaze( i, j, direction, vMaze ) ) {
						return visitmaze( i, j, direction, vMaze );	 
					}
				}
				else { // ���k�����٦����N���ɰw�� 
					direction = 3;
        			return visitmaze( i, j, direction, vMaze );
        		}
			}
			else if ( vMaze.maze[i+1][j] == 'E' || vMaze.maze[i+1][j] == 'G' ){ // �p�G�U�@�檺���i�H�� 
        		return visitmaze( i + 1, j, direction, vMaze );		
			}
		}
		
		else if ( direction == 3 ){ // �V���� 
			if ( vMaze.maze[i][j-1] == 'O' || vMaze.maze[i][j-1] == 'V' || j - 1 < 0 ){ // �p�G�����ê�B��کΨ��L�F  
				if ( vMaze.maze[i+1][j] == 'O' && vMaze.maze[i-1][j] == 'O' 
				 	 || vMaze.maze[i+1][j] == 'V' && vMaze.maze[i-1][j] == 'V' 
					 || vMaze.maze[i+1][j] == 'O' && vMaze.maze[i-1][j] == 'V' 
					 || vMaze.maze[i+1][j] == 'V' && vMaze.maze[i-1][j] == 'O'){
					direction = 1; // ��V�ܥk
					if ( backmaze( i, j, direction, vMaze ) ) { 
						return visitmaze( i, j, direction, vMaze );	
					} 
				} 
				else { // ���k�����٦����N���ɰw�� 
        			direction = 4;
        			return visitmaze( i, j, direction, vMaze );
        		}
			}
			else if( vMaze.maze[i][j-1] == 'E' || vMaze.maze[i][j-1] == 'G' ){ // �p�G�U�@�檺���i�H�� 
        		return visitmaze( i, j - 1, direction, vMaze );		
			}		
		}

		else if ( direction == 4 ){ // �V�W��   
			if ( vMaze.maze[i-1][j] == 'O' || vMaze.maze[i-1][j] == 'V' || i - 1 < 0 ){ // �p�G�����ê�B��کΨ��L�F  
				if ( vMaze.maze[i][j+1] == 'O' && vMaze.maze[i][j-1] == 'O' 
				 	 || vMaze.maze[i][j+1] == 'V' && vMaze.maze[i][j-1] == 'V' 
					 || vMaze.maze[i][j+1] == 'O' && vMaze.maze[i][j-1] == 'V' 
					 || vMaze.maze[i][j+1] == 'V' && vMaze.maze[i][j-1] == 'O'){
					direction = 2; // ��V�ܤU 
					if ( backmaze( i, j, direction, vMaze ) ) {
						return visitmaze( i, j, direction, vMaze );	 
					}
				}
				else { // ���k�����٦����N���ɰw��  
        			direction = 1;
        			return visitmaze( i, j, direction, vMaze );
        		}
			}
			else if ( vMaze.maze[i-1][j] == 'E' || vMaze.maze[i-1][j] == 'G' ){ // �p�G�U�@�檺���i�H�� 
        		return visitmaze( i - 1, j, direction, vMaze );	
			}	
		} 
		
		return false;
	}
	
	bool backmaze( int &i, int &j, int &direction, Maze &vMaze ) {
       	if ( direction == 1 ){ // �V�k�� 
       		if ( maze[i][j+1] == 'R' ) { // ���e�OR���� 
       			if ( vMaze.maze[i+1][j] == 'E' ){ // �ⰼ��E��E��  
					direction = 2;
					return true;
				}
				else if ( vMaze.maze[i-1][j] == 'E' ){
					direction = 4;
					return true;
				}
				else{ //�S��E��R�� 
					maze[i][j] = 'E';
					j++;
 					return backmaze( i, j, direction, vMaze );
				}
			}
			else if ( maze[i][j+1] == 'E' && vMaze.maze[i][j+1] != 'O' ){  
				return true;      			
			}
			else if ( maze[i+1][j] == 'R' ) { // �p�G�ⰼ�O�N��R�� 
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
		
		else if ( direction == 2 ){ // �V�U�� 
       		if ( maze[i+1][j] == 'R' ) { // ���e�OR����
				if ( vMaze.maze[i][j-1] == 'E' ){ // �ⰼ��E��E��
					direction = 3;
					return true;
				}
				else if ( vMaze.maze[i][j+1] == 'E' ){
					direction = 1;
					return true;
				}
				else{ //�S��E��R�� 
					maze[i][j] = 'E';
					i++;
 					return backmaze( i, j, direction, vMaze );
				}
			} 
			else if ( vMaze.maze[i+1][j] == 'E' && vMaze.maze[i+1][j] != 'O' ) 
				return true;
			else if ( maze[i][j+1] == 'R' ) { // �p�G�ⰼ�O�N��R�� 
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
		
		else if ( direction == 3 ){ // �V���� 
			if ( maze[i][j-1] == 'R' ) {
				if ( vMaze.maze[i+1][j] == 'E' ){ // �ⰼ��E��E��
					direction = 4;
					return true;
				}
				else if ( vMaze.maze[i-1][j] == 'E' ){
					direction = 2;
					return true;
				}
				else{ //�S��E��R�� 
					maze[i][j] = 'E';
					j--;
 					return backmaze( i, j, direction, vMaze );
				}
			} 
			else if ( maze[i][j-1] == 'E' && vMaze.maze[i][j-1] != 'O' ){ 
				return true;
			} 
			else if ( maze[i+1][j] == 'R' ) { // �p�G�ⰼ�O�N��R�� 
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
		
		else if ( direction == 4 ){ // �V�W�� 
			if ( maze[i-1][j] == 'R' ){
				if ( vMaze.maze[i][j+1] == 'E' ){ // �ⰼ��E��E��
					direction = 1;
					return true;
				}
				else if ( vMaze.maze[i][j-1] == 'E' ){
					direction = 3;
					return true;
				}
				else{ //�S��E��R�� 
					maze[i][j] = 'E';
					i--;
 					return backmaze( i, j, direction, vMaze );
				}
			} 
			else if ( maze[i-1][j] == 'E' && vMaze.maze[i-1][j] != 'O' ){ 
				return true;
			} 
			else if ( maze[i][j+1] == 'R' ){ // �p�G�ⰼ�O�N��R�� 
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
 
		for ( int i = 0; i < row; i++ ){ // �p�G���l�Ϥ�A��maze�쥻�ӬOG����l 
			for ( int j = 0; j < column; j++ ){
				if ( firsthandMaze[i][j] == 'G' )
					 maze[i][j] = 'G';
			}
		}
		
		for( int i = 0; i < row; i++ ){ // �@�Ӥ@�ӦL�X�� 
			for( int j = 0; j < column; j++ ){
				cout << maze[i][j];
			}
			cout << endl;
		}
	}
	
	void clr() {
		for ( int i = 0; i < row; i++ ){ // �M�Ű}�C 
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
