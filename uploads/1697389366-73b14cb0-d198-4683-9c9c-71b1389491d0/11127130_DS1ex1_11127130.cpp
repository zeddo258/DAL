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
 
		bool findGoals(Maze& vMaze, int row, int column, int dir) { // right:dir == 1, down:dir == 2, left:dir == 3, up:dir == 4
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
		
		bool goRight(Maze& vMaze, int row, int column) {
			int originalGoals = goals;                           // 紀錄向右走前剩餘目標數 
			bool success = findGoals(vMaze, row, column + 1, 1); // 向右遞迴找目標 
			if (originalGoals > goals)                           // 若剩餘目標數減少 
				if (mazeptr[row][column] != 'G') mazeptr[row][column] = 'R'; // 且該格不是目標G，就紀錄路徑R 
			
			return success; // 回傳是否成功找到所有目標 
		}
		
		bool goDown(Maze& vMaze, int row, int column) {
			int originalGoals = goals;                           // 紀錄向下走前剩餘目標數 
			bool success = findGoals(vMaze, row + 1, column, 2); // 向下遞迴找目標 
			if (originalGoals > goals)                           // 若剩餘目標數減少
				if (mazeptr[row][column] != 'G') mazeptr[row][column] = 'R'; // 且該格不是目標G，就紀錄路徑R
			
			return success; // 回傳是否成功找到所有目標  
		}
		
		bool goLeft(Maze& vMaze, int row, int column) {
			int originalGoals = goals;                           // 紀錄向左走前剩餘目標數 
			bool success = findGoals(vMaze, row, column - 1, 3); // 向左遞迴找目標  
			if (originalGoals > goals)                           // 若剩餘目標數減少
				if (mazeptr[row][column] != 'G') mazeptr[row][column] = 'R'; // 且該格不是目標G，就紀錄路徑R
			
			return success; // 回傳是否成功找到所有目標  
		}
		
		bool goUp(Maze& vMaze, int row, int column) {
			int originalGoals = goals;                           // 紀錄向上走前剩餘目標數 
			bool success = findGoals(vMaze, row - 1, column, 4); // 向上遞迴找目標  
			if (originalGoals > goals)                           // 若剩餘目標數減少
				if (mazeptr[row][column] != 'G') mazeptr[row][column] = 'R'; // 且該格不是目標G，就紀錄路徑R
			
			return success; // 回傳是否成功找到所有目標  
		}
		
		void clr() {                            // 釋放動態陣列空間 
			for (int i = 0; i < mazerow; i++) {
				delete[] mazeptr[i];            // 先一列一列刪除迷宮 
			}		
			
			delete [] mazeptr;                  // 再刪除指標陣列 
		}
		
	private:
		int goals;                              // 剩餘目標數 
		char **mazeptr;                         // 迷宮指標(pointer of pointer array) 
		int mazerow;                            // 迷宮列數 
		int mazecolumn;                         // 迷宮行數 
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
		cout << endl << "********************";
		cout << endl << "Input a command(0, 1, 2): ";
		cin >> command;                        // get the command
		
		if (command == '1' || command == '2') {			
			cout << endl << "Input a file number(e.g. 201, 202, ...): ";
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
				bool success = aMaze.findGoals(vMaze, 0, 0, 1); // find a path to goal(s)
				
				goalNum = 1;                   // reset to default
				vMaze.show();                  // show on screen the visited cells
				
				if (success) {                 // to check if the goal is reached or not
					printf("\n");
					aMaze.show();              // show on screen the route to reach the goal
				}
				
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
