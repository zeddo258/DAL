// 11127127 陳沛君

#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

/** ======================= Check(class) ======================= **/

class Check{

  public :

    // check is the input string an integer. If yes, return true; else, return false
    static bool isInteger( string inputNum ) ;

    // check is the input number in the specified range
    static bool inRange( string inputNum ) ;

};

/** ======================= Check(function) ======================= **/


// check is the input string an integer. If yes, return true; else, return false
bool Check::isInteger( string inputNum ) {

  for( int i = 0 ; i < inputNum.size() ; i++ ) {
    if ( inputNum[i] == '.' )
      return false ;
  } // for

  return true ;

} // isInteger()

// check is the input number in the specified range
bool Check::inRange( string inputNum ) {

  int num = stoi( inputNum ) ;

  if ( num <= 100 && num >= 1 ) {
    return true ;
  } // if

  return false ;

} // inRange

/** ======================= Maze(class) ======================= **/

class Maze {

  private:

    std::ifstream ifs ;
    static int row , col ; // 行→ 列↓ the number of row and col of the maze
    char **maze ;  // the two-dimensional array of the maze

  // ------------------------------------

  public:

    Maze() ;

    Maze( char** aMaze ) ;

    // load a .txt file and input in the maze
    bool inputMaze( string fileName ) ;

    // print the maze
    void printMaze() ;

    // to get the data of the maze
    char ** getMaze() ;

    // clear the maze
    void clr() ;

    // ------------------------

    // to get the number of row
    static int getRow() ;  // 行→
    // to get the number of col
    static int getCol() ;  // 列↓

};

/** ======================= Maze(functions) ======================= **/


int Maze::row ;
int Maze::col ;

// construction
Maze::Maze(){

  Maze::row = 0 ;
  Maze::col = 0 ;

} // Maze()

// construction
Maze::Maze( char** aMaze ) {

  // create the maze
  maze = new char*[Maze::row]; // 配置第一層（col）
  for ( int i = 0; i < Maze::row; i++ ) {
    maze[i] = new char[Maze::col]; // 配置第二層（row）
  } // for


  // load the maze
  for ( int i = 0; i < Maze::row; i++ ) {
    for ( int j = 0; j < Maze::col; j++ ) {

      maze[i][j] = aMaze[i][j] ;

    } // for

  } // for

} // Maze()


// load a .txt file and input in the maze
bool Maze::inputMaze( string fileName ) {

  string strRow = "\0" ;
  string strCol = "\0" ;

  // open the .txt file
  ifs.open( fileName );

  // check if the file is opened sucessfully
  if ( !ifs.is_open() ){

    cout << "Failed to open file." << endl;
    system("pause");
    cout << endl ;
    return false;

  } // if

  // input the number of column, and ensure the type is correct
  ifs >> strCol ;

  if ( Check::isInteger( strCol ) && Check::inRange( strCol ) )
    Maze::col = stoi( strCol ) ;
  else{
    cout << "### There's an error with the maze ###" << endl << endl ;
    ifs.close() ;
    return false ;
  } // else

  // input the number of row, and ensure the type is correct
  ifs >> strRow ;

  if ( Check::isInteger( strRow ) && Check::inRange( strRow ) )
    Maze::row = stoi( strRow ) ;
  else{
    cout << "### There's an error with the maze ###" << endl << endl ;
    ifs.close() ;
    return false ;
  } // else

  // ifs >> Maze::col ;
  // ifs >> Maze::row ;

  // cout << "row = " << Maze::row << endl ;
  // cout << "col = " << Maze::col << endl ;

  // create the maze
  maze = new char*[Maze::row]; // 配置第一層（col）
  for ( int i = 0; i < Maze::row; i++ ) {
    maze[i] = new char[Maze::col]; // 配置第二層（row）
  } // for

  // load the maze
  for ( int i = 0; i < Maze::row; i++ ) {
    for ( int j = 0; j < Maze::col; j++ ) {

      ifs >> maze[i][j] ;

    } // for

  } // for

  ifs.close() ;
  // printMaze() ;

  return true ;

} // inputMaze

// print the maze
void Maze::printMaze() {

  // print the maze
  for( int i = 0 ; i < Maze::row ; i++ ) {

    for( int j = 0 ; j < Maze::col ; j++ ) {
      cout << maze[i][j] ;
    } // for

    cout << endl ;
  } // for

  cout << endl ;

} // printMaze()

char ** Maze::getMaze() {

  return maze ;

} // getMaze

// clear the maze
void Maze::clr() {

  // clear the second layer first
  for ( int i = 0; i < Maze::row; i++ ) {
    delete[] maze[i];
  } // for

  // then clear the first layer
  delete[] maze ;

} // clr()

// -------------------------------------------------

// 行→
int Maze::getRow() {

  return Maze::row ;

} // getRow()

// 列↓
int Maze::getCol() {
  return Maze::col ;

} // getCol()

/** ======================= Mode(class) ======================= **/

// run the maze
class Mode {

  private :

    int countsOfG = 0 ;  // the number of the goals that the mouse had passed
    int numOfG ;  // the number of the goals that the mouse have to pass
    bool isRoute = false ;  // boolean value checks whether the cell is a route

    // check the east cell is able to pass. If yes, then move forward that cell.
    // And if the mouse passes over a certain number of goals, returns true; else, returns false
    bool goingEast( char ** path, char ** maze, int currentRow, int currentCol, bool findfindThePath  ) ;

    // check the west cell is able to pass. If yes, then move forward that cell.
    // And if the mouse passes over a certain number of goals, returns true; else, returns false
    bool goingWest( char ** path, char ** maze, int currentRow, int currentCol, bool findfindThePath  ) ;

    // check the south cell is able to pass. If yes, then move forward that cell.
    // And if the mouse passes over a certain number of goals, returns true; else, returns false
    bool goingSouth( char ** path, char ** maze, int currentRow, int currentCol, bool findfindThePath  ) ;

    // check the north cell is able to pass. If yes, then move forward that cell.
    // And if the mouse passes over a certain number of goals, returns true; else, returns false
    bool goingNorth( char ** path, char ** maze, int currentRow, int currentCol, bool findfindThePath  ) ;

  // ------------------------------------

  public :

    Mode( int numOfG ) ;

    // the function to run the maze
    bool runMaze( char ** aMaze, char ** vMaze, int currentRow, int currentCol, char dir ) ;

};

/** ======================= Mode(functions) ======================= **/


// construction
// set the numOfG
Mode::Mode( int numOfG ) {

  this -> numOfG = numOfG ;

} // Mode()

// ---------------------------------- runMaze() ----------------------------------

// The function to run the maze
// -
// path: the route of the maze
// maze: the visiting of the maze
// currentRow: the current row of the mouse
// currentCol: the current col of the mouse
// dir: the direction of the mouse facing( E:east, W:west, S:south, N:north )
// -
bool Mode::runMaze( char ** path, char ** maze, int currentRow, int currentCol, char dir ) {

  bool findThePath = false ;

  // cout << currentRow << ", " << currentCol << endl;

  if ( isRoute == true ) {

    if ( path[currentRow][currentCol] != 'G' )
      path[currentRow][currentCol] = 'R' ;

  } // if


  // 'g' is G that has been passed
  //  to assure the mouse won't pass a G that has been passed
  if ( maze[currentRow][currentCol] == 'G' )
    maze[currentRow][currentCol] = 'g' ;
  else
    maze[currentRow][currentCol] = 'V' ;
  // mark the route with R

  // if the mouse is facing the east
  if ( dir == 'E' ) {

    findThePath = goingEast( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingSouth( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingWest( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingNorth( path, maze, currentRow, currentCol, findThePath ) ;

  } // if
  // if the mouse is facing the south
  else if ( dir == 'S' ) {

    findThePath = goingSouth( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingWest( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingNorth( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingEast( path, maze, currentRow, currentCol, findThePath ) ;

  } // else if
  // if the mouse is facing the west
  else if ( dir == 'W' ) {

    findThePath = goingWest( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingNorth( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingEast( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingSouth( path, maze, currentRow, currentCol, findThePath ) ;

  } // else if
  // if the mouse is facing the north
  else if ( dir == 'N' ) {

    findThePath = goingNorth( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingEast( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingSouth( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingWest( path, maze, currentRow, currentCol, findThePath ) ;

  } // else if

  // change g back to G
  if ( maze[currentRow][currentCol] == 'g' )
    maze[currentRow][currentCol] = 'G' ;

  // mark the route with R
  if ( path[currentRow][currentCol] == 'R' ) {
    isRoute = true ;
  } // if

  // cout << "counts = " << countsOfG << endl ;
  // cout << "isRoute = " << isRoute << endl ;
  // cout << endl ;

  if ( findThePath == true ) {

    return true ;

  } // if

  return false ;

} // runMaze

// ---------------------------------- goingEast() ----------------------------------

// check the east cell is able to pass. If yes, then move forward that cell.
// And if the mouse passes over a certain number of goals, returns true; else, returns false
bool Mode::goingEast( char ** path, char ** maze, int currentRow, int currentCol, bool findThePath ) {

  // cout << "going east form " << currentRow << ", " << currentCol << ": " ;

  /** east */
  if( currentCol < Maze::getCol() - 1 && findThePath == false &&
      ( maze[currentRow][currentCol + 1] == 'E' || maze[currentRow][currentCol + 1] == 'G' ) ) {

    // cout << "sucessed " << endl;
    isRoute = false ;

    // if the next step is the goal
    if ( maze[currentRow][currentCol + 1] == 'G'  ) {

      countsOfG ++ ;
      isRoute = true ;

      // cout << "== reach the goal - " << countsOfG << " ==" << endl;
        path[currentRow][currentCol] = 'R' ;

      // if the mouse passes over the specified number of G
      if ( countsOfG == numOfG ) {
        return true ;
      } // if
      // if not, going on
      else {
        findThePath = runMaze( path, maze, currentRow, currentCol + 1, 'E' ) ;
      } // else

    } // if
    else {
      findThePath = runMaze( path, maze, currentRow, currentCol + 1, 'E' ) ;
    } // else


  } // if
  // else
    // cout << "fail" << endl ;

  // mark the cell with R if it's the route
  if ( isRoute == true ) {

    if ( path[currentRow][currentCol] != 'G' )
      path[currentRow][currentCol] = 'R' ;

  } // if

  return findThePath;

} // goingEast()

// ---------------------------------- goingWest() ----------------------------------

// check the west cell is able to pass. If yes, then move forward that cell.
// And if the mouse passes over a certain number of goals, returns true; else, returns false
bool Mode::goingWest( char ** path, char ** maze, int currentRow, int currentCol, bool findThePath  ) {

  // cout << "going west form " << currentRow << ", " << currentCol << ": " ;

  /** west */
  if( currentCol > 0 && findThePath == false &&
      ( maze[currentRow][currentCol - 1] == 'E' || maze[currentRow][currentCol - 1] == 'G' ) ) {

    // cout << "sucessed " << endl;
    isRoute = false ;

    // if the next step is the goal
    if ( maze[currentRow][currentCol - 1] == 'G'  ) {

      countsOfG ++ ;
      isRoute = true ;

      // cout << "== reach the goal - " << countsOfG << " ==" << endl;
        path[currentRow][currentCol] = 'R' ;

      if ( countsOfG == numOfG ) {
        return true ;
      } // if
      else {
        findThePath = runMaze( path, maze, currentRow, currentCol - 1, 'W' ) ;
      } // else
    } // if
    else {
      findThePath = runMaze( path, maze, currentRow, currentCol - 1, 'W' ) ;
    } // else


  } // if

  // mark the cell with R if it's the route
  if ( isRoute == true ) {

    if ( path[currentRow][currentCol] != 'G' )
      path[currentRow][currentCol] = 'R' ;

  } // if

  return findThePath;

} // goingWest()

// ---------------------------------- goingSouth() ----------------------------------

// check the south cell is able to pass. If yes, then move forward that cell.
// And if the mouse passes over a certain number of goals, returns true; else, returns false
bool Mode::goingSouth( char ** path, char ** maze, int currentRow, int currentCol, bool findThePath  ) {

  // cout << "going south form " << currentRow << ", " << currentCol << ": " ;

  /** south */
  if( currentRow < Maze::getRow() - 1 && findThePath == false &&
      ( maze[currentRow + 1][currentCol] == 'E' || maze[currentRow + 1][currentCol] == 'G' ) ) {

    // cout << "sucessed " << endl;
    isRoute = false ;

    // if the next step is the goal
    if ( maze[currentRow + 1][currentCol] == 'G'  ) {

      countsOfG ++ ;
      isRoute = true ;

      // cout << "== reach the goal - " << countsOfG << " ==" << endl;
        path[currentRow][currentCol] = 'R' ;

      if ( countsOfG == numOfG ) {
        return true ;
      } // if
      else {
        findThePath = runMaze( path, maze, currentRow + 1, currentCol, 'S' ) ;
      } // else

    } // if
    else{
      findThePath = runMaze( path, maze, currentRow + 1, currentCol, 'S' ) ;
    } // else

  } // if

  // mark the cell with R if it's the route
  if ( isRoute == true ) {

    if ( path[currentRow][currentCol] != 'G' )
      path[currentRow][currentCol] = 'R' ;

  } // if

  return findThePath;

} // goingSouth

// ---------------------------------- goingNorth() ----------------------------------

// check the south cell is able to pass. If yes, then move forward that cell.
// And if the mouse passes over a certain number of goals, returns true; else, returns false
bool Mode::goingNorth( char ** path, char ** maze, int currentRow, int currentCol, bool findThePath  ) {

  // cout << "going north form " << currentRow << ", " << currentCol << ": " ;

  /** north */
  if( currentRow > 0 && findThePath == false &&
      ( maze[currentRow - 1][currentCol] == 'E' || maze[currentRow - 1][currentCol] == 'G' ) ) {

    // cout << "sucessed " << endl;
    isRoute = false ;

    // if the next step is the goal
    if ( maze[currentRow - 1][currentCol] == 'G'  ) {

      countsOfG ++ ;
      isRoute = true ;

      // cout << "== reach the goal - " << countsOfG << " ==" << endl;
      path[currentRow][currentCol] = 'R' ;

      if ( countsOfG == numOfG ) {
        return true ;
      } // if
      else {
        findThePath = runMaze( path, maze, currentRow - 1, currentCol, 'N' ) ;
      } // else
    } // if
    else {
      findThePath = runMaze( path, maze, currentRow - 1, currentCol, 'N' ) ;
    } // else


  } // if

  // mark the cell with R if it's the route
  if ( isRoute == true ) {

    if ( path[currentRow][currentCol] != 'G' )
      path[currentRow][currentCol] = 'R' ;

  } // if

  return findThePath;

} // goingNorth

/** ======================= main() ======================= **/

int main() {



  do {

    Maze aMaze ;  // a matrix
    string fileName ;  // a file name
    string inputNum ;  // a string of the number of the goals
    string strCmd ;  // a string of the command
    int cmd = -1 ;  // user command
    int numOfG = 1 ;  // the number of the goals

    cout << "*** Path Finding ***\n"  ;
    cout <<  "* 0. Quit          *\n" ;
    cout <<  "* 1. One goal      *\n" ;
    cout <<  "* 2. More goals    *\n" ;
    cout <<  "********************\n" ;
    cout <<  "Input a command(0, 1, 2): " ;

    cin >> strCmd ;
    cout << endl ;

    cmd = stoi(strCmd) ;

    if ( !Check::isInteger( strCmd ) ){
      cout << "Command does not exist!" << endl << endl ;
    } // if
    // if the command is 0, stop the program
    else if( cmd == 0 ){
      break ;
    } // else if
    // if the command isn't 1 and 2, then the command does not exist
    else if ( cmd != 1 && cmd != 2 ){

      cout << "Command does not exist!" << endl << endl ;

    } // else if
    else {

      // input the file number
      cout <<  "Input a file number: " ;

      // create the file name with the number
      cin >> fileName ;
      fileName = "input" + fileName + ".txt" ;
      cout << endl ;

      // input the maze. If input successfully, return true
      if( aMaze.inputMaze( fileName ) ) {

        Maze vMaze( aMaze.getMaze() ) ; // a copy of visiting the maze

        if ( cmd == 2 ) {

          // input the numOfG and ensure it's in the correct type
          do {

            // input a string of the number of G
            cout << "Number of G (goals):" ;
            cin >> inputNum ;
            cout << endl ;

            // check if the number in the range of 1 to 100
            if ( Check::isInteger( inputNum ) && !Check::inRange( inputNum ) ) {
              cout << "### The number must be in [1,100] ###" << endl << endl ;
            } // if

          } while( !Check::isInteger( inputNum ) || !Check::inRange( inputNum ) ) ;

          numOfG = stoi( inputNum ) ;

        } // if

        Mode mode( numOfG ) ;
        bool success = mode.runMaze( aMaze.getMaze(), vMaze.getMaze(), 0, 0, 'E' ) ;

        // print the visited cells
        vMaze.printMaze() ;

        // if the mouse pass a certain number of goals, then print the route
        if ( success )
          aMaze.printMaze() ;

        vMaze.clr() ;

      } // if

      aMaze.clr() ;
    }

  } while( true ) ;

  return 0 ;

} // main()

/** ======================= main() ======================= **/



