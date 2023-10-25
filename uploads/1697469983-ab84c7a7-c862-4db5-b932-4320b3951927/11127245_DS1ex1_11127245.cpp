// 11127245 薛宏毓  資工二乙 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum direction{
// 你知道的，這樣進行判斷的時候比較具體化 
	Right = 0, 
	Down  = 1,
	Left  = 2,
	Up    = 3,
};



// 此class專門處理資料輸入並存進設置的變數裡面 
class FileHandler {
public:
    FileHandler(string temp) {
    // 在構建函數中設置文件名
        fileName = temp;
    } // FileHandler()

    bool openAndCheckFile() {
    // 確認是否有此文件被打開 
        file.open(fileName.c_str());         // 以將字串轉成字元打開 
        
        if (!file.is_open()) {
            cout << endl << fileName << " does not exist!" << endl;
            return false;
        }
        else{
        	return true;	
		}
    } // openAndCheckFile()
    
    void readData(int &x, int &y) {
    // 讀入迷宮所需的大小 
    	int  number;
    	char nextChar;
    	x = 0, y = 0;
		while (file >> number) {        // 將讀入到的元數字存進number 
        	if (x == 0)  x = number;
			else         y = number;
			
        	nextChar = file.get();
        	
        	if (nextChar == '\n')  return;
			
    	} // while()
    	
	} // readData()
	
	vector<char> setMatrix(int row, int column) {
	// 設置矩陣所包含元素 
    	vector <char> maze(row*column);
    	char nextChar;
    	file >> nextChar;
	    for (int i = 0; i < row*column ; i++) {
	    	
	    	if (nextChar == 'O')       maze[i] = 'O';
	        else if (nextChar == 'E')  maze[i] = 'E';
	        else if (nextChar == 'G')  maze[i] = 'G';
			else cout << endl << "There has illeage element: " << nextChar << endl;
			
			file >> nextChar;    // 讀入下一個字元並存入nextChar 
    	} // for()
    	
    	return maze;
	} // setMatrix()

    void closeFile() {      // 關閉此資料 
        file.close();
    } // closeFile()

private:
    string fileName;
    ifstream file;         // 創造ifstream 物件 file 
    
}; // class FileHandler



// 此class處理走路方向和所需移動的方向格數 
class WalkingLogic{
public:
	int row, column;      // 座標 
	
	WalkingLogic(int x, int y) {
	// 使用構建函數初始化行、列 
		row    = x;
		column = y;
	}
	
	int decideDirec(int location, int direc) {
	// 決定要走的方向 
		if      (direc == Right) return goRight(location);
		else if (direc == Down)  return goDown(location);
		else if (direc == Left)  return goLeft(location);
		else if (direc == Up)    return goUp(location);
	} // decideDirec()
	
	int goRight(int location) { // 向右走一次 
		return location+=1;
	} // goRight()
	
	int goDown(int location) {  // 向下走一次
		return location+=row;
	} // goDown()
	
	int goLeft(int location) {  // 向左走一次
		return location-=1; 
	} // goLeft()
	
	int goUp(int location) {    // 向上走一次
		return location-=row;
	} // goUp()
	
private:
	
}; // class WalkingLogic



// 處理迷宮任何事情
// e.g.(是否可以移動、是否超過移動區域、搜索路徑、印出迷宮....) 
class Maze : public WalkingLogic{
public:
	vector <char> maze;          // 迷宮的串鍊 
	vector <int>  G_Location;    // 紀錄 G的位置
	vector <int>  R_Location;    // 紀錄 R的位置 
	int G_Amount;                // 目標終點個數 
	
	Maze(int x, int y, int amount, vector <char> temp) : WalkingLogic(x, y) {
	// Maze的初始化，順便呼叫 WalkingLogic的構建函數進行初始化 
		row      = x;
		column   = y;
		maze     = temp;
		G_Amount = amount;            // 預設為0 
	} // Maze() : WalkingLogic()
	
	void walked(int location) {  // 凡走過必留下V 
		maze[location]  = 'V';
	} // walked()
	
	bool callFindExit(int curLocation, int curDirection) {
	// 依據終點個數進行多次呼叫 findExit()
		while(G_Amount != 0) {
			if (!findExit(curLocation, curDirection))
				return false;
			else
				G_Amount-=1;   // 成功找到一個終點時，需找終點總數-1 
		}
		
		return true;
	} // callFindExit()
	
	bool findExit(int curLocation, int curDirection) {
	// ####### 主要運行方式為遞迴，base case為走到 G即 return true #######
		
		if (maze[curLocation] == 'G') {           // base case
			G_Location.push_back(curLocation);    // 將 G的位置記錄下來 
			maze[curLocation] = 'R';              // 將 G覆蓋，避免尋找多個終點時，重複同個點 
			return true;                          // 回傳true，即表示成功找到一個終點 
		}
		
		walked(curLocation);                      // 凡走過必留下 V 
		
		for (int i = 0; i < 4 ; i++) {                                   // 右上左下為4的循環 
		
			// e.g.[若現在為左，(左+0)%4 = 左、(左+1)%4 =上、(左+2)%4 = 右、(左+3)%4 =下 ] 
			int newDirection = (curDirection+i) % 4;
			int newLocation  = decideDirec(curLocation, newDirection);   // 往決定的方向進行移動
			
			if (canMove(newLocation, newDirection) && maze[newLocation] != 'V') {
			// 確認是否可走(有障礙物，超出矩陣) 與 是否此次遞迴走過此路 
				
				if (findExit(newLocation, newDirection)) {               // 直至遇到base case   
				
					// 結束遞迴時，會從此終點回到起點 
					// 且在已走過路上回去時，不會有繞路的情況 
					maze[curLocation] = 'R';                             // 回去的路改成 R 
					bool repeat = false;                                 // 是否重複
					for (int j = 0 ; j < R_Location.size() ; j++){
						if(R_Location[j] == curLocation) repeat = true;  // 是否在紀錄 R的資料裡面有重複資料 
					} // for() 
					
					if(!repeat) 
						R_Location.push_back(curLocation);               // 沒有就儲存 
						
					return true; // 找到終點 
				} // if(找到終點)
			} // if(可以移動且沒走過) 
		} // for(四個方向) 
		
		return false; // 沒有終點 
	} // findExit() 
	
	bool canMove(int newLocation, int mode) {
	// 確認沒走錯或超出路或到終點了 
		if (!overBlock(newLocation, mode) && !hasObstacle(newLocation)) // 超出區域 && 有障礙物 
			return true;
		else 
			return false;
	} // canMove()
	
	bool overBlock(int newLocation, int mode) {  
	// 向右就確認 X的範圍、向左就確認 X的範圍
	// 向下則確認 Y的範圍、向上則確認 Y的範圍 
		if (newLocation < 0 || newLocation > row*column-1)  return true;  // 超出整個迷宮 
		else if (mode == Right && newLocation%row == 0)     return true;  // 向右走超出範圍
		else if (mode == Down && newLocation >= row*column) return true;  // 向右走超出範圍
		else if (mode == Left && (newLocation+1)%row == 0)  return true;  // 向右走超出範圍
		else if (mode == Up && newLocation < 0)             return true;  // 向右走超出範圍
		else                                                return false;
	} // overBlock()
	
	bool hasObstacle(int newLocation) {
	// 確認前方是否有障礙物 
		if(maze[newLocation] == 'O')  return true;
		else                          return false;
	} // hasObstacle()
	
	void printV() {
	// 印出包含 V路徑的迷宮 
		cout << endl;
		for (int i = 0 ; i < G_Location.size() ; i++) {
		// 因為 G在進行遞迴時被蓋過去，所以需要復原他原本的位置
			int temp = G_Location[i];
			maze[temp] = 'G';
		} // for() 
		
		for (int i = 0 ; i < maze.size() ; i++) {
		// 因為 V在結束遞迴時被 R蓋過去，所以需要復原他原本的位置
			if (maze[i] == 'R') cout << 'V';
			else                cout << maze[i];
			
	    	if ((i + 1) % row == 0) cout << endl;
		} // for()
	} // printV()
	
	void printR() {
	// 印出包含 R路徑的迷宮
		cout << endl;
		for (int i = 0 ; i < R_Location.size() ; i++) {
		// 有些 R會被多次遞迴的V蓋過去，所以需要復原他原本的位置
			int temp = R_Location[i];
			maze[temp] = 'R';
		} // for()
		
		for (int i = 0 ; i < G_Location.size() ; i++) {
		// 因為 G在進行遞迴時被蓋過去，所以需要復原他原本的位置
			int temp = G_Location[i];
			maze[temp] = 'G';
		} // for()
		
		for (int i = 0 ; i < maze.size() ; i++) {
		// 因為 V在印出 R路徑的迷宮沒用，所以 V轉為 E 
			if (maze[i] == 'V') cout << 'E';
			else                cout << maze[i];
	    	if ((i + 1) % row == 0) cout << endl;
		} // for()
	} // printR()
	
	void end(){          // 結束並清理空間 
		maze.clear();
		G_Location.clear();
		R_Location.clear();
	} // end()
};

int main(void) {
	int  command = 0;
	bool continueMaze = true;
	
	do {
		string  fileName;           // 文件名 
		int     G_Amount;           // 目標總數 
		
		cout << endl << "*** Path Finding ***";
		cout << endl << "* 0. Quit          *";
		cout << endl << "* 1. One goal      *";
		cout << endl << "* 2. More goals    *";
		cout << endl << "********************";
		cout << endl << "Input a commnad(0, 1, 2): ";
		cin >> command;
		
		if ((command == 1) || (command == 2)) {
			
			int           row, column;      // 行列 
			vector<char>  mazeList;       // 迷宮串鍊 
			G_Amount = 1;                   // 必定有一個目標，預設為1 
			
    		cout << endl << "Input a file number (e.g., 201, 202,...): ";
    		cin >> fileName;
    		fileName = "input" + fileName + ".txt";

    		FileHandler fileHandler(fileName);   // 將輸入的文件名塞入 FileHandler的構建函數 

    		if (fileHandler.openAndCheckFile()) {                      // 確認是否能讀到此檔案 
    			fileHandler.readData(row, column);                     // 讀進裡面的資料
    			if (row > 0 && column > 0) {                           // 避免有 0和負數矩陣 
	    			mazeList = fileHandler.setMatrix(row, column);    // 將迷宮存起來 
	     			fileHandler.closeFile();                          // 結束此檔案 
	     			
	     			if (command == 2) {              // 詢問需要找到目標總數 
		    			int tempNum = 1;             // 暫時用來存目標的 
		    			
		    			cout << endl << "Number of G (goals): ";
		    			cin  >> tempNum;
		    			while (tempNum <= 0 || tempNum > 100) {
		    			// 沒目標很可悲，目標太多容易分心 
		    				cout << endl << "### The number must be in [1,100] ###" << endl;
		    				cout << endl << "Number of G (goals): ";
		    				cin >> tempNum;
						} // while()
						
						G_Amount = tempNum;
					} // if(command = 2) 
		   			
				    Maze  aMaze(row, column, G_Amount, mazeList);  // 將迷宮的基本資料塞入 Maze的構建函數 
				    
					if (aMaze.callFindExit(0, Right)) {            // 當完成全部的目標數，輸出他的 V、R路徑 
				    	aMaze.printV();
				    	aMaze.printR();
					} // if()
					else {                                         // 失敗的只能知道走過哪裡 
				    	aMaze.printV();
					} // else()
					
				    aMaze.end();                                   // 處理一下空間
				    mazeList.clear();                              // 處理一下迷宮串鍊 
				} // if(正常矩陣大小)
				else {
					cout << endl << "There's something wrong with the size of this maze"  <<endl;
				}
    		} // if(文件可以開啟)
		} // if (1 || 2)
		
		else if (command == 0)
			continueMaze = false;                              // 結束找迷宮程式 
			
		else
			cout << endl << "Command does not exist!" << endl; // 超出服務範圍 
		
	} while(continueMaze); // 除了 0，持續此迷宮執行 
	
} // main()

