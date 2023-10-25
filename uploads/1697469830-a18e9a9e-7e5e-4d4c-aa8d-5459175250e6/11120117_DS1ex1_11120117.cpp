// 11120117 ªL¸aµ¾ 

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <iostream>
# include <fstream> 

using namespace std ;

class chunk {

public:
	int line ;
	int column ;
	char status ;
	bool find ; // avoid counting same goals twice
    chunk * up ;
    chunk * down ;
    chunk * left ;
    chunk * right ;
};


void GoUp( chunk * currentPoint, int & currentGoals, int NumOfGoals ) ;
void GoDown( chunk * currentPoint, int & currentGoals, int NumOfGoals ) ;
void GoLeft( chunk * currentPoint, int & currentGoals, int NumOfGoals ) ;
void GoRight( chunk * currentPoint, int & currentGoals, int NumOfGoals ) ;

void Print( chunk * start ) ;

chunk * CreateMaze( int line, int column, int currentLine, int currentColumn, char input[10000], chunk * start ) {	

  int i = 0; // index of input[10000]
	
  chunk * generator = NULL ;
  chunk * tempHead = NULL ;
  chunk * lastPoint = NULL ; // record last generatored space  
  chunk * floorPoint = start ; // record the floor which down is NULL 
  
  while ( currentLine <= line ) {
  	
  	generator = new chunk() ;
  	
  	generator -> status = input[i] ;
  	
  	generator -> find = false ;
  	
  	generator -> line = currentLine ;
  	generator -> column = currentColumn ;
  	
  	// cout << generator -> status << " Line¡G" << generator -> line << " Column¡G" << generator -> column << endl ; // test-line
  	
  	generator -> up = NULL ; // top border	  
    generator -> down = NULL ; // floor border
    generator -> left = NULL ; // left border
  	generator -> right = NULL ; // right border
  	  
  	if ( start == NULL ) {
  		
  	  start = generator ;	
  	  lastPoint = generator ;
  	  
	} // first data
	
	else if ( currentLine == 1 ) {
		
	  tempHead = generator ;
	  lastPoint = generator ;
		
	} // first line's date
	
	else {
	
	  lastPoint -> right = generator ;
	  lastPoint -> right -> left = lastPoint ; 
	  lastPoint = generator ;
		
	} //  line's second data or above 
  
    currentLine ++ ;
    i ++ ;
  	
  } // create a line of new data 
  
	
  if ( tempHead != NULL ) {
  	
  	while ( floorPoint -> down != NULL )
  	  floorPoint = floorPoint -> down ;
  	
  	while ( floorPoint != NULL ) {
  		
      floorPoint -> down = tempHead ;
      floorPoint -> down -> up = floorPoint ;
      
      floorPoint = floorPoint -> right ;
      tempHead = tempHead -> right ;
    }
    
  }
	
  return start;
	
}

chunk * InputData( int line, int column, char input[10000], chunk * start, bool & error, char errorType[10000] ) {
  
  int i = 0 ; // check input file has error or not 
  
  int currentLine = 1 ;
  int currentColumn = 1 ;
  
  char fileNum[100] = "\0\0\0\0\0\0\0";
  char fileName[1000] = "input\0\0\0\0\0\0\0\0\0\0\0" ;
  char fileType[10] = ".txt\0" ;
  
  cout << endl << "Please select file Number¡G" << endl << endl ;
  
  cin >> fileNum ;
  
  strcat( fileName, fileNum ) ;
  strcat( fileName, fileType ) ;
  
  fstream in( fileName, ios::in );
  
  // cout << fileName << endl ; // test-line 
  
  if ( ! in.is_open() ) {
  	
    error = true ;
	strcpy( errorType, "( Failed to open file )" ) ;
	return NULL ;
  	
  }
  
  in >> line >> column ; 
  
  if ( line < 0 || column < 0 ) {
      	
    error = true ;
	strcpy( errorType, "( Invalid input line or column )" ) ;
	return NULL ;
      	
  }
  
  while ( ! in.eof() && currentColumn <= column ) {

    in >> input ;
    
    i = 0 ;
    while ( i < line ) {
      
      if ( input[i] != 'E' && input[i] != 'O' && input[i] != 'G' ) {
      	
      	error = true ;
		strcpy( errorType, "( Invalid input character )" ) ;
		return NULL ;
      	
	  }
	  
      i ++ ;
		
	}
    
    start = CreateMaze( line, column, currentLine, currentColumn, input, start ) ;
    
    // cout << "currentLine¡G" << currentLine << " " << "currentColumn¡G" << currentColumn << endl << input << endl ; // test line 
    
    currentLine = 1 ;
    currentColumn ++ ;

  }	
  
  if ( in.is_open() )
    in.close();
		
  return start;
	
}

// Right first ------------------------------------------------------------

void GoRight( chunk * currentPoint, int & currentGoals, int NumOfGoals ) {

  // cout << "Right:" << currentGoals << endl ; // test-line 

  if ( currentPoint -> status == 'E' )
    currentPoint -> status = 'V' ;
  
  // right
  
  if ( currentGoals < NumOfGoals && currentPoint -> right != NULL && currentPoint -> right -> status == 'E' )
    GoRight( currentPoint -> right, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> right != NULL && currentPoint -> right -> status == 'G' && ! currentPoint -> right -> find ) {
  	
  	currentPoint -> right -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoRight( currentPoint -> right, currentGoals, NumOfGoals ) ; // keep going    

  }
  
  // down

  if ( currentGoals < NumOfGoals && currentPoint -> down != NULL && currentPoint -> down -> status == 'E' )
    GoDown( currentPoint -> down, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> down != NULL && currentPoint -> down -> status == 'G' && ! currentPoint -> down -> find ) {
  	
  	currentPoint -> down -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoDown( currentPoint -> down, currentGoals, NumOfGoals ) ; // keep going    

  }
  
  // left
  
  if ( currentGoals < NumOfGoals && currentPoint -> left != NULL && currentPoint -> left -> status == 'E' )
    GoLeft( currentPoint -> left, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> left != NULL && currentPoint -> left -> status == 'G' && ! currentPoint -> left -> find ) {
  	
  	currentPoint -> left -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoLeft( currentPoint -> left, currentGoals, NumOfGoals ) ; // keep going    

  }
  
  // up
  
  if ( currentGoals < NumOfGoals && currentPoint -> up != NULL && currentPoint -> up -> status == 'E' )
    GoUp( currentPoint -> up, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> up != NULL && currentPoint -> up -> status == 'G' && ! currentPoint -> up -> find ) {
  	
  	currentPoint -> up -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoUp( currentPoint -> up, currentGoals, NumOfGoals ) ; // keep going    

  }
  
  // mark shortest route'
  
  if ( currentGoals == NumOfGoals && currentPoint -> status == 'V' ) {
  	
    currentPoint -> status = 'R' ;
    
  }

  return ;
  
} 

// Down first ------------------------------------------------------------

void GoDown( chunk * currentPoint, int & currentGoals, int NumOfGoals )  {
	
  // cout << "Down:" << currentGoals << endl ; // test-line 	
	
  if ( currentPoint -> status == 'E' )
    currentPoint -> status = 'V' ;	
  
  // down

  if ( currentGoals < NumOfGoals && currentPoint -> down != NULL && currentPoint -> down -> status == 'E' )
    GoDown( currentPoint -> down, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> down != NULL && currentPoint -> down -> status == 'G' && ! currentPoint -> down -> find ) {
  	
  	currentPoint -> down -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoDown( currentPoint -> down, currentGoals, NumOfGoals ) ; // keep going    

  }
  
  // left
  
  if ( currentGoals < NumOfGoals && currentPoint -> left != NULL && currentPoint -> left -> status == 'E' )
    GoLeft( currentPoint -> left, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> left != NULL && currentPoint -> left -> status == 'G' && ! currentPoint -> left -> find ) {
  	
  	currentPoint -> left -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoLeft( currentPoint -> left, currentGoals, NumOfGoals ) ; // keep going    

  }
  
  // up
  
  if ( currentGoals < NumOfGoals && currentPoint -> up != NULL && currentPoint -> up -> status == 'E' )
    GoUp( currentPoint -> up, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> up != NULL && currentPoint -> up -> status == 'G' && ! currentPoint -> up -> find ) {
  	
  	currentPoint -> up -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoUp( currentPoint -> up, currentGoals, NumOfGoals ) ; // keep going    

  }	
  
  // right
  
  if ( currentGoals < NumOfGoals && currentPoint -> right != NULL && currentPoint -> right -> status == 'E' )
    GoRight( currentPoint -> right, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> right != NULL && currentPoint -> right -> status == 'G' && ! currentPoint -> right -> find ) {
  	
  	currentPoint -> right -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoRight( currentPoint -> right, currentGoals, NumOfGoals ) ; // keep going    

  }
  
  // mark shortest route
  
  if ( currentGoals == NumOfGoals && currentPoint -> status == 'V' ) 
    currentPoint -> status = 'R' ; 

  return ;	
	
}

// left first ------------------------------------------------------------

void GoLeft( chunk * currentPoint, int & currentGoals, int NumOfGoals ) {

  // cout << "Left:" << currentGoals << endl ; // test-line 

  if ( currentPoint -> status == 'E' )
    currentPoint -> status = 'V' ;

  // left
  
  if ( currentGoals < NumOfGoals && currentPoint -> left != NULL && currentPoint -> left -> status == 'E' )
    GoLeft( currentPoint -> left, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> left != NULL && currentPoint -> left -> status == 'G' && ! currentPoint -> left -> find ) {
  	
  	currentPoint -> left -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoLeft( currentPoint -> left, currentGoals, NumOfGoals ) ; // keep going    

  }
  
  // up
  
  if ( currentGoals < NumOfGoals && currentPoint -> up != NULL && currentPoint -> up -> status == 'E' )
    GoUp( currentPoint -> up, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> up != NULL && currentPoint -> up -> status == 'G' && ! currentPoint -> up -> find ) {
  	
  	currentPoint -> up -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoUp( currentPoint -> up, currentGoals, NumOfGoals ) ; // keep going    

  }	
  
  // right
  
  if ( currentGoals < NumOfGoals && currentPoint -> right != NULL && currentPoint -> right -> status == 'E' )
    GoRight( currentPoint -> right, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> right != NULL && currentPoint -> right -> status == 'G' && ! currentPoint -> right -> find ) {
  	
  	currentPoint -> right -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoRight( currentPoint -> right, currentGoals, NumOfGoals ) ; // keep going    

  }
  
  // down

  if ( currentGoals < NumOfGoals && currentPoint -> down != NULL && currentPoint -> down -> status == 'E' )
    GoDown( currentPoint -> down, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> down != NULL && currentPoint -> down -> status == 'G' && ! currentPoint -> down -> find ) {
  	
  	currentPoint -> down -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoDown( currentPoint -> down, currentGoals, NumOfGoals ) ; // keep going    

  }

  // mark shortest route
  
  if ( currentGoals == NumOfGoals && currentPoint -> status == 'V' ) 
    currentPoint -> status = 'R' ; 

  return ;

}

// up first ------------------------------------------------------------

void GoUp( chunk * currentPoint, int & currentGoals, int NumOfGoals ) {

  // cout << "Up:" << currentGoals << endl ; // test-line 

  if ( currentPoint -> status == 'E' )
    currentPoint -> status = 'V' ;

  // up
  
  if ( currentGoals < NumOfGoals && currentPoint -> up != NULL && currentPoint -> up -> status == 'E' )
    GoUp( currentPoint -> up, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> up != NULL && currentPoint -> up -> status == 'G' && ! currentPoint -> up -> find ) {
  	
  	currentPoint -> up -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoUp( currentPoint -> up, currentGoals, NumOfGoals ) ; // keep going    

  }	
  
  // right
  
  if ( currentGoals < NumOfGoals && currentPoint -> right != NULL && currentPoint -> right -> status == 'E' )
    GoRight( currentPoint -> right, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> right != NULL && currentPoint -> right -> status == 'G' && ! currentPoint -> right -> find ) {
  	
  	currentPoint -> right -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoRight( currentPoint -> right, currentGoals, NumOfGoals ) ; // keep going    

  }
  
  // down

  if ( currentGoals < NumOfGoals && currentPoint -> down != NULL && currentPoint -> down -> status == 'E' )
    GoDown( currentPoint -> down, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> down != NULL && currentPoint -> down -> status == 'G' && ! currentPoint -> down -> find ) {
  	
  	currentPoint -> down -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoDown( currentPoint -> down, currentGoals, NumOfGoals ) ; // keep going    

  }
  
  // left
  
  if ( currentGoals < NumOfGoals && currentPoint -> left != NULL && currentPoint -> left -> status == 'E' )
    GoLeft( currentPoint -> left, currentGoals, NumOfGoals ) ;  

  if ( currentGoals < NumOfGoals && currentPoint -> left != NULL && currentPoint -> left -> status == 'G' && ! currentPoint -> left -> find ) {
  	
  	currentPoint -> left -> find = true ;
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  currentPoint -> status = 'R' ;
      return ;

    }
      
    else 
      GoLeft( currentPoint -> left, currentGoals, NumOfGoals ) ; // keep going    

  }
  
  // mark shortest route
  
  if ( currentGoals == NumOfGoals && currentPoint -> status == 'V' ) 
    currentPoint -> status = 'R' ; 

  return ;	

}

void RunMaze( chunk * start, int NumOfGoals ) {

  int currentGoals = 0 ; // the amount of goals being found

  start -> status = 'V' ;
  
  // right first

  if ( start -> right != NULL && start -> right -> status == 'E' && currentGoals < NumOfGoals )
    GoRight( start -> right, currentGoals, NumOfGoals ) ;
    
  if ( start -> right != NULL && start -> right -> status == 'G' && currentGoals < NumOfGoals ) {
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals ) {

  	  start -> status = 'R' ;
      return ;

    }
		  
    else 
      GoRight( start -> right, currentGoals, NumOfGoals ) ; // keep going    

  }
  
  // down second

  if ( start -> down != NULL && start -> down -> status == 'E' && currentGoals < NumOfGoals )
    GoDown( start -> down, currentGoals, NumOfGoals ) ;
    
  if ( start -> down != NULL && start -> down -> status == 'G' && currentGoals < NumOfGoals ) {
  	
    currentGoals ++ ;
  	
  	if ( currentGoals == NumOfGoals && currentGoals < NumOfGoals ) {
  		
	start -> status = 'R' ;
	return ;
	
	}
      
    else 
      GoDown( start -> down, currentGoals, NumOfGoals ) ; // keep going    

  }

  if ( currentGoals == NumOfGoals )
    start -> status = 'R' ;

  return ;
	
} // fitst step


// ------------------------------------------------------------

void PrintPath( chunk * start ) {
	 
  chunk * temp = start ;
  
  cout << endl ;
  
  while ( temp -> right != NULL || temp -> down != NULL ) {
  	
  	if ( temp -> status == 'R' )
  	  cout << 'V' ;
  	  
  	else
  	  cout << temp -> status ;
  	
  	if ( temp -> right == NULL ) {
	  temp = start -> down ;
	  start = temp ;
	  cout << endl ;
	}
	
	else 
	  temp = temp -> right ;
  	
  }
  
  cout << temp -> status << endl << endl ;
  
  return ;
	
}

void PrintRoute( chunk * start ) {
	
  chunk * temp = start ;

  if ( temp -> status != 'R')
    return ; // failed to find enough goals
	
  while ( temp -> right != NULL || temp -> down != NULL ) {
  	
  	if ( temp -> status == 'V' )
  	  cout << 'E' ;
  	  
  	else
  	  cout << temp -> status ;
  	
  	if ( temp -> right == NULL ) {
	  temp = start -> down ;
	  start = temp ;
	  cout << endl ;
	}
	
	else 
	  temp = temp -> right ;
  	
  }
  
  cout << temp -> status << endl << endl ;
  
  return ;
	
}

chunk * Reset( chunk * recycle ) {
  
  int column = 1 ; // Odd : go from left to right. Even : go from right to left. ( delete from top )
  
  chunk * nextPoint = NULL ;
  
  while ( recycle -> down != NULL ) {
  	
    // cout << recycle -> status << "(" << recycle -> line << "," << recycle -> column << ")" << endl ; // test-line  	
  	
  	if ( column % 2 == 1 ) {
	  
  	  if ( recycle -> right == NULL ) {
  	  	
  	    nextPoint = recycle -> down ;
  	    column ++ ;  
  	    
      }
      
      else
  	    nextPoint = recycle -> right ;
  	  
    } // odd
  	
  	else if ( column % 2 == 0 ) {
	  
  	  if ( recycle -> left == NULL ) {
  	  	
  	    nextPoint = recycle -> down ;
  	    column ++ ; // next column
      }
      
      else
  	    nextPoint = recycle -> left ;
  	  
    } // even		
  	
  	delete recycle ;
  	recycle = nextPoint ;

  }  // delete data expect last column 
  
  if ( recycle -> right != NULL ) {
  	
  	while ( recycle != NULL ) {
  		
      // cout << recycle -> status << "(" << recycle -> line << "," << recycle -> column << ")" << endl ; // test-line 
  		
  	  nextPoint = recycle -> right ;
	  delete recycle ;	
  	  
  	  recycle = nextPoint ;
  	  
	}
  	
  } // delete from left to right 
  
  else if ( recycle -> left != NULL ) {
  	
  	while ( recycle != NULL ) {
  		
      // cout << recycle -> status << "(" << recycle -> line << "," << recycle -> column << ")" << endl ; // test-line 
  		
  	  nextPoint = recycle -> left ;
	  delete recycle ;	
  	  
  	  recycle = nextPoint ;
  	  
	}
  	
  } // delete from right to left

  return NULL ;
 		
}

bool UI( int & NumOfGoals ) {

  int tempNumInt = 0;

  char tempGoals[1000] ; // check amount of goals
  char tempNumArray[1000] ;
 
  char command[1000] ; 

  while ( true ) { 
  
    cout << "Path Finding" << endl ;
    cout << "0. Quit" << endl ;  
    cout << "1. One goal" << endl ; 
    cout << "2. More goals" << endl ;
    cout << "Input a command¡G" << endl << endl ;
  
    cin >> command ;
  
    if ( strcmp( command, "0" ) == 0 )
      return false ;  
    
    else if ( strcmp( command, "1" ) == 0 ) { 
    
      NumOfGoals = 1;
      return true ;
    
    } // command 1
    
    else if ( strcmp( command, "2" ) == 0 ) {
  	
    	cout << endl << "Enter the number of goals you want to find¡G" << endl << endl ;
  	
    	cin >> tempGoals ;
    	
    	// cout << atoi( tempGoals ) ; // test-line
    	
    	tempNumInt = atoi( tempGoals ) ;
    	itoa( tempNumInt, tempNumArray, 10 ) ;
  	
    	if ( strlen( tempGoals ) != strlen( tempNumArray ) || atoi( tempGoals ) <= 0 )  {

  	      cout << endl << "Invalid number! Please try again." << endl << endl ;
 	      system("pause") ; 	    
        }
        
        else {    	   	
          NumOfGoals = atoi( tempGoals ) ; 
          return true ;    
        }
  
    }  // command 2
    
    else {
  	
      cout << endl << "Invalid command! Please try again. " << endl << endl ;      
	  system("pause") ;
  	
    } // command error
  
  } // while
  
  return false ;

} 

int main() {

  int NumOfGoals = 1 ; // default

  int line = -1 ;
  int column = -1 ;
  
  bool error = false ;
  
  char errorType[10000] = "" ;

  
  char input[10000] ;
  
  chunk * start = NULL ; // the maze's start
  
  while ( UI( NumOfGoals ) ) {

    start = InputData( line, column, input, start, error, errorType ) ;
    
  // cout << "(" << start -> line << "," << start -> column << ")" << endl ; // test-line
  
    if ( ! error ) {
  
      RunMaze( start, NumOfGoals ) ;
  
      PrintPath( start ) ;
  
      PrintRoute( start ) ; // if not find enough goals, it will do nothing
  
      start = Reset( start ) ;
  
    } // no error
    
    else {
    	
      cout << endl << "Error happen! Please try again. " << errorType << endl << endl ; 
      error = false ;
      system( "pause" ) ;
    	
	}
  
  }
  
  return 0 ;

}
