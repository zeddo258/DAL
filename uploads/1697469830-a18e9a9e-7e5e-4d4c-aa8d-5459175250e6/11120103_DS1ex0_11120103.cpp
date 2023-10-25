// 11120103 ��β[ 

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;




class Maze{
	private:
		vector<vector<char>> maze, visitted, route;
		
	public:
		int command; // ���O 
		int x, y; // �g�c�j�p 
		int expectedNum = 1, foundNum = 0; // G������ƶq�A���ƶq  
	
	
	
	
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
			fin.open(fileName); // ���}�ɮ� 
			if( ! fin.is_open() ) { 
				cout << fileName << " does not exist!" << endl;
				return false;
			}
				
			string row, column;  // �g�c�j�p
			fin >> column >> row; 
			if( IsNumeric(row) && IsNumeric(column) &&
				0 < stoi(row) && 0 < stoi(column) ) { 
				x = stoi(row);
				y = stoi(column);
			}
			else return false; // ���b���� 
		
			maze.resize( x, vector<char>(y) ); // �إ߰g�c
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
	
	
	

		void GetExpectedNum(){ // ��oG������ƶq
			while( true ){
				string en; 
				cout << "Number of G (goals): ";
				cin >> en;
				cout << endl;
				if( IsNumeric(en) ){
					if( 1 <= stoi(en) && stoi(en) <= 100 ){ // �ݬ�1��100�����
						expectedNum = stoi(en);
						return;
					}
					else cout << "### The number must be in [1,100] ###" << endl;
				}
			}
		} // GetExpectedNum()
	
	

		
		bool Move2( int i, int j, char toward ){
			if( i < 0 || i >= x || j < 0 || j >= y || visitted[i][j] == 'O' || // �쩳�ιJ���ê�Ψ��L�F
				( visitted[i][j] == 'V' && maze[i][j] != 'G' ) )
				return false;
				
			else if( visitted[i][j] == 'G' ){ // �S���L��G 
				foundNum++;
				if( foundNum == expectedNum ) // ���ƶq��F����ƶq�A(�@��true�^�h)�������j 
					return true;
			}
			
			visitted[i][j] = 'V';						
				
			if( toward == 'R' ){ // �k�A�U�A�W�A�˰h(��)
				if( ! Move2(i,j+1,'R') ){
					if( ! Move2(i+1,j,'D') ){
						if( ! Move2(i-1,j,'U') )
							return false;
					}
				}
			}
			
			else if( toward == 'D' ){ // �U�A���A�k�A�˰h(�W) 
				if( ! Move2(i+1,j,'D') ){
					if( ! Move2(i,j-1,'L') ){
						if( ! Move2(i,j+1,'R') )
							return false;
					}
				}
			}
			
			else if( toward == 'L' ){ // ���A�W�A�U�A�˰h(�k) 
				if( ! Move2(i,j-1,'L') ){
					if( ! Move2(i-1,j,'U') ){
						if( ! Move2(i+1,j,'D') )
							return false;
					}
				}
			}
			
			else if( toward == 'U' ){ // �W�A�k�A���A�˰h(�U) 
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
	
	while( m.GetCommand() ){ // ���O���O0(Quit) 	
		if( m.ReadFile( m.GetFileName() ) ) { // ���\Ū���ɮ�	
			if( m.command == 2 )
				m.GetExpectedNum(); // ��oG������ƶq
				 	
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





