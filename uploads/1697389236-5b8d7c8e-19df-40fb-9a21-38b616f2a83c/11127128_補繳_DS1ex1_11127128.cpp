// 11127128 蔡維庭

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std ;

enum {
    Right = 0,
    Down = 1,
    Left = 2,
    Up = 3
};

typedef enum {
    Quit, oneG, moreG
} Modes;

class Co {
    int y ;
    int x ;

public:
    Co(): y(0), x(0) {};

    Co(int py, int px) {
        y = py ;
        x = px ;
    }

    /** set up the coordinate (py, px)
     */
    void setCo(int py, int px) {
        y = py ;
        x = px ;
    }

    /** get the X coordinate of pt
     */
    int getX() const {
        return x ;
    }

    /** get the Y coordinate of pt
     */
    int getY() const {
        return y ;
    }

    Co nextXY(int dir) const {
        Co nt(y,x);
        switch (dir) {
            case Right: nt.x++;
                break;
            case Down: nt.y++;
                break;
            case Left: nt.x--;
                break;
            case Up: nt.y--;
                break;
            default: ;
        }
        return nt;
    }

    /**  check if it is the same as pt
     */
    bool match(const Co& pt) const {
        if ((y == pt.y) && (x == pt.x))
            return true;

        return false;
    }

    bool inRange(const Co& maxLimit) const {
        if ((y >= 0) && (y < maxLimit.y) && (x >= 0) && (x < maxLimit.x))
            return true;
        return false;
    }
};

struct VisitResult {
    bool result ;
    Co goal ;
};

class Maze {
    Co coMax ;
    char **mArray{} ;
    vector< vector<char> > map ;

public:
    Maze() = default;
    Maze(const Maze & src): coMax(src.coMax), map(src.map) {
        if (src.mArray != NULL) {
            mArray = new char * [coMax.getY()] ;
            for (int i = 0 ; i < coMax.getY() ; i++) {
                mArray[i] = new char [coMax.getX() + 1] ;
                strcpy(mArray[i], src.mArray[i]) ;
            }
        }

    }


    bool load(string fileName) {
        FILE *infile = NULL ;
        bool done = false ;

        fileName = "input" + fileName + ".txt";
        infile = fopen(fileName.c_str(), "r");
        if (infile == NULL)
            cout << endl << fileName << " does not exist." << endl;
        else {
            int arg1 = 0, arg2 = 0;
            fscanf(infile,"%d %d", &arg1, &arg2);
            coMax.setCo(arg2-1, arg1-1); // the number of rows & columns in the maze
            if ((coMax.getY() >= 0) && (coMax.getX() >= 0)) {
                int line = 0;
                char *temp = new char [coMax.getX() + 2]; // buffer to keep one line

                mArray = new char * [coMax.getY() + 1]; // prepare a series of pointers
                while (fscanf(infile, "%s", temp) != EOF) {
                    mArray[line] = new char [coMax.getX() + 2]; // ended by an extra '\0'
                    strcpy(mArray[line++], temp); // load the maze line by line
                }
                if (line == coMax.getY() + 1)
                    done = true; // the number of rows is correct
            }

            fclose(infile); // close the file
        }

        map.resize(coMax.getY() + 1);
        for (int i = 0 ; i <= coMax.getY() ; i++) {
            map[i].resize(coMax.getX() + 1);
            for (int j = 0 ; j <= coMax.getX() ; j++) {
                map[i][j] = mArray[i][j] ;
            }
        }

        return done;
    }

    void markPoint(Co target, char status) {
        int y = target.getY() ;
        int x = target.getX() ;

        map[y][x] = status ;
    }

    bool findGoals(Maze &vM, int goalCount) {

        vector<Co> goal ;
        Co current(0, 0) ;
        int gc = 0 ;
        for (int i = 0 ; i <= coMax.getY() ; i++) {
            for (int j = 0 ; j <= coMax.getX() ; j++) {
                if (map[i][j] == 'G') {
                    goal.emplace_back(i, j);
                }
            }
        }

        if (!visit(current, goal, vM))
            return false;

        for (int i = 0 ; i <= coMax.getY() ; i++) {
            for (int j = 0 ; j <= coMax.getX() ; j++) {
                if (map[i][j] == 'V')
                    map[i][j] = 'R' ;
            }
        }

        return true;
    }

    bool visit(Co current, vector<Co> goal, Maze &vM, int dir = Right) {
        for (auto i : goal) {
            if (i.match(current)) {    // when goal reached
                return true;
            }
        }

        if (!current.inRange(coMax))
            return false ;    // out of range

        if (map[current.getY()][current.getX()] != 'E') {
            return false ;    // impassable
        }
        else {
            if (map[current.getY()][current.getX()] != 'G') {
                map[current.getY()][current.getX()] = 'V' ;  // mark current point as visited
                vM.markPoint(current, 'V');
            }

            if (!visit(current.nextXY(dir), goal, vM, dir) &&
                !visit(current.nextXY((dir+1)%4), goal, vM, (dir+1)%4) &&
                !visit(current.nextXY((dir+2)%4), goal, vM, (dir+1)%4) &&
                !visit(current.nextXY((dir+3)%4), goal, vM, (dir+1)%4)) {   // all directions failed, dead end
                if (map[current.getY()][current.getX()] != 'G')
                    map[current.getY()][current.getX()] = 'E' ;

                return false ;
            }
        }

        return true ;
    }

    void show() {
        for (int i = 0 ; i <= coMax.getY() ; i++) {
            for (int j = 0 ; j <= coMax.getX() ; j++) {
                cout << map[i][j] ;
            }

            cout << endl ;
        }
    }

    void clr() {

    }
};

int main() {

    int command = 0; // user command
    do {
        Maze aMaze; // a matrix
        string fileName; // a file name
        int goalCount = 1 ;
        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit *";
        cout << endl << "* 1. One goal *";
        cout << endl << "* 2. More goals *";
        cout << endl << "********************";
        cout << endl << "Input a command(0, 1, 2): ";
        cin >> command; // get the command
        if ((command == 1) || (command == 2)) {
            cout << endl << "Input a file number (e.g., 201, 202, ...): " ;
            cin >> fileName ;
            if (command == 2) {
                cout << endl << "Input the count of G (goals):";
                cin >> goalCount;
            }
            if (aMaze.load(fileName)) { // load the original matrix
                Maze vMaze(aMaze); // a copy to keep the visited cells
                bool success = aMaze.findGoals(vMaze, goalCount); // find a path to goal(s)

                cout << endl ;
                vMaze.show(); // show on screen the visited cells
                cout << endl ;
                if (success) // to check if the goal is reached or not
                    aMaze.show(); // show on screen the route to reach the goal
                else
                    cout << "Cannot find any valid route." << endl ;

                vMaze.clr(); // clear up the copy
            }
            aMaze.clr(); // clear up the original matrix
        }
        else if (!command) // '0': stop the program
            break;
        else
            cout << endl << "Command does not exist!" << endl;
    } while (true) ;

    system("pause"); // pause the execution
    return 0;
}