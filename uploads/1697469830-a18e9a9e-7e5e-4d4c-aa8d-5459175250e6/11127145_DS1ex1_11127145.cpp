// 11127145 陳采妮
# include <fstream>
# include <stdio.h>
# include <iostream>
# include <string.h>
using namespace std;
int  column, row = 0 ;
int rowIndex, columnIndex = 0 ;

class Maze {
public :
    char** seat ;
    char** dir ;
    int n = 0;
    char** GetMaze(char fileName[30]);
    char** TakeNote( );
    bool MeetG( char **seat, char **dir);
    bool BeAware(char **seat, char **dir);
    bool BackBack(char **seat, char **dir);
    bool Right(char **seat, char **dir);
    bool Left(char **seat, char **dir);
    bool Down(char **seat, char **dir);
    bool Up(char **seat, char **dir);
    int CanTurnRight( char **seat, char **dir );
    int CanTurnLeft( char **seat, char **dir );
    int CanTurnUp( char **seat, char **dir );
    int CanTurnDown( char **seat, char **dir );
    void PrintMaze(char **seat ) ;
    void DoneMaze(char **seat);

};

char** Maze::GetMaze(char fileName[30] ){  // input maze
  ifstream in;
  ifstream out;
  char title[30] ;
  rowIndex=0, columnIndex = 0;
  column=0, row = 0 ;
  strcpy(title,"input" );
  strcat(title, fileName);
  strcat(title,".txt" );


  ifstream inputfile(title) ;
  inputfile >> row >> column ;
  char** seat = new char*[row];
  for ( int d = 0; d <= row - 1; d ++ )
    seat[d] = new char[column] ;
  
  for( int i = 0; i <= column - 1; i ++ ){  
    for( int j = 0; j <= row - 1; j ++ )
      inputfile >> seat [j][i]  ;
  }
  return seat ;
}

char** Maze::TakeNote( ){        // return a array to record the direction of every step 
  char** dir = new char*[row];
  for ( int d = 0; d <= row - 1; d ++ )
    dir[d] = new char[column] ;
  dir[0][0] = '0';
  return dir;
}

bool Maze::MeetG( char **seat, char **dir){ 
  if(seat[rowIndex][columnIndex]!= 'F'&& seat[rowIndex][columnIndex]!= 'D'&& seat[rowIndex][columnIndex]!= 'G')  // 這一條是找到G的路徑，所以要特別做記號
    seat[rowIndex][columnIndex]= 'V' ;
  if (CanTurnRight( seat, dir) == 2 || CanTurnDown( seat, dir) == 2 || CanTurnLeft( seat, dir) == 2 
            || CanTurnUp( seat, dir) == 2 ){  // 找到G
    return true;
  }
  else if (CanTurnRight( seat, dir) == 1){   // 可以繼續向右
    rowIndex = rowIndex + 1 ; 
    Right(seat, dir);
  }
  else if (CanTurnDown( seat, dir) == 1){  // 可以向下
    columnIndex = columnIndex + 1;
    Down(seat, dir);
  }
  else if (CanTurnLeft( seat, dir) == 1){  // 可以向左
    rowIndex = rowIndex - 1 ; 
    Left(seat, dir);
  }
  else if (CanTurnUp( seat, dir) == 1){    // 可以向上
    columnIndex = columnIndex - 1;
    Up(seat, dir);
  }
  else {                                     // 往回
    if (dir[rowIndex][columnIndex]== '1'){
      rowIndex = rowIndex - 1 ; 
      MeetG(seat, dir);
    }
    else if (dir[rowIndex][columnIndex]== '2'){
      columnIndex = columnIndex -1;
      MeetG(seat, dir);
    }
    else if (dir[rowIndex][columnIndex]== '3'){
      rowIndex = rowIndex + 1 ; 
      MeetG(seat, dir);
    }
    else if (dir[rowIndex][columnIndex]== '4'){
      columnIndex = columnIndex +1;
      MeetG(seat, dir);

    }
    else
      return false;

  }
  return true;
}

bool Maze::BeAware(char **seat, char **dir){         // 判斷當前位置是否為走到G前的最後一步
  int num = 0 ;                                      // 如果是的話就走MeetG()這條function下去遞迴，這樣才能保留路徑
    if ( columnIndex+1 < column&& num == 0){
      if ( seat[rowIndex][columnIndex+1]== 'F' && dir[rowIndex][columnIndex+1] =='2' ) {// 下面是F
        MeetG(seat, dir);
        num = 1 ;
      }
    }
    if ( columnIndex-1 >=0&& num == 0){
      if ( seat[rowIndex][columnIndex-1]== 'F' && dir[rowIndex][columnIndex-1] =='4'){ // 上面是F
        MeetG(seat, dir);
        num = 1 ;
      }
    }
    if (rowIndex-1 >=0&& num == 0){
      if ( seat[rowIndex-1][columnIndex]== 'F' &&dir[rowIndex-1][columnIndex] =='3' ) {// 左邊是F
        MeetG(seat, dir);
        num = 1 ;
      }
    }
    if (rowIndex+1 < row&& num == 0){
      if ( seat[rowIndex+1][columnIndex]== 'F' && dir[rowIndex+1][columnIndex] =='1' ){ // 右邊是F
        MeetG(seat, dir);
        num = 1 ;
      }
    }
    if (num == 1 )
      return true;
    else 
      return false;
}
bool Maze::BackBack(char **seat, char **dir){   // 如果確定都沒路，呼叫BackBack()這個function走回去
  if (dir[rowIndex][columnIndex]== '1'){        // 左邊來的，向左回去
    if (seat[rowIndex][columnIndex]!= 'F')
      seat[rowIndex][columnIndex]= 'D' ;
    rowIndex = rowIndex - 1 ; 
    Left(seat, dir);
  }
  else if (dir[rowIndex][columnIndex]== '2'){   // 上面來的，向上回去
    if (seat[rowIndex][columnIndex]!= 'F')
      seat[rowIndex][columnIndex]= 'D' ;
    columnIndex = columnIndex -1;
    Up(seat, dir);
  }
  else if (dir[rowIndex][columnIndex]== '3'){    // 右邊來的，向右回去
    if (seat[rowIndex][columnIndex]!= 'F')
      seat[rowIndex][columnIndex]= 'D' ;
    rowIndex = rowIndex + 1 ; 
    Right(seat, dir);
  }
  else if (dir[rowIndex][columnIndex]== '4'){   // 下面來的，向下回去
    if (seat[rowIndex][columnIndex]!= 'F')
      seat[rowIndex][columnIndex]= 'D' ;
    columnIndex = columnIndex +1;
    Down(seat, dir);
  }
  else 
    return false;
  return true;
}

bool Maze::Right(char **seat, char **dir){           // 向右轉
  if(seat[rowIndex][columnIndex]!= 'F'&& seat[rowIndex][columnIndex]!= 'D'&& seat[rowIndex][columnIndex]!= 'G')
    seat[rowIndex][columnIndex]= 'V' ;
  if (CanTurnRight( seat, dir) == 2 || CanTurnDown( seat, dir) == 2 || CanTurnLeft( seat, dir) == 2 
            || CanTurnUp( seat, dir) == 2 ){  // 找到G
    return true;
  }
  else if (CanTurnRight( seat, dir) == 1){   // 可以繼續向右
    rowIndex = rowIndex + 1 ; 
    Right(seat, dir);
  }
  else if (CanTurnDown( seat, dir) == 1){  // 可以向下
    columnIndex = columnIndex + 1;
    Down(seat, dir);
  }
  else if (CanTurnLeft( seat, dir) == 1){  // 可以向左
    rowIndex = rowIndex - 1 ; 
    Left(seat, dir);
  }
  else if (CanTurnUp( seat, dir) == 1){    // 可以向上
    columnIndex = columnIndex - 1;
    Up(seat, dir);
  }
  else {                                     // 往回
    if (BeAware(seat, dir)== false) {
      if (BackBack(seat, dir)== true) 
        return true ;
      else
        return false;
    }
    else
      return true;
  }


  
  return true ;

}

bool Maze::Down( char **seat, char **dir ){       // 向下轉
  if(seat[rowIndex][columnIndex]!= 'F'&& seat[rowIndex][columnIndex]!= 'D'&& seat[rowIndex][columnIndex]!= 'G')
    seat[rowIndex][columnIndex]= 'V' ;
  if (CanTurnRight( seat, dir) == 2 || CanTurnDown( seat, dir) == 2 || CanTurnLeft( seat, dir) == 2 
            || CanTurnUp( seat, dir) == 2 ){  // 找到G
    return true;
  }
  else if (CanTurnDown( seat, dir) == 1){    // 可以繼續向下
    columnIndex = columnIndex + 1;
    Down(seat, dir);
  }
  else if (CanTurnLeft( seat, dir) == 1){   // 可以向左
    rowIndex = rowIndex - 1;
    Left(seat, dir);
  }
  else if (CanTurnUp( seat, dir) == 1){     // 可以向上
    columnIndex = columnIndex - 1;
    Up(seat, dir);
  }
  else if (CanTurnRight( seat, dir) == 1){  // 可以向右
    rowIndex = rowIndex + 1;
    Right(seat, dir);
  }
  else {                                     // 往回
    if (BeAware(seat, dir)== false) {
      if (BackBack(seat, dir)== true) 
        return true ;
      else
        return false;
    }
    else
      return true;
  }
  
  return true ;
}

bool Maze::Left( char **seat, char **dir ){          // 向左轉
  if(seat[rowIndex][columnIndex]!= 'F'&& seat[rowIndex][columnIndex]!= 'D'&& seat[rowIndex][columnIndex]!= 'G')
    seat[rowIndex][columnIndex]= 'V' ;
  if (CanTurnRight( seat, dir) == 2 || CanTurnDown( seat, dir) == 2 || CanTurnLeft( seat, dir) == 2 
            || CanTurnUp( seat, dir) == 2 ){  // 找到G
    return true;
  }
  else if (CanTurnLeft( seat, dir) == 1){     // 可以向左
    rowIndex = rowIndex - 1;
    Left(seat, dir);
  }
  else if (CanTurnUp( seat, dir) == 1){      // 可以向上
    columnIndex = columnIndex - 1;
    Up(seat, dir);
  }
  else if (CanTurnRight( seat, dir) == 1){    // 可以向右
    rowIndex = rowIndex + 1;
    Right(seat, dir);
  }
  else if (CanTurnDown( seat, dir) == 1){    // 可以向下
    columnIndex = columnIndex + 1;
    Down(seat, dir);
  }

  else {                                     // 往回
    if (BeAware(seat, dir)== false) {
      if (BackBack(seat, dir)== true) 
        return true ;
      else
        return false;
    }
    else
      return true;
  }


  
  return true ;
}

bool Maze::Up( char **seat, char **dir ){            // 向上轉
  if(seat[rowIndex][columnIndex]!= 'F'&& seat[rowIndex][columnIndex]!= 'D'&& seat[rowIndex][columnIndex]!= 'G')
    seat[rowIndex][columnIndex]= 'V' ;
  if (CanTurnRight( seat, dir) == 2 || CanTurnDown( seat, dir) == 2 || CanTurnLeft( seat, dir) == 2 
            || CanTurnUp( seat, dir) == 2 ){  // 找到G
    return true;
  }
  else if (CanTurnUp( seat, dir) == 1){      // 可以繼續向上
    columnIndex = columnIndex - 1;
    Up(seat, dir);
  }
  else if (CanTurnRight( seat, dir) == 1){   // 可以向右
    rowIndex = rowIndex + 1;
    Right(seat, dir);
  }
  else if (CanTurnDown( seat, dir) == 1){    // 可以向下
    columnIndex = columnIndex + 1;
    Down(seat, dir);
  }
  else if (CanTurnLeft( seat, dir) == 1){    // 可以向左
    rowIndex = rowIndex - 1;
    Left(seat, dir);
  }
  else {                                     // 往回
    if (BeAware(seat, dir)== false) {
      if (BackBack(seat, dir)== true) 
        return true ;
      else
        return false;
    }
    else
      return true;
  }

  
  return true ;
}

int Maze::CanTurnRight( char **seat, char **dir ){
  if (rowIndex + 1 < row ){
    if (seat[rowIndex+1][columnIndex] == 'E' ){       // 檢查向右是否能走
      dir[rowIndex+1][columnIndex]= '1';
      return 1 ;
    }
    else if (seat[rowIndex+1][columnIndex] == 'G'){   // 檢查向右是否能碰到G
      seat[rowIndex+1][columnIndex] = 'F';
      dir[rowIndex+1][columnIndex]= '1';
      rowIndex = rowIndex+1;
      return 2 ;
    }


  }
  return 3 ;
}

int Maze::CanTurnDown( char **seat, char **dir ){
  if (columnIndex + 1 < column ){
    if (seat[rowIndex][columnIndex+1] == 'E'){     // 檢查向下是否能走
      dir[rowIndex][columnIndex+1]= '2';
      return 1 ;
    }
    
    else if (seat[rowIndex][columnIndex+1] == 'G'){   // 檢查向下是否能碰到G
      seat[rowIndex][columnIndex+1] = 'F';
      dir[rowIndex][columnIndex+1]= '2';
      columnIndex = columnIndex+1;
      return 2 ;
    }

    
  }
  return 3 ;
}

int Maze::CanTurnLeft( char **seat, char **dir ){
  if (rowIndex - 1 >= 0 ){
    if (seat[rowIndex-1][columnIndex] == 'E'){     // 檢查向左是否能走
      dir[rowIndex-1][columnIndex]= '3';
      return 1 ;
    }
      
    
    else if (seat[rowIndex-1][columnIndex] == 'G'){   // 檢查向左是否能碰到G
      seat[rowIndex-1][columnIndex] ='F';
      dir[rowIndex-1][columnIndex]= '3';
      rowIndex = rowIndex-1;
      return 2 ;
    }

  }
  return 3 ;
}

int Maze::CanTurnUp( char **seat, char **dir ){
  if (columnIndex - 1 >= 0 ){
    if (seat[rowIndex][columnIndex-1] == 'E'){     // 檢查向上是否能走
      dir[rowIndex][columnIndex-1]= '4';
      return 1 ;
    }

    else if (seat[rowIndex][columnIndex-1] == 'G'){   // 檢查向上是否能碰到G
      seat[rowIndex][columnIndex-1] ='F';
      dir[rowIndex][columnIndex-1]= '4';
      columnIndex= columnIndex-1;
      return 2 ;
    }

  }
  return 3 ;
}


void Maze::PrintMaze(char **seat){
  for( int k = 0; k <= column - 1; k ++ ){  // print maze
    for( int l = 0; l <= row - 1; l ++ )
      if ( seat [l][k] == 'F')          // F代表走過的G
        cout << 'G';
      else if ( seat [l][k] == 'D')     // D代表走錯的路徑
        cout << 'V';
      else 
        cout << seat [l][k] ;
    
    cout << endl ;
  }
}

void Maze::DoneMaze(char **seat){
  cout << endl ;
  for( int k = 0; k <= column - 1; k ++ ){  // print maze if success
    for( int l = 0; l <= row - 1; l ++ ){
      if ( seat [l][k]== 'V')
        cout << "R" ;
      else if ( seat [l][k] == 'F')   // F代表走過的G
        cout << 'G';
      else if ( seat [l][k] == 'D')   // D代表走錯的路徑
        cout << 'E';
      else 
        cout << seat [l][k] ;
      
    }
    cout << endl ;
  
  }
}

int main() {
  int command = 0 ;
  do{
    Maze maze1  ;
    char fileName[30] ;
    int n = 1 ;
    cout << endl<< "*** Path Finding ***";
    cout << endl << "* 0. Quit          *" ;
    cout << endl << "* 1. One Goal      *";
    cout << endl << "* 2. More Goal     *";
    cout << endl << "********************";
    cout << endl << "Input a command(0, 1, 2): ";
    cin >> command ;
    if (command == 1 || command == 2){
      if ( command == 2 ){
        cout << endl << "Input a positive number (e.g., 1, 2, ...): ";
        cin >> n ;
        maze1.n = n;
      }
      cout << endl << "Input a file number (e.g., 201, 202, ...): ";
      cin >> fileName ;
      maze1.seat= maze1.GetMaze(fileName);
      maze1.dir= maze1.TakeNote();
      int result = maze1.Right(maze1.seat, maze1.dir);
      while ( maze1.n > 1){
        maze1.MeetG(maze1.seat, maze1.dir) ;
        maze1.n = maze1.n - 1 ;
      
      }

      if(result == 1){
        maze1.PrintMaze(maze1.seat);
        maze1.DoneMaze(maze1.seat) ;
      }
      
      else 
        maze1.PrintMaze(maze1.seat);
    }
    else if (!command)
      break;
    else 
      cout << endl << "Command does not exist!" << endl;
  }  while (true);

  system("pause");
  return 0;
}

