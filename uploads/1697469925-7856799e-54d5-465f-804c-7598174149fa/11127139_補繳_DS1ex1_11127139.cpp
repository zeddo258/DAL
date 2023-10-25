// 11127139 陳恩
#include <iostream>
#include <fstream>

using namespace std;

enum Modes {
    oneGoal = 1,
    multiGoal,
    Shortest
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
    void resetDirection();
private:
    Directions m_direct; // the direction would be tried in next movement
    int m_x; // counting from 0, the horizontal axis
    int m_y; // counting from 0
    int m_triedDirect; // record how many different directions has tried.

};

class Path {
public:
    Path();
    void addNode( int x, int y , int NumOfStep); // add the index of NumOfStep-th step into the path array
    void setPath( int numOfLength ); // new a appropriate memory space for path array
    void remove(); // remove current path and free the memory space
    int** getShortest(); // get a pointer of the array of path
    int getLength(); // get the path length
private:
    int** m_ShortestPath; // record the index of each step in path
    int m_pathLength; // record the length of path
};


class Maze {
public:
    Maze(); // constructor
    bool findGoals( Maze &visitedMaze, Modes mode ); // method of find N goals
    bool load( string fileNo, Modes mode ); // load the map from text file and setting m_NGoal
    void clr(); // clean up the map
    void show() const; // print out the map
    char** getMap(); // get the m_map
    void set( char ch, int x, int y );
    void copyMap( char** goalMap );
    bool findShortest( Maze vMaze, Maze visitedMaze, int numOfStep, Mouse micky );
    void settingMap( int** p, int length );
    int getPathLength();
private:
    int m_width; // the number of characters in each row.
    int m_length; // the number of characters in each column
    int m_NGoal; // number of goals which need to find
    char **m_map;
    Path m_path;

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
        cout << endl << "- 3. Shortest m_path -";
        cout << endl << "--------------------";
        cout << endl << "Please input a command(0, 1, 2, 3): ";

        cin >> cmd;

        if ( 1 <= cmd && cmd <= 3 ) {
            if ( cmd == 1 )
                mode = oneGoal;
            else if ( cmd == 3 )
                mode = Shortest;
            else
                mode = multiGoal;

            cout << endl << "Please input a file number: ";
            cin >> fileName;
            if ( aMaze.load(fileName, mode ) ) {
                Maze vMaze(aMaze);
                vMaze.copyMap( aMaze.getMap() ); // Copy a new map from aMaze
                // 傳入vMaze，紀錄歷過的節點
                bool successOrNot = aMaze.findGoals( vMaze, mode);
                vMaze.show();
                if ( successOrNot ) {
                    aMaze.show();
                    if ( mode == Shortest )
                        cout << endl << " Shortest Path Length : " << aMaze.getPathLength();
                }
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
    m_triedDirect = 1; // 移動後，走過的方向數量reset

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

void Mouse::resetDirection() {
    m_triedDirect = 1;
}

Maze::Maze() {
    m_width = 0;
    m_length = 0;
    m_NGoal = 1;
    m_map = NULL;
    m_path = Path();
}

bool Maze::findGoals( Maze &vMaze, Modes mode) {
    Mouse micky;
    int NumOfFound = 0;
    if ( mode == Shortest ) {
        Maze visitedMaze( vMaze );
        visitedMaze.copyMap(vMaze.getMap());

        if ( findShortest( vMaze, visitedMaze, 1, micky ) ) { // 由起點第一步開始尋找

            settingMap(m_path.getShortest(), m_path.getLength() );
            return true;
        }
        else
            return false;
    }
    else {
        findingGoals(vMaze, NumOfFound, micky);
        if (NumOfFound == m_NGoal)
            return true;
        else
            return false;
    }
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
    file.open( fileName.c_str() ); // 轉換為字元陣列

    // 無法打開檔案
    if ( ! file.is_open() ) {
        cout << endl << "Failed to get file!";
        return false;
    }

    string str;
    getline(file, str); // str接取第一行數字
    getWidthAndLength(str);    // 讀取 width and length

    setMapSize(); // 分配記憶體空間

    int rowNum = 0;
    // 將每列的路徑資訊存進m_map
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
    m_map = NULL;
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
    // 讀入 width
    while ( isdigit( str[i] ) && i < str.length() ) {
        width = width * 10 + str[i] - '0';
        success1 = true;
        i++;
    }
    // 讀入 length
    while ( ! isdigit(str[i]) && i < str.length() )
        i++;
    while ( isdigit( str[i] ) && i < str.length() ) {
        length = length * 10 + str[i] - '0';
        i++;
        success2 = true;
    }

    if ( success1 && success2 ) { // 成功讀入長寬
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

    // go through the four different directions
    while ( !done && m_NGoal != NumOfFound ) {
        Mouse nextMicky(micky); // been declared to try the different next step
        if ( visitedMaze.checkNext( micky ) ) {
            nextMicky.move();
            nextMicky.resetDirection();
            if ( findingGoals( visitedMaze, NumOfFound, nextMicky ) ) {

                if ( m_map[y][x] != 'G' )
                    set( 'R', x, y );
                foundAGoal = true;

            }
            nextMicky.back(); // set the mouse position back to the initial index of this recursive call
        }

        // try next direction
        if ( !micky.changeDirection() )
            done = true;
        // if done, quit the loop
    }  // end of while

    if ( foundAGoal || m_NGoal == NumOfFound ) // find a goal or enough goals after trying next steps
        return true;
    return false;
}

bool Maze::findShortest(Maze vMaze, Maze visitedMaze, int numOfStep, Mouse micky ) {
    int x, y;
    micky.getPosition(x, y);
    /*
     * 流程：
     * 當找到G的時候使用一個紀錄path的object設定path的大小，一路紀錄回去?
     * 還是要從出發點開始記錄?
     * 當碰到盡頭就設定?
     *
     */

    int length = m_path.getLength();
    if ( length != -1 ) {
        if ( length <= numOfStep )
            return false;
    }
    if ( m_map[y][x] == 'G' ) {

        if (m_path.getLength() > 0 )
            m_path.remove();

        m_path.setPath(numOfStep);
        return true;
    }
    else {
        vMaze.set('V', x, y);
        visitedMaze.set( 'V', x, y);
    }
    bool done = false;
    bool reachGoal = false;
    // copy a map from vMaze
    Maze thisMaze(visitedMaze); // 這層將要進行造訪的Maze
    thisMaze.copyMap( visitedMaze.getMap() );
    while ( ! done ) {
        if ( thisMaze.checkNext( micky ) ) {
            Mouse nextMicky(micky);
            nextMicky.move();
            nextMicky.resetDirection();
            if (findShortest(vMaze, thisMaze, numOfStep + 1, nextMicky )) {
                m_path.addNode(x, y, numOfStep);
                reachGoal = true;
            }
        }

        if ( !micky.changeDirection() ) // 當無法改變方向時 done = true
            done = true;
    }

    if ( reachGoal )
        return true;
    else
        return false;
}

void Maze::settingMap(int **path, int length) {
    for (int i = 0; i < length - 1; i++ ) {
        set( 'R', path[0][i], path[1][i] );
    }
}

int Maze::getPathLength() {
    return m_path.getLength();
}



// definitions of methods in Path class

Path::Path() {
    m_ShortestPath = NULL;
    m_pathLength = -1;
}

void Path::addNode(int x, int y, int NumOfStep) {
    m_ShortestPath[0][NumOfStep - 1] = x;
    m_ShortestPath[1][NumOfStep - 1] = y;

}
void Path::setPath(int numOfLength) {
    // set the temp m_path size to fit the m_path need to be store
    m_ShortestPath = new int* [2];
    m_ShortestPath[0] = new int[numOfLength];
    m_ShortestPath[1] = new int[numOfLength];
    m_pathLength = numOfLength;
}
void Path::remove() {
    // 釋放記憶體空間
    if ( m_ShortestPath != NULL ){
        delete [] m_ShortestPath[0];
        delete [] m_ShortestPath[1];
        delete m_ShortestPath;
    }
}

int Path::getLength() {
    return m_pathLength;
}
int** Path::getShortest() {
    return m_ShortestPath;
}
