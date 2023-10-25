//11144114盧鈴臻
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool solveMaze(std::vector<std::string>& maze, int x, int y)
{

    if (x < 0 || x >= maze.size() || y < 0 || y >= maze[0].size() || maze[x][y] == 'O' || maze[x][y] == 'V') {
        return false; // 越界、遇到牆壁或已走過的位置
    }

    if (maze[x][y] == 'G') {
        // 找到一條路
        return true;
    }

    maze[x][y] = 'V'; // 標記當前位置為已走過

    // 依次嘗試右、下、左、上四个方向
    if (solveMaze(maze, x, y + 1) || solveMaze(maze, x + 1, y) || solveMaze(maze, x, y - 1) || solveMaze(maze, x - 1, y))
    {
        maze[x][y] = 'R'; // 標記成功路徑
        return true;
    }

    maze[x][y] = 'E'; // 恢復當前位置為可走的路以便查找其他路徑
    return false;
}//end solveMaze

int main()
{
    while (true)
    {
        std::string fileName;

        // 輸入要執行的迷宫文件名
        std::cout << "輸入文件名（或輸入'exit'退出):";
        std::cin >> fileName;

        if (fileName == "exit")
        {
            break; // 用戶輸入'exit'時退出程序
        }

        std::ifstream inputFile(fileName.c_str()); // 使用用戶輸入的文件名
        if (!inputFile.is_open())
        {
            std::cerr << "无法打开迷宫文件" << std::endl;
            continue; // 如果文件無法打開，繼續下一个循環
        }

        int rows, cols;
        inputFile >> rows >> cols; // 讀取行數和列數

        // 讀取迷宫地圖
        std::vector<std::string> maze;
        std::string line;
        for (int i = 0; i < rows; ++i)
        {
            inputFile >> line;
            maze.push_back(line);
        }

        inputFile.close();

        // 調用求解函數，從左上角開始查找路徑
        if (solveMaze(maze, 0, 0))
        {
            // 印出找到的正確路徑，保留G和R的位置
            for (const std::string& row : maze)
            {
                std::cout << row << std::endl;
            }
        }
        else
        {
            std::cout << "未找到路徑" << std::endl;
        }
    }

    return 0;
}//end main
