// 11127203 郭力嫚 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std ;

enum Modes {
    oneG = 1,   // command == 1，找一個G 
    moreG = 2,   // command == 2，找多個G 
} ;


class Maze {
private:
    int ROWS, COLS ; // x，y值 
    vector< vector<char> > maze ; //迷宮矩陣 
    int dx[4] = {0, 1, 0, -1} ; // x 軸方向上四個可能的移動步驟：0 表示不移動，1 表示向右移動，-1 表示向左移動。 
	int dy[4] = {1, 0, -1, 0} ; // y 軸方向上四個可能的移動步驟：0 表示不移動，1 表示向下移動，-1 表示向上移動。

public:
    Maze( int rows, int cols ) : ROWS( rows ), COLS( cols ), maze( rows, vector<char>( cols ) ) {} // C++建構函式的定義，用來建立一個名為Maze的類別的物件。它接受兩個參數：rows和cols，用於指定迷宮的行數和列數。
    bool load( string fileNumber ) {
    	string fileName = "input" + fileNumber + ".txt" ; // 將fileNumber改為string樣式"input + fileNumber + .txt" 
		const char* charFileName = fileName.c_str() ; // 將 fileName 中儲存的 C++ 字串轉換為 C字串 
			                                             // ，因為ifstream只接受 C字串作為檔案名稱參數。 
        ifstream inputFile( charFileName ) ; // 打開txt

        if ( !inputFile.is_open() ) { // 如果打不開txt檔 
            cout << "\n" << fileName << " does not exist!" << endl;  //輸出文字 
            return false ; // 返回false 
        } // if ( !inputFile.is_open() )

        inputFile >> COLS >> ROWS ; // 讀入行與列 
        
        maze.resize( ROWS, vector<char>( COLS ) ) ; // 重新定義迷宮大小，關鍵錯誤點！！！ 

        for ( int i = 0; i < ROWS; i++ ) {  // 讀進行的陣列內容
            string line ;
            inputFile >> line ; // 讀進陣列內容
            for ( int j = 0; j < COLS; j++ ) { // 讀進列的陣列內容
                maze[i][j] = line[j] ; // 把字元放進陣列
            } // for ( int j = 0; j < COLS; j++ )
        } // for ( int i = 0; i < ROWS; i++ )
        
       	//從txt檔讀進迷宮資料並儲存在矩陣 

        inputFile.close() ;  // 關閉資料

        return true ; // 有讀入txt檔，返回true 
    } // load( string fileName)

	void showV() {
    		// 印出迷宮內容
    		for ( int i = 0; i < ROWS; i++ ) { 
        		for ( int j = 0; j < COLS; j++ ) {
            		cout << maze[i][j] ;
        		} // for (int j = 0; j < COLS; j++)
        		cout << endl ;
    		} // for (int i = 0; i < ROWS; i++)
	} // showV() 印出遍歷路徑V
	
	void showR() { 
    	for ( int i = 0; i < ROWS; i++ ) {
        	for ( int j = 0; j < COLS; j++ ) {
            	if ( maze[i][j] == 'V' ) {
                	cout << 'E' ;
            	} // if ( maze[i][j] == 'V' ) 如果有V就改回E 
				else {
                cout << maze[i][j];
            	} // else 輸出原內容 
            	
        	} // for (int j = 0; j < COLS; j++)
        	cout << endl ; // 換行 
   		} // for (int i = 0; i < ROWS; i++)
	} // showR() // 印出完美路徑R 

	bool isValid( int x, int y ) {
    	return x >= 0 && x < ROWS && y >= 0 && y < COLS ;  
	} // 檢查是否到邊界 


    bool findRPath( int x, int y, int dir ) {
        if ( maze[x][y] == 'G' ) {
            return true ; // 找到出口
        } // if ( maze[x][y] == 'G' )
        
        else if ( maze[x][y] == 'E' ) {
        	maze[x][y] = 'V' ;  //標記V 
		} // else if ( maze[x][y] == 'E' )

    	int newX = x + dx[dir] ;  // 當前座標 (x, y) 開始，在水平方向上（行方向）移動的新座標 newX  
    	int newY = y + dy[dir] ; // 當前座標 (x, y) 開始，在垂直方向上（列方向）移動的新座標 newY 

        if ( isValid( newX, newY ) == true && ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' ) ) { // 遞迴尋找路徑
            if ( findRPath( newX, newY, dir ) == true ) { // 檢查在新的座標 (newX, newY) 上是否有一條有效的路徑
            	maze[x][y] = 'R' ; // 如果有，將當前位置 (x, y) 標記為 'R' 
                return true ; // 返回 true 表示找到了路徑
            } // if ( findRPath( newX, newY ) == true )
			else {
				if ( dir == 3 ) // 如果方向為上，重新變回右 
				    dir = -1 ; //重新設定值 
        		bool findR = findRPath( x, y, dir+1 ) ; // 當前座標 (x, y) 上，嘗試在下一個方向 dir+1 上繼續搜尋路徑
        		if ( findR == true ) { 
        			maze[x][y] = 'R' ; //如果在新方向上找到了路徑，就標記目前位置為 'R'
        			return true ; // 回傳true 
				} // if ( findR == true )
        	
			} // else
			
    	} // if ( isValid( newX, newY ) == true && ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' )
		else { // 如果碰到障礙物 'O'，則嘗試改變方向
        	for ( int newDir = 0; newDir < 4; ++newDir ) {
            	int nextX = x + dx[dir] ; // 當前座標 (x, y) 開始，在水平方向上（行方向）移動的新座標 newX  
            	int nextY = y + dy[dir] ; // 當前座標 (x, y) 開始，在垂直方向上（列方向）移動的新座標 newY 

            	if  ( isValid( nextX, nextY ) && ( maze[nextX][nextY] == 'E'  || maze[nextX][nextY] == 'G' ) ) { // 遞迴尋找路徑 
					if ( maze[nextX][nextY] == 'G' ) // 檢查在新的座標 (newX, newY) 上是否有為'G' 
					    return true ;

                	if ( findRPath( x, y, dir ) ) { // 改變方向並尋找路徑
                    	return true;
                	} // if ( findRPath( x, y, dir ) )
                	
            	} // if ( isValid( nextX, nextY ) && maze[nextX][nextY] == 'E' )
            	
            	else { 
            		if ( dir == 3 ) { // 如果已到上，改變方向為右 
            			dir = 0 ;
					} // if ( dir == 3 )
					else{
						dir++ ;  // 右、上、左、下 
					} // else
					
				} // else
				
        	} // for ( int newDir = 0; newDir < 4; ++newDir ) 
        	
    	} // else

    return false; // 沒有找到路徑
	} // bool findRPath( int x, int y, int dir )


    bool findVPath( int x, int y, int dir ) { // 找遍歷V路徑 
        if ( maze[x][y] == 'G' ) {
            return true ; // 找到出口
        } // if ( maze[x][y] == 'G' )
        
        else if ( maze[x][y] == 'E' ) {
        	maze[x][y] = 'V' ; //標記V 
		} // else if ( maze[x][y] == 'E' )

    	int newX = x + dx[dir] ; // 當前座標 (x, y) 開始，在水平方向上（行方向）移動的新座標 newX  
    	int newY = y + dy[dir] ; // 當前座標 (x, y) 開始，在垂直方向上（列方向）移動的新座標 newY 

        if ( isValid( newX, newY ) == true && ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' ) ) { // 遞迴尋找路徑
			maze[x][y] = 'V' ; // 標記當前位置為 'V'，表示已經走過
			
            if ( findVPath(newX, newY, dir) == true ) { // 遞迴尋找路徑
                return true;
            } // if ( findVPath( newX, newY ) == true )
			else {
				if ( dir == 3 ) // 如果方向為上，重新變回右 
				    dir = -1 ; //重新設定值 
        		bool findV = findVPath( x, y, dir+1 ) ; // 當前座標 (x, y) 上，嘗試在下一個方向 dir+1 上繼續搜尋路徑
        		if ( findV == true ) {
        			return true ;  // 回傳true 
				} // if ( findV == true )
        	
			} // else
    	} // if ( isValid( newX, newY ) == true && ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' )
		else { // 如果碰到障礙物 'O'，則嘗試改變方向
        	for ( int newDir = 0; newDir < 4; ++newDir ) {
            	int nextX = x + dx[dir] ; // 當前座標 (x, y) 開始，在水平方向上（行方向）移動的新座標 newX  
            	int nextY = y + dy[dir] ; // 當前座標 (x, y) 開始，在垂直方向上（列方向）移動的新座標 newY
            	//cout << "maze:" << maze[nextX][nextY] << endl ;

            	if ( isValid( nextX, nextY ) && ( maze[nextX][nextY] == 'E' || maze[nextX][nextY] == 'G' )  ) { 
					maze[x][y] = 'V' ; // 標記當前位置為 'V'，表示已經走過
					if ( maze[nextX][nextY] == 'G' )  // 檢查在新的座標 (newX, newY) 上是否有為'G'
					    return true ;

                	// 改變方向並尋找路徑
                	if (findVPath(x, y, dir)) { // 改變方向並尋找路徑
                    	return true ;
                	} // if ( findPath( x, y, dir ) )
                	
            	} // if ( isValid( nextX, nextY ) && maze[nextX][nextY] == 'E' )
            	
            	else {
            		if ( dir == 3 ) { // 如果已到上，改變方向為右
            			dir = 0 ;
					} // if ( dir == 3 )
					else {
						dir++ ;  // 右、上、左、下 
					} // else
				}
        	} // for ( int newDir = 0; newDir < 4; ++newDir ) {
    	} // else 

    return false ; // 沒有找到路徑
	} // bool findVPath( int x, int y, int dir )

}; // class Maze() 

int main() {
	char command ; // 指令 
	do {
		Maze aMaze( 0,0 ) ; //設置初始迷宮大
		string fileName ; // txt數字 
		Modes mode = oneG ; //模式一，找一個G 

		
		cout << "\n" ;
		cout << "*** Path Finding ***\n" ;
		cout << "* 0. Quit          *\n" ;
		cout << "* 1. One goal      *\n" ;
		cout << "* 2. More goals    *\n" ;
		cout << "********************\n" ;
		cout << "Input a command(0, 1, 2): " ;
		cin >> command ;
		if ( ( command == '1' ) || ( command == '2' ) ) {
			if ( command == '2' ) // '2'，找多個G 
			    mode = moreG ; 
			
			cout << "\n" ;
			cout << "Input a file number: " ;
			cin >> fileName ;
			if ( mode == oneG ) { // '1'，找一個G
			
				if ( aMaze.load( fileName ) ) { //讀入迷宮 
					Maze vMaze(aMaze) ; //複製找V路徑的迷宮 
					bool vsuccess = vMaze.findVPath( 0, 0, 0 ) ; //V路徑迷宮是否找到路			
					vMaze.showV() ; //印出V路徑 
					cout << "\n" ; //換行 
					if ( vsuccess == true ) { // 如果成功找到V路徑 
						aMaze.findRPath( 0, 0, 0 ) ; // 找出R路徑 
						aMaze.showR() ; // 印出R路徑 
						cout << "\n" ; //換行 
					} // if ( vsuccess == true )
					
				    
				} // if ( aMaze.ioad( fileName ) )
				
				
			} // if ( mode == oneG )
			
			
			
			else if ( mode == moreG ){ //模式2，找多G 
				mode = oneG ;
			} //else if ( mode == moreG )
			
		} // if ( ( command == '1' ) || ( command == '2' ) )
		
		else if ( command == '0' ) // 輸入0離開程式 
		    break ;
		    
		else //非'0'、'1'、'2' 
		    cout << "\n" << "Command does not exist!\n" ;
	} while ( true ) ;
	
	system( "pause" ) ; // 暫停程序執行，等待按下Enter鍵
	return 0 ;
} // main()


