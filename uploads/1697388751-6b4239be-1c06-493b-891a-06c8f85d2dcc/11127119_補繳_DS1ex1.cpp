#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string.h>

using namespace std;

enum Modes{
 oneG, moreG
};

class Maze {
 private:
  char maze[100][100];
  int length, width;
  
  
 public :
  
  bool Load( string fileName, Modes mode ) {
   string filename = "input" + fileName + ".txt"; //
   char Filename[20];  
   strcpy(Filename, filename.c_str());
   ifstream file(Filename);
   if( !file.is_open())
    return false; 
   string len, wide;
   file >> len;
   file >> wide;
   int a = 0; //長的int形式 
   int b = 0; //寬的int形式 
   a = atoi(len.c_str());
   b = atoi(wide.c_str());
   char nextline;
   cin >> nextline;
   while ( )
   
   
   
  }
};

enum Modes{
 oneG, moreG;
};

int main( void ) {
  int command = 0;         // user command 
  
  do {
    Maze aMaze;            // a matrix
    string fileName;       // a file name
    Modes mode = oneG;     // default: one goal
    
    cout << endl<< "*** Path Finding ***";
    cout << endl << "* 0. Quit          *";
    cout << endl << "* 1. One goal      *";
    cout << endl << "* 2. More goals    *";
    cout << endl << "********************";
    cout << endl << "Input a command(0, 1, 2):";
    cin >> command;                     // get the command
    if ( ( command == 1 ) || ( command == 2 ) ) {
      if ( command == 2 ) 
        mode = moreG;                   // one or more goals
      cout << endl << "Input a file number (e.g.,201,202,...)";
      cin >> fileName;
      if ( aMaze.load( fileName, mode ) ) {       // load the original matrix
     Maze vMaze( aMaze );                      // a copy to keep the visited cells
     bool success = aMaze.findGoals( vMaze );  // find a path to goal(s)
   
     mode = oneG;            // reset to default
     vMaze.show();           // show on screen the visited cells
     if ( success )          // to check if the goal is rea
       aMaze.show();         // clear up the copy
     vMaze.clr();
   } // end inner-if
   
      aMaze.clr();             // '0':stop the program
 } // end outer-if
    else if ( !command )
      break;
    else 
      cout << endl << "Command does not exist!" << endl;

  } while ( true );
  system( "pause" );            // pause the execution
  return 0;
} // end of main
