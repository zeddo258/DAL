// 10942208 陳洺安 資四乙


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
	
	scanf( "%d", &cmd ); // 讀入命令 
	cout << endl ;
	if ( cmd != 0 && cmd != 1 && cmd != 2 ) {  // 命令判斷 
		cout << endl<< "Command does not exist!" << endl ;  //命令不存在，重新讀入 
		control ( cmd ) ;
	} // if
	else if ( cmd == 0 ) {
		system("exit"); // 執行退出 
	} // else if
	else return true ; // 讀入成功 
	
} // control

int main( void ) {

	int cmd = -1 ; 
	control ( cmd ) ; // 呼叫控制面板

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
    		
    	if (!inputFile.is_open() || inputFile.peek() == EOF ) { // peek查看文件下一字符,如果是eof表示空檔案 
       		cout << filename << " does not exist! " << endl;
       		control ( cmd ) ;
       		//return 1 ; // 退出程序
    	} // if
	    else { 
		    	
			int column = -1 ;
		 	int row = -1 ;
			int mou_x = 0 ;
			int mou_y = 0 ;
		
			inputFile >> column ;	
			inputFile >> row ;
			   	
			if ( column >= 0 && row >= 0 ) { 
					
				if (cmd == 1 ) { // 行數列數不能為負
					
					Maze maze(row, column);
					//cout << maze.getColumn() << "行" << endl; 	
					//cout << maze.getRow() << "列" << endl; 
						
					maze.setGraph( row, column, filename ) ; // 設定迷宮 
					maze.solveMaze( -1, -1, mou_x, mou_y,'R' , false ) ; // 解迷宮
					maze.setpassPathGraph() ;
					maze.printGraph( row, column, maze.passPathGraph ) ; // 輸出迷宮

		    		cout << endl ;
		    		/*cout << "開始列印經過點" << endl ;
		    		for ( int i = 0 ; maze.passPath[i][0] != -1 ; i++ ) {
		    			cout << maze.passPath[i][0] ;
		    			cout << maze.passPath[i][1] << endl;
					}
					cout << "開始列印走兩步" << endl ; 
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
		    		if ( maze.foundPath ) { // 如過有找到路徑顯示R 
		    			for ( int i = 0 ; i <  row ; i++ ) {
			    			for ( int j = 0 ; j < column ; j++ ) {
			    				if( maze.getC(i,j) == 'V' ) {
			    					maze.setC(i,j,'R');
								} // if
							} // for
					 	} // for
					maze.printGraph( row, column ) ; // 輸出迷宮
					}
					//cout << endl ;
					//maze.printGraph( row, column ) ;
					//maze.printGraph() ;

					
					inputFile.close();
					control ( cmd ) ; // 呼叫控制面板 
						
				} // if
				else if ( cmd == 2 ) { // mode = 2 ，使用者輸入想要的目標個數 
					int  goalnumber = -1 ;
					cout << "Number of G (goals):" ;
					cin >> goalnumber ;
					Maze maze(row, column);
					maze.setGraph( row, column, filename ) ; // 設定迷宮
			    	
			    	if(  goalnumber == 1 ) {
			    		maze.solveMaze( -1, -1, mou_x, mou_y,'R' , false ) ;
			    		maze.setpassPathGraph() ;
						maze.printGraph( row, column, maze.passPathGraph ) ; // 輸出迷宮
						cout << endl ; 
						if ( maze.foundPath ) { // 如過有找到路徑顯示R 
			    			for ( int i = 0 ; i <  row ; i++ ) {
				    			for ( int j = 0 ; j < column ; j++ ) {
				    				if( maze.getC(i,j) == 'V' ) {
				    					maze.setC(i,j,'R');
									} // if
								} // for
						 	} // for
						maze.printGraph( row, column ) ; // 輸出迷宮
						}		
					} 
					else { 
						maze.solveMaze( -1, -1, mou_x, mou_y, 'R' , false, goalnumber ) ;
						maze.setpassPathGraph2() ;
						maze.printGraph( row, column, maze.passPathGraph ) ; // 輸出迷宮
				   		cout << endl ;
		
				   		if( maze.getGoalnum() >= goalnumber ) { // 如果使用者輸入N> 迷宮目標數量顯示R 
				   			for ( int i = 0 ; i <  row ; i++ ) {
			    				for ( int j = 0 ; j < column ; j++ ) {
			    					if( maze.getC(i,j) == 'V' ) {
			    						maze.setC(i,j,'R');
									} // if
								} // for
							} // for
							maze.printGraph( row, column ) ; // 輸出迷宮
						}// if
					}

				
					
			   		inputFile.close();
					control ( cmd ) ; // 呼叫控制面板 
				} // else if 
				else cout << "格式錯誤" << endl ;
					
			} // if
				
		} // else 
			
	} //while  



	
    system("pause"); 
	return 0; 
} // main()

