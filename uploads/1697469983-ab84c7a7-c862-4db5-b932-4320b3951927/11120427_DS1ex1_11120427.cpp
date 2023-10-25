#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Maze {
public:
    bool loadMaze(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open the file." << endl;
            return false;
        }

        file >> cols_ >> rows_;


        maze_.resize(rows_, vector<char>(cols_, ' '));
        visited_maze_.resize(rows_, vector<char>(cols_, ' '));

        for (int i = 0; i < rows_; ++i) {
            string line;
            file >> line;
            for (int j = 0; j < cols_; ++j) {
                visited_maze_[i][j]=maze_[i][j] = line[j];
            }
        }

        return true;
    }
    bool isValidMove(int x, int y) {
        return (x >= 0 && x < rows_ && y >= 0 && y < cols_ && (maze_[x][y] == 'E' || maze_[x][y] == 'G'));
    }
    bool solution(int count){
        vector<vector<vector<char>>>maps(count,maze_);
        bool tag=0; 
        for(int i=0;i<count ;i++){
            tag=dfs(maps[i],0,0,0);//start at (0,0) at the next time
        }
        for(int i=0;i<rows_;i++){
            for(int j=0;j<cols_;j++){
                for(int k=0;k<count;k++){
                    if((maps[k][i][j]=='V'|| maps[k][i][j]=='R')&&visited_maze_[i][j]!='G')
                        visited_maze_[i][j]='V';
                }
            }
        }
        cout<<endl;
        printMaze(visited_maze_);//visited
        if(tag){//if solution is found
            for(int i=0;i<rows_;i++){
                for(int j=0;j<cols_;j++){
                    for(int k=0;k<count;k++){
                        if(maps[k][i][j]=='R' && maze_[i][j]!='G')
                            maze_[i][j]='R';
                    }
                }
            }
            cout<<endl;
            printMaze(maze_);
        }
        return 0;
    }
    bool dfs(vector<vector<char>> &map,int x, int y,int mode) {
        //reached the goal
        if (map[x][y] == 'G') {
            bool tag=0;
            for(int i=0;i<goals.size();i++)//check whether the (x,y) is already found
            {
                if(goals[i][0]==x && goals[i][1]==y)
                    tag=1;
            }
            if(tag==0){//if the (x,y) not found, push the new goal(G) to vector
                vector<int> tmp(2);
                tmp[0]=x;
                tmp[1]=y;
                goals.push_back(tmp);
                return true;
            }
        }

        //mark as visited
        map[x][y] = 'V';

        //right, down, left, up
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        
        int newX = x + dx[mode];
        int newY = y + dy[mode];
        int times=0;
        while (times!=4) { //if is a vaild move and not visited
            if(isValidMove(newX, newY) && map[newX][newY] != 'V'){
                if (dfs(map,newX, newY,mode)) {
                    //mark current cell as part of the correct route
                    if(map[x][y]!='G')
                        map[x][y] = 'R';
                    return true;
                }
            }
            else{
                mode=(mode+1)%4;
                newX = x + dx[mode];
                newY = y + dy[mode];
                times++;
            }
        }

        return false;
    }
    void printMaze() {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                cout << maze_[i][j];
            }
            cout << '\n';
        }
    }
    void printMaze(vector<vector<char>> map) {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                cout << map[i][j];
            }
            cout << '\n';
        }
    }

private:
    int rows_;
    int cols_;
    vector<vector<char>> maze_;
    vector<vector<char>> visited_maze_;
    vector<vector<int>>goals;

};

int main() {
    Maze maze;
    string filename;
    int command = 0;
    
    cout << endl << "***Path Finding***";
    cout << endl << "*0. Quit         *";
    cout << endl << "*1. One goal     *";
    cout << endl << "*2. More goals   *";
    cout << endl << "******************";
    cout << endl << "Input a command(0, 1, 2): ";
    cin >> command;

    while (command != 0) {
        switch (command) {
            case 1:
                // Execute task 1 (One goal)
                cout << "Enter the file number: ";
                cin >> filename;
                filename = "input" + filename + ".txt";
                maze.loadMaze(filename);
                maze.solution(1); // Assuming task 1 corresponds to goal count 1
                break;
            case 2:
                // Execute task 2 (More goals)
                int goalCount;
                cout << "Enter the goal count: ";
                cin >> goalCount;
                cout << "Enter the file number: ";
                cin >> filename;
                filename = "input" + filename + ".txt";
                maze.loadMaze(filename);
                maze.solution(goalCount);
                break;
            default:
                cout << "Invalid command." << endl;
                break;
        }

        // After executing the selected task, return to the main menu
        cout << endl << "Input a command(0, 1, 2): ";
        cin >> command;
    }
    system( "pause" ) ;
    return 0;
}