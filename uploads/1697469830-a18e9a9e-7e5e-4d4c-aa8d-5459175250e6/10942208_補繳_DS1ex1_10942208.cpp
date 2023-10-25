// 10942208 ���y�w ��|�A


#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Maze.h"

using namespace std;
typedef char Str[40] ;

bool control ( int &cmd ) {  
	
	
	cout << "\n*** Path Finding ***" << endl ;
	cout << "* 0. Quit          *" << endl ;
	cout << "* 1. One goal      *" << endl ;
	cout << "* 2. More goals    *" << endl ;
	cout << "********************" << endl ;
	cout << "Input a command(0, 1, 2): " ; 
	
	scanf( "%d", &cmd ); // Ū�J�R�O 
	cout << endl ;
	if ( cmd != 0 && cmd != 1 && cmd != 2 ) {  // �R�O�P�_ 
		cout << endl<< "Command does not exist!" << endl ;  //�R�O���s�b�A���sŪ�J 
		control ( cmd ) ;
	} // if
	else if ( cmd == 0 ) {
		system("exit"); // ����h�X 
	} // else if
	else return true ; // Ū�J���\ 
	
} // control

int main( void ) {

	int cmd = -1 ; 
	control ( cmd ) ; // �I�s����O

	while ( control && ( cmd != 0 ) ) { 
	    
	    Str num = " " ;
		Str backname = ".txt" ;
		ifstream inputFile; 
	   	cout << "Input a file number:" ;  
		cin >> num ;
		cout << endl ;
    	Str filename = "input" ;
		strcat( filename, num ) ; 
		strcat( filename, backname ) ; 
    	inputFile.open(filename);
    		
    	if (!inputFile.is_open() || inputFile.peek() == EOF ) { // peek�d�ݤ��U�@�r��,�p�G�Oeof��ܪ��ɮ� 
       		cout << filename << " does not exist! " << endl;
       		control ( cmd ) ;
       		//return 1 ; // �h�X�{��
    	} // if
	    else { 
		    	
			int column = -1 ;
		 	int row = -1 ;
			int mou_x = 0 ;
			int mou_y = 0 ;
		
			inputFile >> column ;	
			inputFile >> row ;
			   	
			if ( column >= 0 && row >= 0 ) { 
					
				if (cmd == 1 ) { // ��ƦC�Ƥ��ର�t
					
					Maze maze(row, column);
					//cout << maze.getColumn() << "��" << endl; 	
					//cout << maze.getRow() << "�C" << endl; 
						
					maze.setGraph( row, column, filename ) ; // �]�w�g�c 
					maze.solveMaze( -1, -1, mou_x, mou_y,'R' , false ) ; // �Ѱg�c
					maze.setpassPathGraph() ;
					maze.printGraph( row, column, maze.passPathGraph ) ; // ��X�g�c

		    		cout << endl ;
		    		/*cout << "�}�l�C�L�g�L�I" << endl ;
		    		for ( int i = 0 ; maze.passPath[i][0] != -1 ; i++ ) {
		    			cout << maze.passPath[i][0] ;
		    			cout << maze.passPath[i][1] << endl;
					}
					cout << "�}�l�C�L����B" << endl ; 
					for ( int i = 0 ; maze.passTwicePath[i][0] != -1 ; i++ ) {
		    			cout << maze.passTwicePath[i][0] ;
		    			cout << maze.passTwicePath[i][1] << endl;
					}
					for ( int i = 0 ; maze.passPath[i][0] != -1 ; i++ ) {
						for ( int j = 0 ; maze.passPath[j][0] != -1 ; j++ ) {
							if ( maze.passPath[j][0] == maze.passTwicePath[i][1] ) {
								
							}
						}
						
					}*/
		    		if ( maze.foundPath ) { // �p�L�������|���R 
		    			for ( int i = 0 ; i <  row ; i++ ) {
			    			for ( int j = 0 ; j < column ; j++ ) {
			    				if( maze.getC(i,j) == 'V' ) {
			    					maze.setC(i,j,'R');
								} // if
							} // for
					 	} // for
					maze.printGraph( row, column ) ; // ��X�g�c
					}
					//cout << endl ;
					//maze.printGraph( row, column ) ;
					//maze.printGraph() ;

					
					inputFile.close();
					control ( cmd ) ; // �I�s����O 
						
				} // if
				else if ( cmd == 2 ) { // mode = 2 �A�ϥΪ̿�J�Q�n���ؼЭӼ� 
					int  goalnumber = -1 ;
					cout << "Number of G (goals):" ;
					cin >> goalnumber ;
					Maze maze(row, column);
					maze.setGraph( row, column, filename ) ; // �]�w�g�c
			    	
			    	if(  goalnumber == 1 ) {
			    		maze.solveMaze( -1, -1, mou_x, mou_y,'R' , false ) ;
			    		maze.setpassPathGraph() ;
						maze.printGraph( row, column, maze.passPathGraph ) ; // ��X�g�c
						cout << endl ; 
						if ( maze.foundPath ) { // �p�L�������|���R 
			    			for ( int i = 0 ; i <  row ; i++ ) {
				    			for ( int j = 0 ; j < column ; j++ ) {
				    				if( maze.getC(i,j) == 'V' ) {
				    					maze.setC(i,j,'R');
									} // if
								} // for
						 	} // for
						maze.printGraph( row, column ) ; // ��X�g�c
						}		
					} 
					else { 
						maze.solveMaze( -1, -1, mou_x, mou_y, 'R' , false, goalnumber ) ;
						maze.setpassPathGraph2() ;
						maze.printGraph( row, column, maze.passPathGraph ) ; // ��X�g�c
				   		cout << endl ;
		
				   		if( maze.getGoalnum() >= goalnumber ) { // �p�G�ϥΪ̿�JN> �g�c�ؼмƶq���R 
				   			for ( int i = 0 ; i <  row ; i++ ) {
			    				for ( int j = 0 ; j < column ; j++ ) {
			    					if( maze.getC(i,j) == 'V' ) {
			    						maze.setC(i,j,'R');
									} // if
								} // for
							} // for
							maze.printGraph( row, column ) ; // ��X�g�c
						}// if
					}

				
					
			   		inputFile.close();
					control ( cmd ) ; // �I�s����O 
				} // else if 
				else cout << "�榡���~" << endl ;
					
			} // if
				
		} // else 
			
	} //while  



	
    system("pause"); 
	return 0; 
} // main()

