// 王詩霈 11127238 
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

enum Modes {
	oneG,
	moreG,
};

class Maze{
private:
	int x;
	int y;
	int number;
	Modes mode;
	bool rule;  
	int direction;            // 紀錄走向 
	vector<vector<char > > array ;
	vector<vector<char > > array_V ;
	vector<vector<char > > array_R ;
	char arraysize;           // 陣列位址
	char aMaze;               // 存可行路徑
	char vMaze;               // 存走過路徑 
	
public:
	
	bool notout( int a, int b ) {
		if ( a >= 0 && a < y && b >= 0 && b < x )
			return true;
		return false;
	}
	
	bool load( string fileName, Modes num ){
		ifstream text;
		mode = num;
		text.open( fileName.c_str() );
		
		if(text.is_open()){
			char ch;
			text >> x >> y;
			for(int i=0;i<y;i++){    	// 輸入迷宮 
				vector<char> store;
				for(int j=0;j<x;j++){
					text >> ch;
					store.push_back(ch);
				}
				array.push_back(store);
			}
			array_V = array;
			array_R = array;
			return true;
		}
		else {
			cout << "Wrong filename!!!!!" << endl; 
			return false;
		}
		
		
	}
	
	
	void Course( int a, int b, int direction, bool & stop, int & goal ) {
		int number = goal;
		for( int i = 0; i < 4;) {  // 限制一個位置的轉彎次數 
			if ( direction == 0 ) 
				b++;
			else if ( direction == 1 ) 		
				a++;
			else if ( direction == 2 )
				b--;
			else if ( direction == 3 )
				a--;
			if ( notout( a, b ) && array_V[a][b] != 'V' && array_V[a][b] != 'O' ) { // 在迷宮內且不是V也不是O 
				if ( array_V[a][b] == 'G' )	{
					if ( goal > 0 ){
						goal--;
						if ( direction == 0 ) 
							b--;
						else if ( direction == 1 ) 		
							a--;
						else if ( direction == 2 )
							b++;
						else if ( direction == 3 )
							a++;	
						direction++;
						direction = direction % 4;  // 取餘數循環 
						Course( a, b, direction, stop , goal );
					}
					else {
						rule = true;
						stop = true;
						break;
					}
					
				}
				else {	
					array_V[a][b] = 'V';
				}		
				Course( a, b, direction, stop , goal );
			}
			else {
				
				if ( direction == 0 ) 
					b--;
				else if ( direction == 1 ) 		
					a--;
				else if ( direction == 2 )
					b++;
				else if ( direction == 3 )
					a++;	
				direction++;
				direction = direction % 4;
			}		
			i++;
			if( stop ) {
				if ( array_V[a][b] == 'V' ){
					array_R[a][b] = 'R';	
				}
					
				return;
				
			}
		}
	}
	
	void print( bool & find, int & lol ) {
		cout << endl;
		for(int i=0;i<y;i++){
			for(int j=0;j<x;j++){
				cout << array_V[i][j];
			}		
			cout << endl;
		}
		
		if ( find ) {   // 有找到目標就會印 
			cout << endl;
			for(int i=0;i<y;i++){
				for(int j=0;j<x;j++){
					cout << array_R[i][j];
				}		
				cout << endl;
			}
		}
		
	}
	
};

int main(int argc, char** argv) {
	int command = 0;
	int lol=0;

	do {
		Maze aMaze;
		Maze vMaze;
		int goal;
		int number;
		string fileName;
		Modes mode = oneG;
		bool find = false;
		bool rule = false;
		cout << endl << "*** Path Finding ***" ;
		cout << endl << "* 0. Quit          *" ;
		cout << endl << "* 1. One goal      *" ;
		cout << endl << "* 2. More goals    *" ; 
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2):" ;
		cin >> command;
		if ( command == 1 || command ==2 ){
			cout << endl << "Input a file number:";
			cin >> fileName;
			fileName ="input"+fileName+".txt";
			goal = 0;
			if ( command == 2 ){
				mode = moreG; 
				cout << endl << "Numbers of G (goals):" ;
				cin >> number;
				goal = number;
			} 
			if (aMaze.load(fileName, mode)){
				aMaze.Course( 0, -1, 0, find , goal );
				aMaze.print( find, lol );
			}
			
			else
			  break;
		}		
		else if ( !command ){
			break;
		}
		else{
			cout << endl << "Command does not exist!" << endl;
		}

	}while(true);
}
