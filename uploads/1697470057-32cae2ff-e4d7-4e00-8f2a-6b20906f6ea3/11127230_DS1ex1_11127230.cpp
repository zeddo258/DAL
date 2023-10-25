// 11127230 鍾帛勳
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class Solve {
	
private:
	char maze[100][100];
    char maze1[100][100]; // output one
	char maze2[100][100]; // output two
	char maze3[100][100];
	char maze4[100][100];
public:
	int n, m;
	bool used[1000][1000];
	int xd[4] = {0, 1, 0, -1}; // array of diraction
	int yd[4] = {1, 0, -1, 0}; 
	int goalnum, goalnum2; 
	int ans = 1e9;
	
	int min(int a, int b) {
		if (a < b) {
			return a;
		}
		return b;
	}
	
	void dfs(int x, int y, bool & pathfind, int dir, int count) {
		int k;
		pathfind = false; // set default pathfind false
		bool hasroute = false;
		if (maze2[x][y] == 'G') { 
			goalnum--; // find one goal
			pathfind = true; // this path can find the goal so pathfind is true
			if (goalnum == 0) return; // if all goal isfind than stop
		}
		
		if (maze1[x][y] != 'G') maze1[x][y] = 'V';
		for (k = dir; k < dir+4; k++) { // find four diraction
			 // set current postion of maze1 to 'V'
			if (x+xd[k%4] >= 0 && x+xd[k%4] < n &&
				y+yd[k%4] >= 0 && y+yd[k%4] < m &&
				(maze2[x+xd[k%4]][y+yd[k%4]] != 'O' &&
				used[x+xd[k%4]][y+yd[k%4]] == false)) { // if next step is legal than keep find
				used[x+xd[k%4]][y+yd[k%4]] = true; // set now position used to true, so next than can't find the step which pass already
				dfs(x+xd[k%4], y+yd[k%4], pathfind, k%4, count+1); 
			}
			
			if (pathfind) { // if pathfind return is true than set 'R' to maze2
				hasroute = true;
				if (maze2[x][y] != 'G') {
					maze2[x][y] = 'R';
				}
				if (goalnum == 0) break; // if all goal is find than stop
			}
		}
		pathfind = hasroute;
	}
	
	void copymap() {
		int i;
		for (i = 0; i < n; i++) {
			strcpy(maze4[i], maze[i]);
		}
	}
	
	bool shortest(int x, int y, int dir, int count) {
		int k;
		bool pathfind = false; // set default pathfind false
		bool hasroute = false;
		if (maze3[x][y] == 'G') {
			pathfind = true; // this path can find the goal so pathfind is true
			ans = min(count, ans);
			copymap();
			return pathfind;
		}
		
		if (maze3[x][y] != 'G') maze3[x][y] = 'V'; // set current postion of maze1 to 'V'
		for (k = dir; k < dir+4; k++) { // find four diraction
			if (x+xd[k%4] >= 0 && x+xd[k%4] < n &&
				y+yd[k%4] >= 0 && y+yd[k%4] < m &&
				(maze2[x+xd[k%4]][y+yd[k%4]] != 'O' &&
				used[x+xd[k%4]][y+yd[k%4]] == false) && 
				count < ans) { // if next step is legal than keep find
				used[x+xd[k%4]][y+yd[k%4]] = true; // set now position used to true, so next than can't find the step which pass already
				pathfind |= shortest(x+xd[k%4], y+yd[k%4], k%4, count+1); 
				used[x+xd[k%4]][y+yd[k%4]] = false;
			}
			
			if (pathfind) { // if pathfind return is true than set 'R' to maze2
				hasroute = true;
				if (maze4[x][y] != 'G') {
					maze4[x][y] = 'R';
					// cout << x << " " << y << endl;
				}

			}
		}
		pathfind = hasroute;
		return pathfind;
	}
	
	void wrmaze(int i, char* str) { // use this function to input the maze
		strcpy(maze[i], str);
		strcpy(maze1[i], str);
		strcpy(maze2[i], str);
		strcpy(maze3[i], str);
		strcpy(maze4[i], str);
	}
	
	char* getmaze1(int i) { // use this function to get the valus of maze
		return maze1[i];
	}
	char* getmaze2(int i) {
		return maze2[i];
	}
	char* getmaze3(int i) {
		return maze3[i];
	}
	char* getmaze4(int i) {
		return maze4[i];
	}
};


int main() {
	int i, j;
	char com;
	Solve solve ;
	do {
		// input
		cout << "*** Path Finding ***" << endl;
		cout << "* 0. Quit          *" << endl;
		cout << "* 1. One goal      *" << endl;
	    cout << "* 2. More goals    *" << endl;
	    cout << "* 3. Shortest path *" << endl;
		cout << "********************" << endl;
		cout << "Input a command(0, 1, 2, 3): ";
		cin >> com;
		solve.ans = 1e9;
		cout << endl;
		if (com == '0') {
			break;
		}
		if (com != '1' && com != '2' && com != '3') {
			cout << "Command does not exist!" << endl;
			cout << endl;
			continue;
		}
		
		string testnum;
		string teststr;
		ifstream in;
		cout << "Input a file number: ";
		cin >> testnum;
		cout << endl;
		teststr = "input" + testnum + ".txt";
		in.open(teststr);
		if (in.fail()) {
			cout << teststr + " does not exist!" << endl << endl;
			cout << endl;
			continue;
		}
		
		in >> solve.m >> solve.n;
		solve.goalnum = 1; // set default goalnum is one
		char strin[105];
		for (i = 0; i < solve.n; i++) {
			in >> strin;
			solve.wrmaze(i, strin);
			for (j = 0; j < solve.m; j++) {
				solve.used[i][j] = false;
			}
		}
		
		if (com == '2') {
			cout << "Number of G (goals): ";
			cin >> solve.goalnum; 
			cout << endl;
		}
		
		for (i = 0; i < solve.n; i++) {
			for (j = 0; j < solve.m; j++) {
				solve.used[i][j] = false;
			}
		}
		
		// solve
		bool temp;
		bool haver3 = false;
		solve.dfs(0, 0, temp, 0, 0);
		for (i = 0; i < solve.n; i++) {
			for (j = 0; j < solve.m; j++) {
				solve.used[i][j] = false;
			}
		}
		haver3 = solve.shortest(0, 0, 0, 0);
		// output
		if (com == '1' || com == '2') {
			for (i = 0; i < solve.n; i++) {
				cout << solve.getmaze1(i) << endl;
			}
			cout << endl;
			if (com == '2' && solve.goalnum == 0) {
				for (i = 0; i < solve.n; i++) {
					cout << solve.getmaze2(i) << endl;
				}
			}
			else if (com == '1' && solve.goalnum != 0) {
				for (i = 0; i < solve.n; i++) {
					cout << solve.getmaze1(i) << endl;
				}
			}
			else if (com == '1' && solve.goalnum == 0) {
				for (i = 0; i < solve.n; i++) {
					cout << solve.getmaze2(i) << endl;
				}
			}
		}
		else if (com == '3') {
			for (i = 0; i < solve.n; i++) {
				cout << solve.getmaze3(i) << endl;
			}
			cout << endl;
			if (haver3) {
				for (i = 0; i < solve.n; i++) {
					cout << solve.getmaze4(i) << endl;
				}
			}
			
			cout << endl;
			cout << "Shortest path length = " << solve.ans+1 << endl;
		}
		
		
	} while (true);
	
	return 0;
}