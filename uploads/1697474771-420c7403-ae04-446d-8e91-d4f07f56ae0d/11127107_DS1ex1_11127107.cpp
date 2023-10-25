// 11127107 ³¯¬f·ì
# include <iostream>
# include <vector>
# include <string>
# include <fstream>

using namespace std ;

enum Modes{oneG, moreG} ; // eNumber used to identify different modes

class Maze { // a class type to represent the maze
	
	public :
		
		vector< vector<char> > getMaze() ; // a getter for maze's matrix
		Modes getMode() ; // a getter for game's mode
		bool load(string fileNumber, Modes mode, int & goalsLastAmount) ; // the function for load and set the file and mode
		bool findOneGoal(Maze & vMaze, int x, int y, int lastDir) ; // the function for find a goal
		bool findMoreGoals(Maze & vMaze, int x, int y, int & goalsLastAmount, int lastDir) ; // the function for find more goals
		bool whetherMove(int x, int y) ; // determine whether can the rat move
		void show() ; // the function for show out the matrix
		void clr() ; // the function for clear up the content
		void setLocationState(int x, int y, char word) ; // the function for set the visited location
		void copyThePathOfMaze() ; // the function for copy the path of maze
		void resetTheMaze() ; // the function for reset the maze
		void showTheFinalPath() ; // the function for print out the final path
		
	private :
		
		vector< vector<char> > originalMaze ; // a matrix for original maze
		vector< vector<char> > theMaze ; // a matrix for maze
		vector< vector<char> > theFinalMaze ; // a matrix for final maze
		Modes theMode ; // the gamemode
		int sizeOfRows, sizeOfCols ; // the maze's sizeOfRows and columns
		
} ; // class Maze
		
vector< vector<char> > Maze::getMaze() { // a getter for maze's matrix

	return theMaze ; // return theMaze
	
} // getMaze() ;

Modes Maze::getMode() { // a getter for game's mode

	return theMode ; // return theMode
	
} // getMode() ;

bool Maze::load(string fileNumber, Modes mode, int & goalsTotalAmount) { // the function for load and set the file and mode

	string fileName = "input" + fileNumber + ".txt" ; // get file's total name : combine "input", fileNumber, and ".txt"
	ifstream fin(fileName.c_str()) ; // read the file
	
	if (!fin.is_open()) { // whether the file was successfully read
		cout << endl << fileName << " does not exist!" << endl ;
		return false ; // read failed
	} // if
	
	theMode = mode ; // setup the mode
	
	fin >> sizeOfCols >> sizeOfRows  ; // get the size
	
	vector<char> temp((sizeOfCols + 2)) ; // the vector to help set matrix's column size
	theMaze.resize((sizeOfRows + 2) , temp) ; // set matrix's row and column size
		
	for (int i = 0 ; i < (sizeOfRows + 2) ; i++) { // save the data into matrix
		for (int j = 0 ; j < (sizeOfCols + 2) ; j++) {
			
			if ( (i == 0) || (j == 0) || (i == (sizeOfRows + 1)) || (j == (sizeOfCols + 1)) ) { // build the boundary
				theMaze[i][j] = 'W' ; // set up the wall of the maze, using character 'W' to represent it
			} // if
			else {
				fin >> theMaze[i][j] ; // read the character from the file and save it into the maze's matrix
			} // else
			
		} // for
		
	} // for
	
	if (theMode == moreG) { // when the mode is find more goals
		
		do{
			cout << endl << "Number of G (goals): " ;
			cin >> goalsTotalAmount ; // input the goals' total amount
			if (goalsTotalAmount < 1 || goalsTotalAmount > 100) // determine whether the input amount is betweent 1 to 100 
				cout << endl << "### The number must be in [1,100] ###" << endl ;
		} while (goalsTotalAmount < 1 || goalsTotalAmount > 100) ; // input the goals' amount (must between 1 to 100)
		
	} // if
	
	originalMaze = theMaze ; // set initial maze
	theFinalMaze = theMaze ; // set initial maze
	
	return true ;
	
} // load() ;

bool Maze::findOneGoal(Maze & vMaze, int x, int y, int lastDir) { // the function for find a goal

  if (!whetherMove(x, y)) { // determine whether the rat can move
      return false ;
  } // if
		
	vector< vector<char> > temp = vMaze.getMaze() ; // vector for temporary storage
	bool success = false ; // boolean to determine whether find the goal

	if (temp[x][y] == 'G') { // determine whether find the goal
		return true ;
	} // if
	
	vMaze.setLocationState(x, y, 'V') ; // set the visited location

  int arrayOfAllDirRow[] = {0, 1, 0, -1} ; // array used to record all directions {right, down, left, up}
  int arrayOfAllDirCol[] = {1, 0, -1, 0} ; // array used to record all directions {right, down, left, up}

	int nextDir, nextRow, nextCol ; // the variables to record direction or coordinate(row, column)

	for (int i = 0 ; i < 4 ; i++) { // a loop to find four directions whether can move
		nextDir = (lastDir + i) % 4 ; // the same or next direction
    nextRow = x + arrayOfAllDirRow[nextDir] ; // the same or next row
    nextCol = y + arrayOfAllDirCol[nextDir] ; // the same or next column
    
		if (whetherMove(nextRow, nextCol) && temp[nextRow][nextCol] != 'V') { // whether the rat can move in the next direction
			success = findOneGoal(vMaze, nextRow, nextCol, nextDir) ; // go to the next direction by recursion
			
			if (success) { // if find the path, return true
				theFinalMaze[x][y] = 'R' ; // mark current location with 'R'
				return true ;
			} // if
			
		} // if
		
	} // for

  return false ; // do not find the path, return false
  
} // findOneGoal() ;

bool Maze::findMoreGoals(Maze & vMaze, int x, int y, int & goalsLastAmount, int lastDir) { // the function for find more goals
  
  if (!whetherMove(x, y) ) { // determine whether the rat can move
    return false;
  } // if
		
	vector< vector<char> > temp = vMaze.getMaze() ; // vector for temporary storage of maze 
	bool success = false ; // boolean to determine whether find the goal

	if (temp[x][y] == 'G') { // when a goal is found and current goal is not repeated
		goalsLastAmount-- ; // every time a goal is found, the total number of goals is reduced by one.

		if (goalsLastAmount == 0) { // when all of the goals are found, return true
			return true ;
		} // if
		
	} // if

	vMaze.setLocationState(x, y, 'V') ; // set the visited location when current location is not goal
	theMaze[x][y] = 'R' ; // mark current locatio with 'R'

  int arrayOfAllDirRow[] = {0, 1, 0, -1} ; // array used to record all directions {right, down, left, up}
  int arrayOfAllDirCol[] = {1, 0, -1, 0} ; // array used to record all directions {right, down, left, up}
  
	int nextDir, nextRow, nextCol ; // the variables to record direction or coordinate(row, column)

	for (int index = 0 ; index < 4 ; index++) { // a loop to find four directions whether can move
		nextDir = (lastDir + index) % 4 ; // the same or next direction
    nextRow = x + arrayOfAllDirRow[nextDir] ; // the same or next row
    nextCol = y + arrayOfAllDirCol[nextDir] ; // the same or next column
    
		if (whetherMove(nextRow, nextCol) && temp[nextRow][nextCol] != 'V') { // whether the rat can move in the next direction

			findMoreGoals(vMaze, nextRow, nextCol, goalsLastAmount, nextDir) ; // go to the next direction by recursion
			
			if (goalsLastAmount == 0) { // when all goals are found, return true
				return true ;
			} // if
			
		} // if
		
	} // for
	
	theMaze[x][y] = originalMaze[x][y] ; // restore the maze to original state

	return false ;
  
} // findMoreGoals() ;

bool Maze::whetherMove(int x, int y) { // the function for determine whether can the rat move

	return (theMaze[x][y] != 'W' && theMaze[x][y] != 'O' && (theMaze[x][y] == 'E' || theMaze[x][y] == 'G')) ;
	// determine whether current location is not walls or obstacles, either empty or goals
	
} // whetherMove

void Maze::show() { // the function for show out the matrix

	for (int i = 1 ; i < sizeOfRows + 1 ; i++) { // save the data into matrix
		for (int j = 1 ; j < sizeOfCols + 1 ; j++) {
			if (originalMaze[i][j] == 'G') // make sure the goal will not be disappear
				cout << 'G' ;
			else
				cout << theMaze[i][j] ; // print out each location
		} // for
		
		cout << endl ;
	} // for
	
	cout << endl ;
	
} // show() ;

void Maze::showTheFinalPath() { // the function for print out the final path

	for (int i = 1 ; i < sizeOfRows + 1 ; i++) { // print out the final path
		for (int j = 1 ; j < sizeOfCols + 1 ; j++) {
			
			if (originalMaze[i][j] == 'G') // make sure the goal will not be disappear
				cout << 'G' ;
			else
				cout << theFinalMaze[i][j] ; // print out each location
				
		} // for
		
		cout << endl ;
	} // for
	
	cout << endl ;
	
} // showTheFinalPath() ;

void Maze::clr() { // the function for clear up the content

	theMaze.clear() ; // clear up the matrix
	
} // clr() ;

void Maze::setLocationState(int x, int y, char word) { // a setter to set the visited location

	theMaze[x][y] = word ;

} // setVisitedLocation() ;

void Maze::copyThePathOfMaze() { // the function for copy the path of maze to the final maze

	for (int i = 1 ; i < sizeOfRows + 1 ; i++) { 
		for (int j = 1 ; j < sizeOfCols + 1 ; j++) {
			
			if (theMaze[i][j] == 'R') { // the function for copy theMaze's 'R' to the final maze
				theFinalMaze[i][j] = 'R' ;
			} // if
				
		} // for
		
	} // for

} // copyThePathOfMaze() ;

void Maze::resetTheMaze() { // the function for reset the maze

	theMaze = originalMaze ; // set the maze to the original state

} // resetTheMaze() ;

int main(void) { // the main function
	
	int command = 0 ; // user's input command
	
	do {
		Maze aMaze ; // the original matrix
		string fileNumber ; // the file name
		Modes mode = oneG ; // the default mode : one goal
		int goalsTotalAmount = 0 ; // the number of target's amount
		
		cout << endl << "*** Path Finding ***" ;
		cout << endl << "* 0. Quit          *" ;
		cout << endl << "* 1. One goal      *" ;
		cout << endl << "* 2. More goals    *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2): " ;
		cin >> command ; // get the command
		
		if ((command == 1) || (command == 2)) {
			
			cout << endl << "Input a file number: " ;
			cin >> fileNumber ;
			
			if (command == 2) { // command 2 : more goals
				mode = moreG ; // one or more goals
			} // if
			
			if (aMaze.load(fileNumber, mode, goalsTotalAmount)) { // the function for load the original matrix
				Maze vMaze(aMaze) ; // copy the original matrix and keep visited cells
				bool success = false ; // a boolean to determine whether find the path
				
				if (mode == oneG) { // one goal mode
					success = aMaze.findOneGoal(vMaze, 1, 1, 0) ; // the function for find a path to goal
				} // if
				else { // more goals mode
					int count = 0 ; // a variable to count the found goals
					Maze tempOfvMaze ; // a maze for temporary storage of vMaze
					for (int index = 1 ; index <= goalsTotalAmount ; index++) {
						
						int currentGoalAmount = index ; // the current goal amount need to find
						bool found = aMaze.findMoreGoals(vMaze, 1, 1, currentGoalAmount, 0) ; // the function for find a path to goals
						
						tempOfvMaze = vMaze ; // a maze for temporary storage of vMaze
						if (found) { // if found the goal
							aMaze.copyThePathOfMaze() ; // copy the path of maze to the final maze
							vMaze.resetTheMaze() ; // reset the maze(vMaze) 
							aMaze.resetTheMaze() ; // reset the maze(aMaze)
							count++ ; // found a goal
						} // if
						else {
							index = goalsTotalAmount + 1 ; // when can not found the path, break the loop
						} // else
						
					} // for
					
					if (count == goalsTotalAmount) { // determine whether found all the goals
						success = true ;
					} // if
					
					vMaze = tempOfvMaze ; // restore state
					
				} // else
				
				mode = oneG ; // reset the mode
				vMaze.show() ; // show out the visited cells
				
				if (success) { // check whether the goal is reached
					aMaze.showTheFinalPath() ; // show out the final path
				} // if
				
				vMaze.clr() ; // clear up the visited matrix
			} // if
			
			aMaze.clr() ; // clear up the traverse matrix
		} // if
		else if (command == 0) // stop the program
			break ;
		else
			cout << endl << "Command does not exist!" << endl ;
			
	} while (true) ; // do while
	
	system("pause") ; // pause the execution
	return 0 ;
	
} // main()
