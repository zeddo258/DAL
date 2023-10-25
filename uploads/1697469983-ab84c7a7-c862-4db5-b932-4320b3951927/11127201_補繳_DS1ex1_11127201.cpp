// 11127201 陳品妤 
#include<iostream> 
#include<string.h> // String,c_str
#include <fstream>
#include<math.h>
#include<cstdlib>
#include <vector>


using namespace std ;

struct Ggrid  // 迷宮的每一格 
{
	bool IsG = false ; // G有沒有走過(兩個G的情況) 
	bool already = false; // 附近都未走過 
    char type ; 
    int step = 0 ;
};


class Maze {
	
    public : 
		int length ; // 迷宮長度 
		int width ; // 迷宮寬度 
		Ggrid **grid ;
		string filenumber ; // a file name(檔名)
		fstream file ;
		
		//================================動態矩陣===============================================
		// 因為不確定多大，用動態矩陣就不會浪費太多空間 

		Ggrid **Setmaze ( int length, int width ) {
			Ggrid **grid = new Ggrid*[length+2] ; // 創造指標長度 
			for(int i = 0 ; i < length + 2 ; i++ ) {
				grid[i] = new Ggrid[width+2] ; // 創建指標寬度 
			} // for (每一行配一個空間) 
			
			return grid;	
		} // Setmaze() 
		


        // =====================================讀檔============================================= 
		
		
		bool OpenFile() {
			file.open( ( "input" + filenumber +  ".txt" ).c_str() ) ; // open the file 開文件 
			if ( file == NULL )  {
				// 沒有檔案輸出錯誤 
				cout << endl << filenumber << ".txt does not exist!" << endl ;
				return false ;
			} // if ( file == NULL )
            else 
			    return true  ;  
		} // OpenFile()

		
		
		
		// =====================================input存取========================================= 
		
		void InputFile()  {
		// 將讀取文件的信息存在變數中	
		// >> 運算符號從檔案中取出數據的意思放置後面的變數中 
			file >> length ; // 將file 裡面的數值存進length(長度) 
			file >> width ; // 將file 裡面的數值存進width(寬度) 
		} // InputFile()  
		
		
		
		// =====================================input============================================ 
		
		void Input() {
			
			for( int y = 0 ; y < width + 2 ; y++ ){ 
			    for ( int x = 0 ; x < length + 2 ; x++ ) 
					grid[x][y].type = 'O'; // 設定牆壁 
					// 確保迷宮外的邊界防止亂走(最外圈) 
			} // for
			
			for( int y = 1 ; y < width + 1 ; y++ ){
				for ( int x = 1 ; x < length + 1 ; x++ ) 
					file >> grid[x][y].type ; // 讀取檔案中每一個符號放在迷宮裡 
			} // for
		} // Input()  
		
		
		
		//===================================output==================================================
		
		void Print()	{
			for( int y = 1 ; y < width + 1 ; y++ ){
				for ( int x = 1 ; x < length + 1 ; x++ ) 
					cout << grid[x][y].type ; // 不要讓她黏在一起 
				cout << endl ;  // 每隔單獨顯示 
			} // for 
			
			cout << endl ; // 分隔迷宮狀態 
		} // Print()
		
		void Print1()	{
			int f = 0 ;
			for( int y = 1 ; y < width + 1 ; y++ ){
				for ( int x = 1 ; x < length + 1 ; x++ ) 
				    if ( grid[x][y].type == 'R'  ) f++ ; 
			} // for 
			
			if ( f > 1 ) {
				for ( int a = 1 ; a < width + 1 ; a++) {
					for ( int z = 1 ; z < length + 1 ; z++ )
						cout << grid[z][a].type; 
					cout << endl;	
				} //for	 
			} // if   
			
			cout << endl ; // 分隔迷宮狀態 
		} // Print()
		
		
		// =====================================任務1============================================ 

		void Mission1(int x, int y, int length, int width, Ggrid **grid, bool &touch, char &direction) {
    	// 只要是E就一直往前走
    		if (grid[x][y].type == 'G') touch = false;  // 碰到目標G 終止條件 
    		else if (grid[x][y].type == 'E' || grid[x][y].type == 'V') {
        		if (grid[x][y].type == 'E') {
            		grid[x][y].type = 'V'; // 老鼠走的地方先弄成V
       		 	} // if 

       			 // 紀錄老鼠走過的路
        		grid[x][y].step = 1; // 已經走過 
        		// 保存原始方向，以便在需要回退使用
        		char originalDirection = direction;
        		// 找新的方向ˋ 
        		char newDirection = direction;
        		while (true) {
            		// 嘗試新的方向 為了檢察有沒有走過 
            		int newX = x, newY = y;
            		if (newDirection == 'R') newX = x + 1;
            		else if (newDirection == 'D') newY = y + 1;
            		else if (newDirection == 'L') newX = x - 1;
            		else if (newDirection == 'U') newY = y - 1;

            		// 檢查新方向是否有效，以及是否已走過 
            		if ((grid[newX][newY].type == 'E' || grid[newX][newY].type == 'G') && touch && grid[newX][newY].step == 0) {
                		direction = newDirection; // 更新方向
                		Mission1(newX, newY, length, width, grid, touch, direction); // 繼續向前 
                		return;
        	    	} // if  
					else {
                		// 嘗試下一個方向 
                		if (newDirection == 'R') newDirection = 'D';
                		else if (newDirection == 'D') newDirection = 'L';
                		else if (newDirection == 'L') newDirection = 'U';
                		else if (newDirection == 'U') newDirection = 'R';


			    		// 查是否已經走完所有方向，如果是需要回退
            			if (  newDirection == originalDirection  ) {
                		// 回退一步，直到找到未探索的路
                			if (originalDirection == 'R' && x > 0 && grid[x-1][y].type != 'O' ) x--;
               	 			else if (originalDirection == 'D' && y > 0 && grid[x][y - 1].type != 'O' ) y--;
                			else if (originalDirection == 'L' && x < length - 1 && grid[x + 1][y].type != 'O'  ) x++;
                			else if (originalDirection == 'U' && y < width - 1 && grid[x][y + 1].type != 'O') y++;
                			else {
                    			touch = false; // 所有方向都已探索沒法回退
                   	 			return;
                    		} // else 
       					}// if 
				
                		direction = originalDirection; // 恢复原始方向 
            		} // else
        		} // while 
    		} // else if 

    		// 老鼠走路 
    		if (direction == 'R' && (grid[x + 1][y].type == 'E' || grid[x + 1][y].type == 'G') && touch) 
        		Mission1(x + 1, y, length, width, grid, touch, direction); // 老鼠往右
				
    		else if (direction == 'D' && (grid[x][y + 1].type == 'E' || grid[x][y + 1].type == 'G') && touch) 
        		Mission1(x, y + 1, length, width, grid, touch, direction); // 老鼠往下
        		
				
    		else if (direction == 'L' && (grid[x - 1][y].type == 'E' || grid[x - 1][y].type == 'G') && touch) 
        		Mission1(x - 1, y, length, width, grid, touch, direction); // 老鼠往左
        	
    		else if (direction == 'U' && (grid[x][y - 1].type == 'E' || grid[x][y - 1].type == 'G') && touch) 
        		Mission1(x, y - 1, length, width, grid, touch, direction); // 老鼠往上
		 } //  Mission1()


		void Mission1_2( int x, int y, int length, int width, Ggrid **grid, bool &touch ) {
			if ( grid[x][y].type == 'G'   )  { 
			    int d = 0 ;
				for( int y = 1 ; y < width + 1 ; y++ ){
					for ( int x = 1 ; x < length + 1 ; x++ ) 
	                	if ( grid[x][y].type == 'V'  ) d++;
				} // for 
			 
			    if ( d > 0 )  touch = true; 
			    else {
					touch = false ; // 碰到目標 G
					return;
			    } //else 
		    } // if 
			else grid[x][y].type = 'R' ; // 將走過的地方都先設 R 
			
			if ( ( grid[x+1][y].type == 'V' || grid[x+1][y].type == 'G' ) && touch ) {
				Mission1_2( x+1, y, length, width, grid, touch ) ;
				if ( touch ) grid[x+1][y].type = 'E' ; // 將死路設為E 
			} // if (右) 
			
			if ( ( grid[x][y+1].type == 'V' || grid[x][y+1].type == 'G' ) && touch ) {
				Mission1_2( x, y+1, length, width, grid, touch ) ;
				if ( touch ) grid[x][y+1].type = 'E' ; // 將死路設為E  
			} // if (下) 
			
			if ( ( grid[x-1][y].type == 'V' || grid[x-1][y].type == 'G' ) && touch ) {
				Mission1_2( x-1, y, length, width, grid, touch ) ;
				if ( touch ) grid[x-1][y].type = 'E' ; // 將死路設為E  
			} // if (左) 
			
			if ( ( grid[x][y-1].type == 'V' || grid[x][y-1].type == 'G' ) && touch ) {
				Mission1_2( x, y-1, length, width, grid, touch ) ;
				if ( touch ) grid[x][y-1].type = 'E' ; // 將死路設為E  
			} // if (上) 
			
			
		
	
		} // Mission1_2()
		
		
		// ====================================任務二=================================================



	void Mission2(int x, int y, int length, int width, Ggrid **grid, bool &touch, char &direction, int &totalTargets) {
    	// 如果目標量已為零停止搜索
    	if (totalTargets == 0) {
        	touch = false;
        	return;
    	} // if 

   		 if ( grid[x][y].type == 'G' ) {
    		 if (grid[x][y].step == 0) { 
        	    grid[x][y].step = 1; 
            	totalTargets--; // 找到一個目標減少一次
            }// if 

        	if ( direction == 'R') {
        		if (  (grid[x + 1][y].type == 'E' ) && touch )
       				Mission2( x + 1, y, length, width, grid, touch, direction, totalTargets ); // 老鼠往右
       			else if ( ( grid[x+1][y].type == 'O' || grid[x][y+1].type == 'V'  )  && touch ) {
       				direction = 'D' ;
       		   	 	Mission2( x, y + 1, length, width, grid, touch, direction, totalTargets ); // 老鼠往下  
				} // else if 
   			} // if  
			else if ( direction == 'D' ) {
				if (   ( grid[x][y + 1].type == 'E' ) && touch)
       				Mission2(x, y + 1, length, width, grid, touch, direction, totalTargets); // 老鼠往下
       			else if ( ( grid[x][y+1].type == 'O' || grid[x][y+1].type == 'V' )  && touch) {
       				direction = 'L' ;
       		    	Mission2(x - 1, y, length, width, grid, touch, direction, totalTargets );  // 老鼠往左 
				} // else if 
   		 	} // else if 
			else if ( direction == 'L' ) {
				if (  ( grid[x - 1][y].type == 'E' ) && touch )
       				Mission2(x - 1, y, length, width, grid, touch, direction, totalTargets); // 老鼠往左
       			else if ( ( grid[x-1][y].type == 'O' || grid[x-1][y].type == 'V' )  && touch) {
       				direction = 'U';
       		   	 	Mission2(x, y - 1, length, width, grid, touch, direction, totalTargets); // 老鼠往上
				} // else if 
    		} // else if  
			else if ( direction == 'U' ) {
				if (   (grid[x][y - 1].type == 'E' ) && touch )
       				Mission2(x, y - 1, length, width, grid, touch, direction, totalTargets); // 老鼠往上
       			else if ( ( grid[x][y-1].type == 'O' || grid[x][y-1].type == 'V' )  && touch) {
       				direction = 'U';
       		    	Mission2(x + 1, y, length, width, grid, touch, direction, totalTargets ); // 老鼠往右
				} // else if 
    		} // else if 
    	} //if
		else if (grid[x][y].type == 'E' || grid[x][y].type == 'V') {
        	if (grid[x][y].type == 'E') {
            	grid[x][y].type = 'V'; // 老鼠走的地方先弄成V
        	} //if 

        	// 看老鼠有沒有走過 
        	grid[x][y].step = 1; // 已經走過 
        	// 保存原始方向，以便在需要回退使用
        	char originalDirection = direction;
        	// 找新的方向
        	char newDirection = direction;
        	while (true) {
            	// 根据新方向往前 
            	int newX = x, newY = y;
            	if (newDirection == 'R') newX = x + 1;
            	else if (newDirection == 'D') newY = y + 1;
            	else if (newDirection == 'L') newX = x - 1;
            	else if (newDirection == 'U') newY = y - 1;

            	// 檢查新方向是否有效，以及是否已走過 
            	if ((grid[newX][newY].type == 'E' || grid[newX][newY].type == 'G') && touch && grid[newX][newY].step == 0) {
                	direction = newDirection; // 更新方向
                	Mission2(newX, newY, length, width, grid, touch, direction, totalTargets); // 繼續往前 
                	return;
            	} //if  
				else {
					 // 找下一個方向
                	if (newDirection == 'R') newDirection = 'D';
                	else if (newDirection == 'D') newDirection = 'L';
                	else if (newDirection == 'L') newDirection = 'U';
                	else if (newDirection == 'U') newDirection = 'R';
                
					 // 查是否已經走完所有方向，如果是需要回退
            		if (newDirection == originalDirection) {
                	// 回退一步，直到找到未探索的路
                		if (originalDirection == 'R' && x > 0 && grid[x - 1][y].type != 'O') x--;
                		else if (originalDirection == 'D' && y > 0 && grid[x][y - 1].type != 'O') y--;
                		else if (originalDirection == 'L' && x < length - 1 && grid[x + 1][y].type != 'O') x++;
                		else if (originalDirection == 'U' && y < width - 1 && grid[x][y + 1].type != 'O') y++;
                		else {
                    		touch = false; // 所有方向都已探索無法回退
                   	 		return;
                    	} // else  
                
					} // if 
				
               		 direction = originalDirection; // 恢复原始方向
				} // else			
        	}//while 
    	}// else if 

    	// 根据方向前進 
    	if (direction == 'R' && (grid[x + 1][y].type == 'E' || grid[x + 1][y].type == 'G') && touch) 
        	Mission2(x + 1, y, length, width, grid, touch, direction, totalTargets); // 老鼠往右
    	else if (direction == 'D' && (grid[x][y + 1].type == 'E' || grid[x][y + 1].type == 'G') && touch) 
        	Mission2(x, y + 1, length, width, grid, touch, direction, totalTargets); // 老鼠往下
    	else if (direction == 'L' && (grid[x - 1][y].type == 'E' || grid[x - 1][y].type == 'G') && touch) 
        	Mission2(x - 1, y, length, width, grid, touch, direction, totalTargets); // 老鼠往左
    	else if (direction == 'U' && (grid[x][y - 1].type == 'E' || grid[x][y - 1].type == 'G') && touch) 
        	Mission2(x, y - 1, length, width, grid, touch, direction, totalTargets); // 老鼠往上
	} // Mission2()
		
		
		void Mission2_2( int x, int y, int length, int width, Ggrid **grid, bool &touch , int &total ) {
		
			if ( grid[x][y].type == 'G' ) {
				if ( !grid[x][y].IsG ) total-- ; // 碰到目標  
				grid[x][y].IsG = true ; // 將碰到過的 G 記錄起來 
			} // if 
			else if ( touch && grid[x][y].type != 'G') grid[x][y].type = 'R' ; // 將走過的地方都先設為 R  
		
			
			if ( total == 0  ) touch  = false ; // 終止條件 
			else if ( ( grid[x+1][y].type == 'V' || grid[x+1][y].type == 'G' ) && touch ) 
				Mission2_2( x+1, y, length, width, grid, touch , total ) ; // 老鼠往右 
			else if ( ( grid[x][y+1].type == 'V' || grid[x][y+1].type == 'G' ) && touch ) 
				Mission2_2( x, y+1, length, width, grid, touch, total ) ; // 老鼠往下 
			else if ( ( grid[x-1][y].type == 'V' || grid[x-1][y].type == 'G' ) && touch ) 
				Mission2_2( x-1, y, length, width, grid, touch , total ) ; // 老鼠往左 
			else if ( ( grid[x][y-1].type == 'V' || grid[x][y-1].type == 'G' ) && touch ) 
				Mission2_2( x, y-1, length, width, grid, touch , total ) ; // 老鼠往上 
			
			if ( !touch ) grid[x][y].already = true ; // 將最後一個 G 的路徑記錄起來 
		} //  Mission2_2()		
		// =================================== G 取消紀錄============================================
		
		void AllGreset( int length, int width, Ggrid **grid ) {  
			for( int y = 1 ; y < width + 1 ; y++ ) {
				for ( int x = 1 ; x < length + 1 ; x++ ) if( grid[x][y].IsG ) grid[x][y].IsG = false ;
			} // for 
		} // AllGreset()
		
		// =================================-將 R 改為 V============================================
		
		void ResetV( int length, int width, Ggrid **grid ) {
			for( int y = 1 ; y < width + 1 ; y++ ){
				for ( int x = 1 ; x < length + 1 ; x++ ) if( grid[x][y].type == 'R') grid[x][y].type = 'V' ;
			} // for 
		} // ResetV()
		
		// ==================================將 V 改為 E============================================
		
		void ResetE( int length, int width, Ggrid **grid ) {
			for( int y = 1 ; y < width + 1 ; y++ ){
				for ( int x = 1 ; x < length + 1 ; x++ ) if( grid[x][y].type == 'V') grid[x][y].type = 'E' ;
			} // for 
		} // ResetE()


		
		// =================================將紀錄起來的路徑設為 R===============================
		
		void ResetR( int length, int width, Ggrid **grid ) {
			for( int y = 1 ; y < width + 1 ; y++ ){
				for ( int x = 1 ; x < length + 1 ; x++ ) if( grid[x][y].already && !grid[x][y].IsG ) grid[x][y].type = 'R' ;
			} // for
		} // ResetR()
		
		
		
		bool Isdigit( string num ) { 
			int thelength = num.length() ;
			for ( int i = 0 ; i < thelength ; i++ ) {  // 一個一個看是不是數字 
				if ( num[i] < '0' || num[i] > '9' ) return false ; 
			} // for  
			
			return true ;
		} //  Isdigi() 	
};

int main() {
	int command = 0 ; // user command
	Maze maze ;
	do {
		int x = 1, y = 1, total = 1 ;
		int step = 1, shorteststep = 0 ;
		bool touch = true ;
		string G ;
		
		cout << endl << "*** Path Finding ***" ;
		cout << endl << "* 0. Quit          *" ;
		cout << endl << "* 1. One goal      *" ;
		cout << endl << "* 2. More goals    *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2):" ;
		cin >> command ; // get the command(獲得指令)
		
		
		
		if ( command == 0 ) break ; //'0':stop 
		else if ( command == 1 || command == 2  ){ 
			cout << "Input a file number (e.g., 201, 202, ...):" ;
			cin >> maze.filenumber ; // 檔案得編號
			if ( maze.OpenFile() ) {
				maze.InputFile() ; // 存取資料 
				maze.grid = maze.Setmaze ( maze.length, maze.width ) ;  // 創建動態陣列 
				maze.Input() ; // 設定迷宮 
				
				if ( command == 1 ) {
					char direction = 'R';
					maze.Mission1( x, y, maze.length, maze.width, maze.grid, touch ,  direction  ) ;
					maze.Print() ; // 印出來 
					if ( !touch ) {
						x = 1, y = 1, touch = true ;
						maze.Mission1_2( x, y, maze.length, maze.width, maze.grid, touch) ;
						maze.Print1() ; // 印出來 
					} // if 
					else x = 1, y = 1, touch = true ;
			    } // if ( command == 1 )
				else if ( command == 2 ) {
				    do { 
						cout << "Number of G (goals):" ;// 迷宮需要多少目標 
						cin >> G ;// 讀進來的數 
						total = std::atoi( G.c_str() ) ;//將讀進來的符號轉成數字 
						if ( ( total > 100 || total < 1 ) ) cout << "### The number must be in [1,100] ###" << endl ;	
				   } while ( !maze.Isdigit( G ) || ( total > 100 || total < 1 ) ) ;

				    char direction = 'R';
					int temp = total ;
					int num = 0 ;
					maze.Mission2( x, y, maze.length, maze.width, maze.grid, touch, direction, total ) ;
					maze.Print();
						if ( !touch ) {
							total = temp ;
							x = 1, y = 1, touch = true ;	
							for ( int i = 1 ; i <= total ; i++ ) { // 讓 Mission2Run2 跑 1 到 total 次 
								total = i ;
								maze.AllGreset( maze.length, maze.width, maze.grid ) ;
								maze.Mission2_2( x, y, maze.length, maze.width, maze.grid, touch, total ) ;
								maze.ResetV( maze.length, maze.width, maze.grid ) ;
								x = 1, y = 1, touch = true ;	
								total = temp ;
							} // for	 
					
							maze.ResetR( maze.length, maze.width, maze.grid ) ;
							maze.ResetE( maze.length, maze.width, maze.grid ) ;
				 			maze.Print();
						} // if  	
				}  // else if ( command == 2 ) 
				
				maze.file.close() ; 
		        delete[] maze.grid ;
			} // if 
		} // else if ( command == 1 || command == 2  )	
		else cout << endl  << "Command does not exist!" << endl ;
		
	} while(true );
	
	
	system( "pause" ) ; // pause the execution 暫停執行 ( system 執行操作命令，pause 用於暫停執行等鬨輸入，執行會顯示案下任意鍵繼續 ) 
	return 0 ;
	
} // main 
