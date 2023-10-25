// 11127101 ÂÅ¦Ü«³
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Maze /* Maze class for storing the map and the functions */{

public:
    Maze(int row, int column): row( row ), column( column ) /* Constructor */ {

    }
    void inputMap( string fileName ); // Reading the map
    bool findThePathToGoals( string beforeDirection, int locationOfColumn, int locationOfRow, int goalNumbers, Maze &endMaze, int time ); // Finding the path to goals
    int link( string beforeDirection, Maze endMaze, int locationOfColumn, int locationOfRow ); // Count the number of links to this point
    bool goBack( string &beforeDirection, string doDirection, int &locationOfColumn, int &locationOfRow, int &goalNumbers, Maze &endMaze, int &time ); // Back tracking
    void showMap(); // Showing the map

private:

    int row; // The row
    int column; // The column
    vector<vector <char> > map; // Storing the map
    int right = 1, left = -1; // The row direction
    int up = -1, down = 1; // The column direction

};

void Maze::inputMap( string fileName ) /* Reading the map */ {

    int unUse; // The row and column;
    map.resize( column + 2, vector<char>( row + 2, 'W')); // Initializing the map
    fstream file;
    file.open(fileName.c_str() ); // Opening the file
    file >> unUse >> unUse; // Storing row and column;
    for ( int i = 1 ; i <= column ; i++ ) {
        for ( int j = 1 ; j <= row ; j++ ) {
            file >> map[i][j]; // Storing the map
        }
    }
    file.close(); // Closing the file
}

bool Maze::findThePathToGoals( string beforeDirection, int locationOfColumn, int locationOfRow, int goalNumbers, Maze &endMaze, int time ) /* Finding the path to goals */ {

    if ( map[locationOfColumn][locationOfRow] == 'G' ) /* If the goal is found */ {
        if ( goalNumbers == 1 ) // If there just last one goal
            return true;
        else {
            map[locationOfColumn][locationOfRow] = 'A'; // Mark the goal as visited
            return findThePathToGoals( beforeDirection, locationOfColumn, locationOfRow, goalNumbers - 1, endMaze, 1 ); // Find the path to the next goal
        }
    }
    else if ( time == 5 ) /* Time out of the four directions */ {
        if ( map[locationOfColumn][locationOfRow] != 'A' ) // If the goal is not visited
            map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
        if ( goBack( beforeDirection, beforeDirection, locationOfColumn, locationOfRow, goalNumbers, endMaze , time ) ) // If the back track is successful
            return findThePathToGoals( beforeDirection, locationOfColumn, locationOfRow, goalNumbers, endMaze, time ); // Keep searching
        else // If the back track is failed meaning the number of goals will not be found successfully
            return false;
    }
    else if ( beforeDirection == "Right" ) /* Find the path to the right direction */{
        if ( map[locationOfColumn][locationOfRow + right] == 'E' || map[locationOfColumn][locationOfRow + right] == 'G' ) /* If the route is not visited or the goal */{
            if ( map[locationOfColumn][locationOfRow] != 'A' ) /* If the route is not visited */ {
                map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
                endMaze.map[locationOfColumn][locationOfRow] = 'R'; // Mark the end map as visited
            }
            return findThePathToGoals("Right", locationOfColumn, locationOfRow + right, goalNumbers, endMaze, 1 ); // Find the path to the next goal
        }
        else
            return findThePathToGoals("Down", locationOfColumn, locationOfRow, goalNumbers, endMaze, ++time ); // Change the direction and find the path

    }
    else if ( beforeDirection == "Down" ) /* Find the path to the down direction */{
        if ( map[locationOfColumn + down][locationOfRow] == 'E' || map[locationOfColumn + down][locationOfRow] == 'G' ) /* If the route is not visited or the goal */ {
            if ( map[locationOfColumn][locationOfRow] != 'A' ) /* If the route is not visited */{
                map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
                endMaze.map[locationOfColumn][locationOfRow] = 'R'; // Mark the end map as visited
            }
            return findThePathToGoals("Down", locationOfColumn + down, locationOfRow, goalNumbers, endMaze, 1 ); // Find the path to the next goal
        }
        else
            return findThePathToGoals("Left", locationOfColumn, locationOfRow, goalNumbers, endMaze, ++time ); // Change the direction and find the path
    }
    else if ( beforeDirection == "Left" ) /* Find the path to the left direction */{
        if ( map[locationOfColumn][locationOfRow + left] == 'E' || map[locationOfColumn][locationOfRow + left] == 'G' ) /* If the route is not visited or the goal */ {
            if ( map[locationOfColumn][locationOfRow] != 'A' ) /* If the route is not visited */{
                map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
                endMaze.map[locationOfColumn][locationOfRow] = 'R'; // Mark the end map as visited
            }
            return findThePathToGoals("Left", locationOfColumn, locationOfRow + left, goalNumbers, endMaze, 1 ); // Find the path to the next goal
        }
        else
            return findThePathToGoals("Up", locationOfColumn, locationOfRow, goalNumbers, endMaze, ++time ); // Change the direction and find the path

    }
    else if ( beforeDirection == "Up" ) /* Find the path to the up direction */ {
        if ( map[locationOfColumn + up][locationOfRow] == 'E' || map[locationOfColumn + up][locationOfRow] == 'G' ) /* If the route is not visited or the goal */ {
            if ( map[locationOfColumn][locationOfRow] != 'A' ) /* If the route is not visited */ {
                map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
                endMaze.map[locationOfColumn][locationOfRow] = 'R'; // Mark the end map as visited
            }
            return findThePathToGoals("Up", locationOfColumn + up, locationOfRow, goalNumbers, endMaze, 1 ); // Find the path to the next goal
        }
        else
            return findThePathToGoals("Right", locationOfColumn, locationOfRow, goalNumbers, endMaze, ++time ); // Change the direction and find the path
    }

}

int Maze::link( string beforeDirection, Maze endMaze, int locationOfColumn, int locationOfRow ) /* Count the number of links to this point */ {
    int returnLink = 0; // The number of links
    if ( beforeDirection == "Right" )
        locationOfRow += right;
    else if ( beforeDirection == "Down" )
        locationOfColumn += down;
    else if ( beforeDirection == "Left" )
        locationOfRow += left;
    else if ( beforeDirection == "Up" )
        locationOfColumn += up;
    if ( ( endMaze.map[locationOfColumn][locationOfRow] == 'R' || endMaze.map[locationOfColumn][locationOfRow] == 'G' ) &&  ( endMaze.map[locationOfColumn + 1][locationOfRow] == 'R'  || endMaze.map[locationOfColumn + 1][locationOfRow] == 'G' ) )
        /* If the location is 'R' or 'G' and the right location is also 'R' or 'G' */
        returnLink++;
    if ( ( endMaze.map[locationOfColumn][locationOfRow] == 'R' || endMaze.map[locationOfColumn][locationOfRow] == 'G' ) &&  ( endMaze.map[locationOfColumn - 1][locationOfRow] == 'R' || endMaze.map[locationOfColumn - 1][locationOfRow] == 'G' ) )
        /* If the location is 'R' or 'G' and the left location is also 'R' or 'G' */
        returnLink++;
    if (  ( endMaze.map[locationOfColumn][locationOfRow] == 'R' || endMaze.map[locationOfColumn][locationOfRow] == 'G' ) && ( endMaze.map[locationOfColumn][locationOfRow + 1] == 'R' || endMaze.map[locationOfColumn][locationOfRow + 1] == 'G' ) )
        /* If the location is 'R' or 'G' and the up location is also 'R' or 'G' */
        returnLink++;
    if ( ( endMaze.map[locationOfColumn][locationOfRow] == 'R' || endMaze.map[locationOfColumn][locationOfRow] == 'G' ) && ( endMaze.map[locationOfColumn][locationOfRow - 1] == 'R' || endMaze.map[locationOfColumn][locationOfRow - 1] == 'G' ) )
        /* If the location is 'R' or 'G' and the down location is also 'R' or 'G' */
        returnLink++;
    return returnLink; // Return the number of links
}

bool Maze::goBack( string &beforeDirection, string doDirection, int &locationOfColumn, int &locationOfRow, int &goalNumbers, Maze &endMaze, int &time ) /* Back tracking and clean the wrong route */ {

    int currentLink = link( "NULL", endMaze, locationOfColumn, locationOfRow ); // Count the number of links to this point
    int beforeLink = link( doDirection, endMaze, locationOfColumn, locationOfRow ); // Count the number of links to before point
    if ( time == 9 || endMaze.map[1][1] == 'E' ) /* Time out of the four directions or clean to the start point */
        return false;
    else if ( doDirection == "Right" ) /* Find the back path to the left direction */{
        if ( map[locationOfColumn][locationOfRow] != 'A' && currentLink < 2  ) // If the route is already visited or the number of links is less than two
            endMaze.map[locationOfColumn][locationOfRow] = 'E'; // Mark the end map as cleared of the route
        if ( ( map[locationOfColumn][locationOfRow - right] != 'V' && map[locationOfColumn][locationOfRow - right] != 'A' ) || endMaze.map[locationOfColumn][locationOfRow - right] == 'E' )
            // If the route is not visited and is not already visited this goal, or the left location is already clean
            return goBack( beforeDirection, "Up", locationOfColumn, locationOfRow, goalNumbers, endMaze, ++time ); // Change the direction and back to the down direction
        else {
            if ( beforeLink == 0 && endMaze.map[locationOfColumn][locationOfRow] == 'R' && endMaze.map[locationOfColumn][locationOfRow - right] == 'G' ) /* If the route is visited and the left direction is a goal and the link of before direction is 0 */ {
                if ( ( endMaze.map[locationOfColumn + down][locationOfRow] == 'R' && link("Decide", endMaze, locationOfColumn + down, locationOfRow) != 2 )
                    || ( endMaze.map[locationOfColumn + up][locationOfRow] == 'R' && link("Decide", endMaze, locationOfColumn + up, locationOfRow) != 2 ) )
                    endMaze.map[locationOfColumn][locationOfRow] = 'E'; // Mark the end map as cleared of the route
            }
            beforeDirection = "Down";
            locationOfRow -= right;
            time = 1;
            return true;
            // Back to the left direction and find the path to the next goal with the down direction
        }
    }
    else if ( doDirection == "Down" ) /* Find the back path to the up direction */ {
        if ( map[locationOfColumn][locationOfRow] != 'A' && currentLink < 2  )
            endMaze.map[locationOfColumn][locationOfRow] = 'E'; // Mark the end map as cleared of the route
        if ( ( map[locationOfColumn - down][locationOfRow] != 'V' && map[locationOfColumn - down][locationOfRow] != 'A') || endMaze.map[locationOfColumn - down][locationOfRow] == 'E' )
            // If the route is not visited and is not already visited this goal, or the up location is already clean
            return goBack( beforeDirection, "Right", locationOfColumn, locationOfRow, goalNumbers, endMaze, ++time); // Change the direction and back to the left direction
        else {
            if ( beforeLink == 0 && endMaze.map[locationOfColumn][locationOfRow] == 'R' && endMaze.map[locationOfColumn - down][locationOfRow] == 'G' ) /* If the route is visited and the up direction is a goal and the link of before direction is 0 */ {
                if ( ( endMaze.map[locationOfColumn][locationOfRow + right] == 'R' && link("Decide", endMaze, locationOfColumn, locationOfRow + right) != 2 )
                    || ( endMaze.map[locationOfColumn][locationOfRow + left] == 'R' && link("Decide", endMaze, locationOfColumn, locationOfRow + left) != 2 ) )
                    endMaze.map[locationOfColumn][locationOfRow] = 'E'; // Mark the end map as cleared of the route
            }
            beforeDirection = "Left";
            locationOfColumn -= down;
            time = 1;
            return true; // Back to the up direction and find the path to the next goal with the left direction
        }
    }
    else if ( doDirection == "Left" ) /* Find the back path to the right direction */{
        if ( map[locationOfColumn][locationOfRow] != 'A' && currentLink < 2 )
            endMaze.map[locationOfColumn][locationOfRow] = 'E'; // Mark the end map as cleared of the route
        if ( ( map[locationOfColumn][locationOfRow - left] != 'V' && map[locationOfColumn][locationOfRow - left] != 'A' ) || endMaze.map[locationOfColumn][locationOfRow - left] == 'E' )
            // If the route is not visited and is not already visited this goal, or the right location is already clean
            return goBack( beforeDirection, "Down", locationOfColumn, locationOfRow, goalNumbers, endMaze, ++time); // Change the direction and back to the up direction
        else {
            if ( beforeLink == 0 && endMaze.map[locationOfColumn][locationOfRow] == 'R' && endMaze.map[locationOfColumn][locationOfRow - left] == 'G' ) /* If the route is visited and the right direction is a goal and the link of before direction is 0 */ {
                if ( ( endMaze.map[locationOfColumn + down][locationOfRow] == 'R' && link("Decide", endMaze, locationOfColumn + down, locationOfRow) != 2 )
                    || ( endMaze.map[locationOfColumn + up][locationOfRow] == 'R' && link("Decide", endMaze, locationOfColumn + up, locationOfRow) != 2 ) )
                    endMaze.map[locationOfColumn][locationOfRow] = 'E'; // Mark the end map as cleared of the route
            }
            beforeDirection = "Up";
            locationOfRow -= left;
            time = 1;
            return true; // Back to the right direction and find the path to the next goal with the up direction
        }
    }
    else if ( doDirection == "Up" ) /* Find the back path to the down direction */ {
        if ( map[locationOfColumn][locationOfRow] != 'A' && currentLink < 2 )
            endMaze.map[locationOfColumn][locationOfRow] = 'E'; // Mark the end map as cleared of the route
        if ( ( map[locationOfColumn - up][locationOfRow] != 'V' && map[locationOfColumn - up][locationOfRow] != 'A' ) || endMaze.map[locationOfColumn - up][locationOfRow] == 'E' )
            // If the route is not visited and is not already visited this goal, or the down location is already clean
            return goBack( beforeDirection, "Left", locationOfColumn, locationOfRow, goalNumbers, endMaze, ++time); // Change the direction and back to the right direction
        else {
            if ( beforeLink == 0 && endMaze.map[locationOfColumn][locationOfRow] == 'R' && endMaze.map[locationOfColumn - up][locationOfRow] == 'G' ) /* If the route is visited and the down direction is a goal and the link of before direction is 0 */ {
                if ( ( endMaze.map[locationOfColumn][locationOfRow + right] == 'R' && link("Decide", endMaze, locationOfColumn, locationOfRow + right) != 2 )
                    || ( endMaze.map[locationOfColumn][locationOfRow + left] == 'R' && link("Decide", endMaze, locationOfColumn, locationOfRow + left) != 2 ) )
                    endMaze.map[locationOfColumn][locationOfRow] = 'E'; // Mark the end map as cleared of the route
            }
            beforeDirection = "Right";
            locationOfColumn -= up;
            time = 1;
            return true; // Back to the down direction and find the path to the next goal with the right direction
        }
    }
}

void Maze::showMap() /* Show the map */ {
    for ( int i = 1 ; i <= column ; i++ ) {
        for ( int j = 1; j <= row ; j++  ) {
            if ( map[i][j] == 'A' )
                map[i][j] = 'G'; // Change the visited A to G
            cout << map[i][j];
        }
        cout << endl;
    }
}

int main() {

    int command = 0, goalNumber = 1;
    int row = 0, column = 0;
    string fileNumber, fileName;
    do {
        cout << "\n" << "*** Path Finding ***";
        cout << "\n" << "* 0. Quit          *";
        cout << "\n" << "* 1. One goal      *";
        cout << "\n" << "* 2. More goals    *";
        cout << "\n" << "********************";
        cout << "\n" << "Input a command(0 , 1, 2): ";
        cin >> command ; // Get the command
        if ( command == 0 ) // Quit
            break;
        else if ( ( command == 1 ) || ( command == 2 ) ) /* One goal or more goals */ {
            goalNumber = 1;
            cout << "\n" << "Input a file number (e.g., 101, 102,...): ";
            cin >> fileNumber ; // Get the file number
            fileName = ".\\input" + fileNumber + ".txt" ; // Get the file name
            fstream file;
            file.open( fileName.c_str() ); // Open the file
            if ( !file.is_open() ) // Check whether the file is open
                cout << "\ninput" << fileNumber << ".txt does not exist!" << endl;
            else {
                if ( command == 2 ) /* More goals */{
                    do {
                        cout << "\n" << "Number of G (goals): ";
                        cin >> goalNumber; // Get the number of goals
                        if ( goalNumber <= 0 || goalNumber > 100 ) // Check whether the number is in [1,100]
                            cout << "\n### The number must be in [1,100] ###\n";
                    } while ( goalNumber <= 0 || goalNumber > 100);
                }
                file >> row >> column; // Get the row and column
                file.close(); // Close the file
                Maze pathMaze( row, column ); // Create a maze
                pathMaze.inputMap( fileName ); // Input the map
                Maze endMaze( pathMaze ); // Create the other maze
                bool success = pathMaze.findThePathToGoals( "Right", 1, 1, goalNumber, endMaze, 0 ); // Find the path to the goals
                pathMaze.showMap(); // Show the map
                cout << endl;
                if ( success ) /* Check whether the path is found */ {
                    endMaze.showMap(); // Show the successful path
                    cout << endl;
                }
            }
        }
        else
            cout << endl << "Command does not exist!" << endl; // The command is not in [0,1,2]

    }while( true );

    return 0; // end

}
