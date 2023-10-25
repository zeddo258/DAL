// 11120103 游舒涵 

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;




class Maze{
	private:
		vector<vector<char>> maze, visitted, route;
		
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
			visitted = route = maze;
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
	
	

		
		bool Move2( int i, int j, char toward ){
			if( i < 0 || i >= x || j < 0 || j >= y || visitted[i][j] == 'O' || // 到底或遇到障礙或走過了
				( visitted[i][j] == 'V' && maze[i][j] != 'G' ) )
				return false;
				
			else if( visitted[i][j] == 'G' ){ // 沒走過的G 
				foundNum++;
				if( foundNum == expectedNum ) // 找到數量到達期望數量，(一直true回去)結束遞迴 
					return true;
			}
			
			visitted[i][j] = 'V';						
				
			if( toward == 'R' ){ // 右，下，上，倒退(左)
				if( ! Move2(i,j+1,'R') ){
					if( ! Move2(i+1,j,'D') ){
						if( ! Move2(i-1,j,'U') )
							return false;
					}
				}
			}
			
			else if( toward == 'D' ){ // 下，左，右，倒退(上) 
				if( ! Move2(i+1,j,'D') ){
					if( ! Move2(i,j-1,'L') ){
						if( ! Move2(i,j+1,'R') )
							return false;
					}
				}
			}
			
			else if( toward == 'L' ){ // 左，上，下，倒退(右) 
				if( ! Move2(i,j-1,'L') ){
					if( ! Move2(i-1,j,'U') ){
						if( ! Move2(i+1,j,'D') )
							return false;
					}
				}
			}
			
			else if( toward == 'U' ){ // 上，右，左，倒退(下) 
				if( ! Move2(i-1,j,'U') ){
					if( ! Move2(i,j+1,'R') ){
						if( ! Move2(i,j-1,'L') )
							return false;
					}
				}
			}
			
			route[i][j] = 'R';
			return true;	
		} // Move2()
		
		
		
		
		bool FindG(){			
			if( Move2(0,0,'R') )
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
			return route;
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
				route[i].clear();
				
			}
			maze.clear();
			visitted.clear();
			route.clear();
			
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





