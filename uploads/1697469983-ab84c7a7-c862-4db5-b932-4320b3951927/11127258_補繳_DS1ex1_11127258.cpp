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

	// 更改地圖 
	void changemap( int x, int y, char ch ) {
		maze[x][y] = ch ;
	} // changemap
    
    // 印出地圖 
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
    vector< vector<char> > maze ; // 迷宮內容 
    int x ;
    int y ;

    void set_Maze(const string& fileName) {
        ifstream inputFile ;
   	    inputFile.open(fileName.c_str()) ;

        string line ;
   	    int number1, number2 ;
       	inputFile >> number1 >> number2 ;  // 輸入矩陣xy 

		// 迷宮矩陣大小 
   	    y = number1 ; // 行 
       	x = number2 ; // 列 
        
        inputFile.ignore() ; // 清除換行符
        
   	    while (getline(inputFile, line)) {
       	    vector<char> ch ;
           	for (int i = 0; i < line.length(); i++) {
           		ch.push_back(line[i]) ; // 將line一次存進ch中 
           	} // for
            
            maze.push_back(ch) ; // 在maze中存入vector<char> 形成陣列 
   	    } // while
		
 	   inputFile.close() ;
    } // set_Maze
    
};

void truepath(int goal, int& goal2) ; // 判斷是否為新路徑 
void updatewalk(int Now_x, int Now_y, int& time, vector<int>& walk_x, vector<int>& walk_y) ; // 更新走過路徑點 

int main() {
    
    int command = 0 ; // user command 

	do {
		ifstream inputFile ;
		int goal = 1 ; // G點數 
		int time = 0 ; // 行走次數 
		string fileName ; // .txtName 	
			
		cout << endl << "*** Path Finding ***" ;
		cout << endl << "* 0. Quit          *" ;
		cout << endl << "* 1. One goal      *" ;
		cout << endl << "* 2. More goals    *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2): " ;

		cin >> command ; //get the command
	
		if ((command == 1) || (command == 2)) {
			vector<int> walk_x ; // 曾走過的xy 
	    	vector<int> walk_y ;
			int Now_x = 0 ; // 老鼠當前位置xy
			int Now_y = 0 ; 
			
			walk_x.push_back(Now_x) ; // time=0 
			walk_y.push_back(Now_y) ;

			cout << endl << "Input a file number: " ;
			cin >> fileName ; // 輸入檔案名稱 
			
			fileName = "input" + fileName + ".txt" ; 
			
    	    inputFile.open(fileName.c_str()) ; 
        
        	if (!inputFile.is_open()) {
            	cout << "\n" << fileName << " does not exist!" << endl ;
            	continue ; // 重新輸入command 
        	} // if
			
			Maze maze1(fileName) ; // 路徑並保留G
			Maze maze2 = maze1 ; // 成功路徑 
			Maze maze0 = maze1 ; // 路徑全改為V	
			
			if (command == 2) {
				cout << "\nNumber of G (goals): " ;
				cin >> goal ; // 輸入G數量 
				while ((goal < 1) || (goal>100)) {
					cout << "\n### The number must be in [1,100] ###" << endl ;
					cout << "\nNumber of G (goals): " ;
					cin >> goal ; // 輸入G數量 
				} // while
			} // if
			
			int goal2 = goal ; // 記錄還剩多少目標 
			
			maze0.changemap( Now_x, Now_y, 'V' ) ;
			maze1.changemap( Now_x, Now_y, 'V' ) ;
			maze2.changemap( Now_x, Now_y, 'R' ) ;
			
			int direction = 0 ; // 0:右, 1:下, 2:左, 3:上
			int back = 0 ; // 計算旋轉次數 
			
			while ( goal > 0  ) {
		    	// 向右移動
				if (direction == 0 && Now_y+1 < maze0.get_y() && (maze0.getMap(Now_x, Now_y+1) == 'E' || maze0.getMap(Now_x, Now_y+1) == 'G')) {
					back = 0 ;
					Now_y++ ;
   					
   					truepath(goal, goal2) ;
   					updatewalk(Now_x, Now_y, time, walk_x, walk_y) ;
					
					if ( maze0.getMap(Now_x, Now_y) == 'G' ) {
						goal-- ; // 找到目標 
					}
					
					else {
						maze1.changemap( Now_x, Now_y, 'V' ) ;
						maze2.changemap( Now_x, Now_y, 'R' ) ;
					}
					
					maze0.changemap( Now_x, Now_y, 'V' ) ;
				} // 右移 
				
			 	// 向下移動
   				else if (direction == 1 && Now_x+1 < maze0.get_x() && (maze0.getMap(Now_x+1, Now_y) == 'E' || maze0.getMap(Now_x+1, Now_y) == 'G')) {
   					back = 0 ;
   					Now_x++ ;
   					
   					truepath(goal, goal2) ;
					updatewalk(Now_x, Now_y, time, walk_x, walk_y) ;
					
					if ( maze0.getMap(Now_x, Now_y) == 'G' ) {
						goal-- ; // 找到目標  
					}
					
					else {
						maze1.changemap( Now_x, Now_y, 'V' ) ;
						maze2.changemap( Now_x, Now_y, 'R' ) ;
					}
					
					maze0.changemap( Now_x, Now_y, 'V' ) ;
				} // 下移 
				
				// 向左移動
   				else if (direction == 2 && Now_y-1 >= 0 && (maze0.getMap(Now_x, Now_y-1) == 'E' || maze0.getMap(Now_x, Now_y-1) == 'G')) {
   					back = 0 ;
   					Now_y-- ;
   					
   					truepath(goal, goal2) ;
   					updatewalk(Now_x, Now_y, time, walk_x, walk_y) ;
					
					if ( maze0.getMap(Now_x, Now_y) == 'G' ) {
						goal-- ; // 找到目標  
					}
					
					else {
						maze1.changemap( Now_x, Now_y, 'V' ) ;
						maze2.changemap( Now_x, Now_y, 'R' ) ;
					}
					
					maze0.changemap( Now_x, Now_y, 'V' ) ;
		    	} // 左移 
				
				// 向上移動
    			else if (direction == 3 && Now_x-1 >= 0 && (maze0.getMap(Now_x-1, Now_y) == 'E' || maze0.getMap(Now_x-1, Now_y) == 'G')) {
    				back = 0 ;
    				Now_x-- ;
    	    		
    	    		truepath(goal, goal2) ;
					updatewalk(Now_x, Now_y, time, walk_x, walk_y) ;
    	    		
					if ( maze0.getMap(Now_x, Now_y) == 'G') {
						goal-- ; // 找到目標  
					}
					
					else {
						maze1.changemap( Now_x, Now_y, 'V' ) ;
						maze2.changemap( Now_x, Now_y, 'R' ) ;
					} 
					
					maze0.changemap( Now_x, Now_y, 'V' ) ;
	    		} // 上移			
				
				// 無法移動					
    			else {
    				// 旋轉方向 
    				if ( back != 4 ) {
    					direction = (direction + 1) % 4 ;  
    					back++ ;
    				} 
    				
    				// 四方皆不可動; back==4
    				else {
    					// 回到起始點(0,0) 
    					if ( Now_x == 0 && Now_y == 0 ) {
    						break ;
    					} 
    					
    					// 將R改回E // goal2 == goal路徑為錯 
    					if ( maze2.getMap(Now_x, Now_y) != 'G' && goal2 == goal ) {
	    					maze2.changemap( Now_x, Now_y, 'E' ) ;
	    				}
	    				
	    				back = 0 ;
	    				time-- ;
						Now_x = walk_x[time] ;  // 返回上一點 
    					Now_y = walk_y[time] ;
					} 
				} // 無法移動 
			} // while

	    	// 印出地走過路徑 
	    	maze1.printMap() ;
	    	
    		// 印出成功路徑 
    		if ( goal == 0 ) {
    			cout << endl ;
				maze2.printMap() ;
    		} // if
    		
			cout << endl ; 
		} // if( command==1or2)

		if ( command != 0 && command != 1 && command != 2 ) { // command輸入錯誤 
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
