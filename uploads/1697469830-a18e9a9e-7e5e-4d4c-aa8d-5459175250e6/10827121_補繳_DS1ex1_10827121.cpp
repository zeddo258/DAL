// 10827121 蕭力誠
# include <iostream>
# include <fstream>
# include <vector>
using namespace std;


class Coordinates {
  public : int x, y;

  public : Coordinates(int a, int b) {
    x = a, y = b;
  } // constructor

}; // class Coordinates


class PathFind {
  private : int mapSizeWidth, mapSizeHeight, numOfGoal;
  private : vector<vector<char>> map;
  private : vector<Coordinates*> visitedGoal;
  private : vector<Coordinates*> routeRecord;

  public : PathFind(int nOG) {
    numOfGoal = nOG;
    visitedGoal.clear();
    routeRecord.clear();

    readFile();

    if (mouseRunMaze(0, 0, "right")) { // find all goal
      printMap("visited");
      cout << '\n';
      printMap("route");
    } // if()
    else printMap("visited");  // didn't find all goal
  } // constructor


  private : void readFile() {
    ifstream inFile;
    string fileName;

    do {
      cout << "Please enter the file name (eg. 101, 102...) : ";

      getline(cin, fileName);
      inFile.open(stringToCharPointer("input" + fileName + ".txt")); // try to open file

      if (!inFile) cout << "Input error, please try again.\n\n";
    } while(!inFile);

    inFile >> mapSizeWidth >> mapSizeHeight; // read the map size

    for (int a = 0; a < mapSizeHeight; a++) { // read map
      vector<char> temp;

      for (int b = 0; b < mapSizeWidth; b++) {
        char c;
        inFile >> c;

        temp.push_back(c);
      } // for(b)

      map.push_back(temp);
    } // for(a)

    inFile.close();
  } // readFile()


  private : char* stringToCharPointer(string s) {
    char* fileName = new char[s.length() + 1]; // string transfer to char*
    for (int a = 0; a < s.length(); a++) fileName[a] = s[a];
    fileName[s.length()] = '\0';

    return fileName;
  } // stringToCharPointer()


  private : bool mouseRunMaze(int x, int y, string direction) {
    if (map[y][x] == 'G' && findNewGoal(x, y)) {
      Coordinates* c = new Coordinates(x, y);
      visitedGoal.push_back(c);
    } // if()

    if (numOfGoal > visitedGoal.size()) {
      Coordinates* c = new Coordinates(x, y); // it's about to record route
      routeRecord.push_back(c);

      recordVisited(x, y);

      int original_visitedGoal_size = visitedGoal.size(); // see Line : 108

      if (thisDirectionCanMove(x, y, direction)) {
        if      (direction == "right") mouseRunMaze(x + 1, y    , direction);
        else if (direction == "down" ) mouseRunMaze(x    , y + 1, direction);
        else if (direction == "left" ) mouseRunMaze(x - 1, y    , direction);
        else if (direction == "up"   ) mouseRunMaze(x    , y - 1, direction);
      } // if()

      direction = turnAround(direction);
      if (thisDirectionCanMove(x, y, direction)) mouseRunMaze(x, y, direction);

      direction = turnAround(turnAround(direction)); // no need to try the opposite direction, it's already been visited
      if (thisDirectionCanMove(x, y, direction)) mouseRunMaze(x, y, direction);

      if (original_visitedGoal_size == visitedGoal.size()) routeRecord.pop_back(); // this way can't find goal, delete it's record
    } // if()

    if (numOfGoal == visitedGoal.size()) return true;
    else                                 return false;
  } // mouseRunMaze()


  private : bool thisDirectionCanMove(int x, int y, string direction) {
    if (direction == "right") {
      if (x + 1 == mapSizeWidth) return false; // bump into the wall
      else if (map[y][x + 1] == 'E' || map[y][x + 1] == 'G') return true;
    } // if (right)
    else if (direction == "down") {
      if (y + 1 == mapSizeHeight) return false; // bump into the wall
      else if (map[y + 1][x] == 'E' || map[y + 1][x] == 'G') return true;
    } // else if (down)
    else if (direction == "left") {
      if (x == 0) return false; // bump into the wall
      else if (map[y][x - 1] == 'E' || map[y][x - 1] == 'G') return true;
    } // else if (down)
    else if (direction == "up") {
      if (y == 0) return false; // bump into the wall
      else if (map[y - 1][x] == 'E' || map[y - 1][x] == 'G') return true;
    } // else if (down)

    return false;
  } // thisDirectionCanMove()


  private : bool findNewGoal(int x, int y) {
    if (visitedGoal.size() == 0) return true;
    else {
      for (int a = 0; a < visitedGoal.size(); a++)
        if (visitedGoal[a]->x == x && visitedGoal[a]->y == y) return false;

      return true;
    } // else
  } // findNewGoal()


  private : string turnAround(string direction) {
    if      (direction == "right") return "down" ;
    else if (direction == "down" ) return "left" ;
    else if (direction == "left" ) return "up"   ;
    else if (direction == "up"   ) return "right";
  } // turnAround()


  private : void recordVisited(int x, int y) {
    if (map[y][x] == 'E') map[y][x] = 'V';
  } // recordVisited()


  private : void printMap(string mapName) {
    if (mapName == "visited") {
      for (int a = 0; a < mapSizeHeight; a++) {
        for (int b = 0; b < mapSizeWidth; b++) cout << map[a][b];
        cout << '\n';
      } // for(a)
    } // if()
    else if (mapName == "route") {
      for (int a = 0; a < mapSizeHeight; a++) {
        for (int b = 0; b < mapSizeWidth; b++)
          if (map[a][b] == 'V') map[a][b] = 'E';
      } // for(a)

      for(int a = 0; a < routeRecord.size(); a++) {
        if (map[routeRecord[a]->y][routeRecord[a]->x] == 'E') map[routeRecord[a]->y][routeRecord[a]->x] = 'R';
      } // for(a)

      for (int a = 0; a < mapSizeHeight; a++) {
        for (int b = 0; b < mapSizeWidth; b++) cout << map[a][b];
        cout << '\n';
      } // for(a)
    } // else if()

  } // printMap()

}; // class PathFind


void printMenu();
int selectFunction();
int readGoalNumber();

int main() {

  while (1) {
    printMenu();
    int function = selectFunction();

    if (function == 0) break;
    else if (1 <= function && function <= 2) ;
    else cout << "\n### Command does not exist! ###\n\n";

    if      (function == 1) PathFind* pf = new PathFind(1); // goal number = 1
    else if (function == 2) PathFind* pf = new PathFind(readGoalNumber());
  } // while(1)

  cout << "\nByeBye~";
} // main()


void printMenu() {
  cout << "\n**** Path Finding ***\n";
  cout <<   "* 0. Quit           *\n";
  cout <<   "* 1. One  goal      *\n";
  cout <<   "* 2. More goals     *\n";
  cout <<   "*********************\n";
  cout <<   "Input your choice ( 0, 1, 2 ) : ";
} // rrintMenu()


int selectFunction() {
  string s; // user can input 1 or 2 to select function
  getline(cin, s);

  if      (s == "0") return 0;
  else if (s == "1") return 1;
  else if (s == "2") return 2;
  else return -1; // Input Error
} // selectFunction()


int readGoalNumber() {
  do {
    string s;
    cout << "Number of G (goals) : ";

    getline(cin, s);
    bool allDigit = true;

    for(int a = 0; a < s.length(); a++)
      if (!isdigit(s[a])) allDigit = false;

    if (allDigit) {
      int number = 0;

      for(int a = s.length() - 1; a >= 0; a--)
        number = number * 10 + (s[a] - '0');

      if (1 <= number && number <= 100) return number;
      else cout << "The number must be in [1, 100].\n\n";
    } // if()
    else cout << "Input error, please try again.\n\n";
  } while(1);
} // readGoalNumber
