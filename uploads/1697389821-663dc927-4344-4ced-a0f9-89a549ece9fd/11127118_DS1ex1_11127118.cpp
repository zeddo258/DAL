// 11127118 ������ 
#include <iostream>
#include <cstdlib> // for atoi 
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <vector>
#include "DS1Maze.hpp"

using namespace std;

/*enum Modes {
	moreG,
	oneG,
}; // Modes*/


		
Maze::Maze() { // �򥻫غc�� 
	
} // Maze()

Maze::Maze(const Maze& other) { // �ƻs��LMaze���󪺫غc��       
    m_maze = other.m_maze; // �ƻs vector<string> m_maze �����e

    m_x = other.m_x; // �ƻs int m_x �M int m_y ����
    m_y = other.m_y;
    
    m_mode = other.m_mode; // �ƻs m_mode 
    
    m_num = other.m_num; // �ƻsm_num
} // Maze

bool Maze::load(string filename, Modes mode) { // ���J�a���� 
	ifstream myFile;
	myFile.open(filename.c_str()); // �]�W��filename���ɮ�
	if (!myFile.is_open()) { // �p�G�ɮ׵L�k�}�ҴN�L�X���~�T���åB�^��false 
    	cerr << "Error opening file " << filename << endl;
    	return false;
	} // if

	char size[5];
	myFile >> size;
	m_x = atoi(size); // ���ox��(�e)�A�N�r��(��)�ഫ����� 

	myFile >> size;
	m_y = atoi(size); // ���oy��(��)�A�N�r��(��)�ഫ�����  

	m_maze.clear(); // �M�Ť��e�����
	for (int i = 0; i < m_y; i++) { // �Q��for�j��N��Ƥ@��@��a�s�ivector�� 
    	string row;
    	myFile >> row;
    	m_maze.push_back(row);
	} // for
	
	m_mode = mode; // �i�Dm_mode�OoneG��moreG 

	return true; // ���eŪ��Ʀ��\�A�]���^��true
} // load()

bool Maze::visit( int y, int x, Maze& v_maze ) { // �Q�λ��j���覡�qx,y�y�дM��Goal�A�ñN�����s��v_maze 
	if ( y >= m_y || y < 0 || x >= m_x || x < 0 ) { // �]�w��ɡA�Y�W�L�N�^��false 
		return false; 
	} // if
	
	if ( m_maze[y][x] == 'G' ) { // �Y���G�N�N����ȧ����A�^��true 
		v_maze.m_num--; // ���@��G�A�N�ؼмƶq��@ 
		return true;
	} // if
	
	if ( m_maze[y][x] == 'O' ) { // ���O�N��J���ê���A�^��false 
		return false ;
	} // if
	
	if ( v_maze.m_maze[y][x] == 'E' ) { // ���E�N��O�i�����| 
		if ( m_mode == moreG ) { // �h�ӥؼ� 
			v_maze.m_maze[y][x] = 'V'; // �N�ثe��m�Ÿ��令V��ܤw���L 
			bool ret_value1 = visit( y, x+1, v_maze ); // ���k���å�ret_value1�ܼƱ����G 
		
			bool ret_value2 = v_maze.m_num>0 && visit( y+1, x, v_maze ); // ���U���å�ret_value2�ܼƱ����G
			
			bool ret_value3 = v_maze.m_num>0 && visit( y, x-1, v_maze ); // �������å�ret_value3�ܼƱ����G	
			
			bool ret_value4 = v_maze.m_num>0 && visit( y-1, x, v_maze ); // ���W���å�ret_value4�ܼƱ����G
		
			if ( ret_value1 || ret_value2 || ret_value3 || ret_value4 ) { // �u�n���䤤�@�өΤ@�ӥH�W���ȬOtrue�N�N���\�A�^��true 
				return true;
			} // if
			
			v_maze.m_maze[y][x] = 'F'; // �аO���w���X�A��ܧ䤣��Goal 
		} // if
		
		else { // �@�ӥؼ�
			v_maze.m_maze[y][x] = 'V'; // �N�ثe��m�Ÿ��令V��ܤw���L 
			bool ret_value = visit( y, x+1, v_maze ); // ���k���å�ret_value�ܼƱ����G  
			if ( ret_value ) { // �p�Gret_value�Otrue�A��ܧ��Goal 
				return ret_value;
			} // if
			
			ret_value = visit( y+1, x, v_maze ); // ���U���å�ret_value�ܼƱ����G 
			if ( ret_value ) { // �p�Gret_value�Otrue�A��ܧ��Goal 
				return ret_value;
			} // if
			
			ret_value = visit( y, x-1, v_maze ); // �������å�ret_value�ܼƱ����G 
			if ( ret_value ) { // �p�Gret_value�Otrue�A��ܧ��Goal  
				return ret_value;
			} // if
			
			ret_value = visit( y-1, x, v_maze ); // ���W���å�ret_value�ܼƱ����G 
			if ( ret_value ) { // �p�Gret_value�Otrue�A��ܧ��Goal 
				return ret_value;
			} // if
			
			v_maze.m_maze[y][x] = 'F'; // �аO���w���X�A��ܧ䤣��Goal  
		} // else
		
		return false; // ��L���~���p�A�^��false 
	} // if
	
	return false; // ��L���~���p�A�^��false
} // visit()

bool Maze::findGoals(Maze& v_maze) {
	bool ret_value = false; // ���w�]ret_value�Ofalse 
	if ( visit( 0, 0, v_maze ) ) { // �Q�λ��j���覡�q(0,0)�M��Goal 
		for ( int i = 0 ; i < m_y ; i++ ) { // �Q�����h�j��NR���NV��ܦ��\�i����| 
			for ( int j = 0 ; j < m_x ; j++ ) {
				if ( v_maze.m_maze[i][j] == 'V' ) {
					m_maze[i][j] = 'R';
				} // if
			} // for
		} // for
		
		ret_value = true; // ��ܧ��Goal�Aret_value�ܦ�true 
	} // if
	
	for ( int i = 0 ; i < m_y ; i++ ) { // �Q�����h�j��NV���NF��ܧ䤣��Goal���`�I�аO���w���X 
		for ( int j = 0 ; j < m_x ; j++ ) {
			if ( v_maze.m_maze[i][j] == 'F' ) {
				v_maze.m_maze[i][j] = 'V';
			} // if
		} // for
	} // for
	
	return ret_value;
} // findGoals()

void Maze::show() {
    for ( int i = 0 ; i < m_maze.size() ; i++ ) { // �L�Xm_maz
    	cout << m_maze[i] << endl; 
	} // for
	
	cout<<endl;
} // show()

void Maze::clr() { // �M��m_maze��� 
    m_maze.clear();
    m_x = m_y = 0;
} // clr()

int main (void) {
	int command = 0;
	do {
		Maze aMaze;
		string fileName;
		Modes mode = oneG;
		int num;
		
		cout<<endl<<"*** Path Finding ***";
		cout<<endl<<"* 0. Quit          *";
		cout<<endl<<"* 1. One goal      *";
		cout<<endl<<"* 2. more goals    *";
		cout<<endl<<"********************";
		cout<<endl<<"Input a command(0,1,2): ";
		cin>>command;
		if ((command == 1) || (command == 2)) {
			if (command == 2) {
				mode = moreG;
				cout<<"��JN=";
				cin>>num;
			} // if
			
			cout<<endl<<"Input a file number(e.g.,201,202,...):";
			cin>>fileName;
			fileName = "input" + fileName + ".txt";
			if (aMaze.load(fileName,mode)) {
				Maze vMaze(aMaze);
				vMaze.m_num = num;
				bool success = aMaze.findGoals(vMaze);
				mode = oneG;
				vMaze.show();
				
				if ( success ) {
					aMaze.show();
				} // if
				
				vMaze.clr();
			} // if
		} // if
		
		else if ( !command ) {
			break;
		} // else if
		
		else {
			cout<<endl<<"Command does not exist!"<<endl;
		} // else
	}while (true) ;
		system ("pause");
	return 0;
} // main()
