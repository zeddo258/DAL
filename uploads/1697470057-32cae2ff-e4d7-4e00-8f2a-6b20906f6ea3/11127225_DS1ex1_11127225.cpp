// ����j�� ��T�G�A 11127225 ��D��  Data Structure Excerise01:Maze with Challenge01:Shortest path

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Input{ // �B�z������J 

public:
	
	// ��J���O0,1,2,3�A�_�h�^��-1��ܵL�ī��O  
	static int input_command() {  
		
		string input_str;		
		cin >> input_str;

		if (input_str.length() == 1)  // �ˬd�O�_��J���׬�1�B��0,1,2,3
			if (input_str[0] == '0' or input_str[0] == '1' or input_str[0] == '2' or input_str[0] == '3' )
				return int(input_str[0] - '0');
			
		return -1; 
		
	} // input_command()
	
	// ��J�һݥؼмơA�ýT�O�b1~100������^�� 
	static int input_goal_needed() {
		
		string input_str;
		int input_int = 0;
		
		while(input_int < 1 or input_int > 100) { // �O�Ҧ^�Ǧb1~100���� 
			
			input_int = 0;
			cout<<"\nPlease input goal needed ( 1 ~ 100 ) : ";
			cin >> input_str;

			bool input_is_int = 1;
			
			for (int i = 0;i < input_str.length();i++) { // �T�{��J�O�_���Ʀr 
				if(input_str[i] < '0' or input_str[i] > '9')
					input_is_int = 0;
			}
			
			if (input_is_int) {  // �p�G��J���Ʀr 
				for (int i = 0;i < input_str.length();i++) // �N�Ʀr�r���ର���  
					input_int = input_int*10 + (input_str[i]-'0');
			} 
			
		}
		
		return input_int;
		
	} // input_goal_needed()
	
}; // class Input

class Coordinate{  // �@���y�и�ƫ��A�A�x�sXY�y�� 
	
public:
	
	Coordinate(int in_x,int in_y) { // Constructor 
	
		// ��l�Ʈy�Ъ� x �M y
		x = in_x;
		y = in_y;
		
	} // Coordinate()
	
	int x ;
	int y ;
	
}; // class Coordinate

class Maze { // �g�c�D�� 
	
public:
	
	enum dir { // �C�|��V�k�B�U�B���B�W 
		right = 0,
		down = 1,
		left = 2,
		up = 3,
	}; 
	
	
	// ���g�c��̵u���|���j�禡�D��  (���ȤT�~�Ψ�) 
	void walk_maze_min_path(int x = 0, int y = 0,int dir = right) {
		
		// x,y ���ثe�y�СA dir ���ثe��V	
		
		if ( min_path_size != -1 and path.size() >= min_path_size) // �p�G�w�g�T�w�ثe���|���פj��ثe�̵u���|���סA�^��W�@��m 
			return;
		
		if (get(x,y) == 'G') { // �p�G������I

			if ( min_path_size == -1 or path.size() < min_path_size) { // ���է�s�̵u���|�P����� 
				min_path_size = path.size();	
				shortest_path = path;
			}
			return;
		}
		

		path.push_back(Coordinate(x,y)); // �N�ثe�y�Щ�J�������|�}�C�� 
		visited_matrix[x][y] = 'V'; // �N�ثe��m�Хܬ�Visited 
		all_V_matrix[x][y] = 'V';  // �N�ثe��m�Хܬ�Visited (�b�Ҧ��w���L��V���x�}��) 
		
		
		// �q�ثe��V���ɰw¶�@����զV�e�� 
		int next_dir = dir;  // �|�Ӥ�V�A���ƥ|�� 
		for ( int count = 0; count < 4 ; count ++){
			
			if (next_dir == right) {  // �k 
				if (get(x+1,y) == 'E' or get(x+1,y) == 'G')
					walk_maze_min_path(x+1,y,next_dir);
			}
			
			else if  (next_dir == down) { // �U 
				if (get(x,y+1) == 'E' or get(x,y+1) == 'G')
					walk_maze_min_path(x,y+1,next_dir);			
			}
			
			else if  (next_dir == left) { // �� 
				if (get(x-1,y) == 'E' or get(x-1,y) == 'G')
					walk_maze_min_path(x-1,y,next_dir);			
			}
			
			else if  (next_dir == up) {  // �W 
				if (get(x,y-1) == 'E' or get(x,y-1) == 'G')
					walk_maze_min_path(x,y-1,next_dir);			
			}
			
			next_dir = (next_dir + 1)%4; // ���ܤ�V 
			
		}
		
		
		visited_matrix[x][y] = 'E'; // �N��m�^�k���� 
		path.pop_back(); //  �N�ثe�y�бq�������|�}�C���̥�������  
		
		return ;
		
	} // walk_maze_min_path()
	
	
	// ���g�c���j�禡�D�� 
	void walk_maze(int x = 0, int y = 0, int dir = right ) {
		// x,y ���ثe�y�СA dir ���ثe��V

		if(get(x,y) == 'G') { // �p�G������I�A�N�����I�ƼW�[�A�æb��ڸ��|�x�}�e�W���|
			goal_found ++;
			draw_real_matrix(path);
		}
		
		if (goal_found == goal_needed) // �p�G�һݲ��I�Ƥw�F��A����������j 
			return;
		
		path.push_back(Coordinate(x,y)); // �N�ثe�y�Щ�J�������|�}�C�� 
		visited_matrix[x][y] = 'V'; // �N�ثe��m�Хܬ�Visited 
		
		if ( dead_end(x,y) ) { // �p�G�J�즺���A�h����(�o�����|��)���j�A�ñN���~�����|�y�бq�������|�}�C���̥�������  
			
		    if (!path.empty())
				path.pop_back();
				
			return ;	
			
		}		
		
		
		if (dir == right) { // �ثe��V�O�k�A�p�G�k��i�H���N�O�d��V�V�k�æV�k���j 
			if (get(x+1,y) == 'E' or get(x+1,y) == 'G')
				walk_maze(x+1,y,dir);
		}
		
		else if  (dir == down) { // �ثe��V�O�U�A�p�G�U���i�H���N�O�d��V�V�U�æV�U���j  
			if (get(x,y+1) == 'E' or get(x,y+1) == 'G')
				walk_maze(x,y+1,dir);			
		}
		
		else if  (dir == left) { // �ثe��V�O���A�p�G����i�H���N�O�d��V�V���æV�����j 
			if (get(x-1,y) == 'E' or get(x-1,y) == 'G')
				walk_maze(x-1,y,dir);			
		}
		
		else if  (dir == up) { // �ثe��V�O�W�A�p�G�W���i�H���N�O�d��V�V�W�æV�W���j  
			if (get(x,y-1) == 'E' or get(x,y-1) == 'G')
				walk_maze(x,y-1,dir);			
		}

		walk_maze(x,y,(dir + 1)%4); // �N��V���ɰw����i�滼�j 
		
		
		if ( dead_end(x,y) ) {  // �p�G�J�즺���A�h����(�o�����|��)���j�A�ñN���~�����|�y�бq�������|�}�C���̥�������  
			  
		    if (!path.empty())
				path.pop_back();

			return ;	
			
		}
		
		return ;
		
	} // walk_maze()
	
	// ��l�Ƹ�� 
	void init() { 
		
		visited_matrix.clear();
    	real_matrix.clear();
    	all_V_matrix.clear(); 
    	path.clear();
    	
    	goal_found = 0;
    	goal_needed = 1; // �һݥؼмƪ�l�Ƭ�1�A�p�G�u�ݤ@�ӥؼдN���ݭn�A��� 
		
    	max_x = -1; 
    	max_y = -1;
		min_path_size = -1;
    	
	} // init()
	
	// �^�ǸӮy�ЬO�_������
	bool dead_end(int x, int y) {  
		
		return (get(x,y+1) != 'E' and get(x+1,y) != 'E' and 
		    	get(x,y-1) != 'E' and get(x-1,y) != 'E' and
				get(x,y+1) != 'G' and get(x+1,y) != 'G' and 
		    	get(x,y-1) != 'G' and get(x-1,y) != 'G' );
	
	} // dead_end()
	
	// �^�ǸӮy�Цb�w���X���|�x�}������ئr�šA�Y�W�X�x�}�d��h�^��'O'��ܤ���樫 
	char get(int x, int y) { 
		
		if ( 0 <= x and x < max_x and 0 <= y and y < max_y)
			return visited_matrix[x][y];
		else
			return 'O';
			
	} // get()
	
	// �q�ɮ׽s��Ū�J�ɮסA�^�ǬO�_���\Ū�J 
	bool read_file(string filenum) { 
	
		string filename = "input" + filenum + ".txt";
		ifstream file( filename.c_str() ); 
		
		if (!file.is_open()) { // �p�G�ɮ׵L�k�}�ҡA��X���~�T����^�� 0 
            cout << "\n" << filename  <<" does not exist!"<< "\n";
            return 0;
        }
        
        if (!(file >> max_x >> max_y)) { // �p�GŪ�J��ƮɥX���D�A��X���~�T����������^�� 0 
            cout << "\nAn error occurred while inputing from file: " << filename << "\n";
            file.close();
            return 0;
        }
        
		// �ھڦ�C���s�t�m�x�}�j�p 
		// ��b��x(�k����)�A�a�b��y(�U����) 
		visited_matrix.resize(max_x);
		for (int i = 0 ; i < max_x ; i++ ) 
			visited_matrix[i].resize(max_y);
		
		// Ū�J�g�c���e
		for (int j = 0; j < max_y; j++) {
			 
			for (int i = 0; i < max_x; i++) {  
	
				// �p�GŪ�J��ƮɥX���D�A��X���~�T����������^�� 0 
                if (!(file >> visited_matrix[i][j]) or ( visited_matrix[i][j] != 'E' and visited_matrix[i][j] != 'O' and visited_matrix[i][j] != 'G') ) {
                    cout << "\nAn error occurred while inputing from file: " << filename << "\n";
                    file.close();
                    return 0;
                }
                
            }
            
        }
        
        
        // �ˬd���W���O�_���Ů�A�p�G���O�A��X���~�T����������^�� 0 
        if (visited_matrix[0][0] != 'E') {
        	
            cout << "\nAn error occurred while inputing from file: " << filename << "\n";
            file.close();
            return 0;	

		}
		
		
		// �ˬd�ɮ׸̭��O�_����L�F��d�U(�ɮ׬O�_���ŦX��J�榡)�A�p�G���A��X���~�T����������^�� 0 
        string trash = "";
        while (!file.eof()){
        	
        	file >> trash;
        	if ( trash != "" ) {
        		cout << "\nAn error occurred while inputing from file: " << filename << "\n";
                file.close();
				return 0;
			}
			
		} 

		real_matrix = visited_matrix; // �ƻs�@���x�}�@����ڸ��|�x�} 
		all_V_matrix = visited_matrix;
		file.close(); // ������� 
		return 1;
	} // read_file()
	
	// �ھکҵ����|�b��ڸ��|�x�}�W�e�W��ڸ��| 
	void draw_real_matrix(vector<Coordinate> path) { 
		
		for (int i = 0;i<path.size();i++)
			if (real_matrix[path[i].x][path[i].y] != 'G')
				real_matrix[path[i].x][path[i].y] = 'R'; 
		
	} // draw_real_matrix()
	
	void draw_real_matrix_by_shortest_path() {
		
		draw_real_matrix(shortest_path);
		
	} // draw_real_matrix_by_shortest_path() 
	
	// �ץ��w���X���|�x�}��Goal(�]���bwalk maze�ɷ|�Q�ܦ�Visited) 
	void correct_visited_matrix() {
		
		// �N��ڸ��|�x�}��G�ƻs���x�s�w���X���|�x�} 
		for (int j = 0; j < max_y; j++) {
            for (int i = 0; i < max_x; i++) {
                    if (real_matrix[i][j] == 'G')
                    	visited_matrix[i][j] = 'G';
            }
        }
		
	} // correct_visited_matrix()

	// ��X�w���X���|�x�} 
	void print_visited_matrix() {
		
		for (int j = 0; j < max_y; j++) {
            for (int i = 0; i < max_x; i++) {
                cout << visited_matrix[i][j] ;
            }
            cout << "\n";
        }

	} // print_visited_matrix()
	
	// ��X�w���X���|�x�} 
	void print_all_V_matrix() {
		
		for (int j = 0; j < max_y; j++) {
            for (int i = 0; i < max_x; i++) {
                cout << all_V_matrix[i][j] ;
            }
            cout << "\n";
        }

	} // print_all_V_matrix()
	
	
	// ��X��ڸ��|�x�} 
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
	
	// ��ʩһݥؼм� 
	void set_goal_needed(int goal_needed_input){ 
		
		goal_needed = goal_needed_input;
		
	} // set_goal_needed()
	
	// �^�ǩһݥؼмƬO�_��� 
	bool found_all_goal_needed(){
		
		return goal_found == goal_needed;
	
	} // found_all_goal_needed()
	
	int get_min_path_size(){
		
		return min_path_size;
		
	} // get_min_path_size()
	
private:

	vector< vector<char> > visited_matrix; // �x�s�w���X���|���x�} 
	vector< vector<char> > real_matrix;    // �x�s�u����|���x�} 
	vector< vector<char> > all_V_matrix;   // �x�s�Ҧ��w���L��V���x�}  (���ȤT�~�Ψ�) 
	
	
	vector<Coordinate> path; // �x�s�ثe�������|���}�C 
	vector<Coordinate> shortest_path; // �x�s��쪺�̵u���|���}�C (���ȤT�~�Ψ�) 
	int min_path_size; // �x�s�̵u���|������ (���ȤT�~�Ψ�)  
	
	
	int goal_needed; // �x�s�һݥؼм� 
	int goal_found;  // �x�s�ثe��쪺�ؼм� 
	
	// �x�s�x�}���j�p 
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
		
		command = Input::input_command(); // will get 0, 1, 2, 3, or -1(�L�ī��O)
		
		if ( command == 1 || command == 2 || command == 3 ) {  // 1 or 2 or 3 means walk maze
			
			cout <<"\nPlease input file number: ";
			cin >> filenum;
			
			maze_obj.init(); // ��l�� 
			
			if (maze_obj.read_file(filenum)) { // Ū�J���A�p�G���\�~�i�樫�g�c 
			
				if ( command == 1 || command == 2 ) { // �Ҧ� 1 or 2, ���`�樫 
			
					if (command == 2) // �p�G�ݭn�h��Goal�A�i���J 
						maze_obj.set_goal_needed ( Input::input_goal_needed() ) ; // goal_needed will set to 1~100 
						
					maze_obj.walk_maze(); // ���j�禡�D�� 
					maze_obj.correct_visited_matrix(); // �ץ��w���X���|�x�}��Goal 
					
					cout << "\n";  
					maze_obj.print_visited_matrix(); // ��X�w���X���|�x�} 
					
					if ( maze_obj.found_all_goal_needed() ) { // �p�G����һݥؼСA��X��ڸ��|�x�} 
						cout << "\n"; 
						maze_obj.print_real_matrix();
					}
					
				}
				
				else if (command == 3) { // ��̵u���| 
				
					maze_obj.walk_maze_min_path(); // ���j��̵u���|�禡�D��  
	
					cout << "\n"; 
					maze_obj.print_all_V_matrix(); // ��X�]�t�Ҧ��w���L��V���x�} 
					
					if ( maze_obj.get_min_path_size() != -1 ){ // �p�G�̵u���|��������l��-1(�ܤ֧��@�����|) 
						
						cout << "\n"; 
						maze_obj.draw_real_matrix_by_shortest_path();  // �b��ڸ��|�x�}ø�s�̵u���| 
						maze_obj.print_real_matrix();  // ��X��ڸ��|�x�} 
						cout <<"\nShortest path length = "<< maze_obj.get_min_path_size() + 1<< "\n"; // ��X�̵u���|����					
						
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





