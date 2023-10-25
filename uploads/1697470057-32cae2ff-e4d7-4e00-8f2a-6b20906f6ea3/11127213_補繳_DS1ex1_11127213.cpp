// 11127213 ­â¹©°a 

# include <iostream>
# include <cstdio> 
# include <string>
# include <stdlib.h>
# include <string.h>
# include <vector>

# define READIN_SIZE 10000

using namespace std;


class Coordinate {
	
	public:
		
		Coordinate()  {
			
            previousLength = 99999;                   // If the length remains 99999, means no path found
            theFirstTime = false;
			
		}
		
		int getX() {
			
			return current.x;
			
		}
		
		int getY()  {
			
			return current.y;
			
		}
		
		int getLength()  {
			
			return coord.size();
			
		}
		
		void push( int x, int y )  {                // Push the coordinate into the vector
			
			current.x = x;
			current.y = y;
			
			coord.push_back( current );		
			
		}
		
		void pop()  {                              // pop the element
			
			coord.pop_back();
			
		}
	    
	    int getPreviousLength()  {
	    	
	    	return previousLength;
	    	
		}
	    
	    void setPreviousLength( int number )  {
	    	
	    	previousLength = number;
	    	
		}
		
		bool getTheFirstTime() {
			
			return theFirstTime;
			
		}
		
		void setTheFirstTime()  {
			
			theFirstTime = true;
			
		}
		
	private:
		
		struct coordinate {
			
			int x;
			int y;
			
		};
		
		coordinate current;             // Store the x and y in a sturct
        vector<coordinate > coord;      // store the position of the shortest route
        int previousLength;             // The length of the shortest path
        bool theFirstTime;              // Whether find a path or not
	    
};

class Maze {
	
	public:
		
        enum Direction {
	
	// The number is for debugging purposes.
	
	        UP = 0,                  
	        DOWN = 1,
	        LEFT = 2,
	        RIGHT = 3
	
        };
        
        enum Modes {        // This is the mode option. It only has two options here.
	
	        oneG,          // One goal.
	        moreG,          // Multiple goal.
	        shortestG
	
        };
        
        char** maze;
		
		Maze();                                      // Constructor, this will also initialize data members, like current position.
		
		Maze( const Maze& aMaze );                   // This constructor will copy the maze to the created object.
		
		bool setUpMaze( string fileName );            // Import and read the file into the 2D array.
		
		void passedToGoal();                          // Change the 'P' in the visited Maze to 'G'.
		
		void refresh();                               // Clean all the 'V'( visited cell ) to 'E'( empty cell ).
		 
		void labelVisited( int x, int y );            // Label 'V' in the visited Maze on the position x and y.
		
		void labelRoute( int x, int y );              // Label 'R'( Route ) on the position x and y.
		
		void clr();                                  // This public function will invoke freeMaze function.
		
		char& getChar( int x, int y );               // char& means char reference. It means making a reference to a variable.
		                                             // If the reference is changed, the original will also be changed.
		
		bool IsValid( int x, int y );  // If the current position is beyond the
		                                    // boundary of the maze.
		                                              
		bool IsGoal( int cx, int y );       // If the current position is the goal.
		
		void displayMaze();                 // Print out the maze.
		
		bool findGoal( Maze& vMaze, Direction direction, int x, int y, int turns );   // find the route to the
		                                                                                // goal. Return true when find a path
	                                                                                    // Return false when encounter dead end.
	    
	    Direction getDirection();           // get the direction of the current maze object.                                     
	    
	    void setDirection( Maze::Direction direction );  // set the direction of the current maze object.
	    
	    void setMode( int command );                     // set mode.
	    
	    void clearRoute();                               // turn all 'R' to 'E'
	    
	    void paintTheRoute( Maze cleaner );              // draw the current shortest route
	    
	    void findShortestGoal( Maze& vMaze, Maze& cleaner, Direction direction, int x, int y, int turns, Coordinate& coord );
	        
	private:
		
		int width;
		int height;
		Direction dir;
		Modes mode;
		int loop_time;
		int maximum_loop;
		
		// functions that are private will all be auxiliary or not intended for user to use.
		
		char** create2DArray( int width, int height );       // Dynamically allocate 2D array.
		void freeMaze();                                     // Free the maze. Prevent memory leak.
		
		// These functions are used for checking the input file have no problem.
		
		bool AllDigits( char str[] );                                       // Check if the first row only contain number.
		
		bool readInTwoNumbers( char str[], string& str1, string& str2 );    // This function worked as follow:
		                                                                    // 1. If there is only one number, return false.
		                                                                    // 2. If there are more than two numbers, read in
		                                                                    //    the first two numbers. The rest will be discarded.
		
		
		int stringToInt( string str );                                      // Turn the valid string into number.
		bool checkTheInput( char str[] );                                   // Check if the first row has no problem.
		bool checkTheCells();                                               // Check for invalid character in the maze.
		
		
};

bool Maze::IsValid( int x, int y )  {         // Check if the current position is still inside the maze.

    if ( x < 0 || x >= height || y < 0 || y >= width )  return false;
	
	if ( maze[x][y] == 'O' || maze[x][y] == 'V' )    return false;
	
    return true;
	
}

void Maze::setMode( int command )  {
	
	if ( command == 1 )
	    mode = oneG;
	
	else if ( command == 2 )
	    mode = moreG;
	    
	else if ( command == 3 )
	    mode = shortestG;
	
}

Maze::Direction Maze::getDirection()  {         // Get the direction
	
	return dir;
	
}

void Maze::setDirection( Maze::Direction direction )  {  // Set the direction
	
	dir = direction;
	
}

void Maze::clearRoute()  {                      // turn 'R' to 'E'
	
	int i = 0, j = 0;
	
	for ( i = 0 ; i < height ; i++ )
	    for ( j = 0 ; j < width ; j++ )
		    if ( maze[i][j] == 'R' )
			    maze[i][j] = 'E'; 
	
}

void Maze::paintTheRoute( Maze cleaner )  {     // Paint 'R' on the cleaner maze
	
    int i = 0, j = 0;
    
    for ( i = 0 ; i < height ; i++ )
        for ( j = 0 ; j < width ; j++ )
            if ( cleaner.maze[i][j] == 'V' )
                this -> maze[i][j] = 'R';
	
}


// mission 3 function
void Maze::findShortestGoal( Maze& vMaze, Maze& cleaner, Direction direction, int x, int y, int turns, Coordinate& coord )  {
	
	// cout << loop_time << endl;
	if ( loop_time >= maximum_loop )  return;
	
	loop_time += 1;
	coord.push( x, y );
	
	if ( vMaze.IsGoal( x, y ) )  {              // If the current cell is a Goal.
		
		if ( !coord.getTheFirstTime() )   {     // If reached the first goal
		
		    coord.setTheFirstTime();            // set the first time variable to true
		    coord.setPreviousLength( coord.getLength() - 1 ); // record the length
		    this -> paintTheRoute( cleaner );
		    
	    }
		    
    	else {                                  // Find another path
 
            int length = coord.getLength();     // get the length
            
		    this -> clearRoute();                   // clean the maze 
            
		    if ( length < coord.getPreviousLength() )  {   // If the current route is shorter
		    
			    coord.setPreviousLength( length - 1 );  // set the shortest to it
			    this -> paintTheRoute( cleaner );       // Paint the route on aMaze
			    
            }
		
	    }
		
		coord.pop();
		return;
		
    }

	vMaze.labelVisited( x, y );             // Label it as visited cell.
	cleaner.labelVisited( x, y );

    while ( turns < 4 )  {                      // When turns >= 4, that means it is a dead end.
	
	    if ( direction == RIGHT && turns < 4 )  {        // If the previous direction is RIGHT and still have turns
		
		    // If the next move is still in the maze
		    // It is either an empty cell or a goal or a Passed goal
		    // It is not visited
		
            if ( cleaner.IsValid( x, y + 1 ) )  {      // If the right cell is valid to walk on              
		     	
		     	
		     	// if the maze haven't found a route or the length of currnet steps is shorter than the previous one's
		     	if ( !coord.getTheFirstTime() || coord.getLength() < coord.getPreviousLength() )
		     	    findShortestGoal( vMaze, cleaner, RIGHT, x, y + 1, 0, coord );
		     	
		    }
		
		    // If the road on the right is blocked
		    direction = DOWN;       // move down
		    turns++;                // changing one direction, turns + 1
		
        }
        
        // The other three directions work the same as the code above
        // Just change the direction
        
	    if ( direction == DOWN && turns < 4 )  {
	    	
            if ( cleaner.IsValid( x + 1, y ) )  {
		     	
		     	if ( !coord.getTheFirstTime() || coord.getLength() < coord.getPreviousLength() )
		     	    findShortestGoal( vMaze, cleaner, DOWN, x + 1, y, 0, coord );
				
		    }
	     
	        direction = LEFT;
		    turns++;
	    
        }
        
	    if ( direction == LEFT && turns < 4 )  {
	    	
            if ( cleaner.IsValid( x, y - 1 ) )  {
		          	
		     	if ( !coord.getTheFirstTime() || coord.getLength() < coord.getPreviousLength() )
		     	    findShortestGoal( vMaze, cleaner, LEFT, x, y - 1, 0, coord );
		     	
		    }  
			 
		    direction = UP;
		    turns++;
		
        }
        
	    if ( direction == UP && turns < 4 )  {
	    	
            if ( cleaner.IsValid( x - 1, y ) )  {
		     	
		     	if ( !coord.getTheFirstTime() || coord.getLength() < coord.getPreviousLength() )
		     	    findShortestGoal( vMaze, cleaner, UP, x - 1, y, 0, coord );
		     	
		    }
		
		    direction = RIGHT;
		    turns++;
		
        }
        
    }
        
    cleaner.getChar( x, y ) = 'E';
    coord.pop();
    return;    // If four turns limit is reached, that means dead end and should return false
    
}

bool Maze::findGoal( Maze& vMaze, Direction direction, int x, int y, int turns )  {
	
	if ( vMaze.IsGoal( x, y ) )  {              // If the current cell is a Goal.
		
		vMaze.getChar( x, y ) = 'P';            // Label it as 'P' and return true for we found a path.
		
		return true;
		
    }

    else if ( vMaze.getChar( x, y ) != 'P' )    // If the current cell is not 'P'( Passed Goal ).
	    vMaze.labelVisited( x, y );             // Label it as visited cell.

    while ( turns < 4 )  {                      // When turns >= 4, that means it is a dead end.
	
	    if ( direction == RIGHT && turns < 4 )  {        // If the previous direction is RIGHT and still have turns
		
		    // If the next move is still in the maze
		    // It is either an empty cell or a goal or a Passed goal
		    // It is not visited
		
            if ( vMaze.IsValid( x, y + 1 ) )  {
		     	
		     	    if ( findGoal( vMaze, RIGHT, x, y + 1, 0 ) )  {              // Move on the same direction
					 
					    if ( !( vMaze.getChar( x, y ) == 'P' ) )  {                 // If we find a path, and it is not passed
		                    this -> labelRoute( x, y );                          // backtracing and label all the previous cell to 'R'
		                    
		                }
		                
		                return true;                                             
		                
		            }
		     	
		    }
		
		    // If the road on the right is blocked
		    direction = DOWN;       // move down
		    turns++;                // changing one direction, turns + 1
		
        }
        
        // The other three directions work the same as the code above
        // Just change the direction
        
	    if ( direction == DOWN && turns < 4 )  {
	    	
            if ( vMaze.IsValid( x + 1, y ) )  {
		     	
		     	    if ( findGoal( vMaze, DOWN, x + 1, y, 0 ) )  {
					 
					    if ( !( vMaze.getChar( x, y ) == 'P' ) )  {
						
		                    this -> labelRoute( x, y );
		                    
		                }
		                return true;
		                
		            }
		     	
	        }
	     
	        direction = LEFT;
		    turns++;
	    
        }
        
	    if ( direction == LEFT && turns < 4 )  {
	    	
            if ( vMaze.IsValid( x, y - 1 ) )  {
		          	
		     	    if ( findGoal( vMaze, LEFT, x, y - 1, 0 ) )  {
					 
					    if ( !( vMaze.getChar( x, y ) == 'P' ) )  {
						
		                    this -> labelRoute( x, y );
		                    
		                }
		                return true;
		                
		            }
		     	
		    }  
			 
		    direction = UP;
		    turns++;
		
        }
        
	    if ( direction == UP && turns < 4 )  {
	    	
            if ( vMaze.IsValid( x - 1, y ) )  {
		     	
		     	    if ( findGoal( vMaze, UP, x - 1, y, 0 ) ) {
					 
					    if ( !( vMaze.getChar( x, y ) == 'P' ) )  {
						
		                    this -> labelRoute( x, y );
		                    
		                }
		                return true;
		                
		            }
		    }
		
		    direction = RIGHT;
		    turns++;
		
        }
        
    }
        
    return false;    // If four turns limit is reached, that means dead end and should return false
    
}

void Maze::passedToGoal()  {                       // Changing all the 'P's to 'G's
	
	int i = 0, j = 0;
	for ( i = 0 ; i < height ; i++ )  {
		for ( j = 0 ; j < width ; j++ )  {
			
			if ( getChar( i, j ) == 'P' )
			    getChar( i, j ) = 'G';
			
		}
		
	}
	
}

char& Maze::getChar( int x, int y )  {             // This worked as a getter and a setter
	                                               // char& means make a reference to the character it pointed to
	return maze[x][y];                             // If the reference is changed, original object changed to
	
}

Maze::Maze()  {                                    // Initialize the private data members
	
	width = 0;
	height = 0;
	dir = RIGHT;
	maze = NULL;
	mode = oneG;	
	
}

void Maze::refresh()  {                            // Clean the visited maze, so the same maze can be used multiple times
	
	int i = 0, j = 0;
	for ( i = 0 ; i < height ; i++ )  {
		
		for ( j = 0 ; j < width ; j++ )  {
			
			if ( maze[i][j] == 'V' )
			    maze[i][j] = 'E';
			
		}
		
	}
	
}

void Maze::labelRoute( int x, int y )  {           // Label ( x, y ) 'R'
	
	maze[x][y] = 'R';
	
}

void Maze::labelVisited( int x, int y )  {         // Label ( x, y ) 'V'
	
	maze[x][y] = 'V';
	
}

bool Maze::IsGoal( int x, int y )  {               // Check if the current position is goal cell
	
	if ( maze[x][y] == 'G' )  return true;
	return false;
	
}

void Maze::clr()  {                               // Call the freeMaze() function to release the memory
	
	int i = 0 ;
	
    freeMaze();
	dir = RIGHT;
	width = 0;
	height = 0;
	
}

void Maze::displayMaze()  {                       // Print out the maze
	
	int i = 0, j = 0;
	for ( i = 0 ; i < height ; i++ ) {
		for ( j = 0 ; j < width ; j++ )
		    cout << maze[i][j];
		cout << endl;
		
	}
	
}

Maze::Maze( const Maze& aMaze )  {               // The caller maze will be initialized and the maze will be copied from argument aMaze
	
	int i = 0, j = 0;
	width = aMaze.width;
	height = aMaze.height;
	dir = RIGHT;
	maze = NULL;
	mode = aMaze.mode;
	
	maze = create2DArray( width, height );       // create a 2D array
	
	while ( i < height ) {	
		while ( j < width )  {
			
			maze[i][j] = aMaze.maze[i][j];       // copy the maze from aMaze
			j++;
			
		}
		
		j = 0;
		i++;
		
	}
	
}

void Maze::freeMaze()  {                         // release the dynamically allocated 2D array
		
	int i = 0;

	while ( i < height )  {
		

		free( maze[i] );                         // free the individual 1D array first
		i++;
		
	}
	
	free( maze );                                // free the last array
	
}


char** Maze::create2DArray( int width, int height )  {               // Create a 2D array with the size of width and height
	
	int i = 0;
    char** maze = ( char** )calloc( height, sizeof( char* ) );
	while ( i < height )  {
		
		maze[i] = ( char* )calloc( width, sizeof( char ) );
		i++;
		
	}
	
	return maze;
	
}

bool Maze::AllDigits( char str[] )  {                      // Check if the first line only contain digits, spaces, and newline.
	
	int i = 0;
	
	for ( i = 0 ; i < strlen( str ) ; i++ )  {
		
		if ( str[i] == ' ' || str[i] == '\n' )
		    continue;
		
		else if ( str[i] < '0' || str[i] > '9' )
		    return false;
		
	}
	
	return true;
	
}

bool Maze::readInTwoNumbers( char str[], string& str1, string& str2 )  {      // Read in two strings and put them in str1 and str2
	
	int i = 0;
	bool getOneStr = false;

	for ( i = 0 ; i < strlen( str ) ; i++ )  {
		
		if ( str[i] != ' ' && str[i] != '\n' )  {
			
			if ( getOneStr )                            // If the str1 is ended, add to str2
			    str2 = str2 + str[i];
			    
			else
			    str1 = str1 + str[i];                   
			
		}
		
		else if ( str[i] == ' ' && str1.length() != 0 && !getOneStr )
            getOneStr = true;
		
		else if ( str[i] == ' ' && str2.length() != 0 )
			return true;
			
		else if ( str[i] == '\n' && ( str1.length() == 0 || str2.length() == 0 ) )  {
		
		    cout << endl << "Insufficient Number!" << endl;
		    return false;
		    
	    }
		
	}
	
	return true;
 	
}
 
int Maze::stringToInt( string str )  {                // Change valid string into number( int )
	
	int i = 0, sum = 0;
	
	while ( i < str.length() )  {
		
		sum = sum * 10 + ( str[i] - '0' );
		i++;
		
	}
	
	return sum;
	
}

bool Maze::checkTheCells()  {              // Check if the original maze contains any unknown characters
	
	int i = 0, j = 0;
	for ( i = 0 ; i < height ; i++ )
	    for ( j = 0 ; j < width ; j++ )
	        if ( maze[i][j] != 'E' && maze[i][j] != 'O' && maze[i][j] != 'G' )
	            return false;
	            
	return true;
	
}

bool Maze::checkTheInput( char str[] )  {  // Check and read the input to width and height
	
	string str1 = "";
	string str2 = "";
	width = 0;
	height = 0;
	
    if ( AllDigits( str ) )  {
    	
    	if ( !readInTwoNumbers( str, str1, str2 ) )
    	    return false;
    	
    	width = stringToInt( str1 );
    	height = stringToInt( str2 );
    	return true;
    	
	}
	
	else  {

	    cout << "\nInput contains non-digit character!\n";
	    return false;
	    
    }
	
}

// This method will load the maze.
// The content of the file format is quite rigorous.
// If there is any left over data, except space and new linew character,
// the file will not be accepted.

// eg.
// 5 6
// EEEEE
// EOGEO
// EOOEE
// OEGEO
// EOEEO
// EOEOE( )( )( )( )
// is acceptable

// eg.
// 5 6
// EEEEE
// EOGEO
// EOOEE
// OEGEO
// EOEEO
// EOEOE
// 
// 
// 
// is acceptable

// eg.
// 5 6
// EEEEE
// EOGEO
// EOOEE
// OEGEO
// EOEEO
// EOEOE
// 
// A
// 
// is NOT acceptable


bool Maze::setUpMaze( string fileName )  {                   

	int row = 0;
	char trash[READIN_SIZE];                                 // Read in the rest of the first line before a new line character
	string input = "input" + fileName + ".txt";
	
	FILE* filePointer;
	filePointer = fopen( input.c_str() , "r" );             // open a file, can only be read from the file
	
	if ( !filePointer )  {                                  // If there is no such file
		
		cout << "\nFile does not exists!\n";
		return false;
		
	}
	
	else if ( filePointer )  {                              // Successfully found the file
		
		int i = 0, j = 0;
		size_t bytes_read;
		char character;
		
		char str[READIN_SIZE];
		fgets( str, READIN_SIZE, filePointer );             // fgets read in the whole line
         
        if ( !checkTheInput( str ) )  return false;         // Check if the first line of input is numbers

		maze = create2DArray( width, height );
	    maximum_loop = width * height * 200;
	    loop_time = 0;
	    
	    
	    // Read in the maze one character at a time. The reason for this is to
	    // exclude new line character( '\n' ).
	    
	    // This part include checking maze size and the corresponding maze size
		for ( i = 0 ; i < height ; i++ )  {
			for ( j = 0 ; j < width ; j++ ) {
				
				bytes_read = fread(&character, sizeof(char), 1, filePointer);           // Read in a character
				
				if ( i != 0 && j == 0 && character != '\n' )  {                         // i != 0 means not the first row
					
						cout << "\nThere is something wrong with the maze size!\n";
				    	return false;
					
				}
				
				else if ( j == 0 && character == '\n' )                                 // discard new line, read another character
				    bytes_read = fread( &character, sizeof(char), 1, filePointer );
				    
				if ( !bytes_read )  {    // If there is no character left in the maze before the loops are finished,
				                         // maze size is incorrect
				
				    cout << "\nThere is something wrong with the maze size\n";
					return false;	
					
				}
				
				maze[i][j] = character;  // Put it in the maze
					
			}
			
			if ( !bytes_read )  break;
					
		}
		
		bytes_read = fread( &character, sizeof(char), 1, filePointer );     // Read in another character for checking maze size

		if ( bytes_read &&  ( character == '\n' || character == ' ' ) )  {                           // If there are still character and that character is new line
			
			bytes_read = fread( &character, sizeof(char), 1, filePointer );
			
			for ( ; bytes_read ; )  {
			
			    if ( character != '\n' && character != ' ' )  {                 // Tolerate for space and new line
			
				    cout << "\nLeft over data in the file!\n";
				    return false;
				
		        }
		        
		        bytes_read = fread( &character, sizeof(char), 1, filePointer ); // Keep reading until bytes_read return 0( character is NULL ). )
		        
		    }
			
		}
	    
	    if ( !checkTheCells() )  {                          // check for invalid characters.
	    	
	    	cout << "\nUnknown character in the maze!\n";
	    	return false;
	    	
		}
		
	}
	
	fclose( filePointer );                                  // Don't waste resources on keep opening files
	return true;
	
}


int main()  {
	
	int command = 0;
	
	do {
		
		Maze aMaze;
		Coordinate coord;
		string fileName;
		int count;
		bool success = false;
		
		cout << "\n*** Path Finding ***\n";
		cout << "* 0. Quit          *\n";
		cout << "* 1. One goal      *\n";
		cout << "* 2. More goals    *\n";
		cout << "********************\n";
		
		cout << "\nInput a command( 0, 1, 2, 3 ): ";
		cin >> command;
		
		if ( command == 1 || command == 2 || command == 3 ) {                             // Choose command 
		
			aMaze.setMode( command );
			    
			cout << "\nInput a file number: ";
			cin >> fileName; 
			
			if ( aMaze.setUpMaze( fileName ) ) {                          // Set up the Maze, load in the file
					  
	            Maze vMaze( aMaze );                                      // make a copy of the maze
	            
	            if ( command == 1 )                                       // If only need to find one goal
				    success = aMaze.findGoal( vMaze, vMaze.getDirection(), 0, 0, 0 );    // Do it once
				    
				else if ( command == 2 )  {                              // If multiple goals
				
				    int goalCount = 0, i = 0;
				    cout << endl << "Number of Goals: ";
				    cin >> goalCount;                                     // input goal count
				    
				    for ( i = 0 ; i < goalCount ; i++ )  {                // Do it multiple times
				    
				        success = aMaze.findGoal( vMaze, vMaze.getDirection(), 0, 0, 0 );
				        if ( goalCount - 1 != i && success )              // Keep the visited Maze when
				            vMaze.refresh();                              // 1. It is the last time of the loop
							                                              // 2. It failed to find a route
							                                              // Other than that, refresh the maze for the next path finding
							                                              
				        else                                              // If it fails once, means no route, break                 
				            break;
				        
				    }
				    
			    }
			    
			    else if ( command == 3 )  {
			    	
			    	Maze cleanerMaze( aMaze );
			    	
			    	aMaze.findShortestGoal( vMaze, cleanerMaze, aMaze.getDirection(), 0, 0, 0, coord );
			    	
			    	aMaze.paintTheRoute( cleanerMaze );
			    	
			    	if ( coord.getTheFirstTime() )  {
					
					    success = true;
			    	    aMaze.paintTheRoute( cleanerMaze );
			    	    
			        }
			    	
				}
	
                vMaze.passedToGoal();                                     // change back the 'P's to the 'G's
        
				vMaze.displayMaze();                                      // show the maze
				cout << endl;
				
				if ( success )                                            // If success, show the Route maze
				    aMaze.displayMaze();
				    
				if ( command == 3 ) {
					
				    if ( success )
				        cout << "The length of the shortest route is " << coord.getPreviousLength() + 1 << endl;
						
					else
					    cout << "### There is no path to find a goal! ###\n"; 	
					
				} 
				
				vMaze.clr();                                              // free the Vmaze
				
			}
			aMaze.clr();                                                  // free the Route Maze
			
			aMaze.setMode( 1 );                                           // Set back to oneG
			
		}
		
		else if ( !command )  break;                                      // command == 0, quit
		
		else 
		    cout << endl << "Command does not exist!" << endl;
		    
	} while ( true );
	
	return 0;
	
}
