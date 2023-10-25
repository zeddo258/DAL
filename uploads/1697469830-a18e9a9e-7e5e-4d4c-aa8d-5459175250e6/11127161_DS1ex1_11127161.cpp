// 11127161 �B��ʳ 

# include <stdlib.h>
# include <iostream>
# include <fstream>
# include <string.h>
# include <vector>

using namespace std;

enum Modes{ // ���X�ӥؼ� 
	oneG, moreG
};

class Maze{
	private:
		vector<string> lines; // �ŧi
		string line; // �Ȯ��x�s��Ӧr�� 
	public:
		int row; // y�y�� �� 
		int column; // x�y�� �C  
		int a1, b1, goalnumber;
		int goalsite1,goalsite2;

	
		
	bool load( string filename , Modes mode){
		
    	string Filename = "input" + filename + ".txt" ; // �ܦ�input101.txt 
    	
    	char Filename2[100];
    	strcpy(Filename2, Filename.c_str());
		ifstream file(Filename2); // �u�Ychar���A���r�� 
		if (!file.is_open()) // �P�_�ɮ׬O�_�}�� 
			return false;
		else {
			string a;
			string b;
			file >> a >> b; // Ū�J�� �C 
			int n1,n2;
			row = atoi(a.c_str());
			column = atoi(b.c_str());
			getline(file, line) ;
    		while (getline(file, line)) {
        		lines.push_back(line); // �C�@��K�[�� vector ��
    		} // while
    		
    		file.close(); // ������� 
			return true;
		} // else
	
	} // load
	
	// ��ơG�b�a�ϤW�M��ؼ�
	bool findGoals(int & goalnumber, Maze & vMaze) {
	    int a1 = 0, b1 = 0;
		int direction = 1; // ���w�]�b(0,0) �B���k 
	    return finddir(a1, b1, goalnumber, direction, vMaze);
	} // findGoals
	
	bool finddir(int a1, int b1, int goalnumber, int direction, Maze &vMaze) {
		//  �k:1 �U:2  ��:3  �W:4  
		if( vMaze.lines[a1][b1] == 'G' ) { // �p�G�O�ؼ� 
			return true;
		} // if

		if ( direction == 1 ) { // �p�G�O���k
			if ( vMaze.lines[a1][b1+1] == 'O' || b1+1 == row || vMaze.lines[a1][b1+1] == 'V') { // �k��O��ê���Ϊ̬O��� 
				direction = 2; // ��V�ܦ��V�U
				return finddir( a1, b1, goalnumber, direction, vMaze);
			} // if ���k��� 
			else if ( vMaze.lines[a1][b1+1] == 'E' || vMaze.lines[a1][b1+1] == 'G' ) { //�U���O�Ů�Υؼ� {
				vMaze.lines[a1][b1] = 'V'; // ���L�����ܦ�V 
				lines[a1][b1] = 'R';
				b1++;
				return finddir(a1, b1, goalnumber, direction, vMaze);
			} // else if	
		} // if 
		else if ( direction == 2 ) { // �p�G�O���U 
			if ( vMaze.lines[a1+1][b1] == 'O' || a1 + 1 == column || vMaze.lines[a1+1][b1] == 'V') { // �U���O��ê���Ϊ̬O��� 
				direction = 3; // ��V�ܦ��V�� 
				return finddir( a1, b1, goalnumber, direction, vMaze);
			} // if
			else if ( vMaze.lines[a1+1][b1] == 'E' || vMaze.lines[a1+1][b1] == 'G' ) { //�U���O�Ů�Υؼ� 
				vMaze.lines[a1][b1] = 'V'; // ���L�����ܦ�V
				lines[a1][b1] = 'R';
				a1++; // �~�򩹤U���� 
				return finddir(a1, b1, goalnumber, direction, vMaze);
			} // else if	
		} // else if 
		else if ( direction == 3 ) { // �p�G�O���� 
			if ( vMaze.lines[a1][b1-1] == 'O' || b1 - 1 < 0 || vMaze.lines[a1][b1-1] == 'V' ) { // �����O��ê���Ϊ̬O��� 
				direction = 4; // ��V�ܦ��V�W 
				return finddir( a1, b1, goalnumber, direction, vMaze );
			} // if
			else if ( vMaze.lines[a1][b1-1] == 'E' || vMaze.lines[a1][b1-1] == 'G' ) { //����O�Ů�Υؼ�
				vMaze.lines[a1][b1] = 'V'; // ���L�����ܦ�V 
				lines[a1][b1] = 'R';
				b1--; // �~�򩹥���� 
				return finddir(a1, b1, goalnumber, direction, vMaze);
			} // else if	
		} // else if 
		else if ( direction == 4 ) { // �p�G�O���W 
			if ( vMaze.lines[a1-1][b1] == 'O' || a1 - 1 < 0 || vMaze.lines[a1-1][b1] == 'V') { // �W���O��ê���Ϊ̬O��� 
				direction = 1; // ��V�ܦ��V�k 
				return finddir(a1, b1, goalnumber, direction, vMaze);
			} // if
			else if ( vMaze.lines[a1-1][b1] == 'E' || vMaze.lines[a1-1][b1] == 'G' ) { //�U���O�Ů�Υؼ� 
				vMaze.lines[a1][b1] = 'V'; // ���L�����ܦ�V
				lines[a1][b1] = 'R';
				a1--; // �~�򩹤W���� 
				return finddir(a1, b1, goalnumber, direction, vMaze);
			} // else if	
		} // else if 
		
		return false;
	} // finddir


	void show(){
			
		for( int i = 0 ; i < lines.size() ; i++ ) {
			cout << lines[i] << "\n" ;
		} // for
		
		cout << endl;
		
	} // show
	
	void cir(){
		for ( int i = 0; i < row ; i++ ){
			for ( int j = 0 ; j < column ; j++ ){
				lines[i][j] = '\0';
			} // for
		} // for 
	} // cir
};


int main(void) {
	int command = 0, number = 0;
	
	do {
		Maze aMaze;
		string filename;
		Modes mode = oneG;
		bool success;
		
		cout << endl << "***Path Finding ***";
		cout << endl << "*0. Quit          *";
		cout << endl << "*1. One goal      *";
		cout << endl << "*2. More goals      *";
		cout << endl << "********************";
		cout << endl << "Input a command(0, 1, 2): ";
		cin >> command; // ���o���O 

		
		if ((command == 1) || (command == 2)) {
			cout << endl << "Input a file number (e.g., 101, 102,...):";
			cin >> filename;
			if (command == 2) {
				mode = moreG; // �@�өΦh�ӥؼ� 
				cout << endl << "Number of G (goals):";
				cin >> number;
			} // if 
			
						
			if (aMaze.load(filename, mode)){ // ���J��l�x�} 

				
				Maze vMaze(aMaze); // �ŧiaMaze vMaze 
				if ( command == 2 ) { // ���u�@�ӥؼ� 
					int goalnumber = number;
					success = aMaze.findGoals(goalnumber, vMaze); //�ݬO�_�����q���ؼЪ����|  
				} // if
				
				else {
					int goalnumber = 1; 
				    success = aMaze.findGoals(goalnumber, vMaze); //�ݬO�_�����q���ؼЪ����|  vMaze
				} // else

			
				mode = oneG; // ���]���w�] 
				vMaze.show(); // ��ܤw�g���L���a��
			  
				if (success) // �p�G�����\�����| 
					aMaze.show(); // ��ܨ�F�ؼЪ����|
				vMaze.cir(); // �M�� 

			} // if
			
		
		// lines.clear();
		aMaze.cir();;
		// aMaze = '\0';
		}
	
	else if(!command)
		break;
	else
		cout << endl << "Command does not exist!" << endl;
	} while(true);
	system("pause");
	return 0;
} // end of main


