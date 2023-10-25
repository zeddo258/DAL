// 11127237 �L�� 

#include<iostream>
#include<fstream>
#include <vector>

using namespace std ;


// ����h�ؼ�or��ؼмҦ� 
enum Modes {
	oneG,
	moreG
};

const int Dir[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} }; 

class Maze {
	
private:

	int N; // �ؼм� 
	int lenght, width; // ���P�e 
	vector< vector< char > > mazeMape; // �g�c�a��
	int G_num; //�ؼЭp���ܼ� 
	vector< pair<int, int> > visitedG; // ���LG���y��	
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
 		
	// �}�Ұg�c�ɮ׻P�إ߰g�c�a�� 
	bool load( string fileName, Modes mode ) {
		fileName = "input" + fileName + ".txt";
		ifstream openFile(fileName.c_str());
		
		if ( openFile.is_open()) {
			openFile >> width >> lenght;
			mazeMape.resize(lenght, vector<char>(width));
			N = 1; //�N�ؼЪ�l��1 
			G_num = 0; //�p�Ƭ�0 
			end = false; // ��l���_�]�P�_G���ᦳ�S�����^ 
 				
			// �p�Gcommand�ɿ�J��2�A�Ҧ��|�]�w���h�ӥؼ� 
			if ( mode == moreG ) {
				cout << endl << "input a  number: ";
				cin >> N;					
			}
			
			// �إ߰g�c�a�� 
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

    // �P�_G�O�_���L 
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
	


	// �P�_��V 
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
	
	// �P�_G����O�_������ 
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
		
	//�@���e�� 
	void Walk( Maze &vMaze, int x, int y, int dir ) {
		if ( vMaze.mazeMape[y][x] != 'G')
			vMaze.mazeMape[y][x] = 'V';
		if (vMaze.mazeMape[y][x] == 'G') {
			visitedG.push_back(make_pair(x, y));
			G_num++;
			end = end_G(vMaze,x,y,dir);
		}
					 
	}
	

	// �M��ؼ�
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
		
	// ��X�g�c�a��	
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
	
	// �M���a�� 
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

