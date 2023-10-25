//11127151 楊少杰
//只完成任務1，任務2沒來得及做完
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class Maze
{
public:
    Maze(const string& filename);
    void executeCommand(int command);
    void printMaze();

private:
    int rows, cols;

    const int dx[4] = {0, 1, 0, -1};  // Define the movement rules in the x-direction
    const int dy[4] = {-1, 0, 1, 0};  // Define the movement rules in the y-direction

    vector<vector<char>> originalMaze; // Original maze map
    vector<vector<char>> visitedMaze;  // Maze map to record visited positions
    vector<vector<char>> pathMaze;     // Maze map to record the shortest path

    void findOneGoal();  // Find one goal in the maze
};

Maze::Maze(const string& filename)
{
    ifstream inputFile(filename);

    if (!inputFile)
    {
        cerr << "Error: Unable to open file." << endl;
        exit(1);
    }

    inputFile>>rows>>cols;

    for (int i = 0; i < rows; ++i)
    {
        vector<char> row;
        for (int j = 0; j < cols; ++j)
        {
            char cell;
            inputFile >> cell;
            row.push_back(cell);
        }

        originalMaze.push_back(row);
    }

    visitedMaze=originalMaze;

    inputFile.close();
}

void Maze::executeCommand(int command)
{
    if(command==1)
    {
        findOneGoal();  // Execute task 1, find one goal
        printMaze();    // Print the result
    }
}

void Maze::findOneGoal()
{
    int x = 0, y = 0; // Start position is the top-left corner
    int direction = 0; // Start direction is right
    while (visitedMaze[y][x] != 'G')
    {
        if (visitedMaze[y][x] == 'E')
        {
            visitedMaze[y][x] = 'V'; // Change 'E' to 'V' to mark as visited
        }
        int nx = x + dx[direction];
        int ny = y + dy[direction];
        if (nx >= 0 && ny >= 0 && nx < cols && ny < rows && visitedMaze[ny][nx] != 'O')
        {
            x = nx;
            y = ny;
        }
        else
        {
            direction = (direction + 1) % 4; // Turn direction: Right > Down > Left > Up
        }
    }

    pathMaze=visitedMaze;

    // Add code here to find the shortest path
    x = 0, y = 0;
    direction = 0;

    while (pathMaze[y][x] != 'G')
    {
        if (pathMaze[y][x] == 'V')
        {
            pathMaze[y][x] = 'R'; // Change 'V' to 'R' to mark as the shortest path
        }
        int nx = x + dx[direction];
        int ny = y + dy[direction];
        if (nx >= 0 && ny >= 0 && nx < cols && ny < rows && pathMaze[ny][nx] != 'O')
        {
            x = nx;
            y = ny;
        }
        else
        {
            direction = (direction + 1) % 4; // Turn direction: Right > Down > Left > Up
        }
    }
}

void Maze::printMaze()
{
    findOneGoal();

    // Print the visitedMaze and pathMaze
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << visitedMaze[i][j];
        }
        cout << endl;
    }

    cout<<endl;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << pathMaze[i][j];
        }
        cout << endl;
    }
}

int main()
{
    while(true)
    {
        int command;

        cout<<"--------------Command List---------------"<<endl;
        cout<<"0 - Exit | 1 - One goal | 2 - Multi goals"<<endl;

        cout<<endl<<"Enter the command(0, 1, or 2): ";
        cin>>command;

        if(command==0)
        {
            cout<<endl<<"Exiting the program..."<<endl;
            break;
        }
        else if(command==1||command==2)
        {
            string filename;
            cout << "Enter a maze file name: ";
            cin >> filename;

            Maze maze(filename);
            maze.executeCommand(command);
        }
        else
        {
            cout<<endl<<"Invalid command. Please enter 0, 1, or 2."<<endl<<endl;
        }
    }

    return 0;
}
