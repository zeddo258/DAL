// 11127103 ��ˢ�o 

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum Direction {
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,
	UP = 4,
	RETURN = -1
};

class Maze {
	
	
	public:
		Maze(); // constructor
		void Read( string str ); // Ū�J�ɮ� 
		bool Goal( int curx, int cury, int dir ); // �P�_�ثe��G�I�O�_�O�w�g���L�� 
		int Determine_Direction( int curx, int cury, int dir ); // �P�_�ѹ��n�樫����V
		int Return( int curx, int cury, int dir, int ret); // �p�G�ѹ��ݭn�^�{�A�P�_�^�{���i������L��V  
		void Storage_FinalR(); // ø�s�̲׸��u�� 
		int Implement( int curx, int cury, int dir, int N ); // ��@�ѹ��g�c���D 
		void Print( int N ); // ��X���G 
		
	
	private:
		int x, y; // x : x�b�ƶq�Ay : y�b�ƶq 
		vector<char> vec[50]; // �sV���|���G���}�C 
		vector<char> rec[50]; // �sR���ĸ��|���G���}�C 
		vector<char> finalr[50]; // �sR�̲צ��ĸ��|���G���}�C
		vector<int> gx; // �s�w����LG�I��x��m 
		vector<int> gy; // �s�w����LG�I��y��m
		
		
		bool find = false; // �J��G��A�ΨӧP�O���ɪ�G�O�_�w���L
		int count = 0, ret; // count : �p�⨫���X��G�Aret : ����Implment���return�^�Ӫ��ƭȡA�ð��P�_ 
			
};

Maze::Maze(){
	this->gx.reserve(10); // �Ngx��l10��Ŷ�
	this->gy.reserve(10); // �Ngy��l10��Ŷ�
} // Maze() 

void Maze::Read( string str ) {
	ifstream in;
    in.open( str.c_str() ); // open file
    
	char r; // Ū�J�ɮפ��e���Ȧs�ܼ� 
	int i = 0, index = 0;
    
    in >> x >> y; // get the row and line
	
    while ( in >> r ) {
        i++;
        		
        vec[index].push_back(r); // ��Ū�J���r����ivec�G���}�C���A���C���̫�@�� 
        		
        if ( i == x ) { // �Yi����C�ƶq�A�h���� 
        	index++;
        	i = 0;
		} // if()
    } // while()

	vec[0].at(0) = 'V'; // ��l��_�I�令���L 
	in.close(); // close file 
	
	in.open( str.c_str() ); // open file
	i = 0, index = 0;
    
    in >> x >> y; // get the row and line 
	
    while ( in >> r ) {
        i++;
        		
        rec[index].push_back(r); // ��Ū�J���r����irec�G���}�C���A���C���̫�@�� 
        		
        if ( i == x ) { // �Yi����C�ƶq�A�h���� 
        	index++;
        	i = 0;
		} // if()
    } // while()
    
    rec[0].at(0) = 'R'; // ��l��_�I�令���L
	in.close(); // close file 
	
	in.open( str.c_str() ); // open file
	i = 0, index = 0;
    
    in >> x >> y; // get the row and line 
	
    while ( in >> r ) {
        i++;
        		
        finalr[index].push_back(r); // ��Ū�J���r����ifinalr�G���}�C���A���C���̫�@�� 
        		
        if ( i == x ) { // �Yi����C�ƶq�A�h���� 
        	index++;
        	i = 0;
		} // if()
    } // while()
    
    finalr[0].at(0) = 'R'; // ��l��_�I�令���L
	in.close(); // close file 
	
} // Read()


bool Maze::Goal( int curx, int cury, int dir ) {
	
	if ( dir == 1 ) { // �P�_���ɦ�m�V�k�@���I�O�_�O�w���L��G�I 
		for ( int i = 0 ; i < gx.size() ; i++ ) { 
			if ( curx+1 == gx[i] && cury == gy[i] ) return true; // �Y�O�w����L��G�I�A�hreturn true 
		} // for()
	} // if()
	
	if ( dir == 2 ) { // �P�_���ɦ�m�V�U�@���I�O�_�O�w���L��G�I  
		for ( int i = 0 ; i < gx.size() ; i++ ) { 
			if ( curx == gx[i] && cury+1 == gy[i] ) return true; // �Y�O�w����L��G�I�A�hreturn true 
		} // for()
	} // if()
	
	if ( dir == 3 ) { // �P�_���ɦ�m�V���@���I�O�_�O�w���L��G�I  
		for ( int i = 0 ; i < gx.size() ; i++ ) {
			if ( curx-1 == gx[i] && cury == gy[i] ) return true; // �Y�O�w����L��G�I�A�hreturn true 
		} // for()
	} // if()
	
	if ( dir == 4 ) { // �P�_���ɦ�m�V�W�@���I�O�_�O�w���L��G�I  
		for ( int i = 0 ; i < gx.size() ; i++ ) {
			if ( curx == gx[i] && cury-1 == gy[i] ) return true; // �Y�O�w����L��G�I�A�hreturn true 
		} // for()
	} // if()
	
	return false; // �Y�O�S����L��G�I�A�hreturn false
} // Goal()

int Maze::Determine_Direction( int curx, int cury, int dir ) {
	
	if ( dir == 1 ) { // �P�_�O�_�ӫ���V�k���A�άO�ӫ��Ӷ������P�_�i����V�άO��^�W���I 
		if ( ( curx+1 < x ) && (vec[cury].at(curx+1) != 'V') && (vec[cury].at(curx+1) !='O') && !Goal(curx,cury,1) ) return 1;        // ����V�k�� 
		else if ( ( cury+1 < y ) && (vec[cury+1].at(curx) != 'V') && (vec[cury+1].at(curx) != 'O') && !Goal(curx,cury,2) ) return 2;  // �ন�V�U�� 
		else if ( ( curx-1 >= 0 ) && (vec[cury].at(curx-1) != 'V') && (vec[cury].at(curx-1) != 'O') && !Goal(curx,cury,3) ) return 3; // �ন�V���� 
		else if ( ( cury-1 >= 0 ) && (vec[cury-1].at(curx) != 'V') && (vec[cury-1].at(curx) != 'O') && !Goal(curx,cury,4) ) return 4; // �ন�V�W�� 
		else return -1;                                                                                                               // ���^�{�� 
	} // if()
			
	if ( dir == 2 ) { // �P�_�O�_�ӫ���V�U���A�άO�ӫ��Ӷ������P�_�i����V�άO��^�W���I 
		if ( ( cury+1 < y ) && (vec[cury+1].at(curx) != 'V') && (vec[cury+1].at(curx) != 'O') && !Goal(curx,cury,2) ) return 2;       // ����V�U�� 
		else if ( ( curx-1 >= 0 ) && (vec[cury].at(curx-1) != 'V') && (vec[cury].at(curx-1) != 'O') && !Goal(curx,cury,3) ) return 3; // �ন�V���� 
		else if ( ( cury-1 >= 0 ) && (vec[cury-1].at(curx) != 'V') && (vec[cury-1].at(curx) != 'O') && !Goal(curx,cury,4) ) return 4; // �ন�V�W�� 
		else if ( ( curx+1 < x ) && (vec[cury].at(curx+1) != 'V') && (vec[cury].at(curx+1) !='O') && !Goal(curx,cury,1) ) return 1;   // �ন�V�k��
		else return -1;                                                                                                               // ���^�{��
	} // if()
			
	if ( dir == 3 ) { // �P�_�O�_�ӫ���V�����A�άO�ӫ��Ӷ������P�_�i����V�άO��^�W���I 
		if ( ( curx-1 >= 0 ) && (vec[cury].at(curx-1) != 'V') && (vec[cury].at(curx-1) != 'O') && !Goal(curx,cury,3) ) return 3;      // ����V���� 
		else if ( ( cury-1 >= 0 ) && (vec[cury-1].at(curx) != 'V') && (vec[cury-1].at(curx) != 'O') && !Goal(curx,cury,4) ) return 4; // �ন�V�W��
		else if ( ( curx+1 < x ) && (vec[cury].at(curx+1) != 'V') && (vec[cury].at(curx+1) !='O') && !Goal(curx,cury,1) ) return 1;   // �ন�V�k�� 
		else if ( ( cury+1 < y ) && (vec[cury+1].at(curx) != 'V') && (vec[cury+1].at(curx) != 'O') && !Goal(curx,cury,2) ) return 2;  // �ন�V�U�� 
		else return -1;                                                                                                               // ���^�{�� 
	} // if()
			
	if ( dir == 4 ) { // �P�_�O�_�ӫ���V�W���A�άO�ӫ��Ӷ������P�_�i����V�άO��^�W���I 
		if ( ( cury-1 >= 0 ) && (vec[cury-1].at(curx) != 'V') && (vec[cury-1].at(curx) != 'O') && !Goal(curx,cury,4) ) return 4;      // ����V�W�� 
		else if ( ( curx+1 < x ) && (vec[cury].at(curx+1) != 'V') && (vec[cury].at(curx+1) !='O') && !Goal(curx,cury,1) ) return 1;   // �ন�V�k�� 
		else if ( ( cury+1 < y ) && (vec[cury+1].at(curx) != 'V') && (vec[cury+1].at(curx) != 'O') && !Goal(curx,cury,2) ) return 2;  // �ন�V�U�� 
		else if ( ( curx-1 >= 0 ) && (vec[cury].at(curx-1) != 'V') && (vec[cury].at(curx-1) != 'O') && !Goal(curx,cury,3) ) return 3; // �ন�V���� 
		else return -1;                                                                                                               // ���^�{�� 
	} // if()
			
} // Determine_Direction()

int Maze::Return( int curx, int cury, int dir, int ret ) {
	
	if ( dir == 1 ) { // �b�^�{�ɧP�_�O�_����L���u�i���A�Y�L�h������V���^�� 
		if ( cury+1 < y && vec[cury+1].at(curx) != 'V' && vec[cury+1].at(curx) != 'O' && !Goal(curx, cury, 2) ) return 2;       // �V�U�訫 
		else if ( cury-1 >= 0 && vec[cury-1].at(curx) != 'V' && vec[cury-1].at(curx) != 'O' && !Goal(curx, cury, 4) ) return 4; // �V�W�訫
		else return -1;                                                                                                         // ���^�{�� 
	} // if()
	
	if ( dir == 2 ) { // �b�^�{�ɧP�_�O�_����L���u�i���A�Y�L�h������V�W�^�� 
		if ( curx-1 >= 0 && vec[cury].at(curx-1) != 'V' && vec[cury].at(curx-1) != 'O' && !Goal(curx, cury, 3) ) return 3;      // �V���訫 
		else if ( curx+1 < x && vec[cury].at(curx+1) != 'V' && vec[cury].at(curx+1) != 'O' && !Goal(curx, cury, 1) ) return 1;  // �V�k�訫 
		else return -1;                                                                                                         // ���^�{��
	} // if()
	
	if ( dir == 3 ) { // �b�^�{�ɧP�_�O�_����L���u�i���A�Y�L�h������V�k�^�� 
		if ( cury-1 >= 0 && vec[cury-1].at(curx) != 'V' && vec[cury-1].at(curx) != 'O' && !Goal(curx, cury, 4) ) return 4;      // �V�W�訫 
		else if ( cury+1 < y && vec[cury+1].at(curx) != 'V' && vec[cury+1].at(curx) != 'O' && !Goal(curx, cury, 2) ) return 2;  // �V�U�訫 
		else return -1;                                                                                                         // ���^�{�� 
	} // if()
	
	if ( dir == 4 ) { // �b�^�{�ɧP�_�O�_����L���u�i���A�Y�L�h������V�U�^�� 
		if ( curx+1 < x && vec[cury].at(curx+1) != 'V' && vec[cury].at(curx+1) != 'O' && !Goal(curx, cury, 1) ) return 1;       // �V�k�訫 
		else if ( curx-1 >= 0 && vec[cury].at(curx-1) != 'V' && vec[cury].at(curx-1) != 'O' && !Goal(curx, cury, 3) ) return 3; // �V���訫 
		else return -1;                                                                                                         // ���^�{�� 
	} // if()
	
} // Return()


void Maze::Storage_FinalR() {
	// �x�s�̲צ��ĸ��| 
	for ( int i = 0 ; i < y ; i++ ) {
		for ( int j = 0 ; j < x ; j++ ) {
			if ( rec[i].at(j) == 'R' && finalr[i].at(j) == 'E' ) finalr[i].at(j) = rec[i].at(j);
		} // for()
	} // for()
} // Storage_FinalR()


int Maze::Implement( int curx, int cury, int dir, int N ) {
	
	if ( count < N ) {
		dir = Determine_Direction( curx, cury, dir ); // �P�_�O�_�n�ഫ���u�Ψ��^�{�� 
			
		if ( dir == 1 && count < N ) { // ���k���� 
			curx++;
			if ( vec[cury].at(curx) == 'G' ) { // �Y���ɬOG�I�A�h�P�_�O�_�O�w����L��G�I 
				for ( int i = 0 ; i < gx.size() && !find ; i++ ) {
					if ( curx == gx[i] && cury == gy[i] ) find = true;
				} // for()
				
				if ( !find && vec[cury].at(curx) == 'G' ) { // �Y�O�S����L��G�I�A�h�x�s�ç��쪺G�I�ƶq�[�@ 
					count++;
					gx.push_back(curx); // �x�sG�Ix��m 
					gy.push_back(cury); // �x�sG�Iy��m
					
					Storage_FinalR(); // �x�s�̲צ��ĸ��| 
				} // if()
				
				find = false;
			} // if()
				
			if ( count < N ) {
				if ( vec[cury].at(curx) != 'G' ) {
					vec[cury].at(curx) = 'V'; // �N���L����m�令V 
					rec[cury].at(curx) = 'R'; // �N���L����m�令R 
				} // if()
				ret = Implement( curx, cury, dir, N ); // ���j�I�s 
			} // if()
		} // if()
			
		if ( dir == 2 && count < N )  { // ���U���� 
			cury++;
			if ( vec[cury].at(curx) == 'G' ) { // �Y���ɬOG�I�A�h�P�_�O�_�O�w����L��G�I  
				for ( int i = 0 ; i < gx.size() && !find ; i++ ) {
					if ( curx == gx[i] && cury == gy[i] ) find = true;
				} // for()
				
				if ( !find && vec[cury].at(curx) == 'G' ) { // �Y�O�S����L��G�I�A�h�x�s�ç��쪺G�I�ƶq�[�@  
					count++;
					gx.push_back(curx); // �x�sG�Ix��m 
					gy.push_back(cury); // �x�sG�Iy��m
					
					Storage_FinalR(); // �x�s�̲צ��ĸ��| 
				} // if()
				
				find = false;
			} // if()
				
			if ( count < N ) {
				if ( vec[cury].at(curx) != 'G' ) {
					vec[cury].at(curx) = 'V'; // �N���L����m�令V 
					rec[cury].at(curx) = 'R'; // �N���L����m�令R 
				} // if()
				ret = Implement( curx, cury, dir, N ); // ���j�I�s 
			} // if()
		} // if()
			
				
		if ( dir == 3 && count < N )  { // �������� 
			curx--;
			if ( vec[cury].at(curx) == 'G' ) { // �Y���ɬOG�I�A�h�P�_�O�_�O�w����L��G�I  
				for ( int i = 0 ; i < gx.size() && !find ; i++ ) {
					if ( curx == gx[i] && cury == gy[i] ) find = true;
				} // for()
				
				if ( !find && vec[cury].at(curx) == 'G' ) { // �Y�O�S����L��G�I�A�h�x�s�ç��쪺G�I�ƶq�[�@  
					count++;
					gx.push_back(curx); // �x�sG�Ix��m 
					gy.push_back(cury); // �x�sG�Iy��m
					
					Storage_FinalR(); // �x�s�̲צ��ĸ��| 
				} // if()
				
				find = false;
			} // if()
				
			if ( count < N ) {
				if ( vec[cury].at(curx) != 'G' ) {
					vec[cury].at(curx) = 'V'; // �N���L����m�令V 
					rec[cury].at(curx) = 'R'; // �N���L����m�令R 
				} // if()
				ret = Implement( curx, cury, dir, N ); // ���j�I�s 
			} // if()
		} // if()
			
			
		if ( dir == 4 && count < N )  { // ���W���� 
			cury--;
			if ( vec[cury].at(curx) == 'G' ) { // �Y���ɬOG�I�A�h�P�_�O�_�O�w����L��G�I
				for ( int i = 0 ; i < gx.size() && !find ; i++ ) {
					if ( curx == gx[i] && cury == gy[i] ) find = true;
				} // for()
				
				if ( !find && vec[cury].at(curx) == 'G' ) { // �Y�O�S����L��G�I�A�h�x�s�ç��쪺G�I�ƶq�[�@  
					count++;
					gx.push_back(curx); // �x�sG�Ix��m 
					gy.push_back(cury); // �x�sG�Iy��m 
					
					Storage_FinalR(); // �x�s�̲צ��ĸ��| 
				} // if()
				
				find = false;
			} // if()
				
			if ( count < N ) {
				if ( vec[cury].at(curx) != 'G' ) {
					vec[cury].at(curx) = 'V'; // �N���L����m�令V 
					rec[cury].at(curx) = 'R'; // �N���L����m�令R 
				} // if()
				ret = Implement( curx, cury, dir, N ); // ���j�I�s 
			} // if()
		} // if()
		

		if ( dir == -1 ) return -1; // �Y�J�즺���A�h�^�� 
		if ( ret == -1 && count < N ) {
		 	int z = Return( curx, cury, dir, ret ); // �P�_�^�{�~���O�_���i������L��V 
		 	if ( z == -1 ) {
		 		if ( rec[cury].at(curx) != 'G' )  rec[cury].at(curx) = 'E'; // �Y�^�ǥB���I���OG�I�A�h��R��^E 
		 		return -1; // �Yz�O-1�h�^�{�æ^��-1 
			} // if()
			
		 	ret = Implement( curx, cury, z, N ); // ���j�I�s 
		 	
		 	z = Return( curx, cury, dir, ret ); // �P�_�^�{�~���O�_���i������L��V
		 	if ( z == -1 && count < N ) {
		 		if ( rec[cury].at(curx) != 'G' )  rec[cury].at(curx) = 'E'; // �Y�^�ǥB���I���OG�I�A�h��R��^E 
		 		return -1; // �Yz�O-1�h�^�{�æ^��-1 
			} // if()
			
			ret = Implement( curx, cury, z, N ); // ���j�I�s 
			
		 	z = Return( curx, cury, dir, ret ); // �P�_�^�{�~���O�_���i������L��V
		 	if ( z == -1 && count < N ) {
		 		if ( rec[cury].at(curx) != 'G' )  rec[cury].at(curx) = 'E'; // �Y�^�ǥB���I���OG�I�A�h��R��^E 
		 		return -1; // �Yz�O-1�h�^�{�æ^��-1 
			} // if()
		} // if()
				
	} // if ()
} // Implement()


void Maze::Print( int N ) {
	// ��X���|���G���}�C 
	for ( int i = 0 ; i < y ; i++ ) {
		for ( int j = 0 ; j < x ; j++ ) {
			cout << vec[i].at(j);
		} // for()
				
		cout << endl;	
	} // for()
	
	cout << endl;
	
	// �p�G�����ݭn��쪺'G'�ƶq�A�h��X�̲צ��ĸ��|���G���}�C
	if ( count == N ) {
		for ( int i = 0 ; i < y ; i++ ) {
			for ( int j = 0 ; j < x ; j++ ) {
				cout << finalr[i].at(j);
			} // for()
				
			cout << endl;	
		} // for()
		
		cout << endl;
	} // if()
	
	
} // Print()



int main() {
	int command = 0; // user command 
	int goals = 1; // Ū�J�n���X��G 
	string fileName; // a file name
	
	
	do {
	Maze aMaze; // a matrix
	int curx = 0, cury = 0, dir = RIGHT; // curx : ����b�}�C����x��m�A cury : ����b�}�C����y��m�Adir : ��V
	
	cout << endl << "*** Path Finding ***";
	cout << endl << "* 0. Quit          *";
	cout << endl << "* 1. One goal      *";
	cout << endl << "* 2. More goals    *";
	cout << endl << "********************";
	cout << endl << "Input a command(0, 1, 2): ";
	cin >> command; // get the command
	
	if ( command == 0 ) break; // '0' : stop the program 
	else if ( command == 1 || command == 2 ) {
		cout << endl << "Input a file number: ";
		cin >> fileName; // get the file 
		fileName = "input" + fileName + ".txt";
		
		ifstream in;
		in.open( fileName.c_str() ); // open file 
		if ( !in.fail() ) {          // �P�_�ɮ׬O�_���}�� 
			
			in.close(); // close file 
			
			if ( command == 2 ) {
				cout << endl << "Number of G (goals): ";
				cin >> goals; // number of targets to find
			
				while ( goals < 1 || goals > 100 ) {
					cout << endl << "### The number must be in [1,100] ###" << endl << "\nNumber of G (goals): ";
					cin >> goals; // number of targets to find 
				} // while()
			} // if()
		

			aMaze.Read(fileName); // Ū�J���
			if ( command == 1 ) {
				aMaze.Implement( curx, cury, dir, command ); // implement 
				aMaze.Print( command ); // ��X���G
			} // if()
			else if ( command == 2 && goals > 0 && goals < 101 ) {
				aMaze.Implement( curx, cury, dir, goals ); // implement 
				aMaze.Print( goals ); // ��X���G
			} // else if()
		} // if()
		else cout << endl << fileName << " does not exist!" << endl; // file does not exist 
		
		
	} // else if()
	else cout << endl << "Command does not exist!" << endl; // command does not exist 
	
	} while( true );
	
	system("pause");
	return 0;
	
} // main()
