// 11127228 周義庭
#include<iostream>
#include<fstream> // to provides the necessary classes and function to handle file operations

using namespace std ;

class Maze{

private:
    int row = 0, column = 0, nowDirction = 1, numGoal = 1 ;
    char maze[100][100] = {'\0'} ; // create an array to record the initial maze
    bool success = false ; // 'success' represents whether find all goals
    bool nodeState[100][100] = {false} ; // create an array to record  the status of each node

public:
    void readFile(string fileName, int x){
        ifstream in ; // create the input stream
        fileName = "input" + fileName + ".txt" ; // to provide the missing filename
        numGoal = x ;

        in.open( fileName ) ; // open a file named "fileName"
        if ( in.fail() ){ // check the file is open
            cout << "input file opening failed" << endl ;
            in.close() ; // close the input stream
            return ;
        }

        in >> column >> row ; // input the number of column and row
        for( int i = 0 ; i < row ; i++ ){ // input the character array
            for( int j = 0 ; j < column ; j++ ){
                in >> maze[i][j] ;
            }
            maze[i][column] = '\n' ;
        }

        in.close() ;

        visit(0, 0) ;
        printMaze() ; // print finally maze
    }

    int visit( int i, int j ){

        int times = 0 ; // 'times' represents the number of rotations

        if ( maze[i][j] == 'E' ) // change the visited cells from 'E' to 'V'
            maze[i][j] = 'V' ;
        else if ( maze[i][j] == 'G' ){ // change the visited goal from 'G' to 'F'
            maze[i][j] = 'F' ;
            numGoal-- ;
            nodeState[i][j] = true ; // the node is on the path to find the goal
            if ( numGoal == 0 ) // all goals have been found
                success = true ;
        }

        while( times < 4 && success != true ){
            // determine which direction to move

            if ( ( maze[i][j+1] == 'E' || maze[i][j+1] == 'G' ) && nowDirction == 1 ){ // right
                visit( i, j+1 ) ;
                if ( nodeState[i][j+1] == true )
                    nodeState[i][j] = true ;
            }
            else if ( ( maze[i+1][j] == 'E' || maze[i+1][j] == 'G' ) && nowDirction == 2 ){ // down
                visit( i+1, j ) ;
                if ( nodeState[i+1][j] == true )
                    nodeState[i][j] = true ;
            }
            else if ( ( maze[i][j-1] == 'E' || maze[i][j-1] == 'G' ) && nowDirction == 3 ){ // left
                visit( i, j-1 ) ;
                if ( nodeState[i][j-1] == true )
                    nodeState[i][j] = true ;
            }
            else if ( ( maze[i-1][j] == 'E' || maze[i-1][j] == 'G' ) && nowDirction == 4 ){ // up
                visit( i-1, j ) ;
                if ( nodeState[i-1][j] == true )
                    nodeState[i][j] = true ;
            }

            times++ ;
            if ( nowDirction < 4 )
                nowDirction++ ;
            else
                nowDirction = 1 ;
        }
    }

    void printMaze(){ // print two maze
        for( int i = 0 ; i < row ; i++ ){
            for( int j = 0 ; j < column + 1 ; j++ ){
                if ( maze[i][j] == 'F' )
                    cout << 'G' ;
                else
                    cout << maze[i][j] ;
            }
        }

        cout << endl ;

        if ( success ) {
            for( int i = 0 ; i < row ; i++ ){
                for( int j = 0 ; j < column + 1 ; j++ ){
                    if ( nodeState[i][j] == true ){
                        if ( maze[i][j] == 'V' )
                            cout << 'R' ;
                        else if ( maze[i][j] == 'F' )
                            cout << 'G' ;
                    }
                    else{
                        if ( maze[i][j] == 'V' )
                            cout << 'E' ;
                        else
                            cout << maze[i][j] ;
                    }
                }
            }
        }
    }
};

int main(){

    while(true){ // continue operating with ensured correct output
        Maze aMaze ;
        string fileName ; // to get the name of file
        int command = 0, numGoal = 1 ; // the default goal quantity is 1

        cout << endl << "*** Path Finding ***" ;
        cout << endl << "* 0. Quit             *" ;
        cout << endl << "* 1. One goal         *" ;
        cout << endl << "* 2. More goals       *" ;
        cout << endl << "********************" ;
        cout << endl << "Input a command(0, 1, 2): " ;
        cin >> command ;

        if ( command == 1 || command == 2 ){
            cout << endl << "input a file number(e.g: 101, 102 ,202.....): " ;
            cin >> fileName ;

            if( command == 2 ){
                cout << endl << "input a number of goals: " ;
                cin >> numGoal ;
            }
            cout << endl ;

            aMaze.readFile( fileName, numGoal ) ; // read file
        }
        else if ( command == 0 ){ // break the loop when the input is 0
            break ;
        }
        else{
            cout << endl << "Command does not exist!" << endl ;
        }
    }
    system( "pause" ) ; // to pause the console window after the program has finished running
    return 0 ;
}
