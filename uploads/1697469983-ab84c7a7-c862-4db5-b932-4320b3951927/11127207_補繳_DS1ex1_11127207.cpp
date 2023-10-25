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
	int lineGoal[100] ; // 紀錄曾走過的GOAL的行 
	int rowGoal[100] ; // 紀錄曾走過的GOAL的列 
	int saveLine[100] ; //紀錄被刪除且周圍有gaol的的行跟列 
	int saveRow[100] ;
	int saveNumber ;
	bool havepath ;
	bool needpath ;
	
	int needLine[100] ;
	int needRow[100] ;
	int need ;
	
 	
	int GetNumber () {
		in >> number ;   //獲取記事本裡的數字 
		return number ;
	} // GetNumber()	
			
public :
	Mazechart() {  // 把class的需要初始化的變數初始化 
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
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2): " ;
		cin >> command ;
		cout << endl ;
		
		
		if ( command == 1 || command == 2 ) {  // 如果輸入指令1跟2 
            cout << "Input a file number(ex.201, 202,... ) : "  ;
            string fileNumber ;
            cin >> fileNumber ;  // 接收檔案名稱 
                  
			bool success = aMaze.Correctfile( fileNumber ) ; //看看是否有這個檔案 
			
			if ( success == true ) {
				aMaze.Read() ; // 讀入記事本中的資料 
				bool findGoal = false ;
				bool end = false ; 
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
 
