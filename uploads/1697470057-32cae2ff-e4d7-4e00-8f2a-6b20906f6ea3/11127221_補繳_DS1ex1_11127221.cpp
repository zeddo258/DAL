# include <iostream>                            // cin, cout
# include <cstdio>                              // fscanf
# include <string>                              // string, c_str
# include <string.h>                            // strcpy
# include <vector>                              // vector<char>

using namespace std;

typedef enum {Copy = -1,
                Right, Down, Left, Up} Moves ; // denote the direction of each move

int gGoalFinded = 0 ;                   // count how many goals were finded
int maxStep = 0 ;                       // the maximum times visit can use

class CoXY {
    int y ;                 // Y coordinate
    int x ;                 // X coordinate
public:
    CoXY(): y(0), x(0) {
    }; // end CoXY default constructor

    CoXY(int py, int px) {              // a coordinate (py, px)
        y = py ;
        x = px ;
    };  // end CoXY constructor

    CoXY(const CoXY& pt): y(pt.y), x(pt.x) {
    };  // end CoXY copy constructor

    void setXY(const int py, const int px) { // set up the coordinate (py, px)
        y = py ;
        x = px ;
    }  // end setXY

    int getX() const {                  // get the X coordinate of pt
        return x ;
    }  // end getX

    int getY() const {                  // get the Y coordinate of pt
        return y ;
    }  // end getY

    CoXY nextXY(Moves dir) const {      // create a copy of the coordinate (y, x)
        CoXY    pt(y,x) ;

        switch (dir) {                  // get the coordinate after the move toward dir
            case Right: pt.x++ ;
                        break ;
            case Down:  pt.y++ ;
                        break ;
            case Left:  pt.x-- ;
                        break ;
            case Up:    pt.y-- ;
                        break ;
            default: ;                   // just a copy at the same coordinate
        } // end switch
        return pt ;
    } // end nextXY

    bool match(const CoXY& pt) const {  // check if it is the same as pt
        if ((y == pt.y) && (x== pt.x))
            return true ;
        return false ;
    } // end match

    bool inRange(const CoXY& maxLimit) const {
        if ((y >= 0) && ( y < maxLimit.y ) && (x >= 0) && (x < maxLimit.x))
            return true ;               // if it is in the range of (0,0) and maxLimit
        return false ;                   // out of range
    } // end inRange
} ; // end CoXY class

vector<CoXY> path ;                     // save the shortest path

class Maze {
    int row = 0 ;
    int column = 0 ;
    vector<vector<char> > maze ;
public:
    bool load(string fileName) {
        FILE    *infile = NULL ;            // a file handle
        bool    success = false ;           // read a file successfully or not
        CoXY    coMax(0,0) ;                // the number of rows & columns in the maze

        fileName = "input" + fileName + ".txt" ;
        infile = fopen(fileName.c_str(), "r") ;                 // open the file
        if (infile == NULL)
            cout << endl << fileName << " does not exist!" << endl ;
        else {
            int arg1 = 0, arg2 = 0 ;
            vector<char> temp2 ;                                // to save a line in .txt files

            fscanf(infile, "%d%d", &arg1, &arg2) ;
            coMax.setXY(arg2, arg1) ;                           // the number of rows & columns in the maze
            row = arg2 ;                                        // width of maze
            column = arg1 ;                                     // length of maze
            maxStep = row * column ;
            char temp[column] ;                                 // fscanf will save at here first before throw into temp2
            for (int i = 0 ; i < row ; i++) {
                fscanf(infile, "%s", temp) ;
                for (int j = 0 ; j < column ; j++)
                    temp2.push_back(temp[j]) ;                  // put every char in temp to temp2
                maze.push_back(temp2) ;                         // put whole temp2 into maze
                temp2.clear() ;                                 // clear temp2 to save another line in file
            }
            if (maze.size() == coMax.getY())
                success = true ;

            fclose(infile) ;                                    // close the file
        } // end else
        return success ;
    } // end load

    bool findGoals(Maze &vMaze, int mode) {
        CoXY start(0,0) ;
        Moves direction = Right ;                               // the direction mouse is facing to, default: Right
        int nOG = -1 ;                                          // number of goals
        int pathCount = 1 ;                                     // the distance of path
        vector<CoXY> pathSaver ;
        if (mode == 2) {
            cout << "Number of G (goals): " ;
            cin >> nOG ;
        }
		if (mode == 3) {
			if (!visit(vMaze, start, 1, nOG, direction, pathSaver, pathCount))
				return false ;
		} 
        if (visit(vMaze, start, mode, nOG, direction, pathSaver, pathCount)) {          // if found G or found enough G, return true, or return false
            if (mode == 3) {
                for (int i = 0 ; i < path.size() ; i++)
                    maze[path[i].getY()][path[i].getX()] = 'R' ;
            }
            return true ;
        }
        else
            if (mode == 3 && path.size() > 0) {
                for (int i = 0 ; i < path.size() ; i++) {
                    if (maze[path[i].getY()][path[i].getX()] != 'G')
                        maze[path[i].getY()][path[i].getX()] = 'R' ;
                }
                return true ;
            }
            return false ;
        return true ;
    } // end findGoals

    bool visit(Maze &vMaze, CoXY pt, int mode, int nOG, Moves direction, vector<CoXY> pathSaver, int pathCount) {      // the function to do recursion
        int i = pt.getY(), j = pt.getX() ;                                      // get the point the mouse are

        if (pt.getY() < 0 || pt.getX() < 0 || pt.getY() > row - 1 || pt.getX() > column - 1 ||                      // if the point over the width or length of maze
            vMaze.maze[pt.getY()][pt.getX()] == 'O' || ((mode == 1 || mode == 2) && vMaze.maze[pt.getY()][pt.getX()] == 'V' ))                                                             // or the point is obstacle
            return false ;

        if (mode == 1) {                        // single goal
            if (maze[i][j] == 'G')              // return true if the point is G
                return true ;
            if (vMaze.maze[i][j] == 'E') {      // the point is visited
                vMaze.maze[i][j] = 'V' ;

                if (direction == Right) {                                               // the mouse is facing to Right
                    if (!(visit(vMaze, pt.nextXY(Right), mode, nOG, Right, pathSaver, pathCount) ||           // return false if no G was found
                          visit(vMaze, pt.nextXY(Down), mode, nOG, Down, pathSaver, pathCount) ||             // or the point is the route to G
                          visit(vMaze, pt.nextXY(Left), mode, nOG, Left, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Up), mode, nOG, Up, pathSaver, pathCount)))
                        return false ;
                    else {
                        maze[i][j] = 'R' ;
                        return true ;
                    }
                }
                else if (direction == Down) {                                           // the mouse is facing to Down
                    if (!(visit(vMaze, pt.nextXY(Down), mode, nOG, Down, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Left), mode, nOG, Left, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Up), mode, nOG, Up, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Right), mode, nOG, Right, pathSaver, pathCount)))
                        return false ;
                    else {
                        maze[i][j] = 'R' ;
                        return true ;
                    }
                }
                else if (direction == Left) {                                           // the mouse is facing to Left
                    if (!(visit(vMaze, pt.nextXY(Left), mode, nOG, Left, pathSaver, pathCount) ||             
                          visit(vMaze, pt.nextXY(Up), mode, nOG, Up, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Right), mode, nOG, Right, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Down), mode, nOG, Down, pathSaver, pathCount)))
                        return false ;
                    else {
                        maze[i][j] = 'R' ;
                        return true ;
                    }
                }
                else {                                                                  // the mouse is facing to Up
                    if (!(visit(vMaze, pt.nextXY(Up), mode, nOG, Up, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Right), mode, nOG, Right, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Down), mode, nOG, Down, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Left), mode, nOG, Left, pathSaver, pathCount)))
                        return false ;
                    else {
                        maze[i][j] = 'R' ;
                        return true ;
                    }
                }
            }
            return false ;
        }
        else if (mode == 2 ){
            if (maze[i][j] == 'G') {                // gGoalFinded + 1 when found a goal
                gGoalFinded++ ;
                if (gGoalFinded == nOG)             // return true if the found goals are enough
                    return true ;
            }
                
            if (vMaze.maze[i][j] == 'E' || vMaze.maze[i][j] == 'G') {
                if (vMaze.maze[i][j] == 'E' || vMaze.maze[i][j] == 'G')
                    vMaze.maze[i][j] = 'V' ;
                    
                if (direction == Right) {
                    if (!(visit(vMaze, pt.nextXY(Right), mode, nOG, Right, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Down), mode, nOG, Down, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Left), mode, nOG, Left, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Up), mode, nOG, Up, pathSaver, pathCount)))
                        return false ;
                    else {
                        if (maze[i][j] != 'G')
                            maze[i][j] = 'R' ;
                        return true ;
                    }
                }
                else if (direction == Down) {
                    if (!(visit(vMaze, pt.nextXY(Down), mode, nOG, Down, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Left), mode, nOG, Left, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Up), mode, nOG, Up, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Right), mode, nOG, Right, pathSaver, pathCount)))
                        return false ;
                    else {
                        if (maze[i][j] != 'G')
                            maze[i][j] = 'R' ;
                        return true ;
                    }
                }
                else if (direction == Left) {
                    if (!(visit(vMaze, pt.nextXY(Left), mode, nOG, Left, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Up), mode, nOG, Up, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Right), mode, nOG, Right, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Down), mode, nOG, Down, pathSaver, pathCount)))
                        return false ;
                    else {
                        if (maze[i][j] != 'G')
                            maze[i][j] = 'R' ;
                        return true ;
                    }
                }
                else {
                    if (!(visit(vMaze, pt.nextXY(Up), mode, nOG, Up, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Right), mode, nOG, Right, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Down), mode, nOG, Down, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Left), mode, nOG, Left, pathSaver, pathCount)))
                        return false ;
                    else {
                        if (maze[i][j] != 'G')
                            maze[i][j] = 'R' ;
                        return true ;
                    }
                }
            }
        }
        else {                                          // the shortest path to find a G
            if (pathCount >= maxStep) {
                if (path.size() > 0)
                    return true ;
                else
                    return false ;
            }
            if (path.size() != 0 && pathCount >= path.size())
                return false ;
            if (pathSaver.size() > pathCount)
                pathSaver.erase(pathSaver.begin() + pathCount, pathSaver.end()) ;
            if (maze[i][j] == 'G' && (path.size() == 0 || pathCount < path.size())) {              // save the shortest path
                if (path.size() != 0)
                    path.clear() ;
                path.insert(path.begin(), pathSaver.begin(), pathSaver.end()) ;
                path.push_back(pt) ;
                return false ;
            }
            if (vMaze.maze[i][j] == 'E' || vMaze.maze[i][j] == 'V') {      // the point is visited
                vMaze.maze[i][j] = 'V' ;
                pathCount++ ;
                pathSaver.push_back(pt) ;

                if (direction == Right) {                                               // the mouse is facing to Right
                    if (!(visit(vMaze, pt.nextXY(Right), mode, nOG, Right, pathSaver, pathCount) ||           // return false if no G was found
                          visit(vMaze, pt.nextXY(Down), mode, nOG, Down, pathSaver, pathCount) ||             // or the point is the route to G
                          visit(vMaze, pt.nextXY(Left), mode, nOG, Left, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Up), mode, nOG, Up, pathSaver, pathCount)))
                        return false ;
                    else
                        return true ;
                }
                else if (direction == Down) {                                           // the mouse is facing to Down
                    if (!(visit(vMaze, pt.nextXY(Down), mode, nOG, Down, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Left), mode, nOG, Left, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Up), mode, nOG, Up, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Right), mode, nOG, Right, pathSaver, pathCount)))
                        return false ;
                    else
                        return true ;
                }
                else if (direction == Left) {                                           // the mouse is facing to Left
                    if (!(visit(vMaze, pt.nextXY(Left), mode, nOG, Left, pathSaver, pathCount) ||             
                          visit(vMaze, pt.nextXY(Up), mode, nOG, Up, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Right), mode, nOG, Right, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Down), mode, nOG, Down, pathSaver, pathCount)))
                        return false ;
                    else
                        return true ;
                }
                else {                                                                  // the mouse is facing to Up
                    if (!(visit(vMaze, pt.nextXY(Up), mode, nOG, Up, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Right), mode, nOG, Right, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Down), mode, nOG, Down, pathSaver, pathCount) ||
                          visit(vMaze, pt.nextXY(Left), mode, nOG, Left, pathSaver, pathCount)))
                        return false ;
                    else
                        return true ;
                }
            }
        }
        return false ;
    }

    void show() {                                   // show the maze
        for (int i = 0 ; i < row ; i++) {
            for (int j = 0 ; j < column; j++)
                cout << maze[i][j] ;
            cout << endl ;
        }
        cout << endl ;
    } // end show

    void clr() {                    // clear the maze
        row = 0 ;
        column = 0 ;
        maze.clear() ;
    } // end clr
} ;

int main(void) {
    int cmd = 0 ;                               // user command

    do {
        Maze    aMaze ;                         // a matrix
        string  fileName ;                      // a file name
        int  mode = 1 ;                   // default: one goal

        gGoalFinded = 0 ;
        path.clear() ;

        cout << endl << "*** Path Finding ***" ;
        cout << endl << "* 0. Quit          *" ;
        cout << endl << "* 1. One goal      *" ;
        cout << endl << "* 2. More goals    *" ;
        cout << endl << "* 3. Shortest path *" ;
        cout << endl << "********************" ;
        cout << endl << "Input a command(0,1,2,3): " ;
        cin >> cmd ;                            // get the command
        if ((cmd == 1) || (cmd == 2) || (cmd == 3)) {
            if (cmd == 2)
                mode = 2 ;                      // one or more goals
            if (cmd == 3)
                mode = 3 ;                      // shortest path
            cout << endl << "Input a file number (e.g., 201, 202, ...): " ;
            cin >> fileName ;
            if (aMaze.load(fileName)) {         // load the original matrix
                Maze    vMaze(aMaze);           // a copy to keep the visited cells
                bool    success = aMaze.findGoals(vMaze, mode); // find a path to goal(s)

                vMaze.show() ;                  // show on screen the visited cells
                if (success) {                    // to check if the goal is reached or not
                    aMaze.show() ;              // show on screen the route to reach the goal
                    if ( mode == 3 )
                        cout << endl << "Shortest path length = " << path.size() << endl ;
                }
                mode = 1 ;                      // reset to default
                vMaze.clr() ;                   // clear up the copy
            } // end if
            aMaze.clr() ;                       // clear up the original matrix
        } // end if
        else if (!cmd)                          // '0': stop the program
            break ;
        else
            cout << endl << "Command does not exist!" << endl ;
    } while (true) ;
    system("pause") ;                           // pause the execution
    return 0 ;
} // end main
