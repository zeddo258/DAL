#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stack>
#include <set>

using namespace std;

enum Modes
{
    oneG = 11111,
    moreG = 22222
}; // 定義枚舉類型 Modes，表示遊戲模式

static int dr[4] = {1, 0, -1, 0};
static int dc[4] = {0, 1, 0, -1};

struct Position
{
    int row;
    int col;
};

struct PathNode
{
    Position position;
    PathNode *parent; // 儲存路徑
};

struct PositionComparator 
{
    bool operator()(const Position &lhs, const Position &rhs) const
    {
        if (lhs.row < rhs.row)
            return true;
        if (lhs.row > rhs.row)
            return false;
        return lhs.col < rhs.col;
    }
};

class Maze
{
public:
    Maze();
    Maze(const Maze &other);                       // 複製建構函數，用來建立迷宮的副本
    bool load(const string &fileName, Modes mode); // 載入迷宮數據
    bool findGoals(Maze &vmaze);                   // 尋找目標位置並標記路徑
    void show();
    void clr(); // 清空迷宮資料

private:
    vector<vector<char>> maze;                 // 儲存迷宮資料的二維字元向量
    int rows;                                  // 迷宮的行數
    int cols;                                  // 迷宮的列數
    int startRow;                              // 起始位置的行坐標
    int startCol;                              // 起始位置的列坐標
    int goalCount;                             // 需要找到的目標數量
    set<Position, PositionComparator> visited; // 記錄已走過的點
    bool isValid(int row, int col, Position currentPosition);
    bool findGoals_helper(Maze &vmaze, PathNode *current, int d);
    void writeShortestPath(PathNode *node, Maze vmaze);
};

Maze::Maze()
{
    rows = 0;
    cols = 0;
    startRow = -1;
    startCol = -1;
    goalCount = 1; // 預設為一個目標
}

Maze::Maze(const Maze &other)
{
    rows = other.rows;
    cols = other.cols;
    startRow = other.startRow;
    startCol = other.startCol;
    goalCount = other.goalCount;
    maze = other.maze; // 複製迷宮數據
}

bool Maze::isValid(int row, int col, Position currentPosition)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        return false;
    }

    if (maze[col][row] != 'E' && maze[col][row] != 'G')
    {
        return false;
    }

    if (visited.count(currentPosition) > 0)
        return false;

    return true;
}

bool Maze::load(const string &fileName, Modes mode)
{
    // 開啟檔案以讀取迷宮數據
    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << endl
             << fileName << " does not exist!" << endl;
        return false; // 如果無法開啟文件，則傳回 false
    }

    // 讀取合法範圍內goal數量
    if (mode == moreG)
    {
        do
        {
            int n;
            cout << "\nNumber of G (goals): ";
            cin >> n;
            goalCount = n;
            if (goalCount > 0 && goalCount < 101)
                break;
            else
                cout << "### The number must be in [1,100] ###\n";
        } while (1);
    }

    // 讀取迷宮的行數和列數 行跟列是row還是col還是不太會分 笑死
    file >> rows >> cols;
    // 為矩陣分配預料內迷宮大小的空間
    maze.resize(cols, vector<char>(rows));

    // 讀取迷宮數據
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            file >> maze[i][j];
            if (maze[i][j] == '\0')
            {
                file.close();
                return false;
            }
        }
    }

    file.get(); // 讀取並丟棄換行符
    file.get(); // 讀取並丟棄尾

    if (!file.eof())
    {
        // 提供的行列小於迷宮的實際大小
        cout << "false ";
        file.close();
        return false;
    }

    startRow = 0;
    startCol = 0;

    file.close();

    return true; // 回傳 true 表示載入成功
}

bool Maze::findGoals(Maze &vmaze)
{
    stack<Position> path;
    PathNode *current = new PathNode;
    current->position.col = startCol;
    current->position.row = startRow;
    current->parent = NULL;
    // 在主函數中呼叫輔助遞迴函數，起始位置為 (startRow, startCol)
    bool success = findGoals_helper(vmaze, current, 0);
    return success;
}

bool Maze::findGoals_helper(Maze &vmaze, PathNode *current, int direction)
{
    // 檢查是否越界
    int row = current->position.row;
    int col = current->position.col;
    if (!isValid(row, col, current->position))
        return false;

    visited.insert(current->position);

    // 如果是目標，減少要找的剩餘目標數
    if (vmaze.maze[col][row] == 'G')
    {
        vmaze.goalCount--;
        writeShortestPath(current, vmaze);
        // 如果找到N個目標了，回傳true
        if (vmaze.goalCount == 0)
        {
            return true;
        }
    }

    // 如果目標沒有被訪問過，標記為已訪問，並增加目標計數
    else if (vmaze.maze[col][row] == 'E')
    {
        vmaze.maze[col][row] = 'V';
    }

    // 嘗試向四個方向遞歸查找目標
    for (int i = 0; i < 4; i++)
    {
        int newRow = row + dr[(direction + i) % 4];
        int newCol = col + dc[(direction + i) % 4];
        PathNode *newNode = new PathNode;
        newNode->position = {newRow, newCol};
        newNode->parent = current;
        if (findGoals_helper(vmaze, newNode, (direction + i) % 4))
            return true;
    }

    // 如果所有方向都沒有找到目標，回傳失敗
    return false;
}

void Maze::writeShortestPath(PathNode *node, Maze vmaze)
{
    int row = node->position.row;
    int col = node->position.col;
    if (vmaze.maze[col][row] == 'V')
        maze[col][row] = 'R'; // 將路徑上的位置標記為R

    if (node->parent == nullptr)
    {
        return; // 遞迴的終止條件：已經回溯到起點
    }

    writeShortestPath(node->parent, vmaze); // 遞回一路溯到父節點
}

void Maze::show()
{
    bool unKonwSymbol = false;
    // 遍歷迷宮矩陣，並根據不同字元顯示不同內容
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            char cell = maze[i][j];
            switch (cell)
            {
            case 'E': // 空格
                cout << 'E';
                break;
            case 'O': // 障礙物
                cout << 'O';
                break;
            case 'G': // 目標
                cout << 'G';
                break;
            case 'V': // 已訪問
                cout << 'V';
                break;
            case 'R': // 可行路線
                cout << 'R';
                break;
            default:
            {
                // 未知字符或其他字符，我是當障礙物處裡啦
                unKonwSymbol = true;
                cout << cell;
                break;
            }
            }
        }
        cout << endl; // 換行顯示下一行
    }

    if (unKonwSymbol)
        cout << endl << "*Default Error: There's an unkonw Symbol.*" << endl;
}

void Maze::clr()
{
    maze.clear();
    rows = 0;
    cols = 0;
    startRow = -1;
    startCol = -1;
    goalCount = 1;
}

string generateFileName(int &number) // 幫數字轉成字串加上其他標準的黨名部分
{
    return "input" + to_string(number) + ".txt";
}

int main(void)
{
    int command = 0;
    do
    {
        Maze aMaze; // 建立 Maze 類別的實例
        string fileName;
        int fileNum;       // 儲存檔案名稱數字部分
        Modes mode = oneG; // 預設遊戲模式為 oneG
        cout << endl
             << "*** Path Finding ***";
        cout << endl
             << "* 0. Quit          *";
        cout << endl
             << "* 1. One goal      *";
        cout << endl
             << "* 2. More goals    *";
        cout << endl
             << "********************";
        cout << endl
             << "Input a command(0, 1, 2): ";
        cin >> command;
        if ((command == 1) || (command == 2))
        {
            if (command == 2)
                mode = moreG;

            cout << endl
                 << "Input a file number (e.g., 201, 202, ...): ";
            cin >> fileNum;
            fileName = generateFileName(fileNum);
            if (aMaze.load(fileName, mode)) // 載入原始迷宮資料
            {
                Maze vMaze(aMaze); // a copy to keep the visited cells
                bool success = aMaze.findGoals(vMaze);
                mode = oneG;
                vMaze.show();
                cout << endl;
                vMaze.clr();
                if (success)
                {
                    aMaze.show();
                }
            } // end inner-if
            aMaze.clr();
            cout << endl;
        } // end outer-if
        else if (!command)
            break; // 重置為預設值
        else
            cout << endl
                 << "Command does not exist!" << endl;

    } while (true);
    system("pause");
    return 0;
    // 主函數結束
}