// 11127149 李後霆
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

enum Mode {aGoal, nGoal};                                       // 兩種模式: { 找一個終點, 找多個終點 }
enum Direction { Right, Down, Left, Up };                       // 四種方向: { 右, 下, 左, 上 }
typedef vector<string> MazeType;                                
typedef vector<int> Location;
typedef vector<Location> Path;
typedef vector<int> Scope;



// 迷宮類別
class Maze
{
    protected:                                                  
        MazeType maze;                                          // 二維迷宮陣列
        Scope scope;                                            // 迷宮範圍 { 垂直範圍, 水平範圍 }
        int goal;                                               // 尋找的終點數量
        Location location;                                      // 位置 { 垂直座標(y軸), 水平座標(x軸) }
        Path path;                                              // 最快找到終點的的路徑
        Path alfgoal;                                           // 已找到的終點位置
        Direction direction;                                    // 偵測方向
  
    public:
        // 建構類別
        Maze();                                                 // 建構類別,初始化

        Maze( const Maze& );                                    // 建構類別,複製另一類別資料

        // 讀取資料
        bool InputMaze( string, Mode );                         // 讀入迷宮資料並儲存,成功回傳true,失敗輸出錯誤資訊並回傳false

        void setMaze( MazeType, int, int, int );                // 儲存資料 { 二維迷宮陣列, 尋找的終點數量, 垂直最大範圍, 水平最大範圍 }

        bool isDight( string );                                 // 判斷輸入是否為整數.正確回傳true,錯誤回傳false
        
        bool formatCheck( string );                             // 字串格式檢查.正確回傳true,錯誤回傳false
        

        // 尋找終點
        bool FindGoal( Maze& );                                 // 尋找終點.成功回傳true,失敗回傳false

        bool forward(int);                                      // 朝偵測方向前進.成功回傳true,失敗回傳false

        Location way();                                         // 根據偵測方向回傳移動的數值

        void changeWay();                                       // 根據偵測方向,順時鐘90度改變偵測方向

        void setRPath( Path );                                  // 將最快找到終點的的路徑複製到迷宮

        
        // 輸出迷宮
        void Print();                                           // 輸出迷宮

        // 初始化
        void Initialization();                                           // 初始化   
};


// 建構類別
Maze::Maze()                            // 建構類別,初始化
{
    maze = {};
    scope = {0,0};
    goal = 1;
    location = {0,0};
    path = {};
    alfgoal = {};
    direction = Right;
} // Maze::Maze()  


Maze::Maze( const Maze& aMaze )         // 建構類別,複製另一類別資料
{
    maze = aMaze.maze;
    scope = aMaze.scope;
    goal = aMaze.goal;
    location = aMaze.location;
    path = aMaze.path;
    alfgoal = aMaze.alfgoal;
    direction = aMaze.direction;
} // Maze::Maze( const Maze& )   


// 讀取資料
bool Maze::InputMaze( string filename, Mode tMode )             // 讀入迷宮資料並儲存,成功回傳true,失敗輸出錯誤資訊並回傳false
{
    ifstream input;
    MazeType newMaze = {};                                      // 暫存迷宮陣列初始化
    string newStr = "";                                         // 暫存迷宮陣列每一行初始化
    string newGoal = "1", x, y;                                 // 暫存尋找的終點數量,水平(X軸)範圍,垂直(Y軸)範圍

    filename = "input" + filename + ".txt";
    input.open( filename );                                     // 開啟檔案          

    if ( input.fail() )                                         // 確認檔案是否開啟
    {
        cout << endl << filename << " is not exist." << endl;                // 輸出錯誤資訊
        input.close();                                              // 關閉檔案
        return false;                                               // 回傳false
    } // if
    
    input >> x >> y;                                                // 從檔案讀入水平(X軸)範圍,垂直(Y軸)範圍
    if (!isDight(x) || !isDight(y) || input.fail())                                 // 確認讀入的範圍是否錯誤 ( 是否為整數 )
    {
        cout << endl << "Format error : The input scope not an Integer." << endl;       // 輸出錯誤資訊
        input.close();                                                          // 關閉檔案
        return false;                                                           // 回傳false
    } // if

    do
    {  
        input >> newStr;                                                        // 從檔案讀入迷宮陣列每一行

        if ( !input.fail() )                                                    // 確認讀入類別是否錯誤
        {
            if ( strlen( newStr.c_str() ) != atoi( x.c_str() ) )                // 是,確認讀入的迷宮陣列每一行長度是否等同先前輸入的水平(X軸)範圍
            {   
                cout << endl << "Format error: The maze X not equal it scope." << endl;     // 是,輸出錯誤資訊
                input.close();                                                      // 關閉檔案
                return false;                                                       // 回傳false
            } // if
            else if ( !formatCheck( newStr ) )                                  // 確認讀入的迷宮陣列每一行是否有無關字元
            {
                cout << endl << "Format error: The string have wrong word." << endl;        // 是,輸出錯誤資訊
                input.close();                                                      // 關閉檔案
                return false;                                                       // 回傳false
            } // else if
            else newMaze.push_back(newStr);                                     // 若無問題,儲存於暫存迷宮陣列
        }
    } while ( !input.eof() );                                               // 確認檔案是否讀完

    input.close();                                                  // 關閉檔案

    if ( newMaze.size() != atoi(y.c_str()) )                        // 確認讀入的迷宮陣列行數是否不等於先前輸入的垂直(Y軸)範圍
    {
        cout << endl << "Format error: The maze Y not equal it scope." << endl; // 是,輸出錯誤資訊
        return false;                                                   // 回傳false
    } // if
    
    if ( tMode == nGoal )                                               // 確認現在模式是否為 找多個終點
    {  
        do
        {
            cout << endl <<"How many Goal?: ";                                  // 輸出詢問終點數量
            cin >> newGoal;                                                     // 輸入終點數量
        } while ( !isDight(newGoal) );                                      // 如果輸入的字串非整數或小於零,繼續迴圈

        if ( atoi( newGoal.c_str() ) < 1 || atoi( newGoal.c_str() ) > 100 )
        {
            cout << endl << "The number of goal must in [1,100]." << endl;
            return false;
        }
    } // if
    
    
    setMaze( newMaze, atoi(newGoal.c_str()), atoi(y.c_str()), atoi(x.c_str()) );    // 將暫存資訊儲存於迷宮類別
    return true;                                                                    // 回傳true
} // bool Maze::inputMaze( string, Mode ) 


void Maze::setMaze( MazeType tMaze, int tgoal, int y, int x )           // 儲存資料 { 二維迷宮陣列, 尋找的終點數量, 垂直最大範圍, 水平最大範圍 }
{
    maze = tMaze;
    goal = tgoal;
    scope[0] = y;
    scope[1] = x;
} // void Maze::setMaze( MazeType, int, int, int )


bool Maze::isDight( string s )          // 判斷輸入是否為整數.正確回傳true,錯誤回傳false
{
    for( int i = 0; i < strlen( s.c_str() ); i++ )
    {
		if ( s[i] < 47 || s[i] > 58 )           // 確認讀入的字串的每一字元是否不為數字(字串是否為整數)
            return false;                           // 是,回傳false
    }

    return true;                                // 是,回傳true
} // bool Maze::isDight( string )


bool Maze::formatCheck( string s )      // 字串格式檢查.正確回傳true,錯誤回傳false
{
    
    for ( int i = 0; i < strlen(s.c_str()); i++ )
    {
        if ( s[i] != 'O' && s[i] != 'E' && s[i] != 'G' )    // 確認讀入的字串的每一字元是否不為'E','O','G',
            return false;                                   // 是,回傳false
    }

    return true;                                            // 是,回傳true
} // bool Maze::FormatCheck( string )


bool Maze::FindGoal( Maze& vMaze )      // // 尋找終點.成功回傳true,失敗回傳false
{
    if ( scope[0] == 0 || scope[1] == 0 )                           // 確認aMaze迷宮範圍是否為0
        return false;                                                   // 是,回傳false

    Location nL = vMaze.location;                                       // 讀取vMaze現在位置座標
    
    if ( vMaze.maze[nL[0]][nL[1]] == 'G' )                              // 確認vMaze現在位置在迷宮陣列上是否為'G'(終點)
    {
        int j = 0;
        while( j < vMaze.alfgoal.size() && nL != vMaze.alfgoal[j]  )         // 是,確認這個位置的'G'終點座標是否沒被找過
            j++;                                                                // 是,等於(vMaze已找到的終點位置鎮列長度).否,j等於((vMaze已找到的終點位置鎮列第n個) - 1)

        if ( j == vMaze.alfgoal.size() )                                    // j等於(vMaze已找到的終點位置鎮列長度(沒找過))
        {
            vMaze.alfgoal.push_back( nL );                                      // 是,在vMaze已找到的終點位置鎮列新增位置
            vMaze.goal--;                                                       // vMaze尋找的終點數量 - 1
            setRPath( vMaze.path );                                             // 將該路徑紀錄於aMaze迷宮陣列
        }
    }
    if ( vMaze.goal == 0 )                                              // 確認vMaze尋找的終點數量是否等於0
        return true;                                                        // 是,回傳true


    if ( vMaze.path.empty()                                                                                             // 確認vMaze最快找到終點的的路徑的陣列是否為空(為空為最初開始的位置[0,0]尚未紀錄)
         || ( nL[0] != vMaze.path[(vMaze.path.size() - 1)][0] || nL[1] != vMaze.path[(vMaze.path.size() - 1)][1] ) )    // 或是現在位置是否不等於已儲存於vMaze最快找到終點的的路徑的陣列尾端(由於當後面發現沒路時會往回走(刪除尾端資料),避免重複紀錄)
    {
        if ( vMaze.maze[nL[0]][nL[1]] != 'G')                           // 是,確認vMaze現在位置在迷宮陣列上是否不為'G'(終點)
            vMaze.maze[nL[0]][nL[1]] = 'V';                                 // 否,將vMaze現在位置在迷宮陣列上改成'V'(已走過的位置)
        vMaze.path.push_back( nL );                                     // 將現在位置儲存於vMaze最快找到終點的的路徑的陣列尾端
    }

    int i = 0;                                                          // 設定已尋找方向次數
    if ( !vMaze.forward(i) )                                            // 確認vMaze現在位置在迷宮陣列上,是否無路可走
    {
        vMaze.path.pop_back();                                              // 是,刪除vMaze最快找到終點的的路徑的陣列尾端資料(往回走)
        if ( vMaze.path.empty() )                                           // 確認vMaze最快找到終點的的路徑的陣列是否為空(為空為包含最初開始的位置[0,0]都被刪除,代表無法往回走)
            return false;                                                       // 是,回傳false

        vMaze.location = vMaze.path[(vMaze.path.size() - 1)];               // 將vMaze位置設定為vMaze最快找到終點的的路徑的陣列尾端資料
    }
    
    return FindGoal( vMaze );
    
}


bool Maze::forward( int i )             // 朝偵測方向前進.成功回傳true,失敗回傳false
{

    if ( i == 4)                        // 當已尋找次數是否等於4
        return false;                   // 是回傳false
    
    Location nL = location;                                                     // 讀取現在位置座標
    Location l = way();                                                         // 讀取偵測方向回傳移動的數值
    if ( ( nL[0] + l[0] + 1 ) > scope[0] || ( nL[0] + l[0] + 1 ) < 1
           || ( nL[1] + l[1] + 1 ) > scope[1] || ( nL[1] + l[1] + 1 ) < 1 )     // 確認((現在位置) + (移動的數值))是否超出範圍
    {
        changeWay();                                                                // 是,改變偵測方向
        return forward( (i + 1) );                                                  // 已尋找次數 + 1,再次偵測
    }

    int yNext = nL[0] + l[0];                                                   // 紀錄移動後的位置Y座標((現在位置Y座標) + (Y座標移動的數值))
    int xNext = nL[1] + l[1];                                                   // 紀錄移動後的位置X座標((現在位置X座標) + (X座標移動的數值))
    if ( maze[yNext][xNext] != 'E' && maze[yNext][xNext] != 'G' )               // 確認移動後的位置在迷宮陣列上是否不是'E'(尚未走過的位置)或'G'(終點)
    {
        changeWay();                                                                // 是,改變偵測方向
        return forward( (i + 1) );                                                  // 已尋找次數 + 1,再次偵測
    }

    
    for ( int j = 0; j < alfgoal.size(); j++ )
    {
        if ( yNext == alfgoal[j][0] && xNext == alfgoal[j][1] )     // 確認移動後的位置的'G'終點座標是否已被找過
        {
            changeWay();                                                // 是,改變偵測方向
            return forward( (i + 1) );                                  // 已尋找次數 + 1,再次偵測
        }
    }

    location[0] = yNext;                    // 紀錄移動後的位置Y座標為現在位置Y座標
    location[1] = xNext;                    // 紀錄移動後的位置X座標為現在位置X座標
    
    return true;
} // bool Maze::Forward( int )


Location Maze::way()            // 根據偵測方向回傳移動的數值
{
    Location Nextl = {0,0};         // 先設定移動的數值為{0,0}(不動)

    if ( direction == Right )       // 確認偵測方向是否為Right(右)
        Nextl[1] = 1;                   // 是,移動的數值設定{0,1}(X軸 + 1)

    if ( direction == Down )        // 確認偵測方向是否為Down(下)
        Nextl[0] = 1;                   // 是,移動的數值設定{1,0}(Y軸 + 1)

    if ( direction == Left )        // 確認偵測方向是否為Left(左)
        Nextl[1] = -1;                  // 是,移動的數值設定{0,-1}(X軸 - 1)

    if ( direction == Up )          // 確認偵測方向是否為Up(上)
        Nextl[0] = -1;                  // 是,移動的數值設定{-1,0}(Y軸 - 1)

    return Nextl;                   // 回傳移動的數值
} // Location Maze::Way()

void Maze::changeWay()          // 根據偵測方向,順時鐘90度改變偵測方向
{
    if ( direction == Right )       // 確認偵測方向是否為Right(右)
        direction = Down;               // 是,將偵測方向順時鐘轉90度,設為Down(下)

    else if ( direction == Down )   // 確認偵測方向是否為Down(下)
        direction = Left;               // 是,將偵測方向順時鐘轉90度,設為Left(左)

    else if ( direction == Left )   // 確認偵測方向是否為Left(左)
        direction = Up;                 // 是,將偵測方向順時鐘轉90度,設為Up(上)

    else if ( direction == Up )     // 確認偵測方向是否為Up(上)
        direction = Right;              // 是,將偵測方向順時鐘轉90度,設為Right(右)
} // void Maze::changeWay()    


void Maze::setRPath( Path vPath )                   // 將最快找到終點的的路徑複製到迷宮
{
    for ( int i = 0; i < vPath.size(); i++ )            
    {
        if ( maze[vPath[i][0]][vPath[i][1]] != 'G' )    // 確認vPath(最快找到終點的的路徑的陣列)的每一步(位置)是否不為'G'(終點)(避免覆蓋終點)
            maze[vPath[i][0]][vPath[i][1]] = 'R';           // 是,將最快找到終點的的路徑每一步(位置)複製到迷宮
    }
} // void Maze::setRPath( Path )


void Maze::Print()                      // 輸出迷宮
{
    for ( int i = 0; i < scope[0]; i++ )
        cout << endl << maze[i].c_str();    // 輸出迷宮陣列每一行(X軸)

    cout << endl;
} // void Maze::print()

void Maze::Initialization()     // 初始化
{
    maze = {};
    scope = {0,0};
    goal = 1;
    location = {0,0};
    path = {};
    alfgoal = {};
    direction = Right;
} // void Maze::Initialization() 


int main()              // 主程式
{
    string command = "0";  // 指令初始化

    do
    {
        Maze aMaze;                 // 建構迷宮類別aMaze(儲存讀入檔案和最快找到終點路徑迷宮陣列)
        string fileName;            // 檔案名
        Mode mode = aGoal;          // 模式初始化

        cout << endl << "**** Path Finding ****";
        cout << endl << "* 0. Exit            *";
        cout << endl << "* 1. One Goal        *";
        cout << endl << "* 2. More Goals      *";
        cout << endl << "**********************";
        cout << endl << "Input a command(0, 1, 2): ";

        cin >> command;             //輸入指令 
        
        if ( ( strcmp( command.c_str(), "1" ) == 0 ) || ( strcmp( command.c_str(), "2" ) == 0 ) )   // 確認指令是否為"1"或"2"
        {
            if ( ( strcmp( command.c_str(), "2" ) == 0 ) )                                              // 是,確認指令是否為"2"
                mode = nGoal;                                                                               // 模式設定為找多個終點
            
            cout << endl << "Input a file number: ";                                                    // 輸出詢問檔案編號
            cin >> fileName;                                                                            // 輸入檔案編號
            
            if ( aMaze.InputMaze( fileName, mode ) )                                                    // 確認讀入迷宮資料並儲存是否成功
            {
                Maze vMaze(aMaze);                                                                          // 是,建構迷宮類別vMaze(處理資料,和儲存經過位置迷宮陣列),並複製aMaze資訊
                bool success = aMaze.FindGoal(vMaze);                                                       // 紀錄尋找終點是否成功

                mode = aGoal;                                                                               // 模式初始化
                vMaze.Print();                                                                              // 輸出vMaze迷宮陣列(經過位置)
                if (success)                                                                                // 確認尋找終點是否成功
                    aMaze.Print();                                                                              // 是,輸出aMaze迷宮陣列(最快找到終點迷宮路徑)

                vMaze.Initialization();                                                                     // vMaze初始化
                
            }
            
            aMaze.Initialization();                                                                     // aMaze初始化
        }
        else if (( strcmp( command.c_str(), "0" ) == 0 ))                                           // 否,確認指令是否為"0"
            break;                                                                                      // 是,跳出迴圈
        else                                                                                        
            cout << endl << "Command " << command << " does not exist!" << endl;                    // 否,輸出錯誤訊息
        
    
    } while (true);

    system("pause");            // 暫停執行程式
    
    return 0;
}


