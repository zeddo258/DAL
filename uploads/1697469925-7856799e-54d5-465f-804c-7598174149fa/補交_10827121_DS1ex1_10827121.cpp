// 10827121 ¿½¤O¸Û
# include <iostream>
# include <fstream>
# include <vector>
using namespace std;


class Coordinates {
  public : int x, y;
  public : string direction;

  public : Coordinates(int a, int b) {
    x = a, y = b;
  } // constructor 1

  public : Coordinates(int a, int b, string c) {
    x = a, y = b, direction = c;
  } // constructor 2

}; // class Coordinates


class PathFind {
  private : int mapSizeWidth, mapSizeHeight, numOfGoal, minPath;
  private : vector<vector<char>> map;
  private : vector<Coordinates*> visitedGoal, visitedRecord, routeRecord;
  private : vector<vector<Coordinates*>> bestRouteRecord;

  public : PathFind(int nOG) {
    numOfGoal = nOG;
    visitedGoal.clear();
    routeRecord.clear();

    readFile();

    if (nOG != 0) { // Mission 1, 2
      if (mouseRunMaze(0, 0, "right")) { // find all goal
        printMap("visited");
        cout << '\n';
        printMap("route");
      } // if()
      else printMap("visited");  // didn't find all goal
    } // if()
    else { // Mission 3
      minPath = 2147483647;
      visitedRecord.clear();
      bestRouteRecord.clear();

      mouseRunMaze_M3(0, 0, "right"); // 2147483647 is about to find shortest path
      printMap_M3();
    } // else
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


  private : bool mouseRunMaze_M3(int x, int y, string direction) {
    if (map[y][x] == 'G') {
      bestRouteRecord.push_back(routeRecord); // record the way to goal
      minPath = routeRecord.size(); // refresh the min path
    } // if()

    else if (map[y][x] != 'G' && !alreadyVisitedThisCoordinate(x, y, direction) && routeRecord.size() < minPath) {
      if (routeRecord.size() != 0 && routeRecord[routeRecord.size() - 1]->x == x && routeRecord[routeRecord.size() - 1]->y == y)
        ; // just change direction, no need to record
      else {
        Coordinates* c = new Coordinates(x, y, direction); // it's about to record route
        routeRecord.push_back(c);
      } // else

      recordVisited_M3(x, y);

      if (thisDirectionCanMove(x, y, direction)) walkOneStep(x, y, direction);

      direction = turnAround(direction);
      if (thisDirectionCanMove(x, y, direction)) walkOneStep(x, y, direction);

      direction = turnAround(turnAround(direction)); // no need to try the opposite direction, it's already been visited
      if (thisDirectionCanMove(x, y, direction)) walkOneStep(x, y, direction);

      if (map[y][x] == 'V') map[y][x] = 'E';

      routeRecord.pop_back();
    } // else if()
  } // mouseRunMaze_M3()


  private : void walkOneStep(int x, int y, string direction) {
    if      (direction == "right") mouseRunMaze_M3(x + 1, y    , direction);
    else if (direction == "down" ) mouseRunMaze_M3(x    , y + 1, direction);
    else if (direction == "left" ) mouseRunMaze_M3(x - 1, y    , direction);
    else if (direction == "up"   ) mouseRunMaze_M3(x    , y - 1, direction);
  } // walkOneStep()


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


  private : bool alreadyVisitedThisCoordinate(int x, int y, string direction) {
    for (int a = 0; a < routeRecord.size(); a++)
      if (routeRecord[a]->x == x && routeRecord[a]->y == y && routeRecord[a]->direction == direction) return true;

    return false;
  } // alreadyVisitedThisCoordinate()


  private : string turnAround(string direction) {
    if      (direction == "right") return "down" ;
    else if (direction == "down" ) return "left" ;
    else if (direction == "left" ) return "up"   ;
    else if (direction == "up"   ) return "right";
  } // turnAround()


  private : void recordVisited(int x, int y) {
    if (map[y][x] == 'E') map[y][x] = 'V';
  } // recordVisited()


  private : void recordVisited_M3(int x, int y) {
    Coordinates* c = new Coordinates(x, y);
    visitedRecord.push_back(c);
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

      for (int a = 0; a < routeRecord.size(); a++) {
        if (map[routeRecord[a]->y][routeRecord[a]->x] == 'E') map[routeRecord[a]->y][routeRecord[a]->x] = 'R';
      } // for(a)

      for (int a = 0; a < mapSizeHeight; a++) {
        for (int b = 0; b < mapSizeWidth; b++) cout << map[a][b];
        cout << '\n';
      } // for(a)
    } // else if()

  } // printMap()


  private : void printMap_M3() {
    for (int a = 0; a < visitedRecord.size(); a++) // print visited
      map[visitedRecord[a]->y][visitedRecord[a]->x] = 'V';

    for (int a = 0; a < mapSizeHeight; a++) {
      for (int b = 0; b < mapSizeWidth; b++) cout << map[a][b];
      cout << '\n';
    } // for(a)

    cout << '\n';

    for (int a = 0; a < mapSizeHeight; a++) { // restore map
      for (int b = 0; b < mapSizeWidth; b++) 
        if (map[a][b] == 'V') map[a][b] = 'E';
    } // for(a)

    int minLength = 2147483647; // find shortest path

    for (int a = 0; a < bestRouteRecord.size(); a++) {
      if (bestRouteRecord[a].size() < minLength) {
        routeRecord = bestRouteRecord[a];
        minLength = routeRecord.size();
      } // if()
    } // for(a)

    if (minLength == 2147483647) cout << "There is no path to find a goal!\n";
    else { // print route
      for (int a = 0; a < routeRecord.size(); a++)
        if (map[routeRecord[a]->y][routeRecord[a]->x] == 'E') map[routeRecord[a]->y][routeRecord[a]->x] = 'R';

      for (int a = 0; a < mapSizeHeight; a++) {
        for (int b = 0; b < mapSizeWidth; b++) cout << map[a][b];
        cout << '\n';
      } // for(a)

      cout << "\nShortest path length = " << minLength + 1 << "\n";
    } // else
  } // printMap_M3()

}; // class PathFind


void printMenu();
int selectFunction();
int readGoalNumber();

int main() {

  while (1) {
    printMenu();
    int function = selectFunction();

    if (function == 0) break;
    else if (1 <= function && function <= 3) ;
    else cout << "\n### Command does not exist! ###\n\n";

    if      (function == 1) PathFind* pf = new PathFind(1); // goal number = 1
    else if (function == 2) PathFind* pf = new PathFind(readGoalNumber());
    else if (function == 3) PathFind* pf = new PathFind(0); // 0 is a singal to talk PathFind, it's Mission 3
  } // while(1)
  
  cout << "\nByeBye~";
} // main()


void printMenu() {
  cout << "\n**** Path Finding ***\n";
  cout <<   "* 0. Quit           *\n";
  cout <<   "* 1. One  goal      *\n";
  cout <<   "* 2. More goals     *\n";
  cout <<   "* 3. Shortest path  *\n";
  cout <<   "*********************\n";
  cout <<   "Input your choice ( 0, 1, 2, 3 ) : ";
} // rrintMenu()


int selectFunction() {
  string s; // user can input 1, 2 or 3 to select function
  getline(cin, s);

  if      (s == "0") return 0;
  else if (s == "1") return 1;
  else if (s == "2") return 2;
  else if (s == "3") return 3;
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
