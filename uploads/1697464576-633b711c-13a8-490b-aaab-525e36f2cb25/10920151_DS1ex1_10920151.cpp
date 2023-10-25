//10920151_張又晟
#include<iostream>
#include<vector>

using namespace std;

//地塊結構
struct square{
	char c;
	square * pre;
	square() {
		pre = NULL;
		c = 'O';
	}
};

//操作迷宮的類別
class maze {

private:
	int x, y,n;
	vector <square*> goal;
	vector<vector<square>> m;

public:
	maze() {
		//目標數量預設為1
		n = 1;
	}

	//輸入迷宮
	void input() {

		goal.clear();
		m.clear();

		cout << "輸入：" << endl;
		cin >> x >> y;
		vector<square>temp(y);

		for (int i = 0; i < y; i++) {
			m.push_back(temp);
			for (int j = 0; j < x; j++) {
				cin >> m[i][j].c;
			}
		}
	}

	//輸入目標數量
	void change_goal_number() {
		cout << "N = ";
		cin >> n;
	}

	void reset_goal() {
		n = 1;
	}

	//判斷周遭那些地塊可走
	bool area(int a, int b) {
		if (a >= y || a < 0) return false;
		if (b >= x || b < 0) return false;
		if (m[a][b].c != 'E' && m[a][b].c != 'G') return false;
		return true;
	}

	//DFS走法
	bool dfs(square & origin, int a, int b) {
		m[a][b].pre = &origin;
		if (m[a][b].c == 'G') {
			goal.push_back(&m[a][b]);
			if (goal .size() == n) return true;
		}
		m[a][b].c = 'V';
		if (area(a, b + 1)) if (dfs(m[a][b], a, b + 1)) return true;
		if (area(a + 1, b)) if (dfs(m[a][b], a + 1, b)) return true;
		if (area(a, b - 1)) if (dfs(m[a][b], a, b - 1)) return true;
		if (area(a - 1, b)) if (dfs(m[a][b], a - 1, b)) return true;
		return false;
	}

	//走迷宮
	void find() {
		dfs(m[0][0], 0, 0);
		for (int i = 0; i < goal.size(); i++)
			goal[i]->c = 'G';
	}

	//使走過的地塊V恢復成E
	void reversion() {
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++)
				if (m[i][j].c == 'V') m[i][j].c = 'E';
		}
	}

	//由目標開始往回走過的路徑至原點之路徑改為R
	void go_back() {
		for (int i = 0; i < goal.size(); i++){
			goal[i] = goal[i]->pre;
			while (goal[i] != goal[i]->pre) {
				if(goal[i]->c != 'G') goal[i]->c = 'R';
				goal[i] = goal[i]->pre;
			}
			goal[i]->c = 'R';
		}

		reversion();
	}

	//螢幕輸出地圖
	void print() {
		cout << "輸出：" << endl;
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				cout << m[i][j].c;
			}
			cout << endl;
		}
	}

};

int main() {

	maze m;
	int misson,leav;

	do{

		do{
			cout << "請選擇任務(1/2)：";
			cin >> misson;
		} while (misson != 1 && misson != 2);

		if (misson == 2) m.change_goal_number();
		else m.reset_goal();
		m.input();
		m.find();
		m.print();
		m.go_back();
		m.print();

		do{
			cout << "是否繼續？(是1/否0)：";
			cin >> leav;
		} while (leav != 1 && leav != 0);

	} while (leav==1);

	system("pause");
	return 0;
}