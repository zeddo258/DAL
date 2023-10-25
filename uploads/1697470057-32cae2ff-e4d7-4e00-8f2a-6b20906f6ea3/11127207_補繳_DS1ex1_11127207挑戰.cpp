// 11127207 楊竣傑

#include <iostream>
#include <fstream> // 標頭檔 
#include <string>
#include <list>  
#include <utility> // 包含 std :: pair 

using namespace std ;

class Mazechart {
	ifstream in ;
private :
	int reachGoal ; // 看是不是達到需要的目標數 
	int line ; // 當前這一行 
	int row ; // 當前這一列 
	int i ; // 陣列行的大小 
	int j ; // 陣列列的大小 
	int number ; // 讀取數字 
	char chart[100][100] ; //主要使用的陣列 
	std :: list <std :: pair< int, int > > thePath ; //存取所走過的每一格 除了GOAL 
	std :: list <std :: pair< int, int > > nowPath ; // 紀錄回頭看的格數 
	std :: list <std :: pair< int, int > > printPath ; // 要印的新最短路徑 
	std :: list <std :: pair< int, int > > dPath ; // 紀錄回頭看的格子延伸出的格數
	std :: list <std :: pair< int, int > > sPath ; // 紀錄岔路 
	int lineGoal[100] ; // 紀錄曾走過的GOAL的行 
	int rowGoal[100] ; // 紀錄曾走過的GOAL的列 
	int saveLine[100] ; //紀錄被刪除且周圍有gaol的的行跟列 
	int saveRow[100] ;
	int saveNumber ;
	bool havepath ;
	bool needpath ;
	
	int needLine[100] ; // 儲存路徑用 
	int needRow[100] ;
	int need ;
	
	 

	bool haveShorest ; // 目前無用處 時間來不及改良   
	int preLength ; // 紀錄最初到目標的長度 
	int nowLength ; // 紀錄目前長度 
	int goalLine ; // 紀錄G的位置 
	int goalRow ;
	int shortlength ; // 要回傳的最短路徑長 
	bool touchGoal ; // 目前無用處時間不足改良 
	
 	
	int GetNumber () {
		in >> number ;   //獲取記事本裡的數字 
		return number ;
	} // GetNumber()	
			
public :
	Mazechart() {  // 把class的需要初始化的變數初始化 
		touchGoal = false ;
		shortlength = 0 ;
		nowLength = 0 ;
		preLength = 0 ;
		haveShorest = false ;

		need = 0 ;
		needpath = false ;
		havepath = false ;
		saveNumber = 0 ; 
		reachGoal = 0 ;
		line = 0 ;
		row = 0 ;
	} // Mazechart 
	
	char Maze ;	
		
	bool Correctfile ( string i ) { //檢查資料的正確性 
		string a = "input" + i + ".txt" ;
		in.open( a.c_str() ) ;
		if ( in.fail() ) {  // 如果沒有這個資料 
			cout << endl << "input" << i << ".txt does not exist" << endl ;
			in.close() ; // 釋放 
			return false ;
		} // if
		else
			return true ;
		
	} // Correctfile
	
	void Read() { // 讀資料 
		i = GetNumber() ;
		j = GetNumber() ;
		
		for ( int row = 0 ; row < j ; row++ ) {
			for ( int line = 0 ; line < i ; line++ ) {
				in >> Maze ;
				chart[line][row] = Maze ;
			} // for
			
		} // for
		
	} // Read()	
	
	bool Move( int x ) { // 老鼠移動依據並記錄自己移動格子 && 上下左右程式碼皆相同只有順序是右下左上
	 	int time = 0 ;
	 	bool haveGoal = false ;
	 	if ( line == 0 && row == 0 ) {
	 		thePath.push_back(std::make_pair( line, row ) ) ;
	 		chart[0][0] = 'V' ;
	 	} // if
	 		
		while( time <= 4  ) { // 只要上下左右四個方向都看過且沒time達到4就跳出迴圈  
			while( line < i  ) { // 移動且不斷檢查是否有可以過去的路徑  這是往右邊走的 
				if ( chart[line + 1][row] == 'O' || chart[line + 1][row] == 'V' || line + 1 == i ) {
					time = time + 1 ;		// 如果是走過的路或有障礙物或是邊界time會+1 
					break ;					// time只要大於四次就代表是死路 
				} // if
				
				else if ( chart[line + 1][row] == 'E' ) { // 如果是可以通過的路就記錄起來並變成V 
					time = 0 ;
					line++ ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
					havepath = true ;
				} // else
				
				else if ( chart[line + 1][row] == 'G' ) { // 如果找到goal的判斷 
					if ( reachGoal > 0 ) {   
						if ( Detect( line + 1, row ) != true ) {  // 已經找到一個以上的goal 
							line++ ;
							time = 0 ;                         
							lineGoal[reachGoal] = line ;    // 將goal座標記錄在特定陣列中 以免遺失 
							rowGoal[reachGoal] = row ;		 
							reachGoal = reachGoal + 1 ;  // 這代表目前已經找到的goal數量 
						} // if
						else {
							time = time + 1 ; // 代表這個goal已經走過 
							break ;
						} // else
					}
					else {  // 還沒遇到任何一個goal的情況 
						line++ ;
						time = 0 ;
						TurnRoute() ;
						lineGoal[reachGoal] = line ;  // 將goal座標記錄在特定陣列中 以免遺失 
						rowGoal[reachGoal] = row ;
						reachGoal = reachGoal + 1 ;
					} //esle
					
					if ( reachGoal == x ) {  // 數量達標可以返回主程式 
						return true ;
					} // if
					
				} // else if
				
			} // while
			
			
			while( row < j ) {  // 往下走  說明同往右程式  
				if ( chart[line][row + 1] == 'O' || chart[line][row + 1] == 'V' || row + 1 == j ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[line][row + 1] == 'E' ) {
					time = 0 ;
					row++ ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
					havepath = true ;
				} // else if
				else if ( chart[line][row + 1] == 'G' ) {
					if ( reachGoal > 0 ) {
						if ( Detect( line, row + 1 ) != true ) {  // 已經找到一個以上的goal 
							row++ ;
							time = 0 ;
							lineGoal[reachGoal] = line ;
							rowGoal[reachGoal] = row ;
							reachGoal = reachGoal + 1 ;
						} // if
						else {
							time = time + 1 ;
							break ;
						}
					}
					
					else if ( reachGoal == 0 ){
						row++ ;
						time = 0 ;
						
						TurnRoute() ;
						
						lineGoal[reachGoal] = line ;
						rowGoal[reachGoal] = row ;
						reachGoal = reachGoal + 1 ;
					} //esle
					
						
					if ( reachGoal == x ) {
						return true ;
					}
					
				} // else if
				
			} // while
			
			
			while( line > 0 ) { // move left  說明同往右程式 
				if ( chart[line - 1][row] == 'O' || chart[line - 1][row] == 'V' ) {
					time = time + 1 ;
					break ;
				}
				else if ( chart[line - 1][row] == 'E' ) {
					time = 0 ;
					line-- ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;	
					havepath = true ;
				}
				else if ( chart[line - 1][row] == 'G' ) {
					if ( reachGoal > 0 ) {
						if ( Detect( line - 1, row ) != true ) {  // 已經找到一個以上的goal
							needpath = false ;
							line-- ;
							time = 0 ;
							TurnRoute() ;
							lineGoal[reachGoal] = line ;
							rowGoal[reachGoal] = row ;
							reachGoal = reachGoal + 1 ;
						
						} // if
						else {
							time = time + 1 ;
							break ;
						} // else
					}
					else {
						line-- ;
						time = 0 ;
						lineGoal[reachGoal] = line ;
						rowGoal[reachGoal] = row ;
						reachGoal = reachGoal + 1 ;
					} //esle
						
					if ( reachGoal == x ) {
						return true ;
					}
				} // else if
				
			} // while
			
			
			while( row > 0 ) { // move up 說明同往右程式  
				
				if ( chart[line][row - 1] == 'O' || chart[line][row - 1] == 'V' ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[line][row - 1] == 'E' ) {
					row-- ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
					havepath = true ;	
					time = 0 ;
				} // else if 
				
				else if ( chart[line][row - 1] == 'G' ) {
					if ( reachGoal > 0 ) {
						if ( Detect( line, row - 1) != true ) {  // 已經找到一個以上的goal 
							row-- ;
							time = 0 ;
							lineGoal[reachGoal] = line ;
							rowGoal[reachGoal] = row ;
							reachGoal = reachGoal + 1 ;
							
						} // if
						else {
							time = time + 1 ;
							break ;
						} // else 
					}
					else {
						row-- ;
						TurnRoute() ;
						time = 0 ;
						lineGoal[reachGoal] = line ;
						rowGoal[reachGoal] = row ;
						reachGoal = reachGoal + 1 ;
					} //esle
					
						
					if ( reachGoal == x ) {
						return true ;
					}
				} // else if
				
			} // while
			
			
		} // while
		
		if ( time >= 4 ) {
			havepath = false ;
			return false ;
		}
		
	} // Move
	
	bool Move3() {
	 	int time = 0 ;
	 	bool haveGoal = false ;
	 	if ( line == 0 && row == 0 ) {
	 		thePath.push_back(std::make_pair( line, row ) ) ;
	 		chart[0][0] = 'V' ;
	 	} // if
	 		
		while( time <= 4  ) { // 只要上下左右四個方向都看過且沒time達到4就跳出迴圈  
			while( line < i  ) { // 移動且不斷檢查是否有可以過去的路徑  這是往右邊走的 
				if ( chart[line + 1][row] == 'O' || chart[line + 1][row] == 'V' || line + 1 == i ) {
					time = time + 1 ;		// 如果是走過的路或有障礙物或是邊界time會+1 
					break ;					// time只要大於四次就代表是死路 
				} // if
				
				else if ( chart[line + 1][row] == 'E' ) { // 如果是可以通過的路就記錄起來並變成V 
					time = 0 ;
					line++ ;
					preLength++ ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
				} // else
				
				else if ( chart[line + 1][row] == 'G' ) { // 如果找到goal的判斷 
					goalLine = line ;
					goalRow = row ;
					preLength++ ;
					line++ ;
					time = 0 ;
					lineGoal[reachGoal] = line ;  // 將goal座標記錄在特定陣列中 以免遺失 
					rowGoal[reachGoal] = row ;
					reachGoal = reachGoal + 1 ;
					return true ;

					
				} // else if
				
			} // while
			
			
			while( row < j ) {  // 往下走  說明同往右程式  
				if ( chart[line][row + 1] == 'O' || chart[line][row + 1] == 'V' || row + 1 == j ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[line][row + 1] == 'E' ) {
					preLength++ ;
					time = 0 ;
					row++ ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
				} // else if
				else if ( chart[line][row + 1] == 'G' ) {
					goalLine = line ;
					goalRow = row ;
					preLength++ ;
					row++ ;
					time = 0 ;
					lineGoal[reachGoal] = line ;
					rowGoal[reachGoal] = row ;
					reachGoal = reachGoal + 1 ;
					return true ;
					
				} // else if
				
			} // while
			
			
			while( line > 0 ) { // move left  說明同往右程式 
				if ( chart[line - 1][row] == 'O' || chart[line - 1][row] == 'V' ) {
					time = time + 1 ;
					break ;
				}
				else if ( chart[line - 1][row] == 'E' ) {
					preLength++ ;
					time = 0 ;
					line-- ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;	
				}
				else if ( chart[line - 1][row] == 'G' ) {
					goalLine = line ;
					goalRow = row ;
					preLength++ ;
					line-- ;
					time = 0 ;
					lineGoal[reachGoal] = line ;
					rowGoal[reachGoal] = row ;
					reachGoal = reachGoal + 1 ;
					return true ;
						
				} // else if
				
			} // while
			
			
			while( row > 0 ) { // move up 說明同往右程式  
				
				if ( chart[line][row - 1] == 'O' || chart[line][row - 1] == 'V' ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[line][row - 1] == 'E' ) {
					row-- ;
					preLength++ ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
					havepath = true ;	
					time = 0 ;
				} // else if 
				
				else if ( chart[line][row - 1] == 'G' ) {
					goalLine = line ;
					goalRow = row ;
					row-- ;
					preLength++ ;
					time = 0 ;
					lineGoal[reachGoal] = line ;
					rowGoal[reachGoal] = row ;
					reachGoal = reachGoal + 1 ;
					if ( nowLength < preLength )
						return true ;
				} // else if
				
			} // while
			
			
		} // while
		
		if ( time >= 4 ) {
			
			return false ;
			
		}	
		
	} // Move3

	
	bool Check() { // 往前找是否還有路徑可以走 
        std::pair<int, int> lastPair = thePath.back();
        line = lastPair.first ;
        row = lastPair.second ;  // 分別將值存儲在變數 i 和 j 中
        
        if ( DetectGoal( line, row ) == true ) { 	// 假設退回去的周圍有goal
			if ( DetectRoute( line, row ) == true ) { // 且此路徑周圍有路或有曾經走過的路(V)可走
				saveLine[saveNumber] = line ;     	 // 將此座標紀錄以免被刪除 
        		saveRow[saveNumber] = row ;
        		saveNumber++ ;
        	} // if
    	} // if
    	
    	thePath.pop_back();
		
		if ( thePath.size() > 0 )  // Return false代表還有路徑可以檢查是否還可以走 
			return false ;
		else 
			return true ;		
	} // check
	
	bool Check1() { // 往前找是否還有路徑可以走 
        std::pair<int, int> lastPair = thePath.back();
        line = lastPair.first ;
        row = lastPair.second ;  // 分別將值存儲在變數 i 和 j 中
        
        if ( DetectGoal( line, row ) == true ) { 	// 假設退回去的周圍有goal
			if ( DetectRoute( line, row ) == true ) { // 且此路徑周圍有路或有曾經走過的路(V)可走
				saveLine[saveNumber] = line ;     	 // 將此座標紀錄以免被刪除 
        		saveRow[saveNumber] = row ;
        		saveNumber++ ;
        	} // if
    	} // if
    	else {
    		preLength-- ;
    		thePath.pop_back();
		}
		
		
		
		if ( thePath.size() > 0 )  // Return false代表還有路徑可以檢查是否還可以走 
			return false ;
		else 
			return true ;		
	} // check
	

	
	bool Detect( int p, int f ) {  // 檢查是不是走到曾經通過的goal 
		int g = 0 ;
		int h = 0 ;
		int x = 0 ;
		while ( x < reachGoal ) {
			g = lineGoal[x] ;
			h = rowGoal[x] ;
			if ( p == g && f == h )
				return true ;  // 重複了 
			x++ ;
		} // for
		
		return false ;
		
	} // Detcet
	
	bool DetectGoal ( int i, int j ) { // 檢查上下左右是否有GOAL 
		if ( chart[i + 1][j] == 'G' ) {
			return true ;
		} // if
		
		else if ( chart[i][j + 1] == 'G' ) {
			return true ;
		} // else if
		
		else if ( chart[i - 1][j] == 'G' ) {
			return true ;
		} // else if
		
		else if ( chart[i][j - 1] == 'G' ) {
			return true ;
		} // else if
		
		else {  								 // 如果都沒有代表是死路 
			return false ;       
		}
		
	} // DetectGoal.
	
	bool DetectRoute ( int line, int row ) { // 檢查上下左右是否為死路 
		if ( line + 1 > i && chart[i][j + 1] == 'O' && chart[i][j - 1] == 'O'  ) { // 右邊遇到牆壁 且上下皆無路可走 
			return false ;
		} // if
		
		else if ( line - 1 < 0  && chart[i][j + 1] == 'O' && chart[i][j - 1] == 'O'  ) { // 左邊遇到牆壁 且上下皆無路可走
			return false ;
		} // else if
		
		else if ( row + 1 > j && chart[i + 1][j] == 'O' && chart[i - 1][j] == 'O'  ) { // 下面遇到牆壁 且左右皆無路可走 
			return false ;
		} // else if
		
		else if ( row - 1 < 0 && chart[i + 1][j] == 'O' && chart[i - 1][j] == 'O'  ) { // 上面遇到牆壁 且左右皆無路可走 
			return false ;
		} // else if
		
		return true ;       
		
	} // DetectGoal.
	 
	
	void Translate() {  // 將必要路徑轉乘R    PS.可能會有被誤刪的 會用Debug()等程式補回 
	    std::pair<int, int> lastPair = thePath.back();
		line = lastPair.first ;
        row = lastPair.second ;
        chart[line][row] = 'R' ;

	} // Translate
	
	void Trans() {
		for ( int row = 0 ; row < j ; row++ ) {  // 多餘路徑轉變成E 
			for ( int line = 0 ; line < i ; line ++ ) {
				if ( chart[line][row] == 'V' )
					chart[line][row] = 'E' ;	
			} // for
		}
	} // Trans
	
	void Fill() {  
		for ( int row = 0 ; row < j ; row++ ) {  // 避免轉角的R被誤刪 
			for ( int line = 0 ; line < i ; line ++ ) {
				if (chart[line][row] == 'V' ) { 
					if ( chart[line + 1][row] == 'R' && chart[line][row + 1] == 'R' ) // 右下 
						chart[line][row] = 'R' ;
					else if ( chart[line + 1][row] == 'R' && chart[line][row - 1] == 'R' ) // 右上 
						chart[line][row] = 'R' ;	
					else if ( chart[line - 1][row] == 'R' && chart[line][row + 1] == 'R' ) // 左下
				 		chart[line][row] = 'R' ;
					else if ( chart[line - 1][row] == 'R' && chart[line][row - 1] == 'R' ) // 左上 
				 		chart[line][row] = 'R' ;
				}				 	
			} // for
		}	
		
	}
	
	bool Cut() { // 刪除多餘的點 
		thePath.pop_back();
		if ( thePath.size() > 0 )
			return false ;
		else 
			return true ;
	} // Cut
	
	void Debug() {  // 把被誤刪掉的必要路徑補回來     ps補丁 
		int deLine = 0 ;
		int deRow = 0 ;
		for ( int x = 0 ; x < saveNumber ; x++ ) {
			deLine = saveLine[x] ;
			deRow = saveRow[x] ;
			chart[deLine][deRow] = 'R' ;
			
		} // for
		
	} // Debug
	
	void Debug2() { // 印出保留的必要路徑 
		int deLine = 0 ;
		int deRow = 0 ;		
		for ( int x = 0 ; x < need ; x++ ) {
			deLine = needLine[x] ;
			deRow = needRow[x] ;
			chart[deLine][deRow] = 'R' ;
			
		} // for	
	}
	
	void Print() { // 印出圖表 
		for ( int row = 0 ; row < j ; row++ ) {
			for ( int line = 0 ; line < i ; line ++ ) 
				cout << chart[line][row] ;
			
			cout << endl ;
			
		} // for
		
	} // Print
	
	void TurnRoute() { // 保留看到G以後回頭看的路徑 
		std::list < std::pair < int, int > > :: iterator it;
		for ( it = thePath.begin() ; it != thePath.end() ; it++ ) {
			needLine[need] = it -> first ;
			needRow[need] = it -> second ;
			need = need + 1 ;	
    	}
		
	}
	
	bool Haves() {  // 看有沒有岔路 
		if (  chart[line + 1][row] == 'E' && chart[line - 1][row] == 'E' ) { // 右邊遇到牆壁 且上下皆無路可走 
			return true ;
		} // if
		
		else if ( chart[line][row - 1] == 'E' && chart[line][row + 1] == 'E'  ) { // 左邊遇到牆壁 且上下皆無路可走
			return true ;
		} // else if
		
		return false ;    
		
	}	
	

	bool Mod() { // 找有沒有更短路徑 
	 	int time = 0 ; 
	 	int x = 0 ;
	 	std::list < std::pair < int, int > > :: iterator it;
		while( time <= 4 && nowPath.size() + dPath.size() < preLength ) { // 看是不是死路而且不能比原本找到的路徑大 
			while( line < i && nowPath.size() + dPath.size() < preLength ) { // 移動且不斷檢查是否有可以過去的路徑  這是往右邊走的 
				if ( chart[line + 1][row] == 'O' || line + 1 == i ||  chart[line + 1][row] == 'V' ) {
					time = time + 1 ;		// 如果是走過的路或有障礙物或是邊界time會+1 
					break ;					// time只要大於四次就代表是死路 
				} // if
				
				
				else if ( chart[line + 1][row] == 'E' && nowPath.size() + dPath.size() < preLength ) { // 如果是可以通過的路就記錄起來並變成V 
					time = 0 ;
					line++ ;
					dPath.push_back(std::make_pair( line, row ) ) ; //把走過的點暫存在list中 
					chart[line][row] = 'V' ; 
					if ( Haves() == true ) { //看有沒有岔路 
						Mod2( line - 1, row ) ;
					}
						
					if ( reach() == true && nowPath.size() + dPath.size() < preLength && touchGoal != true )
						return true ; // 如果找到的路徑有被走過且這是可以相連的最短路徑就回傳 

				} // else
				else if ( chart[line + 1][row] == 'G' ) {
					time = 0 ; //確認找到的路就是不是重複而且不能比原來大 
					if ( nowPath.size() + dPath.size() < preLength && Detect( line + 1, row) != true ) {
						shortlength = nowPath.size() + dPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else 
						return false ;
				}
			} // while
			
			
			while( row < j && nowPath.size() + dPath.size() < preLength ) {  // 往下走  說明同往右程式  
				if ( chart[line][row + 1] == 'O' || row + 1 == j ||  chart[line][row + 1] == 'V' ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[line][row + 1] == 'E' && nowPath.size() + dPath.size() < preLength ) {
					time = 0 ;
					row++ ;
					x++ ;
					chart[line][row] = 'V' ;
					dPath.push_back(std::make_pair( line, row ) ) ;
					if ( Haves() == true ) {
						Mod2( line + 1, row ) ;
					}
					if ( reach() == true && nowPath.size() + dPath.size() < preLength && touchGoal != true )
						return true ;
				} // else if
				else if ( chart[line][row+ 1] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + dPath.size() < preLength && Detect( line, row + 1) != true ) {
						shortlength = nowPath.size() + dPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else {
						return false ;
					}
				}
			} // while
			
			
			while( line > 0 && nowPath.size() + dPath.size() < preLength ) { // move left  說明同往右程式 
				if ( chart[line - 1][row] == 'O' ||  chart[line - 1][row] == 'V' ) {
					time = time + 1 ;
					break ;
				}
				else if ( chart[line - 1][row] == 'E' && nowPath.size() + dPath.size() < preLength ) {
					time = 0 ;
					line-- ;
					x++ ;
					dPath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
					if ( Haves() == true ) {
						Mod2( line + 1, row ) ;
					}
					if ( reach() == true && nowPath.size() + dPath.size() < preLength && touchGoal != true && Detect( line - 1, row) != true )
						return true ;				 
					
				}
				else if ( chart[line - 1][row] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + dPath.size() < preLength ) {
						shortlength = nowPath.size() + dPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else 
						return false ;
				}
			} // while
			
			
			while( row > 0 && nowPath.size() + dPath.size() < preLength ) { // move up 說明同往右程式  
				
				if ( chart[line][row - 1] == 'O' ||  chart[line][row - 1] == 'V' ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[line][row - 1] == 'E' && nowPath.size() + dPath.size() < preLength ) {
					row-- ;
					x++ ;
					dPath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;	
					time = 0 ;
					if ( Haves() == true ) {
						Mod2( line - 1, row ) ;
					}
					if ( reach() == true && nowPath.size() + dPath.size() < preLength && touchGoal != true && Detect( line, row - 1) != true)
						return true ;
				} // else if 
				else if ( chart[line + 1][row] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + dPath.size() < preLength ) {
						shortlength = nowPath.size() + dPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else 
						return false ;
				}
			} // while
			
			
		} // while
		
		
		if ( time >= 4 || nowPath.size() + dPath.size() >= preLength ) {
    		dPath.clear() ; // 如果沒有更短路徑把原本暫存的資料清空 
			return false ;		
		}		
		
	} // Mod
	
	bool Mod2( int l, int r ) { // 在岔路找有沒有更短路徑 
	 	int time = 0 ; 
	 	int x = 0 ;
	 	std::list < std::pair < int, int > > :: iterator it;
	 	sPath.push_back(std::make_pair( l, r ) ) ;
	 	chart[l][r] = 'V' ;
		while( time <= 4 && nowPath.size() + sPath.size() + dPath.size() < preLength ) { // 只要上下左右四個方向都看過且沒time達到4就跳出迴圈  
			while( l < i && nowPath.size() + sPath.size() + dPath.size() < preLength ) { // 移動且不斷檢查是否有可以過去的路徑  這是往右邊走的 
				if ( chart[l + 1][r] == 'O' || l + 1 == i ||  chart[l + 1][r] == 'V' ) {
					time = time + 1 ;		// 如果是走過的路或有障礙物或是邊界time會+1 
					break ;					// time只要大於四次就代表是死路 
				} // if
				
				
				else if ( chart[l + 1][r] == 'E' && nowPath.size() + sPath.size() + dPath.size() < preLength ) { // 如果是可以通過的路就記錄起來並變成V 
					time = 0 ;
					l++ ;
					sPath.push_back(std::make_pair( l, r ) ) ;
					chart[l][r] = 'V' ; 	
					if ( reach() == true && nowPath.size() + sPath.size() + dPath.size() < preLength && touchGoal != true )
						return true ;

				} // else
				else if ( chart[l + 1][r] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + sPath.size() + dPath.size() < preLength && Detect( l + 1, r) != true ) {
						shortlength = nowPath.size() + sPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else 
						return false ;
				}
			} // while
			
			
			while( r < j && nowPath.size() + sPath.size() + dPath.size() < preLength ) {  // 往下走  說明同往右程式  
				if ( chart[l][r + 1] == 'O' || r + 1 == j ||  chart[l][r + 1] == 'V' ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[l][r + 1] == 'E' && nowPath.size() + dPath.size() + sPath.size() < preLength ) {
					time = 0 ;
					r++ ;
					chart[l][r] = 'V' ;
					sPath.push_back(std::make_pair( l, r ) ) ;
					if ( reach() == true && nowPath.size() + dPath.size() < preLength && touchGoal != true )
						return true ;
				} // else if
				else if ( chart[l][r+ 1] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + dPath.size() + sPath.size() < preLength && Detect( l, r + 1) != true ) {
						shortlength = nowPath.size() + dPath.size() + sPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else {
						return false ;
					}
				}
			} // while
			
			
			while( l > 0 && nowPath.size() + dPath.size() + sPath.size() < preLength ) { // move left  說明同往右程式 
				if ( chart[l - 1][r] == 'O' ||  chart[l - 1][r] == 'V' ) {
					time = time + 1 ;
					break ;
				}
				else if ( chart[l - 1][r] == 'E' && nowPath.size() + dPath.size() + sPath.size() < preLength ) {
					time = 0 ;
					l-- ;

					sPath.push_back(std::make_pair( l, r ) ) ;
					chart[l][r] = 'V' ;

					if ( reach() == true && nowPath.size() + dPath.size() + sPath.size() < preLength && touchGoal != true && Detect( l - 1, r) != true )
						return true ;				 
					
				}
				else if ( chart[l - 1][r] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + dPath.size() + sPath.size() < preLength ) {
						shortlength = nowPath.size() + dPath.size() + sPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else 
						return false ;
				}
			} // while
			
			
			while( r > 0 && nowPath.size() + dPath.size() + sPath.size() < preLength ) { // move up 說明同往右程式  
				
				if ( chart[l][r - 1] == 'O' ||  chart[l][r - 1] == 'V' ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[l][r - 1] == 'E' && nowPath.size() + dPath.size() + sPath.size() < preLength ) {
					r-- ;
					sPath.push_back(std::make_pair( l, r ) ) ;
					chart[line][row] = 'V' ;	
					time = 0 ;
					if ( reach() == true && nowPath.size() + dPath.size() + sPath.size() < preLength && touchGoal != true && Detect( l, r - 1) != true)
						return true ;
				} // else if 
				else if ( chart[l + 1][r] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + dPath.size() + sPath.size() < preLength ) {
						shortlength = nowPath.size() + dPath.size() + sPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else 
						return false ;
				}
			} // while
			
			
		} // while
		
		
		if ( time >= 4 || nowPath.size() + dPath.size() + sPath.size() >= preLength ) {
    		sPath.clear() ;
			return false ;		
		}		
		
	} // Mod

	
	bool findShortest() { // 找最短路徑 沒有就回傳錯誤 
		std::list < std::pair < int, int > > :: iterator it;
		bool x = false ;
		for ( it = thePath.begin() ; it != thePath.end() ; it++ ) {
			line = it -> first ;
			row = it -> second ;
			nowPath.push_back(std::make_pair( line, row ) ) ;
			if ( Mod()== true ) { 
				x = true ; 
				Copy() ;
			}
			 
    	}	
		
		if ( x == true ) { 
			return true ;
		}
		
		shortlength = thePath.size() + 1 ;
		return false ;
		
	
	}
	 
	
	void Copy() { // 把找到的最短路徑存取在這個list中 
		std::list < std::pair < int, int > > :: iterator it;
		bool x = false ;
		for ( it = nowPath.begin() ; it != nowPath.end() ; it++ ) {
			line = it -> first ;
			row = it -> second ;
			printPath.push_back(std::make_pair( line, row ) ) ;
		}
		for ( it = dPath.begin() ; it != dPath.end() ; it++ ) {
			line = it -> first ;
			row = it -> second ;
			printPath.push_back(std::make_pair( line, row ) ) ;
		}
		
		if ( touchGoal != true ) // 如果這個最短路徑有通過已走過的路徑就加進去 
			printPath.push_back(std::make_pair( goalLine, goalRow ) ) ;

	}
	
	bool reach() { // 最短路徑有通過已走過的路徑 長度加上該路徑以及終點 
		if ( line + 1 == goalLine && row == goalRow ) {
			shortlength = nowPath.size() + dPath.size() + 2 ;
			return true ;
		}
		else if ( line - 1 == goalLine && row == goalRow ) {
			shortlength = nowPath.size() + dPath.size() + 2 ;
			return true ;
		}
		else if ( line == goalLine && row + 1 == goalRow ) {
			shortlength = nowPath.size() + dPath.size() + 2 ;
			return true ;
		}
		else if ( line == goalLine && row - 1 == goalRow ) {
			shortlength = nowPath.size() + dPath.size() + 2 ;
			return true ;
		}
			
		return false ;
	}
	
	void Turnshort() { // 把最短路徑轉變到圖上 
		std::list < std::pair < int, int > > :: iterator it;
		int l = 0 ;
		int r = 0 ;
		for ( it = printPath.begin() ; it != printPath.end() ; it++ ) {
			l = it -> first ;
			r = it -> second ;
			chart[l][r] = 'R' ;
		}
		
	}
	void noShortPath() { // 沒有最短路徑 直接印出原本路徑 
		std::list < std::pair < int, int > > :: iterator it;
		int l = 0 ;
		int r = 0 ;
		for ( it = thePath.begin() ; it != thePath.end() ; it++ ) {
			l = it -> first ;
			r = it -> second ;
			chart[l][r] = 'R' ;
		}		
		
	}
	
	int GetLength() { // 回傳長度 
		return shortlength ;	
	}
			
} ;	


int main() {
	int x = 0 ;
	do {
		Mazechart aMaze ;  // 建構子 
		string fileName ;   // 檔案名 
		int command = 0 ;  // 指令 
		
		cout << endl << "*** Path Finding ***" ;
		cout << endl << "*0. Quit           *" ;   // 使用者所看到的介面 
		cout << endl << "*1. One goal       *" ;
		cout << endl << "*2. More goals     *" ;
		cout << endl << "*3. Shortest path  *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2, 3 ): " ;
		cin >> command ;
		cout << endl ;
		
		
		if ( command == 1 || command == 2 || command == 3 ) {  // 如果輸入指令1跟2 
            cout << "Input a file number(ex.201, 202,... ) : "  ;
            string fileNumber ;
            cin >> fileNumber ;  // 接收檔案名稱 
			bool findGoal = false ;
			bool end = false ;      
			bool success = aMaze.Correctfile( fileNumber ) ; //看看是否有這個檔案 
			
			if ( success == true ) {
				aMaze.Read() ; // 讀入記事本中的資料 

				if ( command == 1 ) {
					while ( findGoal != true && end != true ) { // 只要找到路徑或沒有其他路可以再走就跳出迴圈 
						findGoal = aMaze.Move( 1 ) ;  
						if ( findGoal != true ) { 
							end = aMaze.Check() ;  // 檢查曾經走過的路是否還有路可以走							
						}  // if 						
					
					} // if
					
				} // if
				
				else if ( command == 2 ) {
					cout << endl << "Number of G(goals) :" ;
					int goal = 0 ;
					cin >> goal ;  // 使用者輸入需要的目標數 
					while ( findGoal != true && end != true ) { // 同上	
						findGoal = aMaze.Move( goal ) ;   // 看需要多少個目標 
						if ( findGoal != true ) {
							end = aMaze.Check() ;
							
						} // if
									
					} // while
					
				} // else if
				
				else if ( command == 3 ) {
					while ( findGoal != true && end != true ) { // 先弄出圖表以及看有無路徑 
						findGoal = aMaze.Move3() ;   
						if ( findGoal != true ) {
							end = aMaze.Check1() ;
						} 			
					} // while
						
					bool shor = false ;
					int g = 0 ;
					shor = aMaze.findShortest() ;
					aMaze.Print() ;
					cout << endl ;
					if ( findGoal == true ) {
						if ( shor == true ) {	// 有找到最短路徑 
							aMaze.Turnshort() ;
						}
						else { // 沒有找到最短路徑 
							aMaze.noShortPath() ;
						}
						
						aMaze.Trans() ; // 把無用路徑轉為E
						aMaze.Print() ;
						g = aMaze.GetLength() ;
						cout << "Shortest path length = " ;
						cout << g << endl ;
					}
					else // 如果都沒有找到路徑的話 
						cout << "### There is no path to find a goal! ###" << endl ;	
						
					
					
						
					
				} // else if
				
				if ( command == 1 || command == 2 ) {
					aMaze.Print() ;
					if ( findGoal == true ) { // 假設找到指定數量的goal就印出帶有R路徑的圖 
						aMaze.Translate() ;
						while ( aMaze.Cut() != true )
							aMaze.Translate( ) ;
						
						cout << endl ;
						aMaze.Debug() ; // 補回被誤刪的必要路徑 
						if ( command == 2 )
							aMaze.Debug2() ;  // 這是在要一個以上的路徑會遇到的bug要保留往回頭看的必要路徑 
						aMaze.Fill() ;	
						aMaze.Trans() ; // 把無用路徑轉為E 
						aMaze.Print() ;	
					} // if
				}
					
					
				
				cout << endl ; 
			} // else
			
		} // if
		
		else if ( command == 0 ) // 如果指令為0就跳出程式 
			return 0 ;
			
		else { // 如果指令錯誤 
			cout << endl << "Command does not exist!" << endl ;	
		} // else11
  
	} while (true) ;
	
	system("pause") ;
	return 0 ; 
} // main
 
