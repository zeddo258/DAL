// 11127223 陳郁豊
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Maze {
private:
    /* data */
    char ** maze; // 二維指針, 座標是 maze[ y ][ x ]
    char ** shortestMaze; // 最短路徑的迷宮
    int x; // 迷宮大小
    int y; // 迷宮大小
    int g; // 要找的 G 的數量
    int shortestPathLength;

    bool isWalkable( int nX, int nY ) {
        if ( nX < 0 || nX >= x ) return false;
        else if ( nY < 0 || nY >= y ) return false;
        else return maze[ nY ][ nX ] == 'E' || maze[ nY ][ nX ] == 'G';
    } // isWalkable()

    bool getIntgerToG() {
        string input;
        getline( cin, input );

        // string to integer, include nagative
        int result = 0, i = 0;
        bool isNegative = false;
        if ( input[ 0 ] == '-' ) {
            isNegative = true;
            i++;
        } // if

        for ( ; i < input.length() ; i++ ) {
            if ( input[ i ] < '0' || input[ i ] > '9' ) return false; // not a number
            result = result * 10 + input[ i ] - '0';
        } // for

        if ( isNegative ) result = -result;
        g = result;
        return true;
    } // getIntgerToG()

    void copyMazeToShortestMaze() {
        if ( shortestMaze == NULL ) {
            shortestMaze = new char*[ y ];
            for ( int i = 0 ; i < y ; i++ ) {
                shortestMaze[ i ] = new char[ x ];
            } // for
        } // if

        for ( int i = 0 ; i < y ; i++ ) {
            for ( int j = 0 ; j < x ; j++ ) {
                shortestMaze[ i ][ j ] = maze[ i ][ j ];
            } // for
        } // for
    } // copyMazeToShortestMaze()

    void copyShortestMazeToMaze() {
        for ( int i = 0 ; i < y ; i++ ) {
            for ( int j = 0 ; j < x ; j++ ) {
                maze[ i ][ j ] = shortestMaze[ i ][ j ];
            } // for
        } // for
    } // copyshortestMazeToMaze()

    bool isWalkableForShortestPath( int nX, int nY ) {
        if ( nX < 0 || nX >= x ) return false;
        else if ( nY < 0 || nY >= y ) return false;
        else return maze[ nY ][ nX ] == 'E' || maze[ nY ][ nX ] == 'G' || maze[ nY ][ nX ] == 'V';
    } // isWalkableForShortestPath()

public:
    Maze(); // default constructor
    ~Maze(); // destructor

    bool createMaze( string fileName ) {
        ifstream input( fileName );
        if ( !input.is_open() ) {
            cout << endl << fileName << " does not exist!" << endl;
            return false;
        } // if
        input >> x >> y; // 讀XY

        // 建立迷宮
        maze = new char*[ y ];
        for ( int i = 0 ; i < y ; i++ ) {
            maze[ i ] = new char[ x ];
        } // for

        // 讀入迷宮
        for ( int i = 0 ; i < y ; i++ ) {
            for ( int j = 0 ; j < x ; j++ ) {
                input >> maze[ i ][ j ];
            } // for
        } // for

        input.close();
        copyMazeToShortestMaze();
        return true;
    }

    bool findRoute( int x = 0, int y = 0, int dir = 0 ) {
        bool found = false;
        //檢查當前
        if ( maze[ y ][ x ] == 'G' ) {
            g--;
            maze[ y ][ x ] = 'g'; // 表示已找到，防止從另一側再次找到這個G
            found = true;
        } // if
        else {
            maze[ y ][ x ] = 'V'; // 標為 visited
        } // else

        for ( int i = 0 ; i < 4 ; i++ ) {
            if ( g <= 0 ) break; // 不用找了

            // i != 2 是為了避免走回頭路
            if ( dir == 0 ) { // right
                if ( isWalkable( x + 1, y ) && i != 2 ) found = findRoute( x + 1, y, dir ) || found;
            } // if
            if ( dir == 1 ) { // down
                if ( isWalkable( x, y + 1 ) && i != 2 ) found = findRoute( x, y + 1, dir ) || found;
            } // if
            if ( dir == 2 ) { // left
                if ( isWalkable( x - 1, y ) && i != 2 ) found = findRoute( x - 1, y, dir ) || found;
            } // if
            if ( dir == 3 ) { // up
                if ( isWalkable( x, y - 1 ) && i != 2 ) found = findRoute( x, y - 1, dir ) || found;
            } // if

            dir = ( dir + 1 ) % 4;
        } // for

        if ( found && maze[ y ][ x ] != 'g' ) maze[ y ][ x ] = 'R'; // 目前位置是路徑的一部份，若為 G 則不改

        if ( x == 0 && y == 0 ) return g == 0; // 有找到要求的數量則回傳 true

        return found || maze[ y ][ x ] == 'G';
    } // findRoute()

    bool findShortestRoute( int length = 1, int x = 0, int y = 0, int dir = 0 ) {
        if ( length >= shortestPathLength && shortestPathLength != -1 ) return false; // 已經超過最短路徑長度，不用找了
        

        bool found = false;
        bool foundHere = false;
        //檢查當前
        if ( maze[ y ][ x ] == 'G' ) {
            g = 0;
            shortestPathLength = length; // length 一定會比 shortestPathLength 小
            foundHere = true;
            found = true;
        } // if
        else {
            maze[ y ][ x ] = 'V'; // 標為 visited
        } // else

        for ( int i = 0 ; i < 4 ; i++ ) {
            if ( foundHere ) break; // 不用找了

            // i != 2 是為了避免走回頭路
            if ( dir == 0 ) { // right
                if ( isWalkableForShortestPath( x + 1, y ) && i != 2 ) found = findShortestRoute( length + 1, x + 1, y, dir ) || found;
            } // if
            if ( dir == 1 ) { // down
                if ( isWalkableForShortestPath( x, y + 1 ) && i != 2 ) found = findShortestRoute( length + 1, x, y + 1, dir ) || found;
            } // if
            if ( dir == 2 ) { // left
                if ( isWalkableForShortestPath( x - 1, y ) && i != 2 ) found = findShortestRoute( length + 1, x - 1, y, dir ) || found;
            } // if
            if ( dir == 3 ) { // up
                if ( isWalkableForShortestPath( x, y - 1 ) && i != 2 ) found = findShortestRoute( length + 1, x, y - 1, dir ) || found;
            } // if

            dir = ( dir + 1 ) % 4;
        } // for

        if ( foundHere ) copyMazeToShortestMaze(); // 找到一條更短的路徑 => 更新最短路徑

        if ( found && shortestMaze[ y ][ x ] != 'G' ) shortestMaze[ y ][ x ] = 'R'; // 目前位置是路徑的一部份，若為 G 則不改

        if ( x == 0 && y == 0 ) return g == 0; // 有找到要求的數量則回傳 true
        return found || foundHere;
    }

    bool haveARoute() {
        if ( findRoute() ){
            copyShortestMazeToMaze();
            return true;
        }
        else {
            return false;
        }
    }

    void setG() {
        while ( true ) {
            cout << endl << "Number of G (goals): ";
            if ( !getIntgerToG() ) continue; // get integer failed
            if ( g >= 1 && g <= 100 ) break; // g in [ 1, 100 ]
            else cout << endl << "### The number must be in [1,100] ###" << endl;
        } // while
    } // setG()

    void printVisited() {
        for ( int i = 0 ; i < y ; i++ ) {
            for ( int j = 0 ; j < x ; j++ ) {
                if ( maze[ i ][ j ] == 'R' ) cout << 'V';
                else if ( maze[ i ][ j ] == 'g' ) cout << 'G';
                else cout << maze[ i ][ j ];
            } // for

            cout << endl;
        } // for
    } // printVisited()

    void printRoute() {
        cout << endl;
        for ( int i = 0 ; i < y ; i++ ) {
            for ( int j = 0 ; j < x ; j++ ) {
                if ( maze[ i ][ j ] == 'V' ) cout << 'E';
                else if ( maze[ i ][ j ] == 'g' ) cout << 'G';
                else cout << maze[ i ][ j ];
            } // for

            cout << endl;
        } //for
    } // printRoute()

    void printShortestRoute() {
        cout << endl;
        for ( int i = 0 ; i < y ; i++ ) {
            for ( int j = 0 ; j < x ; j++ ) {
                if ( shortestMaze[ i ][ j ] == 'V' ) cout << 'E';
                else cout << shortestMaze[ i ][ j ];
            } // for

            cout << endl;
        } //for
    } // printShortestRoute()

    int getShortestPathLength() {
        return shortestPathLength;
    } // getShortestPathLength()

}; // class Maze

Maze::Maze() {
    // Default constructor
    g = 1;
    x = 0;
    y = 0;
    shortestPathLength = -1;
    shortestMaze = NULL;
    maze = NULL;
} // Maze()

Maze::~Maze() {
    // Destructor, 用於釋放記憶體, 只要手動管理動態記憶體(new)就行
    // 靜態記憶體用完會自動釋放
    if ( maze != NULL ) {
        for ( int i = 0 ; i < y ; ++i ) {
            delete[] maze[ i ];
        } // for
        delete[] maze;
    } // if

    if ( shortestMaze != NULL ) {
        for ( int i = 0 ; i < y ; ++i ) {
            delete[] shortestMaze[ i ];
        } // for
        delete[] shortestMaze;
    } // if
} // ~Maze()

int getCommand() {
    string input;
    getline( cin, input );
    if ( input.length() != 1 ) return -1;
    else if ( input[ 0 ] < '0' || input[ 0 ] > '3' ) return -1;
    else return input[ 0 ] - '0';
} // getCommand()

string getFileName() {
    cout << endl << "Input a file number: ";
    string fileName;
    getline( cin, fileName );

    return "input" + fileName + ".txt";
} // getFileName()

int main() {
    do {
        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit          *";
        cout << endl << "* 1. One goal      *";
        cout << endl << "* 2. More goals    *";
        cout << endl << "********************";
        cout << endl << "Input a command(0, 1, 2, 3): ";

        int command = getCommand();
        if ( command == 1 || command == 2 ) {
            string fileName = getFileName();

            Maze myMaze;
            if ( !myMaze.createMaze( fileName ) ) continue; // create maze failed

            if ( command == 2 ) myMaze.setG(); // set G

            if ( myMaze.findRoute() ) {
                myMaze.printVisited();
                myMaze.printRoute();
            } // if
            else {
                myMaze.printVisited();
            } // else
        } // if
        else if ( command == 3 ) {
            string fileName = getFileName();

            Maze myMaze;
            if ( !myMaze.createMaze( fileName ) ) continue; // create maze failed

            if ( myMaze.haveARoute() ) { // 先確定有路徑
                myMaze.findShortestRoute();
                myMaze.printVisited();
                myMaze.printShortestRoute();
                cout << endl << "Shortest path length = " << myMaze.getShortestPathLength() << endl;
            } // if
            else {
                myMaze.printVisited();
                cout << endl << "### There is no path to find a goal! ###" << endl;
            } // else
        }
        else if ( command == 0 ) {
            break;
        } // else if
        else {
            cout << endl << "Command does not exist!" << endl;
        } // else
    } while ( true );
    
    system( "pause" ); // for windows
    return 0;
} // main()