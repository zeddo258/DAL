#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


class Maze
{

public:
    Maze(const string& filename,int command);
    int rows;
    int cols;
    int goal;
    int startX = 0;
    int startY = 0;
    int tempX ;
    int tempY;
    vector<vector<char>> grid; //二維向量//

    void solve();
    void printMaze();
    void findRoute() ;
    bool isValid(int x, int y);
    bool IsValid(int x, int y) ;
    bool moveRight(int& x, int& y);
    bool moveDown(int& x, int& y);
    bool moveLeft(int& x, int& y);
    bool moveUp(int& x, int& y);


    void solvemoregoals(int& N) ;
    bool moremoveRight(int& x, int& y, int& N);
    bool moremoveDown(int& x, int& y, int& N);
    bool moremoveLeft(int& x, int& y, int& N);
    bool moremoveUp(int& x, int& y, int& );

};

Maze::Maze(const string& filename, int command )
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Failed to open the file." << endl;
        exit(1);
    }

    if(command == 1)
    {

        file >> rows >> cols; // 7、9
        grid.resize(cols, vector<char>(rows)); //向量大小

        for (int i = 0; i < cols; ++i)
        {
            for (int j = 0; j < rows; ++j)
            {
                file >> grid[i][j];
            }
        }

    }
    else if (command == 2 )
    {

        file >> cols >> rows; // 7、9
        grid.resize(rows, vector<char>(cols)); //向量大小

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                file >> grid[i][j];
            }
        }
        goal = 0 ;
    }
    file.close();
}



void Maze::printMaze()
{
    int i, j  ;

    for ( i = 0 ; i < cols; ++i)
    {
        for ( j = 0 ; j < rows; ++j)
        {
            cout << grid[i][j];
        }
        j = 0 ;
        cout << endl;
    }
}

void Maze::findRoute()

{
    int i, j  ;

    for ( i = 0 ; i < cols; ++i)
    {
        for ( j = 0 ; j < rows; ++j)
        {
            if( grid[i][j] == 'V' )
            {
                grid[i][j] = 'R' ;
            }
        }
        j = 0 ;
    }


}

bool Maze::isValid(int x, int y)
{
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

bool Maze::IsValid(int x, int y)
{
    return x >= 0 && x < cols && y >= 0 && y < rows;
}

bool Maze::moveRight(int& x, int& y)
{
    int newX = x;
    int newY = y + 1;

    while(isValid(newX, newY))
    {
        if ( grid[newX][newY] == 'E')
        {
            grid[newX][newY] = 'V';
            x = newX;
            y = newY;
        }

        else if (grid[newX][newY] == 'G')
        {

            printMaze(); // 輸出結果
            findRoute();
            cout << endl ;
            printMaze();
            return 0; // 不要結束程式的執行，返回 true
        }

        else
        {
            return false ;
        }
        newX = x;
        newY = y + 1;
    }
    return false;
}

bool Maze::moveDown(int& x, int& y)
{
    int newX = x + 1;
    int newY = y;
    while(isValid(newX, newY))
    {
        if ( grid[newX][newY] == 'E')
        {
            grid[newX][newY] = 'V';
            x = newX;
            y = newY;

        }

        else if (grid[newX][newY] == 'G')
        {

            printMaze(); // 輸出結果
            findRoute();
            cout << endl ;
            printMaze();
            return 0; // 不要結束程式的執行，返回 true
        }

        else
        {
            return false ;
        }
        newX = x + 1 ;
        newY = y ;
    }
    return false;
}

bool Maze::moveLeft(int& x, int& y)
{
    int newX = x;
    int newY = y - 1;
    while(isValid(newX, newY))
    {
        if ( grid[newX][newY] == 'E')
        {
            grid[newX][newY] = 'V';
            x = newX;
            y = newY;

        }

        else if (grid[newX][newY] == 'G')
        {

            printMaze(); // 輸出結果
            findRoute();
            cout << endl ;
            printMaze();
            return 0; // 不要結束程式的執行，返回 true
        }

        else
        {
            return false ;
        }
        newX = x;
        newY = y - 1;
    }
    return false;
}

bool Maze::moveUp(int& x, int& y)
{
    int newX = x - 1;
    int newY = y;
    while(isValid(newX, newY))
    {
        if ( grid[newX][newY] == 'E')
        {
            grid[newX][newY] = 'V';
            x = newX;
            y = newY;

        }

        else if (grid[newX][newY] == 'G')
        {

            printMaze(); // 輸出結果
            findRoute();
            cout << endl ;
            printMaze();
            return 0; // 不要結束程式的執行，返回 true
        }

        else
        {
            return false ;
        }
        newX = x - 1;
        newY = y ;
    }
    return false;
}



void Maze::solve()
{
    int startX = 0;
    int startY = 0;

    grid[startX][startY] = 'V' ;
    while (true)
    {
        // 向右移動
        if (moveRight(startX, startY))
        {
            continue;
        }
        // 向下移動
        if (moveDown(startX, startY))
        {
            continue;
        }
        // 向左移動
        if (moveLeft(startX, startY))
        {
            continue;
        }
        // 向上移動
        if (moveUp(startX, startY))
        {
            continue;
        }

        if (moveRight(startX, startY))
        {
            continue;
        }

        if (moveDown(startX, startY))
        {
            continue;
        }


        if (moveLeft(startX, startY))
        {
            continue;
        }
        // 向上移動

        if (moveUp(startX, startY))
        {
            continue;
        }



        // 如果沒有有效移動，則已經無路可走
        break;
    }
}
//////////////////////////////////////////////////////////////////////////


bool Maze::moremoveRight(int& x, int& y, int& N)
{
    int newX = x;
    int newY = y + 1;
    int X ;
    while(IsValid(newX, newY))
    {
        if ( grid[newX][newY] == 'E')
        {
            grid[newX][newY] = 'V';
            x = newX;
            y = newY;
        }

        else if (grid[newX][newY] == 'G'  )
        {
            tempX = newX ;
            tempY = newY ;
            goal++ ;

            if(goal == N)
            {
                printMaze(); // 輸出結果
                findRoute();
                cout << endl ;
                printMaze();
                return 0; // 不要結束程式的執行，返回 true
            }
            x = newX;
            y = newY;

        }

        else if (grid[newX][newY] == 'O' )
        {
            return false ;
        }
        newX = x;
        newY = y + 1;
        if(!IsValid(newX, newY))
        {
            return false ;
        }
    }
}

bool Maze::moremoveDown(int& x, int& y, int& N)
{
    int newX = x + 1;
    int newY = y;
    int X ;
    while(IsValid(newX, newY))
    {
        if ( grid[newX][newY] == 'E' )
        {
            grid[newX][newY] = 'V';
            x = newX;
            y = newY;

        }

        else if (grid[newX][newY] == 'G'   )
        {
            tempX = newX ;
            tempY = newY ;
            goal++ ;


            if(goal == N)
            {
                printMaze(); // 輸出結果
                findRoute();
                cout << endl ;
                printMaze();
                return 0; // 不要結束程式的執行，返回 true
            }
            x = newX;
            y = newY;

        }


        else if (grid[newX][newY] == 'O' )
        {
            return false ;
        }
        newX = x + 1 ;
        newY = y ;
        if(!IsValid(newX, newY))
        {
            return false ;
        }
    }
}

bool Maze::moremoveLeft(int& x, int& y, int& N)
{
    int newX = x;
    int newY = y - 1;
    int X ;
    while(IsValid(newX, newY))
    {
        if ( grid[newX][newY] == 'E')
        {
            grid[newX][newY] = 'V';
            x = newX;
            y = newY;

        }

        else if (grid[newX][newY] == 'G' )
        {
            tempX = newX ;
            tempY = newY ;
            goal++ ;
            if(goal == N)
            {

                findRoute();
                cout << endl ;
                printMaze();
                return 0; // 不要結束程式的執行，返回 true
            }
            x = newX;
            y = newY;
        }

        else if (grid[newX][newY] == 'O' )
        {
            return false ;
        }

        newX = x;
        newY = y - 1 ;

        if(!IsValid(newX, newY))
        {
            return false ;
        }
    }
}

bool Maze::moremoveUp(int& x, int& y, int& N)
{
    int newX = x - 1;
    int newY = y;
    int X ;
    while(IsValid(newX, newY))
    {
        if ( grid[newX][newY] == 'E')
        {
            grid[newX][newY] = 'V';
            x = newX;
            y = newY;

        }

        else if (grid[newX][newY] == 'G'  )
        {
            tempX = newX ;
            tempY = newY ;
            goal++ ;


            if(goal == N)
            {

                printMaze(); // 輸出結果
                findRoute(); //換
                cout << endl ;
                printMaze();
                return 0; // 不要結束程式的執行，返回 true
            }
            x = newX;
            y = newY;
        }

        else if (grid[newX][newY] == 'O' )
        {
            return false ;
        }
        newX = x - 1;
        newY = y ;
        if(!IsValid(newX, newY))
        {
            return false ;
        }
    }
}




void Maze::solvemoregoals(int& N )
{

    grid[startX][startY] = 'V' ;
    while (true)
    {
        // 向右移動
        if (moremoveRight(startX, startY, N))
        {
            continue;
        }
        // 向下移動
        if (moremoveDown(startX, startY, N))
        {
            continue;
        }
        // 向左移動
        if (moremoveLeft(startX, startY, N))
        {
            continue;
        }
        // 向上移動
        if (moremoveUp(startX, startY, N))
        {
            continue;
        }

        if (moremoveRight(startX, startY, N))
        {
            continue;
        }

        if (moremoveDown(startX, startY, N))
        {
            continue;
        }


        if (moremoveLeft(startX, startY, N))
        {
            continue;
        }

        if (moremoveUp(startX, startY, N))
        {
            continue;
        }

        break;
    }
}


int main()
{
    int command = 0 ;
    int N ;

    do
    {
        string filename ;
        cout << endl <<"***Path Finding***" ;
        cout << endl <<"* 0. Quit          *" ;
        cout << endl <<"* 1. One goal      *" ;
        cout << endl <<"* 2. More goals    *" ;
        cout << endl <<"********************" ;
        cout << endl <<"Input a command(0, 1, 2):" ;

        cin >> command ;

        if((command == 1 ) || (command == 2))
        {
            cout << "Input a file number:" ;
            cin >> filename ;
            filename = "input" + filename + ".txt" ;

            if( command == 1 )
            {
                Maze maze(filename,command) ;
                maze.solve() ;
            }

            else if( command == 2 )
            {
                Maze maze(filename,command) ;
                cout << "Number of G (goals):" ;
                cin >> N ;
                maze.solvemoregoals(N) ;

            }
        }

        else if (!command)
            break ;

        else
            cout << "Command does not exist!" << endl ;
    }
    while(true) ;

    system("pause") ;
    return 0 ;

}

