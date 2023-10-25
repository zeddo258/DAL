#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

class Maze {
private:
    vector<string> maze;        
    vector<string> clearMaze;   // in order to draw path
    vector<vector<bool> > visited;
    vector<vector<bool> > path;   

public:
    void setMaze(vector<string> inputMaze) {
        maze = inputMaze;
    }
    
    void initvisit(){
		for( int x = 0; x < Rows() ; x++ ){
			for ( int y = 0; y < Cols() ; y++ ){
				visited[x][y] = false;
			}
		} // let visted to init
		
	}

    vector<string> getMaze() {
        return maze;
    }
    
    bool getPath( int x, int y) {
    	return path[x][y];
	}

    void printMaze() {
        for (int j = 0; j < maze.size(); j++) {
            cout << maze[j] << "\n";
        }
        cout << endl;
    }

    int Rows() {
        return maze.size();
    }

    int Cols() {
        return maze[0].size();
    }

    char value(int x, int y) {
        return maze[x][y];
    }

    void setValue(int x, int y, char ch) {
        maze[x][y] = ch;
    }

    void initVisitPath(vector<vector<bool> > init) {
        visited = init;
        path = init;
    }

    vector<vector<bool> > getVisit() {
        return visited;
    }

    bool visitValue(int x, int y) {
        return visited[x][y];
    }

    void setVisit(int x, int y) {
        visited[x][y] = true;
    }
    
    void  setPath(int x, int y ){
    	path[x][y] = true;
	}
	
	void setclearMaze(){
		clearMaze = maze;	}
	
	void printPath(){
		// draw the path
		for( int x = 0; x < Rows() ; x++ ){
			for ( int y = 0; y < Cols() ; y++ ){					
					if( path[x][y] == true && clearMaze[x][y] != 'G' ){ 
						cout << 'R';
					}
					else{
						cout << clearMaze[x][y];
					}
			
			}
			cout << endl;
		}
		cout << endl;
	}
};

bool isLegalChar(string s) {
// the maze only can struct from 'O'¡B'E'¡B'G' 
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != 'O' && s[i] != 'G' && s[i] != 'E') {
            return false;
        }
    }
    return true;
}

bool isDigit(string s, int& num) {
// the file begin is number or not, and return num
    num = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] <= '9' && s[i] >= 0) {
            num = num * 10 + s[i] - '0';
        }
        else {
            return false;
        }
    }

    return true;
}

int mazeInput(Maze& maze) {
    vector<string> inputMaze;
    string fileName;
    cout << endl << "Input a file number:";
    cin >> fileName;
    fileName = "input" + fileName + ".txt";

    // open file
    ifstream inputFile(fileName.c_str()); // let filename end become NULL

    // is open or not
    if (!inputFile.is_open()) {
        cout << endl << fileName << " does not exist!\n";
        return 1;                 // no correct return
    }

    // input length and width
    string length, width;
    int len, wid;
    inputFile >> length >> width;
    if (!isDigit(length, len) || !isDigit(width, wid)) {   // if lenth,width is integer,store at len,wid
        cout << "No enter maze size!\n";
        return 1;                  // no correct return
    }
    vector<vector<bool> > visited(wid, vector<bool>(len, false));  // let all of the maze set false
    maze.initVisitPath(visited);                  // initial visted


    // input the maze
    string line;
    getline(inputFile, line);               // use string store a line
    while (getline(inputFile, line)) {      // until end
        if (line.length() == len) {         // Is maze have correct rows
            if (isLegalChar(line)) {       
                inputMaze.push_back(line);  // add the string to the maze
            }
            else {
                cout << "Not legal character!";
                return 1;                 // no correct return
            }
        }
        else {
            cout << "No correct size!";
            return 1;                   // no correct return
        }
    }
    if (inputMaze.size() != wid) {         // Is maze have correct cols
        cout << "No correct size!";
        return 1;                 // no correct return
    }

    maze.setMaze(inputMaze); // store to maze
	maze.setclearMaze();

    // close file
    inputFile.close();
    return 0;
} // InputMaze

bool isValid(int x, int y, int rows, int cols) {
	// no exceed the range of maze
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

bool multidfs(Maze & maze, int x, int y, int direction, int & Gnum) {
    // Gnum is represent the how many G need pass
    if (maze.value(x, y) == 'G' && maze.visitValue(x,y) == false ) { // if this point is G and no visited,
    	Gnum = Gnum - 1;                                             // Gnum can reduce
    }
    
    if (Gnum <= 0){       // if Gnum = 0 , this recursion is found the end 
    	return true;      // return true to last step
	}


    if (maze.value(x, y) == 'O' || maze.visitValue(x, y) == true) {   // this point can't visited and obstacle
        return false;                                                 // return false to last step , and will take to next direction
    }

	// record this point is visited
    maze.setVisit(x, y);
    if(maze.value(x,y) != 'G'){    // except this point is G, G not to become V
		maze.setValue(x, y, 'V'); 
	}	
	// direction : right, doen, left, up   
	int dx[] = { 0, 1, 0, -1 };
    int dy[] = { 1, 0, -1, 0 };

    // move direction
    for (int i = 0; i < 4; i++) {
        int newIndex = (direction + i) % 4; // search from last time direction
        int newX = x + dx[newIndex];
        int newY = y + dy[newIndex];
        
        if (isValid(newX, newY, maze.Rows(), maze.Cols())) {   // check no exceed the maze
            if (multidfs(maze, newX, newY, newIndex,Gnum)) {
            	/* recursion to next step, if false (already visited or obstacle) will search next step, until find the end or no path to end.
			   		find the end will return true, and will record the path from the end to the start.													  
				*/
        	    maze.setPath(x,y);
				return true;
            }
        }
    }
    // if all be visited or obstacle return false, it is not have path to end
    return false;
}
int main() {
    int command = 0;
    Maze maze;
    string fileName;
    int Gnum = 0;

    do {
        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit          *";
        cout << endl << "* 1. One goal      *";
        cout << endl << "* 2. More goals    *";
        cout << endl << "********************";
        cout << endl << "Input a command( 0, 1, 2): ";
        cin >> command;

        if (command == 1 && mazeInput(maze) == 0) {  // condition 1
        	Gnum = 1;
            if ( multidfs(maze, 0, 0, 0, Gnum ) ) {
                maze.printMaze();
                maze.printPath();
            }
            else {
                maze.printMaze();
            }
        }
        else if (command == 2 && mazeInput(maze) == 0 ) {  // condition 2
        	
        	int leftNum = 1;
        	cout << "\nNumber of G (goals): " ;
        	cin >> Gnum ;    	                        // numbers of G
        	if( Gnum>100 || Gnum < 1) {
        		cout<< "### The number must be in [1,100] ###" << endl; 
        	}
        	else{
	        	while ( Gnum > 0 ) {
	        		maze.initvisit();
	        		if(multidfs(maze,0,0,0,leftNum)){       // It will record the path Gnum times.
	        			leftNum = Gnum;						
	        			Gnum = Gnum - 1;				     
					}
					else{
						Gnum = -1;                          // end the while
					}
	            }
	            if(Gnum == 0){
	                maze.printMaze();
	                maze.printPath();
	        	}
	            else {
	                maze.printMaze();
	            }
	    	}
        	
        }
        else if (command == 0) {
            break;            // when command = 0 ,finish 
        }
        else if ( command > 2 || command < 0){
            cout << "\nCommand does not exist!\n";
        }

    } while (true);

    return 0;
}
