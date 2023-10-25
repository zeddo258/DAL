//11127123 林靖庭

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <windows.h>


struct Size {
	int x;
	int y;
};

enum Direction {
	RIGHT,
	DOWN,
	LEFT,
	UP
};

enum RouteState {
	DEAD_END,
	TO_GOAL
};

enum WindowColor {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};

using namespace std;

// PointList class start ---->
class PointList {
public:
	~PointList();
	bool contains(int x, int y); // 是否包含 (x,y) 這個點
	void add(int x, int y);
	vector<int*> & getAllPoint();

private:
	vector<int*> content;
};

PointList::~PointList() {
	for (int i = 0; i < content.size(); i++) {
		delete[] content[i];
	}
}

bool PointList::contains(int x, int y) {

	// 一個一個尋找是不是有一樣的 座標 x和y
	for (int i = 0; i < content.size(); i++) {
		int* cord = content[i];
		if (cord[0] == x && cord[1] == y) return true;
	}

	return false;
}

void PointList::add(int x, int y) {
	int* newCord = new int[2];
	newCord[0] = x;
	newCord[1] = y;

	content.push_back(newCord);
}
vector<int*> & PointList::getAllPoint()
{
	return content;
}
//<------- end PointList class

// LengthList class start ---->
class LengthList {
public:
	~LengthList();
	bool contains(int x, int y); // 是否包含 (x,y) 這個點
	void add(int x, int y, int depth);
	int getDepth(int x, int y);
	void setDepth(int x, int y, int depth);

private:
	vector<int*> content;
};

LengthList::~LengthList() {
	for (int i = 0; i < content.size(); i++) {
		delete[] content[i];
	}
}

bool LengthList::contains(int x, int y) {

	// 一個一個尋找是不是有一樣的 座標 x和y
	for (int i = 0; i < content.size(); i++) {
		int* cord = content[i];
		if (cord[0] == x && cord[1] == y) return true;
	}

	return false;
}

void LengthList::add(int x, int y, int depth) {
	int* newCord = new int[3];
	newCord[0] = x;
	newCord[1] = y;
	newCord[2] = depth;

	content.push_back(newCord);
}

int LengthList::getDepth(int x, int y) {
	for (int i = 0; i < content.size(); i++) {
		int* cord = content[i];
		if (cord[0] == x && cord[1] == y) return cord[2];
	}

	cout << "X: " << x << " Y: " << y << " depth not found!\n";
	return 0;
}

void LengthList::setDepth(int x, int y, int depth) {
	for (int i = 0; i < content.size(); i++) {
		int* cord = content[i];
		if (cord[0] == x && cord[1] == y) {
			cord[2] = depth;
			return;
		}
	}

	cout << "X: " << x << " Y: " << y << " depth not set!\n";
}
//<------- end LengthList class

// Canvas class start ---->
class Canvas {
public:
	~Canvas();
	void setSize(Size size); // 按照傳入的大小初始化
	char get(int x, int y);
	void set(int x, int y, char c);
	void copyFrom(Canvas &from); // deepClone 另一個的內容
	void show(HANDLE &window, PointList &findedGoal); // 展示所有內容
	void show();
	void clearRoute();
private:
	char** property = NULL;
	Size size{0,0};

	bool checkSize(int x, int y);
	void releaseMemory();
	void changeColor(HANDLE& window, char ch, int x, int y, PointList &findedGoal);
	void setConsoleColor(HANDLE& window, WindowColor color);
};

bool Canvas::checkSize(int x, int y) {

	// 確保已經設定大小
	if (this->property == NULL) {
		cout << "Size not set\n";
		return false;
	}

	// 確保沒超出陣列大小
	if (size.x <= x || size.y <= y) {
		cout << "Out of range: X: " << x << " Y: " << y << endl;
		return false;
	}

	return true;
}

Canvas::~Canvas() {
	releaseMemory();
}

void Canvas::setSize(Size size) {
	releaseMemory();
	this->size = size;

	this->property = new char* [size.y];

	for (int y = 0; y < size.y; y++) {
		this->property[y] = new char[size.x];
	}
}

char Canvas::get(int x, int y) {
	if (!checkSize(x, y))return 0;

	return this->property[y][x];
}

void Canvas::set(int x, int y, char c) {
	if (!checkSize(x, y)) return;

	this->property[y][x] = c;
}

void Canvas::copyFrom(Canvas &from) {
	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			set(x, y, from.get(x, y) );
		}
	}
}

void Canvas::show(HANDLE& window, PointList &findedGoal) {
	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			char ch = get(x, y);
			changeColor(window, ch, x, y, findedGoal);

			cout << ch;
		}

		cout << endl;
	}

	setConsoleColor(window, WHITE);
}

void Canvas::show() {
	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			char ch = get(x, y);

			cout << ch;
		}

		cout << endl;
	}

}

void Canvas::clearRoute() {
	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			char ch = get(x, y);

			if (ch == 'R') {
				set(x, y, 'E');
			}
		}
	}
}

void Canvas::changeColor(HANDLE& window, char ch, int x, int y, PointList& findedGoal) {
	WindowColor color = WHITE;
	switch (ch) {
	case 'O':
		color = DARKGRAY;
		break;
	case 'V':
		color = YELLOW;
		break;
	case 'R':
		color = LIGHTGREEN;
		break;
	case 'G':
		if (findedGoal.contains(x, y)) color = LIGHTCYAN;
		else color = LIGHTRED;
		break;
	case 'E':
		color = LIGHTGRAY;
		break;
	}

	setConsoleColor(window, color);
}

void Canvas::setConsoleColor(HANDLE& window, WindowColor color) {
	SetConsoleTextAttribute(window, color);
}

void Canvas::releaseMemory() {
	if (this->property == NULL) return;

	for (int y = 0; y < size.y; y++) {
		delete[] this->property[y];
	}

	delete[] this->property;
	this->property = NULL;
}
//<------- end Canvas class



// Maze class start ---->
class Maze {
public:
	Maze();
	void showHistoryPath(HANDLE& window); //展示走過的路徑
	void showRoute(HANDLE& window); // 展示可以到G的路徑

	bool findPath(int goalCount);
	int findShortestPath();

private:
	Canvas canvas, routeCanvas;
	Size canvasSize;
	PointList goalHistory;
	LengthList pointDepth;
	int currentRouteDepth;
	Direction shortestGoalFacing;

	string getFileName();
	bool loadFile(string fileName);
	void getMazeData(ifstream &inFile); // 拿到迷宮主體

	bool isBoundary(int x, int y);
	bool isValidStep(int x, int y); // 檢查該點是否可走
	bool isValidStepShortest(int x, int y, int depth); //攜帶與原點距離來確認下一點是否可走
	bool isGoal(int x, int y); // 檢查是不是沒走過的 目標(G)
	bool needContinueFindShortest(int currentGoal, int depth, int returnDepth); // 在最短路進模式下要不要繼續找路徑
	bool isHistoryRoute(int x, int y);
	bool findNextStep(int& x, int& y, Direction &facing);
	bool findNextStep(int& x, int& y, Direction& facing, int currentDepth); //攜帶與原點距離的找下一點
	void getCurrentFacingNextPos(int& x, int& y, Direction facing); // 依據目前朝向拿下一個點
	bool canCurrentFacingForward(int x, int y, Direction facing); //依照四個方位的順序尋找是否有可以走的地方
	bool canCurrentFacingForward(int x, int y, Direction facing, int currentDepth); 
	Direction nextFacing(Direction facing);
	RouteState goToNextStep(int x, int y, Direction facing, int &currentGoal, int totalGoal);

	RouteState goToNextStepShortest(int x, int y, Direction facing, int& currentGoal, int totalGoal, int depth, int &returnDepth);
	int findAdjecentShortestDepth(int x, int y, int depth); //尋找臨近點與原點最小距離
	void findSmallestDepthGoal(int& x, int& y); //尋找路徑最短的G
	

};

Maze::Maze() {
	// 載入有效檔案
	while(!loadFile(getFileName())){}
}


string Maze::getFileName() {
	string fileNumber;
	cout << "Input a file number: ";
	cin >> fileNumber;

	return "input" + fileNumber + ".txt";
}

bool Maze::loadFile(std::string fileName) {
	ifstream inFile(fileName.c_str());

	//判斷有沒有檔案
	if (!inFile.is_open()) {
		cout << fileName << " does not exists!\n";
		return false;
	}

	inFile >> this->canvasSize.x >> this->canvasSize.y; // 輸入迷宮大小

	// 設定迷宮大小
	canvas.setSize(this->canvasSize);
	routeCanvas.setSize(this->canvasSize);
	

	getMazeData(inFile);

	inFile.close();

	return true;
}

void Maze::getMazeData(ifstream &inFile) {

	int x = 0, y = 0;
	//除去第一次換行
	char buf = inFile.get();

	// end of file 或 大於 迷宮行數時停
	while (!inFile.eof() && y < canvasSize.y ) {
		buf = inFile.get();
		//遇到換行 或是 x超過列 -->可能等於下一列迷宮
		if ( buf == '\n' || x >= canvasSize.x) {
			y++;
			x = 0;
			continue;
		}

		//非換行就是迷宮資料
		this->canvas.set(x, y, buf);
		x++;
	}

	routeCanvas.copyFrom(canvas);
}

Direction Maze::nextFacing(Direction facing) {
	// 依照 右、下、左、上 切換
	return (Direction)((facing + 1) % 4);
}

RouteState Maze::goToNextStep(int x, int y, Direction facing, int& currentGoal, int totalGoal) {
	bool isCurrentGoal = isGoal(x, y);
	RouteState routeState = DEAD_END;

	if (isCurrentGoal) {
		goalHistory.add(x, y);
		routeState = TO_GOAL;

		currentGoal++;
		//已達成目標就結束
		if (currentGoal == totalGoal) return TO_GOAL;
	}
	else {
		//新增目前為走過的路徑
		canvas.set(x, y, 'V');
	}

	bool hasNextStep;
	// 重複執行找下一個點直到達成目標(G) 或是 遇到死路 就停
	do {
		int nextX = x, nextY = y;
		hasNextStep = findNextStep(nextX, nextY, facing);

		if (hasNextStep) {
			RouteState nextRouteState = goToNextStep(nextX, nextY, facing, currentGoal, totalGoal);

			//如果此點是到G的路徑
			if (nextRouteState == TO_GOAL) routeState = nextRouteState;
		}
		
	} while (currentGoal < totalGoal && hasNextStep);

	if (!isCurrentGoal && routeState == TO_GOAL) {
		routeCanvas.set(x, y, 'R');
	}


	return routeState;
}

RouteState Maze::goToNextStepShortest(int x, int y, Direction facing, int& currentGoal, int totalGoal, int depth, int &returnDepth) {
	//因為尋找路徑是 do while 所以要在這先判斷
	if (!needContinueFindShortest(currentGoal, depth, returnDepth))return DEAD_END;

	bool isCurrentGoal = canvas.get(x,y) == 'G';
	RouteState routeState = DEAD_END;

	depth = findAdjecentShortestDepth(x, y, depth) + 1;
	if (pointDepth.contains(x, y)) {
		pointDepth.setDepth(x, y, depth);
	}
	else {
		pointDepth.add(x, y, depth);
	}


	if (isCurrentGoal) {
		if (!goalHistory.contains(x, y)) goalHistory.add(x, y);
		


		//如果沒有找過或是之前最短路徑長度比現在找到的還長
		if (currentGoal != 1 || returnDepth > depth) {
			//重新找R
			if (returnDepth > depth) {
				routeCanvas.clearRoute();
			}

			routeState = TO_GOAL;
			returnDepth = depth;
			currentRouteDepth = depth;

			
		}
		

		currentGoal = 1;
		//只要遇到G絕對結束
		if (currentGoal == totalGoal) return routeState;
	}
	else {
		//新增目前為走過的路徑
		canvas.set(x, y, 'V');
	}


	bool hasNextStep;
	// 重複執行找下一個點直到達成目標(G) 或是 遇到死路 就停
	do {
		int nextX = x, nextY = y;
		hasNextStep = findNextStep(nextX, nextY, facing, depth);

		if (hasNextStep) {
			RouteState nextRouteState = goToNextStepShortest(nextX, nextY, facing, currentGoal, totalGoal, depth, returnDepth);

			//如果此點是到G的路徑
			if (nextRouteState == TO_GOAL) routeState = nextRouteState;
		}


	
	} while (hasNextStep && needContinueFindShortest(currentGoal,depth,returnDepth));


	// currentRouteDepth 是防止有可能從較遠的路徑recursion回來
	if (routeState == TO_GOAL && currentRouteDepth > depth) {
		routeCanvas.set(x, y, 'R');
		currentRouteDepth = depth;
	 }

	return routeState;
}

int Maze::findAdjecentShortestDepth(int x, int y, int depth) {

	Direction facing = RIGHT;
	for (int i = 0; i < 4; i++) {
		int cloneX = x, cloneY = y;
		getCurrentFacingNextPos(cloneX, cloneY, facing);

		if (isHistoryRoute(cloneX, cloneY)) {
			int adjecentDepth = pointDepth.getDepth(cloneX, cloneY);
			depth = min(adjecentDepth, depth);
		}
		
		facing = nextFacing(facing);
	}

	return depth;
}

void Maze::findSmallestDepthGoal(int& x, int& y) {
	int shortestDepth = -1;
	for (int i = 0; i < goalHistory.getAllPoint().size(); i++) {
		int* cord = goalHistory.getAllPoint()[i];

		int depth = pointDepth.getDepth(cord[0], cord[1]);

		if (shortestDepth == -1 || shortestDepth > depth) {
			x = cord[0];
			y = cord[1];
		}
	}
}


bool Maze::findNextStep(int& x, int& y, Direction &facing) {


	//依順序嘗試可否往前
	for (int i = 0; i < 4; i++) {
		if (canCurrentFacingForward(x, y, facing)) {
			getCurrentFacingNextPos(x, y, facing);
			return true;
		}

		facing =  nextFacing(facing);
	}
	
	//遇到死胡同
	return false;
}

bool Maze::findNextStep(int& x, int& y, Direction& facing, int currentDepth) {
	//依順序嘗試可否往前
	for (int i = 0; i < 4; i++) {
		if (canCurrentFacingForward(x, y, facing, currentDepth)) {
			getCurrentFacingNextPos(x, y, facing);
			return true;
		}

		facing = nextFacing(facing);
	}

	//遇到死胡同
	return false;
}

void Maze::getCurrentFacingNextPos(int& x, int& y, Direction facing) {
	switch(facing){
	case RIGHT:
		x++;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	default:
		y--;
	}
}

bool Maze::canCurrentFacingForward(int x, int y, Direction facing) {
	getCurrentFacingNextPos(x, y, facing);
	return isValidStep(x,y);
}

bool Maze::canCurrentFacingForward(int x, int y, Direction facing, int currentDepth) {
	getCurrentFacingNextPos(x, y, facing);
	return isValidStepShortest(x,y,currentDepth);
}

bool Maze::isBoundary(int x, int y) {
	//超出邊界
	if (x < 0 || y < 0) return true;
	if (x >= canvasSize.x || y >= canvasSize.y) return true;

	return false;
}

bool Maze::isValidStep(int x, int y) {
	if (isBoundary(x, y))return false;
	

	// 是不是有效的位置
	char state = canvas.get(x, y);


	//只有E和G可能是有效位置
	if (state == 'E') return true;

	//不能是之前已經碰過的G
	if (state == 'G') return !goalHistory.contains(x, y);

	return false;
}

bool Maze::isValidStepShortest(int x, int y, int currentDepth) {
	if (isBoundary(x, y))return false;


	// 是不是有效的位置
	char state = canvas.get(x, y);


	//只有E和G可能是有效位置
	if (state == 'E') return true;

	//是不是之前已經碰過的G
	if (state == 'G') {
		if(!goalHistory.contains(x, y)) return true;
	}


	//是不是更新後的長度
	if (state == 'V' || state == 'G') {
		if (pointDepth.contains(x, y)) {
			int depth = pointDepth.getDepth(x, y);

			if (depth > currentDepth + 1)  return true;
		}
	}

	return false;
}

bool Maze::isGoal(int x, int y) {
	if (!isValidStep(x, y)) return false;

	return canvas.get(x, y) == 'G';
}

bool Maze::needContinueFindShortest(int currentGoal, int depth, int returnDepth) {
	// 沒找到G前不能停
	if (currentGoal < 1) return true;
	
	//超出當前最短路徑的長度
	return depth < returnDepth-1;
	
}

bool Maze::isHistoryRoute(int x, int y) {
	if (isBoundary(x, y)) return false;

	// 是不是有走過的位置
	char state = canvas.get(x, y);
	
	return state == 'V';
}


void Maze::showHistoryPath(HANDLE &window) {
	canvas.show(window, goalHistory);
}

void Maze::showRoute(HANDLE& window) {
	routeCanvas.show(window, goalHistory);
}

bool Maze::findPath(int goalCount) {
	if (goalCount == 0) return true;

	int currentGoal = 0;
	
	goToNextStep(0, 0, RIGHT, currentGoal, goalCount);
	return currentGoal == goalCount;
}

int Maze::findShortestPath() {
	int currentGoal = 0, returnDepth;

	goToNextStepShortest(0, 0, RIGHT, currentGoal, 0, 0, returnDepth);
	bool success = currentGoal == 1;

	//如果成功就記錄深度
	int depth = -1;
	if (success) {
		int goalX, goalY;
		findSmallestDepthGoal(goalX, goalY);
		depth = pointDepth.getDepth(goalX, goalY);
	}

	return depth;
}

// <------- End Maze class

void printInfo() {
	cout << endl;

	cout << "\
*** Path Finding ***\n\
* 0. Quite         *\n\
* 1. One goal      *\n\
* 2. More goals    *\n\
* 3. Shortest Path *\n\
******************\n\
Input a command(0, 1, 2, 3): ";

}

void printGoalCountError() {
	cout << "### The number must be in [1,100] ###";
}

bool isAllNum(string &str) {

	for (int i = 0; i < str.size(); i++) {
		if (str[i] < '0' || str[i] > '9') return false;
	}

	return true;
}

int getUserGoalCount() {
	while (true) {
		string strNum;
		cout << "Number of G (goals): ";
		cin >> strNum;

		//檢查是不是全部都是數字
		if (!isAllNum(strNum)) {
			printGoalCountError();
			continue;
		}

		int count = atoi(strNum.c_str());

		//檢查範圍是否合理
		if (count == 0 || count > 100) {
			printGoalCountError();
			continue;		
		}

		return count;
	}
}

int main() {
	HANDLE window = GetStdHandle(STD_OUTPUT_HANDLE);

	while (true) {
		printInfo();

		int command;
		cin >> command;

		if (command == 0) break;
		
		if (command == 1 || command == 2) {

			Maze maze;

			int goals = 1;

			if (command == 2) {
				goals = getUserGoalCount();
			}


			bool success = maze.findPath(goals);

			maze.showHistoryPath(window);

			//只有成功找到所有路徑才能印 R 
			if (success) {
				cout << "\n";
				maze.showRoute(window);
			}
		}
		else if (command == 3) {
			Maze maze;
			int depth = maze.findShortestPath();

			maze.showHistoryPath(window);

			//只有成功找到所有路徑才能印 R 
			if (depth != -1) {
				cout << "\n";
				maze.showRoute(window);
				cout << "\nShortest path length: " << depth << endl;;
			}
			else {
				cout << "\nNo shortest path found!\n";
			}
		}
		else {
			cout << "Command does not exists! \n";
		}

		cout << "\n";

	}
	
	system("pause"); 
}


