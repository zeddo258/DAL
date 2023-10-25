#include <iostream>
#include <string> 
#include <cstdio>
#include <cstring>

using namespace std;

typedef enum {oneG, moreG} Mode;

#define right 0
#define down 1
#define left 2
#define up 3
// namespace enum direction {copy = -1,right,down,left,up} ;

void Move(int curDir, int& corY, int& corX) {
	if (curDir % 4 == 0) {
		corX++;
	} 
	else if (curDir % 4 == 1) {
		corY++;
	}
	else if (curDir % 4 == 2) {
		corX--;
	}
	else if (curDir % 4 == 3) {
		corY--;
	}
	
}

void ChangeDirection (int &curDir) {
	curDir = curDir + 1;
}

class CoXY {
	int y;
	int x;
	
	public :
		CoXY(): y(0),x(0){
			
		} // end CoXY default constructor
		CoXY(int py, int px) : y(py), x(px) {
			
		} // end CoXY copy constructor
		
		void setXY(const int py, const int px){
			y = py;
			x = px;
		} // set up the coordinate}
		
		int getX() const {
			return x;
		} // get the X coordinate of pt
		
		int getY() const {
			return y;
		} // get the Y coordinate of pt
		
/*		CoXY nextXY(Moves dir) const {
			CoXY pt(y,x);
			
			switch(dir) {
				case Right: pt.x++;
					break;
				case Down: pt. y++;
					break;
				case Left: pt.x--;
					break;
				case Up: pt.y--;
					break;
				default:	;
			} // end switch
			return pt;
			
		} // get the coordinate after the move toward dir */
		
		bool match(const CoXY& pt) const {
			if((y == pt.y) && (x == pt.x)){
				return true;
			}
			
			return false;
		} // check if the coordinate is the same as pt
		
		bool inRange(const CoXY & maxLimit) const {
			if ((y >= 0) && (y < maxLimit.y) && 
				(x >= 0) && (x < maxLimit.x)) {
					return true;
			}
			
			return false;		
		} // check if the coordinate is in the range
}; // end CoXY class

class Maze {
	CoXY coMax;
	char** matrixMaze;;
	char curBlock;
	int curDir;
	int corX, corY,tempX,tempY;
	int foundGoal = 0;
	int vNum = 0;
	
public:
	Maze() : matrixMaze(NULL) {
		curBlock = ' ';
		curDir = right;
		corX = 0;
		corY = 0;
	} 
	
	bool load(std::string fileName) {
		FILE *infile = NULL; // a file handle
		bool success = false; // read a file successfully or not
		coMax.setXY(0,0); // the number of rows & columns in the maze
	
		fileName = "input" + fileName + ".txt";
		infile = fopen(fileName.c_str(), "r"); // open the file
		if (infile == NULL)
			cout << endl << fileName << "does not exist!" << endl;
		else {
			int arg1 = 0,arg2 = 0;
			if (fscanf(infile,"%d %d", &arg1, &arg2) == 2) {
				coMax.setXY(arg1,arg2); // the number of rows & columns in the maze
				
				// Allocate memory for matrixMaze
				
				matrixMaze = new char*[coMax.getX()];
				for (int i = 0; i < coMax.getX(); i++) {
					matrixMaze[i] = new char[coMax.getY()];
				}
				
				// Read the data
			
				for (int row = 0; row < coMax.getX(); row++) {
                    for (int col = 0; col < coMax.getY(); col++) {
                        fscanf(infile, " %c", &matrixMaze[row][col]);
                    }
                }
                
                success = true;
			}
			
			fclose(infile);
		} // end else
		return success;
	} // end Maze::load

	bool findGoals(int goalNum) {
		curBlock = matrixMaze[corY][corX];
		
		if ( curBlock == 'E' ) {
			matrixMaze[corY][corX] = 'V';
		}
		else if ( curBlock == 'O' || curBlock == 'V' )  {
			if (curBlock == 'V') {
				vNum++;
			}
			corX = tempX;
			corY = tempY;  
			ChangeDirection(curDir);
		}
		else if ( curBlock == 'G') {
			cout << goalNum << endl;
			foundGoal++;
			if (foundGoal == goalNum) {
				return true;
			}
		}
		
		if (corX == (coMax.getX()-2) || corY == (coMax.getY()-2) || corX < 0 || corY < 0 ) { // reach the border
			corX = tempX;
			corY = tempY;
			ChangeDirection(curDir);
		}
		
		tempX = corX;
		tempY = corY;
		Move(curDir, corY, corX);
		if ( vNum < 4 ) {
			findGoals(goalNum);
		}
		else if (vNum >= 4) {
			return false;
		}
	}  
	
	void show() {
		for (int a = 0;a < coMax.getX();a++) {
			for(int b = 0; b < coMax.getY();b++) {
				cout << matrixMaze[a][b] << " ";
			}
			
			cout << endl;
		}
		
		cout << endl;
	}
	
	void Rshow() {
		for (int a = 0;a < coMax.getX();a++) {
			for(int b = 0; b < coMax.getY();b++) {
				if (matrixMaze[a][b] == 'V') {
					matrixMaze[a][b] = 'R'; 
				}
				cout << matrixMaze[a][b] << " ";
			}
			
			cout << endl;
		}
		
		cout << endl;
	}
	
	void clr() {
		if (matrixMaze) {
			for (int i = 0;i < coMax.getY();i++) {
				delete[] matrixMaze[i];
			}
			delete[] matrixMaze;
			matrixMaze = NULL;
		}	
	}
};


int main() {
	
	int command = 0;
	do {
		Maze aMaze; // a matrix
		string fileName; // a file name
		int goalNum = 1; // default one goal
		
		cout << endl <<"***Path Finding***";
		cout << endl <<"*0. Quit         *";
		cout << endl <<"*1. One goal     *";
		cout << endl <<"*2. More goals   *";
		cout << endl <<"******************";
		cout << endl << "input a command(0,1,2):";
		cin >> command;
		if((command == 1) || (command == 2)) {
			cout << endl << "input a file number(e.g., 201, 202)";
			cin >> fileName;
			if (command == 2) {
				cout << endl << "how  many goals?";
				cin >> goalNum;
			}
			if (aMaze.load(fileName)) {
				bool achieve = aMaze.findGoals(goalNum); // find a path to goal
				aMaze.show(); // show on screen the visited cells
				if ( achieve ) {
					aMaze.Rshow();
				}
			}
			
			aMaze.clr(); // clear up the original matrix
		} // end outer-if
		else if (!command) { // '0' stop the program
			break;
		}
			
		else {
			cout << endl << "Command does not exist" << endl;
		}
	}while(true);
		
	system("pause"); // pause the execution
	return 0;
} // end of main

