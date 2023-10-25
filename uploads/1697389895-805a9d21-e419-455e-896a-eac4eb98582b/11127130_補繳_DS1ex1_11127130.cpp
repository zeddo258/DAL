// 11127130 ���E��  
# include <iostream>                            // cin, cout, system...
# include <stdio.h>                             // printf, scanf, FILE...
# include <string.h>                            // strcpy(), strcat()...

using namespace std;                            // �ϥμзǩR�W�Ŷ� 

typedef char Char40[40];                        // �w�q40�檺�r���}�C��Char40 


class Maze {
	public:
		Maze() {}                               // Default constructor
		
		Maze(const Maze& aMaze) {               // Declare copy constructor
			mazerow = aMaze.mazerow;            // copy mazerow
			mazecolumn = aMaze.mazecolumn;      // copy mazecolumn
			goals = aMaze.goals;                // copy goals
			shortestPathLength = aMaze.shortestPathLength;
			char **ptr = aMaze.mazeptr;         // �إߤ@�ӫ��Ы��V��g�c  
			 
			// �إ߷s���ʺA�}�C(��mazeptr���V)�A�ç��ª��g�c��T�ƻs�즹�}�C 
			mazeptr = new char *[mazerow];
			for (int i = 0; i < mazerow; i++) {
				mazeptr[i] = new char[mazecolumn + 2]; // mazecolumn + 2�O�]���n�񴫦�r���M�Ŧr�� 
				strcpy(mazeptr[i], ptr[i]);
			}
			
			ptr = NULL;                         // �Nptr���a 
		}
		
		bool load(Char40 fileName, int goalNum) {
			FILE * fp;                          
		    Char40 completeFileName;
		    strcpy(completeFileName, "input");
		    strcat(completeFileName, fileName);
		    strcat(completeFileName, ".txt");   // completeFileName = "input{fileName}.txt"
		    fp = fopen(completeFileName, "r");  // ���}�@�ӥΩ�Ū�������A�Ӥ�󥲶��s�b  
						
			if (fp == NULL) {                   // Ū�ɥ��� 
				printf("\ninput%s.txt does not exist!\n", fileName);
				return false;
			}
			
			Char40 line;
			int row, column;                    // row:�C, column:�� 
			fscanf(fp, "%d %d", &column, &row); // Ū���g�c��C�� 
			fgets(line, 40, fp);                // ��Ĥ@��Ū�� 
			mazerow = row;                      // �]�wprivat�ܼ� mazerow
			mazecolumn = column;                // �]�wprivat�ܼ� mazecolumn
			
			char **ptr = new char *[row];       // �إ߰ʺA�}�C row * column
			for (int i = 0; i < row; i++) {
				ptr[i] = new char[column + 2];  // column + 2�O�]���n�񴫦�r���M�Ŧr��  
				fgets(line, column + 2, fp);    // n = column + 2�O�]��fgets�bŪ��n - 1�Ӧr���ɷ|����A�n����Ū�촫��r�� 
				strcpy(ptr[i], line);           // �NŪ�쪺�g�c��T�s�i�ʺA�}�C 
			}
			
			mazeptr = ptr;                      // �]�wprivat���� mazeptr
			ptr = NULL;                         // �Nptr���a 
			goals = goalNum;                    // �]�wprivat�ܼ� goals 
			shortestPathLength = 99999;         // �]�wprivat�ܼ� shortestPathLength�A
			                                    // ��l�ȵ��ܤj�A�o�˧��Ĥ@�����|�ɴN�|���shortestPathLength�� 
			
			fclose(fp);                         // ������� 
			return true;
		}
		
		void show() {                           // �L�X�g�c�x�} 
			for (int i = 0; i < mazerow; i++) {
				for (int j = 0; j < mazecolumn; j++) {
					printf("%c", mazeptr[i][j]);
				}
				
				printf("\n");                   // �L���@�C���@�� 
			}
		}
 
		bool findGoals(Maze& vMaze, int row, int column, int dir) {
			// right:dir == 1, down:dir == 2, left:dir == 3, up:dir == 4
			if (vMaze.mazeptr[row][column] == 'E' || vMaze.mazeptr[row][column] == 'G') {
				if (vMaze.mazeptr[row][column] == 'E')                // �Y�O�q�� 
					vMaze.mazeptr[row][column] = 'V';                 // �������L������V 
				else if (vMaze.mazeptr[row][column] == 'G') {         // �Y�O�ؼ� 
					goals -= 1;                                       // �Ѿl�ؼмƴ�1 
					if (goals == 0)	return true;                      // �Y�Ѿl�ؼмƬ�0�A�h�����j���Ireturn true 
				}
				
				if (dir == 1) {                                       // ���V�k�� 
					if (column < mazecolumn - 1)                      // ���b�g�c�̥k 
						if (goRight(vMaze, row, column)) return true; // �V�k���A���Ҧ��ؼдNreturn true 
							                            
					if (row < mazerow - 1)                            // ���b�g�c�̤U 
						if (goDown(vMaze, row, column)) return true;  // �V�U���A���Ҧ��ؼдNreturn true  
						
					if (row > 0)                                      // ���b�g�c�̤W 
						if (goUp(vMaze, row, column)) return true;    // �V�W���A���Ҧ��ؼдNreturn true
				}
				else if (dir == 2) {                                  // ���V�U�� 
					if (row < mazerow - 1)                            // ���b�g�c�̤U 
						if (goDown(vMaze, row, column)) return true;  // �V�U���A���Ҧ��ؼдNreturn true
					
					if (column > 0)                                   // ���b�g�c�̥� 
						if (goLeft(vMaze, row, column)) return true;  // �V�����A���Ҧ��ؼдNreturn true 
						
					if (column < mazecolumn - 1)                      // ���b�g�c�̥k 
						if (goRight(vMaze, row, column)) return true; // �V�k���A���Ҧ��ؼдNreturn true					
				}
				else if (dir == 3) {                                  // ���V���� 
					if (column > 0)                                   // ���b�g�c�̥� 
						if (goLeft(vMaze, row, column)) return true;  // �V�����A���Ҧ��ؼдNreturn true
					
					if (row > 0)                                      // ���b�g�c�̤W 
						if (goUp(vMaze, row, column)) return true;    // �V�W���A���Ҧ��ؼдNreturn true
					
					if (row < mazerow - 1)                            // ���b�g�c�̤U 
						if (goDown(vMaze, row, column)) return true;  // �V�U���A���Ҧ��ؼдNreturn true			
				}
				else if (dir == 4) {                                  // ���V�W�� 
					if (row > 0)                                      // ���b�g�c�̤W 
						if (goUp(vMaze, row, column)) return true;    // �V�W���A���Ҧ��ؼдNreturn true
					
					if (column < mazecolumn - 1)                      // ���b�g�c�̥k 
						if (goRight(vMaze, row, column)) return true; // �V�k���A���Ҧ��ؼдNreturn true		
					
					if (column > 0)                                   // ���b�g�c�̥� 
						if (goLeft(vMaze, row, column)) return true;  // �V�����A���Ҧ��ؼдNreturn true									
				}
				
				return false;  // �|����쨬���ؼм� 
			}			
			else return false; // �J���ê���Τw���L���� 
		} 
		
		bool findShortestPath(Maze& vMaze, Maze& rMaze, int row, int column, int dir, int path) {
			// right:dir == 1, down:dir == 2, left:dir == 3, up:dir == 4
			bool success = false;     // ���L���\���ؼ� 
			bool returnValue = false; // ���j�^�ǭ� 
			path++;                   // �C���j�@���A���|�N+1 
			if (mazeptr[row][column] == 'E' || mazeptr[row][column] == 'G') { 
				if (path == shortestPathLength || path > (mazerow  * mazecolumn)) {
					// �p�G���|����ثe�̵u���| �� ���|�j���Ӱg�c��� 
					return false; // �N���~�򻼰j 
				} 
				
				if (mazeptr[row][column] == 'E') {    // �Y�O�q�� 
					vMaze.mazeptr[row][column] = 'V'; // �������L������V 
				} 
				
				if (mazeptr[row][column] == 'G') {              // �Y�O�ؼ� 			
					if (path < shortestPathLength) {            // �B���|�p��ثe�̵u���| 
						shortestPathLength = path;              // ��s�ثe�̵u���|�� 
						char **ptr = new char *[mazerow];       // �إ߷s���ʺA�}�C mazerow * mazecolumn
						for (int i = 0; i < mazerow; i++) {
							ptr[i] = new char[mazecolumn + 2];  // mazecolumn + 2�O�]���n�񴫦�r���M�Ŧr��   
							strcpy(ptr[i], mazeptr[i]);         // �N��l�g�c��T�s�i�ʺA�}�C 
						}
						
						// �R��rMaze�쥻�s���̵u���|��(�]���̵u���|�ܤF) 
						for (int i = 0; i < mazerow; i++) {
							delete[] rMaze.mazeptr[i];          // ���@�C�@�C�R���g�c 
						}		
						
						delete [] rMaze.mazeptr;                // �A�R�����а}�C 
						
						rMaze.mazeptr = ptr;                    // �NrMaze�g�c���Ы��V�s���̵u���|�� 
						ptr = NULL;                             // �Nptr���a 
					}
					
					goals = 0;                                  // �Ѿl�ؼмƳ]��0(�]���`�@�u���@�ӥؼ�) 
					return true;                                // ����ؼСA���j���Ireturn true 
				}
				
				if (dir == 1) {                                                             // ���V�k��                               
					if (column < mazecolumn - 1) {                                          // ���b�̥k 
						success = findShortestPath(vMaze, rMaze, row, column + 1, 1, path); // �V�k��ؼ� 
						if (success) {                                                      // �Y���\���ؼ� 
							returnValue = success;                                          // �]�w�^�ǭ� 
							rMaze.mazeptr[row][column] = 'R';                               // �b���|�ϤW�������|R 
						}
					}
							                            
					if (row < mazerow - 1) {                                                // ���b�̤U  
						success = findShortestPath(vMaze, rMaze, row + 1, column, 2, path); // �V�U��ؼ�                         
						if (success) {                                                      // �Y���\���ؼ� 
							returnValue = success;                                          // �]�w�^�ǭ� 
							rMaze.mazeptr[row][column] = 'R';                               // �b���|�ϤW�������|R 
						}
					}
						
					if (row > 0) {                                                          // ���b�̤W  
						success = findShortestPath(vMaze, rMaze, row - 1, column, 4, path); // �V�W��ؼ�  
						if (success) {                                                      // �Y���\���ؼ� 
							returnValue = success;                                          // �]�w�^�ǭ� 
							rMaze.mazeptr[row][column] = 'R';                               // �b���|�ϤW�������|R 
						}                               
					}
					
					return returnValue;	   
				}
				else if (dir == 2) {                                 
					if (row < mazerow - 1) {                                                // ���b�̤U  
						success = findShortestPath(vMaze, rMaze, row + 1, column, 2, path); // �V�U��ؼ�                          
						if (success) {                                                      // �Y���\���ؼ� 
							returnValue = success;                                          // �]�w�^�ǭ� 
							rMaze.mazeptr[row][column] = 'R';                               // �b���|�ϤW�������|R 
						}
					}
					
					if (column > 0) {                                                       // ���b�̥� 
						success = findShortestPath(vMaze, rMaze, row, column - 1, 3, path); // �V����ؼ�                             
						if (success) {                                                      // �Y���\���ؼ� 
							returnValue = success;                                          // �]�w�^�ǭ� 
							rMaze.mazeptr[row][column] = 'R';                               // �b���|�ϤW�������|R 
						}
					}
						
					if (column < mazecolumn - 1) {                                          // ���b�̥k  
						success = findShortestPath(vMaze, rMaze, row, column + 1, 1, path); // �V�k��ؼ�                   
						if (success) {                                                      // �Y���\���ؼ� 
							returnValue = success;                                          // �]�w�^�ǭ� 
							rMaze.mazeptr[row][column] = 'R';                               // �b���|�ϤW�������|R 
						}
					}
					 
					return returnValue;					
				}
				else if (dir == 3) {                                 
					if (column > 0) {                                                       // ���b�̥� 
						success = findShortestPath(vMaze, rMaze, row, column - 1, 3, path); // �V����ؼ�                               
						if (success) {                                                      // �Y���\���ؼ� 
							returnValue = success;                                          // �]�w�^�ǭ� 
							rMaze.mazeptr[row][column] = 'R';                               // �b���|�ϤW�������|R 
						}
					}
					
					if (row > 0) {                                                          // ���b�̤W  
						success = findShortestPath(vMaze, rMaze, row - 1, column, 4, path); // �V�W��ؼ�                               
						if (success) {                                                      // �Y���\���ؼ� 
							returnValue = success;                                          // �]�w�^�ǭ� 
							rMaze.mazeptr[row][column] = 'R';                               // �b���|�ϤW�������|R 
						}
					}
					
					if (row < mazerow - 1) {                                                // ���b�̤U  
						success = findShortestPath(vMaze, rMaze, row + 1, column, 2, path); // �V�U��ؼ�          
						if (success) {                                                      // �Y���\���ؼ� 
							returnValue = success;                                          // �]�w�^�ǭ� 
							rMaze.mazeptr[row][column] = 'R';                               // �b���|�ϤW�������|R 
						}
					}
					
					return returnValue;  			
				}
				else if (dir == 4) {                                
					if (row > 0) {                                                          // ���b�̤W  
						success = findShortestPath(vMaze, rMaze, row - 1, column, 4, path); // �V�W��ؼ�                               
						if (success) {                                                      // �Y���\���ؼ� 
							returnValue = success;                                          // �]�w�^�ǭ� 
							rMaze.mazeptr[row][column] = 'R';                               // �b���|�ϤW�������|R 
						}
					}
					
					if (column < mazecolumn - 1) {                                          // ���b�̥k  
						success = findShortestPath(vMaze, rMaze, row, column + 1, 1, path); // �V�k��ؼ�                     
						if (success) {                                                      // �Y���\���ؼ� 
							returnValue = success;                                          // �]�w�^�ǭ� 
							rMaze.mazeptr[row][column] = 'R';                               // �b���|�ϤW�������|R 
						}
					}
					
					if (column > 0) {                                                       // ���b�̥� 
						success = findShortestPath(vMaze, rMaze, row, column - 1, 3, path); // �V����ؼ�   
						if (success) {                                                      // �Y���\���ؼ� 
							returnValue = success;                                          // �]�w�^�ǭ� 
							rMaze.mazeptr[row][column] = 'R';                               // �b���|�ϤW�������|R 
						}
					}
					
					return returnValue;									
				}
			}			
			else return false; // �J���ê�� 
		}
		
		bool goRight(Maze& vMaze, int row, int column) {
			int originalGoals = goals;                           // �����V�k���e�Ѿl�ؼм� 
			bool success = findGoals(vMaze, row, column + 1, 1); // �V�k���j��ؼ� 
			if (originalGoals > goals) {                          // �Y�Ѿl�ؼмƴ�� 
				if (mazeptr[row][column] != 'G') mazeptr[row][column] = 'R'; // �B�Ӯ椣�O�ؼ�G�A�N�������|R 
			}
			
			return success; // �^�ǬO�_���\���Ҧ��ؼ� 
		}
		
		bool goDown(Maze& vMaze, int row, int column) {
			int originalGoals = goals;                           // �����V�U���e�Ѿl�ؼм� 
			bool success = findGoals(vMaze, row + 1, column, 2); // �V�U���j��ؼ� 
			if (originalGoals > goals) {                         // �Y�Ѿl�ؼмƴ��
				if (mazeptr[row][column] != 'G') mazeptr[row][column] = 'R'; // �B�Ӯ椣�O�ؼ�G�A�N�������|R
			}
						
			return success; // �^�ǬO�_���\���Ҧ��ؼ�  
		}
		
		bool goLeft(Maze& vMaze, int row, int column) {
			int originalGoals = goals;                           // �����V�����e�Ѿl�ؼм� 
			bool success = findGoals(vMaze, row, column - 1, 3); // �V�����j��ؼ�  
			if (originalGoals > goals) {                          // �Y�Ѿl�ؼмƴ��
				if (mazeptr[row][column] != 'G') mazeptr[row][column] = 'R'; // �B�Ӯ椣�O�ؼ�G�A�N�������|R
			}
			
			return success; // �^�ǬO�_���\���Ҧ��ؼ�  
		}
		
		bool goUp(Maze& vMaze, int row, int column) {
			int originalGoals = goals;                           // �����V�W���e�Ѿl�ؼм� 
			bool success = findGoals(vMaze, row - 1, column, 4); // �V�W���j��ؼ�  
			if (originalGoals > goals) {                          // �Y�Ѿl�ؼмƴ��
				if (mazeptr[row][column] != 'G') mazeptr[row][column] = 'R'; // �B�Ӯ椣�O�ؼ�G�A�N�������|R
			}
			
			return success; // �^�ǬO�_���\���Ҧ��ؼ�  
		}
		
		void clr() {                            // ����ʺA�}�C�Ŷ� 
			for (int i = 0; i < mazerow; i++) {
				delete[] mazeptr[i];            // ���@�C�@�C�R���g�c 
			}		
			
			delete [] mazeptr;                  // �A�R�����а}�C 
		}
		
		int getSPL() {                          // ���o�̵u���|�� 
			return shortestPathLength;
		}
		
	private:
		int goals;                              // �Ѿl�ؼм� 
		char **mazeptr;                         // �g�c����(pointer of pointer array) 
		int mazerow;                            // �g�c�C�� 
		int mazecolumn;                         // �g�c��� 
		int shortestPathLength;                 // �ثe�̵u���|�� 
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
					vMaze.show();              // �L�X����� 
					printf("\n");
					
					if (success) {             // �Y����쨬���ؼ� 
						aMaze.show();          // �L�X���|�� 
						printf("\n");
					}
				}
				
				if (command == '3') {
					Maze rMaze(aMaze);         // �ƻs�@���g�c�ΨӦs�̵u���| 
					success = aMaze.findShortestPath(vMaze, rMaze, 0, 0, 1, 0); // find the shortest path to the goal 
					vMaze.show();              // �L�X�����
					printf("\n");
					
					if (success) {             // �Y�����ؼ� 
						rMaze.show();          // �L�X���|�� 
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
