// 11127116 曾詮淳 
# include <iostream>
# include <string>
#include <fstream>
#include <vector>
#include <cctype> 

using namespace std;

class Maze {

	
	public :
		bool load ( string fileName, int mode ); // 從檔案加載迷宮
		bool findGoal( Maze &vMaze, int row, int column, int dir ); // 尋找迷宮中的目標 
		void show(); // 顯示迷宮的當前狀態 
		bool findWay(Maze &vMaze, int mode); // 處理多個目標的最佳路徑問題 
		void findGoal3( Maze &vMaze, int row, int column, int dir,int vNum, bool &find );
		int howLong; // 走過多長 
		Maze(){
			found = 0; // 初始化已找到的出口數為0 
			goals = 1; // 預設的出口數為1 
			howLong = 1000; 
		}
		
		
	private :
		int length; // 迷宮的長度
		int width;  // 迷宮的寬度
		int dir;    // 目前的方向
		vector<string> trace; // 用來儲存迷宮的每一行資料
		vector<string> all; 
		int goals; // 出口的數量
		int found; // 已找到的出口數
		
};

int main () {
	int cmd = 1; // 指令 
	while ( cmd != 0 ) {
		Maze aMaze; // 創建一個迷宮物件
		string fileName; // 存儲檔案名
		int mode = 1; // 模式 (1代表一個出口, 2代表多個出口)
		// 顯示說明 
		cout << endl << "*** Path Finding ***";
		cout << endl << "* 0. Quit          *";
		cout << endl << "* 1. One goal      *";
		cout << endl << "* 2. More goals    *";
		cout << endl << "* 3. shortest path *";
		cout << endl << "********************";
		cout << endl << "Input a command(0, 1, 2, 3):";
		cin >> cmd; // 輸入指令
		
		// 載入及尋找迷宮 
		if ( cmd == 1 || cmd == 2 || cmd == 3 ) {
			if ( cmd == 2 )
				mode = 2;
				
			if ( cmd == 3 )
				mode = 3;
			
			cout << endl << "input file name : " ;
			cin >> fileName;
			if ( aMaze.load( fileName, mode ) ) {
				Maze vMaze(aMaze);
				bool success = aMaze.findWay( vMaze, mode );

				vMaze.show();
				if ( success ) {
					aMaze.show();
					if ( mode == 3 )
						cout << endl << "shortest path : " << aMaze.howLong+1;
				}
				mode = 1;
					
			} 
		} // if
		else if ( cmd == 0 ) {
			break ; // 結束程式
		}
		else {
			cout << endl << "command does not exist" << endl; // 顯示錯誤訊息
		} // else
		
	} // while
	
	cout << "pause" ; // 顯示結束訊息
	return 0;
}

// 以下是 Maze 類別的成員函數的實現

bool Maze :: load ( string fileName, int mode ) {
	// 加載迷宮資料
	fileName = "input" + fileName + ".txt"; // 組合檔案名
	std::ifstream file;
	file.open( fileName.c_str() , std::ios::in); // 打開資料夾
	// 如果無法開啟顯示 Unable to open the file.
	if (!file.is_open()) {
        cout << "Unable to open the file." << endl;
        return false;
    }
    
    string line;
    int count = 0;
    file >> length >> width;  // 讀取迷宮的大小 
    getline(file,line); // 把空行讀掉 

	// 讀取迷宮的每一行資料
    while ( ! file.eof() ) {
    	getline(file,line);
        trace.push_back(line);  // 將行添加到 vector 中
    }
    
    file.close(); // 關閉檔案
    
     // 如果mode為二，輸入出口的數量
    if ( mode == 2 ) {
    	cout << "Nunber of goals ? ";
    	cin >> goals;
	}
    return true;
} // load

bool Maze :: findGoal( Maze &vMaze, int row, int column, int dir ) {
	// 這個函數的目的是從指定的位置(row, column)開始，試圖尋找迷宮的出口。
    // 函數會根據當前的方向(dir)進行搜索，並在必要時改變方向。
    // 若找到出口數等於輸入的數量，則返回true；否則返回false。
    
	bool control = false; // 用來記錄當下這個節點是否為必經之路( 是否為R點 ) 
	int count = 0; // 用來記錄當下這個節點走過幾個方向 
	
	// 用來避免vector的index變成-1 
	if ( column < 0 ) 
		return false;
		
	// 檢查當前位置是否為出口(G)
	if ( vMaze.trace[column][row] == 'G' ) {
		vMaze.found = vMaze.found + 1;
	} // if
	
	if ( vMaze.goals == vMaze.found ) { // 如果找到的目標數等於與輸入值相等回報任務成
	 
		return true;
	}
	else if ( 0 > row || row >= length || 0 > column || column >= width ) {  // 如果超出迷宮的邊界，則返回false
		return false;
	}
	else if ( vMaze.trace[column][row] == 'O' || vMaze.trace[column][row] == 'V' || vMaze.trace[column][row] == 'T' ) {
		// 如果當前位置是一堵牆(O)、已訪問過的路徑(V)或已訪問過的目標(T)，則返回false
		return false;
	}
	else if( vMaze.trace[column][row] == 'E' || vMaze.trace[column][row] == 'G' ) { // 如果當前位置是入口(E)或出口(G) 
		
		// 標記為已訪問
		if ( vMaze.trace[column][row] == 'E' )
			vMaze.trace[column][row] = 'V';  
		else 
			vMaze.trace[column][row] = 'T';
		
		// 嘗試所有四個方向進行搜索
		while ( count < 4 ) {
			switch ( dir % 4 ) {
				case 0 :
					control = findGoal( vMaze, row + 1, column, dir );
					break;
					
				case 1 :
					control = findGoal( vMaze, row, column + 1, dir );
					break;
					
				case 2 :
					control = findGoal( vMaze, row - 1, column, dir );
					break;
					
				case 3 :
					control = findGoal( vMaze, row, column - 1, dir );
					break;
			}
			if ( control ) {
				// 如果在某個方向上找到出口，則標記當前位置為路徑(R)並返回true
				trace[column][row] = 'R';
				return true;
			}
			dir = dir+1;// 改變方向
			count = count+1;// 增加已嘗試的方向數
		}
	}
	
	return false; // 如果所有方向都無法找到出口，則返回false
}

void Maze :: show (  ) {
	
	// 這個迴圈的目的是將所有表示目標的 'T'( 已走過的目標 ) 字符替換回 'G' 字符
	for (int i = 0; i < trace.size(); i++) {
    	for (int j = 0; j < trace[i].size(); j++) {
        	if (trace[i][j] == 'T') {
            	trace[i][j] = 'G';
        	}
    	}
	}

	// 這個迴圈的目的是顯示整個迷宮的當前狀態
	for ( int i = 0; i < trace.size(); i++ ) {
		cout << endl << trace.at(i);
	}
}

bool Maze :: findWay( Maze &vMaze, int mode ) {
	int row = 0, column = 0, dir = 0, num = goals; // 初始化起始位置和方向 
	int vNum = 0;
	vector<string> temp = trace; // 創建一個臨時vector來儲存當前迷宮的狀態 
	Maze oMaze(vMaze); // 創建一個新的迷宮物件作為紀錄原本G載那裏的副本(為了解決G變R的問題) 

	bool find = false; // 用於判斷是否找到目標的標誌
	if ( mode == 3 ) {
		all = vMaze.trace;
		findGoal3( vMaze, row, column, dir, vNum, find );
		vMaze.trace = all;
		for (int i = 0; i < trace.size(); i++) {
    		for (int j = 0; j < trace[i].size(); j++) {
        		if (trace[i][j] == 'V') {
            		trace[i][j] = 'R';
        		}
    		}
		}
	
		if ( find == false )
			return false; 
	
		return true;
	}

		
	// 處理多個目標的最佳路徑問題
	
	// 處理多個目標的最佳路徑問題
	while ( vMaze.goals > 0 ) {
		Maze tMaze( vMaze );
		find = findGoal( tMaze, row, column, dir );
		if ( !find ) {
			findGoal( vMaze, row, column, dir );
			return false;
		}

		// 解決死路問題 
		for (int i = 0; i < trace.size(); i++) {
    		for (int j = 0; j < trace[i].size(); j++) {
				if ( trace[i][j] == 'R' && temp[i][j] != 'R' ) {
					temp[i][j] = 'R';
				}
    		}
		}
		vMaze.goals = vMaze.goals-1;
	}
	vMaze.goals = num;
	findGoal( vMaze, row, column, dir ); // 生成vMaze 
	
	// 解決G變R的問題 
	for (int i = 0; i < trace.size(); i++) {
    	for (int j = 0; j < trace[i].size(); j++) {
			if ( temp[i][j] == 'R' && oMaze.trace[i][j] == 'G' ) {
				temp[i][j] = 'G';
			}
   		}
	}
	trace = temp; // 儲存更新後的迷宮狀態
	return true;
}

void Maze :: findGoal3( Maze &vMaze, int row, int column, int dir, int vNum, bool &find ) {

    
	int count = 0; 
	
	if ( column < 0 ) 
		return ;

	if ( vNum >= howLong ) {
		return ;
	}
		
	if ( vMaze.trace[column][row] == 'G' ) {
		howLong = vNum;
		find = true;
		trace = vMaze.trace;
		return ;
	} // if
	


	if ( 0 > row || row >= length || 0 > column || column >= width ) {  // 如果超出迷宮的邊界，則返回false
		return ;
	}
	else if ( vMaze.trace[column][row] == 'O' || vMaze.trace[column][row] == 'V' ) {
		// 如果當前位置是一堵牆(O)、已訪問過的路徑(V)
		return ;
	}
	else if( vMaze.trace[column][row] == 'E'  ) { // 如果當前位置是入口(E)	
	// 標記為已訪問

	vMaze.trace[column][row] = 'V'; 
	all[column][row] = 'V';

		
		// 嘗試所有四個方向進行搜索
	while ( count < 4 ) {
		switch ( dir % 4 ) {
			case 0 :
				findGoal3( vMaze, row + 1, column, dir, vNum+1, find );
				break;
									
			case 1 :
				findGoal3( vMaze, row, column + 1, dir, vNum+1, find );
				break;
					
			case 2 :
				findGoal3( vMaze, row - 1, column, dir, vNum+1, find );
				break;
					
			case 3 :
				findGoal3( vMaze, row, column - 1, dir, vNum+1, find );
				break;
		}

		dir = dir+1;// 改變方向
		count = count+1;// 增加已嘗試的方向數
		}
	}
	
	vMaze.trace[column][row] = 'E'; 
	return ; // 如果所有方向都無法找到出口，則返回false	

}
