// 11127103 王芃穎 

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum Direction {
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,
	UP = 4,
	RETURN = -1
};

class Maze {
	
	
	public:
		Maze(); // constructor
		void Read( string str ); // 讀入檔案 
		bool Goal( int curx, int cury, int dir ); // 判斷目前的G點是否是已經找到過的 
		int Determine_Direction( int curx, int cury, int dir ); // 判斷老鼠要行走的方向
		int Return( int curx, int cury, int dir, int ret); // 如果老鼠需要回程，判斷回程中可走的其他方向  
		void Storage_FinalR(); // 繪製最終路線圖 
		int Implement( int curx, int cury, int dir, int N ); // 實作老鼠迷宮問題 
		void Print( int N ); // 輸出結果 
		
	
	private:
		int x, y; // x : x軸數量，y : y軸數量 
		vector<char> vec[50]; // 存V路徑的二維陣列 
		vector<char> rec[50]; // 存R有效路徑的二維陣列 
		vector<char> finalr[50]; // 存R最終有效路徑的二維陣列
		vector<int> gx; // 存已走到過G點的x位置 
		vector<int> gy; // 存已走到過G點的y位置
		
		
		bool find = false; // 遇到G後，用來判別此時的G是否已走過
		int count = 0, ret; // count : 計算走到到幾個G，ret : 接收Implment函數return回來的數值，並做判斷 
			
};

Maze::Maze(){
	this->gx.reserve(10); // 將gx初始10格空間
	this->gy.reserve(10); // 將gy初始10格空間
} // Maze() 

void Maze::Read( string str ) {
	ifstream in;
    in.open( str.c_str() ); // open file
    
	char r; // 讀入檔案內容的暫存變數 
	int i = 0, index = 0;
    
    in >> x >> y; // get the row and line
	
    while ( in >> r ) {
        i++;
        		
        vec[index].push_back(r); // 把讀入的字元放進vec二維陣列中，此列的最後一個 
        		
        if ( i == x ) { // 若i等於列數量，則換行 
        	index++;
        	i = 0;
		} // if()
    } // while()

	vec[0].at(0) = 'V'; // 初始把起點改成走過 
	in.close(); // close file 
	
	in.open( str.c_str() ); // open file
	i = 0, index = 0;
    
    in >> x >> y; // get the row and line 
	
    while ( in >> r ) {
        i++;
        		
        rec[index].push_back(r); // 把讀入的字元放進rec二維陣列中，此列的最後一個 
        		
        if ( i == x ) { // 若i等於列數量，則換行 
        	index++;
        	i = 0;
		} // if()
    } // while()
    
    rec[0].at(0) = 'R'; // 初始把起點改成走過
	in.close(); // close file 
	
	in.open( str.c_str() ); // open file
	i = 0, index = 0;
    
    in >> x >> y; // get the row and line 
	
    while ( in >> r ) {
        i++;
        		
        finalr[index].push_back(r); // 把讀入的字元放進finalr二維陣列中，此列的最後一個 
        		
        if ( i == x ) { // 若i等於列數量，則換行 
        	index++;
        	i = 0;
		} // if()
    } // while()
    
    finalr[0].at(0) = 'R'; // 初始把起點改成走過
	in.close(); // close file 
	
} // Read()


bool Maze::Goal( int curx, int cury, int dir ) {
	
	if ( dir == 1 ) { // 判斷此時位置向右一個點是否是已走過的G點 
		for ( int i = 0 ; i < gx.size() ; i++ ) { 
			if ( curx+1 == gx[i] && cury == gy[i] ) return true; // 若是已走到過的G點，則return true 
		} // for()
	} // if()
	
	if ( dir == 2 ) { // 判斷此時位置向下一個點是否是已走過的G點  
		for ( int i = 0 ; i < gx.size() ; i++ ) { 
			if ( curx == gx[i] && cury+1 == gy[i] ) return true; // 若是已走到過的G點，則return true 
		} // for()
	} // if()
	
	if ( dir == 3 ) { // 判斷此時位置向左一個點是否是已走過的G點  
		for ( int i = 0 ; i < gx.size() ; i++ ) {
			if ( curx-1 == gx[i] && cury == gy[i] ) return true; // 若是已走到過的G點，則return true 
		} // for()
	} // if()
	
	if ( dir == 4 ) { // 判斷此時位置向上一個點是否是已走過的G點  
		for ( int i = 0 ; i < gx.size() ; i++ ) {
			if ( curx == gx[i] && cury-1 == gy[i] ) return true; // 若是已走到過的G點，則return true 
		} // for()
	} // if()
	
	return false; // 若是沒走到過的G點，則return false
} // Goal()

int Maze::Determine_Direction( int curx, int cury, int dir ) {
	
	if ( dir == 1 ) { // 判斷是否該持續向右走，或是該按照順時鐘判斷可走方向或是返回上個點 
		if ( ( curx+1 < x ) && (vec[cury].at(curx+1) != 'V') && (vec[cury].at(curx+1) !='O') && !Goal(curx,cury,1) ) return 1;        // 持續向右走 
		else if ( ( cury+1 < y ) && (vec[cury+1].at(curx) != 'V') && (vec[cury+1].at(curx) != 'O') && !Goal(curx,cury,2) ) return 2;  // 轉成向下走 
		else if ( ( curx-1 >= 0 ) && (vec[cury].at(curx-1) != 'V') && (vec[cury].at(curx-1) != 'O') && !Goal(curx,cury,3) ) return 3; // 轉成向左走 
		else if ( ( cury-1 >= 0 ) && (vec[cury-1].at(curx) != 'V') && (vec[cury-1].at(curx) != 'O') && !Goal(curx,cury,4) ) return 4; // 轉成向上走 
		else return -1;                                                                                                               // 走回程路 
	} // if()
			
	if ( dir == 2 ) { // 判斷是否該持續向下走，或是該按照順時鐘判斷可走方向或是返回上個點 
		if ( ( cury+1 < y ) && (vec[cury+1].at(curx) != 'V') && (vec[cury+1].at(curx) != 'O') && !Goal(curx,cury,2) ) return 2;       // 持續向下走 
		else if ( ( curx-1 >= 0 ) && (vec[cury].at(curx-1) != 'V') && (vec[cury].at(curx-1) != 'O') && !Goal(curx,cury,3) ) return 3; // 轉成向左走 
		else if ( ( cury-1 >= 0 ) && (vec[cury-1].at(curx) != 'V') && (vec[cury-1].at(curx) != 'O') && !Goal(curx,cury,4) ) return 4; // 轉成向上走 
		else if ( ( curx+1 < x ) && (vec[cury].at(curx+1) != 'V') && (vec[cury].at(curx+1) !='O') && !Goal(curx,cury,1) ) return 1;   // 轉成向右走
		else return -1;                                                                                                               // 走回程路
	} // if()
			
	if ( dir == 3 ) { // 判斷是否該持續向左走，或是該按照順時鐘判斷可走方向或是返回上個點 
		if ( ( curx-1 >= 0 ) && (vec[cury].at(curx-1) != 'V') && (vec[cury].at(curx-1) != 'O') && !Goal(curx,cury,3) ) return 3;      // 持續向左走 
		else if ( ( cury-1 >= 0 ) && (vec[cury-1].at(curx) != 'V') && (vec[cury-1].at(curx) != 'O') && !Goal(curx,cury,4) ) return 4; // 轉成向上走
		else if ( ( curx+1 < x ) && (vec[cury].at(curx+1) != 'V') && (vec[cury].at(curx+1) !='O') && !Goal(curx,cury,1) ) return 1;   // 轉成向右走 
		else if ( ( cury+1 < y ) && (vec[cury+1].at(curx) != 'V') && (vec[cury+1].at(curx) != 'O') && !Goal(curx,cury,2) ) return 2;  // 轉成向下走 
		else return -1;                                                                                                               // 走回程路 
	} // if()
			
	if ( dir == 4 ) { // 判斷是否該持續向上走，或是該按照順時鐘判斷可走方向或是返回上個點 
		if ( ( cury-1 >= 0 ) && (vec[cury-1].at(curx) != 'V') && (vec[cury-1].at(curx) != 'O') && !Goal(curx,cury,4) ) return 4;      // 持續向上走 
		else if ( ( curx+1 < x ) && (vec[cury].at(curx+1) != 'V') && (vec[cury].at(curx+1) !='O') && !Goal(curx,cury,1) ) return 1;   // 轉成向右走 
		else if ( ( cury+1 < y ) && (vec[cury+1].at(curx) != 'V') && (vec[cury+1].at(curx) != 'O') && !Goal(curx,cury,2) ) return 2;  // 轉成向下走 
		else if ( ( curx-1 >= 0 ) && (vec[cury].at(curx-1) != 'V') && (vec[cury].at(curx-1) != 'O') && !Goal(curx,cury,3) ) return 3; // 轉成向左走 
		else return -1;                                                                                                               // 走回程路 
	} // if()
			
} // Determine_Direction()

int Maze::Return( int curx, int cury, int dir, int ret ) {
	
	if ( dir == 1 ) { // 在回程時判斷是否有其他路線可走，若無則按原路向左回傳 
		if ( cury+1 < y && vec[cury+1].at(curx) != 'V' && vec[cury+1].at(curx) != 'O' && !Goal(curx, cury, 2) ) return 2;       // 向下方走 
		else if ( cury-1 >= 0 && vec[cury-1].at(curx) != 'V' && vec[cury-1].at(curx) != 'O' && !Goal(curx, cury, 4) ) return 4; // 向上方走
		else return -1;                                                                                                         // 走回程路 
	} // if()
	
	if ( dir == 2 ) { // 在回程時判斷是否有其他路線可走，若無則按原路向上回傳 
		if ( curx-1 >= 0 && vec[cury].at(curx-1) != 'V' && vec[cury].at(curx-1) != 'O' && !Goal(curx, cury, 3) ) return 3;      // 向左方走 
		else if ( curx+1 < x && vec[cury].at(curx+1) != 'V' && vec[cury].at(curx+1) != 'O' && !Goal(curx, cury, 1) ) return 1;  // 向右方走 
		else return -1;                                                                                                         // 走回程路
	} // if()
	
	if ( dir == 3 ) { // 在回程時判斷是否有其他路線可走，若無則按原路向右回傳 
		if ( cury-1 >= 0 && vec[cury-1].at(curx) != 'V' && vec[cury-1].at(curx) != 'O' && !Goal(curx, cury, 4) ) return 4;      // 向上方走 
		else if ( cury+1 < y && vec[cury+1].at(curx) != 'V' && vec[cury+1].at(curx) != 'O' && !Goal(curx, cury, 2) ) return 2;  // 向下方走 
		else return -1;                                                                                                         // 走回程路 
	} // if()
	
	if ( dir == 4 ) { // 在回程時判斷是否有其他路線可走，若無則按原路向下回傳 
		if ( curx+1 < x && vec[cury].at(curx+1) != 'V' && vec[cury].at(curx+1) != 'O' && !Goal(curx, cury, 1) ) return 1;       // 向右方走 
		else if ( curx-1 >= 0 && vec[cury].at(curx-1) != 'V' && vec[cury].at(curx-1) != 'O' && !Goal(curx, cury, 3) ) return 3; // 向左方走 
		else return -1;                                                                                                         // 走回程路 
	} // if()
	
} // Return()


void Maze::Storage_FinalR() {
	// 儲存最終有效路徑 
	for ( int i = 0 ; i < y ; i++ ) {
		for ( int j = 0 ; j < x ; j++ ) {
			if ( rec[i].at(j) == 'R' && finalr[i].at(j) == 'E' ) finalr[i].at(j) = rec[i].at(j);
		} // for()
	} // for()
} // Storage_FinalR()


int Maze::Implement( int curx, int cury, int dir, int N ) {
	
	if ( count < N ) {
		dir = Determine_Direction( curx, cury, dir ); // 判斷是否要轉換路線或走回程路 
			
		if ( dir == 1 && count < N ) { // 往右移動 
			curx++;
			if ( vec[cury].at(curx) == 'G' ) { // 若此時是G點，則判斷是否是已走到過的G點 
				for ( int i = 0 ; i < gx.size() && !find ; i++ ) {
					if ( curx == gx[i] && cury == gy[i] ) find = true;
				} // for()
				
				if ( !find && vec[cury].at(curx) == 'G' ) { // 若是沒走到過的G點，則儲存並把找到的G點數量加一 
					count++;
					gx.push_back(curx); // 儲存G點x位置 
					gy.push_back(cury); // 儲存G點y位置
					
					Storage_FinalR(); // 儲存最終有效路徑 
				} // if()
				
				find = false;
			} // if()
				
			if ( count < N ) {
				if ( vec[cury].at(curx) != 'G' ) {
					vec[cury].at(curx) = 'V'; // 將走過的位置改成V 
					rec[cury].at(curx) = 'R'; // 將走過的位置改成R 
				} // if()
				ret = Implement( curx, cury, dir, N ); // 遞迴呼叫 
			} // if()
		} // if()
			
		if ( dir == 2 && count < N )  { // 往下移動 
			cury++;
			if ( vec[cury].at(curx) == 'G' ) { // 若此時是G點，則判斷是否是已走到過的G點  
				for ( int i = 0 ; i < gx.size() && !find ; i++ ) {
					if ( curx == gx[i] && cury == gy[i] ) find = true;
				} // for()
				
				if ( !find && vec[cury].at(curx) == 'G' ) { // 若是沒走到過的G點，則儲存並把找到的G點數量加一  
					count++;
					gx.push_back(curx); // 儲存G點x位置 
					gy.push_back(cury); // 儲存G點y位置
					
					Storage_FinalR(); // 儲存最終有效路徑 
				} // if()
				
				find = false;
			} // if()
				
			if ( count < N ) {
				if ( vec[cury].at(curx) != 'G' ) {
					vec[cury].at(curx) = 'V'; // 將走過的位置改成V 
					rec[cury].at(curx) = 'R'; // 將走過的位置改成R 
				} // if()
				ret = Implement( curx, cury, dir, N ); // 遞迴呼叫 
			} // if()
		} // if()
			
				
		if ( dir == 3 && count < N )  { // 往左移動 
			curx--;
			if ( vec[cury].at(curx) == 'G' ) { // 若此時是G點，則判斷是否是已走到過的G點  
				for ( int i = 0 ; i < gx.size() && !find ; i++ ) {
					if ( curx == gx[i] && cury == gy[i] ) find = true;
				} // for()
				
				if ( !find && vec[cury].at(curx) == 'G' ) { // 若是沒走到過的G點，則儲存並把找到的G點數量加一  
					count++;
					gx.push_back(curx); // 儲存G點x位置 
					gy.push_back(cury); // 儲存G點y位置
					
					Storage_FinalR(); // 儲存最終有效路徑 
				} // if()
				
				find = false;
			} // if()
				
			if ( count < N ) {
				if ( vec[cury].at(curx) != 'G' ) {
					vec[cury].at(curx) = 'V'; // 將走過的位置改成V 
					rec[cury].at(curx) = 'R'; // 將走過的位置改成R 
				} // if()
				ret = Implement( curx, cury, dir, N ); // 遞迴呼叫 
			} // if()
		} // if()
			
			
		if ( dir == 4 && count < N )  { // 往上移動 
			cury--;
			if ( vec[cury].at(curx) == 'G' ) { // 若此時是G點，則判斷是否是已走到過的G點
				for ( int i = 0 ; i < gx.size() && !find ; i++ ) {
					if ( curx == gx[i] && cury == gy[i] ) find = true;
				} // for()
				
				if ( !find && vec[cury].at(curx) == 'G' ) { // 若是沒走到過的G點，則儲存並把找到的G點數量加一  
					count++;
					gx.push_back(curx); // 儲存G點x位置 
					gy.push_back(cury); // 儲存G點y位置 
					
					Storage_FinalR(); // 儲存最終有效路徑 
				} // if()
				
				find = false;
			} // if()
				
			if ( count < N ) {
				if ( vec[cury].at(curx) != 'G' ) {
					vec[cury].at(curx) = 'V'; // 將走過的位置改成V 
					rec[cury].at(curx) = 'R'; // 將走過的位置改成R 
				} // if()
				ret = Implement( curx, cury, dir, N ); // 遞迴呼叫 
			} // if()
		} // if()
		

		if ( dir == -1 ) return -1; // 若遇到死路，則回傳 
		if ( ret == -1 && count < N ) {
		 	int z = Return( curx, cury, dir, ret ); // 判斷回程途中是否有可走的其他方向 
		 	if ( z == -1 ) {
		 		if ( rec[cury].at(curx) != 'G' )  rec[cury].at(curx) = 'E'; // 若回傳且此點不是G點，則把R改回E 
		 		return -1; // 若z是-1則回程並回傳-1 
			} // if()
			
		 	ret = Implement( curx, cury, z, N ); // 遞迴呼叫 
		 	
		 	z = Return( curx, cury, dir, ret ); // 判斷回程途中是否有可走的其他方向
		 	if ( z == -1 && count < N ) {
		 		if ( rec[cury].at(curx) != 'G' )  rec[cury].at(curx) = 'E'; // 若回傳且此點不是G點，則把R改回E 
		 		return -1; // 若z是-1則回程並回傳-1 
			} // if()
			
			ret = Implement( curx, cury, z, N ); // 遞迴呼叫 
			
		 	z = Return( curx, cury, dir, ret ); // 判斷回程途中是否有可走的其他方向
		 	if ( z == -1 && count < N ) {
		 		if ( rec[cury].at(curx) != 'G' )  rec[cury].at(curx) = 'E'; // 若回傳且此點不是G點，則把R改回E 
		 		return -1; // 若z是-1則回程並回傳-1 
			} // if()
		} // if()
				
	} // if ()
} // Implement()


void Maze::Print( int N ) {
	// 輸出路徑的二維陣列 
	for ( int i = 0 ; i < y ; i++ ) {
		for ( int j = 0 ; j < x ; j++ ) {
			cout << vec[i].at(j);
		} // for()
				
		cout << endl;	
	} // for()
	
	cout << endl;
	
	// 如果有找到需要找到的'G'數量，則輸出最終有效路徑的二維陣列
	if ( count == N ) {
		for ( int i = 0 ; i < y ; i++ ) {
			for ( int j = 0 ; j < x ; j++ ) {
				cout << finalr[i].at(j);
			} // for()
				
			cout << endl;	
		} // for()
		
		cout << endl;
	} // if()
	
	
} // Print()



int main() {
	int command = 0; // user command 
	int goals = 1; // 讀入要找到幾個G 
	string fileName; // a file name
	
	
	do {
	Maze aMaze; // a matrix
	int curx = 0, cury = 0, dir = RIGHT; // curx : 此刻在陣列中的x位置， cury : 此刻在陣列中的y位置，dir : 方向
	
	cout << endl << "*** Path Finding ***";
	cout << endl << "* 0. Quit          *";
	cout << endl << "* 1. One goal      *";
	cout << endl << "* 2. More goals    *";
	cout << endl << "********************";
	cout << endl << "Input a command(0, 1, 2): ";
	cin >> command; // get the command
	
	if ( command == 0 ) break; // '0' : stop the program 
	else if ( command == 1 || command == 2 ) {
		cout << endl << "Input a file number: ";
		cin >> fileName; // get the file 
		fileName = "input" + fileName + ".txt";
		
		ifstream in;
		in.open( fileName.c_str() ); // open file 
		if ( !in.fail() ) {          // 判斷檔案是否有開啟 
			
			in.close(); // close file 
			
			if ( command == 2 ) {
				cout << endl << "Number of G (goals): ";
				cin >> goals; // number of targets to find
			
				while ( goals < 1 || goals > 100 ) {
					cout << endl << "### The number must be in [1,100] ###" << endl << "\nNumber of G (goals): ";
					cin >> goals; // number of targets to find 
				} // while()
			} // if()
		

			aMaze.Read(fileName); // 讀入資料
			if ( command == 1 ) {
				aMaze.Implement( curx, cury, dir, command ); // implement 
				aMaze.Print( command ); // 輸出結果
			} // if()
			else if ( command == 2 && goals > 0 && goals < 101 ) {
				aMaze.Implement( curx, cury, dir, goals ); // implement 
				aMaze.Print( goals ); // 輸出結果
			} // else if()
		} // if()
		else cout << endl << fileName << " does not exist!" << endl; // file does not exist 
		
		
	} // else if()
	else cout << endl << "Command does not exist!" << endl; // command does not exist 
	
	} while( true );
	
	system("pause");
	return 0;
	
} // main()
