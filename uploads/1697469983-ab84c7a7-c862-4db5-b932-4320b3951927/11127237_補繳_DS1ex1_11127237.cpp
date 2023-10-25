// 11127237 林翰 

#include<iostream>
#include<fstream>
#include <vector>

using namespace std ;


// 控制多目標or單目標模式 
enum Modes {
	oneG,
	moreG
};

const int Dir[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} }; 

class Maze {
	
private:

	int N; // 目標數 
	int lenght, width; // 長與寬 
	vector< vector< char > > mazeMape; // 迷宮地圖
	int G_num; //目標計數變數 
	vector< pair<int, int> > visitedG; // 走過G的座標	
	bool end;
		
		
public :	
	bool inRange( int x, int y) {
		if ((y >= 0) && (y < mazeMape.size()) && 
			(x >= 0) && (x < mazeMape[0].size()) )
		{
			return true;		
		}
		return false;
	}	
 		
	// 開啟迷宮檔案與建立迷宮地圖 
	bool load( string fileName, Modes mode ) {
		fileName = "input" + fileName + ".txt";
		ifstream openFile(fileName.c_str());
		
		if ( openFile.is_open()) {
			openFile >> width >> lenght;
			mazeMape.resize(lenght, vector<char>(width));
			N = 1; //將目標初始為1 
			G_num = 0; //計數為0 
			end = false; // 初始為否（判斷G往後有沒有路） 
 				
			// 如果command時輸入為2，模式會設定為多個目標 
			if ( mode == moreG ) {
				cout << endl << "input a  number: ";
				cin >> N;					
			}
			
			// 建立迷宮地圖 
			for ( int i = 0; i < lenght; i++ ) {
        		for ( int j = 0; j < width; j++ ) {
        			openFile >> mazeMape[i][j];
				}
			}
			openFile.close();
			return true;
		}
		
		else {
			cout << endl << fileName << " " << "Command does not exist" << endl;
		}
		return false;			
	}

    // 判斷G是否走過 
	bool exist_G( int x, int y) {
		if (!visitedG.empty()) {
			for ( int i = 0; i < visitedG.size(); i++ ) {
				if ( visitedG[i].first == x && visitedG[i].second == y ) {
					return true;
				}
			}
		}
		return false;
	}
	


	// 判斷方向 
	bool Turn( Maze &vMaze, int x, int y, int &dir ) {
		int tempDir = dir;
		for ( int i = 0; i < 4; i++ ) {
			if ( inRange( (x + Dir[tempDir][1]), (y + Dir[tempDir][0])) ) {
				if( vMaze.mazeMape[(y + Dir[tempDir][0])][(x + Dir[tempDir][1])] == 'E')  {
					dir = tempDir;
					return true;
				}
				if ( !exist_G( (x + Dir[tempDir][1]), (y + Dir[tempDir][0])) && 
					 vMaze.mazeMape[(y + Dir[tempDir][0])][(x + Dir[tempDir][1])] == 'G' ) 
				{
					dir = tempDir; 
					return true;
				}
			}
			tempDir = (tempDir + 1) % 4;			
		}
		
		return false;
	}
	
	// 判斷G往後是否為死路 
	bool end_G(Maze &vMaze,int x, int y, int dir) {
		int tempDir = dir;
		for ( int i = 0; i < 4; i++ ) {
			if ( inRange( (x + Dir[tempDir][1]), (y + Dir[tempDir][0])) ) {
				if( vMaze.mazeMape[(y + Dir[tempDir][0])][(x + Dir[tempDir][1])] == 'E')  {
					dir = tempDir;
					return false;
				}
				if ( !exist_G( (x + Dir[tempDir][1]), (y + Dir[tempDir][0])) && 
					 vMaze.mazeMape[(y + Dir[tempDir][0])][(x + Dir[tempDir][1])] == 'G' ) 
				{
					dir = tempDir; 
					return false;
				}
			}
			tempDir = (tempDir + 1) % 4;			
		}
		
		return true;		
		
	}
		
	//　往前走 
	void Walk( Maze &vMaze, int x, int y, int dir ) {
		if ( vMaze.mazeMape[y][x] != 'G')
			vMaze.mazeMape[y][x] = 'V';
		if (vMaze.mazeMape[y][x] == 'G') {
			visitedG.push_back(make_pair(x, y));
			G_num++;
			end = end_G(vMaze,x,y,dir);
		}
					 
	}
	

	// 尋找目標
	bool findGoals( Maze &vMaze, int x, int y, int dir ) {
		bool done,turn;
		Walk(vMaze, x,y,dir);
		
		if ( G_num == N ) {
			return true;
		}
		
		else {
			done = false;
			turn = Turn(vMaze,x,y,dir); 
			
			while ( turn && !done ) {
				end = false;
				done = findGoals(vMaze, x + Dir[dir][1], y + Dir[dir][0], dir);	
				if ( end ) {
					mazeMape[y][x] = 'R';
				}		
		    	if ( !done ) { 
		    		turn = Turn(vMaze,x,y,dir);
				}				
			}
 			if ( G_num == N )
 				mazeMape[y][x] = 'R';
			return done;
		}
	}
		
	// 輸出迷宮地圖	
	void show() {
		for (int i = 0; i < mazeMape.size(); ++i) {
        	for (int j = 0; j < mazeMape[i].size(); ++j) {
          		cout << mazeMape[i][j];
        	}
        	cout << endl; 
    	}	
		cout << endl;
		return ;	
	}
	
	// 清除地圖 
	void clr() {
		mazeMape.clear();
	}	
};

int main() {
	char command = '0';
	
	do {
		Maze aMaze;
		string fileName;
		Modes mode = oneG;
	
	cout << endl << "*** Path Finding ***";
	cout << endl << "* 0. Quit          *";
	cout << endl << "* 1. One goal      *";
	cout << endl << "* 2. More goals    *";
	cout << endl << "********************";
	cout << endl << "input a command(0,1,2): ";
	cin >> command ;
	if ( command == '1' || command == '2' ) {
		if ( command == '2' )
			mode = moreG;
		cout << endl << "input a file number: ";
		cin >> fileName;
		if ( aMaze.load(fileName, mode)) {
			Maze vMaze(aMaze);
			bool success = aMaze.findGoals(vMaze, 0, 0, 0);
			
			mode = oneG;
			vMaze.show();
			if ( success ) 
				aMaze.show();
			vMaze.clr();	
		}	
		aMaze.clr();	
	} 
	
	else if (command == '0')
		break;
	else 
		cout << endl << "Command does not exist" << endl;		
	} while(true);
	
	return 0;
}

