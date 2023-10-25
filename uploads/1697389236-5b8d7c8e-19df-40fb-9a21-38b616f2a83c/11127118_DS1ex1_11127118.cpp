// 11127118 江翊寧 
#include <iostream>
#include <cstdlib> // for atoi 
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <vector>
#include "DS1Maze.hpp"

using namespace std;

/*enum Modes {
	moreG,
	oneG,
}; // Modes*/


		
Maze::Maze() { // 基本建構元 
	
} // Maze()

Maze::Maze(const Maze& other) { // 複製其他Maze物件的建構元       
    m_maze = other.m_maze; // 複製 vector<string> m_maze 的內容

    m_x = other.m_x; // 複製 int m_x 和 int m_y 的值
    m_y = other.m_y;
    
    m_mode = other.m_mode; // 複製 m_mode 
    
    m_num = other.m_num; // 複製m_num
} // Maze

bool Maze::load(string filename, Modes mode) { // 載入地圖檔 
	ifstream myFile;
	myFile.open(filename.c_str()); // 設名為filename的檔案
	if (!myFile.is_open()) { // 如果檔案無法開啟就印出錯誤訊息並且回傳false 
    	cerr << "Error opening file " << filename << endl;
    	return false;
	} // if

	char size[5];
	myFile >> size;
	m_x = atoi(size); // 取得x值(寬)，將字元(串)轉換成整數 

	myFile >> size;
	m_y = atoi(size); // 取得y值(長)，將字元(串)轉換成整數  

	m_maze.clear(); // 清空之前的資料
	for (int i = 0; i < m_y; i++) { // 利用for迴圈將資料一行一行地存進vector中 
    	string row;
    	myFile >> row;
    	m_maze.push_back(row);
	} // for
	
	m_mode = mode; // 告訴m_mode是oneG或moreG 

	return true; // 之前讀資料成功，因此回傳true
} // load()

bool Maze::visit( int y, int x, Maze& v_maze ) { // 利用遞迴的方式從x,y座標尋找Goal，並將足跡更新到v_maze 
	if ( y >= m_y || y < 0 || x >= m_x || x < 0 ) { // 設定邊界，若超過就回傳false 
		return false; 
	} // if
	
	if ( m_maze[y][x] == 'G' ) { // 若找到G就代表任務完成，回傳true 
		v_maze.m_num--; // 找到一個G，將目標數量減一 
		return true;
	} // if
	
	if ( m_maze[y][x] == 'O' ) { // 找到O代表遇到障礙物，回傳false 
		return false ;
	} // if
	
	if ( v_maze.m_maze[y][x] == 'E' ) { // 找到E代表是可走路徑 
		if ( m_mode == moreG ) { // 多個目標 
			v_maze.m_maze[y][x] = 'V'; // 將目前位置符號改成V表示已走過 
			bool ret_value1 = visit( y, x+1, v_maze ); // 往右走並用ret_value1變數接結果 
		
			bool ret_value2 = v_maze.m_num>0 && visit( y+1, x, v_maze ); // 往下走並用ret_value2變數接結果
			
			bool ret_value3 = v_maze.m_num>0 && visit( y, x-1, v_maze ); // 往左走並用ret_value3變數接結果	
			
			bool ret_value4 = v_maze.m_num>0 && visit( y-1, x, v_maze ); // 往上走並用ret_value4變數接結果
		
			if ( ret_value1 || ret_value2 || ret_value3 || ret_value4 ) { // 只要有其中一個或一個以上的值是true就代表成功，回傳true 
				return true;
			} // if
			
			v_maze.m_maze[y][x] = 'F'; // 標記為已拜訪，表示找不到Goal 
		} // if
		
		else { // 一個目標
			v_maze.m_maze[y][x] = 'V'; // 將目前位置符號改成V表示已走過 
			bool ret_value = visit( y, x+1, v_maze ); // 往右走並用ret_value變數接結果  
			if ( ret_value ) { // 如果ret_value是true，表示找到Goal 
				return ret_value;
			} // if
			
			ret_value = visit( y+1, x, v_maze ); // 往下走並用ret_value變數接結果 
			if ( ret_value ) { // 如果ret_value是true，表示找到Goal 
				return ret_value;
			} // if
			
			ret_value = visit( y, x-1, v_maze ); // 往左走並用ret_value變數接結果 
			if ( ret_value ) { // 如果ret_value是true，表示找到Goal  
				return ret_value;
			} // if
			
			ret_value = visit( y-1, x, v_maze ); // 往上走並用ret_value變數接結果 
			if ( ret_value ) { // 如果ret_value是true，表示找到Goal 
				return ret_value;
			} // if
			
			v_maze.m_maze[y][x] = 'F'; // 標記為已拜訪，表示找不到Goal  
		} // else
		
		return false; // 其他錯誤情況，回傳false 
	} // if
	
	return false; // 其他錯誤情況，回傳false
} // visit()

bool Maze::findGoals(Maze& v_maze) {
	bool ret_value = false; // 先預設ret_value是false 
	if ( visit( 0, 0, v_maze ) ) { // 利用遞迴的方式從(0,0)尋找Goal 
		for ( int i = 0 ; i < m_y ; i++ ) { // 利用雙層迴圈將R取代V表示成功可行路徑 
			for ( int j = 0 ; j < m_x ; j++ ) {
				if ( v_maze.m_maze[i][j] == 'V' ) {
					m_maze[i][j] = 'R';
				} // if
			} // for
		} // for
		
		ret_value = true; // 表示找到Goal，ret_value變成true 
	} // if
	
	for ( int i = 0 ; i < m_y ; i++ ) { // 利用雙層迴圈將V取代F表示找不到Goal的節點標記為已拜訪 
		for ( int j = 0 ; j < m_x ; j++ ) {
			if ( v_maze.m_maze[i][j] == 'F' ) {
				v_maze.m_maze[i][j] = 'V';
			} // if
		} // for
	} // for
	
	return ret_value;
} // findGoals()

void Maze::show() {
    for ( int i = 0 ; i < m_maze.size() ; i++ ) { // 印出m_maz
    	cout << m_maze[i] << endl; 
	} // for
	
	cout<<endl;
} // show()

void Maze::clr() { // 清空m_maze資料 
    m_maze.clear();
    m_x = m_y = 0;
} // clr()

int main (void) {
	int command = 0;
	do {
		Maze aMaze;
		string fileName;
		Modes mode = oneG;
		int num;
		
		cout<<endl<<"*** Path Finding ***";
		cout<<endl<<"* 0. Quit          *";
		cout<<endl<<"* 1. One goal      *";
		cout<<endl<<"* 2. more goals    *";
		cout<<endl<<"********************";
		cout<<endl<<"Input a command(0,1,2): ";
		cin>>command;
		if ((command == 1) || (command == 2)) {
			if (command == 2) {
				mode = moreG;
				cout<<"輸入N=";
				cin>>num;
			} // if
			
			cout<<endl<<"Input a file number(e.g.,201,202,...):";
			cin>>fileName;
			fileName = "input" + fileName + ".txt";
			if (aMaze.load(fileName,mode)) {
				Maze vMaze(aMaze);
				vMaze.m_num = num;
				bool success = aMaze.findGoals(vMaze);
				mode = oneG;
				vMaze.show();
				
				if ( success ) {
					aMaze.show();
				} // if
				
				vMaze.clr();
			} // if
		} // if
		
		else if ( !command ) {
			break;
		} // else if
		
		else {
			cout<<endl<<"Command does not exist!"<<endl;
		} // else
	}while (true) ;
		system ("pause");
	return 0;
} // main()
