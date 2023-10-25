// 11127106 ���l�� 
#include<iostream>
#include <fstream>
#include<vector>
#include<string>
using namespace std;

class Maze {
		int row;
		int column;	
		char s[100][100];
		char v_road[100][100];
		char r_road[100][100];
		int Gx[100];
		int Gy[100];
	public:
		int gtimes = 0; // �����ڧ��X��G�F
		bool load( string fileName );
		int Get_row() const;
		int Get_column() const;
		void set_v( int i, int j);
		void set_row_col( int r, int w);
		bool setManyWay( int i, int j, int direction, int G, int G_detect, int success );
		bool donthaveDirection( int i, int j ); // �p�G�P��S���i�H�� �Nreturn true�C
		void printv( int i, int j);	
		void printr( int i, int j);
};

bool Maze::donthaveDirection( int i, int j){ 
	int time = 0;
	bool test = false;
	bool test1 = false;
	bool test2 = false;
	bool test3 = false; 
	while ( time < gtimes ){ // ��M�P��O�_���w�g��L��G  �p�G���A�N�N���Ӥ�V�]�O����
    		if ( ( Gx[time] == i-1 && Gy[time] == j ) ){
    			test = true; 
			}
			if ( Gx[time] == i && Gy[time] == j-1 ) {
				test1 = true;
			}
			if( Gx[time] == i+1 && Gy[time] == j ) {
				test2 = true;
			}
			if ( Gx[time] == i && Gy[time] == j+1 )  {
				test3 = true;
			}
    			
    		time++;		
	}
	if ( j-1 < 0 ){ //�u�nreturn true �N��P�򳣬O����
			if ( ( v_road[i][j+1] == 'V' || v_road[i][j+1] == 'O' || test3 == true ) ){
				if ( ( v_road[i-1][j]=='V' || v_road[i-1][j] == 'O' || test == true ) ) {
					if ( i+1 == column ){
						return true;
					}
					else {
						if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test2 == true ) ){
							return true;
						}
						return false;
					}
					
				}
				return false;
			}
			
			return false;
	}
	else { //�u�nreturn true �N��P�򳣬O����
		if ( ( v_road[i][j-1]=='V' || v_road[i][j-1] == 'O' || test1 == true ) ) {
			if  ( j+1 == row) {
				if ( i-1 < 0){
					if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test2 == true) ){
						return true;
					}
					return false;
				}
				else {
					if ( ( v_road[i-1][j]=='V' || v_road[i-1][j] == 'O' || test == true) ) {
						if ( i+1 == column){
							return true;	
						}
						else {
							if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test2 == true) ){
								return true;
							}
							return false;
						}
						
					
					
					}
					return false;
				}
				
								
			} 
			else{
				if( ( v_road[i][j+1] == 'V' || v_road[i][j+1] == 'O' || test3 == true)){	
					if ( i-1 < 0) {
						if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test2 == true) )
							return true;
						return false;
					}
					else {
						if ( ( v_road[i-1][j]=='V' || v_road[i-1][j] == 'O' || test == true ) ) {
							if ( i+1 == column ){
								return true;
							}
							else {
								if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test2 == true) ){
									return true	;
								}
								return false;
							}
						
						}
						return false;
						
				 
					}
				}
				return false;
			}
			
		}
		return false;
				
	}	
}
	
void Maze::printv( int i, int j) {
	cout<< v_road[i][j]; // �I�s�æL�X��e��v���|
}

void Maze::printr( int i, int j) {
	cout<< r_road[i][j]; // �I�s�æL�X��e��R���|
}
void Maze::set_row_col( int r, int w) { 
	row = r;
	column = w;
	
}

void Maze::set_v( int i, int j) { // �g�L�����|�n�令V 
	v_road[i][j] = 'V';
}
int Maze::Get_row() const{ // ���o�g�c����
	return row;
}

int Maze::Get_column() const{ // ���o�g�c���e
	return column;
}
bool  Maze::setManyWay(int i, int j ,int direction, int G, int G_detect, int success) { // �o��function�O�n��X�ڭ̭n��M���Ҧ�G
	int row = Maze::Get_row() ;
	int column = Maze::Get_column() ;
	int time = 0;  
	bool test = false; 
	bool test1 = false;
	bool test2 = false;
	bool test3 = false;
    if ( v_road[i][j] == 'G' ){ 
    	Gx[gtimes] = i;  // �����o��G����m �H�K���ۦP��G 
    	Gy[gtimes] = j; // �����o��G����m �H�K���ۦP��G 
    	gtimes = gtimes + 1; // r�O����L�X��G�F 
    	if ( Maze::donthaveDirection( i, j ) ){  // �p�G�P��S����L���i�H�� �Nreturn true 
    		return true;							
		}
    		
    	else { // �p�G�٦����A�N�̧ǥ����k�B���U�B�����B���W�h�� �A ���ӥh����V�éI�s���j 
    		if ( j+1 != row ){
				if ( (v_road[i][j+1] == 'E' && v_road[i][j+1] != 'G' && v_road[i][j+1] != 'V'  ) ) success = Maze::setManyWay(i,j+1, 1, G, G_detect, success);	
			}	
			if ( i+1 != column) {
				if ( (v_road[i+1][j] == 'E' && v_road[i+1][j] != 'G' && v_road[i+1][j] != 'V') ) success = Maze::setManyWay(i+1,j, 2, G, G_detect, success);
			}
		
			if ( j-1 != -1) {
				if ( (v_road[i][j-1] == 'E' && v_road[i][j-1] != 'G' && v_road[i][j-1] != 'V') ) success = Maze::setManyWay(i,j-1, 3, G, G_detect, success);
			}
		
			if ( i-1 != -1 ){
				if ( (v_road[i-1][j] == 'E' && v_road[i-1][j] != 'G' && v_road[i-1][j] != 'V') )success = Maze::setManyWay(i-1,j, 4, G, G_detect, success);	
			}
			
			return true;
    		
		}
	}
	else if ( gtimes == G ){  
		return true;
	}
    else{ // direction �� 1�B2�B3�B4 ���O�N�� �V�k �V�U �V�� �V�W 
    	v_road[i][j] = 'V';
    	r_road[i][j] = 'R';
    	while ( time < gtimes ){ // �o��while�O�h�H���|�@�����ۦPG
    		if ( Gx[time] == i && Gy[time] == j+1 )
    			test = true;
    		time++;		
		}
		if ( (j+1 != row ) &&  direction == 1) {
			if ( (v_road[i][j+1] != 'O' &&  v_road[i][j+1] != 'V' &&  direction == 1  && ( test == false && !Maze::donthaveDirection( i, j) ) ) )  {
    			direction = 1;
    			success = Maze::setManyWay(i, j+1, direction, G , G_detect, success);
    			if ( (success == true &&  Maze::donthaveDirection( i, j )) || gtimes == G ){
    				return true;
				}
    				
			}  		
		}
		if ( j+1 != row){
			if ( (v_road[i][j+1] == 'O' ||  v_road[i][j+1] == 'V' || v_road[i][j+1] == 'G' ) &&  (direction == 1 ) ){// �q�쥻���k �ܦ����U�h�P�_�O�_���� (direction=2)
				direction = 2;	
			}
		}
		else {
			if( direction == 1 )	
				direction = 2;
		}
		
		time = 0;
		while ( time < gtimes ){ // �o��while�O�h�H���|�@�����ۦPG 
    		if ( Gx[time] == i+1 && Gy[time] == j )
    			test1 = true;
    		time++;		
		}
		if ( (i+1 != column) && direction == 2){
			if ( v_road[i+1][j] != 'O' &&  v_road[i+1][j] != 'V' && direction == 2 && ( test1 == false && !Maze::donthaveDirection( i, j) ) ){
				direction = 2;
			
				success = Maze::setManyWay(i+1, j , direction, G, G_detect, success);
				if ( ( success == true && Maze::donthaveDirection( i, j) ) || gtimes == G )
					return true;
			}
		}
		if ( i+1 != column ){
			if ( (v_road[i+1][j] == 'O' || v_road[i+1][j] == 'V' || v_road[i+1][j] == 'G') && (direction == 2) ) // �q�쥻���U �ܦ������h�P�_�O�_���� (direction=3) 
			direction = 3;		
		}
		else{
			if( direction == 2 )
				direction = 3;
		}
		
		time = 0;
		while ( time < gtimes ){ // �o��while�O�h�H���|�@�����ۦPG 
    		if ( (Gx[time] == i )&& Gy[time] == (j-1) )
    			test2 = true;
    		time++;		
		}
		if( (j-1 != -1) && direction == 3){
			if ( v_road[i][j-1] != 'O' &&  v_road[i][j-1] != 'V' && direction == 3 && ( test2 == false && !Maze::donthaveDirection( i, j) )) {
				direction = 3;
				success = Maze::setManyWay(i,j-1, direction, G, G_detect, success);
				if ( ( success == true && Maze::donthaveDirection( i, j) ) || gtimes == G ){
					return true;
				}
					
			}
		}
		
		if( j-1 != -1 ) {  
			if ( (v_road[i][j-1]=='V' || v_road[i][j-1] == 'O' || v_road[i][j-1] == 'G' ) && (direction == 3) ) // �q�쥻���� �ܦ����W�h�P�_�O�_���� (direction=4) 
				direction = 4;
		}
		else {
			if ( direction == 3 )
				direction = 4;
		}
		
		time = 0;	
		while ( time < gtimes ){  // �o��while�O�h�H���|�@�����ۦPG 
    		if ( Gx[time] == i-1 && Gy[time] == j )
    			test3 = true;
    		time++;		
		}
		
		if( (i-1 != -1) && direction == 4 ) { 
			if ( v_road[i-1][j] != 'O' && v_road[i-1][j] != 'V'  && direction == 4 && ( test3 == false && !Maze::donthaveDirection( i, j) ) ){
				direction = 4;
				success = Maze::setManyWay(i-1,j, direction, G, G_detect, success);
				if ( ( success == true  && Maze::donthaveDirection( i, j)) || gtimes == G )
					return true;
			}
		}
		// �H�U���|��if �O�n�P�_�٦��S�����i�� 
		if ( j+1 != row ){  // �P�_�٦��S�����i��
			if ( (v_road[i][j+1] != 'O' && v_road[i][j+1] != 'V' && ( test == false && !Maze::donthaveDirection( i, j)  ) )) {
				success = Maze::setManyWay(i,j+1, 1, G, G_detect, success);
				if ( ( success == true  && Maze::donthaveDirection( i, j)) || gtimes == G )
					return true;
			}
					
		}	
		if ( i+1 != column) { // �P�_�٦��S�����i��
			if ( v_road[i+1][j] != 'O' && v_road[i+1][j] != 'V' && ( test1 == false && !Maze::donthaveDirection( i, j) ) )  {
				success = Maze::setManyWay(i+1,j, 2, G, G_detect, success);
				if ( ( success == true  && Maze::donthaveDirection( i, j)) || gtimes == G )
					return true;
			}
				
		}
		
		if ( j-1 != -1) {  // �P�_�٦��S�����i��
			if ( v_road[i][j-1] != 'O' && v_road[i][j-1] != 'V' && ( test2 == false && !Maze::donthaveDirection( i, j) ) ) {
				success = Maze::setManyWay(i,j-1, 3, G, G_detect, success);
				if ( ( success == true  && Maze::donthaveDirection( i, j)) || gtimes == G )
					return true;
			}
				
		}
		
		if ( i-1 != -1 ){ // �P�_�٦��S�����i��
			if ( v_road[i-1][j] != 'O' && v_road[i-1][j] != 'V' && ( test3 == false && !Maze::donthaveDirection( i, j) ) ){
				success = Maze::setManyWay(i-1,j, 4, G, G_detect, success);	
				if ( ( success == true  && Maze::donthaveDirection( i, j)) || gtimes == G )
					return true;
			}
				
		}
		if ( gtimes == G ){
			return true;
		}
		
			
		time = 0;	
		while ( time < gtimes ){  // ��M�P��O�_���w�g��L��G  �p�G���A�N�N���Ӥ�V�]�O����
    		if ( ( Gx[time] == i && Gy[time] == j+1 ) ){
    			test = true;
			}
			if ( Gx[time] == i+1 && Gy[time] == j ) {
				test1 = true;
			}
			if( Gx[time] == i && Gy[time] == j-1 ) {
				test2 = true;
			}
			if ( Gx[time] == i-1 && Gy[time] == j )  {
				test3 = true;
			}
    			
    		time++;		
		}
		
		if ( j-1 < 0 ){ //�P�򳣬O���� �ҥH�{��return false �ҥH�]�n�� R���|�o�Ӧ�m�� R �令 E 
			if ( ( v_road[i][j+1] == 'V' || v_road[i][j+1] == 'O' || test == true ) ){
				if ( ( v_road[i-1][j]=='V' || v_road[i-1][j] == 'O' || test3 == true ) ) {
					if ( i+1 == column ){
						r_road[i][j] = 'E'; // �� R���|�o�Ӧ�m�� R �令 E 
						return false;  
					}
					else {
						if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test3 == true ) ){
							r_road[i][j] = 'E';
							return false; 
						}
						
					}
					
				}
			}
		}
		else {
			if ( ( v_road[i][j-1]=='V' || v_road[i][j-1] == 'O' || test2 == true ) ) {
				if  ( j+1 == row) {
					if ( i-1 < 0 ){
						if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test1 == true) ){
							r_road[i][j] = 'E';
							return false; 
						}
					}
					else{
						if ( ( v_road[i-1][j]=='V' || v_road[i-1][j] == 'O' || test3 == true) ) {
							if ( i+1 == column ){
								r_road[i][j] = 'E';
								return false; 
							} 
							else {
								if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test1 == true) ){
									r_road[i][j] = 'E';
									return false;  
								}
								
							}
							
						} 	
					}
					
				}
				else{
					if( ( v_road[i][j+1] == 'V' || v_road[i][j+1] == 'O' || test == true)){
					
						if ( i-1 < 0 ){
							if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test1 == true) ){
								r_road[i][j] = 'E';
								return false; 
							} 		
						}
						else{
							if ( ( v_road[i-1][j]=='V' || v_road[i-1][j] == 'O' || test3 == true ) ) {
								if ( i+1 == column ){
									r_road[i][j] = 'E';
									return false;
								}
								else{
									if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test1 == true) ){
										r_road[i][j] = 'E';
										return false;   
									}
										
								}
							}
						}
					}
				}
			}
				
		}
		
	}
    
}
bool Maze::load( string fileName ) {
	int row = 0,column = 0;
	string file = "input" + fileName + ".txt";  
	ifstream ifs( file.c_str() );//���}�ɮ�
	int i = 0;
	int j = 0;
    if ( ifs ){  
    	 ifs >> row; 
   		 ifs >> column; 
   		 Maze::set_row_col( row, column);  // ��ұo�쪺row column �s�_�� 
		for ( i = 0; i <  column ; i++) {  //�N�g�c�s�J�}�C��
			for ( j = 0 ; j < row ; j++) {
				ifs >> Maze::s[i][j];
				Maze::v_road[i][j] = Maze::s[i][j];
				Maze::r_road[i][j] = Maze::v_road[i][j];
			}
		} 
    	ifs.close(); // �����ɮ� 
        return true; 
    }
    cout <<"\n"; 
    cout << file << " does not exist!" << endl;

	return false;	
}


int main() {
	int command = 0;
	int moreGoals = 0;
	int G_detect = 0;  
	do {
		Maze aMaze;
		string fileName;
    	
		cout << endl << "*** Path Finding ***";
		cout << endl << "* 0. Quit          *";
		cout << endl << "* 1. One goal      *";
		cout << endl << "* 2. More goals    *";
		cout << endl << "********************";
		cout << endl << "Input a command(0, 1, 2): ";
		cin >> command;
		if ( ( command == 1 ) || ( command == 2) ) {
			cout << endl << "Input a file number: ";
			cin >> fileName;
			if ( command == 1 ) {
			
				if ( aMaze.load(fileName)) { 
					if (aMaze.setManyWay( 0, 0 , 1, 1,1,0) ) {  //�䪺��G  �N�̧ǦL�X V���| �M R���|  
						for ( int i = 0; i <  aMaze.Get_column() ; i++) { 
							for ( int j = 0 ; j <  aMaze.Get_row() ; j++) {
								aMaze.printv( i, j );
							}
			
							cout << "\n";
						} 
					
						cout << "\n";
						for ( int i = 0; i <  aMaze.Get_column() ; i++) { 
							for ( int j = 0 ; j <  aMaze.Get_row() ; j++) {
								aMaze.printr( i, j );
							}	
			
							cout << "\n";
						} 	
						cout << "\n";
						
					}
					else { // �䤣��G �u�L�X V���|
					
						for ( int i = 0; i <  aMaze.Get_column() ; i++) { 
							for ( int j = 0 ; j <  aMaze.Get_row() ; j++) {
								aMaze.printv( i, j );
							}	
			
							cout << "\n";
						} 
					}			
				}
			}
			
			else if ( command == 2 ) {
				if ( aMaze.load(fileName)) {
					cout << endl << "Number of G (goals): ";
					cin >> moreGoals ; //��J�ڭn�䪺G�Ӽ� 
					G_detect = moreGoals;
					if ( aMaze.setManyWay( 0, 0 , 1, moreGoals, G_detect, 0) ) {  //�p�G���X�ŦX�ڭn�䪺G�ӼƴN�̧ǦL�X V���| �M R���|
						for ( int i = 0; i <  aMaze.Get_column() ; i++) { 
							for ( int j = 0 ; j <  aMaze.Get_row() ; j++) {
								aMaze.printv( i, j );
							}
			
							cout << "\n";
						} 
					
						cout << "\n";
						for ( int i = 0; i <  aMaze.Get_column() ; i++) { 
							for ( int j = 0 ; j <  aMaze.Get_row() ; j++) {
								aMaze.printr( i, j );
							}	
			
							cout << "\n";
						} 
						cout << "\n";	
						
					}
					else {  //�p�G�����X�ŦX�ڭn�䪺G�Ӽ� �u�L�XV���| 
						for ( int i = 0; i <  aMaze.Get_column() ; i++) { 
							for ( int j = 0 ; j <  aMaze.Get_row() ; j++) {
								aMaze.printv( i, j );
							}	
							cout << "\n";
							
						} 
						cout << "\n";
					}		
				}
			}
		}
		else if ( !command )
			break;
		else
			cout << endl << "Command does not exist!" << endl;
					
		
	} while(true);
	system( "pause" );
	return 0;

}
