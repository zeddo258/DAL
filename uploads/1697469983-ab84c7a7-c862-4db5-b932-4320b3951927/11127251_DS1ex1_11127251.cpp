// 11127251 林柏安 

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
	
	vector<string> maze;  // 儲存迷宮 
	int countG; // 再 solveMaze 中記錄已經經過的目標數量 
	int findG; // 再 findGoals 中記錄已經經過的目標數量 
	bool check; // 再 findGoals 中紀錄遞迴回傳時是因為找到 G ( check = true ) 還是其他因素 ( check = false ) 
	
	// 初始化 
	void Initial() {
		countG = 0;
		findG = 0;
		check = false;
	}

	
	// 讀取檔案並且把迷宮存入 Vector maze 中 
	bool load( string fileName, Modes mode ) {
		
		fileName = "input"+fileName+".txt";
		ifstream file( fileName.c_str());
		
		// 確定檔案有開啟 
		if ( !file.is_open() ) {
			
			// 防呆機制 
			cout << endl << fileName << " does not exist!" << endl;
			return false;
			
		}
		
		// 新增字串變數讀取檔案資料 
		string line;
		getline( file, line ); // 讀取迷宮大小 
		
		// 讀取迷宮 
		while ( getline( file, line ) ) {
			
			// 寫入 Vector maze 中 
			maze.push_back( line );
			
		}
		
		// 關閉檔案讀取 
		file.close();
	}
	
	// 找到老鼠跑迷宮所經過的路徑 
	bool solveMaze( int x, int y, int nextStep, int target ) { // x, y 代表老鼠現在位置, nextStep 代表下一步的移動方向, target 代表需要經過的目標數量 
		
		// 直到找到的 G 等於目標數量 
		while ( countG != target ) {

			// 確認是否超出邊界, 超出邊界回傳 false 
			if ( x < 0 || y < 0 || x >= maze.size() || y >= maze[x].size() ) {
				return false;
			}
	
			// 確認是否找到 G, 如果找到 G 把 G 改成 A 並紀錄 
			if ( maze[x][y] == 'G' ) {
				countG += 1; 
				maze[x][y] = 'A';
			}
	
			// 確認是否撞到牆或者走到已經走過的路 
			if ( maze[x][y] == 'O' || maze[x][y] == 'V' ) {
				
				return false;
			}
	
	
			// 如果經過的路徑不是 G 或 A, 把當前位置改成 V 
			if ( maze[x][y] != 'G' && maze[x][y] != 'A' ) maze[x][y] = 'V';
		
			// 設定 for 迴圈紀錄座標四周是否有路可以走 
			for ( int way = 0; way < 4 ; )  {
				
				// 如果 nextStep % 4 == 0 且還沒確認完四周皆無路可走, 下一步往右走 
		    	if ( nextStep % 4 == 0 && way < 4 ) {
		    		
		    		// 往右走, 如果找到 G 回傳true 
			    	if ( solveMaze( x, y+1, nextStep, target ) ) {
			    		
					    return true;
					    
				    }
		
					// 沒有找到G, 把 nextStep + 1 , way + 1 
				    nextStep += 1;
			    	way++;
				
	    		}
	
				// 往下走 
			    if ( nextStep % 4 == 1 && way < 4 ) {
			    	
				    if ( solveMaze( x+1, y, nextStep, target ) ) {
					    return true;
			    	}
			
				    nextStep += 1;
				    way++;
			
	    		}
	
				// 往左走 
			    if ( nextStep % 4 == 2 && way < 4 ) {
			    	
				    if ( solveMaze( x, y-1, nextStep,target ) ) {
				    	
					    return true;
					    
			    	}
		
			    	nextStep += 1;
				    way++;
			
				}
	
				// 往上走 
			    if ( nextStep % 4 == 3 && way < 4 ) {
			    	
				    if ( solveMaze( x-1, y, nextStep, target ) ) {
				    	
				    	return true;
				    	
			    	}
			
			    	nextStep += 1;
				    way++;
		
			    }
	
	    	}
	
			// 四周都沒有路, 退回上一步 
			return false;
		}
	
		// 找到符合目標數量的 G  
		return true;
	}
	
	// 沿著先前的路徑( V )找出經過符合目標數量的 G 的路徑 
	bool findGoals( int x, int y, int nextStep, int target ) {
		
		while ( findG != target ) {
			
			if ( x < 0 || y < 0 || x >= maze.size() || y >= maze[x].size() ) {
				
				return false;
				
			}
	
			// 找到目標  
			if ( maze[x][y] == 'A' ) {
				
				findG += 1;
				maze[x][y] = 'G'; 
				check = true; // 設定 check 
				
				// 成功找到所有目標 
				if ( findG == target ) return true; 
				
			}
	
			// 如果撞到障礙物( O ) 已走過路徑( R ) 未探索的路徑( E ), 回傳 false 
			if ( maze[x][y] == 'O' || maze[x][y] == 'R' || maze[x][y] == 'E' ) {
		
				return false;
				
			}
			
			// 已經走過的目標且不是才剛經過的目標, 回傳 false 
			if ( maze[x][y] == 'G' && check == false ) {
				
				return false;
				
			}
	
	
			// 如果經過的點不是 G 或 A, 修改成 R 
			if ( maze[x][y] != 'G' && maze[x][y] != 'A' ) {
				
				check = false; // 確認已走到新的一條路, 把 check 設回 false 
				maze[x][y] = 'R';
				
			}
		
			for ( int way = 0; way < 4 ; )  {
				
				if ( findG == target ) break; // 找到所有目標 停止迴圈 
				
	    		if ( nextStep % 4 == 0 && way < 4 ) {
	    			
	    			// 往右走 
		    		if ( findGoals( x, y+1, nextStep, target ) ) {
		    			
			    		return true;
			    		
		    		}
		
			    	nextStep += 1;
			    	way++;
				
			    }
	
				// 往下走
			    if ( nextStep % 4 == 1 && way < 4 ) {
			    	
				    if ( findGoals( x+1, y, nextStep, target ) ) {
				    	
				    	return true;
				    	
		    		}
			
				    nextStep += 1;
				    way++;
		
			    }
			    
				// 往左走
		    	if ( nextStep % 4 == 2 && way < 4 ) {
		    		
			    	if ( findGoals( x, y-1, nextStep, target ) ) {
			    		
				    	return true;
				    	
			    	}
		
				    nextStep += 1;
				    way++;
		
				}
	
				// 往上走
		    	if ( nextStep % 4 == 3 && way < 4 ) {
		    		
			    	if ( findGoals( x-1, y, nextStep, target ) ) {
			    		
			    		return true;
			    		
			    	}
			    	
		
			    	nextStep += 1;
			    	way++;
		
		    	}
	
    		}
	
			// 走進死路 把先前改成 R 的 路徑設回 V  
			if ( maze[x][y] != 'G' && maze[x][y] != 'A' && check == false ) maze[x][y] = 'V';
			
			return false;
			
		}
	}
	
	// 顯示有經訪的路徑 
	void showV() {
		
		for ( int i = 0 ; i < maze.size() ; i ++ ) {
			
			for ( int j = 0 ; j < maze[i].size() ; j ++ ) {
				
				// 因為 solveMaze 把經過的 G 設定成 A, 故把目標鼎設定回來 
				if ( maze[i][j] == 'A' ) maze[i][j] = 'G';
				
				cout << maze[i][j];
				
			}
			
			cout << endl;
			
		}
		
		cout << endl;
		
	}
	
	// 顯示經過所有目標的路徑 
	void showR() {
		
		for ( int i = 0 ; i < maze.size() ; i ++ ) {
			
			for ( int j = 0 ; j < maze[i].size() ; j ++ ) {
				
				// 因為使用 solveMaze 產生的所經過路徑去使用, 故把沒經過的點 V 設回 E 
				if ( maze[i][j] == 'V' ) maze[i][j] = 'E';
				
				cout << maze[i][j];
				
			}
			
			cout << endl;
		}
		
		cout << endl;
		
	}
	
	// 清空迷宮 
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
		
		aMaze.Initial(); // 初始化 
		
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
				aMaze.solveMaze( 0, 0, 0, target ); // 完成老鼠跑迷宮 
				
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
			cout << endl <<"Command does not exist!" << endl; // 防呆機制 
		
			
	} while(true);
	
	system("pause");  //pause the execeution
	
	
	return 0;
} //end of main
