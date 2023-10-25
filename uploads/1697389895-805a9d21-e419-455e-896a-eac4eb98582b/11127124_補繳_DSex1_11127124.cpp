// 11127124 何俊霆
#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include <cstdlib>
using namespace std;
#define infinity 0x0fffffff

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
  vector<vector<int>> deepMatrix;
  // vector<vector<Direction>> DirectionMatrix;


  int currentGoal = 0;             // number of G currently get
  // Direction direction = RIGHT;     // direction
  int shortestPath = infinity;
  // vector<char> bufx;
  // vector<char> bufy;

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

  void outputDeepMatrix() {
    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j) cout << deepMatrix[i][j] ;
      cout << endl;
    }
    cout << endl;
  }

  void setMaze2( ) {
    deepMatrix.resize(y, vector<int>(x));
    for (int i = 0; i < y; ++i) 
      for (int j = 0; j < x; ++j) if( matrix[i][j] == 'E' ) deepMatrix[i][j] = -1;
  }

  // a function to copy data
  void copy( Maze &newMaze ) {
    newMaze.matrix = matrix;
    newMaze.x = x;
    newMaze.y = y;
    newMaze.goal = goal;
  }

  // function to find next step
  bool findNextStep( int posX, int posY, Direction & direction ) {

    if ( direction == RIGHT ) {
      if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' ||  matrix[posY][posX+1] == 'G'  ) ) {         // RIGHT
        return true;
      }
      else {
        if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G'  ) ) {       // DOWN
          direction = DOWN;
          return true;
        }
        else {
          if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G'  ) ) {    // LEFT
            direction = LEFT;
            return true;
          }
          else {
            if ( posY - 1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G'  ) ) {  // UP
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
      if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G'  ) ) {         // Down
        return true;
      }
      else {
        if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G'  ) ) {      // LEFT
          direction = LEFT;
          return true;
        }
        else {
          if ( posY - 1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G'  ) ) {    // UP
            direction = UP;
            return true;
          }
          else {
            if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' || matrix[posY][posX+1] == 'G'  ) ) {   // RIGHT
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
      if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G'  ) ) {        // LEFT
        return true;
      }
      else {
        if ( posY - 1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G'  ) ) {      // UP
          direction = UP;
          return true;
        }
        else {
          if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' || matrix[posY][posX+1] == 'G'  ) ) {     // RIGHT
            direction = RIGHT;
            return true;
          }
          else {
            if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G'  ) ) {   // DOWN
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
      if ( posY - 1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G'  ) ) {        // UP
        return true;
      }
      else {
        if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' || matrix[posY][posX+1] == 'G'  ) ) {       // RIGHT
          direction = RIGHT;
          return true;
        }
        else {
          if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G' ) ) {     // DOWN
            direction = DOWN;
            return true;
          }
          else {
            if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G'  ) ) {  // LEFT
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


  // function to find next step  if returning
  bool confirmPoint( int posX, int posY, Direction nowDirection ) {

    if ( nowDirection == RIGHT ) {
      // right
      if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' || matrix[posY][posX+1] == 'G' ) ) {
        return true;
      }
    }
 
    if ( nowDirection == DOWN ) {
      // down
      if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G' ) ) {
        return true;
      }
    }

    if ( nowDirection == LEFT ) {
      // left
      if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G' ) ) {
        return true;
      }
    }

    if ( nowDirection == UP ) {
      // up
      if ( posY -1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G' ) ) {
        return true;
      }
    }

    return false;
  }




  // function to create V path and R path
  bool findPath( int posX, int posY, Maze &rMaze, Direction direction ) {

    // outputMatrix();

    bool getG = false;                                           // whether meet G
    bool changeToR = false;                                      // whether added to route

    if ( matrix[posY][posX] == 'E' ) matrix[posY][posX] = 'V';   // add to visit way

    if ( matrix[posY][posX] == 'G' ) {
      currentGoal++;                                             // increase get gaol
      matrix[posY][posX] = 'J';                                  // Change G to J
      if ( goal == currentGoal ) {
        if ( getG == true ) changeToR = true;
        if ( ( changeToR || getG ) && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R';    // set route        
        return true;                                             // mission accomplished
      }
    }

    bool isFindNextStep = findNextStep( posX, posY, direction );            // detect next step
    if ( isFindNextStep ) {                                      // find next step and call recursion
      if ( direction == RIGHT ) getG = findPath( posX+1, posY, rMaze, direction );
      else if ( direction == DOWN ) getG = findPath( posX, posY+1, rMaze, direction );
      else if ( direction == LEFT ) getG = findPath( posX-1, posY, rMaze, direction );
      else if ( direction == UP ) getG = findPath( posX, posY-1, rMaze, direction );
    }
    else {                                                       // not find next step and return to previous position
      if ( rMaze.matrix[posY][posX] == 'G' ) return true;
      if ( ( changeToR || getG ) && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R';    // set route
      return ( changeToR || getG );
    }

    // return

    if ( matrix[posY][posX] == 'G' || matrix[posY][posX] == 'J' ) changeToR = true;

    if ( getG == true ) changeToR = true; 
    if ( currentGoal == goal ) {
      if ( ( changeToR || getG ) && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R';      // set route
        return ( changeToR || getG );
    }
    else {

      if ( direction == RIGHT )  {
        if ( confirmPoint( posX, posY, RIGHT ) && currentGoal < goal ) getG = findPath( posX+1, posY, rMaze, RIGHT );     // right
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
        if ( confirmPoint( posX, posY, DOWN ) && currentGoal < goal ) getG = findPath( posX, posY+1, rMaze, DOWN );       // down
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
        if ( confirmPoint( posX, posY, LEFT ) && currentGoal < goal ) getG = findPath( posX-1, posY, rMaze, LEFT );       // left
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
        if ( confirmPoint( posX, posY, UP ) && currentGoal < goal ) getG = findPath( posX, posY-1, rMaze, UP );           // up
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
      }

      else if ( direction == DOWN )  {
        if ( confirmPoint( posX, posY, DOWN ) && currentGoal < goal ) getG = findPath( posX, posY+1, rMaze, DOWN );       // down
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
        if ( confirmPoint( posX, posY, LEFT ) && currentGoal < goal ) getG = findPath( posX-1, posY, rMaze, LEFT );       // left
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
        if ( confirmPoint( posX, posY, UP ) && currentGoal < goal ) getG = findPath( posX, posY-1, rMaze, UP );           // up
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
        if ( confirmPoint( posX, posY, RIGHT ) && currentGoal < goal ) getG = findPath( posX+1, posY, rMaze, RIGHT );     // right
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
      } 

      else if ( direction == LEFT ) {
        if ( confirmPoint( posX, posY, LEFT ) && currentGoal < goal ) getG = findPath( posX-1, posY, rMaze, LEFT );       // left
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
        if ( confirmPoint( posX, posY, UP ) && currentGoal < goal ) getG = findPath( posX, posY-1, rMaze, UP );           // up
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
        if ( confirmPoint( posX, posY, RIGHT ) && currentGoal < goal ) getG = findPath( posX+1, posY, rMaze, RIGHT );     // right
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
        if ( confirmPoint( posX, posY, DOWN ) && currentGoal < goal ) getG = findPath( posX, posY+1, rMaze, DOWN );       // down
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
      }

      else if ( direction == UP )  {
        if ( confirmPoint( posX, posY, UP ) && currentGoal < goal ) getG = findPath( posX, posY-1, rMaze, UP );           // up
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
        if ( confirmPoint( posX, posY, RIGHT ) && currentGoal < goal ) getG = findPath( posX+1, posY, rMaze, RIGHT );     // right
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
        if ( confirmPoint( posX, posY, DOWN ) && currentGoal < goal ) getG = findPath( posX, posY+1, rMaze, DOWN );       // down
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
        if ( confirmPoint( posX, posY, LEFT ) && currentGoal < goal ) getG = findPath( posX-1, posY, rMaze, LEFT );       // left
        if ( matrix[posY][posX] == 'G' ) changeToR = true;
        if ( getG ) changeToR = true;
      }
    }


    if ( matrix[posY][posX] == 'G' || matrix[posY][posX] == 'J' ) changeToR = true;
    // if ( getG == true ) changeToR = true;                        // this position is route
    if ( ( changeToR ) && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R';      // set route
    return ( changeToR );

  }


  // function to find next step  if returning
  bool confirmPath( int posX, int posY, Direction nowDirection, int pathNum ) {

    if ( nowDirection == RIGHT ) {
      // right
      if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' || matrix[posY][posX+1] == 'G' ) ) {
        return true;
      }
      if ( posX + 1 < x && matrix[posY][posX+1] == 'V' && deepMatrix[posY][posX+1] - pathNum > 1  ) {
        return true;
      }
    }
 
    if ( nowDirection == DOWN ) {
      // down
      if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G' ) ) {
        return true;
      }
      if ( posY + 1 < y && matrix[posY+1][posX] == 'V' && deepMatrix[posY+1][posX] - pathNum > 1  ) {
        return true;
      }
    }

    if ( nowDirection == LEFT ) {
      // left
      if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G' ) ) {
        return true;
      }
      if ( posX - 1 >= 0 && matrix[posY][posX-1] == 'V' && deepMatrix[posY][posX-1] - pathNum > 1  ) {
        return true;
      }
    }

    if ( nowDirection == UP ) {
      // up
      if ( posY -1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G' ) ) {
        return true;
      }
      if ( posY -1 >= 0 && matrix[posY-1][posX] == 'V' && deepMatrix[posY-1][posX] - pathNum > 1  ) {
        return true;
      }
    }

    return false;
  }


  void deleteR( ) {
    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j) {
        if ( matrix[i][j] == 'R' ) matrix[i][j] = 'E';
      }
    }
  }

  bool findNextStep2( int posX, int posY, Direction &nowDirection, int pathNum ) {

    if ( nowDirection == RIGHT ) {
      // right
      if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' || matrix[posY][posX+1] == 'G' ) ) {
        return true;
      }
      if ( posX + 1 < x && matrix[posY][posX+1] == 'V' && deepMatrix[posY][posX+1] - pathNum > 1  ) {
        return true;
      }
      // down
      if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G' ) ) {
        nowDirection = DOWN;
        return true;
      }
      if ( posY + 1 < y && matrix[posY+1][posX] == 'V' && deepMatrix[posY+1][posX] - pathNum > 1  ) {
        nowDirection = DOWN;
        return true;
      }
      // left
      if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G' ) ) {
        nowDirection = LEFT;
        return true;
      }
      if ( posX - 1 >= 0 && matrix[posY][posX-1] == 'V' && deepMatrix[posY][posX-1] - pathNum > 1  ) {
        nowDirection = LEFT;
        return true;
      }
      // up
      if ( posY -1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G' ) ) {
        nowDirection = UP;
        return true;
      }
      if ( posY -1 >= 0 && matrix[posY-1][posX] == 'V' && deepMatrix[posY-1][posX] - pathNum > 1  ) {
        nowDirection = UP;
        return true;
      }
    }

    else if ( nowDirection == DOWN ) {
      // down
      if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G' ) ) {
        return true;
      }
      if ( posY + 1 < y && matrix[posY+1][posX] == 'V' && deepMatrix[posY+1][posX] - pathNum > 1  ) {
        return true;
      }
      // left
      if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G' ) ) {
        nowDirection = LEFT;
        return true;
      }
      if ( posX - 1 >= 0 && matrix[posY][posX-1] == 'V' && deepMatrix[posY][posX-1] - pathNum > 1  ) {
        nowDirection = LEFT;
        return true;
      }
      // up
      if ( posY -1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G' ) ) {
        nowDirection = UP;
        return true;
      }
      if ( posY -1 >= 0 && matrix[posY-1][posX] == 'V' && deepMatrix[posY-1][posX] - pathNum > 1  ) {
        nowDirection = UP;
        return true;
      }
      // right
      if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' || matrix[posY][posX+1] == 'G' ) ) {
        nowDirection = RIGHT;
        return true;
      }
      if ( posX + 1 < x && matrix[posY][posX+1] == 'V' && deepMatrix[posY][posX+1] - pathNum > 1  ) {
        nowDirection = RIGHT;
        return true;
      }
    }

    else if ( nowDirection == LEFT ) {
      // left
      if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G' ) ) {
        return true;
      }
      if ( posX - 1 >= 0 && matrix[posY][posX-1] == 'V' && deepMatrix[posY][posX-1] - pathNum > 1  ) {
        return true;
      }
      // up
      if ( posY -1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G' ) ) {
        nowDirection = UP;
        return true;
      }
      if ( posY -1 >= 0 && matrix[posY-1][posX] == 'V' && deepMatrix[posY-1][posX] - pathNum > 1  ) {
        nowDirection = UP;
        return true;
      }
      // right
      if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' || matrix[posY][posX+1] == 'G' ) ) {
        nowDirection = RIGHT;
        return true;
      }
      if ( posX + 1 < x && matrix[posY][posX+1] == 'V' && deepMatrix[posY][posX+1] - pathNum > 1  ) {
        nowDirection = RIGHT;
        return true;
      }
      // down
      if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G' ) ) {
        nowDirection = DOWN;
        return true;
      }
      if ( posY + 1 < y && matrix[posY+1][posX] == 'V' && deepMatrix[posY+1][posX] - pathNum > 1  ) {
        nowDirection = DOWN;
        return true;
      }
    }

    else if ( nowDirection == UP ) {
      // up
      if ( posY -1 >= 0 && ( matrix[posY-1][posX] == 'E' || matrix[posY-1][posX] == 'G' ) ) {
        return true;
      }
      if ( posY -1 >= 0 && matrix[posY-1][posX] == 'V' && deepMatrix[posY-1][posX] - pathNum > 1  ) {
        return true;
      }
      // right
      if ( posX + 1 < x && ( matrix[posY][posX+1] == 'E' || matrix[posY][posX+1] == 'G' ) ) {
        nowDirection = RIGHT;
        return true;
      }
      if ( posX + 1 < x && matrix[posY][posX+1] == 'V' && deepMatrix[posY][posX+1] - pathNum > 1  ) {
        nowDirection = RIGHT;
        return true;
      }
      // down
      if ( posY + 1 < y && ( matrix[posY+1][posX] == 'E' || matrix[posY+1][posX] == 'G' ) ) {
        nowDirection = DOWN;
        return true;
      }
      if ( posY + 1 < y && matrix[posY+1][posX] == 'V' && deepMatrix[posY+1][posX] - pathNum > 1  ) {
        nowDirection = DOWN;
        return true;
      }
      // left
      if ( posX - 1 >= 0 && ( matrix[posY][posX-1] == 'E' || matrix[posY][posX-1] == 'G' ) ) {
        nowDirection = LEFT;
        return true;
      }
      if ( posX - 1 >= 0 && matrix[posY][posX-1] == 'V' && deepMatrix[posY][posX-1] - pathNum > 1  ) {
        nowDirection = LEFT;
        return true;
      }
    }

    return false;
  }




  bool findShortestWay( int posX, int posY, Maze &rMaze, int pathNum, Direction nowDirection ) {

    bool isShortest = false;
    bool changeToR = false;


    // cout << pathNum <<  "  " << shortestPath << "  " << posX << " " << posY << " " << deepMatrix[posY+1][posX] << " " << deepMatrix[posY][posX] << endl ;


    if ( matrix[posY][posX] == 'E' && matrix[posY][posX] != 'G' ) {
      matrix[posY][posX] = 'V';
      if ( deepMatrix[posY][posX] == -1 ||  pathNum < deepMatrix[posY][posX] ) {
        deepMatrix[posY][posX] = pathNum;
      }
    }

    if ( matrix[posY][posX] == 'G' ) {
      if ( pathNum < shortestPath ) {
        shortestPath = pathNum;
        rMaze.deleteR();
        return true;
      }
      return changeToR;
    }

    if ( pathNum >= shortestPath-1 ) {
      if ( changeToR && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R' ;
      return changeToR;
    }

    bool isFindNextStep = findNextStep2( posX, posY, nowDirection, pathNum );
    if ( isFindNextStep ) {                                     
      if ( nowDirection == RIGHT )  isShortest = findShortestWay( posX+1, posY, rMaze, pathNum+1, nowDirection );
      else if ( nowDirection == DOWN )  isShortest = findShortestWay( posX, posY+1, rMaze, pathNum+1, nowDirection );
      else if ( nowDirection == LEFT )  isShortest = findShortestWay( posX-1, posY, rMaze, pathNum+1, nowDirection );
      else if ( nowDirection == UP )  isShortest = findShortestWay( posX, posY-1, rMaze, pathNum+1, nowDirection );
    }
    else {                                                       
      if ( changeToR && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R' ;
      return changeToR;
    }



    // return
    // cout << "return : " << pathNum <<  "  " << shortestPath << "  " << posX << " " << posY << " " << deepMatrix[posY+1][posX] << " " << deepMatrix[posY][posX] << endl ;

    if ( isShortest ) changeToR = true;
    if ( pathNum >= shortestPath-1 ) {
      if ( changeToR && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R' ;
      return changeToR;
    } 
    else {
      if ( nowDirection == RIGHT )  {
        if ( confirmPath( posX, posY, RIGHT, pathNum ) ) isShortest = findShortestWay( posX+1, posY, rMaze, pathNum+1, RIGHT );     // right
        if ( isShortest ) changeToR = true;
        if ( confirmPath( posX, posY, DOWN, pathNum ) ) isShortest = findShortestWay( posX, posY+1, rMaze, pathNum+1, DOWN );       // down
        if ( isShortest ) changeToR = true;
        if ( confirmPath( posX, posY, LEFT, pathNum ) ) isShortest = findShortestWay( posX-1, posY, rMaze, pathNum+1, LEFT );       // left
        if ( isShortest ) changeToR = true;
        if ( confirmPath( posX, posY, UP, pathNum ) ) isShortest = findShortestWay( posX, posY-1, rMaze, pathNum+1, UP );           // up
        if ( isShortest ) changeToR = true;
      }

      else if ( nowDirection == DOWN )  {
        if ( confirmPath( posX, posY, DOWN, pathNum ) ) isShortest = findShortestWay( posX, posY+1, rMaze, pathNum+1, DOWN );       // down
        if ( isShortest ) changeToR = true;
        if ( confirmPath( posX, posY, LEFT, pathNum ) ) isShortest = findShortestWay( posX-1, posY, rMaze, pathNum+1, LEFT );       // left
        if ( isShortest ) changeToR = true;
        if ( confirmPath( posX, posY, UP, pathNum ) ) isShortest = findShortestWay( posX, posY-1, rMaze, pathNum+1, UP );           // up
        if ( isShortest ) changeToR = true;
        if ( confirmPath( posX, posY, RIGHT, pathNum ) ) isShortest = findShortestWay( posX+1, posY, rMaze, pathNum+1, RIGHT );     // right
        if ( isShortest ) changeToR = true;
      } 

      else if ( nowDirection == LEFT ) {
        if ( confirmPath( posX, posY, LEFT, pathNum ) ) isShortest = findShortestWay( posX-1, posY, rMaze, pathNum+1, LEFT );       // left
        if ( isShortest ) changeToR = true;
        if ( confirmPath( posX, posY, UP, pathNum ) ) isShortest = findShortestWay( posX, posY-1, rMaze, pathNum+1, UP );           // up
        if ( isShortest ) changeToR = true;
        if ( confirmPath( posX, posY, RIGHT, pathNum ) ) isShortest = findShortestWay( posX+1, posY, rMaze, pathNum+1, RIGHT );     // right
        if ( isShortest ) changeToR = true;
        if ( confirmPath( posX, posY, DOWN, pathNum ) ) isShortest = findShortestWay( posX, posY+1, rMaze, pathNum+1, DOWN );       // down
        if ( isShortest ) changeToR = true;
      }

      else if ( nowDirection == UP )  {
        if ( confirmPath( posX, posY, UP, pathNum ) ) isShortest = findShortestWay( posX, posY-1, rMaze, pathNum+1, UP );           // up
        if ( isShortest ) changeToR = true;
        if ( confirmPath( posX, posY, RIGHT, pathNum ) ) isShortest = findShortestWay( posX+1, posY, rMaze, pathNum+1, RIGHT );     // right
        if ( isShortest ) changeToR = true;
        if ( confirmPath( posX, posY, DOWN, pathNum ) ) isShortest = findShortestWay( posX, posY+1, rMaze, pathNum+1, DOWN );       // down
        if ( isShortest ) changeToR = true;
        if ( confirmPath( posX, posY, LEFT, pathNum ) ) isShortest = findShortestWay( posX-1, posY, rMaze, pathNum+1, LEFT );       // left
        if ( isShortest ) changeToR = true;
      }
    }


    if ( changeToR && rMaze.matrix[posY][posX] != 'G' ) rMaze.matrix[posY][posX] = 'R' ;
    return changeToR;

  }



  int getShortestPath() {
    return shortestPath;
  }

  // function change J to G
  void changeJToG() {
    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j)
          if ( matrix[i][j] == 'J' ) matrix[i][j] = 'G';
    }
  }

  // function to solve maze problem
  bool solveMazeProblem( Maze &vMaze, Maze &rMaze, int goalNum, int command ) {
    goal = goalNum;
    copy( vMaze );
    copy( rMaze );

    bool getG = false;

    // vMaze.outputMatrix();
    vMaze.setMaze2();
    // vMaze.outputDeepMatrix();

    if ( command == 1 || command == 2 ) bool getReturn = vMaze.findPath( 0, 0, rMaze, RIGHT );
    if ( command == 3 ) getG = vMaze.findShortestWay( 0, 0, rMaze, 1, RIGHT );

    // vMaze.outputDeepMatrix();
    vMaze.changeJToG();
    // cout << endl << vMaze.currentGoal << endl;

    // cout << vMaze.shortestPath << endl;
    if ( vMaze.currentGoal == vMaze.goal || getG ) return true;
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
    cout << endl << "Input a command(0, 1, 2, 3): ";
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

    if ( command == 1 || command == 2 || command == 3 ) {                             // one goal or more goal
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

        
        maze.setMaze( inputFile );                                                // save the file into maze
        Maze vMaze;                                                              // store visit path
        Maze rMaze;                                                              // stroe route
        bool isFind = maze.solveMazeProblem( vMaze, rMaze, goal, command );      // Start Solve Problem


        vMaze.outputMatrix();                                                   // Output visit path
        if ( isFind ) {
          rMaze.outputMatrix();                                                 // Find all goals
          if ( command == 3 ) cout << endl << "Shortest path length = " << vMaze.getShortestPath() << endl;
        } 
        else {
          if ( command == 3 ) {
            cout << endl << "### There is no path to find a goal! ###" << endl;
          }
        }
        inputFile.close();                                                      // close file
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
