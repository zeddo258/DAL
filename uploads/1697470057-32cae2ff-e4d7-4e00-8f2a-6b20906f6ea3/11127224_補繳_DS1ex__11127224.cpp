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
    int shortestStep = 0;
    vector<vector<char>> map;//移動過程的路徑
    vector<vector<char>> mapGoal;//成功抵達的路徑
    vector<vector<char>> mapRoad;
    vector<vector<char>> mapStart;
    vector<vector<char>> mapShortest;
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
            mapStart.push_back(map1);
            mapShortest.push_back(map1);
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
    bool isWall2(int nowX,int nowY){
        if (nowX <x && nowX >=0 &&nowY <y && nowY >= 0)
        {
            if (map[nowY][nowX]=='E'||map[nowY][nowX]=='G'||map[nowY][nowX]=='V'){
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

    bool MoveShortest(int nowX, int nowY, int shortest, int direction) {
        if (shortest >= shortestStep && shortestStep != 0)
        {
            return false;
        }//若該路徑步數已大於等於最短路徑步數則停止
        
        bool run = false;
        if (map[nowY][nowX] == 'G')
        {
            if (shortestStep > shortest || shortestStep == 0)
            {
                shortestStep = shortest;
                RestartShortest();
                return true;
            }
            else{
                return false;
            }
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
            if (i != 2)
            {
                /* code */
            }
            
            if( direction > 4 )
                direction = 1;//跑完一次右下左上便重複
            

            if (!isWall2(nowX +1, nowY ) && direction == 1&& i != 2) {
                if (MoveShortest(nowX+1, nowY, shortest+1, 1))
                {
                    mapShortest[nowY][nowX] = 'R';
                    run = true;
                }
            }//往右走
            else if (!isWall2(nowX, nowY-1 ) && direction == 2&& i != 2) {
                if (MoveShortest(nowX, nowY-1, shortest+1, 2))
                {
                    mapShortest[nowY][nowX] = 'R';
                    run = true;
                }
            }//往下走
            else if (!isWall2(nowX-1, nowY ) && direction == 3&& i != 2) {
                if (MoveShortest(nowX-1, nowY, shortest+1, 3))
                {
                    mapShortest[nowY][nowX] = 'R';
                    run = true;
                }
            }//往左走
            else if (!isWall2(nowX, nowY+1 ) && direction == 4&& i != 2) {
                if (MoveShortest(nowX, nowY+1, shortest+1, 4))
                {
                    mapShortest[nowY][nowX] = 'R';
                    run = true;
                }
            }//往上走
            direction = direction + 1;
        }//輪流走四個方位，且不走回頭路

        return run;
    }//找出最短路徑


    void printRoadMap(){
        for (int i = 0; i < y; i++)
        {
            cout << endl;    
            for (int j = 0; j < x; j++)
            {
                cout << mapRoad[i][j];
            }  
        }
        cout << endl;
    
    } //輸出路徑
    void printMap(){
        for (int i = 0; i < y; i++)
        {
            cout << endl;    
            for (int j = 0; j < x; j++)
            {
                cout << map[i][j];
            }  
        }
        cout << endl;
    
    } //輸出地圖
    void printGoalMap(){
        for (int i = 0; i < y; i++)
        {
            cout << endl;
            for (int j = 0; j < x; j++)
            {
                cout << mapGoal[i][j];
            }         
        }
        cout << endl;
    
    }//輸出達成路徑地圖
    void printShortestMap(){
        for (int i = 0; i < y; i++)
        {
            cout << endl;    
            for (int j = 0; j < x; j++)
            {
                cout << mapShortest[i][j];
            }  
        }
        cout << endl;
    
    }//輸出最短路徑地圖
    void Restart(){
        map.clear();
        mapGoal.clear();
        mapRoad.clear();
        for (int i = 0; i < y; i++)
        {
            map.push_back(mapStart[i]);
            mapGoal.push_back(mapStart[i]);
            mapRoad.push_back(mapStart[i]);
        }
    
    } //重設路徑地圖
    void RestartShortest(){
        mapShortest.clear();
        for (int i = 0; i < y; i++)
        {
            mapShortest.push_back(mapStart[i]);
        }
    
    }//重設最短路徑地圖
    void clr(){
        map.clear();
        mapGoal.clear();
        mapRoad.clear();
        mapShortest.clear();
        mapStart.clear();
    }//清除記憶體空間

    int getShortest(){
        return shortestStep;
    }//回傳最短路徑步數
  
};

bool isNumber(string str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false; 
        }
    }

    return true;

}//是否為數字

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
    int shortest;
    do
    {
        cout << endl << "***Path Finding***";
        cout << endl << "*0.Quit          *";
        cout << endl << "*1.One goal      *";
        cout << endl << "*2.More goals    *";
        cout << endl << "******************";
        cout << endl << "Input a command(0,1,2,3):";
        cin >> command;
        if ((command == '1')||(command == '2')||(command == '3')) {
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
                }//若是有路徑則輸出過程路徑及達成路徑
                else {
                    aMaze.printRoadMap();
                    cout << endl ;
                    aMaze.clr();
                }//否則輸出過程路徑
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
                        }//goal是否在指定範圍內
                        else{
                            cout << endl << "### The number must be in [1,100] ###";
                            cout << endl << "Number of G (goals):";
                            cin >> goalRead;
                        }//否則重新輸入
                    }//goal是否為數字
                    else {
                        cout << endl << "Number of G (goals):";
                        cin >> goalRead;
                    }//否則重新輸入
                }
                
                if (aMaze.Move(0,0,0,goal,1))
                {
                    aMaze.printRoadMap();
                    cout << endl ;
                    aMaze.printGoalMap();
                    cout << endl ;
                    aMaze.clr();
                }//是否達成目標
                else {
                    aMaze.printRoadMap();
                    cout << endl;
                    aMaze.clr();
                }
            }
            else if (command == '3'){
                if (aMaze.Move(0,0,0,1,1))
                {
                    aMaze.Restart();
                    if(aMaze.MoveShortest(0, 0,1,1)) {
                        shortest = aMaze.getShortest();
                        aMaze.printRoadMap();
                        cout << endl ;
                        aMaze.printShortestMap();
                        cout << endl;
                        cout << "Shortest path length = " << shortest;
                        aMaze.clr();
                    }//輸出最短路徑
                }//是否有路徑
                else {
                    aMaze.printRoadMap();
                    cout << endl;
                    cout << endl;
                    cout << "### There is no path to find a goal! ###";
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