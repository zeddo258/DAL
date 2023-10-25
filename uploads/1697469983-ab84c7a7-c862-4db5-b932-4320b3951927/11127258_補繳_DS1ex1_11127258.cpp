#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Maze {
public:
    Maze(const string& fileName) {
        set_Maze(fileName) ;
    } // Maze()

	// ���a�� 
	void changemap( int x, int y, char ch ) {
		maze[x][y] = ch ;
	} // changemap
    
    // �L�X�a�� 
    void printMap() {
        for (int i = 0; i < maze.size() ; i++) {
            for (int j = 0; j < maze[i].size() ; j++) {
			    cout << maze[i][j] ;
            } // for
            
            cout << endl ;
        } // for
    } // printMap
    
    int get_x() {
    	return x ;
    } // get_x
    
    int get_y() {
    	return y ;
    } // get_y
    
    char getMap( int x, int y ) {
		return maze[x][y] ;
    } // getMap

private:
    vector< vector<char> > maze ; // �g�c���e 
    int x ;
    int y ;

    void set_Maze(const string& fileName) {
        ifstream inputFile ;
   	    inputFile.open(fileName.c_str()) ;

        string line ;
   	    int number1, number2 ;
       	inputFile >> number1 >> number2 ;  // ��J�x�}xy 

		// �g�c�x�}�j�p 
   	    y = number1 ; // �� 
       	x = number2 ; // �C 
        
        inputFile.ignore() ; // �M�������
        
   	    while (getline(inputFile, line)) {
       	    vector<char> ch ;
           	for (int i = 0; i < line.length(); i++) {
           		ch.push_back(line[i]) ; // �Nline�@���s�ich�� 
           	} // for
            
            maze.push_back(ch) ; // �bmaze���s�Jvector<char> �Φ��}�C 
   	    } // while
		
 	   inputFile.close() ;
    } // set_Maze
    
};

void truepath(int goal, int& goal2) ; // �P�_�O�_���s���| 
void updatewalk(int Now_x, int Now_y, int& time, vector<int>& walk_x, vector<int>& walk_y) ; // ��s���L���|�I 

int main() {
    
    int command = 0 ; // user command 

	do {
		ifstream inputFile ;
		int goal = 1 ; // G�I�� 
		int time = 0 ; // �樫���� 
		string fileName ; // .txtName 	
			
		cout << endl << "*** Path Finding ***" ;
		cout << endl << "* 0. Quit          *" ;
		cout << endl << "* 1. One goal      *" ;
		cout << endl << "* 2. More goals    *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2): " ;

		cin >> command ; //get the command
	
		if ((command == 1) || (command == 2)) {
			vector<int> walk_x ; // �����L��xy 
	    	vector<int> walk_y ;
			int Now_x = 0 ; // �ѹ���e��mxy
			int Now_y = 0 ; 
			
			walk_x.push_back(Now_x) ; // time=0 
			walk_y.push_back(Now_y) ;

			cout << endl << "Input a file number: " ;
			cin >> fileName ; // ��J�ɮצW�� 
			
			fileName = "input" + fileName + ".txt" ; 
			
    	    inputFile.open(fileName.c_str()) ; 
        
        	if (!inputFile.is_open()) {
            	cout << "\n" << fileName << " does not exist!" << endl ;
            	continue ; // ���s��Jcommand 
        	} // if
			
			Maze maze1(fileName) ; // ���|�ëO�dG
			Maze maze2 = maze1 ; // ���\���| 
			Maze maze0 = maze1 ; // ���|���אּV	
			
			if (command == 2) {
				cout << "\nNumber of G (goals): " ;
				cin >> goal ; // ��JG�ƶq 
				while ((goal < 1) || (goal>100)) {
					cout << "\n### The number must be in [1,100] ###" << endl ;
					cout << "\nNumber of G (goals): " ;
					cin >> goal ; // ��JG�ƶq 
				} // while
			} // if
			
			int goal2 = goal ; // �O���ٳѦh�֥ؼ� 
			
			maze0.changemap( Now_x, Now_y, 'V' ) ;
			maze1.changemap( Now_x, Now_y, 'V' ) ;
			maze2.changemap( Now_x, Now_y, 'R' ) ;
			
			int direction = 0 ; // 0:�k, 1:�U, 2:��, 3:�W
			int back = 0 ; // �p����স�� 
			
			while ( goal > 0  ) {
		    	// �V�k����
				if (direction == 0 && Now_y+1 < maze0.get_y() && (maze0.getMap(Now_x, Now_y+1) == 'E' || maze0.getMap(Now_x, Now_y+1) == 'G')) {
					back = 0 ;
					Now_y++ ;
   					
   					truepath(goal, goal2) ;
   					updatewalk(Now_x, Now_y, time, walk_x, walk_y) ;
					
					if ( maze0.getMap(Now_x, Now_y) == 'G' ) {
						goal-- ; // ���ؼ� 
					}
					
					else {
						maze1.changemap( Now_x, Now_y, 'V' ) ;
						maze2.changemap( Now_x, Now_y, 'R' ) ;
					}
					
					maze0.changemap( Now_x, Now_y, 'V' ) ;
				} // �k�� 
				
			 	// �V�U����
   				else if (direction == 1 && Now_x+1 < maze0.get_x() && (maze0.getMap(Now_x+1, Now_y) == 'E' || maze0.getMap(Now_x+1, Now_y) == 'G')) {
   					back = 0 ;
   					Now_x++ ;
   					
   					truepath(goal, goal2) ;
					updatewalk(Now_x, Now_y, time, walk_x, walk_y) ;
					
					if ( maze0.getMap(Now_x, Now_y) == 'G' ) {
						goal-- ; // ���ؼ�  
					}
					
					else {
						maze1.changemap( Now_x, Now_y, 'V' ) ;
						maze2.changemap( Now_x, Now_y, 'R' ) ;
					}
					
					maze0.changemap( Now_x, Now_y, 'V' ) ;
				} // �U�� 
				
				// �V������
   				else if (direction == 2 && Now_y-1 >= 0 && (maze0.getMap(Now_x, Now_y-1) == 'E' || maze0.getMap(Now_x, Now_y-1) == 'G')) {
   					back = 0 ;
   					Now_y-- ;
   					
   					truepath(goal, goal2) ;
   					updatewalk(Now_x, Now_y, time, walk_x, walk_y) ;
					
					if ( maze0.getMap(Now_x, Now_y) == 'G' ) {
						goal-- ; // ���ؼ�  
					}
					
					else {
						maze1.changemap( Now_x, Now_y, 'V' ) ;
						maze2.changemap( Now_x, Now_y, 'R' ) ;
					}
					
					maze0.changemap( Now_x, Now_y, 'V' ) ;
		    	} // ���� 
				
				// �V�W����
    			else if (direction == 3 && Now_x-1 >= 0 && (maze0.getMap(Now_x-1, Now_y) == 'E' || maze0.getMap(Now_x-1, Now_y) == 'G')) {
    				back = 0 ;
    				Now_x-- ;
    	    		
    	    		truepath(goal, goal2) ;
					updatewalk(Now_x, Now_y, time, walk_x, walk_y) ;
    	    		
					if ( maze0.getMap(Now_x, Now_y) == 'G') {
						goal-- ; // ���ؼ�  
					}
					
					else {
						maze1.changemap( Now_x, Now_y, 'V' ) ;
						maze2.changemap( Now_x, Now_y, 'R' ) ;
					} 
					
					maze0.changemap( Now_x, Now_y, 'V' ) ;
	    		} // �W��			
				
				// �L�k����					
    			else {
    				// �����V 
    				if ( back != 4 ) {
    					direction = (direction + 1) % 4 ;  
    					back++ ;
    				} 
    				
    				// �|��Ҥ��i��; back==4
    				else {
    					// �^��_�l�I(0,0) 
    					if ( Now_x == 0 && Now_y == 0 ) {
    						break ;
    					} 
    					
    					// �NR��^E // goal2 == goal���|���� 
    					if ( maze2.getMap(Now_x, Now_y) != 'G' && goal2 == goal ) {
	    					maze2.changemap( Now_x, Now_y, 'E' ) ;
	    				}
	    				
	    				back = 0 ;
	    				time-- ;
						Now_x = walk_x[time] ;  // ��^�W�@�I 
    					Now_y = walk_y[time] ;
					} 
				} // �L�k���� 
			} // while

	    	// �L�X�a���L���| 
	    	maze1.printMap() ;
	    	
    		// �L�X���\���| 
    		if ( goal == 0 ) {
    			cout << endl ;
				maze2.printMap() ;
    		} // if
    		
			cout << endl ; 
		} // if( command==1or2)

		if ( command != 0 && command != 1 && command != 2 ) { // command��J���~ 
			cout << endl << "Command does not exist!" << endl ;
		} // if 

	} while ( command != 0 ) ; 
	
	system ("pause") ; //pause the execution

	return 0 ; 
} // main

void truepath(int goal, int& goal2) {
  	if (goal2 > goal) {
		goal2-- ;
	}
} // truepath

void updatewalk(int Now_x, int Now_y, int& time, vector<int>& walk_x, vector<int>& walk_y) {
	time++ ;
	walk_x.insert(walk_x.begin()+time, Now_x) ;
	walk_y.insert(walk_y.begin()+time, Now_y) ;
} // updatewalk
