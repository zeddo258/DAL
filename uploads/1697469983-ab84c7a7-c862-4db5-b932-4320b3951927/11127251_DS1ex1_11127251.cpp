// 11127251 �L�f�w 

#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <sstream>

using namespace std;

enum Modes {
	oneG,
	moreG
};


class Maze{
public:
	
	vector<string> maze;  // �x�s�g�c 
	int countG; // �A solveMaze ���O���w�g�g�L���ؼмƶq 
	int findG; // �A findGoals ���O���w�g�g�L���ؼмƶq 
	bool check; // �A findGoals ���������j�^�ǮɬO�]����� G ( check = true ) �٬O��L�]�� ( check = false ) 
	
	// ��l�� 
	void Initial() {
		countG = 0;
		findG = 0;
		check = false;
	}

	
	// Ū���ɮרåB��g�c�s�J Vector maze �� 
	bool load( string fileName, Modes mode ) {
		
		fileName = "input"+fileName+".txt";
		ifstream file( fileName.c_str());
		
		// �T�w�ɮצ��}�� 
		if ( !file.is_open() ) {
			
			// ���b���� 
			cout << endl << fileName << " does not exist!" << endl;
			return false;
			
		}
		
		// �s�W�r���ܼ�Ū���ɮ׸�� 
		string line;
		getline( file, line ); // Ū���g�c�j�p 
		
		// Ū���g�c 
		while ( getline( file, line ) ) {
			
			// �g�J Vector maze �� 
			maze.push_back( line );
			
		}
		
		// �����ɮ�Ū�� 
		file.close();
	}
	
	// ���ѹ��]�g�c�Ҹg�L�����| 
	bool solveMaze( int x, int y, int nextStep, int target ) { // x, y �N��ѹ��{�b��m, nextStep �N��U�@�B�����ʤ�V, target �N��ݭn�g�L���ؼмƶq 
		
		// �����쪺 G ����ؼмƶq 
		while ( countG != target ) {

			// �T�{�O�_�W�X���, �W�X��ɦ^�� false 
			if ( x < 0 || y < 0 || x >= maze.size() || y >= maze[x].size() ) {
				return false;
			}
	
			// �T�{�O�_��� G, �p�G��� G �� G �令 A �ì��� 
			if ( maze[x][y] == 'G' ) {
				countG += 1; 
				maze[x][y] = 'A';
			}
	
			// �T�{�O�_������Ϊ̨���w�g���L���� 
			if ( maze[x][y] == 'O' || maze[x][y] == 'V' ) {
				
				return false;
			}
	
	
			// �p�G�g�L�����|���O G �� A, ���e��m�令 V 
			if ( maze[x][y] != 'G' && maze[x][y] != 'A' ) maze[x][y] = 'V';
		
			// �]�w for �j������y�Х|�P�O�_�����i�H�� 
			for ( int way = 0; way < 4 ; )  {
				
				// �p�G nextStep % 4 == 0 �B�٨S�T�{���|�P�ҵL���i��, �U�@�B���k�� 
		    	if ( nextStep % 4 == 0 && way < 4 ) {
		    		
		    		// ���k��, �p�G��� G �^��true 
			    	if ( solveMaze( x, y+1, nextStep, target ) ) {
			    		
					    return true;
					    
				    }
		
					// �S�����G, �� nextStep + 1 , way + 1 
				    nextStep += 1;
			    	way++;
				
	    		}
	
				// ���U�� 
			    if ( nextStep % 4 == 1 && way < 4 ) {
			    	
				    if ( solveMaze( x+1, y, nextStep, target ) ) {
					    return true;
			    	}
			
				    nextStep += 1;
				    way++;
			
	    		}
	
				// ������ 
			    if ( nextStep % 4 == 2 && way < 4 ) {
			    	
				    if ( solveMaze( x, y-1, nextStep,target ) ) {
				    	
					    return true;
					    
			    	}
		
			    	nextStep += 1;
				    way++;
			
				}
	
				// ���W�� 
			    if ( nextStep % 4 == 3 && way < 4 ) {
			    	
				    if ( solveMaze( x-1, y, nextStep, target ) ) {
				    	
				    	return true;
				    	
			    	}
			
			    	nextStep += 1;
				    way++;
		
			    }
	
	    	}
	
			// �|�P���S����, �h�^�W�@�B 
			return false;
		}
	
		// ���ŦX�ؼмƶq�� G  
		return true;
	}
	
	// �u�ۥ��e�����|( V )��X�g�L�ŦX�ؼмƶq�� G �����| 
	bool findGoals( int x, int y, int nextStep, int target ) {
		
		while ( findG != target ) {
			
			if ( x < 0 || y < 0 || x >= maze.size() || y >= maze[x].size() ) {
				
				return false;
				
			}
	
			// ���ؼ�  
			if ( maze[x][y] == 'A' ) {
				
				findG += 1;
				maze[x][y] = 'G'; 
				check = true; // �]�w check 
				
				// ���\���Ҧ��ؼ� 
				if ( findG == target ) return true; 
				
			}
	
			// �p�G�����ê��( O ) �w���L���|( R ) �����������|( E ), �^�� false 
			if ( maze[x][y] == 'O' || maze[x][y] == 'R' || maze[x][y] == 'E' ) {
		
				return false;
				
			}
			
			// �w�g���L���ؼХB���O�~��g�L���ؼ�, �^�� false 
			if ( maze[x][y] == 'G' && check == false ) {
				
				return false;
				
			}
	
	
			// �p�G�g�L���I���O G �� A, �ק令 R 
			if ( maze[x][y] != 'G' && maze[x][y] != 'A' ) {
				
				check = false; // �T�{�w����s���@����, �� check �]�^ false 
				maze[x][y] = 'R';
				
			}
		
			for ( int way = 0; way < 4 ; )  {
				
				if ( findG == target ) break; // ���Ҧ��ؼ� ����j�� 
				
	    		if ( nextStep % 4 == 0 && way < 4 ) {
	    			
	    			// ���k�� 
		    		if ( findGoals( x, y+1, nextStep, target ) ) {
		    			
			    		return true;
			    		
		    		}
		
			    	nextStep += 1;
			    	way++;
				
			    }
	
				// ���U��
			    if ( nextStep % 4 == 1 && way < 4 ) {
			    	
				    if ( findGoals( x+1, y, nextStep, target ) ) {
				    	
				    	return true;
				    	
		    		}
			
				    nextStep += 1;
				    way++;
		
			    }
			    
				// ������
		    	if ( nextStep % 4 == 2 && way < 4 ) {
		    		
			    	if ( findGoals( x, y-1, nextStep, target ) ) {
			    		
				    	return true;
				    	
			    	}
		
				    nextStep += 1;
				    way++;
		
				}
	
				// ���W��
		    	if ( nextStep % 4 == 3 && way < 4 ) {
		    		
			    	if ( findGoals( x-1, y, nextStep, target ) ) {
			    		
			    		return true;
			    		
			    	}
			    	
		
			    	nextStep += 1;
			    	way++;
		
		    	}
	
    		}
	
			// ���i���� ����e�令 R �� ���|�]�^ V  
			if ( maze[x][y] != 'G' && maze[x][y] != 'A' && check == false ) maze[x][y] = 'V';
			
			return false;
			
		}
	}
	
	// ��ܦ��g�X�����| 
	void showV() {
		
		for ( int i = 0 ; i < maze.size() ; i ++ ) {
			
			for ( int j = 0 ; j < maze[i].size() ; j ++ ) {
				
				// �]�� solveMaze ��g�L�� G �]�w�� A, �G��ؼй��]�w�^�� 
				if ( maze[i][j] == 'A' ) maze[i][j] = 'G';
				
				cout << maze[i][j];
				
			}
			
			cout << endl;
			
		}
		
		cout << endl;
		
	}
	
	// ��ܸg�L�Ҧ��ؼЪ����| 
	void showR() {
		
		for ( int i = 0 ; i < maze.size() ; i ++ ) {
			
			for ( int j = 0 ; j < maze[i].size() ; j ++ ) {
				
				// �]���ϥ� solveMaze ���ͪ��Ҹg�L���|�h�ϥ�, �G��S�g�L���I V �]�^ E 
				if ( maze[i][j] == 'V' ) maze[i][j] = 'E';
				
				cout << maze[i][j];
				
			}
			
			cout << endl;
		}
		
		cout << endl;
		
	}
	
	// �M�Űg�c 
	void clr() {
		
		maze.clear();
		
	}
	
};


// Path finding for one or more goals in a maze
int main(void) {
	int command = 0; // user command 

	do {
		Maze aMaze;         // a matrix 
		string fileName;    // a file name
		Modes mode = oneG;  // default: one goal
		int target = 1;
		
		aMaze.Initial(); // ��l�� 
		
		cout << endl << "*** Path Finding ***";
		cout << endl << "* 0. Quit          *";
		cout << endl << "* 1. One goal      *";
		cout << endl << "* 2. More goals    *";
		cout << endl << "********************";
		cout << endl << "Input a command(0, 1, 2): ";
		cin >> command;
		
		
		if ( (command == 1 ) || (command == 2) ) {
			
			cout << endl << "Input a file number: ";
			cin >> fileName;  // get the command
			
			if (command == 2) {
				mode = moreG; // one or more goals
				cout << endl << "Number of G (goals): ";
				cin >> target; // get the Number of goals 
			}
			
			if ( aMaze.load(fileName, mode) ) {  // load the original matrix
				aMaze.solveMaze( 0, 0, 0, target ); // �����ѹ��]�g�c 
				
				Maze vMaze(aMaze);  // a copy to keep the visited cells
				
				bool success = aMaze.findGoals( 0, 0, 0, target );  // find a path to goal(s)
				
				mode = oneG;   // reset to default
				vMaze.showV();  // show on screen the visited cells
				
				if (success)   // to check if the goal is reached or not
					aMaze.showR(); // show on screen the route to reach the goal
					
				vMaze.clr();  // clear up the copy
			}
			
			aMaze.clr();  // clear up the original matrix
			
		}
		else if (!command)  // '0' : stop the program
			break;
		else
			cout << endl <<"Command does not exist!" << endl; // ���b���� 
		
			
	} while(true);
	
	system("pause");  //pause the execeution
	
	
	return 0;
} //end of main
