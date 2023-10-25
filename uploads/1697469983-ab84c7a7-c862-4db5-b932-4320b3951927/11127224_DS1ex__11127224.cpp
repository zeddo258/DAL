//11127224 許宥騏
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

class Maze {
    int x;
    int y;
    vector<vector<char>> map;//移動過程的路徑
    vector<vector<char>> mapGoal;//成功抵達的路徑
    vector<vector<char>> mapRoad;
public:

    void Set( ifstream & input)
    {
        input >> x >> y;
        for (int j = 0; j < y; j++)
        {
            vector<char> map1;
            char element;
            for (int i = 0; i < x; i++)
            {
                input >> element;
                map1.push_back(element);
            }
            map.push_back(map1);
            mapGoal.push_back(map1);
            mapRoad.push_back(map1);
        }
    }//儲存兩張地圖

    bool isWall(int nowX,int nowY){
        if (nowX <x && nowX >=0 &&nowY <y && nowY >= 0)
        {
            if (map[nowY][nowX]=='E'||map[nowY][nowX]=='G'){
                return false;
            }
        }
        
        return true;
        
    }//判斷是否可行

    bool Move(int nowX, int nowY, int goaltime, int achieve, int direction) {

        if (goaltime == achieve)
        {
            return true;
        }//完成目標次數
                
        
        if (map[nowY][nowX] == 'E'||map[nowY][nowX]=='G')
        {
            map[nowY][nowX] = 'V';
        }//移動路徑
        if (mapRoad[nowY][nowX] == 'E')
        {
            mapRoad[nowY][nowX] = 'V';
        }//移動路線


        for (int i = 0; i < 4; i++)
        {
            if( direction > 4 )
                direction = 1;//跑完一次右下左上便重複
            

            if (!isWall(nowX +1, nowY ) && direction == 1) {
                if (map[nowY][nowX+1] == 'G')
                {
                    goaltime = goaltime + 1;
                }
                if (Move(nowX+1, nowY, goaltime,achieve, 1))
                {
                    mapGoal[nowY][nowX] = 'R';
                    return true;
                }
            }//往右走
            else if (!isWall(nowX, nowY-1 ) && direction == 2) {
                if (map[nowY-1][nowX] == 'G')
                {
                    goaltime = goaltime + 1;
                }
                
                if (Move(nowX, nowY-1, goaltime,achieve, 2))
                {
                    mapGoal[nowY][nowX] = 'R';
                    return true;
                }
            }//往下走
            else if (!isWall(nowX-1, nowY ) && direction == 3) {
                if (map[nowY][nowX-1] == 'G')
                {
                    goaltime = goaltime + 1;
                }
                if (Move(nowX-1, nowY, goaltime,achieve, 3))
                {
                    mapGoal[nowY][nowX] = 'R';
                    return true;
                }
            }//往左走
            else if (!isWall(nowX, nowY+1 ) && direction == 4) {
                if (map[nowY+1][nowX] == 'G')
                {
                    goaltime = goaltime + 1;
                }
                if (Move(nowX, nowY+1, goaltime,achieve, 4))
                {
                    mapGoal[nowY][nowX] = 'R';
                    return true;
                }
            }//往上走
            direction = direction + 1;
        }//輪流走四個方位

        return false;//都不行就直接回傳
    }
    void printRoadMap(){
        for (int i = 0; i < y; i++)
        {
            cout << endl;    
            for (int j = 0; j < x; j++)
            {
                cout << mapRoad[i][j];
            }  
        }
    
    } 
    void printMap(){
        for (int i = 0; i < y; i++)
        {
            cout << endl;    
            for (int j = 0; j < x; j++)
            {
                cout << map[i][j];
            }  
        }
    
    } 
    void printGoalMap(){
        for (int i = 0; i < y; i++)
        {
            cout << endl;
            for (int j = 0; j < x; j++)
            {
                cout << mapGoal[i][j];
            }         
        }
    
    }
    void clr(){
        map.clear();
        mapGoal.clear();
        mapRoad.clear();
    }
  
};

bool isNumber(string str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false; 
        }
    }

    return true;

}

int main (void) {
    char command ='0' ;
    string filename;
    string length;
    string width;
    Maze aMaze;
    string goalRead ;
    int goal = 1;
    int check =0;
    ifstream file;
    do
    {
        cout << endl << "***Path Finding***";
        cout << endl << "*0.Quit          *";
        cout << endl << "*1.One goal      *";
        cout << endl << "*2.More goals    *";
        cout << endl << "******************";
        cout << endl << "Input a command(0,1,2):";
        cin >> command;
        if ((command == '1')||(command == '2')) {
            cout << endl << "Input a file number(e.g.,201,202,...):";
            cin >> filename;
            file.open( "input" + filename + ".txt");
            if ( !file.is_open() ) {
                cout << "input" + filename +".txt does not exist!";
                continue;
            } // 如果沒讀到資料就跳出
            aMaze.Set(file);//設定地圖
            file.close();
            if (command == '1'){
                goal = 1;
                if (aMaze.Move(0,0,0,goal,1))
                {
                    aMaze.printRoadMap();
                    cout << endl;
                    aMaze.printGoalMap();
                    cout << endl ;
                    aMaze.clr();
                }
                else {
                    aMaze.printRoadMap();
                    cout << endl ;
                    aMaze.clr();
                }
            }
            else if (command == '2')
            {
                cout << endl << "Number of G (goals):";
                cin >> goalRead;
                
                while (check == 0)
                {
                    if(isNumber(goalRead)) {
                        goal = atoi(goalRead.c_str());
                        if (goal >0 && goal <= 100)
                        {
                            check =1;
                        }
                        else{
                            cout << endl << "### The number must be in [1,100] ###";
                            cout << endl << "Number of G (goals):";
                            cin >> goalRead;
                        }
                    }
                    else {
                        cout << endl << "Number of G (goals):";
                        cin >> goalRead;
                    }
                }
                
                if (aMaze.Move(0,0,0,goal,1))
                {
                    aMaze.printRoadMap();
                    cout << endl ;
                    aMaze.printGoalMap();
                    cout << endl ;
                    aMaze.clr();
                }
                else {
                    aMaze.printRoadMap();
                    cout << endl;
                    aMaze.clr();
                }
            }
            

        }
        else if (command=='0')
            break;
        else {
            cout << endl << "Cammand does not exist!" << endl;
            continue;
        }
    } while (true);
    return 0;

}