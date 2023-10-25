// 11127130 蔡淳全  
# include <iostream>                            // cin, cout, system...
# include <stdio.h>                             // printf, scanf, FILE...
# include <string.h>                            // strcpy(), strcat()...

using namespace std;                            // 使用標準命名空間 

typedef char Char40[40];                        // 定義40格的字元陣列為Char40 


class Maze {
	public:
		Maze() {}                               // Default constructor
		
		Maze(const Maze& aMaze) {               // Declare copy constructor
			mazerow = aMaze.mazerow;            // copy mazerow
			mazecolumn = aMaze.mazecolumn;      // copy mazecolumn
			goals = aMaze.goals;                // copy goals
			shortestPathLength = aMaze.shortestPathLength;
			char **ptr = aMaze.mazeptr;         // 建立一個指標指向原迷宮  
			 
			// 建立新的動態陣列(用mazeptr指向)，並把舊的迷宮資訊複製到此陣列 
			mazeptr = new char *[mazerow];
			for (int i = 0; i < mazerow; i++) {
				mazeptr[i] = new char[mazecolumn + 2]; // mazecolumn + 2是因為要放換行字元和空字元 
				strcpy(mazeptr[i], ptr[i]);
			}
			
			ptr = NULL;                         // 將ptr接地 
		}
		
		bool load(Char40 fileName, int goalNum) {
			FILE * fp;                          
		    Char40 completeFileName;
		    strcpy(completeFileName, "input");
		    strcat(completeFileName, fileName);
		    strcat(completeFileName, ".txt");   // completeFileName = "input{fileName}.txt"
		    fp = fopen(completeFileName, "r");  // 打開一個用於讀取的文件，該文件必須存在  
						
			if (fp == NULL) {                   // 讀檔失敗 
				printf("\ninput%s.txt does not exist!\n", fileName);
				return false;
			}
			
			Char40 line;
			int row, column;                    // row:列, column:行 
			fscanf(fp, "%d %d", &column, &row); // 讀取迷宮行列數 
			fgets(line, 40, fp);                // 把第一行讀完 
			mazerow = row;                      // 設定privat變數 mazerow
			mazecolumn = column;                // 設定privat變數 mazecolumn
			
			char **ptr = new char *[row];       // 建立動態陣列 row * column
			for (int i = 0; i < row; i++) {
				ptr[i] = new char[column + 2];  // column + 2是因為要放換行字元和空字元  
				fgets(line, column + 2, fp);    // n = column + 2是因為fgets在讀到n - 1個字元時會停止，要讓它讀到換行字元 
				strcpy(ptr[i], line);           // 將讀到的迷宮資訊存進動態陣列 
			}
			
			mazeptr = ptr;                      // 設定privat指標 mazeptr
			ptr = NULL;                         // 將ptr接地 
			goals = goalNum;                    // 設定privat變數 goals 
			shortestPathLength = 99999;         // 設定privat變數 shortestPathLength，
			                                    // 初始值給很大，這樣找到第一條路徑時就會更改shortestPathLength值 
			
			fclose(fp);                         // 關閉文件 
			return true;
		}
		
		void show() {                           // 印出迷宮矩陣 
			for (int i = 0; i < mazerow; i++) {
				for (int j = 0; j < mazecolumn; j++) {
					printf("%c", mazeptr[i][j]);
				}
				
				printf("\n");                   // 印完一列換一行 
			}
		}
 
		bool findGoals(Maze& vMaze, int row, int column, int dir) {
			// right:dir == 1, down:dir == 2, left:dir == 3, up:dir == 4
			if (vMaze.mazeptr[row][column] == 'E' || vMaze.mazeptr[row][column] == 'G') {
				if (vMaze.mazeptr[row][column] == 'E')                // 若是通路 
					vMaze.mazeptr[row][column] = 'V';                 // 紀錄走過的路為V 
				else if (vMaze.mazeptr[row][column] == 'G') {         // 若是目標 
					goals -= 1;                                       // 剩餘目標數減1 
					if (goals == 0)	return true;                      // 若剩餘目標數為0，則為遞迴終點return true 
				}
				
				if (dir == 1) {                                       // 面向右邊 
					if (column < mazecolumn - 1)                      // 不在迷宮最右 
						if (goRight(vMaze, row, column)) return true; // 向右走，找到所有目標就return true 
							                            
					if (row < mazerow - 1)                            // 不在迷宮最下 
						if (goDown(vMaze, row, column)) return true;  // 向下走，找到所有目標就return true  
						
					if (row > 0)                                      // 不在迷宮最上 
						if (goUp(vMaze, row, column)) return true;    // 向上走，找到所有目標就return true
				}
				else if (dir == 2) {                                  // 面向下面 
					if (row < mazerow - 1)                            // 不在迷宮最下 
						if (goDown(vMaze, row, column)) return true;  // 向下走，找到所有目標就return true
					
					if (column > 0)                                   // 不在迷宮最左 
						if (goLeft(vMaze, row, column)) return true;  // 向左走，找到所有目標就return true 
						
					if (column < mazecolumn - 1)                      // 不在迷宮最右 
						if (goRight(vMaze, row, column)) return true; // 向右走，找到所有目標就return true					
				}
				else if (dir == 3) {                                  // 面向左邊 
					if (column > 0)                                   // 不在迷宮最左 
						if (goLeft(vMaze, row, column)) return true;  // 向左走，找到所有目標就return true
					
					if (row > 0)                                      // 不在迷宮最上 
						if (goUp(vMaze, row, column)) return true;    // 向上走，找到所有目標就return true
					
					if (row < mazerow - 1)                            // 不在迷宮最下 
						if (goDown(vMaze, row, column)) return true;  // 向下走，找到所有目標就return true			
				}
				else if (dir == 4) {                                  // 面向上面 
					if (row > 0)                                      // 不在迷宮最上 
						if (goUp(vMaze, row, column)) return true;    // 向上走，找到所有目標就return true
					
					if (column < mazecolumn - 1)                      // 不在迷宮最右 
						if (goRight(vMaze, row, column)) return true; // 向右走，找到所有目標就return true		
					
					if (column > 0)                                   // 不在迷宮最左 
						if (goLeft(vMaze, row, column)) return true;  // 向左走，找到所有目標就return true									
				}
				
				return false;  // 尚未找到足夠目標數 
			}			
			else return false; // 遇到障礙物或已走過的路 
		} 
		
		bool findShortestPath(Maze& vMaze, Maze& rMaze, int row, int column, int dir, int path) {
			// right:dir == 1, down:dir == 2, left:dir == 3, up:dir == 4
			bool success = false;     // 有無成功找到目標 
			bool returnValue = false; // 遞迴回傳值 
			path++;                   // 每遞迴一次，路徑就+1 
			if (mazeptr[row][column] == 'E' || mazeptr[row][column] == 'G') { 
				if (path == shortestPathLength || path > (mazerow  * mazecolumn)) {
					// 如果路徑等於目前最短路徑 或 路徑大於整個迷宮格數 
					return false; // 就不繼續遞迴 
				} 
				
				if (mazeptr[row][column] == 'E') {    // 若是通路 
					vMaze.mazeptr[row][column] = 'V'; // 紀錄走過的路為V 
				} 
				
				if (mazeptr[row][column] == 'G') {              // 若是目標 			
					if (path < shortestPathLength) {            // 且路徑小於目前最短路徑 
						shortestPathLength = path;              // 更新目前最短路徑長 
						char **ptr = new char *[mazerow];       // 建立新的動態陣列 mazerow * mazecolumn
						for (int i = 0; i < mazerow; i++) {
							ptr[i] = new char[mazecolumn + 2];  // mazecolumn + 2是因為要放換行字元和空字元   
							strcpy(ptr[i], mazeptr[i]);         // 將原始迷宮資訊存進動態陣列 
						}
						
						// 刪除rMaze原本存的最短路徑圖(因為最短路徑變了) 
						for (int i = 0; i < mazerow; i++) {
							delete[] rMaze.mazeptr[i];          // 先一列一列刪除迷宮 
						}		
						
						delete [] rMaze.mazeptr;                // 再刪除指標陣列 
						
						rMaze.mazeptr = ptr;                    // 將rMaze迷宮指標指向新的最短路徑圖 
						ptr = NULL;                             // 將ptr接地 
					}
					
					goals = 0;                                  // 剩餘目標數設為0(因為總共只有一個目標) 
					return true;                                // 走到目標，遞迴終點return true 
				}
				
				if (dir == 1) {                                                             // 面向右邊                               
					if (column < mazecolumn - 1) {                                          // 不在最右 
						success = findShortestPath(vMaze, rMaze, row, column + 1, 1, path); // 向右找目標 
						if (success) {                                                      // 若成功找到目標 
							returnValue = success;                                          // 設定回傳值 
							rMaze.mazeptr[row][column] = 'R';                               // 在路徑圖上紀錄路徑R 
						}
					}
							                            
					if (row < mazerow - 1) {                                                // 不在最下  
						success = findShortestPath(vMaze, rMaze, row + 1, column, 2, path); // 向下找目標                         
						if (success) {                                                      // 若成功找到目標 
							returnValue = success;                                          // 設定回傳值 
							rMaze.mazeptr[row][column] = 'R';                               // 在路徑圖上紀錄路徑R 
						}
					}
						
					if (row > 0) {                                                          // 不在最上  
						success = findShortestPath(vMaze, rMaze, row - 1, column, 4, path); // 向上找目標  
						if (success) {                                                      // 若成功找到目標 
							returnValue = success;                                          // 設定回傳值 
							rMaze.mazeptr[row][column] = 'R';                               // 在路徑圖上紀錄路徑R 
						}                               
					}
					
					return returnValue;	   
				}
				else if (dir == 2) {                                 
					if (row < mazerow - 1) {                                                // 不在最下  
						success = findShortestPath(vMaze, rMaze, row + 1, column, 2, path); // 向下找目標                          
						if (success) {                                                      // 若成功找到目標 
							returnValue = success;                                          // 設定回傳值 
							rMaze.mazeptr[row][column] = 'R';                               // 在路徑圖上紀錄路徑R 
						}
					}
					
					if (column > 0) {                                                       // 不在最左 
						success = findShortestPath(vMaze, rMaze, row, column - 1, 3, path); // 向左找目標                             
						if (success) {                                                      // 若成功找到目標 
							returnValue = success;                                          // 設定回傳值 
							rMaze.mazeptr[row][column] = 'R';                               // 在路徑圖上紀錄路徑R 
						}
					}
						
					if (column < mazecolumn - 1) {                                          // 不在最右  
						success = findShortestPath(vMaze, rMaze, row, column + 1, 1, path); // 向右找目標                   
						if (success) {                                                      // 若成功找到目標 
							returnValue = success;                                          // 設定回傳值 
							rMaze.mazeptr[row][column] = 'R';                               // 在路徑圖上紀錄路徑R 
						}
					}
					 
					return returnValue;					
				}
				else if (dir == 3) {                                 
					if (column > 0) {                                                       // 不在最左 
						success = findShortestPath(vMaze, rMaze, row, column - 1, 3, path); // 向左找目標                               
						if (success) {                                                      // 若成功找到目標 
							returnValue = success;                                          // 設定回傳值 
							rMaze.mazeptr[row][column] = 'R';                               // 在路徑圖上紀錄路徑R 
						}
					}
					
					if (row > 0) {                                                          // 不在最上  
						success = findShortestPath(vMaze, rMaze, row - 1, column, 4, path); // 向上找目標                               
						if (success) {                                                      // 若成功找到目標 
							returnValue = success;                                          // 設定回傳值 
							rMaze.mazeptr[row][column] = 'R';                               // 在路徑圖上紀錄路徑R 
						}
					}
					
					if (row < mazerow - 1) {                                                // 不在最下  
						success = findShortestPath(vMaze, rMaze, row + 1, column, 2, path); // 向下找目標          
						if (success) {                                                      // 若成功找到目標 
							returnValue = success;                                          // 設定回傳值 
							rMaze.mazeptr[row][column] = 'R';                               // 在路徑圖上紀錄路徑R 
						}
					}
					
					return returnValue;  			
				}
				else if (dir == 4) {                                
					if (row > 0) {                                                          // 不在最上  
						success = findShortestPath(vMaze, rMaze, row - 1, column, 4, path); // 向上找目標                               
						if (success) {                                                      // 若成功找到目標 
							returnValue = success;                                          // 設定回傳值 
							rMaze.mazeptr[row][column] = 'R';                               // 在路徑圖上紀錄路徑R 
						}
					}
					
					if (column < mazecolumn - 1) {                                          // 不在最右  
						success = findShortestPath(vMaze, rMaze, row, column + 1, 1, path); // 向右找目標                     
						if (success) {                                                      // 若成功找到目標 
							returnValue = success;                                          // 設定回傳值 
							rMaze.mazeptr[row][column] = 'R';                               // 在路徑圖上紀錄路徑R 
						}
					}
					
					if (column > 0) {                                                       // 不在最左 
						success = findShortestPath(vMaze, rMaze, row, column - 1, 3, path); // 向左找目標   
						if (success) {                                                      // 若成功找到目標 
							returnValue = success;                                          // 設定回傳值 
							rMaze.mazeptr[row][column] = 'R';                               // 在路徑圖上紀錄路徑R 
						}
					}
					
					return returnValue;									
				}
			}			
			else return false; // 遇到障礙物 
		}
		
		bool goRight(Maze& vMaze, int row, int column) {
			int originalGoals = goals;                           // 紀錄向右走前剩餘目標數 
			bool success = findGoals(vMaze, row, column + 1, 1); // 向右遞迴找目標 
			if (originalGoals > goals) {                          // 若剩餘目標數減少 
				if (mazeptr[row][column] != 'G') mazeptr[row][column] = 'R'; // 且該格不是目標G，就紀錄路徑R 
			}
			
			return success; // 回傳是否成功找到所有目標 
		}
		
		bool goDown(Maze& vMaze, int row, int column) {
			int originalGoals = goals;                           // 紀錄向下走前剩餘目標數 
			bool success = findGoals(vMaze, row + 1, column, 2); // 向下遞迴找目標 
			if (originalGoals > goals) {                         // 若剩餘目標數減少
				if (mazeptr[row][column] != 'G') mazeptr[row][column] = 'R'; // 且該格不是目標G，就紀錄路徑R
			}
						
			return success; // 回傳是否成功找到所有目標  
		}
		
		bool goLeft(Maze& vMaze, int row, int column) {
			int originalGoals = goals;                           // 紀錄向左走前剩餘目標數 
			bool success = findGoals(vMaze, row, column - 1, 3); // 向左遞迴找目標  
			if (originalGoals > goals) {                          // 若剩餘目標數減少
				if (mazeptr[row][column] != 'G') mazeptr[row][column] = 'R'; // 且該格不是目標G，就紀錄路徑R
			}
			
			return success; // 回傳是否成功找到所有目標  
		}
		
		bool goUp(Maze& vMaze, int row, int column) {
			int originalGoals = goals;                           // 紀錄向上走前剩餘目標數 
			bool success = findGoals(vMaze, row - 1, column, 4); // 向上遞迴找目標  
			if (originalGoals > goals) {                          // 若剩餘目標數減少
				if (mazeptr[row][column] != 'G') mazeptr[row][column] = 'R'; // 且該格不是目標G，就紀錄路徑R
			}
			
			return success; // 回傳是否成功找到所有目標  
		}
		
		void clr() {                            // 釋放動態陣列空間 
			for (int i = 0; i < mazerow; i++) {
				delete[] mazeptr[i];            // 先一列一列刪除迷宮 
			}		
			
			delete [] mazeptr;                  // 再刪除指標陣列 
		}
		
		int getSPL() {                          // 取得最短路徑長 
			return shortestPathLength;
		}
		
	private:
		int goals;                              // 剩餘目標數 
		char **mazeptr;                         // 迷宮指標(pointer of pointer array) 
		int mazerow;                            // 迷宮列數 
		int mazecolumn;                         // 迷宮行數 
		int shortestPathLength;                 // 目前最短路徑長 
};
		
int main() {
	char command = 0;                          // user command
	
	do {
		Maze aMaze;                            // a matrix
		Char40 fileName;                       // a file name
		int goalNum = 1;                       // default: one goal
		
		cout << endl << "*** Path Finding ***";
		cout << endl << "* 0. Quit          *";
		cout << endl << "* 1. One goal      *";
		cout << endl << "* 2. More goals    *";
		cout << endl << "* 3. Shortest path *";
		cout << endl << "********************";
		cout << endl << "Input a command(0, 1, 2, 3): ";
		cin >> command;                        // get the command
		
		if (command == '1' || command == '2' || command == '3') {			
			cout << endl << "Input a file number: ";
			scanf("%s", fileName);             // get the file number 
			
			if (command == '2') {              // one or more goals
				cout << endl << "Number of G (goals): ";
				cin >> goalNum;                // get the number of goals				
				while (goalNum > 100 || goalNum < 1) {
					printf("\n### The number must be in [1,100] ###\n");
					cout << endl << "Number of G (goals): ";
					cin >> goalNum;            // get the number of goals
				}
			}
			
			if(aMaze.load(fileName, goalNum)) {// load the original matrix
				Maze vMaze(aMaze);             // a copy to keep the visited cells
				bool success = false;          // default: not found enough goal(s) 
								
				if (command == '1' || command == '2') {
					success = aMaze.findGoals(vMaze, 0, 0, 1); // find a path to goal(s)
					vMaze.show();              // 印出足跡圖 
					printf("\n");
					
					if (success) {             // 若有找到足夠目標 
						aMaze.show();          // 印出路徑圖 
						printf("\n");
					}
				}
				
				if (command == '3') {
					Maze rMaze(aMaze);         // 複製一份迷宮用來存最短路徑 
					success = aMaze.findShortestPath(vMaze, rMaze, 0, 0, 1, 0); // find the shortest path to the goal 
					vMaze.show();              // 印出足跡圖
					printf("\n");
					
					if (success) {             // 若有找到目標 
						rMaze.show();          // 印出路徑圖 
						printf("\n");
						printf("\nShortest path length = %d\n", aMaze.getSPL());
					}
					else {
						printf("\n### There is no path to find a goal! ###\n");
					}
					
					rMaze.clr();               // clear up the matrix
					system("pause");           // pause the execution
				}
				
				goalNum = 1;                   // reset to default		
				vMaze.clr();                   // clear up the matrix
				aMaze.clr();                   // clear up the matrix
			} // end inner-if
		} // end outer-if
		else if (command == '0') {             // '0': stop the program
			break;
		}
		else {
			cout << endl << "Command does not exist!" << endl;
		}
	} while (true);
	
	system("pause");                           // pause the execution
	return 0;
} // end of main
