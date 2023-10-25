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
		int Return( int curx, int cury, int dir, int ret ); // �p�G�ѹ��ݭn�^�{�A�P�_�^�{���i������L��V  
		void Storage_FinalR(); // ø�s�̲׸��u�� 
		int Implement( int curx, int cury, int dir, int N ); // ��@�ѹ��g�c���D
		void Print( int N ); // ��X���G
		
		int Determine_Direction2( int curx, int cury, int dir, int curlength ); // �P�_�ѹ��n�樫����V
		int Return2( int curx, int cury, int dir, int curlength ); // �p�G�ѹ��ݭn�^�{�A�P�_�^�{���i������L��V
		void Update_shortest(); // ��s�̲׸��u�� 
		int FindShortestPath( int curx, int cury, int dir, int curlength, int predir ); // ��@��M�̵u���| 
		void PrintShortest(); // ��X���G 
		int getCount(); // ���ocount���ƭ� 
		
	
	private:
		int x, y; // x : x�b�ƶq�Ay : y�b�ƶq 
		vector<char> vec[50]; // �sV���|���G���}�C 
		vector<char> rec[50]; // �sR���ĸ��|���G���}�C 
		vector<char> finalr[50]; // �sR�̲צ��ĸ��|���G���}�C
		vector<int> gx; // �s�w����LG�I��x��m 
		vector<int> gy; // �s�w����LG�I��y��m
		vector<int> current[50]; // �x�s�C�Ӧ�m�Z���_�I���Z�� 
		
		bool find = false; // �J��G��A�ΨӧP�O���ɪ�G�O�_�w���L
		int count = 0, ret; // count : �p�⨫���X��G�Aret : ����Implment���return�^�Ӫ��ƭȡA�ð��P�_ 
		int shortestpath = 10000; // �x�s�̵u���|�Z�� 
			
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
		finalr[index].push_back(r); // ��Ū�J���r����ifinalr�G���}�C���A���C���̫�@��
        		
        if ( i == x ) { // �Yi����C�ƶq�A�h���� 
        	index++;
        	i = 0;
		} // if()
    } // while()
    
    rec[0].at(0) = 'R'; // ��l��_�I�令���L
    finalr[0].at(0) = 'R'; // ��l��_�I�令���L
	in.close(); // close file 
	
	
	// ��l��C�@�ӥ��]��-1 
	for ( int i = 0 ; i < y ; i++ ) {
		for ( int j = 0 ; j < x ; j++ ) {
			current[i].push_back(-1);
		} // for()
	} // for()
	
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
		if ( curx+1 < x && vec[cury].at(curx+1) != 'V' && vec[cury].at(curx+1) !='O' && !Goal(curx,cury,1) ) return 1;        // ����V�k�� 
		else if ( cury+1 < y && vec[cury+1].at(curx) != 'V' && vec[cury+1].at(curx) != 'O' && !Goal(curx,cury,2) ) return 2;  // �ন�V�U�� 
		else if ( curx-1 >= 0 && vec[cury].at(curx-1) != 'V' && vec[cury].at(curx-1) != 'O' && !Goal(curx,cury,3) ) return 3; // �ন�V���� 
		else if ( cury-1 >= 0 && vec[cury-1].at(curx) != 'V' && vec[cury-1].at(curx) != 'O' && !Goal(curx,cury,4) ) return 4; // �ন�V�W�� 
		else return -1;                                                                                                       // ���^�{�� 
	} // if()
			
	if ( dir == 2 ) { // �P�_�O�_�ӫ���V�U���A�άO�ӫ��Ӷ������P�_�i����V�άO��^�W���I 
		if ( cury+1 < y && vec[cury+1].at(curx) != 'V' && vec[cury+1].at(curx) != 'O' && !Goal(curx,cury,2) ) return 2;       // ����V�U�� 
		else if ( curx-1 >= 0 && vec[cury].at(curx-1) != 'V' && vec[cury].at(curx-1) != 'O' && !Goal(curx,cury,3) ) return 3; // �ন�V���� 
		else if ( cury-1 >= 0 && vec[cury-1].at(curx) != 'V' && vec[cury-1].at(curx) != 'O' && !Goal(curx,cury,4) ) return 4; // �ন�V�W�� 
		else if ( curx+1 < x && vec[cury].at(curx+1) != 'V' && vec[cury].at(curx+1) !='O' && !Goal(curx,cury,1) ) return 1;   // �ন�V�k��
		else return -1;                                                                                                       // ���^�{��
	} // if()
			
	if ( dir == 3 ) { // �P�_�O�_�ӫ���V�����A�άO�ӫ��Ӷ������P�_�i����V�άO��^�W���I 
		if ( curx-1 >= 0 && vec[cury].at(curx-1) != 'V' && vec[cury].at(curx-1) != 'O' && !Goal(curx,cury,3) ) return 3;      // ����V���� 
		else if ( cury-1 >= 0 && vec[cury-1].at(curx) != 'V' && vec[cury-1].at(curx) != 'O' && !Goal(curx,cury,4) ) return 4; // �ন�V�W��
		else if ( curx+1 < x && vec[cury].at(curx+1) != 'V' && vec[cury].at(curx+1) !='O' && !Goal(curx,cury,1) ) return 1;   // �ন�V�k�� 
		else if ( cury+1 < y && vec[cury+1].at(curx) != 'V' && vec[cury+1].at(curx) != 'O' && !Goal(curx,cury,2) ) return 2;  // �ন�V�U�� 
		else return -1;                                                                                                       // ���^�{�� 
	} // if()
			
	if ( dir == 4 ) { // �P�_�O�_�ӫ���V�W���A�άO�ӫ��Ӷ������P�_�i����V�άO��^�W���I 
		if ( cury-1 >= 0 && vec[cury-1].at(curx) != 'V' && vec[cury-1].at(curx) != 'O' && !Goal(curx,cury,4) ) return 4;      // ����V�W�� 
		else if ( curx+1 < x && vec[cury].at(curx+1) != 'V' && vec[cury].at(curx+1) !='O' && !Goal(curx,cury,1) ) return 1;   // �ন�V�k�� 
		else if ( cury+1 < y && vec[cury+1].at(curx) != 'V' && vec[cury+1].at(curx) != 'O' && !Goal(curx,cury,2) ) return 2;  // �ন�V�U�� 
		else if ( curx-1 >= 0 && vec[cury].at(curx-1) != 'V' && vec[cury].at(curx-1) != 'O' && !Goal(curx,cury,3) ) return 3; // �ন�V���� 
		else return -1;                                                                                                       // ���^�{�� 
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


int Maze::Determine_Direction2( int curx, int cury, int dir, int curlength ) {
	
	if ( dir == 1 ) { // �P�_�O�_�ӫ���V�k���A�άO�ӫ��Ӷ������P�_�i����V�άO��^�W���I 
		if ( curx+1 < x && vec[cury].at(curx+1) == 'E' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'G' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx+1) ) return 1;  // ����V�k��

		if ( cury+1 < y && vec[cury+1].at(curx) == 'E' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'G' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury+1].at(curx) ) return 2;  // �ন�V�U�� 

		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'E' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'G' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx-1) ) return 3; // �ন�V���� 

		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'E' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'G' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury-1].at(curx) ) return 4; // �ন�V�W�� 
		
		return -1; // ���^�{�� 
	} // if()
			
	if ( dir == 2 ) { // �P�_�O�_�ӫ���V�U���A�άO�ӫ��Ӷ������P�_�i����V�άO��^�W���I 

		if ( cury+1 < y && vec[cury+1].at(curx) == 'E' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'G' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury+1].at(curx) ) return 2;  // ����V�U�� 
		
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'E' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'G' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx-1) ) return 3; // �ন�V���� 

		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'E' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'G' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury-1].at(curx) ) return 4; // �ন�V�W��
		
		if ( curx+1 < x && vec[cury].at(curx+1) == 'E' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'G' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx+1) ) return 1;  // �ন�V�k�� 

		return -1; // ���^�{��
	} // if()
			
	if ( dir == 3 ) { // �P�_�O�_�ӫ���V�����A�άO�ӫ��Ӷ������P�_�i����V�άO��^�W���I 
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'E' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'G' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx-1) ) return 3; // ����V���� 
		
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'E' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'G' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury-1].at(curx) ) return 4; // �ন�V�W��

		if ( curx+1 < x && vec[cury].at(curx+1) == 'E' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'G' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx+1) ) return 1;  // �ন�V�k��

		if ( cury+1 < y && vec[cury+1].at(curx) == 'E' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'G' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury+1].at(curx) ) return 2;  // �ন�V�U�� 
		
		return -1; // ���^�{�� 
	} // if()
			
	if ( dir == 4 ) { // �P�_�O�_�ӫ���V�W���A�άO�ӫ��Ӷ������P�_�i����V�άO��^�W���I 
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'E' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'G' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury-1].at(curx) ) return 4; // ����V�W��
		 
		if ( curx+1 < x && vec[cury].at(curx+1) == 'E' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'G' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx+1) ) return 1;  // �ন�V�k�� 

		if ( cury+1 < y && vec[cury+1].at(curx) == 'E' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'G' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury+1].at(curx) ) return 2;  // �ন�V�U�� 

		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'E' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'G' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx-1) ) return 3; // �ন�V���� 
		
		return -1; // ���^�{�� 
	} // if()
			
} // Determine_Direction2()

int Maze::Return2( int curx, int cury, int dir, int curlength ) {
	
	if ( dir == 1 ) { // �b�^�{�ɧP�_�O�_����L���u�i���A�Y�L�h������V���^�� 
		if ( cury+1 < y && vec[cury+1].at(curx) == 'E' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'G' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury+1].at(curx) ) return 2;  // �V�U�訫 

		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'E' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'G' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx-1) ) return 3; // �V���訫 

		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'E' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'G' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury-1].at(curx) ) return 4; // �V�W�訫
		
		return -1; // ���^�{�� 
	} // if()
	
	if ( dir == 2 ) { // �b�^�{�ɧP�_�O�_����L���u�i���A�Y�L�h������V�W�^�� 
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'E' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'G' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx-1) ) return 3; // �V���訫 
		
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'E' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'G' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury-1].at(curx) ) return 4; // �V�W�訫

		if ( curx+1 < x && vec[cury].at(curx+1) == 'E' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'G' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx+1) ) return 1;  // �V�k�訫 
		
		return -1; // ���^�{��
	} // if()
	
	if ( dir == 3 ) { // �b�^�{�ɧP�_�O�_����L���u�i���A�Y�L�h������V�k�^�� 
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'E' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'G' && curlength+1 < shortestpath ) return 4;
		if ( cury-1 >= 0 && vec[cury-1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury-1].at(curx) ) return 4; // �V�W�訫
		
		if ( curx+1 < x && vec[cury].at(curx+1) == 'E' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'G' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx+1) ) return 1;  // �V�k�訫 

		if ( cury+1 < y && vec[cury+1].at(curx) == 'E' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'G' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury+1].at(curx) ) return 2;  // �V�U�訫 
		
		return -1; // ���^�{�� 
	} // if()
	
	if ( dir == 4 ) { // �b�^�{�ɧP�_�O�_����L���u�i���A�Y�L�h������V�U�^�� 
		if ( curx+1 < x && vec[cury].at(curx+1) == 'E' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'G' && curlength+1 < shortestpath ) return 1;
		if ( curx+1 < x && vec[cury].at(curx+1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx+1) ) return 1;  // �V�k�訫
		
		if ( cury+1 < y && vec[cury+1].at(curx) == 'E' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'G' && curlength+1 < shortestpath ) return 2;
		if ( cury+1 < y && vec[cury+1].at(curx) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury+1].at(curx) ) return 2;  // �V�U�訫 

		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'E' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'G' && curlength+1 < shortestpath ) return 3;
		if ( curx-1 >= 0 && vec[cury].at(curx-1) == 'V' && curlength+1 < shortestpath && curlength+1 < current[cury].at(curx-1) ) return 3; // �V���訫 
		
		return -1; // ���^�{�� 
	} // if()
	
} // Return2()

void Maze::Update_shortest()  {
	// ��finalr�ܦ^��� 
	for ( int i = 0 ; i < y ; i++ ) {
		for ( int j = 0 ; j < x ; j++ ) {
			if ( finalr[i].at(j) == 'R' ) finalr[i].at(j) = 'E';
		} // for()
	} // for()
	
	// ��s�̵u���| 
	for ( int i = 0 ; i < y ; i++ ) {
		for ( int j = 0 ; j < x ; j++ ) {
			if ( finalr[i].at(j) == 'E' && rec[i].at(j) == 'R' ) finalr[i].at(j) = 'R';
		} // for()
	} // for()
	
} // Update_shortest()

int Maze::FindShortestPath( int curx, int cury, int dir, int curlength, int predir ) {
	
	current[cury].at(curx) = curlength; // �x�s�C�Ӧ�m�Z���_�I���Z�� 
	dir = Determine_Direction2( curx, cury, dir, curlength ); // �P�_�O�_�n�ഫ���u�Ψ��^�{��
	
	
	if ( dir == 1 ) { // ���k����
	
		if ( vec[cury].at(curx) != 'G' ) {
			vec[cury].at(curx) = 'V'; // �N���L����m�令V 
			rec[cury].at(curx) = 'R'; // �N���L����m�令R 
			
			ret = FindShortestPath( curx+1, cury, dir, curlength+1, dir ); // ���j�I�s 
		} // if()
		
		
		if ( vec[cury].at(curx) == 'G' && curlength < shortestpath ) { // �Y���G�A�B�Z����u 
			count++;
			shortestpath = curlength; // ��s�̵u���|�Z�� 
			
			Update_shortest(); // ��s�̵u���| 
			return -1; // �^�{ 
		} // if()
				

	} // if()
			
	if ( dir == 2 )  { // ���U����
		
		if ( vec[cury].at(curx) != 'G' ) {
			vec[cury].at(curx) = 'V'; // �N���L����m�令V 
			rec[cury].at(curx) = 'R'; // �N���L����m�令R 
			
			ret = FindShortestPath( curx, cury+1, dir, curlength+1, dir ); // ���j�I�s 
		} // if()

		
		if ( vec[cury].at(curx) == 'G' && curlength < shortestpath ) { // �Y���G�A�B�Z����u
			count++;
			shortestpath = curlength; // ��s�̵u���|�Z�� 
			
			Update_shortest(); // ��s�̵u���| 
			return -1; // �^�{ 
		} // if()
		
	} // if()
			
				
	if ( dir == 3 )  { // �������� 
		
		if ( vec[cury].at(curx) != 'G' ) {
			vec[cury].at(curx) = 'V'; // �N���L����m�令V 
			rec[cury].at(curx) = 'R'; // �N���L����m�令R 
			
			ret = FindShortestPath( curx-1, cury, dir, curlength+1, dir ); // ���j�I�s 
		} // if()

		
		if ( vec[cury].at(curx) == 'G' && curlength < shortestpath ) { // �Y���G�A�B�Z����u
			count++;
			shortestpath = curlength; // ��s�̵u���|�Z�� 
			
			Update_shortest(); // ��s�̵u���| 
			return -1; // �^�{ 
		} // if()
		
	} // if()
			
			
	if ( dir == 4 )  { // ���W���� 
		
		if ( vec[cury].at(curx) != 'G' ) {
			vec[cury].at(curx) = 'V'; // �N���L����m�令V 
			rec[cury].at(curx) = 'R'; // �N���L����m�令R 
			
			ret = FindShortestPath( curx, cury-1, dir, curlength+1, dir ); // ���j�I�s 
		} // if()
		
		
		if ( vec[cury].at(curx) == 'G' && curlength < shortestpath ) { // �Y���G�A�B�Z����u
			count++;
			shortestpath = curlength; // ��s�̵u���|�Z�� 
			
			Update_shortest(); // ��s�̵u���| 
			return -1; // �^�{ 
		} // if()
	} // if()
		

	if ( dir == -1 ) {
		
		if ( vec[cury].at(curx) != 'G' ) vec[cury].at(curx) = 'V'; // �N���L����m�令V 
		
		if ( vec[cury].at(curx) == 'G' && curlength < shortestpath ) { // �Y���G�A�B�Z����u
			count++;
			shortestpath = curlength; // ��s�̵u���|�Z�� 
			
			Update_shortest(); // ��s�̵u���| 
		} // if()
					
		return -1; // �Y�J�즺���A�h�^��
	} // if () 
	
 
	if ( ret == -1 ) {
		int z = Return2( curx, cury, predir, curlength ); // �P�_�^�{�~���O�_���i������L��V 
		if ( z != -1 && curlength+1 < shortestpath ) {
			if ( z == 1 ) ret = FindShortestPath( curx+1, cury, z, curlength+1, z );      // �Y�i�V�k�A���j�I�s 
			else if ( z == 2 ) ret = FindShortestPath( curx, cury+1, z, curlength+1, z ); // �Y�i�V�U�A���j�I�s
			else if ( z == 3 ) ret = FindShortestPath( curx-1, cury, z, curlength+1, z ); // �Y�i�V���A���j�I�s
			else if ( z == 4 ) ret = FindShortestPath( curx, cury-1, z, curlength+1, z ); // �Y�i�V�W�A���j�I�s
		} // if()
		else {
			if ( rec[cury].at(curx) != 'G' ) rec[cury].at(curx) = 'E'; // �Y�^�ǥB���I���OG�I�A�h��R��^E 
		 	return -1; // �Yz�O-1�h�^�{�æ^��-1 
		} // else
			
 	
		z = Return2( curx, cury, predir, curlength ); // �P�_�^�{�~���O�_���i������L��V
		if ( z != -1 && curlength+1 < shortestpath ) {
			if ( z == 1 ) ret = FindShortestPath( curx+1, cury, z, curlength+1, z );      // �Y�i�V�k�A���j�I�s 
			else if ( z == 2 ) ret = FindShortestPath( curx, cury+1, z, curlength+1, z ); // �Y�i�V�U�A���j�I�s
			else if ( z == 3 ) ret = FindShortestPath( curx-1, cury, z, curlength+1, z ); // �Y�i�V���A���j�I�s
			else if ( z == 4 ) ret = FindShortestPath( curx, cury-1, z, curlength+1, z ); // �Y�i�V�W�A���j�I�s
		} // if()
		else {
			if ( rec[cury].at(curx) != 'G' ) rec[cury].at(curx) = 'E'; // �Y�^�ǥB���I���OG�I�A�h��R��^E 
		 	return -1; // �Yz�O-1�h�^�{�æ^��-1 
		} // else
			
		z = Return2( curx, cury, predir, curlength ); // �P�_�^�{�~���O�_���i������L��V
		if ( rec[cury].at(curx) != 'G' ) rec[cury].at(curx) = 'E'; // �Y�^�ǥB���I���OG�I�A�h��R��^E 
		return -1; // �Yz�O-1�h�^�{�æ^��-1 
	} // if()	
	
} // FindShortestPath()


void Maze::Print( int N ) {
	// �L�X���|���G���}�C 
	for ( int i = 0 ; i < y ; i++ ) {
		for ( int j = 0 ; j < x ; j++ ) {
			cout << vec[i].at(j);
		} // for()
				
		cout << endl;	
	} // for()
	
	cout << endl;
	
	// �p�G�����ݭn��쪺'G'�ƶq�A�h�L�X�̲צ��ĸ��|���G���}�C
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

void Maze::PrintShortest() {
	// �L�X���|���G���}�C 
	for ( int i = 0 ; i < y ; i++ ) {
		for ( int j = 0 ; j < x ; j++ ) {
			cout << vec[i].at(j);
		} // for()
		
		cout << endl;	
	} // for()
	
	cout << endl;
	
	// �Y�����G�A�h�L�X�̵u���|�γ̵u�Z�� 
	if ( count != 0  ) {
		for ( int i = 0 ; i < y ; i++ ) {
			for ( int j = 0 ; j < x ; j++ ) {
				cout << finalr[i].at(j);
			} // for()
				
			cout << endl;	
		} // for()
		
		cout << endl << endl << "Shortest path length = " << shortestpath << endl;
	} // if()
	
} // PrintShortest()

int Maze::getCount() {
	return count;
} // getCount()


int main() {
	int command = 0; // user command 
	int goals = 1; // Ū�J�n���X��G 
	string fileName; // a file name
	
	
	do {
	Maze aMaze; // a matrix
	int curx = 0, cury = 0, dir = RIGHT; // curx : ����b�}�C����x��m�A cury : ����b�}�C����y��m�Adir : ��V
	int curlength = 1, predir = RIGHT; // curlength : �C�Ӧ�m�Z���_�I���Z���Apredir : ��V 
	
	cout << endl << "*** Path Finding ***";
	cout << endl << "* 0. Quit          *";
	cout << endl << "* 1. One goal      *";
	cout << endl << "* 2. More goals    *";
	cout << endl << "* 3. Shortest Path *";
	cout << endl << "********************";
	cout << endl << "Input a command(0, 1, 2, 3): ";
	cin >> command; // get the command
	
	if ( command == 0 ) break; // '0' : stop the program 
	else if ( command == 1 || command == 2 || command == 3 ) {
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
			else if ( command == 3 ) {
				aMaze.FindShortestPath( curx, cury, dir, curlength, predir ); // implement 
				aMaze.PrintShortest(); // ��X���G
				
				if ( aMaze.getCount() == 0 ) cout << endl << "### There is no path to find a goal! ###" << endl ;
			} // else if
		} // if()
		else cout << endl << fileName << " does not exist!" << endl; // file does not exist 
		
		
	} // else if()
	else cout << endl << "Command does not exist!" << endl; // command does not exist 
	
	} while( true );
	
	system("pause");
	return 0;
	
} // main()
