#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

enum Mode { One = 101, More = 10110 };
enum Dire { Right = 1034, Down = 952, Left = 870, Up = 788, None = 0 };

class doMaze {
public:
  doMaze() {
    Mazeline = 0;
    Mazecolumn = 0;
    theMaze[0][0] = ' ';
    currentdire = Right;
    N = 1;
  }

  doMaze(doMaze &Origin) {
    Mazeline = Origin.Mazeline;
    Mazecolumn = Origin.Mazecolumn;
    for (int j = 0; j < Origin.Mazecolumn; j++) {
      for (int i = 0; i < Origin.Mazeline; i++) {
        theMaze[i][j] = Origin.theMaze[i][j];
      } // for
    }   // for
  }     // doMaze()

  bool Load(string theFile, Mode mode) {

    ifstream file;
    file.open(theFile.c_str());
    if (file.fail()) {
      cout << endl << "The file-input just failed.";
      return false;
    } // if()

    char tmp;
    file >> Mazeline >> Mazecolumn;
    for (int j = 0; j < Mazecolumn; j++) {
      for (int i = 0; i < Mazeline; i++) {
        file >> tmp;
        if (tmp == 'E' || tmp == 'G' || tmp == 'O')
          theMaze[i][j] = tmp;
      } // for()
    }   // for()

    if (mode == More) {
      cout << endl << " Input the number of Goals :";
      cin >> N;
    } // if()

    file.close();
    return true;
  } // input the file data

  void Clr() {
    for (int j = 0; j < 42; j++) {
      for (int i = 0; i < 42; i++) {
        theMaze[i][j] = ' ';
      } // for()
    }   // for()
  }

  bool findGoals(doMaze &copy, Mode mode) {
    int c = 0;
    int l = 0;
    bool check = false;
    while (N > 0) {
      N = N - 1;
      if (theMaze[l][c] == 'E') {
        copy.theMaze[l][c] = 'V';
        check = Walknext(copy, currentdire, l, c);
      } // if()

      else if (mode == More && theMaze[l][c] == 'G')
        check = Walknext(copy, currentdire, l, c);
    } // while()
    return check;
  } // find the goal, and return the bool if it's success or not

  bool Walknext(doMaze &copy, Dire dire, int &l, int &c) {
    if ( returnBlock(l, c) == 'G' && N == 0 ) {
      returnMaze( copy, dire, l, c ) ;
      return true;
    } // if
    else if (returnBlock(l, c) == 'E')
      copy.theMaze[l][c] = 'V';

    if (dire == Right)
      l = l + 1;
    else if (dire == Down)
      c = c + 1;
    else if (dire == Left)
      l = l - 1;
    else if (dire == Up)
      c = c - 1;

    if (returnBlock(l, c) == 'O') {
      ChangeDire(dire, l, c);
      Walknext(copy, dire, l, c);
    } // else if
    else if (returnBlock(l, c) == 'V') {
      if (dire == None) { // there's no 'E' around
        dire = CheckAround(dire, l, c, 'V');
        if (dire == None)
          return false;
        Walkback(copy, dire, l, c) ;
      } // if
    } // else if
    else 
      Walknext( copy, dire, l, c ) ;

  } // walk through the maze by recursion

  void ChangeDire(Dire &dire, int &l, int &c) {
    if (dire == Right) {
      l = l -1 ;
      dire = Down;
      if (c == Mazecolumn - 1)
        ChangeDire(dire, l, c);
    } // if()
    else if (dire == Down) {
      c = c - 1 ;
      dire = Left;
      if (l == 0)
        ChangeDire(dire, l, c);
    } // else if()
    else if (dire == Left) {
      l = l + 1 ;
      dire = Up;
      if (c == 0)
        ChangeDire(dire, l, c);
    } // else if()
    else if (dire == Up) {
      c = c + 1 ;
      dire = Right;
      if (l == Mazecolumn - 1)
        ChangeDire(dire, l, c);
    } // else if()
  }   // ChangeDire()

  char returnBlock(int x, int y) {
    return theMaze[x][y];
  } // return the exact block

  Dire CheckAround(Dire dire, int l, int c, char ch) {
    if (dire == Right) {
      if (returnBlock(l, c + 1) == ch)
        return Down;
      else if (returnBlock(l - 1, c) == ch)
        return Left;
      else if (returnBlock(l, c - 1) == ch)
        return Up;
    } // if()

    else if (dire == Down) {
      if (returnBlock(l - 1, c) == ch)
        return Left;
      else if (returnBlock(l, c - 1) == ch)
        return Down;
      else if (returnBlock(l + 1, c) == ch)
        return Right;
    } // else if()

    else if (dire == Left) {
      if (returnBlock(l, c - 1) == ch)
        return Up;
      else if (returnBlock(l + 1, c) == ch)
        return Right;
      else if (returnBlock(l, c + 1) == ch)
        return Down;
    } // else if()

    else if (dire == Up) {
      if (returnBlock(l + 1, c) == ch)
        return Right;
      else if (returnBlock(l, c + 1) == ch)
        return Down;
      else if (returnBlock(l - 1, c) == ch)
        return Left;
    } // else if()

    else {
      if (returnBlock(l + 1, c) == ch)
        return Right;
      else if (returnBlock(l, c + 1) == ch)
        return Down;
      else if (returnBlock(l - 1, c) == ch)
        return Left;
      else if (returnBlock(l, c - 1) == ch)
        return Up;
    } // else
    return None;
  }

  void Walkback(doMaze copy, Dire dire, int l, int c) {
    if (dire == Right) {
      if (copy.returnBlock(l + 1, c) == 'V') {
        l = l + 1;
        Walkback(copy, dire, l, c);
      }
    } // if()
    else if (dire == Down) {
      if (copy.returnBlock(l, c + 1) == 'V') {
        c = c + 1;
        Walkback(copy, dire, l, c);
      }
    } // else if()
    else if (dire == Left) {
      if (copy.returnBlock(l - 1, c) == 'V') {
        l = l - 1;
        Walkback(copy, dire, l, c);
      }
    } // else if()
    else if (dire == Up) {
      if (copy.returnBlock(l, c - 1) == 'V') {
        c = c - 1;
        Walkback(copy, dire, l, c);
      }
    } // else if()
  }

  void returnMaze( doMaze copy, Dire &dire, int &l, int &c ) {
    int line = l ;
    int column = c ;
    if ( copy.returnBlock( l, c ) == 'V' ) 
      theMaze[l][c] = 'V' ;
    
    if ( l != 0 && c != 0 ) {
      if ( dire == Right ) 
        line++ ;
      else if ( dire == Down )
        column++ ;
      else if ( dire == Left )
        line-- ;
      else if ( dire == Up )
        column-- ;
      if ( copy.returnBlock( line, column ) == 'V' )
        returnMaze( copy, dire, line, column ) ;
      else {
        dire = CheckAround(dire, l, c, 'V' ) ;
        returnMaze( copy, dire, line, column ) ;
      } // else 
    } // if
  }

  void printMaze() {
    for (int j = 0; j < Mazecolumn; j++) {
      for (int i = 0; i < Mazeline; i++) {
        cout << returnBlock(i, j);
      } // for()
      cout << endl;
    } // for()
    cout << endl;
  }

private:
  int Mazeline;
  int Mazecolumn;
  char theMaze[42][42];
  Dire currentdire;
  int N;
  int Goalline, Goalcolumn;

}; // doMaze()

int main() {
  int command = 0;
  string filenumber;
  Mode mode = One;
  bool stop = false;
  bool success;
  doMaze aMaze;

  while (!stop) {
    cout << endl << "***Path Finding***";
    cout << endl << "*0.Quit          *";
    cout << endl << "*1.One goal      *";
    cout << endl << "*2.More goal     *";
    // cout << endl << "*3.Shortest path *";
    cout << endl << "******************";
    cout << endl << "Input a command(0,1,2):";
    cin >> command;
    if (command == 1 || command == 2) {
      if (command == 2) {
        mode = More;
      }
      cout << "Please input a file number :";
      cin >> filenumber;
      string filename = "input" + filenumber + ".txt";
      if (aMaze.Load(filename, mode)) {
        doMaze vMaze(aMaze);
        success = aMaze.findGoals(vMaze, mode);
        mode = One;
        vMaze.printMaze();
        if (success)
          aMaze.printMaze();
        vMaze.Clr();
      } // if load the maze succesfully
      aMaze.Clr();
    } else if (command == 0) {
      cout << endl << "System close..." << endl;
      stop = true;
    } else {
      cout << endl << "Command doesn't exist !" << endl;
    }
  } // while(!stop)
} // main()
