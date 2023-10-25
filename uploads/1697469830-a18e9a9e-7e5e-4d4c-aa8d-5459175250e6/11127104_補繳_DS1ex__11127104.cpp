// 11127104 陳昱安 
#include <iostream>
#include <fstream>
#include <string>
using namespace std ;
typedef char char5050[50][50] ;

class Maze {
	
	private : 
		int mode = 1 ; // 單目標及多目標 
		char5050 map, mapOfG ; //  map是存迷宮的二維陣列, mapOfG是存成功的路徑 
		int row, column, direction = 1 ; // row是迷宮的列, column是迷宮的行, x、y是迷宮的哪個位置, direction 1 = 右, 2 = 下, 3 = 左, 4 = 上 
		int NumOfG = 1, NowOfG = 0 ; // NumOfG是需要幾個目標, NowOfG是現在有幾個目標 
		bool Stop = false ; // 是否停止繼續走迷宮
		//bool returnR = false ;

    public :
    	
	void setmode( int whatmode ) { // 設定mode
		mode = whatmode ;
	}

    void load() { // 讀資料 
    	ifstream input ; // 讀資料進來的物件 
    	string fileName ; // 檔案名稱的字串 
    	bool RightOrWrong = true ; // 輸入是否正確 
    	do // 重複執行到輸入正確 
		{
			RightOrWrong = true ; // 初始化是否輸入正確 
			cout << endl << "Input a file number (e.g.,101,102,103,104....):" ; // 輸入檔案名稱 
			cin >> fileName ;
			fileName = "input" + fileName + ".txt" ; // 把檔案名稱組成完整的字串 
			input.open( fileName.c_str() ) ; // 把檔案名稱字串轉成字元陣列, 並開啟檔案 
			if ( input.fail() ) { // 確認是否成功開啟檔案, 沒開成功就把RightOrWrong設成false表示找不到檔案 
				cout << endl << "File does not exist!" << endl ;
				RightOrWrong = false ;
			}
				
			if ( RightOrWrong ) { // 如果成功找到檔案 
				if ( mode == 2 ) { // 選擇多個目標 
					do { // 要求輸入目標數量, 並重複執行到得到範圍內的目標數量 
						cout << endl << "Number of G (goals):" ;
						cin >> NumOfG ;
						if ( NumOfG < 1 || NumOfG > 100 ) {
							cout << endl << "### The number must be in [1,100] ###" << endl ;
						}
						else {
							break ;  
						}
					} while(1) ;
				}
					
				input >> column >> row ; // 從檔案裡輸入迷宮的行、列 
				for (  int i = 0 ; i < row ; i ++ ) { // 從檔案裡輸入迷宮到map和mapOfG 
					for (  int j = 0 ; j < column ; j ++ ) {
						input >> map[i][j] ;
						mapOfG[i][j] = map[i][j] ;
					}
				}
				
				break ;
			}
		} while(1) ;
		
		input.close() ; // 關閉資料讀入串流 
	}  
	
	void findGoal() { // 執行findG這個函式 
		findG( 0, 0, false ) ;
	}
	
	void findG( int x, int y, bool returnR ) { // 走迷宮 

		map[y][x] = 'V' ; //經過的路徑設成V 
	
		if ( direction == 1 ) { // 方向為向右的情形 
			
			if ( map[y][x+1] == 'E' || map[y][x+1] == 'G' ) { // 判斷再向右是否可走 
				if ( map[y][x+1] == 'G' ) { // 判斷再向右是否為G 
					NowOfG ++ ; // 現有的目標數加一 
					returnR = true ;
					mapOfG[y][x] = 'R' ; // 設此位置為成功的路徑
					if ( NowOfG == NumOfG ) { // 判斷現有的目標數是否達到要求的目標數 
						Stop = true ; // 停止繼續走迷宮 
						return ; // 跳出此層遞迴 
					}
				
					findG( x+1, y, returnR ) ; // 還沒達到要求的目標數就再繼續向右 
					map[y][x+1] = 'G' ; // 因為上層遞迴會把G設為V,所以要設回G 
				}
				else {
					findG( x+1, y, returnR ) ; // 再向右為E的情況 
				}
			
				if ( Stop ) { // 上層遞迴是否已經停止繼續走迷宮 
					if ( mapOfG[y][x] != 'G' ) { // 判斷此位置是否為G 
						mapOfG[y][x] = 'R' ;  // 設此位置為成功的路徑
					}
				
					return ; // 回上層 
				}
			
			}
		
			direction = 2 ; // 向右走不下去換向下 
		
		
		}
	
		if ( direction == 2 ) { // 方向為向下的情形  
		
			if ( map[y+1][x] == 'E' || map[y+1][x] == 'G' ) { // 判斷再向下是否可走 
				if ( map[y+1][x] == 'G' ) { // 判斷再向下是否為G 
					NowOfG ++ ; // 現有的目標數加一 
					returnR = true ;
					mapOfG[y][x] = 'R' ; // 設此位置為成功的路徑 
					if ( NowOfG == NumOfG ) { // 判斷現有的目標數是否達到要求的目標數  
						Stop = true ; // 停止繼續走迷宮  
						return ; // 跳出此層遞迴  
					}
					findG( x, y+1, returnR ) ; // 還沒達到要求的目標數就再繼續向下 
					map[y+1][x] = 'G' ; // 因為上層遞迴會把G設為V,所以要設回G 
				}
				else {
					findG( x, y+1, returnR ) ; // 再向下為E的情況 
				}
			
				if ( Stop ) { // 上層遞迴是否已經停止繼續走迷宮  
					if ( mapOfG[y][x] != 'G' ) { // 判斷此位置是否為G  
						mapOfG[y][x] = 'R' ; // 設此位置為成功的路徑 
					}
					return ; // 回上層  
				}
			}
		
			direction = 3 ; // 向下走不下去換向左  
		
		}

  		 if ( direction == 3 ) { // 方向為向左的情形   
			
			if ( map[y][x-1] == 'E' || map[y][x-1] == 'G' ) { // 判斷再向左是否可走  
				if ( map[y][x-1] == 'G' ) { // 判斷再向左是否為G 
					NowOfG ++ ; // 現有的目標數加一  
					returnR = true ;
					mapOfG[y][x] = 'R' ; // 設此位置為成功的路徑
					if ( NowOfG == NumOfG ) { // 判斷現有的目標數是否達到要求的目標數   
						Stop = true ; // 停止繼續走迷宮     
						return ; // 跳出此層遞迴   
					}
					findG( x-1, y, returnR ) ; // 還沒達到要求的目標數就再繼續向左 
					map[y][x-1] = 'G' ; // 因為上層遞迴會把G設為V,所以要設回G 
				} 
				else {
					findG( x-1, y, returnR ) ; // 再向左為E的情況 
				}
				if ( Stop ) { // 上層遞迴是否已經停止繼續走迷宮 
					if ( mapOfG[y][x] != 'G' ) { // 判斷此位置是否為G   
						mapOfG[y][x] = 'R' ;  // 設此位置為成功的路徑 
					}
					return ; // 回上層
				}
			}
		
			direction = 4 ; // 向左走不下去換向上 
		
		}
	
		if ( direction == 4 ) { // 方向為向上的情形   
			
			if ( map[y-1][x] == 'E' || map[y-1][x] == 'G' ) { // 判斷再向上是否可走  
				if ( map[y-1][x] == 'G' ) { // 判斷再向上是否為G  
					NowOfG ++ ; // 現有的目標數加一   
					returnR = true ;
					mapOfG[y][x] = 'R' ; // 設此位置為成功的路徑
					if ( NowOfG == NumOfG ) { // 判斷現有的目標數是否達到要求的目標數   
						Stop = true ; // 停止繼續走迷宮 
						return ; // 跳出此層遞迴 
					}
					findG( x, y-1, returnR ) ; // 還沒達到要求的目標數就再繼續向上 
					map[y-1][x] = 'G' ; // 因為上層遞迴會把G設為V,所以要設回G
				} 
				else {
					findG( x, y-1, returnR ) ; // 再向上為E的情況 
				}
			
				if ( Stop ) { // 上層遞迴是否已經停止繼續走迷宮  
					if ( mapOfG[y][x] != 'G' ) { // 判斷此位置是否為G 
						mapOfG[y][x] = 'R' ; // 設此位置為成功的路徑  
					}
					return ; // 回上層
				}
			}
			
		    
			if ( map[y][x+1] == 'E' || map[y][x+1] == 'G' ) { // 因為已經走完右下左上一個循環, 所以再循環一次, 從右開始, 先判斷是否可向右 
				direction = 1 ; // 方向設成右 
				if ( map[y][x+1] == 'G' ) { // 判斷再向右是否為G 
					NowOfG ++ ; // 現有的目標數加一 
					returnR = true ;
					mapOfG[y][x] = 'R' ; // 設此位置為成功的路徑
					if ( NowOfG == NumOfG ) { // 判斷現有的目標數是否達到要求的目標數 
						Stop = true ; // 停止繼續走迷宮 
						return ; // 跳出此層遞迴 
					}
				
					findG( x+1, y, returnR ) ; // 還沒達到要求的目標數就再繼續向右 
					map[y][x+1] = 'G' ; // 因為上層遞迴會把G設為V,所以要設回G 
				}
				else {
					findG( x+1, y, returnR ) ; // 再向右為E的情況 
				}
				
				if ( Stop ) { // 上層遞迴是否已經停止繼續走迷宮 
					if ( mapOfG[y][x] != 'G' ) { // 判斷此位置是否為G  
						mapOfG[y][x] = 'R' ; // 設此位置為成功的路徑  
					}
	
					return ; // 回上層 
				}
			}
		
			else if ( map[y+1][x] == 'E' || map[y+1][x] == 'G' ) { // 判斷是否可向下 
				direction = 2 ; // 方向設成下 
				if ( map[y+1][x] == 'G' ) { // 判斷再向下是否為G 
					NowOfG ++ ; // 現有的目標數加一 
					returnR = true ;
					mapOfG[y][x] = 'R' ; // 設此位置為成功的路徑
					if ( NowOfG == NumOfG ) { // 判斷現有的目標數是否達到要求的目標數  
						Stop = true ; // 停止繼續走迷宮   
						return ; // 跳出此層遞迴  
					}
					findG( x, y+1, returnR ) ; // 還沒達到要求的目標數就再繼續向下 
					map[y+1][x] = 'G' ; // 因為上層遞迴會把G設為V,所以要設回G 
				}
				else {
					findG( x, y+1, returnR ) ; // 再向下為E的情況 
				}
				if ( Stop ) { // 上層遞迴是否已經停止繼續走迷宮 
					if ( mapOfG[y][x] != 'G' ) { // 判斷此位置是否為G 
						mapOfG[y][x] = 'R' ; // 設此位置為成功的路徑 
					}
	
					return ; // 回上層 
				}
			}
		
			else if ( map[y][x-1] == 'E' || map[y][x-1] == 'G' ) { // 判斷是否可向左 
				direction = 3 ; // 方向設成左 
				if ( map[y][x-1] == 'G' ) { // 判斷再向左是否為G 
					NowOfG ++ ; // 現有的目標數加一  
					returnR = true ;
					mapOfG[y][x] = 'R' ; // 設此位置為成功的路徑
					if ( NowOfG == NumOfG ) { // 判斷現有的目標數是否達到要求的目標數   
						Stop = true ; // 停止繼續走迷宮      
						return ; // 跳出此層遞迴   
					}
					findG( x-1, y, returnR ) ; // 還沒達到要求的目標數就再繼續向左  
					map[y][x-1] = 'G' ; // 因為上層遞迴會把G設為V,所以要設回G 
				} 
				else {
					findG( x-1, y, returnR ) ; // 再向左為E的情況 
				} 
				
				if ( Stop ) { // 上層遞迴是否已經停止繼續走迷宮 
					if ( mapOfG[y][x] != 'G' ) { // 判斷此位置是否為G 
						mapOfG[y][x] = 'R' ; // 設此位置為成功的路徑 
					}
	
					return ; // 回上層 
				}
			}
			
		}
		
		if ( returnR ) {
			if ( mapOfG[y][x] != 'G' ) { // 判斷此位置是否為G 
				mapOfG[y][x] = 'R' ; // 設此位置為成功的路徑 
			} 
		}
		//cout << "_---------------" ;
		return ; // 回上層 
	}
	
	void ClearMaze() { //初始化數值 
	    Stop = false ;
	    direction = 1 ; // 方向一開始先向右 
	    NowOfG = 0 ;
	    NumOfG = 1 ;
		for ( int i = 0 ; i < 50 ; i++ ) { // 清空迷宮及成功路徑 
			for( int j = 0 ; j < 50 ; j ++ ) {
				map[i][j] = '0' ;
				mapOfG[i][j] = '0' ;
			}
		}
	}
	
	void ShowMazeV() { // 輸出走過的路徑 
		for ( int i = 0 ; i < row ; i ++ ) { // 輸出走過的路徑圖 
			for ( int j = 0 ; j < column ; j ++ ) {
				cout << map[i][j] ;
			}
		
			cout << endl ;
		}
	} 
	
	void ShowMazeR() { // 輸出成功的路徑 
		cout << endl ;
		for ( int i = 0 ; i < row ; i ++ ) {
			for ( int j = 0 ; j < column ; j ++ ) {
				cout << mapOfG[i][j] ;
			}
	
			cout << endl ;
		}
	}
	
	bool IsSuccess() { // 回傳是否成功找到所有目標 
		return Stop ;
	}
} ;

int main() {
	int command = 0 ; // 使用者的輸入的變數 
	
	do // 重複執行直到使用者結束執行 
	{
		Maze aMaze ;
		// string fileName ; // 檔案名稱的字串 
		
		cout << endl << "*** Path Finding ***" ; // 使用者介面 
		cout << endl << "* 0.Quit           *" ;
		cout << endl << "* 1.One goal       *" ;
		cout << endl << "* 2.More goal      *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command( 0, 1, 2 ):" ;
		cin >> command ; // 輸入動作 
		
		aMaze.setmode( command ) ; // 設定mode 
			
		if ( command == 1 || command == 2 ) { // 執行動作為1或2的情況 
			
			aMaze.load() ; // 讀取資料 
			
			aMaze.findGoal() ; // 走迷宮 

			aMaze.ShowMazeV() ; // 輸出走過的路徑 
			if ( aMaze.IsSuccess() ) { // 判斷是否有找到所有目標 
				aMaze.ShowMazeR() ; // 輸出成功的路徑 
			}
			
			aMaze.ClearMaze() ; // 初始化資料 
			
			
		}
		else if ( command == 0 ) {
			break ; // 停止執行 
		}
		else {
			cout << endl << "Command does not exist!" << endl ;	// 輸出此操作不存在 
		}
	
	} while(1) ;
}

