/** 11127110, ³\¦Ü©û *
  * Data Structures  *
  * Exercise 1 Quiz  **/
  
# include <iostream>
# include <string>
# include <fstream>
# include <vector>
# include <sstream>

using namespace std ;

class Maze {
	private :
		int mazeColumn ;         // y
		int mazeRow ;            // x
		int countGoal ;          // total goals
		int shortestPathLength ; // shortest path length
		
		vector< vector< char > > maze ;                  // input maze
		vector< vector< char > > mazeVisited ;           // record maze 'V'
		vector< vector< char > > mazeRoute ;             // record maze 'R'
		vector< vector< char > > mazeRouteAll ;          // record many goals 'R'
		vector< vector< char > > mazeRouteShortestPath ; // record route of shortest path
		vector< string > isGoal ;                        // record goals
			
	public :
		int getCountGoal() ;          // get countGoal
		int getIsGoalSize() ;         // get isGoal size
		int getShortestPathLength() ; // get shortestPathLength
		
		bool isInMaze( int x, int y ) ;                   // if ( x, y ) is in maze and not obstacle
		bool isInMazeRoute( int x, int y ) ;              // if ( x, y ) is in mazeRoute and not obstacle
		bool findPath( int x, int y, int nowDirection ) ; // recursion findPath
		bool setmazeVector() ;                            // input file and set maze
		
		
		void setMazeVisited( int x, int y ) ;          // set mazeVisited
		void setMazeRoute( int x, int y ) ;            // set mazeRoute
		void setMazeRouteEmpty( int x, int y ) ;       // set MazeRoute 'E'
		void setCountGoal( int goal ) ;                // set countGoal
		void setIsGoal( int x, int y ) ;               // record the goals
		void setShortestPathLength( int pathLength ) ; // set pathLength to shortestPathLength 
		void setMazeRouteAll() ;                       // copy mazeRoute to mazeRouteAll	
		void setMazeRouteShortestPath() ;              // renew mazeRouteShortestPath
		
		void findShortestPath( int x, int y, int nowDirection, int pathLength ) ; // find shortest path
		
		void rebuildmazeVisitedRoute() ; // rebuild mazeVisited and mazeRoute
		
		void printMazeVisited() ;           // print mazeVisited
		void printMazeRoute() ;             // print mazeRoute
		void printMazeRouteAll() ;          // print mazeRouteAll
		void printMazeRouteShortestPath() ; // print mazeRouteShortestPath
		
		void clearVector() ; // clear all vectors
		void clearIsGoal() ; // clear isGoal
} ; // class Maze


void Maze::setMazeRouteEmpty( int x, int y ) { // set MazeRoute 'E'
	mazeRoute[x][y] = 'E' ;
} // setMazeRouteEmpty()


void Maze::setMazeRouteShortestPath() { // renew mazeRouteShortestPath
	mazeRouteShortestPath.clear() ;
	mazeRouteShortestPath = mazeRoute ;
} // setMazeRouteShortestPath()


void Maze::setShortestPathLength( int pathLength ) { // set pathLength to shortestPathLength
	shortestPathLength = pathLength ;
} // setShortestPathLength() ;


int Maze::getShortestPathLength() { // get shortestPathLength
	return shortestPathLength ;
} // getShortestPathLength()


bool Maze::setmazeVector() { // input file and set maze
	string fileNumber ;
	string fileName ;
	
	cout << endl << "Input a file number: " ;
	cin >> fileNumber ;
	fileName =  "input" + fileNumber + ".txt" ;
	
	ifstream file( fileName.c_str() ) ; // change fileName from string to char
	
	if( !file.is_open() ) { // if the file not exist
		cout << endl << fileName + " does not exist!" << endl << endl ;
		return false ;
	} // if
	
	else {
	    file >> mazeColumn ; // get mazeColumn
	    file >> mazeRow ;    // get mazeRow
	    
		string line ;
		int lineNumber = 0 ; // count the line number
		while ( getline( file, line ) ) {
		    lineNumber = lineNumber + 1 ; 
		    if ( lineNumber > 1 ) { // start from the second line 
		        vector< char > row ;
		        for ( int i = 0 ; i < mazeColumn ; i = i + 1 ) {
		        	if (line[i] != ' ' && line[i] != '\n') {
		        		row.push_back( line[i] ) ;
		        	} // if
		        } // for
		        
		        maze.push_back( row ) ;         // get maze
		        mazeVisited.push_back( row ) ;  // initialize mazeVisited
		        mazeRoute.push_back( row ) ;    // initialize mazeRoute
		        mazeRouteAll.push_back( row ) ; // initialize mazeRouteAll
		    } // if
		} // while

		return true ;
	} // else
} // setmazeVector()


bool Maze::isInMaze( int x, int y ) { // if ( x, y ) is in maze and empty or goal
    if ( x >= 0 && x < mazeRow && y >= 0 && y < mazeColumn && ( maze[x][y] == 'E' || maze[x][y] == 'G' ) ) {
    	return true ;
	} // if
    else {
    	return false ;
	} // else
} // isInMaze()


bool Maze::isInMazeRoute( int x, int y ) { // if ( x, y ) is in mazeRoute and empty or goal
    if ( x >= 0 && x < mazeRow && y >= 0 && y < mazeColumn && ( mazeRoute[x][y] == 'E' || maze[x][y] == 'G' ) ) { 
    	return true ;
	} // if
    else {
    	return false ;
	} // else
} // isInMazeRoute()


void Maze::rebuildmazeVisitedRoute() { // rebuild mazeVisited and mazeRoute
	mazeVisited.clear() ;
	mazeRoute.clear() ;
	mazeVisited = maze ;
	mazeRoute = maze ;
} // rebuildmazeVisitedRoute()


void  Maze::setMazeVisited( int x, int y ) { // set mazeVisited
	mazeVisited[x][y] = 'V' ;
} // setMazeVisited()


void  Maze::setMazeRoute( int x, int y ) { // set mazeRoute
	mazeRoute[x][y] = 'R' ;
} // setMazeRoute()


void Maze::setCountGoal( int goal ) { // set countGoal
	countGoal = goal ;
} // setCountGoal()


int Maze::getCountGoal() { // get countGoal
	return countGoal ;
} // getCountGoal()


void Maze::clearVector() { // clear all vectors
	maze.clear() ;
	mazeVisited.clear() ;
	mazeRoute.clear() ;
	isGoal.clear() ;
	mazeRouteAll.clear() ;
} // clearVector()


void Maze::clearIsGoal() { // clear isGoal
	isGoal.clear() ;
} // clearIsGoal()


int Maze::getIsGoalSize(){ // get isGoal size
	return isGoal.size() ;
} // getIsGoalSize()


void Maze::setIsGoal( int x, int y ) { // record the goals
	stringstream stringstreamX, stringstreamY ;
	stringstreamX << x ;
	stringstreamY << y ;
	string stringX = stringstreamX.str() ; // change x from int to string
	string stringY = stringstreamY.str() ; // change y from int to string
	
	string stringGoal = stringX + "," + stringY ; // "x,y"
	
	if ( isGoal.size() == 0 ) { // if "x,y" the first goal
		isGoal.push_back( stringGoal ) ;
	}  // if
	
	else {		
		bool inIsGoal = false ;
		
		for ( int i = 0 ; i < isGoal.size() ; i = i + 1 ) {
			if ( isGoal[i].compare( stringGoal ) == 0 ){ // if "x,y" in isGoal
				inIsGoal = true ;
			} // if
		} // for
		
		if ( inIsGoal == false ) { // if "x,y" not in isGoal
			isGoal.push_back( stringGoal ) ;
		} // if
	} // else
} // setIsGoal()


void Maze::findShortestPath( int x, int y, int nowDirection, int pathLength ) { // find shortest path
	int xDirection[] = { 0, 1, 0, -1 } ; // right[0], down[1], left[2], up[3]
	int yDirection[] = { 1, 0, -1, 0 } ; // right[0], down[1], left[2], up[3]
	
	if ( !isInMazeRoute( x, y ) || maze[x][y] == 'O' ) { // if not in mazeRoute or obstacle
		return ;
	} // if
	
    if ( getShortestPathLength() != 0 && getShortestPathLength() <= pathLength ) { // if shortestPathLength exist and pathLength bigger or equal than shortestPathLength
		return ;
	} // if 	

	if ( maze[x][y] == 'G' ) { // find the goal
		if ( getShortestPathLength() == 0 || getShortestPathLength() > pathLength ) { // if shortestPathLength is not exist or bigger than pathLength		
			setShortestPathLength( pathLength ) ; // set pathLength to shortestPathLength
    		setMazeRouteShortestPath() ; // renew mazeRouteShortestPath
		} // if	
		
		return ;
	} // if
	
	setMazeVisited( x, y ) ; // set ( x, y ) is visited
	setMazeRoute( x, y ) ; // set ( x, y ) is route
	
	for ( int i = 0 ; i < 4 ; i = i + 1 ) { // try four directions
    	int newX = x + xDirection[nowDirection] ;
        int newY = y + yDirection[nowDirection] ;
        int newDirection = ( nowDirection + i ) % 4 ; // next direction
        
		findShortestPath( newX, newY, newDirection, pathLength + 1 ) ;
    } // for
    
    setMazeRouteEmpty( x, y ) ; // set ( x, y ) back to empty
    return ;
} // findShortestPath()


bool Maze::findPath( int x, int y, int nowDirection ) { // recursion findPath
	int xDirection[] = { 0, 1, 0, -1 } ; // right[0], down[1], left[2], up[3]
	int yDirection[] = { 1, 0, -1, 0 } ; // right[0], down[1], left[2], up[3]
	
	if ( !isInMaze( x, y ) || maze[x][y] == 'O' || mazeVisited[x][y] == 'V' ) { // if ( x, y ) not in maze or obstacle or is visited
		return false ;
    } // if
	
	setMazeVisited( x, y ) ; // set ( x, y ) is visited	
	
	if ( maze[x][y] == 'G' ) { // find the goal
		setIsGoal( x, y ) ; // set ( x, y ) is goal
		if ( getIsGoalSize() == getCountGoal() ) { // if the amount of found goals same as input goals
			return true ;
		} // if
    } // if

    for ( int i = 0 ; i < 4 ; i = i + 1 ) { // try four directions
    	int newX = x + xDirection[nowDirection] ;
        int newY = y + yDirection[nowDirection] ;
        
        if ( findPath( newX, newY, nowDirection ) == true ) {
        	if ( maze[x][y] != 'G' ) { // if ( x, y ) not goal
        		setMazeRoute( x, y ) ; // set ( x, y ) is route
			} // if
			
            return true ;
    	} // if
    	else {
    		nowDirection = ( nowDirection + 1 ) % 4 ; // next direction    		
		} // else
    } // for
    
	return false ;
} // findPath()


void Maze::setMazeRouteAll() { // copy mazeRoute to mazeRouteAll
	for ( int i = 0 ; i < mazeRow ; i = i + 1 ) {
        for ( int j = 0 ; j < mazeColumn ; j = j + 1) {
        	if ( mazeRoute[i][j] == 'R' ) {
        		mazeRouteAll[i][j] = 'R' ;
			} // if
		} // for
    } // for	
} // setMazeRouteAll()


void Maze::printMazeVisited() { // print mazeVisited
	for ( int i = 0 ; i < mazeRow ; i = i + 1 ) {
        for ( int j = 0 ; j < mazeColumn ; j = j + 1) {
        	if ( maze[i][j] == 'G' ) {
        		cout << 'G' ;
			} // if
        	else {
        		cout << mazeVisited[i][j] ;
			} // else
		} // for
		cout << endl ;
    } // for
    cout << endl ;
} // printMazeVisited()


void Maze::printMazeRoute() { // print mazeRoute
    for ( int i = 0 ; i < mazeRow ; i = i + 1 ) {
        for ( int j = 0 ; j < mazeColumn ; j = j + 1) {
        	cout << mazeRoute[i][j] ;
		} // for
		cout << endl ;
    } // for
	cout << endl << endl ;
} // printMazeRoute()


void Maze::printMazeRouteAll() { // print mazeRouteAll
    for ( int i = 0 ; i < mazeRow ; i = i + 1 ) {
        for ( int j = 0 ; j < mazeColumn ; j = j + 1) {
        	cout << mazeRouteAll[i][j] ;
		} // for
		cout << endl ;
    } // for
	cout << endl << endl ;
} // printMazeRouteAll()


void Maze::printMazeRouteShortestPath() { // print mazeRouteShortestPath
    for ( int i = 0 ; i < mazeRow ; i = i + 1 ) {
        for ( int j = 0 ; j < mazeColumn ; j = j + 1) {
        	if ( maze[i][j] == 'G' ) {
        		cout << 'G' ;
			} // if
        	else {
        		cout << mazeRouteShortestPath[i][j] ;
			} // else
        	
		} // for
		cout << endl ;
    } // for
	cout << endl << endl ;	
	
} // printMazeRouteShortestPath()




int main() {
	int command = 0 ;
	int goal = 0 ; 
	bool findPathBool = false ;

	do {
		cout << "*** Path Finding ***" << endl ;
		cout << "* 0. Quit          *" << endl ;
		cout << "* 1. One goal      *" << endl ;
		cout << "* 2. More goals    *" << endl ;
		cout << "* 3. Shortest path *" << endl ;
		cout << "********************" << endl ;
		
		cout << "Input a command(0, 1, 2, 3): "  ;	
		cin >> command ;
		
		if ( command == 0 ){ // quit
			break ;
		} // if
		else if ( command == 1 ){
			Maze aMaze ;
			
			bool getFile = aMaze.setmazeVector() ;
			if ( getFile == true ) {
				goal = 1 ;
				aMaze.setCountGoal( goal ) ; // set countGoal is one
				
				findPathBool = aMaze.findPath( 0, 0, 0 ) ; // ( x, y, right )
	    		
	    		aMaze.printMazeVisited() ;
	    		if ( findPathBool == true ) { // if maze has route
	    			aMaze.printMazeRoute() ;
				} // if						
			} // if

			aMaze.clearVector() ;
		} // else if
		else if ( command == 2 ){			
			Maze aMaze ;
			
			bool getFile = aMaze.setmazeVector() ; 
			if ( getFile == true ) { // if file exist
				cout << endl << "Number of G (goals): " ;
				cin >> goal ; // input goals
				
				while ( goal < 1 || goal > 100 ) { // goal must be one to one hundred
					cout << endl << "### The number must be in [1,100] ###" << endl ;
					cout << endl << "Number of G (goals): " ;
					cin >> goal ; // input goals again
				} // while

				for ( int i = 1 ; i <= goal ; i = i + 1 ) { // from one to goals
					aMaze.setCountGoal( i ) ; // set countGoal is i
					
					findPathBool = aMaze.findPath( 0, 0, 0 ) ; // ( x, y, right )
					
		    		if ( findPathBool == true ) { // if maze has route
		    			aMaze.setMazeRouteAll() ;	
					} // if
					
					aMaze.clearIsGoal() ;
					
					if ( i != goal ) { // if not final goals
						aMaze.rebuildmazeVisitedRoute() ;
					} // if					
				} // for
				
				aMaze.printMazeVisited() ;
	    		if ( findPathBool == true ) { // if maze has route
	    			aMaze.printMazeRouteAll() ;
				} // if				
			} // if

			aMaze.clearVector() ;
		} // else if
		else if ( command == 3 ){
			Maze aMaze ;
			
			aMaze.setShortestPathLength( 0 ) ; // initialize setShortestPathLength
			
			bool getFile = aMaze.setmazeVector() ;
			if ( getFile == true ) {
				aMaze.findShortestPath( 0, 0, 0, 1 ) ; // ( x, y, right, pathlength )
	    		
	    		aMaze.printMazeVisited() ;
	    		if ( aMaze.getShortestPathLength() != 0 ) { // if find goal
	    			aMaze.printMazeRouteShortestPath() ; // print mazeRouteShortestPath
					cout << "Shortest path length = " << aMaze.getShortestPathLength() << endl ; // print shortestPathLength
				} // if
				else {
					cout << endl << "### There is no path to find a goal! ###" << endl ;
				} // else				
			} // if
			
			aMaze.clearVector() ;
			
			system( "pause" ) ;
		} // else if
		else{
			cout << endl << "Command does not exist!" << endl << endl ;
		} // else
	} while( command != 0 ) ;

	system( "pause" ) ;
	return 0 ;
} // main()

