// 11127132 羅海綺
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

enum Direction { R, D, L, U }; 
enum Mode { oneG, moreG };

class CoXY{
    int x, y; // X and Y coordinate
    public:
        CoXY(): y(0), x(0)
        {} // end CoXY default constructor
        CoXY(int py, int px){ // a coordinate (py, px)
            y = py;
            x = px;
        } // end CoXY constructor
        CoXY(const CoXY &pt): y(pt.y), x(pt.x) // copy a coordinate
        {} // end CoXY copy constructor

        void setXY(const int py, const int px){ // set up the coordinate (py, px)
            y = py;
            x = px;
        } // end CoXY::setXY

        int getX() const { // get the X coordinate of pt
            return x;
        } // end CoXY::getX

        int getY() const { // get the Y coordinate of pt
            return y;
        } // end CoXY::getY 

        bool inRange(const CoXY &maxLimit) const {
            if ((y >= 0) && ( y < maxLimit.y) 
                && ( x >= 0 ) && ( x < maxLimit.x))
                return true; // if it is in the range of (0,0) and maxLimit
            return false; // out of range
         } // end CoXY::inRange
}; // end CoXY class

class Maze{ 
    private:
        int numOfG = 1; // how many goals
        int row = 0, column = 0; 

    public:
        vector<vector<char>> enter, passed, success, trace; // vector of the input, visited cells and path
        vector<vector<CoXY>> path; // vector of the successful path
        vector<CoXY> tmpP, shortestP; // vector of the coordinate of the successful path
        Direction dir = R; // the direction
        int len = 0;

    bool load(string fileName, Mode mode){ // read a file to create a maze
        ifstream in; // input file stream
        bool suc = false; // read a file successfully or not
        CoXY coMax(0,0); // the number of rows & columns in the maze

        fileName = "input"+fileName+".txt";
        in.open(fileName); // open the file
        while(in.fail()){ 
            cout << endl << fileName << " does not exist!" << endl;
            cout << endl << "Input a file number (e.g., 201, 202, ...):";
            cin >> fileName; 
            fileName = "input"+fileName+".txt";
            in.open(fileName); // open the new file
        } // while

        in >> column >> row;
        coMax.setXY(row, column); // the number of rows & columns in the maze
        if((coMax.getY() > 0) && (coMax.getX() > 0)){
            int line = 0;
            string tmp; // buffer to keep one line
            
            enter.resize(row); // resize the vector
            for( int i=0 ; i < row ; i++ )
                enter[i].resize(column);
            passed.resize(row);
            for( int i=0 ; i < row ; i++ )
                passed[i].resize(column);
            success.resize(row);
            for( int i=0 ; i < row ; i++ )
                success[i].resize(column);
            trace.resize(row);
            for( int i=0 ; i < row ; i++ )
                trace[i].resize(column);
            
            while(in >> tmp){
                enter[line].assign(tmp.begin(), tmp.end()); // load the maze line by line
                line = line+1;
            } // end while

            if(line == coMax.getY()) // the number of rows is correct
                suc = true; 
                
        } // end if      
        in.close(); // close the file
      
        if ((mode == moreG) && (suc == true)){ // if the number of rows is correct and the mode is more goals
            cout << endl << "Number of G (goals):";
            cin >> numOfG ;
            while (!((numOfG < 101) && (numOfG > 0))){ // if the number of goals not in the range 1~100
                cout << endl << "### The number must be in [1,100] ###" << endl;
                cout << endl << "Number of G (goals):";
                cin >> numOfG ;
            } // end while
        } // end if

        return suc;
    } // end load

    bool findGoals(int x, int y){
        CoXY cur(y,x); // current coordinate
        CoXY max(row,column); // maxLimit

        if(numOfG == 0) // found all the goals
            return true;

        if(!cur.inRange(max))// current coordinate exceeds the array boundary
            return false;

        if((passed[y][x] == 'V') || (passed[y][x] == 'O')) // current coordinate is visited or obstacle
            return false;

        passed[y][x] = 'V'; // mark as visited
        tmpP.push_back(cur) ; // add the path to the temp path
 
        if(enter[y][x] == 'G'){ // current coordinate is the goal
            path.push_back(tmpP); // add the path to the final path
            numOfG = numOfG-1; 
        } // end if

        for(int i = 0 ; i < 4 ; i++){
            switch (dir){
                case R:
                    x = cur.getX()+1;
                    y = cur.getY();
                    break;
                case D:
                    x = cur.getX();
                    y = cur.getY()+1;
                    break;
                case L:
                    x = cur.getX()-1;
                    y = cur.getY();
                    break;
                case U:
                    x = cur.getX();
                    y = cur.getY()-1;
                    break;
                default:
                    break;
            } // end switch

            findGoals(x,y);
            if(dir == R) // change the direction
                dir = D;
            else if(dir == D)
                dir = L;
            else if(dir == L)
                dir = U;
            else if(dir == U)
                dir = R;
        } // end for

        tmpP.pop_back(); // remove this coordinate
        if (numOfG == 0)
            return true;
        else
            return false;
    } // end findGoals

    void show(){ 
        for(int i=0 ; i<passed.size() ; i++){
            for(int j=0 ; j<passed[i].size() ; j++){
                if(enter[i][j] == 'G') // if the original sign is the goal
                    cout << enter[i][j]; 
                else
                    cout << passed[i][j]; // print the visited sign
            } // end inner for

            cout << endl;
        } // end outter for
        cout << endl;

        tmpP.clear(); // clear up the temp path
    } // end show

    void showR(){
        for(int i=0 ; i<path.size() ; i++){
            for(int j=0 ; j<path[i].size() ; j++){
                if ( enter[path[i][j].getY()][path[i][j].getX()] == 'E') // if the original sign is empty
                    success[path[i][j].getY()][path[i][j].getX()] = 'R'; // change the sign to R
            } // end inner for
        } // end outter for

        for(int i=0 ; i<success.size() ; i++){
            for(int j=0 ; j<success[i].size() ; j++){
                cout << success[i][j];
            } // end inner for

            cout << endl;
        } // end outter for
        cout << endl;

        path.clear(); // clear up the path
    } // end showR


    void findShortestPath(int x, int y){
        CoXY cur(y,x); // current coordinate
        CoXY max(row,column); // maxLimit

        if(!cur.inRange(max))// current coordinate exceeds the array boundary
            return ;

        if(trace[y][x] == 'O') // current coordinate is obstacle
            return ;

        if((trace[y][x] == 'V') && (enter[y][x] != 'G')) // current coordinate is visited
            return ;

        if((tmpP.size() >= shortestP.size()-1) && (shortestP.size() != 0))
            return ;

        passed[y][x] = 'V';
        trace[y][x] = 'V';   
        tmpP.push_back(cur); // add the path to the temp path

        if(enter[y][x] == 'G'){ // current coordinate is the goal
            if((shortestP.size() == 0) || (tmpP.size() < shortestP.size()))
                shortestP = tmpP; // add the path to the shortest path
            
        } // end if

        for(int i = 0 ; i < 4 ; i++){
            switch (dir){
                case R:
                    x = cur.getX()+1;
                    y = cur.getY();
                    break;
                case D:
                    x = cur.getX();
                    y = cur.getY()+1;
                    break;
                case L:
                    x = cur.getX()-1;
                    y = cur.getY();
                    break;
                case U:
                    x = cur.getX();
                    y = cur.getY()-1;
                    break;
                default:
                    break;
            } // end switch
            
            findShortestPath(x,y);
            if(dir == R) // change the direction
                dir = D;
            else if(dir == D)
                dir = L;
            else if(dir == L)
                dir = U;
            else if(dir == U)
                dir = R;
        } // end for

        trace[cur.getY()][cur.getX()] = enter[cur.getY()][cur.getX()]; // change the sign to original
        tmpP.pop_back(); // remove this coordinate
        return ;
    } // end findShortestPath

    void showS(){
        if (shortestP.size() == 0)
            cout << endl << "### There is no path to find a goal! ###" << endl;
        else{
            for(int i=0 ; i<shortestP.size() ; i++){
                if ( enter[shortestP[i].getY()][shortestP[i].getX()] == 'E') // if the original sign is empty
                    success[shortestP[i].getY()][shortestP[i].getX()] = 'R'; // change the sign to R
            } // end outter for

            for(int i=0 ; i<success.size() ; i++){
                for(int j=0 ; j<success[i].size() ; j++){
                    cout << success[i][j];
                } // end inner for

                cout << endl;
            } // end outter for

            cout << endl << "Shortest path length = " << shortestP.size() << endl;
        } // end else
        tmpP.clear(); // clear up the temp path
        trace.clear();
        shortestP.clear();
    } // end showS
}; // end Maze class



int main(void){
    int command = 0;
    do{
        Maze maze; // matrix
        string fileName; // a file name
        Mode mode = oneG; // default: one goal
        bool suc = false;

        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit          *";
        cout << endl << "* 1. One goal      *";
        cout << endl << "* 2. More goals    *";
        cout << endl << "* 3. Shortest Path *";
        cout << endl << "********************";
        cout << endl << "Input a  command(0, 1, 2, 3):";
        cin >> command; // get the command
        if((command == 1) || (command == 2) || (command == 3)){
            if(command == 2)
                mode = moreG; // one or more goals
            cout << endl << "Input a file number (e.g., 201, 202, ...):";
            cin >> fileName;
            if(maze.load(fileName, mode)){ // load the original matrix
                copy(maze.enter.begin(), maze.enter.end(), maze.passed.begin()); // a copy to keep the visited cells
                copy(maze.enter.begin(), maze.enter.end(), maze.success.begin());
                copy(maze.enter.begin(), maze.enter.end(), maze.trace.begin());

                if((command == 1) || (command == 2))  
                    suc = maze.findGoals(0,0); // find a path to goal(s)
                if(command == 3) 
                    maze.findShortestPath(0,0); // find a shortest path to goal

                mode = oneG; // reset to default
                maze.show(); // show on screen the visited cells

                if(command == 3)
                    maze.showS(); // show on screen the shortest route to reach the goal
                    
                if( suc )
                    maze.showR(); // show on screen the route to reach the goal

                maze.passed.clear(); // clear up the copy
                maze.success.clear();
            } // end inner-if
            maze.enter.clear(); // clear up the original matrix
        } // end outer-i
        else if( !command ) // '0': stop the program
            break;
        else
            cout << endl << "Command does not exist!" << endl;
    }while( true );
    system("pause"); // pause the execution
    return 0;
} // end of main