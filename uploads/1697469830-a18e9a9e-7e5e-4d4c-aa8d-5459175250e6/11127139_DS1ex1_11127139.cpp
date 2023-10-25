// 11127139 ����
#include <iostream>
#include <fstream>

using namespace std;

enum Modes {
    oneGoal = 1,
    multiGoal
};

enum Directions {
    Right = 0,
    Down,
    Left,
    Up
};

class Mouse {
public:
    Mouse();
    void getPosition(int &x, int&y ) const; // get the current position
    void getNextPosition( int &x, int &y ); // get the position of the mouse should be in next move
    bool changeDirection(); // change current direction
    void move(); // go to the next position with respect to the current direction
    void back(); // move back to the previous position with respect to the current direction
private:
    Directions m_direct; // the direction would be tried in next movement
    int m_x; // counting from 0, the horizontal axis
    int m_y; // counting from 0
    int m_triedDirect; // record how many different directions has tried.

};





class Maze {
public:
    Maze(); // constructor
    bool findGoals( Maze &visitedMaze ); // method of find N goals
    bool load( string fileNo, Modes mode ); // load the map from text file and setting m_NGoal
    void clr(); // clean up the map
    void show() const; // print out the map
    char** getMap(); // get the m_map
    void set( char ch, int x, int y );
    void copyMap( char** goalMap );
private:
    int m_width; // the number of characters in each row.
    int m_length; // the number of characters in each column
    int m_NGoal; // number of goals which need to find
    char **m_map;
    bool checkNext( Mouse micky );
    void setRow(string str, int rowNum); // Set each character in the rows
    bool getWidthAndLength( string str ); // get the input number of row and column
    void setMapSize();  // set m_map to be an m_length-row string array
    bool checkInsideOrNot( int x, int y) const;
    bool findingGoals( Maze visitedMaze, int &NumOfFound, Mouse micky );
};


int main() {

    int cmd = -1;
    string fileName;
    Modes mode;

    while ( cmd != 0 ) {

        Maze aMaze;
        // get Command (0, 1, 2)
        cout << endl << "--Path Finding    --";
        cout << endl << "- 0. Quit          -";
        cout << endl << "- 1. One goal      -";
        cout << endl << "- 2. Multiple goal -";
        cout << endl << "--------------------";
        cout << endl << "Please input a command(0, 1, 2): ";

        cin >> cmd;

        if ( 1 <= cmd && cmd <= 2 ) {
            if ( cmd == 1 )
                mode = oneGoal;
            else
                mode = multiGoal;

            cout << endl << "Please input a file number: ";
            cin >> fileName;
            if ( aMaze.load(fileName, mode ) ) {
                Maze vMaze(aMaze);
                vMaze.copyMap( aMaze.getMap() ); // Copy a new map from aMaze
                // �ǤJvMaze�A�������L���`�I
                bool successOrNot = aMaze.findGoals( vMaze);
                vMaze.show();
                if ( successOrNot )
                    aMaze.show();
                vMaze.clr();
            }

            aMaze.clr();
        }
        else if ( cmd != 0 )
            cout << endl << "Command does not exist!" << endl;

        // else command == 0, quit.
    }

    return 0;
}

Mouse::Mouse() {
    m_direct = Right;
    m_x = 0;
    m_y = 0;
    m_triedDirect = 1;
}

void Mouse::getPosition(int &x, int &y) const {
    x = m_x;
    y = m_y;
}

void Mouse::getNextPosition(int &x, int &y) {
    x = m_x;
    y = m_y;
    if ( m_direct == Right )
        x += 1;
    else if ( m_direct == Down )
        y += 1;
    else if ( m_direct == Left )
        x -= 1;
    else  // up
        y -= 1;

}

bool Mouse::changeDirection() {
    /*
     * if change successfully, return true
     * otherwise, if the four directions had all been tried, return false
     */
    if ( m_triedDirect < 4 ) {
        if (m_direct == Right)
            m_direct = Down;
        else if (m_direct == Down)
            m_direct = Left;
        else if (m_direct == Left)
            m_direct = Up;
        else
            m_direct = Right;
        m_triedDirect++;
        return true;
    }
    else
        return false;
}

void Mouse::move() {
    // set the position into ( x, y ) which were given by getNextPosition(x, y)
    int x, y;
    getNextPosition( x, y );
    m_x = x;
    m_y = y;
    m_triedDirect = 1; // ���ʫ�A���L����V�ƶqreset
}

void Mouse::back() {
    // move backwardly according to the direction: m_direct
    if ( m_direct == Right )
        m_x -= 1;
    else if ( m_direct == Down )
        m_y -= 1;
    else if ( m_direct == Left )
        m_x += 1;
    else
        m_y += 1;
}

Maze::Maze() {
    m_width = 0;
    m_length = 0;
    m_NGoal = 1;
    m_map = NULL;
}

bool Maze::findGoals( Maze &visitedMaze) {
    Mouse micky;
    int NumOfFound = 0;
    findingGoals( visitedMaze, NumOfFound, micky );
    if ( NumOfFound == m_NGoal )
        return true;
    else
        return false;

}


bool Maze::load( string fileNo, Modes mode ) {
    /*
     * this function will get a text file according to the argument: fileNo. Then setting the map.
     * And set the number of goals need to be found.
     * return true when the task has done successfully.
     * otherwise, return false.
     */
    string fileName = "input" + fileNo + ".txt"; // set the file to the form of "input###.txt"


    ifstream file;
    file.open( fileName.c_str() ); // �ഫ���r���}�C

    // �L�k���}�ɮ�
    if ( ! file.is_open() ) {
        cout << endl << "Failed to get file!";
        return false;
    }

    string str;
    getline(file, str); // str�����Ĥ@��Ʀr
    getWidthAndLength(str);    // Ū�� width and length

    setMapSize(); // ���t�O����Ŷ�

    int rowNum = 0;
    // �N�C�C�����|��T�s�im_map
    while( ! file.eof() && rowNum < m_length ) {
        getline(file, str); // get one line in file
        setRow( str, rowNum); // set m_map[rowNum]
        rowNum++;
    }

    file.close();

    // set the number of goals which need to be found
    if ( mode == multiGoal ) {
        cout << endl << "Please input number of goals: ";
        cin >> m_NGoal;
    }
    else // mode == oneGoal
        m_NGoal = 1;

    return true;
}

void Maze::clr() {
    // free the memory use by m_map
    for ( int y = 0; y < m_length; y++ ) {
        delete [] m_map[y];
    }
    delete [] m_map;
}

void Maze::show() const {
    // print out the m_map of the maze

    for (int i = 0; i < m_length; i++ ) {
        cout << endl;
        for ( int j = 0; j < m_width; j++ ) {
            if ( m_map[i][j] == 'D' )
                cout << 'G';
            else
                cout << m_map[i][j];
        }
    }
    cout << endl;
}

char** Maze::getMap() {
    return m_map;
}

void Maze::set(char ch, int x, int y ) {
    m_map[y][x] = ch;
}


void Maze::copyMap( char** goalMap ) {
    /*
     * goalMap: a map which want to copy
     * set the m_map to be as same as goalMap
     */

    setMapSize(); // new a m_length * m_width array for m_map

    for ( int i = 0; i < m_length; i++ ) {
        for ( int j = 0; j < m_width; j++ ) {
            m_map[i][j] = goalMap[i][j];
        }
    }
}

bool Maze::checkNext( Mouse micky ) {
    /*
     * if the next place is 'E' or 'G', return true.
     * otherwise, return false.
     */

    int x,y;
    micky.getNextPosition( x, y );
    if ( checkInsideOrNot( x, y )  ) {
        if ( m_map[y][x] == 'E' || m_map[y][x] == 'G' )
            return true;
    }

    return false;
}

void Maze::setRow(std::string str, int rowNum) {
    // setting map data
    for (int i = 0; i < m_width; i++) {
        m_map[rowNum][i] = str[i];
    }
}

bool Maze::getWidthAndLength( string str) {
    // get two number in the str and set up the value of m_length and m_width
    int i = 0;
    int width = 0, length = 0;
    bool success1 = false, success2 = false;
    // Ū�J width
    while ( isdigit( str[i] ) && i < str.length() ) {
        width = width * 10 + str[i] - '0';
        success1 = true;
        i++;
    }
    // Ū�J length
    while ( ! isdigit(str[i]) && i < str.length() )
        i++;
    while ( isdigit( str[i] ) && i < str.length() ) {
        length = length * 10 + str[i] - '0';
        i++;
        success2 = true;
    }

    if ( success1 && success2 ) { // ���\Ū�J���e
        m_width = width;
        m_length = length;
        return true;
    }
    else
        return false;

}

void Maze::setMapSize() {
    // new m_length strings to store each rows
    m_map = new char *[m_length];
    for ( int i = 0; i < m_length; i++ ) {
        m_map[i] = new char[m_width];
    }
}


bool Maze::checkInsideOrNot( int x, int y ) const {
    // if x,y out of range return false
    if (x < 0 || y < 0)
        return false;
    else if (y >= m_length || x >= m_width)
        return false;

    return true;
}

bool Maze::findingGoals(Maze visitedMaze, int &NumOfFound, Mouse micky) {
    /*
     * for each recursive call:
     * this function would be given:
     * visited Maze: record where are already visited.
     * NumOfFound: the total number of goals which were already found.
     * micky: Mouse type data record current position and direction.
     * it will check four different node next to this node.
     * return true when it finds out any 'G'
     * otherwise, return false.
     */
    bool done = false;
    bool foundAGoal = false;
    int x, y; // the index of mouse position in this recursive call
    micky.getPosition(x, y);
    if ( m_map[y][x] == 'G' ) {
        foundAGoal = true;
        NumOfFound+=1;
        visitedMaze.set('D', x, y ); // set the visited 'G' into another char to avoid from visiting again
    }
    else
        visitedMaze.set( 'V', x, y );

    Mouse nextMicky(micky); // been declared to try the different next step
    // go through the four different directions
    while ( !done && m_NGoal != NumOfFound ) {

        if ( visitedMaze.checkNext( nextMicky ) ) {
            nextMicky.move();
            if ( findingGoals( visitedMaze, NumOfFound, nextMicky ) ) {

                if ( m_map[y][x] != 'G' )
                    set( 'R', x, y );
                foundAGoal = true;

            }
            nextMicky.back(); // set the mouse position back to the initial index of this recursive call
        }

        // try next direction
        if ( !nextMicky.changeDirection() )
            done = true;
        // if done, quit the loop
    }  // end of while

    if ( foundAGoal || m_NGoal == NumOfFound ) // find a goal or enough goals after trying next steps
        return true;
    return false;
}