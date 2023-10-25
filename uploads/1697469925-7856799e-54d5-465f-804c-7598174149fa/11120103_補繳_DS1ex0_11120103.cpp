// 11120103 游舒涵 

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;




class Maze{
	private:
		vector<vector<char>> maze, visitted, shortestRoute;
		
	public:
		int command; // 指令 
		int x, y; // 迷宮大小 
		int expectedNum = 1, foundNum = 0; // G的期望數量，找到數量	
	
	
	
		int GetCommand(){
			while( true ){
				cout << "***Path Finding***" << endl;
				cout << "* 0. Quit        *" << endl;
				cout << "* 1. One goal    *" << endl;
				cout << "* 2. More goals  *" << endl;
				cout << "******************" << endl;
				cout << "Input a command(0, 1, 2): ";
				cin >> command;
				cout << endl;
			
				if( command == 0 || command == 1 || command == 2 )
					return command;
				else cout << "Command does not exit!" << endl;
			}
		} // GetCommand()
	
	
	
	
		string GetFileName(){
			string fileNum;	
			cout << "Input a file number: ";
			cin >> fileNum;
			cout << endl;
			return "input" +fileNum +".txt";
		} // GetFileName()
	
	
	
	
		bool ReadFile( string fileName ){
			ifstream fin;
			fin.open(fileName); // 打開檔案 
			if( ! fin.is_open() ) { 
				cout << fileName << " does not exist!" << endl;
				return false;
			}
				
			string row, column;  // 迷宮大小
			fin >> column >> row; 
			if( IsNumeric(row) && IsNumeric(column) &&
				0 < stoi(row) && 0 < stoi(column) ) { 
				x = stoi(row);
				y = stoi(column);
			}
			else return false; // 防呆機制 
		
			maze.resize( x, vector<char>(y) ); // 建立迷宮
			for( int i = 0 ; i < x ; i++ ){ // row
				for( int j = 0 ; j < y ; j++ ) // column
					fin >> maze[i][j]; 
			} 
			visitted = shortestRoute = maze;
			return true;
		} // ReadFile()
		
		
		
		
		bool IsNumeric( string str ){
			for( int i = 0, len = str.length() ; i < len ; i++ ){
				if( ! isdigit(str[i]) )
					return false;
			}
			return true;
		} // IsNumeric()
	
	
	

		void GetExpectedNum(){ // 獲得G的期望數量
			while( true ){
				string en; 
				cout << "Number of G (goals): ";
				cin >> en;
				cout << endl;
				if( IsNumeric(en) ){
					if( 1 <= stoi(en) && stoi(en) <= 100 ){ // 需為1到100的整數
						expectedNum = stoi(en);
						return;
					}
					else cout << "### The number must be in [1,100] ###" << endl;
				}
			}
		} // GetExpectedNum()
		
		
		
		
		int CountR( vector<vector<char>> r ){ // 再改改 
			int cr;
			for( int i = 0 ; i < r.size() ; i++ ){
				for( int j = 0 ; j < r[i].size() ; j++ ){
					if( r[i][j] == 'R' )
						cr++;
				}
			}
			return cr;
		} // CountR()
		
		
		
		
		void FindShortestRoute( vector<vector<char>> sr ){
			if( CountR(shortestRoute) == 0 ||
				CountR(sr) < CountR(shortestRoute) ){
				shortestRoute = sr;
				
				// 是這個意思嗎?不然會變成所有路都走過 
				for( int i = 0 ; i < sr.size() ; i++ ){
					for( int j = 0 ; j < sr[i].size() ; j++ ){
						if( sr[i][j] == 'R' ) // 把那條路徑視為路徑 
							visitted[i][j] = 'V';
					}
				}
			}
		} // FindShortestRoute()
	
	

		
		bool Move2( int i, int j, char toward, vector<vector<char>> r ){
		// (位置，前進方向，其中一條到G的r圖) 
			if( i < 0 || i >= x || j < 0 || j >= y || maze[i][j] == 'O' || // 到底或遇到障礙或那條路走過了
				r[i][j] == 'R' )
				return false;
				
			else if( r[i][j] == 'G' ){ // 那條路沒找過的G
				if( visitted[i][j] != 'V' ) // 沒找過的G 
					foundNum++;
				visitted[i][j] = 'V';
				FindShortestRoute(r);
				if( foundNum == expectedNum ) // 找到數量到達期望數量，(一直true回去)結束遞迴 
					return true;
			}
			
			if( foundNum == 0 )
				visitted[i][j] = 'V';
			r[i][j] = 'R';
				
			if( toward == 'R' ){ // 右，下，上，倒退(左)
				if( ! Move2(i,j+1,'R',r) ){
					if( ! Move2(i+1,j,'D',r) ){
						if( ! Move2(i-1,j,'U',r) )
							return false;
					}
					else Move2(i-1,j,'U',r);
				}
				else Move2(i+1,j,'D',r);
			}
			
			else if( toward == 'D' ){ // 下，左，右，倒退(上)
				if( ! Move2(i+1,j,'D',r) ){
					if( ! Move2(i,j-1,'L',r) ){
						if( ! Move2(i,j+1,'R',r) )
							return false;
					}
					else Move2(i,j+1,'R',r);
				}
				else Move2(i,j-1,'L',r);
			}
			
			else if( toward == 'L' ){ // 左，上，下，倒退(右) 
				if( ! Move2(i,j-1,'L',r) ){
					if( ! Move2(i-1,j,'U',r) ){
						if( ! Move2(i+1,j,'D',r) )
							return false;
					}
					else Move2(i+1,j,'D',r);
				}
				else Move2(i-1,j,'U',r);
			}
			
			else if( toward == 'U' ){ // 上，右，左，倒退(下) 
				if( ! Move2(i-1,j,'U',r) ){
					if( ! Move2(i,j+1,'R',r) ){
						if( ! Move2(i,j-1,'L',r) )
							return false;
					}
					else Move2(i,j-1,'L',r);
				}
				else Move2(i,j+1,'R',r);
			}
			
			return true;	
		} // Move2()
		
		
		
		
		bool FindG(){			
			if( Move2(0,0,'R',maze) )
				return true;
			else
				return false;
		} // FindG()
	
	
	
	
		vector<vector<char>> GetMaze(){
			return maze;
		} // GetMaze()
		
		vector<vector<char>> GetMazeV(){
			return visitted;
		} // GetMazeV()
		
		vector<vector<char>> GetMazeR(){
			return shortestRoute;
		} // GetMazeR()
	
	
		
		
		void Print( vector<vector<char>> m ){
			for( int i = 0 ; i < x ; i++ ){ // row
				for( int j = 0 ; j < y ; j++ ) // column
					if( maze[i][j] == 'G' )
						cout << 'G';
					else cout << m[i][j];
				cout << endl;
			}
			cout << endl;
		} // Print()
		
		
		
		
		void Initialize(){
			for( int i = 0 ; i < x ; i++ ){
				maze[i].clear();
				visitted[i].clear();
				shortestRoute[i].clear();
				
			}
			maze.clear();
			visitted.clear();
			shortestRoute.clear();
			
			foundNum = 0;
			expectedNum = 1;
		} // Initialize()
	
}; // class Maze

	


int main(){
	Maze m;	
	
	while( m.GetCommand() ){ // 指令不是0(Quit) 	
		if( m.ReadFile( m.GetFileName() ) ) { // 成功讀取檔案	
			if( m.command == 2 )
				m.GetExpectedNum(); // 獲得G的期望數量
				 	
			if( m.FindG() ) {
				m.Print( m.GetMazeV() );
				m.Print( m.GetMazeR() );
			}
			else m.Print( m.GetMazeV() );
			
		}
		m.Initialize();		
	}
	
	system("pause");
} // main()
