// 11127222 邱妤蓁 
#include <stdio.h>
#include <iostream>

using namespace std;

#define MAX_X 100
#define MAX_Y 100

int x, y;  // 迷宮的長寬 
int n, goalsFound; // N
char mazeCopy1[MAX_Y][MAX_X]; 
char mazeCopy2[MAX_Y][MAX_X];
char roadR[MAX_Y][MAX_X];
char record[MAX_Y][MAX_X];

// 定義橫坐標的左右移動 
int dx[4] = {1, 0, -1, 0};
// 定義縱座標的上下移動 
int dy[4] = {0, 1, 0, -1};


class Maze {
	public:
		char maze[MAX_Y][MAX_X];
		
		// 讀取文件 
		void initMaze(FILE*file) {
  		fscanf(file, "%d %d", &x, &y);
  		for (int i = 0; i < y; i++) {
  			fscanf(file, "%s", maze[i]);
 			}
 			
 			fclose(file);
		}
};

// 檢查座標是否在迷宮內 
int isInside(int newX, int newY) {
    return newX >= 0 && newY >= 0 && newX < x && newY < y;
}

// 印出矩陣 
void printMaze(char m[MAX_Y][MAX_X]) {
  for (int i = 0; i < y; i++) {
	  for (int j = 0; j < x; j++) {
      printf("%c", m[i][j]);
    }
    
    printf("\n");
  }
}

// 用遞迴搜尋路逕(任務一) 
int findPath(int direction, int posX, int posY) {
    if (mazeCopy1[posY][posX] == 'G') {
    	goalsFound--;
      return 1; // 找到目標 
    }

    // 此位置已經過
    mazeCopy1[posY][posX] = 'V';

    // 嘗試當前方向
    int newX = posX + dx[direction];
    int newY = posY + dy[direction];

    // 檢查新位置是否合理，且位置是空格或目標
    if (isInside(newX, newY) && (mazeCopy1[newY][newX] == 'E' || mazeCopy1[newY][newX] == 'G')) {
      if (findPath(direction, newX, newY)) {
        // 找到一條可達到目標的路徑 
        mazeCopy2[posY][posX] = 'R';
        return 1;
      }
    }

    // 當前方向無法繼續，嘗試右、下、左、上 
    for (int step = 0; step < 4; step++) {
      int newDirection = (direction + step) % 4; // 變更方向為右、下、左、上的循環

      newX = posX + dx[newDirection];
      newY = posY + dy[newDirection];
            
      // 檢查新位置是否合理，且位置是空格或目標
      if (isInside(newX, newY) && (mazeCopy1[newY][newX] == 'E' || mazeCopy1[newY][newX] == 'G')) {
        if (findPath(newDirection, newX, newY)) {
			  // 找到一條可達到目標的路徑 
          mazeCopy2[posY][posX] = 'R';
          return 1;
        }
      }
    }
    
    return 0;
}

// 用遞迴搜尋路逕(任務二，矩陣二) 
int findPath2(int direction, int posX, int posY, Maze maze) {
    if (mazeCopy1[posY][posX] == 'G') {
    	
    	//還原迷宮
			for (int i = 0; i < y; i++) {
   			for (int j = 0; j < x; j++) {
   				if ( maze.maze[i][j] != 'G' ) {
       			mazeCopy1[i][j] = maze.maze[i][j];
   				}
   			}
			} 	 
			
			// 將此目標改為可通行的空格 
    	mazeCopy1[posY][posX] = 'E';
    	goalsFound--;
      return 1; // 找到目標 
    }

    // 此位置已經過
    mazeCopy1[posY][posX] = 'V';

    // 嘗試當前方向
    int newX = posX + dx[direction];
    int newY = posY + dy[direction];

    // 檢查新位置是否合理，且位置是空格或目標
    if (isInside(newX, newY) && (mazeCopy1[newY][newX] == 'E' || mazeCopy1[newY][newX] == 'G')) {
      if (findPath2(direction, newX, newY, maze)) {
        // 找到一條可達到目標的路徑 
        mazeCopy2[posY][posX] = 'R';
        return 1;
      }
    }

    // 當前方向無法繼續，嘗試右、下、左、上 
    for (int step = 0; step < 4; step++) {
      int newDirection = (direction + step) % 4; // 變更方向為右、下、左、上的循環

      newX = posX + dx[newDirection];
      newY = posY + dy[newDirection];
            
      // 檢查新位置是否合理，且位置是空格或目標
      if (isInside(newX, newY) && (mazeCopy1[newY][newX] == 'E' || mazeCopy1[newY][newX] == 'G')) {
        if (findPath2(newDirection, newX, newY, maze)) {
			  // 找到一條可達到目標的路徑 
          mazeCopy2[posY][posX] = 'R';
          return 1;
        }
      }
    }
    
    return 0;
}

// 用遞迴尋找路徑(任務二，矩陣一) 
  int findPath21(int direction, int posX, int posY) { 
    if (mazeCopy1[posY][posX] == 'G') {
      n--;
      goalsFound--;
    }

    // 如果已找到N個目標，則停止搜索
    if (n == 0) {
      return 1;
    }

    // 此位置已經過
    mazeCopy1[posY][posX] = 'V';

    // 嘗試當前方向
    int newX = posX + dx[direction];
    int newY = posY + dy[direction];

    // 檢查新位置是否合理，且位置是空格或目標
    if (isInside(newX, newY) && (mazeCopy1[newY][newX] == 'E' || mazeCopy1[newY][newX] == 'G')) {
      if (findPath21(direction, newX, newY)) {
        // 找到一條可達到目標的路徑  
        return 1;
        }
    	}


    // 嘗試右、下、左、上 
    for (int step = 0; step < 4; step++) {
        int newDirection = (direction + step) % 4; // 變更方向為右、下、左、上的循環

        newX = posX + dx[newDirection];
        newY = posY + dy[newDirection];
            
        // 檢查新位置是否合理，且位置是空格或目標
        if (isInside(newX, newY) && (mazeCopy1[newY][newX] == 'E' || mazeCopy1[newY][newX] == 'G')) {
          if (findPath21(newDirection, newX, newY)) {
            // 找到一條可達到目標的路徑 
            return 1;
          }
        }
      }

    return 0; // 沒有可行路徑 
}

int main() {
	
	int commamd,inputNumber,success;
	char filename[100];
	FILE *file;
	Maze maze;
	
	while(1) {
	  printf("***Path Finding***\n");
  	printf("*0. Quit         *\n");
  	printf("*1. One Goal     *\n");
  	printf("*2. More Goals   *\n");
  	printf("******************\n");
  	printf("Input a command(0, 1, 2):");
  	scanf("%d", &commamd);
  	if ( ( commamd == 1 || commamd == 2 ) ) {
  	  if ( commamd == 1 ) {
  	  	goalsFound = 1;
    		printf("\nInput a file number:");
	    	scanf("%d", &inputNumber);
	    	
	  		sprintf(filename, "input%d.txt", inputNumber); // 建構文件名稱 
	  		file = fopen(filename, "r"); // 打開文件 
	    	    		
	    	if (file == NULL) {
        	printf("input%d.txt does not exist!", inputNumber);
        	return 0;
    		}

    		// 讀取檔案
        maze.initMaze(file);
        
        // 複製原迷宮來讓矩陣使用
				for (int i = 0; i < y; i++) {
    			for (int j = 0; j < x; j++) {
        		mazeCopy1[i][j] = maze.maze[i][j];
        		mazeCopy2[i][j] = maze.maze[i][j];
    			}
				}    

    		// 從左上角開始找路徑 
    		findPath(0, 0, 0);
				
    		if (goalsFound == 0) {
					// 印出第一個矩陣 
    			printMaze(mazeCopy1);
          printf("\n");				
				
    		  // 印出第二個矩陣 
    		  printMaze(mazeCopy2);
          printf("\n");				
        }
        else{
   				// 印出第一個矩陣 
    			printMaze(mazeCopy1);
          printf("\n");	
				}
  		}	 
    	else if ( commamd == 2 ) {
    		printf("\nInput a file number:");
	    	scanf("%d", &inputNumber);
	    	
	  		sprintf(filename, "input%d.txt", inputNumber); // 建構文件名稱 
	  		file = fopen(filename, "r"); // 打開文件 
	    	    		
	    	if (file == NULL) {
        	printf("\ninput%d.txt does not exist!", inputNumber);
        	return 0;
    		}

    		printf("\nNumber of G( goals ) :");
    		scanf("%d", &n);
				goalsFound = n;
				
    		// 讀取檔案
        maze.initMaze(file);
        
        // 複製原迷宮來讓矩陣使用
				for (int i = 0; i < y; i++) {
    			for (int j = 0; j < x; j++) {
        		mazeCopy1[i][j] = maze.maze[i][j];
        		mazeCopy2[i][j] = maze.maze[i][j];
         		record[i][j] =  maze.maze[i][j];
    			}
				}  
      	
      	
      	// 從左上角開始找路徑，製造矩陣二 
    		while (goalsFound != 0 && findPath2(0, 0, 0, maze) ) {
				}
      	
        // 複製原迷宮來讓矩陣使用
       	goalsFound = n;
				for (int i = 0; i < y; i++) {
    			for (int j = 0; j < x; j++) {
        		mazeCopy1[i][j] = maze.maze[i][j];
    			}
				}  
      	
     		// 從左上角開始找路徑 
    		findPath21(0, 0, 0);
    		
        // 將G還原
       	for (int i = 0; i < y; i++) {
      	  for (int j = 0; j < x; j++) {
				    if ( record[i][j] == 'G') {
					    mazeCopy1[i][j] = 'G';
					    mazeCopy2[i][j] = 'G';
				    } 
				  }
			  }
    
    		if (goalsFound == 0) {
					// 印出第一個矩陣 
    			printMaze(mazeCopy1);
    			printf("\n");
        
        	// 印出第二個矩陣 
       		printMaze(mazeCopy2);
       		printf("\n");
        }
        else {
 					// 印出第一個矩陣 
    			printMaze(mazeCopy1);
    			printf("\n");
				}
    	}	
  	}
		else {
			printf("Command doesn't exsit.\n");		
		}
	}

}
