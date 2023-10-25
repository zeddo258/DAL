//10920151_�i�S��
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

//�a�����c
struct square{
	char c;
	int a;
	int b;
	square * pre;
	square() {
		pre = NULL;
		c = 'O';
	}
};

//�ާ@�g�c�����O
class maze {

private:
	int x, y,n;
	int path_lenth;
	vector <square*> goal;
	vector<vector<square>> m;

public:
	maze() {
		//�ؼмƶq�w�]��1
		n = 1;
	}

	//��J�g�c
	void input() {

		goal.clear();
		m.clear();
		path_lenth = 1;

		cout << "��J�G" << endl;
		cin >> x >> y;
		vector<square>temp(y);

		for (int i = 0; i < y; i++) {
			m.push_back(temp);
			for (int j = 0; j < x; j++) {
                m[i][j].a=i;
                m[i][j].b=j;
				cin >> m[i][j].c;
			}
		}
	}

	//��J�ؼмƶq
	void change_goal_number() {
		cout << "N = ";
		cin >> n;
	}

	void reset_goal() {
		n = 1;
	}

	//�P�_�P�D���Ǧa���i��
	bool area(int a, int b) {
		if (a >= y || a < 0) return false;
		if (b >= x || b < 0) return false;
		if (m[a][b].c != 'E' && m[a][b].c != 'G') return false;
		return true;
	}

	//DFS���k
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

	//BFS��̵u���|
	void find_2(){
	    queue<square*> f;
		m[0][0].pre = &m[0][0];
	    f.push(&m[0][0]);
		int a;
		int b;
	    while( !f.empty() && f.front()->c != 'G'){
			f.front()->c = 'V';
			a = f.front()->a;
			b = f.front()->b;
			if (area(a, b + 1)) {
				f.push(&m[a][b + 1]);
				m[a][b + 1].pre = f.front();
			}
			if (area(a + 1, b)) {
				f.push(&m[a + 1][b]);
				m[a+1][b].pre = f.front();
			}
			if (area(a, b - 1)) {
				f.push(&m[a][b - 1]);
				m[a][b - 1].pre = f.front();
			}
			if (area(a - 1, b)) {
				f.push(&m[a - 1][b]);
				m[a-1][b].pre = f.front();
			}
            f.pop();
        }

		if (!f.empty()) goal.push_back(f.front());
	}

	//���g�c
	void find_1() {
		dfs(m[0][0], 0, 0);
		for (int i = 0; i < goal.size(); i++)
			goal[i]->c = 'G';
	}

	//�Ϩ��L���a��V��_��E
	void reversion() {
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++)
				if (m[i][j].c == 'V') m[i][j].c = 'E';
		}
	}

	//�ѥؼж}�l���^���L�����|�ܭ��I�����|�אּR
	void go_back() {
		for (int i = 0; i < goal.size(); i++){
			goal[i] = goal[i]->pre;
			while (goal[i] != goal[i]->pre) {
				if(goal[i]->c != 'G') goal[i]->c = 'R';
				goal[i] = goal[i]->pre;
				path_lenth++;
			}
			goal[i]->c = 'R';
			path_lenth++;
		}

		reversion();
	}

	//�ù���X�a��
	void print() {
		//������X���L���|
		cout << "\n��X�G" << endl;
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				cout << m[i][j].c;
			}
			cout << endl;
		}
		cout << endl;

		//�Y�L�ؼЪ������h�h�X
		if (goal.empty()) return;

		//�^���ؼЦܭ��I�����|
		go_back();

		//��X�ؼЦܭ��I�����|
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				cout << m[i][j].c;
			}
			cout << endl;
		}
		cout << endl;

	}

	void print_path_lenth() {
		if (goal.empty())path_lenth = 0;
		cout << "Shortest path length = " << path_lenth <<endl<< endl;
	}

};

int main() {

	maze m;
	int misson,leav;

	do{

		do{
			cout << "�п�ܥ���(1/2/3)�G";
			cin >> misson;
		} while (misson != 1 && misson != 2 && misson != 3);

		if (misson == 2) m.change_goal_number();
		else m.reset_goal();
		m.input();
		if (misson == 3)m.find_2();
		else m.find_1();
		m.print();
		if (misson == 3) m.print_path_lenth();

		do{
			cout << "�O�_�~��H(�O1/�_0)�G";
			cin >> leav;
		} while (leav != 1 && leav != 0);

	} while (leav==1);

	system("pause");
	return 0;
}
