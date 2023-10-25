// 11127161 劉芷妘 

# include <stdlib.h>
# include <iostream>
# include <fstream>
# include <string.h>
# include <vector>

using namespace std;

enum Modes{ // 有幾個目標 
	oneG, moreG
};

class Maze{
	private:
		vector<string> lines; // 宣告
		string line; // 暫時儲存單個字串 
	public:
		int row; // y座標 行 
		int column; // x座標 列  
		int a1, b1, goalnumber;
		int goalsite1,goalsite2;

	
		
	bool load( string filename , Modes mode){
		
    	string Filename = "input" + filename + ".txt" ; // 變成input101.txt 
    	
    	char Filename2[100];
    	strcpy(Filename2, Filename.c_str());
		ifstream file(Filename2); // 只吃char型態的字串 
		if (!file.is_open()) // 判斷檔案是否開啟 
			return false;
		else {
			string a;
			string b;
			file >> a >> b; // 讀入行 列 
			int n1,n2;
			row = atoi(a.c_str());
			column = atoi(b.c_str());
			getline(file, line) ;
    		while (getline(file, line)) {
        		lines.push_back(line); // 每一行添加到 vector 中
    		} // while
    		
    		file.close(); // 關閉文件 
			return true;
		} // else
	
	} // load
	
	// 函數：在地圖上尋找目標
	bool findGoals(int & goalnumber, Maze & vMaze) {
	    int a1 = 0, b1 = 0;
		int direction = 1; // 先預設在(0,0) 且往右 
	    return finddir(a1, b1, goalnumber, direction, vMaze);
	} // findGoals
	
	bool finddir(int a1, int b1, int goalnumber, int direction, Maze &vMaze) {
		//  右:1 下:2  左:3  上:4  
		if( vMaze.lines[a1][b1] == 'G' ) { // 如果是目標 
			return true;
		} // if

		if ( direction == 1 ) { // 如果是往右
			if ( vMaze.lines[a1][b1+1] == 'O' || b1+1 == row || vMaze.lines[a1][b1+1] == 'V') { // 右邊是障礙物或者是邊界 
				direction = 2; // 方向變成向下
				return finddir( a1, b1, goalnumber, direction, vMaze);
			} // if 往右邊看 
			else if ( vMaze.lines[a1][b1+1] == 'E' || vMaze.lines[a1][b1+1] == 'G' ) { //下面是空格或目標 {
				vMaze.lines[a1][b1] = 'V'; // 走過的路變成V 
				lines[a1][b1] = 'R';
				b1++;
				return finddir(a1, b1, goalnumber, direction, vMaze);
			} // else if	
		} // if 
		else if ( direction == 2 ) { // 如果是往下 
			if ( vMaze.lines[a1+1][b1] == 'O' || a1 + 1 == column || vMaze.lines[a1+1][b1] == 'V') { // 下面是障礙物或者是邊界 
				direction = 3; // 方向變成向左 
				return finddir( a1, b1, goalnumber, direction, vMaze);
			} // if
			else if ( vMaze.lines[a1+1][b1] == 'E' || vMaze.lines[a1+1][b1] == 'G' ) { //下面是空格或目標 
				vMaze.lines[a1][b1] = 'V'; // 走過的路變成V
				lines[a1][b1] = 'R';
				a1++; // 繼續往下面找 
				return finddir(a1, b1, goalnumber, direction, vMaze);
			} // else if	
		} // else if 
		else if ( direction == 3 ) { // 如果是往左 
			if ( vMaze.lines[a1][b1-1] == 'O' || b1 - 1 < 0 || vMaze.lines[a1][b1-1] == 'V' ) { // 左面是障礙物或者是邊界 
				direction = 4; // 方向變成向上 
				return finddir( a1, b1, goalnumber, direction, vMaze );
			} // if
			else if ( vMaze.lines[a1][b1-1] == 'E' || vMaze.lines[a1][b1-1] == 'G' ) { //左邊是空格或目標
				vMaze.lines[a1][b1] = 'V'; // 走過的路變成V 
				lines[a1][b1] = 'R';
				b1--; // 繼續往左邊找 
				return finddir(a1, b1, goalnumber, direction, vMaze);
			} // else if	
		} // else if 
		else if ( direction == 4 ) { // 如果是往上 
			if ( vMaze.lines[a1-1][b1] == 'O' || a1 - 1 < 0 || vMaze.lines[a1-1][b1] == 'V') { // 上面是障礙物或者是邊界 
				direction = 1; // 方向變成向右 
				return finddir(a1, b1, goalnumber, direction, vMaze);
			} // if
			else if ( vMaze.lines[a1-1][b1] == 'E' || vMaze.lines[a1-1][b1] == 'G' ) { //下面是空格或目標 
				vMaze.lines[a1][b1] = 'V'; // 走過的路變成V
				lines[a1][b1] = 'R';
				a1--; // 繼續往上面找 
				return finddir(a1, b1, goalnumber, direction, vMaze);
			} // else if	
		} // else if 
		
		return false;
	} // finddir


	void show(){
			
		for( int i = 0 ; i < lines.size() ; i++ ) {
			cout << lines[i] << "\n" ;
		} // for
		
		cout << endl;
		
	} // show
	
	void cir(){
		for ( int i = 0; i < row ; i++ ){
			for ( int j = 0 ; j < column ; j++ ){
				lines[i][j] = '\0';
			} // for
		} // for 
	} // cir
};


int main(void) {
	int command = 0, number = 0;
	
	do {
		Maze aMaze;
		string filename;
		Modes mode = oneG;
		bool success;
		
		cout << endl << "***Path Finding ***";
		cout << endl << "*0. Quit          *";
		cout << endl << "*1. One goal      *";
		cout << endl << "*2. More goals      *";
		cout << endl << "********************";
		cout << endl << "Input a command(0, 1, 2): ";
		cin >> command; // 取得指令 

		
		if ((command == 1) || (command == 2)) {
			cout << endl << "Input a file number (e.g., 101, 102,...):";
			cin >> filename;
			if (command == 2) {
				mode = moreG; // 一個或多個目標 
				cout << endl << "Number of G (goals):";
				cin >> number;
			} // if 
			
						
			if (aMaze.load(filename, mode)){ // 載入原始矩陣 

				
				Maze vMaze(aMaze); // 宣告aMaze vMaze 
				if ( command == 2 ) { // 不只一個目標 
					int goalnumber = number;
					success = aMaze.findGoals(goalnumber, vMaze); //看是否有找到通往目標的路徑  
				} // if
				
				else {
					int goalnumber = 1; 
				    success = aMaze.findGoals(goalnumber, vMaze); //看是否有找到通往目標的路徑  vMaze
				} // else

			
				mode = oneG; // 重設為預設 
				vMaze.show(); // 顯示已經走過的地圖
			  
				if (success) // 如果有成功找到路徑 
					aMaze.show(); // 顯示到達目標的路徑
				vMaze.cir(); // 清空 

			} // if
			
		
		// lines.clear();
		aMaze.cir();;
		// aMaze = '\0';
		}
	
	else if(!command)
		break;
	else
		cout << endl << "Command does not exist!" << endl;
	} while(true);
	system("pause");
	return 0;
} // end of main


