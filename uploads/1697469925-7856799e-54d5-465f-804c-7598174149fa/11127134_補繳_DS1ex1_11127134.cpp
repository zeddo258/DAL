//11127134 林日彥

#include <iostream> // C++語法(輸入輸出)
#include <fstream> // 包含文件輸入流的頭文件
#include <vector> // 存迷宮二為動態陣列
#include <utility> // 包含std::pair

using namespace std; // 

class Maze { // 儲存迷宮資料，外部程式要透過該類別的方法函示才能存取矩陣內容
private: // 私用繼承，只有該函式才能存取
    int column; // 矩陣的欄
    int row; // 矩陣的行
    vector<vector<char> > charArray; // 儲存迷宮裡面的字符元素的動態二維陣列
    vector<pair<int, int> > coordinates; // 使用pair來儲存座標對
    int goals; // 剩餘目標數(會變動)
    int shortlength; // 最短路徑長
public: // 自由，外部函式也能取用
    Maze () { // c++語法必須存在此建構子

    }

    Maze (Maze& aMaze) { // 複製primate, Vector
        column = aMaze.column;
        row = aMaze.row;
        goals = aMaze.goals;
        charArray = aMaze.charArray;
    }

    bool load (string fileName) { // 讀取檔案並儲存
        string completeFileName = "input" + string(fileName) + ".txt"; // 拼接文件名
        ifstream inputFile(completeFileName.c_str()); // 使用 C++ 的文件輸入流
        if (!inputFile.is_open()) { // 如果檔案無法被打開
            cerr << completeFileName <<" does not exist!" << endl;
            return false;
        }

        column = 0; // 設定二維陣列的列數
        row = 0;    // 設定二維陣列的行數
        inputFile >> column >> row; // 依序讀取檔案內容(int int)
        charArray.resize(row, vector<char>(column)); // 創建一個空的二維字元向量，分配二維字元陣列

        for (int i = 0; i < row; i++) { // 讀取文件內容並存儲到二維向量
            for (int j = 0; j < column; j++) {
                inputFile >> charArray[i][j]; // 讀取檔案內部的矩陣
            }
        }

        inputFile.close(); // 關閉文件
        return true;
    }
    
    bool findGoals(Maze& vMaze, char command, int direction, int i, int j) { // 遞迴走迷宮，右下左上，已經有目標個數
        if (command == '2') { // 只有command == '2'時要輸入goals，否則goals值=1
            cin >> goals; // 輸入goals值
            while (goals < 0 || goals > 100 || goals == 0) {
                if (goals == 0 || goals > 100) {
                    cout << endl << "### The number must be in [1,100] ###" << endl;
                    cout << endl << "Number of G (goals): ";
                    cin >> goals;
                }
                if (goals < 0) {
                    cout << endl << "Number of G (goals): ";
                    cin >> goals;
                }
            }
        }
        else if (command == '1')  goals = 1;

        bool returnvalue = false; // 接findGoals的回傳值

        command = '0'; // 阻止遞迴時再跑一次上面，遞迴只跑下面!!!
        //charArray[i][j]; i到row-1(直), j到column-1

        int goalsvalue = 0; // 儲存遞迴前的goals值
        // 如果return到左上角，左上角的右邊和下面都走完了，代表沒有找到目標路徑
        if (i == 0 && j == 0 && vMaze.charArray[0][1] != 'E' && vMaze.charArray[1][0] != 'E')  return false;
        if (vMaze.charArray[i][j] == 'E') { // 走到的字符=E
            vMaze.charArray[i][j] = 'V'; // 把E改成V
            if (direction == 1) { // 往右
                if (j + 1 < column) { // 不在最右
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    returnvalue = findGoals(vMaze, command, 1, i, j+1); // 往原來的方向走(右)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (returnvalue == true)  return true; // 有找到目標
                }
                if (i + 1 < row) { // 不在最下
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    returnvalue = findGoals(vMaze, command, 2, i+1, j); // 改變方向走(下)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (returnvalue == true)  return true; // 有找到目標
                }
                if (i > 0) { // 不在最上
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    returnvalue = findGoals(vMaze, command, 4, i-1, j); // 改變方向走(上)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (returnvalue == true)  return true; // 有找到目標
                }
                return false; // 都無法前進就後退
            }
            if (direction == 2) { // 往下
                if (i + 1 < row) { // 不在最下
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    returnvalue = findGoals(vMaze, command, 2, i+1, j); // 往原來的方向走(下)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (returnvalue == true)  return true; // 有找到目標
                }
                if (j > 0) { // 不在最左
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    returnvalue = findGoals(vMaze, command, 3, i, j-1); // 改變方向走(左)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (returnvalue == true)  return true; // 有找到目標
                }
                if (j + 1 < column) { // 不在最右
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    returnvalue = findGoals(vMaze, command, 1, i, j+1); // 改變方向走(右)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (returnvalue == true)  return true; // 有找到目標
                }
                return false; // 都無法前進就後退
            }
            if (direction == 3) { // 往左
                if (j > 0) { // 不在最左
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    returnvalue = findGoals(vMaze, command, 3, i, j-1); // 往原來的方向走(左)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (returnvalue == true)  return true; // 有找到目標
                }
                if (i > 0) { // 不在最上
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    returnvalue = findGoals(vMaze, command, 4, i-1, j); // 改變方向走(上)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (returnvalue == true)  return true; // 有找到目標
                }
                if (i + 1 < row) { // 不在最下
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    returnvalue = findGoals(vMaze, command, 2, i+1, j); // 改變方向走(下)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (returnvalue == true)  return true; // 有找到目標
                }
                return false; // 都無法前進就後退
            }
            else { // 往上
                if (i > 0) { // 不在最上
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    returnvalue = findGoals(vMaze, command, 4, i-1, j); // 往原來的方向走(上)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (returnvalue == true)  return true; // 有找到目標
                }
                if (j + 1 < column) { // 不在最右
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    returnvalue = findGoals(vMaze, command, 1, i, j+1); // 改變方向走(右)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (returnvalue == true)  return true; // 有找到目標
                }
                if (j > 0) { // 不在最左
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    returnvalue = findGoals(vMaze, command, 3, i, j-1); // 改變方向走(左)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (returnvalue == true)  return true; // 有找到目標
                }
                return false; // 都無法前進就後退
            }
        }
        else if (vMaze.charArray[i][j] == 'G') { // 先判斷G有沒有走過(是否在coordinates中存在)，如果不存在，添加座標到coordinates
            // 如果座標G存在繼續走(走其他方向)
            if (coordinates.empty()) { // 儲存G的座標陣列是空的
                coordinates.push_back(make_pair(i, j)); // 將此座標添加到儲存G的座標陣列
                goals--; // 找到G的話，目標少1
                if (goals == 0) { // 如果目標找完了
                    return true;
                }
                else { // 還沒結束繼續往原方向走
                    if (direction == 1) { // 往右
                        if (j + 1 < column) { // 不在最右
                            returnvalue = findGoals(vMaze, command, 1, i, j+1); // 往原來的方向走(右)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (i + 1 < row) { // 不在最下
                            returnvalue = findGoals(vMaze, command, 2, i+1, j); // 改變方向走(下)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (i > 0) { // 不在最上
                            returnvalue = findGoals(vMaze, command, 4, i-1, j); // 改變方向走(上)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        return false; // 都無法前進就後退
                    }
                    if (direction == 2) { // 往下
                        if (i + 1 < row) { // 不在最下
                            returnvalue = findGoals(vMaze, command, 2, i+1, j); // 往原來的方向走(下)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (j > 0) { // 不在最左
                            returnvalue = findGoals(vMaze, command, 3, i, j-1); // 改變方向走(左)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (j + 1 < column) { // 不在最右
                            returnvalue = findGoals(vMaze, command, 1, i, j+1); // 改變方向走(右)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        return false; // 都無法前進就後退
                    }
                    if (direction == 3) { // 往左
                        if (j > 0) { // 不在最左
                            returnvalue = findGoals(vMaze, command, 3, i, j-1); // 往原來的方向走(左)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (i > 0) { // 不在最上
                            returnvalue = findGoals(vMaze, command, 4, i-1, j); // 改變方向走(上)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (i + 1 < row) { // 不在最下
                            returnvalue = findGoals(vMaze, command, 2, i+1, j); // 改變方向走(下)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        return false; // 都無法前進就後退
                    }
                    else { // 往上
                        if (i > 0) { // 不在最上
                            returnvalue = findGoals(vMaze, command, 4, i-1, j); // 往原來的方向走(上)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (j + 1 < column) { // 不在最右
                            returnvalue = findGoals(vMaze, command, 1, i, j+1); // 改變方向走(右)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (j > 0) { // 不在最左
                            returnvalue = findGoals(vMaze, command, 3, i, j-1); // 改變方向走(左)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        return false; // 都無法前進就後退
                    }
                }
            }
            else { // 使用for迴圈檢查是否已存在座標
                bool exist = false; // 預設不存在
                for (int k = 0; k < coordinates.size(); k++) { // 搜尋coordinates陣列的所有元素，看存不存在與目前G相同的座標
                    if (coordinates[k].first == i && coordinates[k].second == j) { // 如果座標相同
                        exist = true; // 設為存在
                    }
                }
                if (exist == true) { // 和E操作相同，只是不用改成V
                    if (direction == 1) { // 往右
                        if (j + 1 < column) { // 不在最右
                            returnvalue = findGoals(vMaze, command, 1, i, j+1); // 往原來的方向走(右)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (i + 1 < row) { // 不在最下
                            returnvalue = findGoals(vMaze, command, 2, i+1, j); // 改變方向走(下)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (i > 0) { // 不在最上
                            returnvalue = findGoals(vMaze, command, 4, i-1, j); // 改變方向走(上)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        return false; // 都無法前進就後退
                    }
                    if (direction == 2) { // 往下
                        if (i + 1 < row) { // 不在最下
                            returnvalue = findGoals(vMaze, command, 2, i+1, j); // 往原來的方向走(下)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (j > 0) { // 不在最左
                            returnvalue = findGoals(vMaze, command, 3, i, j-1); // 改變方向走(左)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (j + 1 < column) { // 不在最右
                            returnvalue = findGoals(vMaze, command, 1, i, j+1); // 改變方向走(右)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        return false; // 都無法前進就後退
                    }
                    if (direction == 3) { // 往左
                        if (j > 0) { // 不在最左
                            returnvalue = findGoals(vMaze, command, 3, i, j-1); // 往原來的方向走(左)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (i > 0) { // 不在最上
                            returnvalue = findGoals(vMaze, command, 4, i-1, j); // 改變方向走(上)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (i + 1 < row) { // 不在最下
                            returnvalue = findGoals(vMaze, command, 2, i+1, j); // 改變方向走(下)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        return false; // 都無法前進就後退
                    }
                    else { // 往上
                        if (i > 0) { // 不在最上
                            returnvalue = findGoals(vMaze, command, 4, i-1, j); // 往原來的方向走(上)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (j + 1 < column) { // 不在最右
                            returnvalue = findGoals(vMaze, command, 1, i, j+1); // 改變方向走(右)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        if (j > 0) { // 不在最左
                            returnvalue = findGoals(vMaze, command, 3, i, j-1); // 改變方向走(左)
                            if (returnvalue == true)  return true; // 有找到目標
                        }
                        return false; // 都無法前進就後退
                    }
                }
                else { // 先判斷G有沒有走過(是否在coordinates中存在)，如果不存在，添加座標到coordinates
                    // 如果座標G存在繼續走(走其他方向)
                    coordinates.push_back(make_pair(i, j)); // 將此座標添加到儲存G的座標陣列
                    goals--; // 找到G的話，目標少1
                    if (goals == 0) { // 如果目標找完了
                        return true;
                    }
                    else { // 還沒結束繼續往原方向走
                        if (direction == 1) { // 往右
                            if (j + 1 < column) { // 不在最右
                                returnvalue = findGoals(vMaze, command, 1, i, j+1); // 往原來的方向走(右)
                                if (returnvalue == true)  return true; // 有找到目標
                            }
                            if (i + 1 < row) { // 不在最下
                                returnvalue = findGoals(vMaze, command, 2, i+1, j); // 改變方向走(下)
                                if (returnvalue == true)  return true; // 有找到目標
                            }
                            if (i > 0) { // 不在最上
                                returnvalue = findGoals(vMaze, command, 4, i-1, j); // 改變方向走(上)
                                if (returnvalue == true)  return true; // 有找到目標
                            }
                            return false; // 都無法前進就後退
                        }
                        if (direction == 2) { // 往下
                            if (i + 1 < row) { // 不在最下
                                returnvalue = findGoals(vMaze, command, 2, i+1, j); // 往原來的方向走(下)
                                if (returnvalue == true)  return true; // 有找到目標
                            }
                            if (j > 0) { // 不在最左
                                returnvalue = findGoals(vMaze, command, 3, i, j-1); // 改變方向走(左)
                                if (returnvalue == true)  return true; // 有找到目標
                            }
                            if (j + 1 < column) { // 不在最右
                                returnvalue = findGoals(vMaze, command, 1, i, j+1); // 改變方向走(右)
                                if (returnvalue == true)  return true; // 有找到目標
                            }
                            return false; // 都無法前進就後退
                        }
                        if (direction == 3) { // 往左
                            if (j > 0) { // 不在最左
                                returnvalue = findGoals(vMaze, command, 3, i, j-1); // 往原來的方向走(左)
                                if (returnvalue == true)  return true; // 有找到目標
                            }
                            if (i > 0) { // 不在最上
                                returnvalue = findGoals(vMaze, command, 4, i-1, j); // 改變方向走(上)
                                if (returnvalue == true)  return true; // 有找到目標
                            }
                            if (i + 1 < row) { // 不在最下
                                returnvalue = findGoals(vMaze, command, 2, i+1, j); // 改變方向走(下)
                                if (returnvalue == true)  return true; // 有找到目標
                            }
                            return false; // 都無法前進就後退
                        }
                        else { // 往上
                            if (i > 0) { // 不在最上
                                returnvalue = findGoals(vMaze, command, 4, i-1, j); // 往原來的方向走(上)
                                if (returnvalue == true)  return true; // 有找到目標
                            }
                            if (j + 1 < column) { // 不在最右
                                returnvalue = findGoals(vMaze, command, 1, i, j+1); // 改變方向走(右)
                                if (returnvalue == true)  return true; // 有找到目標
                            }
                            if (j > 0) { // 不在最左
                                returnvalue = findGoals(vMaze, command, 3, i, j-1); // 改變方向走(左)
                                if (returnvalue == true)  return true; // 有找到目標
                            }
                            return false; // 都無法前進就後退
                        }
                    }
                }
            }
        }
        else  return false; // 如果不是E和G的話就返回
    }
    
    bool findshortpath(Maze& vMaze, Maze& tMaze, char command, int direction, int i, int j, int length) { // 遞迴走迷宮，右下左上，已經有目標個數
        if (length > row * column)  return false; // 不能走超過所有元素的總合格數
        if (command == '3')  goals = 1; // 只找一個G

        command = '0'; // 阻止遞迴時再跑一次上面，遞迴只跑下面!!!   //charArray[i][j]; i到row-1(直), j到column-1

        int goalsvalue = 0; // 儲存遞迴前的goals值

        bool returnvalue = false; // 判斷tempreturn的回傳值
        bool tempreturn = false; // 原本的矩陣(不會變)

        if (goals < 1) { // 至少找到一個G了
            if (length == shortlength)  return false; // 不能比上一個路徑長度還要長
        }

        if (tMaze.charArray[i][j] == 'E') { // 走到的字符=E
            vMaze.charArray[i][j] = 'V'; // 把E改成V
            if (direction == 1) { // 往右
                if (j + 1 < column) { // 不在最右
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    tempreturn = findshortpath(vMaze, tMaze, command, 1, i, j+1, length+1); // 往原來的方向走(右)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (tempreturn == true)  returnvalue = true; // findshortpath回傳值，不能直接return true or false
                }
                if (i + 1 < row) { // 不在最下
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    tempreturn = findshortpath(vMaze, tMaze, command, 2, i+1, j, length+1); // 改變方向走(下)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (tempreturn == true)  returnvalue = true; // findshortpath回傳值，不能直接return true or false
                }
                if (i > 0) { // 不在最上
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    tempreturn = findshortpath(vMaze, tMaze, command, 4, i-1, j, length+1); // 改變方向走(上)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (tempreturn == true)  returnvalue = true; // findshortpath回傳值，不能直接return true or false
                }
                return returnvalue; // 剩下三方向做完才回傳true,false，全部都要經過
            }
            if (direction == 2) { // 往下
                if (i + 1 < row) { // 不在最下
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    tempreturn = findshortpath(vMaze, tMaze, command, 2, i+1, j, length+1); // 往原來的方向走(下)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (tempreturn == true)  returnvalue = true; // findshortpath回傳值，不能直接return true or false
                }
                if (j > 0) { // 不在最左
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    tempreturn = findshortpath(vMaze, tMaze, command, 3, i, j-1, length+1); // 改變方向走(左)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (tempreturn == true)  returnvalue = true; // findshortpath回傳值，不能直接return true or false
                }
                if (j + 1 < column) { // 不在最右
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    tempreturn = findshortpath(vMaze, tMaze, command, 1, i, j+1, length+1); // 改變方向走(右)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (tempreturn == true)  returnvalue = true; // findshortpath回傳值，不能直接return true or false
                }
                return returnvalue; // 剩下三方向做完才回傳true,false，全部都要經過
            }
            if (direction == 3) { // 往左
                if (j > 0) { // 不在最左
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    tempreturn = findshortpath(vMaze, tMaze, command, 3, i, j-1, length+1); // 往原來的方向走(左)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (tempreturn == true)  returnvalue = true; // findshortpath回傳值，不能直接return true or false
                }
                if (i > 0) { // 不在最上
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    tempreturn = findshortpath(vMaze, tMaze, command, 4, i-1, j, length+1); // 改變方向走(上)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (tempreturn == true)  returnvalue = true; // findshortpath回傳值，不能直接return true or false
                }
                if (i + 1 < row) { // 不在最下
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    tempreturn = findshortpath(vMaze, tMaze, command, 2, i+1, j, length+1); // 改變方向走(下)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (tempreturn == true)  returnvalue = true; // findshortpath回傳值，不能直接return true or false
                }
                return returnvalue; // 剩下三方向做完才回傳true,false，全部都要經過
            }
            else { // 往上
                if (i > 0) { // 不在最上
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    tempreturn = findshortpath(vMaze, tMaze, command, 4, i-1, j, length+1); // 往原來的方向走(上)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (tempreturn == true)  returnvalue = true; // findshortpath回傳值，不能直接return true or false
                }
                if (j + 1 < column) { // 不在最右
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    tempreturn = findshortpath(vMaze, tMaze, command, 1, i, j+1, length+1); // 改變方向走(右)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (tempreturn == true)  returnvalue = true; // findshortpath回傳值，不能直接return true or false
                }
                if (j > 0) { // 不在最左
                    goalsvalue = goals; // 紀錄遞迴前的goals值
                    tempreturn = findshortpath(vMaze, tMaze, command, 3, i, j-1, length+1); // 改變方向走(左)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // 如果遞迴前值較大，代表有找到G，return時要改成R
                    if (tempreturn == true)  returnvalue = true; // findshortpath回傳值，不能直接return true or false
                }
                return returnvalue; // 剩下三方向做完才回傳true,false，全部都要經過
            }
        }
        else if (vMaze.charArray[i][j] == 'G') { // 找到G直接紀錄長度和return true回來畫R，再繼續地回找G比較長度，如果更短覆蓋矩陣
            goals--; // 找到G的話，目標少1
            if (coordinates.empty()) { // 儲存G的座標陣列是空的
                coordinates.push_back(make_pair(i, j)); // 將此座標添加到儲存G的座標陣列
                shortlength = length; // 最短路徑長度
                return true;
            }
            else { // 使用for迴圈檢查是否已存在座標
                bool exist = false; // 預設不存在
                for (int k = 0; k < coordinates.size(); k++) { // 搜尋coordinates陣列的所有元素，看存不存在與目前G相同的座標
                    if (coordinates[k].first == i && coordinates[k].second == j) { // 如果座標相同
                        exist = true; // 設為存在
                    }
                }
                if (exist == true) { // 和E操作相同，只是不用改成V
                    if (shortlength > length) { // 新路徑長比原路徑長短
                        shortlength = length; // 將新路徑長賦值覆蓋掉原路徑長
                        for (int i = 0; i < row; i++) { // 將原來的R矩陣重置成一開始迷宮的樣子
                            for (int j = 0; j < column; j++) {
                                charArray[i][j] = tMaze.charArray[i][j];
                            }
                        }
                        return true;
                    }
                    else  return false;
                }
                else { // 先判斷G有沒有走過(是否在coordinates中存在)，如果不存在，添加座標到coordinates
                    coordinates.push_back(make_pair(i, j)); // 將此座標添加到儲存G的座標陣列
                    if (shortlength > length) { // 新路徑長比原路徑長短
                        shortlength = length; // 將新路徑長賦值覆蓋掉原路徑長
                        for (int i = 0; i < row; i++) { // 將原來的R矩陣重置成一開始迷宮的樣子
                            for (int j = 0; j < column; j++) {
                                charArray[i][j] = tMaze.charArray[i][j];
                            }
                        }
                        return true;
                    }
                    else  return false;
                }
            }
        }
        else  return false; // 如果不是E和G的話就返回
    }

    void show() { // 將迷宮印出來
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                cout << charArray[i][j];
            }
            cout << endl;
        }
        cout << endl;
        return;
    }

    void shortpath() {
        if (goals == 1)  cout << endl << "### There is no path to find a goal! ###" << endl; // goals完全沒變少(沒找到)
        else  cout << endl << "Shortest path length = " << shortlength << endl; // 輸出最短路徑
    }

    void clr() { // 將迷宮全部清除
        charArray.clear(); // 清空迷宮裡的所有元素
        charArray.resize(0, vector<char>(column)); // 全部清除
        return;
    }
};

int main(void) {
    char command = '0'; // user command
    int direction = 1; // 預設前進方向為右邊
    int i = 0; // 控制迷宮的座標上下移動，(正為下，負為上)
    int j = 0; // 控制迷宮的座標左右移動，(正為右，負為左)
    int length = 1; // 路徑長度

    do {
        Maze aMaze; // a matrix
        string fileName; // a file name

        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit          *";
        cout << endl << "* 1. One goal      *";
        cout << endl << "* 2. More goals    *";
        cout << endl << "********************";
        cout << endl << "Input a command(0, 1, 2, 3): ";

        cin >> command; // get the command
        if ((command == '1')||(command == '2')||(command == '3')) { // command='1'或'2'或'3'時才執行命令
            cout << endl << "Input a file number: ";
            cin >> fileName; // 讀入檔案名稱(數字)
            if (command == '2')  cout << endl << "Number of G (goals): ";
            if (aMaze.load(fileName)) { // load the original matrix
                Maze vMaze(aMaze); // a copy to keep the visited cells
                if ((command == '1')||(command == '2')) {
                    bool success = aMaze.findGoals(vMaze, command, direction, i, j); // find a path to goal(s)
                    vMaze.show(); // show on screen the visited cells
                    if (success) // to check if the goal is reached or not
                        aMaze.show(); // show on screen the route to reach the goal
                }
                else if ((command == '3')) {
                    Maze tMaze(aMaze); // a copy to keep the temped cells
                    bool havefind = aMaze.findshortpath(vMaze, tMaze, command, direction, i, j, length); // find a path to goal(s)
                    vMaze.show(); // show on screen the visited cells
                    if (havefind) // to check if the goal is reached or not
                        aMaze.show(); // show on screen the route to reach the goal
                    aMaze.shortpath(); // 印最短路徑
                    tMaze.clr(); // clear up the copy
                }
                vMaze.clr(); // clear up the copy
            } // end inner-if
            aMaze.clr(); // clear up the original matrix
        } // end outer-if 
        else if (command == '0')  break; // '0': stop the program
        else  cout << endl << "Command does not exist!" << endl;
        system("pause"); // pause the execution
    }while(true);
    system("pause"); // pause the execution
    return 0;
} // end of main