// 11127124 何俊霆
#include <iostream>
#include <fstream>
#include <vector>
#include<string>
using namespace std;

// four directions
enum Direction {
  UP    ,
  DOWN  ,
  LEFT  ,
  RIGHT
};

// a calss of maze
class Maze{

private:
  int x;                           // width
  int y;                           // height
  int goal;                        // number of Goals to be achieved
  vector<vector<char>> matrix;     // a two-dimensional array to Save maze
  int currentGoal = 0;             // number of G currently get
  Direction direction = RIGHT;     // direction

public:

  // function to read file
  void setMaze( ifstream &InputFile ) {
    InputFile >> x >> y;                                     // store length and width
    matrix.resize(y, vector<char>(x));                       // set matrix size
    for (int i = 0; i < y; ++i) 
      for (int j = 0; j < x; ++j) InputFile >> matrix[i][j]; // input maze
  }

  // output matrix of maze
  void outputMatrix() {
    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j) cout << matrix[i][j] ;
      cout << endl;
    }
    cout << endl;
  }

  // a function to copy data
  void copy( Maze &newMaze ) {
    newMaze.matrix = matrix;
    newMaze.x = x;
    newMaze.y = y;
    newMaze.goal = goal;
  }

  // function to find next step
  bool findNextStep( int posX, int posY ) {

    if ( direction == RIGHT ) {
      if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' ||  matrix[posY][posX+1] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {         // RIGHT
        return true;
      }
      else {
        if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {       // DOWN
          direction = DOWN;
          return true;
        }
        else {
          if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {    // LEFT
            direction = LEFT;
            return true;
          }
          else {
            if ( posY - 1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {  // UP
              direction = UP;
              return true;
            }
            else {
              return false;
            }
          }
        }
      }
    }

    if ( direction == DOWN ) {
      if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {         // Down
        return true;
      }
      else {
        if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {      // LEFT
          direction = LEFT;
          return true;
        }
        else {
          if ( posY - 1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {    // UP
            direction = UP;
            return true;
          }
          else {
            if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' || matrix[posY][posX+1] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {   // RIGHT
              direction = RIGHT;
              return true;
            }
            else {
              return false;
            }
          }
        }
      }
    }

    if ( direction == LEFT ) {
      if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {        // LEFT
        return true;
      }
      else {
        if ( posY - 1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {      // UP
          direction = UP;
          return true;
        }
        else {
          if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' || matrix[posY][posX+1] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {     // RIGHT
            direction = RIGHT;
            return true;
          }
          else {
            if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {   // DOWN
              direction = DOWN;
              return true;
            }
            else {
              return false;
            }
          }
        }
      }
    }

    if ( direction == UP ) {
      if ( posY - 1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {        // UP
        return true;
      }
      else {
        if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' || matrix[posY][posX+1] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {       // RIGHT
          direction = RIGHT;
          return true;
        }
        else {
          if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {     // DOWN
            direction = DOWN;
            return true;
          }
          else {
            if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G' ||  matrix[posY][posX+1] == 'J' ) ) {  // LEFT
              direction = LEFT;
              return true;
            }
            else {
              return false;
            }
          }
        }
      }
    }

    return false;
  }


  // function to create V path and R path
  bool findPath( int posX, int posY, Maze &rMaze ) {

    bool getG = false;                                           // whether meet G
    bool changeToR = false;                                      // whether added to route

    if ( matrix[posY][posX] == 'E' ) matrix[posY][posX] = 'V';   // add to visit way

    if ( matrix[posY][posX] == 'G' ) {
      currentGoal++;                                             // increase get gaol
      matrix[posY][posX] = 'J';                                  // Change G to J
      if ( goal == currentGoal ) return true;                    // mission accomplished
    }

    bool isFindNextStep = findNextStep( posX, posY );            // detect next step
    if ( isFindNextStep ) {                                      // find next step and call recursion
      if ( direction == RIGHT ) getG = findPath( posX+1, posY, rMaze );
      else if ( direction == DOWN ) getG = findPath( posX, posY+1, rMaze );
      else if ( direction == LEFT ) getG = findPath( posX-1, posY, rMaze );
      else if ( direction == UP ) getG = findPath( posX, posY-1, rMaze );
    }
    else {                                                       // not find next step and return to previous position
      if ( rMaze.matrix[posY][posX] == 'G' ) return true;
      if ( ( changeToR || getG ) && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R';    // set route
      return ( changeToR || getG );
    }

    // return 1

    if ( getG == true ) changeToR = true;                        // this position is route
    
    if ( currentGoal == goal ) {                                 // mission accomplished
      if ( ( changeToR || getG ) && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R';
      return true;
    }
    else {                                                       // mission is not accomplished
      isFindNextStep = findNextStep( posX, posY );
      if ( isFindNextStep ) {                                    // find next step and call recursion
        if ( direction == RIGHT ) getG = findPath( posX+1, posY, rMaze );
        else if ( direction == DOWN ) getG = findPath( posX, posY+1, rMaze );
        else if ( direction == LEFT ) getG = findPath( posX-1, posY, rMaze );
        else if ( direction == UP ) getG = findPath( posX, posY-1, rMaze );
      }
      else {                                                     // not find next step and return to previous position
        if ( rMaze.matrix[posY][posX] == 'G' ) return true;
        if ( ( changeToR || getG ) && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R';  // set route
        return ( changeToR || getG );
      }
    }

    // return 2

    if ( getG == true ) changeToR = true;                        // this position is route
    
    if ( currentGoal == goal ) {                                 // mission accomplished
      if ( ( changeToR || getG ) && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R';
      return true;
    }
    else {                                                       // mission is not accomplished
      isFindNextStep = findNextStep( posX, posY );
      if ( isFindNextStep ) {                                    // find next step and call recursion
        if ( direction == RIGHT ) getG = findPath( posX+1, posY, rMaze );
        else if ( direction == DOWN ) getG = findPath( posX, posY+1, rMaze );
        else if ( direction == LEFT ) getG = findPath( posX-1, posY, rMaze );
        else if ( direction == UP ) getG = findPath( posX, posY-1, rMaze );
      }
      else {                                                     // not find next step and return to previous position
        if ( rMaze.matrix[posY][posX] == 'G' ) return true;
        if ( ( changeToR || getG ) && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R';  // set route
        return ( changeToR || getG );
      }
    }

    // return 3

    if ( getG == true ) changeToR = true;                        // this position is route
    if ( ( changeToR || getG ) && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R';      // set route
    return ( changeToR || getG );

  }


  // function change J to G
  void changeJToG() {
    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j)
          if ( matrix[i][j] == 'J' ) matrix[i][j] = 'G';
    }
  }

  // function to solve maze problem
  bool solveMazeProblem( Maze &vMaze, Maze &rMaze, int goalNum ) {
    goal = goalNum;
    copy( vMaze );
    copy( rMaze );
    vMaze.findPath( 0, 0, rMaze );
    vMaze.changeJToG();
    if ( vMaze.currentGoal == vMaze.goal ) return true;
    return false;
  }
};

// function to detect string is a number
bool detectString( string str ) {
  for ( int i = 0 ; i < str.size() ; i++ )
    if ( str[i] - '0' > 9 || str[i] < '0' )  return false;
  return true;
}

// function to output UI
void UIOutput( int mode ) {
  if ( mode == 0 ) {
    cout << endl << "*** Path Finding ***";
    cout << endl << "* 0. Quit          *";
    cout << endl << "* 1. One goal      *";
    cout << endl << "* 2. More goals    *";
    cout << endl << "********************";
    cout << endl << "Input a command(0, 1, 2): ";
  }
  if ( mode == 1 ) cout << endl << "Input a file number: " ;
  if ( mode == 2 ) cout << endl << "Number of G ( goals ) " ;
  if ( mode == 3 ) cout << endl << "### The number must be in [1,100] ###" << endl ;
}

// main
int main()
{
  do {
    int command = 0;                                                 // command number
    int goal = 1;                                                    // number of Goals to be achieved
    int fileNumber;                                                  // number of input file
    Maze maze;                                                       // original maze

    UIOutput(0);                                                     // output user UI
    cin >> command ;                                                 // input command

    if ( command == 1 || command == 2) {                             // one goal or more goal
      UIOutput(1);                                                   // output user UI
      cin >> fileNumber;

      string fileName = "input" + to_string( fileNumber ) + ".txt";  // filename
      ifstream inputFile( fileName );                                // open file

      if (inputFile) {                                               // File opened successfully
        if ( command == 2 ) {
          do {
            string Input;                                            // store number of goals
            UIOutput(2);
            cin >> Input;
            if ( detectString( Input ) ) {                           // string is a number
              int number = stoi( Input );                            // convert string to int
              if ( number >= 1 && number <= 100 ) {
                goal = number;                                       // set goal
                break;                                               // end loop
              }
              else UIOutput(3);                                      // exceeds numeric range
            }
          } while ( true ) ;
        }

        maze.setMaze( inputFile );                                   // save the file into maze
        Maze vMaze;                                                  // store visit path
        Maze rMaze;                                                  // stroe route
        bool isFind = maze.solveMazeProblem( vMaze, rMaze, goal );   // Start Solve Problem
        vMaze.outputMatrix();                                        // Output visit path
        if ( isFind ) rMaze.outputMatrix();                          // Find all goals
        inputFile.close();                                           // close file
      }

      // File opened not successfully
      else if (!inputFile)  cout << endl << fileName << " does not exist!" << endl;
    }

    else if ( command == 0 ) break;                                  // Exit
    else cout << endl << "Command does not exist!" << endl;          // command does not exist

  } while ( true );

  system( "pause" );
  return 0;
}
