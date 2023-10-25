#include <cstdio>
#include <fstream> 
#include "iostream"
#include <vector>
#include <string>
#include <string.h>
#include <sstream> 

#define oneG 1
#define MoreG 2
/*
input101.txt
const int N = 6; 
const int M = 6+1; 
char orignaL_maze[N][M] = {
"EEEEOO",
"OEOEEE",
"GEEEOE",
"OOEOOE",
"EEEOOO",
"OOEEEE",
};

input102.txt
const int N = 10; 
const int M = 8+1; 
char orignaL_maze[N][M] = {
"EEEEOOEO",
"OEOEEEEE",
"EEEOOEOE",
"EOEOEOEG",
"EEEOEOEO",
"EOEEEOEO",
"EOEOEEEE",
"EEEEOEOE",
"OEOEEEEE",
"EEEEOEEE"
};

input103.txt
const int N = 6; 
const int M = 6+1; 
char orignaL_maze[N][M] = {
"EEEEOO",
"OEOEEE",
"EGEEOE",
"OOEOOE",
"EEEOOO",
"OOEEEG",

};

input104.txt
const int N = 10; 
const int M = 8+1; 
char orignaL_maze[N][M] = {
"EEEEOOEO",
"OEOEEEEE",
"EEEOOEOE",
"EOEOEOEG",
"EEEOEOEO",
"EOEEEOEO",
"EOEOEEEE",
"EEEOOEOG",
"OEOEEEEE",
"EEEOEEG",

};
*/
using namespace std;
// ¥þ§½ÅÜ¶q¡A¥Î©ó³]¸m¥Ø¼Ð¼Æ¶q 
int target_count;

// ©w¸q²¾°Ê¤è¦Vªº¼W¶q
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
typedef enum
{
	Copy = -1,
	Right,
	Down,
	Left,
	Up
} Moves;

// ¥Nªí§¤¼Ð
class CoXY
{
	int y;
	int x;

public:
	CoXY() :y(0), x(0)
	{}; 

	CoXY(int py, int px) 
	{
		y = py;
		x = px;
	}
	CoXY(const CoXY & pt) : y(pt.y), x(pt.x)
	{}; 

	//*******/
	//setXY(py,px):set up the coordinate(py , px)
	//getX(pt): get the X of pt
	//getY(pt): get the Y of pt
	//nextXY(dir): get tje corrdinate after the move dir
	//match(pt): check if the coordinate is the same as pt
	//inRange(maxLimit):check if the coordinate is in the range
	//******/

	void setXY(const int py, const int px)
	{
		y = py;
		x = px;
	}
	int getX() const
	{
		return x;
	}
	int getY() const
	{
		return y;
	}
	CoXY nextXY(Moves dir) const // ®Ú¾Ú²¾°Ê¤è¦VÀò¨ú·s§¤¼Ð
	{
		CoXY pt(y, x);

		switch (dir)
		{
			case Right:
				pt.x++;
				break;
			case Down:
				pt.y++;
				break;
			case Left:
				pt.x--;
				break;
			case Up:
				pt.y--;
				break;
			default:
				break;
		}
		return pt;
	}
	bool match(const CoXY & pt) const // §PÂ_¬O§_»P¥t¤@§¤¼Ð¬Û¤Ç°t
	{
		if ((y == pt.y) && (x == pt.x))
			return true;

		return false;
	}
	bool inRange(const CoXY & maxLimit) const // §PÂ_§¤¼Ð¬O§_¦b½d³ò¤º
	{
		if ((y >= 0) && (y < maxLimit.y) && (x >= 0) && (x < maxLimit.x))
			return true;
		return false;
	}
};

// ¥D­nªº°g®c¡A¥]§t°g®c¸ê®Æ©M¬ÛÃö¾Þ§@
class Maze
{
	char **mazeArray;  // ¥Î©ó¾Þ§@ªº°g®c°}¦C
	char **orignal_maze; // ­ì©l°g®c°}¦C
	int N ; // ¦æ¼Æ
	int M ; // ¦C¼Æ
	int goal_count; // ­p¼Æ¾¹¡A¥Î©ó°O¿ý¤w§ä¨ìªº¥Ø¼Ð¼Æ

 // ¤º³¡ªºÀ°§U¨ç¼Æ¡AÀË¬d¬Y¦ì¸m¬O§_¥i¹F
	bool isSafe(int x, int y) {
		return (x >= 0 && x < N && y >= 0 && y < M - 1 && mazeArray[x][y] != 'O' && mazeArray[x][y] != 'V');
	}
	// »¼Âk¨ç¼Æ¡A¬d§ä¥X¤f
	int findExit(int x, int y, int prevDirection)
	{
		int status = 0;
		if (mazeArray[x][y] == 'G')
		{
			//cout << "x = " << x << "y = " << y << endl;
			status = 1;
			goal_count++;
		}
		if (goal_count == target_count)
		{
			status = 2;
			return status;
		}
		int directions[] = { prevDirection, (prevDirection + 1) % 4, (prevDirection + 2) % 4, (prevDirection + 3) % 4 };

		for (int i = 0; i < 4; i++)
		{
			int direction = directions[i];
			int newX = x + dx[direction];
			int newY = y + dy[direction];

			/*if(maze[x][y] != 'G' )*/mazeArray[x][y] = 'V';
			if (isSafe(newX, newY)) {

				status = findExit(newX, newY, direction);
				if (status == 2)
				{
					return status;
				}

				if (status == 0)mazeArray[x][y] = 'R';
				//print(maze);
				//cout << endl;
			}
			else
			{
				if (status == 0)mazeArray[x][y] = 'R';
			}
		}

		return status;
	}

public:
	Maze() :goal_count(0){};
	Maze(const Maze& pt) : mazeArray(pt.mazeArray), orignal_maze(pt.orignal_maze), N(pt.N), M(pt.M) ,goal_count(0) {}
	bool load(string fileName);  // ±q¤å¥ó¥[¸ü°g®c
	bool findGoals(void); // ´M§ä¥Ø¼Ð©Î¥X¤f
	void show(void); // Åã¥Ü°g®c
	void clr(void);
};
void Maze::show()
{
	int i, j;

	if (goal_count != 0)
	{
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < M - 1; j++)
			{
				if (orignal_maze[i][j] == 'G') cout << orignal_maze[i][j];
				else if (mazeArray[i][j] == 'R') cout << 'V';
				else cout << mazeArray[i][j];

			}
			cout << endl;
		}
		cout << endl;
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < M - 1; j++)
			{
				if (orignal_maze[i][j] == 'G') cout << orignal_maze[i][j];
				else if (mazeArray[i][j] == 'R') cout << 'E';
				else if (mazeArray[i][j] == 'V') cout << 'R';
				else cout << mazeArray[i][j];

			}
			cout << endl;
		}

	}
	else
	{
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < M - 1; j++)
			{
				if (orignal_maze[i][j] == 'G') cout << orignal_maze[i][j];
				else if (mazeArray[i][j] == 'R') cout << 'V';
				else cout << mazeArray[i][j];
			}
			cout << endl;
		}
	}
}
bool Maze::findGoals(void)
{
	int status = findExit(0, 0, 0);//‘å³

	if (status == 0) return false;
	else return true;
}
bool Maze::load(string fileName)
{
	FILE *infile = 0;
	bool success = false;
	CoXY coMax(0, 0);

	fileName = "input" + fileName + ".txt";
	//ifstream inputFile("maze.txt");
	infile = fopen(fileName.c_str(), "r");
	if (!infile)
		cout << endl << fileName << "does not exist!" << endl;
	else
	{
		int arg1 = 0, arg2 = 0;
		fscanf(infile, "%d %d", &arg1, &arg2);
		coMax.setXY(arg2, arg1);
		if ((coMax.getY() > 0) && (coMax.getX() > 0))
		{
			int line = 0;
			M = coMax.getX()+1;
			N = coMax.getY();
			char *temp = new char[coMax.getX() + 1];

			mazeArray = new char*[coMax.getY()];
			orignal_maze = new char*[coMax.getY()];
			while (fscanf(infile, "%s", temp) != EOF)
			{
				mazeArray[line] = new char[coMax.getX() + 1];
				orignal_maze[line] = new char[coMax.getX() + 1];
				int templine = line;
				strcpy(mazeArray[line++], temp);
				strcpy(orignal_maze[templine++], temp);
			}
			if (line == coMax.getY())
				success = true;
		}

		fclose(infile);
	}
	return success;
}
void Maze::clr(void)
{
    for(int i = 0; i < N; i++)
    {
        delete [] mazeArray[i];
        delete [] orignal_maze[i];
    }

    delete [] orignal_maze;
    delete [] mazeArray;
}

int goal_count = 0;

const int N = 6; 
const int M = 6 + 1; 
char orignaL_maze[N][M] = {
	"EEEEOO",
    "OEOEEE",
    "GEEEOE",
    "OOEOOE",
    "EEEOOO",
    "OOEEEE",

};

char maze[N][M];

int main()
{
	int command = 0;

	do
	{
		Maze aMaze; // ³Ð«Ø°g®cª«¥ó
		string fileName;
		target_count = oneG;

		cout << endl << "***Path Finding***";
		cout << endl << "0. Quit";
		cout << endl << "1. One goal";
		cout << endl << "2. More goal";
		cout << endl << "*******************";
		cout << endl << "Input a command(0,1,2):";
		cin >> command;

		if ((command == 1) || (command == 2))
		{
			if (command == 2)
			{
				target_count = MoreG;
				cout << endl << "input goal number:";
				cin >> target_count;
			}

			cout << endl << "input a file number (eg.,101,102.. ):";
			cin >> fileName;

			if (aMaze.load(fileName))
			{
				int a = 0;
				Maze vMaze(aMaze);
				bool success = vMaze.findGoals();
				if (success)
				{
					vMaze.show();
				}
				else
				{
					aMaze.show();
				}
                vMaze.clr();
				//bool success = aMaze.findGoals(vMaze);
			}
			aMaze.clr();
		}

	} while (true); // «O«ù¦b´`Àô¤¤¡Aª½¨ì¿ï¾Ü°h¥X


	return 0;
}
