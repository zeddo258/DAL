// 中原大學 資訊二乙 11127225 賴枋佑  Data Structure Excerise01:Maze with Challenge01:Shortest path

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Input{ // 處理複雜輸入 

public:
	
	// 輸入指令0,1,2,3，否則回傳-1表示無效指令  
	static int input_command() {  
		
		string input_str;		
		cin >> input_str;

		if (input_str.length() == 1)  // 檢查是否輸入長度為1且為0,1,2,3
			if (input_str[0] == '0' or input_str[0] == '1' or input_str[0] == '2' or input_str[0] == '3' )
				return int(input_str[0] - '0');
			
		return -1; 
		
	} // input_command()
	
	// 輸入所需目標數，並確保在1~100之間後回傳 
	static int input_goal_needed() {
		
		string input_str;
		int input_int = 0;
		
		while(input_int < 1 or input_int > 100) { // 保證回傳在1~100之間 
			
			input_int = 0;
			cout<<"\nPlease input goal needed ( 1 ~ 100 ) : ";
			cin >> input_str;

			bool input_is_int = 1;
			
			for (int i = 0;i < input_str.length();i++) { // 確認輸入是否為數字 
				if(input_str[i] < '0' or input_str[i] > '9')
					input_is_int = 0;
			}
			
			if (input_is_int) {  // 如果輸入為數字 
				for (int i = 0;i < input_str.length();i++) // 將數字字串轉為整數  
					input_int = input_int*10 + (input_str[i]-'0');
			} 
			
		}
		
		return input_int;
		
	} // input_goal_needed()
	
}; // class Input

class Coordinate{  // 作為座標資料型態，儲存XY座標 
	
public:
	
	Coordinate(int in_x,int in_y) { // Constructor 
	
		// 初始化座標的 x 和 y
		x = in_x;
		y = in_y;
		
	} // Coordinate()
	
	int x ;
	int y ;
	
}; // class Coordinate

class Maze { // 迷宮主體 
	
public:
	
	enum dir { // 列舉方向右、下、左、上 
		right = 0,
		down = 1,
		left = 2,
		up = 3,
	}; 
	
	
	// 走迷宮找最短路徑遞迴函式主體  (任務三才用到) 
	void walk_maze_min_path(int x = 0, int y = 0,int dir = right) {
		
		// x,y 為目前座標， dir 為目前方向	
		
		if ( min_path_size != -1 and path.size() >= min_path_size) // 如果已經確定目前路徑長度大於目前最短路徑長度，回到上一位置 
			return;
		
		if (get(x,y) == 'G') { // 如果走到終點

			if ( min_path_size == -1 or path.size() < min_path_size) { // 嘗試更新最短路徑與其長度 
				min_path_size = path.size();	
				shortest_path = path;
			}
			return;
		}
		

		path.push_back(Coordinate(x,y)); // 將目前座標放入紀錄路徑陣列中 
		visited_matrix[x][y] = 'V'; // 將目前位置標示為Visited 
		all_V_matrix[x][y] = 'V';  // 將目前位置標示為Visited (在所有已走過的V的矩陣裡) 
		
		
		// 從目前方向順時針繞一圈嘗試向前走 
		int next_dir = dir;  // 四個方向，重複四次 
		for ( int count = 0; count < 4 ; count ++){
			
			if (next_dir == right) {  // 右 
				if (get(x+1,y) == 'E' or get(x+1,y) == 'G')
					walk_maze_min_path(x+1,y,next_dir);
			}
			
			else if  (next_dir == down) { // 下 
				if (get(x,y+1) == 'E' or get(x,y+1) == 'G')
					walk_maze_min_path(x,y+1,next_dir);			
			}
			
			else if  (next_dir == left) { // 左 
				if (get(x-1,y) == 'E' or get(x-1,y) == 'G')
					walk_maze_min_path(x-1,y,next_dir);			
			}
			
			else if  (next_dir == up) {  // 上 
				if (get(x,y-1) == 'E' or get(x,y-1) == 'G')
					walk_maze_min_path(x,y-1,next_dir);			
			}
			
			next_dir = (next_dir + 1)%4; // 改變方向 
			
		}
		
		
		visited_matrix[x][y] = 'E'; // 將位置回歸為空 
		path.pop_back(); //  將目前座標從紀錄路徑陣列中最末尾移除  
		
		return ;
		
	} // walk_maze_min_path()
	
	
	// 走迷宮遞迴函式主體 
	void walk_maze(int x = 0, int y = 0, int dir = right ) {
		// x,y 為目前座標， dir 為目前方向

		if(get(x,y) == 'G') { // 如果走到終點，將找到終點數增加，並在實際路徑矩陣畫上路徑
			goal_found ++;
			draw_real_matrix(path);
		}
		
		if (goal_found == goal_needed) // 如果所需終點數已達到，停止全部遞迴 
			return;
		
		path.push_back(Coordinate(x,y)); // 將目前座標放入紀錄路徑陣列中 
		visited_matrix[x][y] = 'V'; // 將目前位置標示為Visited 
		
		if ( dead_end(x,y) ) { // 如果遇到死路，則停止(這條路徑的)遞迴，並將錯誤的路徑座標從紀錄路徑陣列中最末尾移除  
			
		    if (!path.empty())
				path.pop_back();
				
			return ;	
			
		}		
		
		
		if (dir == right) { // 目前方向是右，如果右邊可以走就保留方向向右並向右遞迴 
			if (get(x+1,y) == 'E' or get(x+1,y) == 'G')
				walk_maze(x+1,y,dir);
		}
		
		else if  (dir == down) { // 目前方向是下，如果下面可以走就保留方向向下並向下遞迴  
			if (get(x,y+1) == 'E' or get(x,y+1) == 'G')
				walk_maze(x,y+1,dir);			
		}
		
		else if  (dir == left) { // 目前方向是左，如果左邊可以走就保留方向向左並向左遞迴 
			if (get(x-1,y) == 'E' or get(x-1,y) == 'G')
				walk_maze(x-1,y,dir);			
		}
		
		else if  (dir == up) { // 目前方向是上，如果上面可以走就保留方向向上並向上遞迴  
			if (get(x,y-1) == 'E' or get(x,y-1) == 'G')
				walk_maze(x,y-1,dir);			
		}

		walk_maze(x,y,(dir + 1)%4); // 將方向順時針旋轉進行遞迴 
		
		
		if ( dead_end(x,y) ) {  // 如果遇到死路，則停止(這條路徑的)遞迴，並將錯誤的路徑座標從紀錄路徑陣列中最末尾移除  
			  
		    if (!path.empty())
				path.pop_back();

			return ;	
			
		}
		
		return ;
		
	} // walk_maze()
	
	// 初始化資料 
	void init() { 
		
		visited_matrix.clear();
    	real_matrix.clear();
    	all_V_matrix.clear(); 
    	path.clear();
    	
    	goal_found = 0;
    	goal_needed = 1; // 所需目標數初始化為1，如果只需一個目標就不需要再更動 
		
    	max_x = -1; 
    	max_y = -1;
		min_path_size = -1;
    	
	} // init()
	
	// 回傳該座標是否為死路
	bool dead_end(int x, int y) {  
		
		return (get(x,y+1) != 'E' and get(x+1,y) != 'E' and 
		    	get(x,y-1) != 'E' and get(x-1,y) != 'E' and
				get(x,y+1) != 'G' and get(x+1,y) != 'G' and 
		    	get(x,y-1) != 'G' and get(x-1,y) != 'G' );
	
	} // dead_end()
	
	// 回傳該座標在已探訪路徑矩陣中為何種字符，若超出矩陣範圍則回傳'O'表示不能行走 
	char get(int x, int y) { 
		
		if ( 0 <= x and x < max_x and 0 <= y and y < max_y)
			return visited_matrix[x][y];
		else
			return 'O';
			
	} // get()
	
	// 從檔案編號讀入檔案，回傳是否成功讀入 
	bool read_file(string filenum) { 
	
		string filename = "input" + filenum + ".txt";
		ifstream file( filename.c_str() ); 
		
		if (!file.is_open()) { // 如果檔案無法開啟，輸出錯誤訊息後回傳 0 
            cout << "\n" << filename  <<" does not exist!"<< "\n";
            return 0;
        }
        
        if (!(file >> max_x >> max_y)) { // 如果讀入資料時出問題，輸出錯誤訊息關閉文件後回傳 0 
            cout << "\nAn error occurred while inputing from file: " << filename << "\n";
            file.close();
            return 0;
        }
        
		// 根據行列重新配置矩陣大小 
		// 橫軸為x(右為正)，縱軸為y(下為正) 
		visited_matrix.resize(max_x);
		for (int i = 0 ; i < max_x ; i++ ) 
			visited_matrix[i].resize(max_y);
		
		// 讀入迷宮內容
		for (int j = 0; j < max_y; j++) {
			 
			for (int i = 0; i < max_x; i++) {  
	
				// 如果讀入資料時出問題，輸出錯誤訊息關閉文件後回傳 0 
                if (!(file >> visited_matrix[i][j]) or ( visited_matrix[i][j] != 'E' and visited_matrix[i][j] != 'O' and visited_matrix[i][j] != 'G') ) {
                    cout << "\nAn error occurred while inputing from file: " << filename << "\n";
                    file.close();
                    return 0;
                }
                
            }
            
        }
        
        
        // 檢查左上角是否為空格，如果不是，輸出錯誤訊息關閉文件後回傳 0 
        if (visited_matrix[0][0] != 'E') {
        	
            cout << "\nAn error occurred while inputing from file: " << filename << "\n";
            file.close();
            return 0;	

		}
		
		
		// 檢查檔案裡面是否有其他東西留下(檔案是否不符合輸入格式)，如果有，輸出錯誤訊息關閉文件後回傳 0 
        string trash = "";
        while (!file.eof()){
        	
        	file >> trash;
        	if ( trash != "" ) {
        		cout << "\nAn error occurred while inputing from file: " << filename << "\n";
                file.close();
				return 0;
			}
			
		} 

		real_matrix = visited_matrix; // 複製一份矩陣作為實際路徑矩陣 
		all_V_matrix = visited_matrix;
		file.close(); // 關閉文件 
		return 1;
	} // read_file()
	
	// 根據所給路徑在實際路徑矩陣上畫上實際路徑 
	void draw_real_matrix(vector<Coordinate> path) { 
		
		for (int i = 0;i<path.size();i++)
			if (real_matrix[path[i].x][path[i].y] != 'G')
				real_matrix[path[i].x][path[i].y] = 'R'; 
		
	} // draw_real_matrix()
	
	void draw_real_matrix_by_shortest_path() {
		
		draw_real_matrix(shortest_path);
		
	} // draw_real_matrix_by_shortest_path() 
	
	// 修正已探訪路徑矩陣的Goal(因為在walk maze時會被變成Visited) 
	void correct_visited_matrix() {
		
		// 將實際路徑矩陣的G複製到儲存已探訪路徑矩陣 
		for (int j = 0; j < max_y; j++) {
            for (int i = 0; i < max_x; i++) {
                    if (real_matrix[i][j] == 'G')
                    	visited_matrix[i][j] = 'G';
            }
        }
		
	} // correct_visited_matrix()

	// 輸出已探訪路徑矩陣 
	void print_visited_matrix() {
		
		for (int j = 0; j < max_y; j++) {
            for (int i = 0; i < max_x; i++) {
                cout << visited_matrix[i][j] ;
            }
            cout << "\n";
        }

	} // print_visited_matrix()
	
	// 輸出已探訪路徑矩陣 
	void print_all_V_matrix() {
		
		for (int j = 0; j < max_y; j++) {
            for (int i = 0; i < max_x; i++) {
                cout << all_V_matrix[i][j] ;
            }
            cout << "\n";
        }

	} // print_all_V_matrix()
	
	
	// 輸出實際路徑矩陣 
	void print_real_matrix() {
		
		for (int j = 0; j < max_y; j++) {
            for (int i = 0; i < max_x; i++) {
                cout << real_matrix[i][j] ;
            }
            cout << "\n";
        }

	} // print_real_matrix()
	
	void print_shortest_path(){
		
		for(int i = 0 ; i < shortest_path.size();i++) {
			
			cout << shortest_path[i].x<< "|" << shortest_path[i].y << " ";
		}
		cout << "\n";
	}
	
	// 更動所需目標數 
	void set_goal_needed(int goal_needed_input){ 
		
		goal_needed = goal_needed_input;
		
	} // set_goal_needed()
	
	// 回傳所需目標數是否找齊 
	bool found_all_goal_needed(){
		
		return goal_found == goal_needed;
	
	} // found_all_goal_needed()
	
	int get_min_path_size(){
		
		return min_path_size;
		
	} // get_min_path_size()
	
private:

	vector< vector<char> > visited_matrix; // 儲存已探訪路徑的矩陣 
	vector< vector<char> > real_matrix;    // 儲存真實路徑的矩陣 
	vector< vector<char> > all_V_matrix;   // 儲存所有已走過的V的矩陣  (任務三才用到) 
	
	
	vector<Coordinate> path; // 儲存目前走的路徑的陣列 
	vector<Coordinate> shortest_path; // 儲存找到的最短路徑的陣列 (任務三才用到) 
	int min_path_size; // 儲存最短路徑的長度 (任務三才用到)  
	
	
	int goal_needed; // 儲存所需目標數 
	int goal_found;  // 儲存目前找到的目標數 
	
	// 儲存矩陣的大小 
	int max_x;
	int max_y;  
	
	
	
}; // class Maze


int main() {

	string filenum;
	int command;
	Maze maze_obj = Maze() ;
	
	do{
		
		cout <<"\n*** Maze Path Finding ***";
		cout <<"\n* 0. Quit Program       *";
		cout <<"\n* 1. One  Goal          *";
		cout <<"\n* 2. More Goals         *";
		cout <<"\n* 3. Find Shortest path *";
		cout <<"\n*************************"; 
		cout <<"\nPlease input a command(0, 1, 2, 3): ";
		
		command = Input::input_command(); // will get 0, 1, 2, 3, or -1(無效指令)
		
		if ( command == 1 || command == 2 || command == 3 ) {  // 1 or 2 or 3 means walk maze
			
			cout <<"\nPlease input file number: ";
			cin >> filenum;
			
			maze_obj.init(); // 初始化 
			
			if (maze_obj.read_file(filenum)) { // 讀入文件，如果成功才進行走迷宮 
			
				if ( command == 1 || command == 2 ) { // 模式 1 or 2, 正常行走 
			
					if (command == 2) // 如果需要多個Goal，進行輸入 
						maze_obj.set_goal_needed ( Input::input_goal_needed() ) ; // goal_needed will set to 1~100 
						
					maze_obj.walk_maze(); // 遞迴函式主體 
					maze_obj.correct_visited_matrix(); // 修正已探訪路徑矩陣的Goal 
					
					cout << "\n";  
					maze_obj.print_visited_matrix(); // 輸出已探訪路徑矩陣 
					
					if ( maze_obj.found_all_goal_needed() ) { // 如果找齊所需目標，輸出實際路徑矩陣 
						cout << "\n"; 
						maze_obj.print_real_matrix();
					}
					
				}
				
				else if (command == 3) { // 找最短路徑 
				
					maze_obj.walk_maze_min_path(); // 遞迴找最短路徑函式主體  
	
					cout << "\n"; 
					maze_obj.print_all_V_matrix(); // 輸出包含所有已走過的V的矩陣 
					
					if ( maze_obj.get_min_path_size() != -1 ){ // 如果最短路徑長不為初始值-1(至少找到一條路徑) 
						
						cout << "\n"; 
						maze_obj.draw_real_matrix_by_shortest_path();  // 在實際路徑矩陣繪製最短路徑 
						maze_obj.print_real_matrix();  // 輸出實際路徑矩陣 
						cout <<"\nShortest path length = "<< maze_obj.get_min_path_size() + 1<< "\n"; // 輸出最短路徑長度					
						
					}
					
					else
						cout <<"\n*** There is no way to find any Goal! ***\n";
				} 
			}
		}
		
		else if ( command == 0 )  // 0 means stop the program
			break;
		else  
			cout << "\nThere is no such command!\n";
			
	} while(true);
	
	cout << "\n";
	system("pause");
	
} // main() 





