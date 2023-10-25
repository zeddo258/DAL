// 11127158 周宗昱 

#include <iostream>
#include <fstream>
#include <string>


// 使用命名空間以簡化程式碼
using namespace std ;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

class Maze {

public:
	
	Maze() {
	}
	
	void Read() {

		string tn ;
		cout << "please input a textname:" ;
		cin >> tn ;
		ifstream inputFile( tn.c_str() ); // 打開文本文件 input101.txt
		char ch ;
		int i = 0 ;
		int en = 0 ;
		char rc[900] ;
		numCols = 0 ; // reset numCols
		numRows = 0 ; // reset numRows
		
	    while (inputFile.get(ch)) { // store file to 1-degree array rc[]
	        rc[i] = ch ;
	        i = i + 1 ;
		} // while
		
		for( int i = 0 ; i < 99 ; i ++ ) { 
			if( rc[en] == '\n' )
				break ;
				
			else 
				en++ ;
		}
		
	    int check = 0 ;
	    
	    for ( int i = 0 ; i< en  ; i ++ ) { // calculate numCols and numRows
	    	if ( rc[i+1] == ' ' && check == 0 ) {
    			numCols += rc[i] - 48 ;
    			i++;
    			check=1;
			} // if

	    	else if(rc[i+1] != ' '&& check == 0){
	    		numCols += rc[i] - 48 ;
	    		numCols = numCols * 10 ;
	    	} // else if 

	    	else if ( i+1<en && check==1 ) {
    			numRows += rc[i] - 48 ;
    			numRows = numRows * 10 ;
			} // else if
			
	    	else if( i+1==en && check==1) {
	    		numRows += rc[i] - 48 ;
	    	} // else if
		} // for

	    int x = en+1 ;
	    
	    for( int i = 0 ; i < numRows ; i++ ) { // transfer 1-degree rc[] to 2-degree maze[][]
	    	for( int j = 0 ; j < numCols ; j++ ) {
	    		if ( x % (numCols+1) == en ) // skip '\n' to store maze[][]
	    			x++ ;
	
	    		maze[i][j] = rc[x] ;
	    		x = x + 1 ;
			}
		}
			
	} // Read()
	
	
	void FindG( int N ) {
		int y = 0 ;
		int nc = 0 ; // nowColumn // right left 
		int nr = 0 ; // nowRow
		bool isFind = false ;
		int count = 0 ;
		int check2=0;
		int path[numRows*numCols][4] ; // each row is [step,row,col,y]
		bool stuck ; // to check if stuck or not
 		int gnum = 0 ; // to count how many 'G's have been found
		int step = 0 ; 
		int tempB[N][3] ; // to store the location when at 'B' and is stuck
		int tempb = 0 ; // the index of tempB
		
		
		for ( int i = 0 ; i < numRows*numCols ; i ++ ) {
			for( int j = 0 ; j < 4 ; j ++ ) {
				path[i][j] = 0 ;
			} 
		} // for reset path
		
		while( !isFind ) {
			stuck = false ;

			if( y == 4 ) y=0;
					
			if ( y == 0 ) { // when direction is right now 
				if ( nc+1 >= numCols ) { // when next step is bond then turn right
					y ++ ;
				}
				
				else if( maze[nr][nc+1] == 'G' ) { // when next step is 'G' and now at 'E', replace now step from 'E' to 'V' 
					if( maze[nr][nc] == 'E' )
						maze[nr][nc] = 'V' ;
					maze[nr][nc+1] = 'B'; // replace next step from 'G' to 'B'
					gnum++ ;
					VtoR() ; // when find a 'G', replace all V in maze[][] to R 
					nc ++ ;
					step ++ ;
					path[step-1][3] = y ;
					stuck = Stuck( step, nr, nc, y ) ; // check if next step will stuck 
				} // else if
				
				else if ( maze[nr][nc+1] == 'E' || maze[nr][nc+1] == 'B' ) {
					if( maze[nr][nc] == 'E' )
						maze[nr][nc] = 'V' ;
					nc ++ ;
					step ++ ; 
					path[step-1][3] = y ;
					stuck = Stuck( step, nr, nc, y ) ;
				} // else if 
				
				else if ( maze[nr][nc+1] == 'O' || maze[nr][nc+1] == 'V' || maze[nr][nc+1] == 'Z' || maze[nr][nc+1] == 'R' ) {
					y = y + 1 ;
				} // else if 
				
		
			} // if y == 0 
			
			else if ( y == 1 ) { // when direction is down now
				
				if ( nr+1 >= numRows ) {
					y ++ ;
				}
				
				else if( maze[nr+1][nc] == 'G') {
					if( maze[nr][nc] == 'E' )
						maze[nr][nc] = 'V' ;
					maze[nr+1][nc] = 'B' ;
					gnum++ ;
					VtoR() ;
					nr ++ ;
					step ++ ;
					path[step-1][3] = y ;
					stuck=Stuck( step, nr, nc, y ) ;
				} // else if 
				
				else if( maze[nr+1][nc] == 'E' || maze[nr+1][nc] == 'B' ) {
					if(maze[nr][nc] == 'E' )
 						maze[nr][nc] = 'V' ;
					nr ++ ;
					step ++ ; 
					path[step-1][3] = y ;
					stuck=Stuck( step, nr, nc, y ) ;
				} // else if 
				
				else if ( maze[nr+1][nc] == 'O' || maze[nr+1][nc] == 'V' || maze[nr+1][nc] == 'Z' || maze[nr+1][nc] == 'R' ) {
					y = y + 1 ;
				} // else if 
			} // else if y == 1
			
			else if ( y == 2 ) { // when direction is left now
				
				if ( nc-1 <0 ) {
					y++;
				}
				else if( maze[nr][nc-1] == 'G') {
					if( maze[nr][nc] == 'E' )
						maze[nr][nc] = 'V' ;
					maze[nr][nc-1] = 'B' ;
					gnum++;
					VtoR() ;
					nc -- ;
					step ++ ;
					path[step-1][3] = y ;
					stuck=Stuck( step, nr, nc, y ) ;
				} // else if 
				
				else if( maze[nr][nc-1] == 'E' || maze[nr][nc-1] == 'B' ) {
					if(maze[nr][nc] == 'E' )
						maze[nr][nc] = 'V' ;
					nc-- ;
					step ++ ; 
					path[step-1][3] = y ;
					stuck=Stuck( step, nr, nc, y ) ;
				} // else if 
				
				else if ( maze[nr][nc-1] == 'O' || maze[nr][nc-1] == 'V' || maze[nr][nc-1] == 'Z' || maze[nr][nc-1] == 'R' ) {
					y = y + 1 ;
				} // else if 
			} // else if y == 2
			
			else if ( y == 3 ) { // when direction is up now 
				if ( nr-1 < 0 ) {
					y ++ ;
				} 
				else if(maze[nr-1][nc] == 'G' ){
					if( maze[nr][nc] == 'E' )
						maze[nr][nc] = 'V' ;
					maze[nr-1][nc] = 'B' ;
					gnum++;
					VtoR() ;
					nr -- ;
					step ++ ;
					path[step-1][3] = y ;
					stuck=Stuck( step, nr, nc, y ) ;
				}
				
				else if( maze[nr-1][nc] == 'E' || maze[nr-1][nc] == 'B' ) {
					if( maze[nr][nc] == 'E' )
						maze[nr][nc] = 'V' ;
					nr -- ;
					step ++ ; 
					path[step-1][3] = y ;
					stuck=Stuck( step, nr, nc, y ) ;
				} // else if 
				
				else if ( maze[nr-1][nc] == 'O' || maze[nr-1][nc] == 'V' || maze[nr-1][nc] == 'Z' || maze[nr-1][nc] == 'R' ) {
					y = y + 1 ;
				} // else if 
				
			} // else if y == 3

				
			if( stuck ) { // when stuck, back to previous step
				while( stuck && step!=1 ) {
					if ( maze[nr][nc] == 'B' ) { // if at 'B' and stuck, remember this location in tempB[][] and change to 'Z' 
						maze[nr][nc] = 'Z' ;
						tempB[tempb][0] = tempb ; 
						tempB[tempb][1] = nr ;
						tempB[tempb][2] = nc ;
						tempb++ ;		
					} // if

					if( maze[nr][nc] == 'V' || maze[nr][nc] == 'E' )
						maze[nr][nc] = 'Z' ;
					step -- ;
					nr = path[step-1][1] ;
					nc = path[step-1][2] ;
					y = path[step-1][3] ;
										
					stuck = Stuck( step, nr, nc, y ) ;
				} // while
			} // if stuck 
			
			else if( stuck==false ) { // update path
			
				path[step-1][0] = step ;
				path[step-1][1] = nr ;
				path[step-1][2] = nc ;
			} // else if
			
			
			if ( gnum == N ) { // when gnum == N this funtion is end
				check2++;
				isFind = true ;
			} // if
			
			count++ ;
			if ( count > 999 )
				break ;
		} // while
		
		if ( maze[nr][nc] == 'E' ) // for the last step when case not find N's G 
			maze[nr][nc] = 'V' ;
		
		if( check2 == 0 ) { //  when gnum < N
		
			cout << "不存在路徑" << endl ;			 
			PrintGraph( check2 ) ;		
		} // if
		
		else{ // print the ansewr
			
			for( int i = 0 ; i < numRows ; i++ ) {
		    	for( int j = 0 ; j < numCols ; j++ ) {
		    		if ( maze[i][j] == 'B' )
		    			maze[i][j] = 'G' ;
				}
			} // for BtoG
	
	    	for( int i = 0 ; i < tempb ; i++ ) {
	    		maze[tempB[i][1]][tempB[i][2]] = 'G' ;
			} // BtoG
			
			PrintGraph( check2 ) ;
			cout << endl ;
		} // else 
		

		
	} // FindG()

	void PrintGraph( int check2 ) {
		char ansR[numRows][numCols]	;
		char ansV[numRows][numCols]	;
		
		for( int i = 0 ; i < numRows ; i++ ) {
	    	for( int j = 0 ; j < numCols ; j++ ) {
	    		ansR[i][j] = maze[i][j] ;
				ansV[i][j] = maze[i][j] ;  		
			}
		}
		
		for( int i = 0 ; i < numRows ; i++ ) {
	    	for( int j = 0 ; j < numCols ; j++ ) {
	    		if ( ansV[i][j] == 'Z' || ansV[i][j] == 'R' )
	    			ansV[i][j] = 'V' ;
			}
		} // ZRtoV
		
		for( int i = 0 ; i < numRows ; i++ ) {
	    	for( int j = 0 ; j < numCols ; j++ ) {
	    		if ( ansR[i][j] == 'V' || ansR[i][j] == 'Z' )
	    			ansR[i][j] = 'E' ;
			}
		} // VZtoE
		
		for( int i = 0 ; i < numRows ; i++ ) {
	    	for( int j = 0 ; j < numCols ; j++ ) {
				cout << ansV[i][j] ;
			}
			cout << endl ;
		} // print ansV
		
		cout << endl ;
		
		if ( check2 != 0 ) {
		
			for( int i = 0 ; i < numRows ; i++ ) {
		    	for( int j = 0 ; j < numCols ; j++ ) {
					cout << ansR[i][j] ;
				}
				
				cout << endl ;
			} // print ansR
		} // if
	} // PrintGraph()
	
	bool Stuck ( int step, int nr, int nc, int y ) {
		
		
		if ( y == 0 ) {
			if ( ( maze[nr][nc+1] == 'O' ||  maze[nr][nc+1] == 'V' || maze[nr][nc+1] == 'Z' || maze[nr][nc+1] == 'R' || nc+1 >= numCols )
				&& ( maze[nr-1][nc] == 'O' || maze[nr-1][nc] == 'V' || maze[nr-1][nc] == 'Z' || maze[nr-1][nc] == 'R' || nr-1 < 0 )
			 	&& ( maze[nr+1][nc] == 'O' ||  maze[nr+1][nc] == 'V' || maze[nr+1][nc] == 'Z' ||  maze[nr+1][nc] == 'R' || nr+1 >= numRows ) )
				return true ;
			else 
				return false ;
		} //  if y == 0
		
		else if ( y == 1 ) {
			if ( ( maze[nr+1][nc] == 'O' || maze[nr+1][nc] == 'V' || maze[nr+1][nc] == 'Z' || maze[nr+1][nc] == 'R' || nr+1 >= numRows  )
				&& ( maze[nr][nc+1] == 'O'|| maze[nr][nc+1] == 'V' || maze[nr][nc+1] == 'Z' || maze[nr][nc+1] == 'R' || nc+1 >= numCols )
				&& ( maze[nr][nc-1] == 'O'|| maze[nr][nc-1] == 'V' || maze[nr][nc-1] == 'Z' || maze[nr][nc-1] == 'R' || nc-1 < 0  ) )
				return true ;
			else 
				return false ;
		} // else if y == 1
		 
		else if ( y == 2 ) {
			if ( ( maze[nr][nc-1] == 'O' || maze[nr][nc-1] == 'V' || maze[nr][nc-1] == 'Z' || maze[nr][nc-1] == 'R' || nc-1 < 0 )
				&& ( maze[nr-1][nc] == 'O'|| maze[nr-1][nc] == 'V' || maze[nr-1][nc] == 'Z' || maze[nr-1][nc] == 'R' || nr-1 < 0 ) 
				&& ( maze[nr+1][nc] == 'O'|| maze[nr+1][nc] == 'V' || maze[nr+1][nc] == 'Z' || maze[nr+1][nc] == 'R' || nr+1 >= numRows ) )
				return true ;
			else 
				return false ;
				
		} // else if y == 2
		
		else if ( y == 3 ) {
			if ( ( maze[nr][nc+1] == 'O' || maze[nr][nc+1] == 'V' || maze[nr][nc+1] == 'Z' || maze[nr][nc+1] == 'R' || nc + 1 >= numCols ) 
				&& ( maze[nr-1][nc] == 'O' || maze[nr-1][nc] == 'V' || maze[nr-1][nc] == 'Z' || maze[nr-1][nc] == 'R' || nr-1 < 0 )
				&& ( maze[nr][nc-1] == 'O'|| maze[nr][nc-1] == 'V' || maze[nr][nc-1] == 'Z' || maze[nr][nc-1] == 'R' || nc-1 < 0 ) )
				return true ;
			else 
				return false ;
		} // else if y == 3 
		
	} // Stuck()
	
	void VtoR () {
		for( int i = 0 ; i < numRows ; i++ ) {
	    	for( int j = 0 ; j < numCols ; j++ ) {
	    		if ( maze[i][j] == 'V' ) 
	    			maze[i][j] = 'R' ;
			}
		}
		
	} // VtoR()
	
	void Run() {
		int cmd = 0 ;
		int N = 0 ;
		while(1) {
			cout << "*** Path Finding ***" << endl ;
			cout << "* 0. Quit          *" << endl ;
			cout << "* 1. One goal      *" << endl ;
			cout << "* 2. More goals    *" << endl ;
			cout << "********************" << endl ;
			cout << "Input a command(0, 1, 2):" ;
			cin >> cmd ; 
			
			if ( cmd == 0 )
				break ;
			
			else if ( cmd == 1 ) {
				N = 1 ;
				Read() ;
			}
			else if ( cmd == 2 ) {
				Read() ;
				cout << "Number of G (goals):" ;
				cin >> N ;			
			} 

			FindG(N) ;
		} // while
	} // Run()
	
	void Take( char** themaze ) {
		
	    themaze = new char*[numRows];
	    
	    for (int i = 0; i < numRows; i++) {
	        themaze[i] = new char[numCols];
	    }
	    
		for (int i = 0; i < numRows; i++) {
	        for (int j = 0; j < numCols; j++) {
	            themaze[i][j] = maze[i][j];
	        }
	    }
	} // Take()
	
private:
    string textName ;
    char maze[30][30] ;
	int numRows = 0, numCols = 0 ;
	
	
}; // Maze{}

int main(int argc, char** argv) {

	char ch[30][30] ;
	Maze find ;
	find.Run() ;

	return 0;
}
