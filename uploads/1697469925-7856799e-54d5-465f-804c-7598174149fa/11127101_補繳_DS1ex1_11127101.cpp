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
    bool findThePathToGoals( string beforeDirection, int locationOfColumn, int locationOfRow, int goalNumbers, Maze &endMaze, int time, int command ); // Finding the path to goals
    int link( string beforeDirection, Maze endMaze, int locationOfColumn, int locationOfRow ); // Count the number of links to this point
    bool goBack( string &beforeDirection, string doDirection, int &locationOfColumn, int &locationOfRow, int &goalNumbers, Maze &endMaze, int &time, int command ); // Back tracking
    void showMap(); // Showing the map
    bool findTheShortestPath( string beforeDirection, int locationOfColumn, int locationOfRow, int goalNumbers, Maze &endMaze ); // Finding the shortest path
    void shortestPath(); // Showing the shortest path

private:

    int row; // The row
    int column; // The column
    vector<vector <char> > map; // Storing the map
    vector<vector <int> > steps;
    int right = 1, left = -1; // The row direction
    int up = -1, down = 1; // The column direction
    int goalOfColumn, goalOfRow; // The shortest goal location
    int currentColumn, currentRow; // The current location
    string direction; // The direction
    int shortestSteps; // The shortest steps

};

void Maze::inputMap( string fileName ) /* Reading the map */ {

    int unUse; // The row and column;
    map.resize( column + 2, vector<char>( row + 2, 'W')); // Initializing the map
    steps.resize( column + 2, vector<int>( row + 2, 1));
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

bool Maze::findThePathToGoals( string beforeDirection, int locationOfColumn, int locationOfRow, int goalNumbers, Maze &endMaze, int time, int command ) /* Finding the path to goals */ {

    if ( map[locationOfColumn][locationOfRow] == 'G' || ( command == 3 && map[locationOfColumn][locationOfRow] == 'A' && steps[locationOfColumn][locationOfRow] < shortestSteps ) ) /* If the goal is found or the last goal is find the shortest path */ {
        if ( goalNumbers == 1 || command == 3 ) /* If there just last one goal */ {
            map[locationOfColumn][locationOfRow] = 'A'; // Mark the goal as visited
            goalOfColumn = locationOfColumn;
            goalOfRow = locationOfRow;
            direction = beforeDirection;
            return true;
        }
        else {
            map[locationOfColumn][locationOfRow] = 'A'; // Mark the goal as visited
            return findThePathToGoals( beforeDirection, locationOfColumn, locationOfRow, goalNumbers - 1, endMaze, 1, command ); // Find the path to the next goal
        }
    }
    else if ( time == 5 ) /* Time out of the four directions */ {
        if ( map[locationOfColumn][locationOfRow] != 'A' && map[locationOfColumn][locationOfRow] != 'G' ) // If the goal is not visited
            map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
        if ( goBack( beforeDirection, beforeDirection, locationOfColumn, locationOfRow, goalNumbers, endMaze , time, command ) ) // If the back track is successful
            return findThePathToGoals( beforeDirection, locationOfColumn, locationOfRow, goalNumbers, endMaze, time, command ); // Keep searching
        else // If the back track is failed meaning the number of goals will not be found successfully
            return false;
    }
    else if ( beforeDirection == "Right" ) /* Find the path to the right direction */{
        if ( map[locationOfColumn][locationOfRow + right] == 'E' || map[locationOfColumn][locationOfRow + right] == 'G' ) /* If the route is not visited or the goal */{
            if ( map[locationOfColumn][locationOfRow] != 'A' ) /* If the route is not visited */ {
                map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
                endMaze.map[locationOfColumn][locationOfRow] = 'R'; // Mark the end map as visited
            }
            steps[locationOfColumn][locationOfRow + right] = steps[locationOfColumn][locationOfRow] + 1; // Update the steps
            if ( command == 3 && steps[locationOfColumn][locationOfRow + right] >= shortestSteps ) /* If the steps is longer than the shortest steps */{
                currentColumn = locationOfColumn;
                currentRow = locationOfRow;
                direction = beforeDirection;
                return false;
            }

            return findThePathToGoals("Right", locationOfColumn, locationOfRow + right, goalNumbers, endMaze, 1, command ); // Find the path to the next goal
        }
        else if ( command == 3 && ( map[locationOfColumn][locationOfRow + right] == 'A' || map[locationOfColumn][locationOfRow + right] == 'V' ) && steps[locationOfColumn][locationOfRow + right] > steps[locationOfColumn][locationOfRow] + 1 && steps[locationOfColumn][locationOfRow] + 1 < shortestSteps ) {
            /* If the right location has been visited and the steps is shorter than the shortest steps also the original steps is longer than the current steps */
            if ( map[locationOfColumn][locationOfRow] != 'A' ) /* If the route is not visited */ {
                map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
                endMaze.map[locationOfColumn][locationOfRow] = 'R'; // Mark the end map as visited
            }
            steps[locationOfColumn][locationOfRow + right] = steps[locationOfColumn][locationOfRow] + 1; // Update the steps
            return findThePathToGoals("Right", locationOfColumn, locationOfRow + right, goalNumbers, endMaze, 1, command ); // Find the path to the next goal
        }
        else
            return findThePathToGoals("Down", locationOfColumn, locationOfRow, goalNumbers, endMaze, ++time, command ); // Change the direction and find the path

    }
    else if ( beforeDirection == "Down" ) /* Find the path to the down direction */ {
        if ( map[locationOfColumn + down][locationOfRow] == 'E' || map[locationOfColumn + down][locationOfRow] == 'G' ) /* If the route is not visited or the goal */ {
            if ( map[locationOfColumn][locationOfRow] != 'A' ) /* If the route is not visited */{
                map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
                endMaze.map[locationOfColumn][locationOfRow] = 'R'; // Mark the end map as visited
            }
            steps[locationOfColumn + down][locationOfRow] = steps[locationOfColumn][locationOfRow] + 1; // Update the steps
            if ( command == 3 && steps[locationOfColumn + down][locationOfRow] >= shortestSteps ) /* If the steps is longer than the shortest steps */ {
                currentColumn = locationOfColumn;
                currentRow = locationOfRow;
                direction = beforeDirection;
                return false;
            }

            return findThePathToGoals("Down", locationOfColumn + down, locationOfRow, goalNumbers, endMaze, 1, command ); // Find the path to the next goal
        }
        else if ( command == 3 && ( map[locationOfColumn +down][locationOfRow] == 'A' || map[locationOfColumn +down][locationOfRow] == 'V' ) && steps[locationOfColumn +down][locationOfRow] > steps[locationOfColumn][locationOfRow] + 1 && steps[locationOfColumn][locationOfRow] + 1 < shortestSteps ) {
            /* If the down location has been visited and the steps is shorter than the shortest steps also the original steps is longer than the current steps */
            if ( map[locationOfColumn][locationOfRow] != 'A' ) /* If the route is not visited */ {
                map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
                endMaze.map[locationOfColumn][locationOfRow] = 'R'; // Mark the end map as visited
            }
            steps[locationOfColumn +down][locationOfRow] = steps[locationOfColumn][locationOfRow] + 1; // Update the steps
            return findThePathToGoals("Down", locationOfColumn + down, locationOfRow, goalNumbers, endMaze, 1, command ); // Find the path to the next goal
        }
        else
            return findThePathToGoals("Left", locationOfColumn, locationOfRow, goalNumbers, endMaze, ++time, command ); // Change the direction and find the path
    }
    else if ( beforeDirection == "Left" ) /* Find the path to the left direction */ {
        if ( map[locationOfColumn][locationOfRow + left] == 'E' || map[locationOfColumn][locationOfRow + left] == 'G' ) /* If the route is not visited or the goal */ {
            if ( map[locationOfColumn][locationOfRow] != 'A' ) /* If the route is not visited */{
                map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
                endMaze.map[locationOfColumn][locationOfRow] = 'R'; // Mark the end map as visited
            }
            steps[locationOfColumn][locationOfRow + left] = steps[locationOfColumn][locationOfRow] + 1; // Update the steps
            if ( command == 3 && steps[locationOfColumn][locationOfRow + left] >= shortestSteps ) /* If the steps is longer than the shortest steps */ {
                currentColumn = locationOfColumn;
                currentRow = locationOfRow;
                direction = beforeDirection;
                return false;
            }

            return findThePathToGoals("Left", locationOfColumn, locationOfRow + left, goalNumbers, endMaze, 1, command ); // Find the path to the next goal
        }
        else if ( command == 3 && ( map[locationOfColumn][locationOfRow + left] == 'A' || map[locationOfColumn][locationOfRow + left] == 'V' ) && steps[locationOfColumn][locationOfRow + left] > steps[locationOfColumn][locationOfRow] + 1 && steps[locationOfColumn][locationOfRow] + 1 < shortestSteps ) {
            /* If the left location has been visited and the steps is shorter than the shortest steps also the original steps is longer than the current steps */
            if ( map[locationOfColumn][locationOfRow] != 'A' ) /* If the route is not visited */ {
                map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
                endMaze.map[locationOfColumn][locationOfRow] = 'R'; // Mark the end map as visited
            }
            steps[locationOfColumn][locationOfRow + left] = steps[locationOfColumn][locationOfRow] + 1; // Update the steps
            return findThePathToGoals("Left", locationOfColumn, locationOfRow + left, goalNumbers, endMaze, 1, command ); // Find the path to the next goal
        }
        else
            return findThePathToGoals("Up", locationOfColumn, locationOfRow, goalNumbers, endMaze, ++time, command ); // Change the direction and find the path

    }
    else if ( beforeDirection == "Up" ) /* Find the path to the up direction */ {
        if ( map[locationOfColumn + up][locationOfRow] == 'E' || map[locationOfColumn + up][locationOfRow] == 'G' ) /* If the route is not visited or the goal */ {
            if ( map[locationOfColumn][locationOfRow] != 'A' ) /* If the route is not visited */ {
                map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
                endMaze.map[locationOfColumn][locationOfRow] = 'R'; // Mark the end map as visited
            }
            steps[locationOfColumn + up][locationOfRow] = steps[locationOfColumn][locationOfRow] + 1; // Update the steps
            if ( command == 3 && steps[locationOfColumn + up][locationOfRow] >= shortestSteps ) /* If the steps is longer than the shortest steps */ {
                currentColumn = locationOfColumn;
                currentRow = locationOfRow;
                direction = beforeDirection;
                return false;

            }
            return findThePathToGoals("Up", locationOfColumn + up, locationOfRow, goalNumbers, endMaze, 1, command ); // Find the path to the next goal
        }
        else if ( command == 3 && ( map[locationOfColumn +up][locationOfRow] == 'A' || map[locationOfColumn +up][locationOfRow] == 'V' ) && steps[locationOfColumn +up][locationOfRow] > steps[locationOfColumn][locationOfRow] + 1 && steps[locationOfColumn][locationOfRow] + 1 < shortestSteps ) {
            /* If the up location has been visited and the steps is shorter than the shortest steps also the original steps is longer than the current steps */
            if ( map[locationOfColumn][locationOfRow] != 'A' ) /* If the route is not visited */ {
                map[locationOfColumn][locationOfRow] = 'V'; // Mark the route as visited
                endMaze.map[locationOfColumn][locationOfRow] = 'R'; // Mark the end map as visited
            }
            steps[locationOfColumn +up][locationOfRow] = steps[locationOfColumn][locationOfRow] + 1; // Update the steps
            return findThePathToGoals("Up", locationOfColumn + up, locationOfRow, goalNumbers, endMaze, 1, command ); // Find the path to the next goal
        }
        else
            return findThePathToGoals("Right", locationOfColumn, locationOfRow, goalNumbers, endMaze, ++time, command ); // Change the direction and find the path
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

bool Maze::goBack( string &beforeDirection, string doDirection, int &locationOfColumn, int &locationOfRow, int &goalNumbers, Maze &endMaze, int &time, int command ) /* Back tracking and clean the wrong route */ {

    if ( command == 3 ) // If the command is 3, means is time to find the shortest steps
            endMaze.map[locationOfColumn][locationOfRow] = 'E'; // Mark the end map as cleared
    int currentLink = link( "NULL", endMaze, locationOfColumn, locationOfRow ); // Count the number of links to this point
    int beforeLink = link( doDirection, endMaze, locationOfColumn, locationOfRow ); // Count the number of links to before point
    if ( time == 9 || endMaze.map[1][1] == 'E' ) /* Time out of the four directions or clean to the start point */
        return false;
    else if ( doDirection == "Right" ) /* Find the back path to the left direction */{
        if ( map[locationOfColumn][locationOfRow] != 'A' && currentLink < 2  ) // If the route is already visited or the number of links is less than two
            endMaze.map[locationOfColumn][locationOfRow] = 'E'; // Mark the end map as cleared of the route
        if ( ( map[locationOfColumn][locationOfRow - right] != 'V' && map[locationOfColumn][locationOfRow - right] != 'A' ) || endMaze.map[locationOfColumn][locationOfRow - right] == 'E' ) {
            // If the route is not visited and is not already visited this goal, or the left location is already clean
            time++;
            return goBack( beforeDirection, "Up", locationOfColumn, locationOfRow, goalNumbers, endMaze, time, command ); // Change the direction and back to the down direction
        }
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
        if ( ( map[locationOfColumn - down][locationOfRow] != 'V' && map[locationOfColumn - down][locationOfRow] != 'A') || endMaze.map[locationOfColumn - down][locationOfRow] == 'E' ) {
            // If the route is not visited and is not already visited this goal, or the up location is already clean
            time++;
            return goBack( beforeDirection, "Right", locationOfColumn, locationOfRow, goalNumbers, endMaze, time, command); // Change the direction and back to the left direction
        }
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
        if ( ( map[locationOfColumn][locationOfRow - left] != 'V' && map[locationOfColumn][locationOfRow - left] != 'A' ) || endMaze.map[locationOfColumn][locationOfRow - left] == 'E' ) {
            // If the route is not visited and is not already visited this goal, or the right location is already
            time++;
            return goBack( beforeDirection, "Down", locationOfColumn, locationOfRow, goalNumbers, endMaze, time, command); // Change the direction and back to the up direction
        }
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
        if ( ( map[locationOfColumn - up][locationOfRow] != 'V' && map[locationOfColumn - up][locationOfRow] != 'A' ) || endMaze.map[locationOfColumn - up][locationOfRow] == 'E' ) {
            // If the route is not visited and is not already visited this goal, or the down location is already clean
            time++;
            return goBack( beforeDirection, "Left", locationOfColumn, locationOfRow, goalNumbers, endMaze, time, command); // Change the direction and back to the right direction
        }
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
bool Maze::findTheShortestPath( string beforeDirection, int locationOfColumn, int locationOfRow, int goalNumbers, Maze &endMaze ) /* Find the shortest path */ {
    int time = 4, locationOfColumn1 = locationOfColumn, locationOfRow1 = locationOfRow;
    int lastColumn, lastRow;
    string doDirection = beforeDirection;
    Maze bridge( endMaze );
    bool success = findThePathToGoals( beforeDirection, locationOfColumn1, locationOfRow1, 1, endMaze, 0, 1 ); // If find the path to the goal
    if ( success ) /* If find the path to the goal success */ {
        bridge.map = endMaze.map; // Copy the end map to the bridge map
        shortestSteps = steps[goalOfColumn][goalOfRow]; // Save the shortest steps
        locationOfColumn1 = goalOfColumn;
        locationOfRow1 = goalOfRow;
        lastColumn = goalOfColumn;
        lastRow = goalOfRow;
        doDirection = direction;
        goBack( doDirection, doDirection, locationOfColumn1, locationOfRow1, goalNumbers, endMaze, time, 3); // Find the back path
        while ( goBack( doDirection, doDirection, locationOfColumn1, locationOfRow1, goalNumbers, endMaze, time, 3) ) /* Find the back path until the end */ {
            if ( findThePathToGoals( doDirection, locationOfColumn1, locationOfRow1, 1, endMaze, 1, 3 ) ) /* If find the path to the goal with the shorter steps */ {
                locationOfColumn1 = goalOfColumn;
                locationOfRow1 = goalOfRow;
                doDirection = direction;
            }
            else {
                locationOfColumn1 = currentColumn;
                locationOfRow1 = currentRow;
                doDirection = direction;
            }
            if ( steps[goalOfColumn][goalOfRow] < shortestSteps ) /* If we find the shorter steps */ {
                shortestSteps = steps[goalOfColumn][goalOfRow]; // Save the shorter steps
                lastColumn = goalOfColumn;
                lastRow = goalOfRow;
                bridge.map = endMaze.map; // Copy the shorter steps map to the bridge map
            }
            time = 4;
        }
    }
    endMaze.map = bridge.map; // Copy back
    for ( int i = 1 ; i <= column ; i++ ) {
        for ( int j = 1; j <= row ; j++  ) {
            if ( map[i][j] == 'A' )
                endMaze.map[i][j] = 'G'; // Filling the G
        }
    }
    return success;
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

void Maze::shortestPath() {
    cout << "\nShortest path length = " << steps[goalOfColumn][goalOfRow]; // Show the shortest path
}

int main() {

    int command = 0, goalNumber = 1;
    int row = 0, column = 0;
    bool success = false;
    string fileNumber, fileName;
    do {
        cout << "\n" << "*** Path Finding ***";
        cout << "\n" << "* 0. Quit          *";
        cout << "\n" << "* 1. One goal      *";
        cout << "\n" << "* 2. More goals    *";
        cout << "\n" << "* 3. Shortest path *";
        cout << "\n" << "********************";
        cout << "\n" << "Input a command(0 , 1, 2, 3): ";
        cin >> command ; // Get the command
        if ( command == 0 ) // Quit
            break;
        else if ( ( command == 1 ) || ( command == 2 ) || ( command == 3 ) ) /* One goal or more goals or shortest path */ {
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
                if ( command == 3 ) /* Shortest path */
                    success = pathMaze.findTheShortestPath( "Right", 1, 1, goalNumber, endMaze ); // Find the shortest path
                else
                    success = pathMaze.findThePathToGoals( "Right", 1, 1, goalNumber, endMaze, 0, 1 ); // Find the path to the goals
                pathMaze.showMap(); // Show the map
                cout << endl;
                if ( success && command == 3 ) /* Check whether the path is found */ {
                    endMaze.showMap(); // Show the successful path
                    cout << endl;
                    pathMaze.shortestPath();
                }
                else if ( success ) {
                    endMaze.showMap(); // Show the successful path
                    cout << endl;
                }
                else if ( !success && command == 3 )
                    cout << "\n### There is no path to find a goal! ###"; // The path is not found
            }
        }
        else
            cout << endl << "Command does not exist!" << endl; // The command is not in [0,1,2]

    }while( true );

    return 0; // end

}
