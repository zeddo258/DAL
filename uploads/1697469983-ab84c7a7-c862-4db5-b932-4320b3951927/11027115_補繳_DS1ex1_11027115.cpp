#include <iostream> //in out
#include <cstdlib>
#include <vector> // vector
#include <iomanip> // setw
#include <math.h> //sqrt
#include <fstream>
#include <string> 
#include <utility> // pair
#include <stack>

using namespace std ;

#define right 0 
#define down 1 
#define left 2
#define up 3 


class Maze{
	private :
		int x ;	// x軸 
		int y ;	// y軸 
		
		char** maze ;	// 二維陣列存地圖 [y][x]
		char** All_maze ;	// 二維陣列存地圖 [y][x]
		bool** walked ;
		vector<pair<int, int > > path ;
		vector<pair<int, int > > All_path ;
	
	public:
		
		bool openFile( string &fileName ) {
			fstream inFile ;
		
			do
			{
				cout << "Input a file number:" ;
				cin >> fileName ;
				//if( !fileName.compare("0") ) return false ;
				
				inFile.open( ("input" + fileName + ".txt").c_str(), fstream::in) ; // 開檔案 
				
				if(  inFile.is_open() ) break ; // 成功則跳出 
				else {
					cout << endl << "input" << fileName << ".txt does not exist!" << endl ;
					return false ;
				}
			} while( true ) ;
			
			inFile.close() ;
			
			return true ;
		
		}
		
		void loadMaze( string &fileName ) {
			path.clear() ;
			All_path.clear() ;
			fstream inFile ;
			inFile.open( ("input" + fileName + ".txt").c_str() ) ;
			
			inFile >> x ;	// 讀取X軸 
			inFile >> y ;	// 讀取Y軸 
			//cout << " X == " << x << endl ;
			//cout << " Y == " << y << endl ;		
					
			maze = (char**)malloc(y * sizeof(char*)) ; 	// 建立地圖大小 
			for (int k = 0; k < y; k++) {
        		maze[k] = (char*)malloc(x * sizeof(char));
    		}
    		
  			All_maze = (char**)malloc(y * sizeof(char*)) ; 	// 建立地圖大小 
			for (int k = 0; k < y; k++) {
        		All_maze[k] = (char*)malloc(x * sizeof(char));
    		}  
					
			walked = (bool**)malloc(y * sizeof(bool*)) ; 	// 建立地圖大小 
			for (int k = 0; k < y; k++) {
        		walked[k] = (bool*)malloc(x * sizeof(bool));
    		}

			for( int i = 0 ; i < y ; i++ ) {
				for ( int j = 0 ; j < x ; j++ ) {
					inFile >> maze[i][j] ;
					All_maze[i][j] = maze[i][j] ;
				}
			}
	
			inFile.close() ;
			
		}
		
		void printmaze() {
			for( int i = 0 ; i < y ; i++ ) {
				//cout << "print X = " << x << endl ; 
				for ( int j = 0 ; j < x ; j++ ) {
					cout << maze[i][j] ;
				}
				cout << endl ;
			}
		}
		
		void print_All_maze() {
			for( int i = 0 ; i < y ; i++ ) {
				//cout << "print X = " << x << endl ; 
				for ( int j = 0 ; j < x ; j++ ) {
					cout << All_maze[i][j] ;
				}
				cout << endl ;
			}
			cout << endl ;
		}
		
		bool xy_in_maze( int xx, int yy ) {
			if ( (xx >= 0 && xx < x ) && ( yy >= 0 && yy < y ) && ((maze[yy][xx] == 'E')||maze[yy][xx] == 'G') ) return true ; // 座標在地圖裡面
			return false ; 
		} 

		bool have_road( int xx, int yy ) {
			if ( xy_in_maze( xx, yy ) == true ) {
			 	if( (maze[yy][xx] == 'E' || maze[yy][xx] == 'G')  && walked[yy][xx] == false ){
					return true ; // 看有沒有障礙物 			 		
			 	}
				else {
					walked[yy][xx] == true ;	
					return false ;
				}
	
			}
			else return false ;
		}
				
		bool ttfind_goal( int x_now, int y_now, int way ) {
			
			
			if ( have_road(x_now, y_now) == false ) return false ; // 看此格有沒有路 
			else {
				path.push_back( {x_now, y_now } ) ; // 丟進路徑 
				All_path.push_back( {x_now, y_now } ) ;
				walked[y_now][x_now] = true ; // 本格標記為走過					
			}

			if( maze[y_now][x_now]  == 'G' ) { // 找到G點了 
				//cout << "found!!!!! ( " << x_now << " , " <<  y_now << " )" << endl ; 
				path.push_back( { x_now, y_now } ) ;	
				return true ; //找到Goal了 return true				
			}			
			
			//然後讓它走下去					
			if( way == right ) {
				x_now = x_now + 1 ; // 往右走 
				// 移動完後進遞迴 
				if( ttfind_goal( x_now, y_now, way ) == false ){
					way = down ; // 如果回傳是false 代表可能沒路了 則換方向 
					x_now = x_now  -1 ; // 並回到移動前 
				} else {
					//cout << "right ( " << x_now << " , " <<  y_now << " )" << endl ; 
					return true ;
				}
				 
			} 
				
			if( way == down ) {
				y_now = y_now + 1 ; // 往下走
				
				// 移動完後進遞迴 
				if( ttfind_goal( x_now, y_now, way ) == false ) {
					way = left ; // 如果回傳是false 代表可能沒路了 則換方向 
					y_now = y_now  -1 ;  // 並回到移動前 
				} else {
					//cout << "down ( " << x_now << " , " <<  y_now << " )" << endl ; 
					return true ;
				} 
				 
			}             
            
  			if( way == left ) {
				x_now = x_now - 1 ; // 往左走
				
				// 移動完後進遞迴 
				if( ttfind_goal( x_now, y_now, way ) == false ) {
					way = up ; // 如果回傳是false 代表可能沒路了 則換方向 
					x_now = x_now +1 ; // 並回到移動前 
				} else {
					//cout << "left ( " << x_now << " , " <<  y_now << " )" << endl ; 
					return true ;
				}
				 
			}             
          
			if( way == up ) {
				y_now = y_now - 1 ; // 往上走
				
				// 移動完後進遞迴 
				if( ttfind_goal( x_now, y_now, way ) == false ) {
				 	way = right ; // 如果回傳是false 代表可能沒路了 則換方向 
				 	y_now = y_now +1 ; // 並回到移動前 
				} else {
					//cout << "up ( " << x_now << " , " <<  y_now << " )" << endl ; 
					return true ;
				}
				 
			}             

			if( way == right ) {
				x_now = x_now + 1 ; // 往右走
				
				// 移動完後進遞迴 
				if( ttfind_goal( x_now, y_now, way ) == false ){
					way = down ; // 如果回傳是false 代表可能沒路了 則換方向 
					x_now = x_now  -1 ; // 並回到移動前 
				} else {
					//cout << "right ( " << x_now << " , " <<  y_now << " )" << endl ; 
					return true ;
				}
				 
			} 
			
			if( way == down ) {
				y_now = y_now + 1 ; // 往下走
				
				// 移動完後進遞迴 
				if( ttfind_goal( x_now, y_now, way ) == false ) {
					way = left ; // 如果回傳是false 代表可能沒路了 則換方向 
					y_now = y_now  -1 ;  // 並回到移動前 
				} else {
					//cout << "down ( " << x_now << " , " <<  y_now << " )" << endl ; 
					return true ;
				} 
				 
			}             

  			if( way == left ) {
				x_now = x_now - 1 ; // 往左走
				
				// 移動完後進遞迴 
				if( ttfind_goal( x_now, y_now, way ) == false ) {
					way = up ; // 如果回傳是false 代表可能沒路了 則換方向 
					x_now = x_now +1 ; // 並回到移動前 
				} else {
					//cout << "left ( " << x_now << " , " <<  y_now << " )" << endl ; 
					return true ;
				}
				 
			}             

			if( way == up ) {
				y_now = y_now - 1 ; // 往上走
				
				// 移動完後進遞迴 
				if( ttfind_goal( x_now, y_now, way ) == false ) {
				 	way = right ; // 如果回傳是false 代表可能沒路了 則換方向 
				 	y_now = y_now +1 ; // 並回到移動前 
				} else {
					//cout << "up ( " << x_now << " , " <<  y_now << " )" << endl ; 
					return true ;
				}
				 
			}             
			                   
			if( maze[y_now][x_now]  == 'G' ) { // 找到G點了 
				//cout << "found!!!!! ( " << x_now << " , " <<  y_now << " )" << endl ; 
				path.push_back( { x_now, y_now } ) ;	
				return true ; //找到Goal了 return true				
			}
			
        	//path.pop_back() ;
        	walked[y_now][x_now] = false ;
			return false ;	
		
		}
		
		void replaceAll_path() {

			for ( int i = 0 ; i < path.size(); i++ ) {
				if( maze[All_path[i].second][All_path[i].first] == 'G' ){
				}
				else All_maze[All_path[i].second][All_path[i].first] = 'V' ;
				
			}
		}
		
		void replace_path() {

			for ( int i = 0 ; i < path.size()-2; i++ ) {
				maze[path[i].second][path[i].first] = 'R' ;

			}
		}
		
};

int main(void) {
	
	int command ;
	Maze m1 ;
	string fileName ;
	
	do{
		cout << endl << "*** Path Finding ***" << endl ;
		cout << "* 0. Quit          *" << endl ;
		cout << "* 1. One goal      *" << endl ;
		cout << "* 2. More goals    *" << endl ;
		cout << "********************" << endl ;
		cout << "Input a command(0, 1, 2): "  ;
		cin >> command ;
		
		switch( command ){
			case 0 :
				break ;
			case 1 :
				
				if ( m1.openFile(fileName) ) {
					m1.loadMaze(fileName) ;
					if( m1.ttfind_goal( 0, 0, right ) ) {
						m1.replaceAll_path() ;					
						m1.print_All_maze() ;					
						m1.replace_path() ;						
						m1.printmaze() ;						
					}
					else {
						m1.replaceAll_path() ;					
						m1.print_All_maze() ;							
					}
						
				}

				

				break ;		/*	
			case 2:
				
				break ;*/ 
		}
		
	}while( command != 0 ) ;
} 
