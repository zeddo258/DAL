/*********************
 學號 10924148
 姓名 陳黃揚
*********************/


#include <string.h> //字串
#include <fstream> // 讀入txt檔
#include <stdlib.h> //system pause
#include <stdio.h>
#include <iostream>

using namespace std;

class puzzle {
  private :
    ifstream in;
    string num;
    string file = "input" ;
    int row = 0, col = 0;
    int nRow = 0, nCol = 0;
    char map[99][99];
    bool isEnd = false;
    bool changeR = false;
    int numOfG = -1;
    int nowG = 0;


  public :
    bool inputMap();
    bool oneGoal();
    bool moreGoals();
    void printOne();
    void setRPath();
    void setGPath();
    void setNumOfG();
    bool test();
    int getNumOfG();
    void setEnd( bool );

};


  void puzzle::setEnd( bool i ) {
    isEnd = i;
    return;
  }

  int puzzle::getNumOfG() {
    return numOfG;
  }

  bool puzzle::inputMap() { // 讀地圖

    cout << "Input a file number: ";
    cin >> num;
    file.append( num ).append( ".txt" );
    in.open( file );

    if ( !in.is_open() ) {
      cout << endl << file << " does not exist! " << endl;
      return false;
    }

    in >> row;
    in >> col;
    // cout << row << "\n" << col << endl;

    for ( int i = 0 ; i < col ; i++ ) {
      for ( int j = 0 ; j < row ; j++ ) {
        in >> map[i][j];
      }
    }

    return true;
  }

  bool puzzle::oneGoal() { // 找一個目標時

    if ( map[nCol][nRow] == 'G' ) {
      isEnd = true;
      printOne();
      return isEnd;
    }
    else {
      map[nCol][nRow] = 'V';

      if ( ( map[nCol][nRow + 1] == 'E' || map[nCol][nRow + 1] == 'G' )
                 && ( nCol < col && nRow + 1 < row ) && !isEnd ) {
        nRow++;
        oneGoal();
        nRow--;

      }

      if ( ( map[nCol + 1][nRow] == 'E' || map[nCol + 1][nRow] == 'G' )
                 && ( nCol + 1 < col && nRow < row ) && !isEnd ) {

        nCol++;
        oneGoal();
        nCol--;
      }

      if ( ( map[nCol][nRow - 1] == 'E' || map[nCol][nRow - 1] == 'G' )
                  && ( nCol < col && nRow - 1 < row && nRow >= 0 ) && !isEnd ) {
        nRow--;
        oneGoal();
        nRow++;
      }

      if ( ( map[nCol - 1][nRow] == 'E' || map[nCol - 1][nRow] == 'G' )
                 && ( nCol - 1 < col && nCol >= 0 && nRow < row ) && !isEnd ) {

        nCol--;
        oneGoal();
        nCol++;
      }

    }

    if ( isEnd )
      map[nCol][nRow] = 'R';

    return isEnd;
  }

  void puzzle::setRPath() { // 只留下最短路徑，其他走過的路改回原本的狀態
    for ( int i = 0 ; i < col ; i++ ) {
      for ( int j = 0 ; j < row ; j++ ) {
          if ( map[i][j] == 'V' )
            map[i][j] = 'E';

      }
    }
  }

  void puzzle::setGPath() { // 把標記走過的目標改回原本的狀態
    for ( int i = 0 ; i < col ; i++ ) {
      for ( int j = 0 ; j < row ; j++ ) {

          if ( map[i][j] == 'A' )
            map[i][j] = 'G';
      }
    }
  }

  void puzzle::printOne() { // 印出地圖
    cout << endl;
    for ( int i = 0 ; i < col ; i++ ) {
      for ( int j = 0 ; j < row ; j++ ) {
        cout << map[i][j];
      }
      cout << endl;
    }
  }

  void puzzle::setNumOfG() { // 輸入要找到多少個目標
    cout << endl << "Number of G (goals): ";
    cin >> numOfG;
  }


  bool puzzle::moreGoals() { // 找多個目標時用，先處理走過的路徑部分

    if ( map[nCol][nRow] == 'G' ) {
      nowG++;
      map[nCol][nRow] = 'A'; // passed Goal


      if ( nowG == numOfG ) {
        isEnd = true;
        setGPath();

        printOne();
        return isEnd;
      }

      moreGoals();

    }
    else {

      if ( map[nCol][nRow] != 'A' )
        map[nCol][nRow] = 'V';

      if ( ( map[nCol][nRow + 1] == 'E' || map[nCol][nRow + 1] == 'G' )
                 && ( nCol < col && nRow + 1 < row ) && !isEnd ) {
        nRow++;
        moreGoals();
        nRow--;

      }

      if ( ( map[nCol + 1][nRow] == 'E' || map[nCol + 1][nRow] == 'G' )
                 && ( nCol + 1 < col && nRow < row ) && !isEnd ) {

        nCol++;
        moreGoals();
        nCol--;
      }

      if ( ( map[nCol][nRow - 1] == 'E' || map[nCol][nRow - 1] == 'G' )
                  && ( nCol < col && nRow - 1 < row && nRow >= 0 ) && !isEnd ) {
        nRow--;
        moreGoals();
        nRow++;
      }

      if ( ( map[nCol - 1][nRow] == 'E' || map[nCol - 1][nRow] == 'G' )
                 && ( nCol - 1 < col && nCol >= 0 && nRow < row ) && !isEnd ) {

        nCol--;
        moreGoals();
        nCol++;
      }

    }

    if ( isEnd && map[nCol][nRow] != 'G' )
      map[nCol][nRow] = 'R';

    return isEnd;



  }

  bool puzzle::test() { // 多個目標時，用來處理最短路徑

    if ( map[nCol][nRow] == 'G' ) {
      map[nCol][nRow] == 'A';
      isEnd = true;

      return isEnd;
    }
    else {
      map[nCol][nRow] = 'V';

      if ( ( map[nCol][nRow + 1] == 'E' || map[nCol][nRow + 1] == 'G'
             || map[nCol][nRow + 1] == 'R' || map[nCol][nRow + 1] == 'A' )
                 && ( nCol < col && nRow + 1 < row ) && !isEnd ) {
        nRow++;
        test();
        nRow--;

      }

      if ( ( map[nCol + 1][nRow] == 'E' || map[nCol + 1][nRow] == 'G'
             || map[nCol + 1][nRow] == 'R' || map[nCol + 1][nRow] == 'A'  )
                 && ( nCol + 1 < col && nRow < row ) && !isEnd ) {

        nCol++;
        test();
        nCol--;
      }

      if ( ( map[nCol][nRow - 1] == 'E' || map[nCol][nRow - 1] == 'G'
             || map[nCol][nRow - 1] == 'R' || map[nCol][nRow - 1] == 'A' )
                  && ( nCol < col && nRow - 1 < row && nRow >= 0 ) && !isEnd ) {
        nRow--;
        test();
        nRow++;
      }

      if ( ( map[nCol - 1][nRow] == 'E' || map[nCol - 1][nRow] == 'G'
              || map[nCol - 1][nRow] == 'R' || map[nCol - 1][nRow] == 'A' )
                 && ( nCol - 1 < col && nCol >= 0 && nRow < row ) && !isEnd ) {

        nCol--;
        test();
        nCol++;
      }

    }

    if ( isEnd && (  map[nCol][nRow] != 'G' &&  map[nCol][nRow] != 'A' ) )
      map[nCol][nRow] = 'R';

    return isEnd;



    return isEnd;
  }



int main() {


  int com = -1; // command
  while ( com != 0 ) {
    puzzle * p = new puzzle;
    com = -1;
    cout << endl;
    cout << "*** Path Finging ***" << endl;
    cout << "* 0. Quit          *" << endl;
    cout << "* 1. One goal      *" << endl;
    cout << "* 2. More goals    *" << endl;
    cout << "********************" << endl;
    cout << "Input a command(0, 1, 2):";
    cin >> com;
    cout << endl;

    if ( com == 0 ) {
      system( "pause" );
      return 0;
    }
    else if ( com == 1 ){
      if (  p -> inputMap() ) {
        if ( p -> oneGoal() ) // 若成功找到單一目標，就會印出最短路徑
          p -> setRPath();    // 否則只會印出所有走過的路徑
        p -> printOne();
      }
    }
    else if ( com == 2 ) {
      if( p -> inputMap() ) {
        p -> setNumOfG();

        if ( p -> moreGoals() ) // 先印出所有路徑
          p -> setRPath();


        for ( int i = 0 ; i < p -> getNumOfG() ; i++ ) { // 分開找出每個目標的最短路徑
          p -> setEnd( false );                          // 並將地圖印出
          if ( p -> test() ) {                           // 若找不到足夠的目標
                                                         // 則只印出所有路徑
            p -> setRPath();

          }
          else
            p -> setGPath();
        }

        p -> printOne();
      }
    }
    else
      cout << "Command does not exist!" << endl;

    delete p;

  }

  return 0;
}
