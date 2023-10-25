// 11127222 ����� 
#include <stdio.h>
#include <iostream>

using namespace std;

#define MAX_X 100
#define MAX_Y 100

int x, y;  // �g�c�����e 
int n, goalsFound; // N
char mazeCopy1[MAX_Y][MAX_X]; 
char mazeCopy2[MAX_Y][MAX_X];
char roadR[MAX_Y][MAX_X];
char record[MAX_Y][MAX_X];

// �w�q��Ъ����k���� 
int dx[4] = {1, 0, -1, 0};
// �w�q�a�y�Ъ��W�U���� 
int dy[4] = {0, 1, 0, -1};


class Maze {
	public:
		char maze[MAX_Y][MAX_X];
		
		// Ū����� 
		void initMaze(FILE*file) {
  		fscanf(file, "%d %d", &x, &y);
  		for (int i = 0; i < y; i++) {
  			fscanf(file, "%s", maze[i]);
 			}
 			
 			fclose(file);
		}
};

// �ˬd�y�ЬO�_�b�g�c�� 
int isInside(int newX, int newY) {
    return newX >= 0 && newY >= 0 && newX < x && newY < y;
}

// �L�X�x�} 
void printMaze(char m[MAX_Y][MAX_X]) {
  for (int i = 0; i < y; i++) {
	  for (int j = 0; j < x; j++) {
      printf("%c", m[i][j]);
    }
    
    printf("\n");
  }
}

// �λ��j�j�M���w(���Ȥ@) 
int findPath(int direction, int posX, int posY) {
    if (mazeCopy1[posY][posX] == 'G') {
    	goalsFound--;
      return 1; // ���ؼ� 
    }

    // ����m�w�g�L
    mazeCopy1[posY][posX] = 'V';

    // ���շ�e��V
    int newX = posX + dx[direction];
    int newY = posY + dy[direction];

    // �ˬd�s��m�O�_�X�z�A�B��m�O�Ů�Υؼ�
    if (isInside(newX, newY) && (mazeCopy1[newY][newX] == 'E' || mazeCopy1[newY][newX] == 'G')) {
      if (findPath(direction, newX, newY)) {
        // ���@���i�F��ؼЪ����| 
        mazeCopy2[posY][posX] = 'R';
        return 1;
      }
    }

    // ��e��V�L�k�~��A���եk�B�U�B���B�W 
    for (int step = 0; step < 4; step++) {
      int newDirection = (direction + step) % 4; // �ܧ��V���k�B�U�B���B�W���`��

      newX = posX + dx[newDirection];
      newY = posY + dy[newDirection];
            
      // �ˬd�s��m�O�_�X�z�A�B��m�O�Ů�Υؼ�
      if (isInside(newX, newY) && (mazeCopy1[newY][newX] == 'E' || mazeCopy1[newY][newX] == 'G')) {
        if (findPath(newDirection, newX, newY)) {
			  // ���@���i�F��ؼЪ����| 
          mazeCopy2[posY][posX] = 'R';
          return 1;
        }
      }
    }
    
    return 0;
}

// �λ��j�j�M���w(���ȤG�A�x�}�G) 
int findPath2(int direction, int posX, int posY, Maze maze) {
    if (mazeCopy1[posY][posX] == 'G') {
    	
    	//�٭�g�c
			for (int i = 0; i < y; i++) {
   			for (int j = 0; j < x; j++) {
   				if ( maze.maze[i][j] != 'G' ) {
       			mazeCopy1[i][j] = maze.maze[i][j];
   				}
   			}
			} 	 
			
			// �N���ؼЧאּ�i�q�檺�Ů� 
    	mazeCopy1[posY][posX] = 'E';
    	goalsFound--;
      return 1; // ���ؼ� 
    }

    // ����m�w�g�L
    mazeCopy1[posY][posX] = 'V';

    // ���շ�e��V
    int newX = posX + dx[direction];
    int newY = posY + dy[direction];

    // �ˬd�s��m�O�_�X�z�A�B��m�O�Ů�Υؼ�
    if (isInside(newX, newY) && (mazeCopy1[newY][newX] == 'E' || mazeCopy1[newY][newX] == 'G')) {
      if (findPath2(direction, newX, newY, maze)) {
        // ���@���i�F��ؼЪ����| 
        mazeCopy2[posY][posX] = 'R';
        return 1;
      }
    }

    // ��e��V�L�k�~��A���եk�B�U�B���B�W 
    for (int step = 0; step < 4; step++) {
      int newDirection = (direction + step) % 4; // �ܧ��V���k�B�U�B���B�W���`��

      newX = posX + dx[newDirection];
      newY = posY + dy[newDirection];
            
      // �ˬd�s��m�O�_�X�z�A�B��m�O�Ů�Υؼ�
      if (isInside(newX, newY) && (mazeCopy1[newY][newX] == 'E' || mazeCopy1[newY][newX] == 'G')) {
        if (findPath2(newDirection, newX, newY, maze)) {
			  // ���@���i�F��ؼЪ����| 
          mazeCopy2[posY][posX] = 'R';
          return 1;
        }
      }
    }
    
    return 0;
}

// �λ��j�M����|(���ȤG�A�x�}�@) 
  int findPath21(int direction, int posX, int posY) { 
    if (mazeCopy1[posY][posX] == 'G') {
      n--;
      goalsFound--;
    }

    // �p�G�w���N�ӥؼСA�h����j��
    if (n == 0) {
      return 1;
    }

    // ����m�w�g�L
    mazeCopy1[posY][posX] = 'V';

    // ���շ�e��V
    int newX = posX + dx[direction];
    int newY = posY + dy[direction];

    // �ˬd�s��m�O�_�X�z�A�B��m�O�Ů�Υؼ�
    if (isInside(newX, newY) && (mazeCopy1[newY][newX] == 'E' || mazeCopy1[newY][newX] == 'G')) {
      if (findPath21(direction, newX, newY)) {
        // ���@���i�F��ؼЪ����|  
        return 1;
        }
    	}


    // ���եk�B�U�B���B�W 
    for (int step = 0; step < 4; step++) {
        int newDirection = (direction + step) % 4; // �ܧ��V���k�B�U�B���B�W���`��

        newX = posX + dx[newDirection];
        newY = posY + dy[newDirection];
            
        // �ˬd�s��m�O�_�X�z�A�B��m�O�Ů�Υؼ�
        if (isInside(newX, newY) && (mazeCopy1[newY][newX] == 'E' || mazeCopy1[newY][newX] == 'G')) {
          if (findPath21(newDirection, newX, newY)) {
            // ���@���i�F��ؼЪ����| 
            return 1;
          }
        }
      }

    return 0; // �S���i����| 
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
	    	
	  		sprintf(filename, "input%d.txt", inputNumber); // �غc���W�� 
	  		file = fopen(filename, "r"); // ���}��� 
	    	    		
	    	if (file == NULL) {
        	printf("input%d.txt does not exist!", inputNumber);
        	return 0;
    		}

    		// Ū���ɮ�
        maze.initMaze(file);
        
        // �ƻs��g�c�����x�}�ϥ�
				for (int i = 0; i < y; i++) {
    			for (int j = 0; j < x; j++) {
        		mazeCopy1[i][j] = maze.maze[i][j];
        		mazeCopy2[i][j] = maze.maze[i][j];
    			}
				}    

    		// �q���W���}�l����| 
    		findPath(0, 0, 0);
				
    		if (goalsFound == 0) {
					// �L�X�Ĥ@�ӯx�} 
    			printMaze(mazeCopy1);
          printf("\n");				
				
    		  // �L�X�ĤG�ӯx�} 
    		  printMaze(mazeCopy2);
          printf("\n");				
        }
        else{
   				// �L�X�Ĥ@�ӯx�} 
    			printMaze(mazeCopy1);
          printf("\n");	
				}
  		}	 
    	else if ( commamd == 2 ) {
    		printf("\nInput a file number:");
	    	scanf("%d", &inputNumber);
	    	
	  		sprintf(filename, "input%d.txt", inputNumber); // �غc���W�� 
	  		file = fopen(filename, "r"); // ���}��� 
	    	    		
	    	if (file == NULL) {
        	printf("\ninput%d.txt does not exist!", inputNumber);
        	return 0;
    		}

    		printf("\nNumber of G( goals ) :");
    		scanf("%d", &n);
				goalsFound = n;
				
    		// Ū���ɮ�
        maze.initMaze(file);
        
        // �ƻs��g�c�����x�}�ϥ�
				for (int i = 0; i < y; i++) {
    			for (int j = 0; j < x; j++) {
        		mazeCopy1[i][j] = maze.maze[i][j];
        		mazeCopy2[i][j] = maze.maze[i][j];
         		record[i][j] =  maze.maze[i][j];
    			}
				}  
      	
      	
      	// �q���W���}�l����|�A�s�y�x�}�G 
    		while (goalsFound != 0 && findPath2(0, 0, 0, maze) ) {
				}
      	
        // �ƻs��g�c�����x�}�ϥ�
       	goalsFound = n;
				for (int i = 0; i < y; i++) {
    			for (int j = 0; j < x; j++) {
        		mazeCopy1[i][j] = maze.maze[i][j];
    			}
				}  
      	
     		// �q���W���}�l����| 
    		findPath21(0, 0, 0);
    		
        // �NG�٭�
       	for (int i = 0; i < y; i++) {
      	  for (int j = 0; j < x; j++) {
				    if ( record[i][j] == 'G') {
					    mazeCopy1[i][j] = 'G';
					    mazeCopy2[i][j] = 'G';
				    } 
				  }
			  }
    
    		if (goalsFound == 0) {
					// �L�X�Ĥ@�ӯx�} 
    			printMaze(mazeCopy1);
    			printf("\n");
        
        	// �L�X�ĤG�ӯx�} 
       		printMaze(mazeCopy2);
       		printf("\n");
        }
        else {
 					// �L�X�Ĥ@�ӯx�} 
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
