// 11127220 ³¢¤d»² 
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <iostream>
# include <vector>
# include <fstream>  // read file

using namespace std ;

enum Modes {
    oneG, moreG
};

class Maze {
    public :
    vector<string> mazeV ;
    vector<string> mazeR ;
    int dx[4] = { 0, 1, 0, -1 } ;
    int dy[4] = { 1, 0, -1, 0 } ;
    int size ;
    int shortestPath = 0 ;
    
    bool islegal(int x, int y) {
        return x >= 0 && x < mazeV.size() && y >= 0 && y < mazeV[x].size() && mazeV[x][y] != 'O' ;
    } // islegal()
    
    bool load ( string fileNum, Modes mode ) {
        string line ;
        string fullFileName = "input" + fileNum + ".txt" ;
        char fileName[500] ;
        strcpy( fileName, fullFileName.c_str() ) ;
        ifstream file( fileName ) ;
        if ( !file.is_open() ) {
            cout << endl << fileName << " does not exist!" << endl ;
            return false ;
        } // if
        
        while ( getline ( file, line ) ) 
            mazeV.push_back( line ) ;
        mazeV.erase( mazeV.begin() ) ;  
        size = mazeV.size() ;      
    } // load() 
    
    void show() {
        for ( int i = 0 ; i < size ; i = i + 1 )
            cout << mazeV.at(i) << endl ;
        cout << endl ;
    } // show()

    bool findGoals( int x, int y, int direction ) {
        int newX, newY ;
        if ( mazeV[x][y] == 'G') // find goal
            return true;
    
        mazeV[x][y] = 'V' ;
    
        for ( int i = 0 ; i < 4 ; i++ ) {
            newX = x + dx[direction] ;
            newY = y + dy[direction] ;        
            if ( islegal(newX, newY) ) {
                mazeV.push_back({newX, newY}) ;
                if ( findGoals( newX, newY, direction ) )
                    return true; // find goals retuen true
                mazeV.pop_back(); // doesn't find goals -> pop back
            } // if 
            else 
                direction = (direction + 1) % 4 ; // turn
        } // for
        return false; // doesn't find the goal
    } // findGoals
    
    bool getR() {
        for ( int j = 0 ; j < size ; j = j + 1 ) {
            for ( int k = 0 ; k < mazeV[j].size() ; k = k + 1 ) {
                if ( mazeV[j][k] == 'V' ) {
                    mazeV[j][k] = 'R' ;
                    shortestPath = shortestPath + 1 ;
                }
            }
        }
    } // getR
    
    void cir() {
        mazeV.clear() ; 
    } // cir() 
    
    void shortest() {
        cout << "Shortest path length " << shortestPath + 1 << endl ;
    }
};

int main(void)
{   int command = 0 ;  // user command

    do
    {   Maze aMaze ;  // a matrix
        string fileName ;  // a file name
        Modes mode = oneG ;  // default: one goal
        
        cout << endl << "***Path Finding***" ;
        cout << endl << "* 0. Quit        *" ;
        cout << endl << "* 1. One goal    *" ;
        cout << endl << "* 2. More goals  *" ;
        cout << endl << "******************" ;
        cout << endl << "Input a command(0, 1, 2):" ;
        cin >> command ;  // get the command
        if ( ( command == 1 ) || ( command == 2 ) )
        {   if ( command == 2 )
                mode = moreG ;  // one or more goals
            cout << endl << "Input a file number(e.g., 201, 202, ...):" ;
            cin >> fileName ;
            if ( aMaze.load( fileName, mode ) )  // load the original matrix
            {   Maze vMaze = aMaze ;  // a copy to keep the visited cells
                bool success = aMaze.findGoals( 0, 0, 1 ) ;  // find a path to goal(s)
                mode = oneG ;  // reset to default
                aMaze.show() ;  // show on screen the visited cells
                if ( success ) {  // to cheak if the goal is reached or not
                    aMaze.getR() ;  // show on screen the route to reach the goal
                    aMaze.show() ;
                    aMaze.shortest() ;
                } // if
                vMaze.cir() ;  // clear up the copy
            } // end inner-if
            aMaze.cir() ;  // clear up the original matrix
        } // end outer-if
        else if ( !command )  // '0': stop the program
            break ;
        else
            cout << endl << "Command does not exist!" << endl ;
    } while ( true ) ;
    system( "pause" ) ;  // pause the execution
    return 0 ;
} // end of main
