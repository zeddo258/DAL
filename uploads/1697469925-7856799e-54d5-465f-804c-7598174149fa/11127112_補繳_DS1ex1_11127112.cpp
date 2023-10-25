// 11127112 莊沛儒
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

class Maze{

  private :
      int length, wideth;
      int shortestpath = 0;
      int temppathlength = 0;
      vector<int> backpointx ;
      vector<int> backpointy ;
      int direction = 0; // 0:turn right, 1:turn dowm, 2:turn left, 3: turn up
      vector<vector<char>> maze ; //initialize the vector of map
      vector<int> prsitex; // memorize x
      vector<int> prsitey; // memorize y
      vector<int> gsitex; // used to memory the place of x that g was visited
      vector<int> gsitey;// used to memory the place of y that g was visited
      vector<int> pathfindgx; // used to sort whether the point is on the way to 'G'
      vector<int> pathfindgy;
      vector<vector<int>> turntime ;
      bool havefound = false; // check the goal

  public:
      vector<vector<char>> vmaze ; //set the vector of visited map
      vector<vector<char>> rmaze; //set the vector of route map

  public :bool load( string name ){
    fstream inputmatrix; // use to read in txt.
    direction = 0; // initialize direction
    shortestpath = 0;
    havefound = false; // initialize havefound
    prsitex.clear(),prsitey.clear(),gsitex.clear(),gsitey.clear(); // initial all vector
    pathfindgx.clear(),pathfindgy.clear(),backpointx.clear(),backpointy.clear(),turntime.clear();// initial all vector
    inputmatrix.open(name); // open the txt.
    if( inputmatrix.is_open() ) { // check whether the file is exist or not
        inputmatrix >> wideth >> length; // read in the wideth and length of matrix
        maze.resize(length); // initialize the length of matrix
        vmaze.resize(length); // initialize the length of visited map
        rmaze.resize(length); // initialize the length of route map
        turntime.resize(length);
        for ( int i = 0 ; i < length; i++ ){
            maze[i].resize(wideth);// initialize the wideth of matrix
            vmaze[i].resize(wideth);// initialize the wideth of visited map
            rmaze[i].resize(wideth);// initialize the wideth of route map
            turntime[i].resize(wideth);
        }

        for ( int i = 0 ; i < length ; i++ ){
            for ( int j = 0 ; j < wideth ; j++ ){
                inputmatrix >> maze[i][j]; // read in every character of matrix
                vmaze[i][j] = maze[i][j]; // let visit map and route map be the same with matrix
                rmaze[i][j] = maze[i][j];
                turntime[i][j] = 0 ;

            }
        }
        inputmatrix.close(); // close the file
        return true;
    }
    else{
        cout << name << " doesn't exist!"; // if thr file can't open
        return false;
    }
  }

  public : void Printvmaze(){
      for( int i = 0 ; i < gsitex.size() ; i++ ){
        vmaze[gsitex[i]][gsitey[i]] = 'G';
      } // turn visited 'V' into 'G' if it origional is 'G'
      for ( int i = 0 ; i < length ; i++ ){
        for ( int j = 0 ; j < wideth; j++ ){
            cout << vmaze[i][j];
        }
        cout << endl;
    }
  } // Printvmaze() used to show the whole visited map

  public : void Printrmaze(){
      for( int i = 0 ; i < gsitex.size() ; i++ ){
        rmaze[gsitex[i]][gsitey[i]] = 'G';
      }
      for ( int i = 0 ; i < length ; i++ ){
        for ( int j = 0 ; j < wideth; j++ ){
            cout << rmaze[i][j];
        }
        cout << endl;
    }
  }//Printvrmaze() used to show the route of route map


    bool CanGo( int &x, int &y ){
      bool cango = false; // initialize the boolen value

      if( direction % 4 == 0 && y+1 < wideth && ( vmaze[x][y+1] == 'E' || vmaze[x][y+1] == 'G')  ) { // turn right
          cango = true;
          prsitex.push_back(x);
          prsitey.push_back(y);
          y+=1;

      }
      else if ( direction % 4 == 1 &&  x+1 < length  && ( vmaze[x+1][y] == 'E' || vmaze[x+1][y] == 'G') ){ // turn down
          cango = true;
          prsitex.push_back(x);
          prsitey.push_back(y);
          x+=1;
      }
      else if ( direction % 4 == 2 && y-1 >= 0 && ( vmaze[x][y-1] == 'E' || vmaze[x][y-1] == 'G')  ){ // turn left
          cango = true;
          prsitex.push_back(x);
          prsitey.push_back(y);
          y-=1;
      }
      else if ( direction % 4 == 3  && x-1 >= 0 && ( vmaze[x-1][y] == 'E' || vmaze[x-1][y] == 'G') ) { // turn down
         cango = true;
         prsitex.push_back(x);
          prsitey.push_back(y);
         x-=1;
      }
      else // turn way
      {
          cango = false;
      }
      return cango;
  }


  public: bool FindGoals( int x, int y, int & mode, int N ) {
      int turntimes = 0;
      bool temp = false;
      bool temp1 = false;
      bool ontheway = false;
      if ( vmaze[x][y] == 'G' && mode+1 == N ) {
        shortestpath += 1;
        for( int i = 0 ; i < prsitex.size() ; i++ ){
            pathfindgx.push_back( prsitex[i]);
            pathfindgy.push_back( prsitey[i]);
        }
        havefound = true;
      }
      else{

        if( vmaze[x][y] == 'G' ){
            mode+=1;
            rmaze[x][y] = 'G';
            gsitex.push_back(x), gsitey.push_back(y); // to sort the x place and y place of 'G'

            for( int i = 0 ; i < prsitex.size() ; i++ ){
                pathfindgx.push_back( prsitex[i]);
                pathfindgy.push_back( prsitey[i]);
            } // sort all the path that on the wat to 'G';
        }
        vmaze[x][y] = 'V', rmaze[x][y] = 'R';
        shortestpath += 1;
        if( CanGo(x,y) ) {
            turntimes = 0;
            FindGoals(x,y,mode,N); // if can go next point, do the recursion
        }
        else{
            if( turntimes < 4){
                for( int i = 0 ; i < 4 ; i++ ){
                    if( CanGo(x,y) != true ) {
                        direction += 1;
                        turntimes += 1;
                        turntime[x][y] = turntimes;
                    } // check four ways to make sure is there any place can go
                    else
                    {
                        temp = true;
                        break;
                    }

                }

                if ( temp == true ){
                  FindGoals(x,y,mode,N);
                }
                else{
                    direction = 0;
                    turntimes = 0;
                    for( int i = 0 ; i < pathfindgx.size(); i++ ){
                        if( x == pathfindgx[i] && y == pathfindgy[i] ){
                            ontheway = true;
                            break;
                        }
                    }
                    if( ontheway != true )
                        rmaze[x][y] = 'E';
                    if( prsitex.back() == 0 && prsitey.back() == 0 ){
                        havefound = false;
                    } // check the point is zero zero or not
                    else{
                        x = prsitex.back();// turn x into previous x point
                        y = prsitey.back();// turn y into previous y point
                        prsitex.pop_back();// delete last x point was be sorted
                        prsitey.pop_back();// delete last y point was be sorted
                        shortestpath -= 1;
                        FindGoals(x,y,mode,N);

                    } // return to the previous point and do recursive

                }

            }
        }


      }
      return havefound;
  }
  bool OnRoad( int x, int y ){
    bool cango = true;
    for(int i = 0 ; i < backpointx.size();i++){
            if( x == backpointx[i] && y == backpointy[i] ){
                cango = false;
            }
    }
    for(int i = 0 ; i < prsitex.size() ;i++){
        if( x == prsitex[i]&& y == prsitey[i]){
            cango = false;
            break;
        }
    }
    return cango;
  }
  public: void FindGoals2( int x, int y) {
    bool temp = false;
    int turntimes = 0;
    if(x == 0 && y == 0 ){
        return ;
    }
    else{
        if( vmaze[x][y] == 'G' && temppathlength < shortestpath -1 ){
            shortestpath = temppathlength;
            pathfindgx.clear();
            pathfindgy.clear();
            for( int i = 0 ; i < prsitex.size() ; i++ ){
                pathfindgx.push_back(prsitex[i]);
                pathfindgy.push_back(prsitey[i]);
            }
        }
        if( vmaze[x][y] != 'G')
          vmaze[x][y] = 'V';
        if(temppathlength >= shortestpath -1 ){
          if( vmaze[x][y] != 'G')
            rmaze[x][y] = 'E';
          backpointx.push_back(x) ;
          backpointy.push_back(y) ;
          x = prsitex.back();
          y = prsitey.back();
          prsitex.pop_back();
          prsitey.pop_back();
          temppathlength -= 1;
          FindGoals2(x,y);
        }
        else{
            if( CanGo2(x,y) ){
                temppathlength += 1;
                FindGoals2(x,y);
            }
            else{
                if(turntime[x][y] < 4 ){
                    for( int i = 0 ; i < 4-turntime[x][y] ; i++ ){
                        if( !CanGo2(x,y) ){
                            direction += 1;
                            turntimes += 1;
                        }
                        else{
                            temp = true;
                            break;
                        }
                    }
                    if( temp == true ){
                        turntime[x][y] += turntimes;
                        temppathlength+=1;
                        FindGoals2(x,y);
                    }
                    else{
                        turntime[x][y] = 0;
                        rmaze[x][y] = 'E';
                        backpointx.push_back(x);
                        backpointy.push_back(y);
                        x = prsitex.back();
                        y = prsitey.back();
                        prsitex.pop_back();
                        prsitey.pop_back();
                        temppathlength -= 1;
                        FindGoals2(x,y);
                    }
                }
            }
        }
    }
  }
  bool CanGo2( int &x, int &y ){
      bool cango = false; // initialize the boolen value
      if(x == 0 && y == 1 && backpointx.size() > 2 ){
        backpointx.erase(backpointx.begin());
        backpointy.erase(backpointy.begin());
      }
      if( direction % 4 == 0 && y+1 < wideth && vmaze[x][y+1] != 'O' && OnRoad(x,y+1) != false) { // turn right
          cango = true;
          prsitex.push_back(x);
          prsitey.push_back(y);
          y+=1;

      }
      else if ( direction % 4 == 1 &&  x+1 < length  && vmaze[x+1][y] != 'O' && OnRoad(x+1,y) != false){ // turn down
          cango = true;
          prsitex.push_back(x);
          prsitey.push_back(y);
          x+=1;
      }
      else if ( direction % 4 == 2 && y-1 >= 0 && vmaze[x][y-1] != 'O' && OnRoad(x,y-1) != false ){ // turn left
          cango = true;
          prsitex.push_back(x);
          prsitey.push_back(y);
          y-=1;
      }
      else if ( direction % 4 == 3  && x-1 >= 0 && vmaze[x-1][y] != 'O' && OnRoad(x-1,y) != false) { // turn down
         cango = true;
         prsitex.push_back(x);
          prsitey.push_back(y);
         x-=1;
      }
      else // turn way
      {
          cango = false;
      }
      return cango;
  }
  public: bool Findshortestpath(int x,int y, int & shortpath ){
      int mode = 0;
      if ( FindGoals(x,y,mode,1) ){
          temppathlength = shortestpath ;
          x = prsitex.back();
          y = prsitey.back();
          prsitex.pop_back();
          prsitey.pop_back();
          temppathlength -= 1;
          FindGoals2(x,y);

          shortpath = shortestpath;

          for( int i = 0 ; i < pathfindgx.size() ; i++ ){
            rmaze[pathfindgx[i]][pathfindgy[i]] = 'R';
          }

          return true;

      }
      else
        return false;
  }




};

bool isDigit( string num, int & mode ){
    int length1  = num.length();
    bool digit = true;
    for( int i = 0 ; i < length1 ; i++ ){
        if( (int) num[i] >= 48 && (int) num[i] <= 57){
            digit = true;
        }
        else{
            digit = false;
            break;
        }
    }
    if( digit == true ){
        mode = stoi(num);
    }
    return digit;
} // isDigit() use to check the sting input is Digit or not

int main(){
  int command = 0; // initialize command
  int mode = 1; // how many goals to find
  int x = 0,y = 0, nowgoal = 0;
  int shortpath = 1000;
  string fileName = "input";
  string temp;
  string num ;
  bool isinterger = true;
  Maze aMaze;

  do {
    nowgoal = 0;
    x = 0 , y = 0 ;
    shortpath = 100;
    fileName = "input";
    cout << endl << "***Path Finding*******";
    cout << endl << "*0.Quit              *";
    cout << endl << "*1.One goal          *";
    cout << endl << "*2.More goal         *";
    cout << endl << "*3.Find shortest path*";
    cout << endl << "**********************";
    cout << endl << "Inpur a command(0,1,2,3):";
    cin >> command; // get the command
    cout << endl;
    if (( command == 1 ) || ( command == 2) || (command == 3))
    {
        cout << "Input a file number:";
        cin >> temp;
        cout << endl;
        fileName = fileName + temp + ".txt";

        if( aMaze.load(fileName) ) {
            if (command == 2 ){ // mission 2
                cout << "Number of G (goals):";
                cin >> num;
                if( isDigit(num,mode) == true) { // check the string is Digit or not
                    if( aMaze.FindGoals(x,y,nowgoal,mode) ) {
                        aMaze.Printvmaze();
                        cout << endl;
                        aMaze.Printrmaze();
                    }
                    else{
                        cout << endl;
                        aMaze.Printvmaze();
                    }
                }
                else{
                    cout << endl << "Number of G (goals):" ;
                    cin >> num;
                    while( isDigit(num,mode) != true ){ // repeat to key in the string until it's digit
                        cout << "Number of G (goals):" ;
                        cin >> num;
                        cout << endl;
                    }
                    if( aMaze.FindGoals(x,y,nowgoal,mode) ) {
                        aMaze.Printvmaze();
                        cout << endl;
                        aMaze.Printrmaze();
                    }
                    else{
                        cout << endl;
                        aMaze.Printvmaze();
                    }


                }
            }
            else if( command == 1 ) { // mission 1
                nowgoal = 0;
                mode = 1;
                if( aMaze.FindGoals(x,y,nowgoal,mode) ) {
                    aMaze.Printvmaze();
                    cout << endl;
                    aMaze.Printrmaze();
                }
                else{
                    aMaze.Printvmaze();
                }
            }
            else if ( command == 3 ){
                nowgoal = 0;
                mode = 1;
                if( aMaze.Findshortestpath(x,y,shortpath ) ) {
                    aMaze.Printvmaze();
                    cout << endl;
                    aMaze.Printrmaze();
                    cout << endl;
                    cout << "Shortest path length = " << shortpath <<endl;
                }
                else{
                    cout << endl;
                    aMaze.Printvmaze();
                }

            }

        }
    }
    else if ( command == 0 ) // break the loop
        break;
    else
        cout << "Command does not exist!"<< endl;
  } while(true);
}


