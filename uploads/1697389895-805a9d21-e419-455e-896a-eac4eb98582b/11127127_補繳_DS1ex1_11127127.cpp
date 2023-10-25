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

  if ( num <= 100 && num >= 1 )
    return true ;

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
  for ( int i = 0; i < Maze::row; i++ )
    delete[] maze[i];

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
    int minLen = -1 ;
    int maxLen ;
    int mode ;

    // ------------- mode 1, 2 ------------------

    // check the cell is able to pass. If yes, then move forward that cell.
    // And if the mouse passes over a certain number of goals, returns true; else, returns false
    bool goingEast( char ** path, char ** maze, int currentRow, int currentCol, bool findfindThePath  ) ;
    bool goingWest( char ** path, char ** maze, int currentRow, int currentCol, bool findfindThePath  ) ;
    bool goingSouth( char ** path, char ** maze, int currentRow, int currentCol, bool findfindThePath  ) ;
    bool goingNorth( char ** path, char ** maze, int currentRow, int currentCol, bool findfindThePath  ) ;

    // ------------- mode 3 ------------------

    // same as above, but to find the shortest path
    bool goingEast( char ** path, char ** maze, int currentRow, int currentCol, bool findfindThePath, int len ) ;
    bool goingWest( char ** path, char ** maze, int currentRow, int currentCol, bool findfindThePath, int len  ) ;
    bool goingSouth( char ** path, char ** maze, int currentRow, int currentCol, bool findfindThePath, int len  ) ;
    bool goingNorth( char ** path, char ** maze, int currentRow, int currentCol, bool findfindThePath, int len ) ;

    // same as above, but to mark the shortest path
    bool goingEast( char ** maze, int currentRow, int currentCol, int len ) ;
    bool goingWest( char ** maze, int currentRow, int currentCol, int len  ) ;
    bool goingSouth( char ** maze, int currentRow, int currentCol, int len  ) ;
    bool goingNorth( char ** maze, int currentRow, int currentCol, int len ) ;

  // ------------------------------------

  public :

    Mode( int numOfG ) ;

    // the function to run the maze in mode 1 and 2
    bool runMaze( char ** aMaze, char ** vMaze, int currentRow, int currentCol, char dir ) ;

    // the function to run the maze in mode 3
    bool runMaze( char ** aMaze, char ** vMaze, int currentRow, int currentCol, char dir, int len ) ;

    bool markShortestRoute( char ** maze, int currentRow, int currentCol, int len, char dir  ) ;

    void setMode( int mode ) ;

    int getMinLen() ;
};

/** ======================= Mode(functions) ======================= **/


// construction
// set the numOfG
Mode::Mode( int numOfG ) {

  this -> numOfG = numOfG ;
  isRoute = false ;
  maxLen = Maze::getCol() * Maze::getRow() + 1 ;

} // Mode()

// ======================================= mode 1, 2 ===========================================

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
    findThePath = goingNorth( path, maze, currentRow, currentCol, findThePath ) ;

  } // if
  // if the mouse is facing the south
  else if ( dir == 'S' ) {

    findThePath = goingSouth( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingWest( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingEast( path, maze, currentRow, currentCol, findThePath ) ;

  } // else if
  // if the mouse is facing the west
  else if ( dir == 'W' ) {

    findThePath = goingWest( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingNorth( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingSouth( path, maze, currentRow, currentCol, findThePath ) ;

  } // else if
  // if the mouse is facing the north
  else if ( dir == 'N' ) {

    findThePath = goingNorth( path, maze, currentRow, currentCol, findThePath ) ;
    findThePath = goingEast( path, maze, currentRow, currentCol, findThePath ) ;
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


// ======================================= mode 3 ===========================================

// ---------------------------------- runMaze() ----------------------------------

// The function to run the maze
// -
// path: the route of the maze
// maze: the visiting of the maze
// currentRow: the current row of the mouse
// currentCol: the current col of the mouse
// dir: the direction of the mouse facing( E:east, W:west, S:south, N:north )
// -
bool Mode::runMaze( char ** path, char ** maze, int currentRow, int currentCol, char dir, int len ) {

  bool findThePath = false ;

  len ++ ;

  char enter ;
  // scanf( "%c", &enter ) ;

  if ( minLen != -1 && len > minLen ) {
    return true ;
  } // if

  if ( len > maxLen )
    return false ;

  // cout << currentRow << ", " << currentCol << endl;
  // cout << "len = " << len << ", minLen = " << minLen << endl ;

  // 'g' is G that has been passed
  //  to assure the mouse won't pass a G that has been passed
  if ( maze[currentRow][currentCol] == 'G' )
    maze[currentRow][currentCol] = 'g' ;
  else
    maze[currentRow][currentCol] = 'V' ;
  // mark the route with R

  // if the mouse is facing the east
  if ( dir == 'E' ) {

    findThePath = goingEast( path, maze, currentRow, currentCol, findThePath, len ) ;
    findThePath = goingSouth( path, maze, currentRow, currentCol, findThePath, len ) ;
    findThePath = goingNorth( path, maze, currentRow, currentCol, findThePath, len ) ;

  } // if
  // if the mouse is facing the south
  else if ( dir == 'S' ) {

    findThePath = goingSouth( path, maze, currentRow, currentCol, findThePath, len ) ;
    findThePath = goingWest( path, maze, currentRow, currentCol, findThePath, len ) ;
    findThePath = goingEast( path, maze, currentRow, currentCol, findThePath, len ) ;

  } // else if
  // if the mouse is facing the west
  else if ( dir == 'W' ) {

    findThePath = goingWest( path, maze, currentRow, currentCol, findThePath, len ) ;
    findThePath = goingNorth( path, maze, currentRow, currentCol, findThePath, len ) ;
    findThePath = goingSouth( path, maze, currentRow, currentCol, findThePath, len ) ;

  } // else if
  // if the mouse is facing the north
  else if ( dir == 'N' ) {

    findThePath = goingNorth( path, maze, currentRow, currentCol, findThePath, len ) ;
    findThePath = goingEast( path, maze, currentRow, currentCol, findThePath, len ) ;
    findThePath = goingWest( path, maze, currentRow, currentCol, findThePath, len ) ;

  } // else if

  // change g back to G
  if ( maze[currentRow][currentCol] == 'g' )
    maze[currentRow][currentCol] = 'G' ;

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
bool Mode::goingEast( char ** path, char ** maze, int currentRow, int currentCol, bool findThePath, int len ) {

  // cout << "going east form " << currentRow << ", " << currentCol << ": " ;

  if ( minLen != -1 && len > minLen ) {
    return true ;
  } // if

  if ( len > maxLen )
    return false ;


  /** east */
  if( currentCol < Maze::getCol() - 1 &&
      ( maze[currentRow][currentCol + 1] == 'E' || maze[currentRow][currentCol + 1] == 'G' || maze[currentRow][currentCol + 1] == 'V' ) ) {

    // cout << "sucessed " << endl;

    // if the next step is the goal
    if ( maze[currentRow][currentCol + 1] == 'G'  ) {

      // cout << "== reach the goal - " << countsOfG << " ==" << endl;

      // if the minLen is bigger than len
      if ( minLen == -1 || minLen > len ){
        minLen = len + 1 ;
      } // if

      return true ;

    } // if
    else {
      findThePath = runMaze( path, maze, currentRow, currentCol + 1, 'E', len) ;
    } // else


  } // if
  else {
    // cout << "fail" << endl ;
  } // else

  return findThePath;

} // goingEast()

// ---------------------------------- goingWest() ----------------------------------

// check the west cell is able to pass. If yes, then move forward that cell.
// And if the mouse passes over a certain number of goals, returns true; else, returns false
bool Mode::goingWest( char ** path, char ** maze, int currentRow, int currentCol, bool findThePath, int len ) {

  // cout << "going west form " << currentRow << ", " << currentCol << ": " ;

  if ( minLen != -1 && len > minLen ) {
    return true ;
  } // if

  if ( len > maxLen )
    return false ;

  /** west */
  if( currentCol > 0 &&
      ( maze[currentRow][currentCol - 1] == 'E' || maze[currentRow][currentCol - 1] == 'G' || maze[currentRow][currentCol - 1] == 'V' ) ) {

    // cout << "sucessed " << endl;

    // if the next step is the goal
    if ( maze[currentRow][currentCol - 1] == 'G'  ) {

      // cout << "== reach the goal - " << countsOfG << " ==" << endl;

      // if the minLen is bigger than len
      if ( minLen == -1 || minLen > len ){
        minLen = len + 1 ;
      } // if

      return true ;

    } // if
    else {
      findThePath = runMaze( path, maze, currentRow, currentCol - 1, 'W', len ) ;
    } // else


  } // if
  else {
    // cout << "fail" << endl ;
  } // else

  return findThePath;

} // goingWest()

// ---------------------------------- goingSouth() ----------------------------------

// check the south cell is able to pass. If yes, then move forward that cell.
// And if the mouse passes over a certain number of goals, returns true; else, returns false
bool Mode::goingSouth( char ** path, char ** maze, int currentRow, int currentCol, bool findThePath, int len ) {

  // cout << "going south form " << currentRow << ", " << currentCol << ": " ;

  if ( minLen != -1 && len > minLen ) {
    return true ;
  } // if

  if ( len > maxLen )
    return false ;

  /** south */
  if( currentRow < Maze::getRow() - 1 &&
      ( maze[currentRow + 1][currentCol] == 'E' || maze[currentRow + 1][currentCol] == 'G'|| maze[currentRow + 1][currentCol] == 'V' ) ) {

    // cout << "sucessed " << endl;

    // if the next step is the goal
    if ( maze[currentRow + 1][currentCol] == 'G'  ) {

      // cout << "== reach the goal - " << countsOfG << " ==" << endl;

      // if the minLen is bigger than len
      if ( minLen == -1 || minLen > len ){
        minLen = len + 1 ;
      } // if

      return true ;

    } // if
    else{
      findThePath = runMaze( path, maze, currentRow + 1, currentCol, 'S', len ) ;
    } // else

  } // if
  else {
    // cout << "fail" << endl ;
  } // else

  return findThePath;

} // goingSouth

// ---------------------------------- goingNorth() ----------------------------------

// check the south cell is able to pass. If yes, then move forward that cell.
// And if the mouse passes over a certain number of goals, returns true; else, returns false
bool Mode::goingNorth( char ** path, char ** maze, int currentRow, int currentCol, bool findThePath, int len ) {

  // cout << "going north form " << currentRow << ", " << currentCol << ": " ;

  if ( minLen != -1 && len > minLen ) {
    return true ;
  } // if

  if ( len > maxLen )
    return false ;

  /** north */
  if( currentRow > 0 &&
      ( maze[currentRow - 1][currentCol] == 'E' || maze[currentRow - 1][currentCol] == 'G' || maze[currentRow - 1][currentCol] == 'V' ) ) {

    // cout << "sucessed " << endl;

    // if the next step is the goal
    if ( maze[currentRow - 1][currentCol] == 'G'  ) {

      // cout << "== reach the goal - " << countsOfG << " ==" << endl;

      // if the minLen is bigger than len
      if ( minLen == -1 || minLen > len ){
        minLen = len + 1 ;
      } // if

      return true ;

    } // if
    else {
      findThePath = runMaze( path, maze, currentRow - 1, currentCol, 'N', len + 1 ) ;
    } // else


  } // if
  else {
    // cout << "fail" << endl ;
  } // else

  return findThePath;

} // goingNorth


// ---------------------------------- MarkShortestRoute() ----------------------------------

bool Mode::markShortestRoute( char ** maze, int currentRow, int currentCol, int len, char dir ) {

  len ++ ;

  if ( len > minLen ) {
    return isRoute ;
  } // if


  if ( dir == 'E' ) {
    isRoute = goingEast( maze, currentRow, currentCol, len ) ;
    isRoute = goingSouth( maze, currentRow, currentCol, len ) ;
    isRoute = goingNorth( maze, currentRow, currentCol, len ) ;
  } // else if
  else if ( dir == 'S' ) {
    isRoute = goingSouth( maze, currentRow, currentCol, len ) ;
    isRoute = goingWest( maze, currentRow, currentCol, len ) ;
    isRoute = goingEast( maze, currentRow, currentCol, len ) ;
  } // else if
  else if ( dir == 'W' ) {
    isRoute = goingWest( maze, currentRow, currentCol, len ) ;
    isRoute = goingNorth( maze, currentRow, currentCol, len ) ;
    isRoute = goingSouth( maze, currentRow, currentCol, len ) ;
  } // else if
  else if ( dir == 'N' ) {
    isRoute = goingNorth( maze, currentRow, currentCol, len ) ;
    isRoute = goingEast( maze, currentRow, currentCol, len ) ;
    isRoute = goingWest( maze, currentRow, currentCol, len ) ;
  } // else if

  if ( isRoute )
    maze[currentRow][currentCol] = 'R' ;

  return isRoute ;

} // markShortestRoute()

bool Mode::goingEast( char ** maze, int currentRow, int currentCol, int len ) {

  if( currentCol < Maze::getCol() - 1 && maze[currentRow][currentCol + 1] != 'O' && !isRoute ) {

    // if the next step is the goal
    if ( maze[currentRow][currentCol + 1] == 'G'  ){
      maze[currentRow][currentCol] = 'R' ;
      return true ;
    } // if

    isRoute = markShortestRoute( maze, currentRow, currentCol + 1, len, 'E' ) ;

  } // if

  return isRoute ;

} // goingEast

bool Mode::goingWest( char ** maze, int currentRow, int currentCol, int len  ) {

  if( currentCol > 0 && maze[currentRow][currentCol - 1] != 'O' && !isRoute ) {

    // if the next step is the goal
    if ( maze[currentRow][currentCol - 1] == 'G'  ){
      maze[currentRow][currentCol] = 'R' ;
      return true ;
    } // if

    isRoute = markShortestRoute( maze, currentRow, currentCol - 1, len, 'W' ) ;

  } // if

  return isRoute ;

} // goingWest

bool Mode::goingSouth( char ** maze, int currentRow, int currentCol, int len  ) {

  if( currentRow < Maze::getRow() - 1 && maze[currentRow + 1][currentCol] != 'O' && !isRoute  ) {

    // if the next step is the goal
    if ( maze[currentRow + 1][currentCol] == 'G'  ){
      maze[currentRow][currentCol] = 'R' ;
      return true ;
    } // if

    isRoute = markShortestRoute( maze, currentRow + 1, currentCol, len, 'S' ) ;

  } // if

  return isRoute ;

} // goingSouth

bool Mode::goingNorth( char ** maze, int currentRow, int currentCol, int len ) {

  if( currentRow > 0 && maze[currentRow - 1][currentCol] != 'O' && !isRoute ) {

    // if the next step is the goal
    if ( maze[currentRow - 1][currentCol] == 'G'  ){
      maze[currentRow][currentCol] = 'R' ;
      return true ;
    } // if

    isRoute = markShortestRoute( maze, currentRow - 1, currentCol, len, 'N' ) ;

  } // if

  return isRoute ;

} // goingNorth


// ---------------------------------- MarkShortestRoute() ----------------------------------

void Mode::setMode( int mode ) {
  this -> mode = mode ;
} // setMode()


int Mode::getMinLen() {
  return minLen ;
} // getMinLen


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
    cout <<  "* 3. Shortest path *\n" ;
    cout <<  "********************\n" ;
    cout <<  "Input a command(0, 1, 2, 3): " ;

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
    else if ( cmd != 1 && cmd != 2 && cmd != 3 ){

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
        mode.setMode( cmd ) ;
        bool success ;
        bool haveRoute = false ;

        if ( cmd == 3 ){
          success = mode.runMaze( aMaze.getMaze(), vMaze.getMaze(), 0, 0, 'E', 0 ) ;
          haveRoute = mode.markShortestRoute( aMaze.getMaze(), 0, 0, 0, 'E' ) ;
        } // if
        else
          success = mode.runMaze( aMaze.getMaze(), vMaze.getMaze(), 0, 0, 'E' ) ;

        // print the visited cells
        vMaze.printMaze() ;

        // if the mouse pass a certain number of goals, then print the route
        if ( success )
          aMaze.printMaze() ;

        if ( cmd == 3 && haveRoute )
          cout << "Shortest path length = " << mode.getMinLen() << endl << endl ;

        vMaze.clr() ;

      } // if

      aMaze.clr() ;
    }

  } while( true ) ;

  return 0 ;

} // main()

/** ======================= main() ======================= **/



