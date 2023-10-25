// 11127152 郭怡楨



# include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;


int load(string filename) {

  string name = "input" + filename + ".txt";

  ifstream inputFile(name);

  if (!inputFile.is_open()) {
    cout << name << " does not exist! " << endl;
    return 1; // 檔案無法開啟
  } // if

  inputFile.ignore(numeric_limits<streamsize>::max(), '\n');

  vector<string> maze; // 儲存迷宮向量

  // 逐行讀取文件内容並儲存到迷宫向量中
  string line;
  while (getline(inputFile, line)) {
    maze.push_back(line);
  } // while

  // 關閉文件
  inputFile.close();

  // 印出迷宫
  for (string row : maze) {
    cout << row << endl;
  } // for


  return 0;
};

int main() {
  int command = 3;
  string filename;

  while(command != 0) {
    cout << endl << "*** Path Finding ***";
    cout << endl << "* 0. Quit          *";
    cout << endl << "* 1. One goal      *";
    cout << endl << "* 2. More goals    *";
    cout << endl << "********************";
    cout << endl << "Input a command(0,1,2):";
    cin >> command;
    cout << endl;

    if (command == 1) {
      cout << "Input a file number:";
      cin >> filename;
      cout << endl;
      load(filename);

    } // if

    else {
      cout << "Command does not exist!" << endl;
    } // else

  } // while

} // main()


