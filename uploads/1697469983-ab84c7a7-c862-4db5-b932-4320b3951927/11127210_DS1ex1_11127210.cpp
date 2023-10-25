// 資工二乙 11127210 劉彥廷 
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std ;

// 儲存迷宮的路徑資訊
struct Block {
	char pos ; // 記錄此路徑的狀態 E O V G R 
	bool GisPassed = false ; // 若此Block的pos儲存的是目標G，紀錄G是否已經被走過 
	bool VFalsereturned = false ; // 若此Block的pos儲存的是V，紀錄此路徑四個方位前方是否為死路或多餘的路
};


// 迷宮的各項資訊 
class Maze {
public:
	
	// Constructor 	
	Maze() {}
	
	// Copy Constructor
	Maze( Maze& other ){
		
		// 複製 Maze裡的各項資訊 
		row = other.getRow() ;
		col = other.getCol() ;
		countG = other.getcountG() ;
		mouseDirection = other.getMouseDirection() ;
		
		for( int i = 0 ; i < row ; i++ ) {
			for( int j = 0 ; j < col ; j++ ) {
				maze[i][j].pos = other.getPos( i, j ) ;
				maze[i][j].GisPassed = other.getGisPassed( i, j ) ;
				maze[i][j].VFalsereturned = other.getVFalsereturned( i, j ) ;
			} // for j
		} // for i
		
	} 

	// 回傳mouseDirection
	int getMouseDirection() {
		return mouseDirection ;
	}


	// 回傳maze的位置資訊 pos
	char getPos( int x, int y ) {
		return maze[x][y].pos ;
	} 
	
	// 回傳maze的 GisPassed
	bool getGisPassed( int x, int y ) {
		return maze[x][y].GisPassed ;
	} 
	
	// 回傳maze的 VFalsereturned
	bool getVFalsereturned( int x, int y ) {
		return maze[x][y].VFalsereturned ;
	}
	
	// 回傳row的值 
	int getRow() {
		return row ;
	} // getRow()
	
	// 回傳col的值 
	int getCol() {
		return col ;
	} // getCol()

	// 數出目前經過的目標G數量 
	void addG() {
		countG = countG + 1 ;
	} // addG() 
	
	// 回傳countG的值 
	int getcountG() {
		return countG ;
	} // getcountG()
	

	// 改變老鼠目前移動的方向，順序為: 0(右) 1(下) 2(左) 3(上) 循環 
	void changeDirection() {
		if ( mouseDirection == 3 ) {
			mouseDirection = 0 ;
		} // if
		else {
			mouseDirection = mouseDirection + 1 ;	
		}
	} // changeDirection()

	// 印出迷宮 
	void show() {
		
		for( int i = 0 ; i < row ; i++ ){
			for( int j = 0 ; j < col ; j++ ){
				
				if ( j == (col - 1) )
					cout << maze[i][j].pos << endl ;
				else 
					cout << maze[i][j].pos ;
					
			} // for j
		} // for i
		
	} // show()
	
	
	// 初始化迷宮資訊 
	void resetAll() {
		
		row = 0 ;
		col = 0 ;
		mouseDirection = 0 ;
		countG = 0 ;
		
		for( int i = 0 ; i < 100 ; i++ ){
			for( int j = 0 ; j < 100 ; j++ ){
				maze[i][j].pos = '\0' ;
			} // for j
		} // for i
			
	} // resetAll
	
	
	// 載入迷宮 
	bool load( string Snumber ) {
		
		// 變數區 
		ifstream in ;
		string filename ;
		char temp ; // 暫時儲存字元 

		
		// 開啟以"Input" + Snumber + ".txt"為名字的檔案 
		filename = "Input" + Snumber + ".txt" ;
		in.open( filename.c_str() ) ;
		
		// 若開啟檔案失敗，則輸出filename + "does not exist!" 
		if ( in.fail() ) {
			cout << filename + " does not exist!" << endl ;
			return false ;
		} // if ( in.fall ) 
		
		else {
			
			// 讀入迷宮的大小 
			in >> col >> row ;
			
			// 避免row以及col是負數或0 
			if( row < 1 || col < 1) {
				return false ;
			} //if( row < 1 || col < 1)
			
			// 讀入迷宮的第一筆資料 
			in >> temp ;

			// 讀入迷宮的資料，並存於maze			
			for( int i = 0 ; i < row ; i++ ){
				for( int j = 0 ; j < col ; j++ ){
					maze[i][j].pos = temp ;
					in >> temp ;
				} // for j
			} // for i
			
			
		} // else 
		
		in.close() ; // 釋放記憶體 
	} // load( string Snumber )
	
	
	// 只需要找到一個目標G的情況 
	bool findAGoal ( int x, int y ) {
		
		// dx,dy 為老鼠的移動方向 
		int dx[10] = { 0, 1, 0, -1 } ;
		int dy[10] = { 1, 0, -1, 0 } ;
		
		// newX,newY 為老鼠下一步的座標 
		int newX ;
		int newY ;
		
		
		// 若此pos是目標G，回傳true停止遞迴 
		if ( maze[x][y].pos == 'G' ) {
			return true ;
	 	} // if ( maze[x][y].pos == 'G' )

		// 若此pos是E即是可以走的路徑，將E改為V(visited) 
		if( maze[x][y].pos == 'E' ) {
			maze[x][y].pos = 'V' ;
			
		} // if( maze[x][y].pos == 'E' )
		
		// 針對現在座標的右下左上進行檢查，若有E或是G即依現在老鼠移動方向前往該座標 
		for( int i = 0 ; i < 4 ; i = i + 1 ) {
			newX = x + dx[mouseDirection] ;
			newY = y + dy[mouseDirection] ;
			
			if ( maze[newX][newY].pos == 'E' || maze[newX][newY].pos == 'G' ) {
				if( findAGoal( newX, newY ) )
					return true ;		
			} // if ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' )
			
			changeDirection() ; // 改變老鼠方向  

		} // for i
		
		// 若右下左上四個方位的前方都是死路或多餘的路即回傳false，並以VFalsereturned紀錄 
		maze[x][y].VFalsereturned = true ;
		return false ;
 
	} // findAGoal ()
	
	
	// 在找到對應數量的G以後，找到一條R路徑，使其不走到死路或多餘的路 
	bool findRoute ( int x, int y, int NumOfGoal ) {
		
		// dx,dy 為老鼠的移動方向 
		int dx[10] = { 0, 1, 0, -1 } ;
		int dy[10] = { 1, 0, -1, 0 } ;
		// newX,newY 為老鼠下一步的座標 
		int newX ;
		int newY ;
		
		// 若此座標是G且沒有被走過，找出R路徑，將此座標設置為走過並記錄G的個數 
		if ( maze[x][y].pos == 'G' && maze[x][y].GisPassed == false ) {
			maze[x][y].GisPassed = true ;
			SetRoute() ;
			addG() ;
	 	} // if ( maze[x][y].pos == 'G' && maze[x][y].isPassed == false )
	 	
	 	// 檢查目前找到G的數量是否已經足夠 
		if ( getcountG() == NumOfGoal )
			return true ;
		
		// 若此座標為E(可走的路徑)，標示為V(visited) 
		if( maze[x][y].pos == 'E' ) {
			maze[x][y].pos = 'V' ;
		} // if( maze[x][y].pos == 'E' )
		
		
		// 針對現在座標的右下左上進行檢查，若有E或是G即依現在老鼠移動方向前往該座標 
		for( int i = 0 ; i < 4 ; i = i + 1 ) {
			newX = x + dx[mouseDirection] ;
			newY = y + dy[mouseDirection] ;
			
			if ( maze[newX][newY].pos == 'E' || maze[newX][newY].pos == 'G' ) {
				if( findRoute( newX, newY, NumOfGoal ) )
					return true ;		
			} // if ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' )
			
			changeDirection() ; // 改變老鼠方向 

			
		} // for i
		
		
		// 若右下左上四個方位的前方都是死路或多餘的路即回傳false，並以VFalsereturned紀錄 
		maze[x][y].VFalsereturned = true ;
		return false ;
 
	} // findRoute ()
	
	// 在尋找多個目標G的情況下，找出一條路徑讓老鼠可以找到多個G 
	bool findGoals ( int x, int y, int NumOfGoal ) {
		
		// dx,dy 為老鼠的移動方向 
		int dx[10] = { 0, 1, 0, -1 } ;
		int dy[10] = { 1, 0, -1, 0 } ;
		// newX,newY 為老鼠下一步的座標 
		int newX ;
		int newY ;
		
		// 若此座標是G且沒有被走過，將此座標設置為走過並記錄G的個數 
		if ( maze[x][y].pos == 'G' && maze[x][y].GisPassed == false ) {
			maze[x][y].GisPassed = true ;
			addG() ;
	 	} // if ( maze[x][y].pos == 'G' && maze[x][y].isPassed == false )
	 	
	 	// 檢查目前找到G的數量是否已經足夠 
		if ( getcountG() == NumOfGoal )
			return true ;
			
		// 若此座標為E(可走的路徑)，標示為V(visited) 
		if( maze[x][y].pos == 'E' ) {
			maze[x][y].pos = 'V' ;
			
		} // if( maze[x][y].pos == 'E' )
		
		// 針對現在座標的右下左上進行檢查，若有E或是G即依現在老鼠移動方向前往該座標 
		for( int i = 0 ; i < 4 ; i = i + 1 ) {
			newX = x + dx[mouseDirection] ;
			newY = y + dy[mouseDirection] ;
			
			if ( maze[newX][newY].pos == 'E' || maze[newX][newY].pos == 'G' ) {
				if( findGoals( newX, newY, NumOfGoal ) )
					return true ;		
			} // if ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' )
			
			changeDirection() ; // 改變老鼠方向 

			
		} // for i
		
		// 若右下左上四個方位的前方都是死路或多餘的路即回傳false
		return false ;
 
	} // findGoals ()
	
	
	// 以VFalsereturned判斷並設置不走死路或多餘的路的路徑R 
	void SetRoute() {
		
		
		for( int i = 0 ; i < row ; i++ ) {
			for( int j = 0 ; j < col ; j++ ) {
				
				// 若此座標是V且不是死路或多餘的路，即設置為路徑R 
				if ( maze[i][j].pos == 'V' && maze[i][j].VFalsereturned == false ) {
					 maze[i][j].pos = 'R' ;
				} // if ( maze[i][j].pos == 'V' && maze[i][j].VFalsereturned == false )
				
				// 若此座標是V且是死路或多餘的路，即不會走這條路(設置為E) 
				else if ( maze[i][j].pos == 'V' && maze[i][j].VFalsereturned == true ) {
					maze[i][j].pos = 'E' ;
					
					
				} // else if ( maze[i][j].pos == 'V' && maze[i][j].VFalsereturned == true )
			} // for j
		} // for i
		
	} // SetRoute()
	

private:

	int row = 0, col = 0 ; // 迷宮大小( row * col ) 
	Block maze[100][100] ; // 迷宮資訊 
	int countG = 0 ; // 紀錄目前G的數量
	 
	//老鼠移動方向 0代表右，1代表下，2代表左，3代表上( default = 0 ) 
	int mouseDirection = 0 ; // 目前老鼠的方向 
	
};

int main(void){
	int command = 1 ; // 指令 ( default = 1 )
	
	
	do{

	int startX = 0, startY = 0 ; // 起始點( 0 , 0 ) 
    int NumOfGoal = 1 ; // 要找的目標G數量( default = 1 ) 
	string fileName ; // 要讀的檔案名稱 
    Maze aMaze ; // 迷宮 
    aMaze.resetAll() ; // 初始化迷宮 

	// 給使用者指令的資訊以及標題 
	cout << endl << "*** Path Finding ***" ;
	cout << endl << "* 0. Quit          *" ;
	cout << endl << "* 1. One goal      *" ;
	cout << endl << "* 2. More goals    *" ;
	cout << endl << "********************" ;
	cout << endl << "Input a command(0, 1, 2): " ;
	
	cin >> command ; // get command
	
	// 確認輸入的指令是否為 ( 0,1,2 ) 否則重新輸入 
	while ( command < 0 || command > 2 ) {
		cout << endl ;
		cout << "Command does not exsist!" << endl ;
		cout << endl << "*** Path Finding ***" ;
		cout << endl << "* 0. Quit          *" ;
		cout << endl << "* 1. One goal      *" ;
		cout << endl << "* 2. More goals    *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2): " ;
		cin >> command ;
	} // while ( command < 0 || command > 2 )
	

	// command = 1 或 2 的情形 
    if ( (command == 1) || ( command == 2) ) {
    	
    	// 引導使用者輸入要讀入的檔案名稱 
    	cout << endl ;
    	cout << "Input a file number (e.g.,201,202,...): " ;
		cin >> fileName ;
		cout << endl ;
			
		// 讀入迷宮 
    	if ( aMaze.load( fileName ) ) {
			
			bool success = false ;

			Maze vMaze(aMaze) ; // vMaze用來印出老鼠Visted的路徑 

			// 有多個G的處理 
			if ( command == 2 ) {
				
				// 引導使用者輸入G的資訊 
				cout << "Number of G (goals): " ;
				cin >> NumOfGoal ;
				while ( NumOfGoal < 1 || NumOfGoal > 100 ) {
					cout << endl ;
					cout << "### The number must be in [1,100] ###" << endl ;
					cout << endl ;
					cout << "Number of G (goals): " ;
					cin >> NumOfGoal ;
    	   	 	} // while ( mode >= 1 && mode <= 100 )
    	   	 	
    	   	 	
    	   	 	success = vMaze.findGoals( startX, startY, NumOfGoal ) ; // 找出有對應目標G數量的路徑 
				vMaze.show() ; // 顯示迷宮目前情形 
				cout << endl ;
				 
				// 若成功找到路徑R，顯示並重設迷宮 
    	   	 	if ( success ) {
    	   	 		aMaze.findRoute( startX, startY, NumOfGoal ) ;
    	   	 		aMaze.show() ;
				} // if ( success )
    	   	 	
    	   	 	vMaze.resetAll() ;
    	   	 	aMaze.resetAll() ;
    	   	 	
			} // if ( command == 2 )

			// 只有一個G的處理 
			else if( command == 1 ) {
				
				
				success = aMaze.findAGoal( startX, startY ) ; // 找出G
				
				// 若成功找出G，顯示其老鼠走過的路徑V，以及沒有死路或多餘的路的R 
				if ( success ) {
					aMaze.show() ;
					cout << endl ;
				
					aMaze.SetRoute() ;
			
					aMaze.show() ;
					aMaze.resetAll() ;
				} // if ( success )
				
				// 若沒有找出G，顯示其老鼠走過的路徑V 
				else{
					aMaze.show() ;
					aMaze.resetAll() ;
				} // else
				
			} // else if ( command == 1 )
			
		} // if ( aMaze.load( fileName ) )

	} // if ( (command == 1) || ( command == 2) )
	
	// command = 0 退出	    
	else if ( !command )
		break ;
	// 指令錯誤 
	else
		cout << endl << "Command does not exsist!" << endl ;
		
	} while ( true ) ;

	system("pause") ;
	return 0 ;
	

} // main()
