// 11127212 曾博仁
# include <iostream>
# include <vector>
# include <string.h>
# include <fstream>
# include <sstream>
# include <stdlib.h>


using namespace std;

enum Modes {
	oneG, moreG         // 兩種模式 ;
};

class Maze {
private :
	int Gpoint = 0 ;			// 有幾個G點 
	int length = 0, width = 0 ; // length and width of maze
	char maze[100][100] ; 		// the maze
	int gxpoint[50], gypoint[50] ;  // 紀錄有G的點 
	int Gnum = 0 ;              // 有幾個G點 
public :
	char getmaze( int i, int j ) { // 得到迷宮每個位置的值 
		return maze[i][j] ;
	} // getmaze
	void setmaze( char A, int x, int y ) { // 設定迷宮的值 
		maze[x][y] = A ;
	} // setmaze
	void clr() {

		for ( int i = 0 ; i < width ; i ++ ) {	// 清空迷宮的所有值 
			for ( int j = 0 ; j < length ; j ++ ) {
				maze[i][j] = '/0' ;
			} // for
		} // for
	} // clr
	void show() {
		for ( int i = 0 ; i < width ; i ++ ) {	// 顯示迷宮 
			cout << endl ;
			for ( int j = 0 ; j < length ; j ++ ) {
				cout << maze[i][j] ;
			} // for
		} // for
	} // showmaze

	bool load ( char filenum[50], Modes mode ) {
		string numline1, mazeline ;				// 
		char filename[50] = "input" ;
		int point ;
		strcat( filename, filenum ) ;
		strcat( filename, ".txt") ;
		ifstream file(filename) ;	// open the file
		if ( ! file.is_open()) {     // if the file can open
			cout << "Unable to open file : " << filename << endl ;
			return false ;
		} // if

		if ( mode == oneG ) Gpoint = 1 ;
		if ( mode == moreG ) {
			cout << endl << "Input how many \"G\" : " ;
			cin >> Gpoint ;
		} // if

		getline(file, numline1) ;  // 取得第一行資料

		LineNumber( numline1 ) ; // 把第一行資料轉換成迷宮的長和寬

		for ( int i = 0 ; i < width ; i ++ ) {	//一行一行把迷宮拼湊起來
			getline(file, mazeline) ;
			for ( int j = 0 ; j < length ; j ++ ) {
				maze[i][j] = mazeline[j] ;
			} // for
		} // for


	} // load

	void LineNumber( string line1 ) { // 把第一行資料轉換成迷宮的長和寬

		char getnum ;							// 讀取字串內容
		char snum1[5] = "\0", snum2[5] = "\0" ;	// 字串型態的數字
		int place = 0 ;			        // line1 的位數
		for ( ; line1[place] != ' ' ; place ++ ){	// 把第一個數字取出來
			snum1[place] = line1[place] ;			
		} // for

		place ++ ;					// 略過空格
		int snum2p = 0 ;						// 第二個整數的位數
		while ( place < line1.size() ) {			// 把第二個數字取出來
			snum2[snum2p] = line1[place] ;
			snum2p ++ ;
			place ++ ;
		} // while


		length = atoi(snum1) ;   				// 將長的數字字串轉換成整數
		width = atoi(snum2) ;					// 將寬的數字字串轉換成整數 

	} // LineNumber

	bool findGoals( Maze & vmaze ) {			// 尋找目標 
		Maze dead_way(vmaze);					// 紀錄死路 
		Maze G_way(vmaze) ;						// 倒退的時候要記錄此條路會不會 
		return findway( vmaze, dead_way,G_way ,0, 0, 0 ) ; // 呼叫走迷宮的函數 
	} // findGoals

	bool findway( Maze & vmaze,Maze & dead_way,Maze & G_way, int dir, int x, int y ) {	// 尋找下一步 
		bool isG ;	// 記錄從哪個方向來 
		int from = (dir+2)%4 ;							// 判斷附近是否有G點 
		vmaze.setmaze( 'V', x, y ) ;			// 在走過的點留下V (vmaze) 
		maze[x][y] = 'R' ;						// 在走過的點留下R (amaze) 

		/*G_way.show() ;
		cout << endl ;*/

		dir = next( vmaze, dead_way, dir, x, y, 0, isG ) ;  // 找出下一步要走的方位 
		if ( isG == 1 ) {									// 判斷是否遇到G 
			Gpoint -- ;										// 如果遇到G，需要遇到的G就少1 
			int ax = x, ay = y ;							// 開始記錄G點的位置 
			nextway(dir,ax,ay) ;
			gxpoint[Gnum] = ax ;
			gypoint[Gnum] = ay ;
			Gnum ++ ;
			if ( Gpoint == 0 ) { reG( vmaze ); dead_way.clr() ; G_way.clr(); return true; } ; // 如果遇到Gpoint = 0表示已經走完全程，就結束這個函式
	 
		}
		if ( dir == 0 ) return findway( vmaze,dead_way, G_way ,dir, x, y+1 ) ;		// 向右走到下一格 
		else if ( dir == 1 ) return findway( vmaze,dead_way,G_way, dir, x+1, y ) ;	// 向下走到下一格 
		else if ( dir == 2 ) return findway( vmaze,dead_way, G_way, dir, x, y-1 ) ;	// 向左走到下一格 
		else if ( dir == 3 ) return findway( vmaze,dead_way,G_way, dir, x-1, y ) ;	// 向上走到下一格 

		else if ( dir == -1 ) {														// 沒有路走，需要倒退 
			backway( vmaze, dead_way,G_way, dir,from, x, y, false ) ;					// 倒退 
			if ( dir == -2 ) { dead_way.clr(); G_way.clr() ; return false ; }					// 退到起點，表示沒有路，回傳false 
			else return findway( vmaze,dead_way,G_way, dir, x, y ) ;				// 找到其他路徑，在呼叫一次findway 
		}

	} // findway
	
	void nextway( int dir, int & x, int & y ) {			// 找出下一步的座標							
		if ( dir == 0 ) y++ ; 
		else if ( dir == 1 ) x++ ;
		else if ( dir == 2 ) y-- ;
		else if ( dir == 3 ) x-- ;
	} // nextway
	


	void backway( Maze & vmaze, Maze & dead_way, Maze & G_way, int & dir,int from, int & x, int & y, bool groute ) { // 倒退 

		//dead_way.show() ; cout << endl ;
		bool isG ;													// 是否有經過G 
		int ax=x,ay=y ;
		if ( x == 0 && y == 0 ) {									// 判斷是否走回起點了 
			cout << "不存在路徑" ;
			reG(vmaze) ;											// 因為G在跑路徑的時候會V、R被蓋掉，所以要補回去 
			dir = -2 ;
			return ;
		} // if
			
		
		 

		if (from!=-1) {	
			dead_way.setmaze('D',x,y) ;
			checkRcE(from,G_way,maze,x,y,groute) ;											// 第一次呼叫backway只需要退回前一格就好 
			nextway(from,x,y) ;
			
			backway(vmaze,dead_way,G_way,dir,-1,x,y,groute) ;
			return ;
		} // if
		//cout << "223" ;
		dir = next( vmaze, dead_way, 0, x, y, 0, isG ) ;	// 尋找是否還有未走過的路
		if ( dir != -1 )  return ; 									// 找到其他路徑就可以return了 
		dead_way.setmaze('D',x,y) ;						// 在dead_way紀錄這條路為死路 

		if ( y+1 < length && maze[x][y+1]== 'R' && dead_way.getmaze(x,y+1) != 'D'  ) // 以下動作為退回前一格 
		{  checkRcE(0,G_way,maze,x,y,groute) ;y ++ ; backway( vmaze, dead_way, G_way , dir,from, x, y, groute ) ; }
		else if ( x+1 < width && maze[x+1][y] == 'R' && dead_way.getmaze(x+1,y) != 'D' ) 
		{  checkRcE(1,G_way,maze,x,y,groute) ;x ++ ; backway( vmaze, dead_way, G_way, dir,from, x, y, groute ) ; }
		else if ( y-1 >= 0 && maze[x][y-1] == 'R' && dead_way.getmaze(x,y-1) != 'D') 
		{ checkRcE(2,G_way,maze,x,y,groute) ;y -- ; backway( vmaze, dead_way, G_way, dir,from, x, y, groute ) ; }
		else if ( x-1 >= 0 && maze[x-1][y] == 'R' && dead_way.getmaze(x-1,y) != 'D') 
		{ checkRcE(3,G_way,maze,x,y,groute) ;x -- ; backway( vmaze, dead_way, G_way, dir,from ,x, y, groute ) ; }

	} // backway
	
	void checkRcE(int dir,Maze G_way,char maze[100][100],int x,int y,bool & groute ) {    	// 判斷是否要把R轉換成E 
		if (groute) {G_way.setmaze('G',x,y) ; return ; }									// 判斷倒退時是否會經過會到G的路徑 
		if(haveG(dir,G_way,x,y) ) {groute = true ; G_way.setmaze('G',x,y) ; return ; }		// 判斷此路徑是否會視抵達G的路徑 
		if ( maze[x][y] == 'R' ) maze[x][y] = 'E' ;		// 退回時將maze的R改成E 
	}  // checkRcE
	
	bool haveG( int dir, Maze G_way, int x, int y ) {			// 檢查倒退的時候此路徑是否也是到G的路徑 
		dir ++ ;			
						 									
		for( int i = 1; i <= 3 ; i ++, dir ++ ) {// 判斷四個方位是否有G
			dir %= 4 ;						 
			int xx = x, yy = y ;
			nextway(dir,xx,yy) ;
			if ( ( xx < width && xx > 0 && yy < length && yy > 0 ) && G_way.getmaze(xx,yy) == 'G') return true ; 
		} // for
		
		return false ;
	} // howmanyR

	int next( Maze vmaze, Maze dead_way, int dir, int x, int y, int time, bool & isG ) { // 判斷下一格要往哪邊走，或是沒路了 

		for ( int i = 0 ; i < 4 ; i ++ ) {					
			dir%=4 ;
			if ( ( y+1 < length && dir == 0 ) && dead_way.getmaze(x,y+1) != 'D' && ( vmaze.getmaze(x,y+1) == 'E' || vmaze.getmaze(x,y+1) == 'G' ) )
				{isG = IsG(vmaze.getmaze(x,y+1)) ;return dir ;}
			else if ( ( x+1 < width && dir == 1 ) && dead_way.getmaze(x+1,y) != 'D' && ( vmaze.getmaze(x+1,y) ==  'E' || vmaze.getmaze(x+1,y) == 'G' ) )
				{isG = IsG(vmaze.getmaze(x+1,y)) ;return dir ;}
			else if ( ( y-1 >= 0 && dir == 2 ) && dead_way.getmaze(x,y-1) != 'D' && ( vmaze.getmaze(x,y-1) ==  'E' || vmaze.getmaze(x,y-1) == 'G' ) )
				{isG = IsG(vmaze.getmaze(x,y-1)) ;return dir ;}
			else if ( ( x-1 >= 0 && dir == 3 ) && dead_way.getmaze(x-1,y) != 'D' && ( vmaze.getmaze(x-1,y) ==  'E' || vmaze.getmaze(x-1,y) == 'G' ) )
				{isG = IsG(vmaze.getmaze(x-1,y)) ;return dir ;}
			else dir++ ;										// 切換方向 
		}
	
		return -1 ;// 如果四個方位都尋找過，表示沒路 
	
	} // haveway

	bool IsG ( char G ) {								// 判斷是否為G 
		if ( G == 'G' ) return 1 ;
		else return 0 ;
	} // isG

	void reG( Maze & vmaze ) {				// 因為G在跑路徑的時候會V、R被蓋掉，所以要補回去
		if( Gnum >= 1 ) {
			for ( int i = 0 ; i < Gnum ; i ++ ) {
				maze[gxpoint[i]][gypoint[i]] = 'G' ;
				vmaze.setmaze('G',gxpoint[i],gypoint[i]) ;
			} // for
		}
	} // reG



};




int main(void) {
	int command = 0 ;     // user command
	do {
		Maze aMaze ;        // a matrix
		char fileName[50] ;   // a file name
		Modes mode = oneG ; // default: one goal

		cout << endl << "*** Path Finding ***" ;
		cout << endl << "*0. Quit           *" ;
		cout << endl << "*1. One Goal       *" ;
		cout << endl << "*2. More goals     *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2) :" ;
		cin >> command ;       // get the command
		if ((command == 1) || (command == 2)) {
			if ( command == 2 )
				mode = moreG ; // one or more goals


			cout << endl << "Input a file number (e.g.,201, 202, ...) :" ;
			cin >> fileName ;
			if ( aMaze.load(fileName, mode))   	// load the orignal matrix
			{	Maze vMaze(aMaze) ;   			// a copy to keep the visited cells
				bool success = aMaze.findGoals(vMaze) ; // find a path to goal(s)

				mode = oneG	;					// reset to default
				vMaze.show() ;					// Show on screen the visited cells
				cout << endl ;
				if ( success )					// to check if the goal is reached or not
					aMaze.show() ;				// show on screen the route to reached the goal
				vMaze.clr() ;					// clear up the copy

			} // end inner-if

			aMaze.clr() ;						// clear up the orignal matrix
		} // end outer-if
		else if (command==0)						// '0' : stop the program
			break ;
		else
			cout << endl << "Command does not exist!" << endl ;
	} while (true) ;
	system("pause") ;

						// pause the execution
	return 0 ;


} // end of main
