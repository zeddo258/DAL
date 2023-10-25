// 11127147 ¶À¬fµ¤
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits.h>

using namespace std; 
struct Record {
	int way[256][256];
}; 

typedef enum modes { oneG, moreG, findG } Modes ;

class Maze {
  int goal ;
  int x ;
  int y ;
  vector<string> content;

  bool inRange( int nowx, int nowy ) const {
    if ((nowy >= 0) && (y > nowy) && (x >= 0) && (x > nowx))
      return true; // if it is in the range of (0.0) and maxLimit
    return false;  // out of range
  } // bool
   

  void walk ( int way, int &nowx, int &nowy  ) { // only walk no judgement
   	if ( way < 0 ) 
      way = way + 8 ;
   	
    switch (way%4) { // find direction
    	
	  case 0:
        nowx++;
        break;

      case 1:
        nowy++;
        break;

      case 2:
        nowx--;
        break;

      case 3:
        nowy--;
        break;

    } // end switch
  } // walk
  
    void back( Record record, int &nowx, int &nowy ) { // no way to go , go back one square
      if ( content[nowy][nowx] != 'E' ) 
      	content[nowy][nowx] = 'V' ;
            
      walk( record.way[nowy][nowx] - 2, nowx, nowy ) ;
      return  ;
    } // void back
 
    bool move( Record &record, int way, int &nowx, int &nowy, int &stuck, int& step, int shortest )  {
    	
      if ( shortest - 1 > step  ) {
    	walk( way, nowx, nowy ) ;

    	if ( inRange( nowx, nowy ) ) { 
    		if ( content[nowy][nowx] == 'E' || content[nowy][nowx] == 'F' ) { // F mean G been finded
      	  		content[nowy][nowx] = 'R' ;
				stuck = 0 ;
      	  		step ++ ;
                record.way[nowy][nowx] = way ;
        		return move( record, way, nowx, nowy, stuck, step, shortest ) ;
        		
      		} // if

      		else if ( content[nowy][nowx] == 'G' ) {
        		content[nowy][nowx] = 'F' ;
        		step ++ ;
        		stuck = 0 ;
            	record.way[nowy][nowx] = way ;
        		return true ;
      		} // else if 
    	} // if
    
   		walk( way - 2, nowx, nowy ) ; // go back
   		
    } // if 
      
    return false ;  
  
  } // bool move
  
  void  Find( Record &record, int &nowx, int &nowy, int &shortest ) {
  	    int four[y+1][x+1] ;
  		int way = 0 ;
		int step = shortest - 1;
  		int tempx, tempy ;
  		int px, py ;
  		int stuck = 0 ;
  		vector<string> save ;
        vector<string> still ;
  		content[nowy][nowx] = 'G' ;
  		for ( int i = 0 ; i < y ; i ++ ) {
      		save.push_back( content[i] ) ;
  		} //for
  		
    	for ( int len = 0 ; len < content.size() ; len ++ )  {  
          for ( int px = 0 ; px <= x ; px ++ ) { 
         	 four[len][px] = -1 ;
            if ( content[len][px] == 'V' )
              content[len][px] = 'E' ;	
          } // for
   		} // for
   		
   		for ( int i = 0 ; i < y ; i ++ ) {
        	still.push_back( content[i] ) ;
    	} // for
    	
    	back( record, nowx, nowy ) ;

    	
    	while ( step > 0 ) {
    		step -- ;
    		still[nowy][nowx] = 'E' ;
    		back( record, nowx, nowy ) ;
    		tempx = nowx ;
    		tempy = nowy ;
    		stuck = 0 ;
    		
    		content.clear() ;
   			for ( int i = 0 ; i < y ; i ++ ) {
        		content.push_back( still[i] ) ;
    		} // for
    		
    		
    		while ( four[tempy][tempx] != 3  )  {
    			
    			four[nowy][nowx] ++ ; 
    			if ( move( record, four[nowy][nowx], nowx, nowy, stuck, step, shortest ) ) {
    				shortest = step ;
    				for ( int len = 0 ; len < content.size() ; len ++ )  {  
          				for ( int px = 0 ; px <= x ; px ++ ) { 
            				if ( save[len][px] == 'V' && content[len][px] != 'R' )
              					content[len][px] = 'V' ;	
              			
          				} // for
   					} // for
    				
    				return Find( record, nowx, nowy, shortest) ;
    				
    				
				} // if 

				if ( four[nowy][nowx] == 3 && ( tempy != nowy || tempx != nowx ) ) {
    				step -- ;
    				

              		px = nowx ;
    		        py = nowy ;
    				back( record, nowx, nowy ) ;
    				

    				
				} // if 
				
				
    	
			} // while
			
			for ( int len = 0 ; len < content.size() ; len ++ )  { // throw R V to save 
          		for ( int px = 0 ; px <= x ; px ++ ) { 
          			four[len][px] = -1 ;	
          			if ( content[len][px] == 'V' && save[len][px] != 'R' ) 
          				save[len][px] = 'V' ;
          		} // for
   			} // for
			
		}  // while
		
		
		content.clear() ;
   		for ( int i = 0 ; i < y ; i ++ ) {
        	content.push_back( save[i] ) ;
    	} // for
    	
   } // shortest

  



  public:

    Maze():x(0),y(0),goal(1) {
    } ; // end Maze default constructor

  void show( char type ) { 
    char spot ;
    for ( int len = 0 ; len < content.size() ; len ++ )  {
      for ( int px = 0 ; px <= x ; px ++ ) { 
        spot = content[len][px] ;
        
        if ( type == 'V' ) { //show every traveled point
    	  if ( spot == 'R' ) 
            spot = 'V' ;
    	} // if 
    	
    	else if ( type == 'R' )  { // show the real way
		  if ( spot == 'V' ) 
            spot = 'E' ;
		} // else if  
        if ( spot == 'F' ) // change the mark G back
          spot = 'G' ;
        cout << spot ;
      } // for

      cout << endl ;
    } // for

  cout << endl ;
  } // show()

  
      bool load( string name, Modes mode) {
      string tmp ;
      ifstream ifs ;
      bool wrong = false ;
      
      name = "input" + name + ".txt" ;
      ifs.open( name.c_str(), ios::in ) ;
      if ( !ifs.is_open() ) {  // check txt is exist 
        cout << endl << name << " does not exist!" << endl ;
        wrong = true ;
      } // if

      else {
        ifs >> x >> y ; // input length and width 
        getline( ifs, tmp ) ; // throw away the excess

        while ( getline( ifs, tmp ) ) { // start input maze
          if ( tmp.size() > x ) 
            wrong = true ; // if the representation is different from actual
          else
             content.push_back( tmp ) ;
             
            
        } // while 

          if ( content.size() > y ) // // if the representation is different from actual
            wrong = true ; 
        ifs.close() ;
      } // else 
      
      

      if ( wrong == true )
        return false ;
        
      if ( mode == moreG ) {
        int num ;
        cout << endl << "Number of G (goal)"  ;
        cin >> goal ; 
      } // if
      
      return true ;
      
    } // bool load

  bool findGoals( Modes mode, int &shortest ) {
  Record record ;
  int nowx = 0 ; // rat x
  int nowy = 0 ; // rat y
  int way = 0 ; // direction 
  int stuck = 0 ; // try one way but cant move
  int find = 0 ;  // number of G looked for
  int step = 0 ;
  vector< string > save ; // save R and V
  vector< string > still ; // save the whole maze
  
  for ( int i = 0 ; i < y ; i ++ ) {
      still.push_back( content[i] ) ;
  } //for
  
  for ( int i = 0 ; i < y ; i ++ ) {
      save.push_back( content[i] ) ;
  } //for
  
    content[0][0] = 'R' ;
    while ( find < goal ) {
      if ( move( record, way, nowx, nowy, stuck, step, shortest ) ) { // if find return true
      	find ++ ; 
      	still[nowy][nowx] = 'F' ; // initialization
      	way = 0 ;
      	if ( mode != findG ) {
      		step = 0 ;
      		nowx = 0 ;
      		nowy = 0 ;
      	} // if
      	else 
      	  shortest = step ;
      	
        for ( int len = 0 ; len < content.size() ; len ++ )  { // throw R V to save 
          for ( int px = 0 ; px <= x ; px ++ ) { 
            if ( content[len][px] == 'R' && save[len][px] != 'G' )
              save[len][px] = 'R' ;	
			else if ( content[len][px] == 'V' && ( save[len][px] != 'R' && save[len][px] != 'G' ) ) 
				save[len][px] = 'V' ;
          } // for
   		} // for
   		
        content.clear() ;
   		for ( int i = 0 ; i < y ; i ++ ) {
        	content.push_back( still[i] ) ;
        } // for
        
        content[0][0] = 'R' ;
      	
	  } // if 
      
      else {

        if ( stuck == 3 ) { // already try four way but still cant move
          if ( nowx == 0 && nowy == 0 ) { // cant move and rat on (0,0) mean already go every point
          	if ( find != 0 ) {
          		
          		for ( int len = 0 ; len < content.size() ; len ++ )  { // throw R V to save 
          			for ( int px = 0 ; px <= x ; px ++ ) { 	
						if ( content[len][px] == 'V' && ( save[len][px] != 'R' && save[len][px] != 'G' ) ) 
							save[len][px] = 'V' ;
					} // for
				} // for
          		
          		content.clear() ;
          		for ( int i = 0 ; i < y ; i ++ ) {
      	 	  		content.push_back( save[i] ) ;
        		  } // for
        		  
          	} // if
          	
          	return false ;
		  } // if 
          
          stuck = 0 ; 
          back( record, nowx, nowy ) ; //go back one space
          step -- ;
          way = 0 ;
        } // if
        
        else { // hit wall try another direction
          stuck ++ ;
          way ++; 
        } // else
      } // else
      
    } // while ()
    
    content.clear() ;
   	for ( int i = 0 ; i < y ; i ++ ) {
        content.push_back( save[i] ) ;
    } // for
    
    if ( mode == findG ) 
    	Find( record, nowx, nowy, shortest) ;
	 
    return true ;

  } // findGoals()


} ; // class Maze

int main(void) {
  int command = 0; // user command
  int shortest = INT_MAX ;

  do {
    Maze Maze;        // a matrix
    string fileName;   // a file name
    Modes mode = oneG; // default: one goal

    cout << endl << "*** Path Finding ***";
    cout << endl << "* 0. Quit          *";
    cout << endl << "* 1. One goal      *";
    cout << endl << "* 2. More goals    *";
    cout << endl << "* 3. Find short    *";
    cout << endl << "********************";
    cout << endl << "Input a command(0, 1, 2, 3):";
    cin >> command; // get the command

    if ((command == 1) || ( (command == 2) || (command ==3) ) ) {

      if ( command == 3 ) 
        mode = findG ;
        
      if ( command == 2 )
        mode = moreG; // one or more goals

      cout << endl << "Input a file number (eg, 201, 202,): ";
      cin >> fileName;

      if (Maze.load(fileName, mode)) { // load the original matrix

        bool success = Maze.findGoals( mode, shortest ); // find a path to goal(s)

        Maze.show( 'V' ); // show on screen the visited cells

        if (success) {    // to check if the goal is reached or not
          Maze.show( 'R' ); // show on screen the route to reach the goal
          if ( mode == findG )
            cout << "Shortest path lengh = " << shortest ;
        } // if
      } // end inner-if
      
      mode = oneG;  // reset to default
      
    } // end outer-if


    else if (!command) //'0' stop the program
      break;

    else
      cout << endl << "Command does not exist!" << endl;

    shortest = INT_MAX ;
  } while (true);

  system("pause"); // pause the execution
  return 0;

} // end of main

