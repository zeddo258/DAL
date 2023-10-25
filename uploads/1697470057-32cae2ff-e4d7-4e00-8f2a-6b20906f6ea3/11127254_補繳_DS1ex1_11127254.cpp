// 11127254 �����R

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <vector>



using namespace std;
enum Modes{
	oneG, 
	moreG,
	shortestG
};
enum Face{
	Right ,
	Down ,
	Left ,
	Up 
};
struct Goal{ // �������I(G) x,y ����m  
	int x; 
	int y;
};

class Maze{
	char trash; // �Y�ť� 
	int x ,y ;
	int col ;  
	int row ;
	vector<vector<char> > matrix; // matrix �G���ʺA�}�C �ΨӦs�g�c 
    
	public :
		int shortest;
		
		bool load(string fileName){
			shortest = 9999999;
			string fileN = "input" + fileName + ".txt";
			ifstream inF( fileN.c_str() ); // inF�O�@�� �H��J�Ӷ}���ɮ� 
										   // �NfileN �ഫ��C���r�Ŧ�(�Hnull����) 
			
			if(inF.is_open()){ // �ɮ׳Q�}�� 
				
				inF >> x >> y ;  
				inF.get(trash); // �Y�Ů� 
				while( trash != '\n'){ // ����Y�촫�� 
					inF.get(trash);
				}
				
				col = x ; // �� �]�w�� x 
				row = y ; // �C �]�w�� y 
				
				
				vector<char> tempRow; // �Ψ��x�s�C�@��C���r��vector 
				string line;
    			while (getline(inF, line)) { 
    				for( int j = 0 ; j < col ; j++ ){
						tempRow.push_back(line[j]); // �C�@�C���r�� �s�btempRow �᭱	
					} // for 
					matrix.push_back(tempRow); //  �N�C�@��C�s�Jmatrix�� 
					tempRow.clear(); // ���� 
   			 	   
    			} // while (getline(inF, line))
    			
    			inF.close(); // �����ɮ� 
    			
    			return true;
			} // if ���\�}�� 
			
			// ���Q���\�}��
			cout << endl << fileN << " does not exist!" << endl;  
			return false ;
		
		
		} // bool load(string fileName)
		
		bool visit(Modes mode, Maze &aMaze) { // ���X�ؼв��I 
			int number ; // �Ψ��x�s���X�ؼЭӼ� 
			if ( mode == oneG ) number = 1;  
			else if ( mode == moreG ) { 
				cout << endl << "Number of G (goals):";
				cin >> number; // ��J�ؼЭӼ� 
				while( number < 1 || number > 100 ){ // �Y�W�X�ؼ� 
					cout << endl << "### The number must be in [1, 100] ###" << endl;
					cout << endl << "Number of G (goals):";
					cin >> number; // ��J�ؼЭӼ�
				} // while 
				
			} // else if
			else if ( mode == shortestG ) number = 0;
			
			int count = 0; // �x�s�����I�Ӽ� 
			// �˴��_�I 
			if (matrix[0][0]  == 'E' ) matrix[0][0] = 'V';  
			else if(matrix[0][0]  == 'G') count++;
			else return false;
			
			
			
			Face face = Right; // ���V��V ��l�Ȭ�Right 
			int xr = 0, yr = 0; // �_�I��m (xr, yr) (0, 0)  
		 	Maze cMaze(aMaze); // �N aMaze ����
		 	
			if ( number >= 1 ){
		 		
			 	Goal G; // �������I(G) x,y ����m  
				bool founded = false; // �O�_�����I
				 
				 
				walk( face, xr, yr, founded, aMaze, cMaze, count, G);
				
				if(founded) cMaze.matrix[G.y][G.x] = 'A'; // �Y���G �h�N'G' �令'A'
				
				while (count < number && founded ) { // �p�G�٥��F�һݥؼЭӼ� && �����s���ؼ� 
					walk( face, xr, yr, founded, aMaze, cMaze, count, G);
					
					if(founded) cMaze.matrix[G.y][G.x] = 'A'; // �Y���G �h�N'G' �令'A'
	
				} // while
				
				if (count == number) { // �Y�F���ؼЭӼ� 
					aMaze.matrix[0][0] = 'R'; // �NaMaze ���_�I�令'R' 
					cMaze.clr(); // ����
					return true;	
				} // if
				cMaze.clr(); // ���� 
				return false;
			} // if ( number >= 1 ) mode = oneG or moreG
			
			else if ( number == 0 ){ // mode = shortestG
				int node = 2; // �_�I�@�B + ����G�@�B = �ܤ�2�B  
				shortWalk( face, xr, yr, aMaze, cMaze, node); 
				cMaze.clr(); // ���� 
				return false;
			} // else if ( number == 0 ) mode = shortestG
		 	
			
		} // bool visit(Modes mode, Maze &aMaze)
		
		// ���L�����| 
		void walk( Face face, int x, int y, bool& founded, Maze &aMaze, Maze cMaze, int &count, Goal &G ){
			//cout << x << ", " << y << endl;
			
			for ( int i = 0; i < 4 ;) { // �˴��|�Ӥ�V �̧� �k �U �� �W 
				
				if ( i < 4 && face == Right ){ // �V�k  
					if ( x+1 < col && cMaze.matrix[y][x+1] == 'G' ){ // �Y���W�X��� �B���G 
						
						founded = true; // ���G 
						count = count + 1; // ���G���Ӽƥ[�@ 
						G.x = x+1; // ����G��x�y�� 
						G.y = y; // ����G��y�y��

						return;
						
					} // if ( x+1 < col && cMaze.matrix[y][x+1] == 'G' )
					 
					if ( x+1 < col && cMaze.matrix[y][x+1] != 'O' && cMaze.matrix[y][x+1] != 'V'){ 
						// �U�@�B���W�X��� �B ������(O) && ���ਫ���L����(V) 
						
						if ( cMaze.matrix[y][x+1] == 'E') { // �U�@�B��'E'�令'V' 
							cMaze.matrix[y][x+1] = 'V';
							this -> matrix[y][x+1] = 'V';
						} // if ( cMaze.matrix[y][x+1] == 'E') 
						
						walk( face, x+1, y, founded, aMaze, cMaze, count, G ); // �~��V�k 
						
						if ( founded ) {  
							if (aMaze.matrix[y][x + 1] != 'G') aMaze.matrix[y][x + 1] = 'R'; // ���G��NaMaze�����|'R'��� 
							return; 
						} // if ( founded ) 
						
					} // if ( x+1 < col && cMaze.matrix[y][x+1] != 'O' && cMaze.matrix[y][x+1] != 'V')
					
					face = Down; // ����V �V�U 
					i++; // ��V�����[�@ 
					
				} // if ( i < 4 && face == Right )
				
				if ( i < 4 && face == Down ){ // �V�U 
					if ( y+1 < row && cMaze.matrix[y+1][x] == 'G' ){ // �Y���W�X��� �B���G  

						founded = true; // ���G
						count = count + 1; // ���G���Ӽƥ[�@ 
						G.x = x; // ����G��x�y��  
						G.y = y+1; // ����G��y�y�� 
						return;
						
					} // if ( y+1 < row && cMaze.matrix[y+1][x] == 'G' ) 
					
					if ( y+1 < row && cMaze.matrix[y+1][x] != 'O' && cMaze.matrix[y+1][x] != 'V'){
						// �U�@�B���W�X��� �B ������(O) && ���ਫ���L����(V) 
						
						if ( cMaze.matrix[y+1][x] == 'E') { // �U�@�B��'E'�令'V' 
							cMaze.matrix[y+1][x] = 'V';
							this -> matrix[y+1][x] = 'V';
						} // if ( cMaze.matrix[y+1][x] == 'E')
						
						walk( face, x, y+1, founded, aMaze, cMaze, count, G ); // �~��V�U 
						
						if ( founded ) {
							if (aMaze.matrix[y + 1][x] != 'G') aMaze.matrix[y + 1][x] = 'R'; // ���G��NaMaze�����|'R'��� 
							return; 
						} // if ( founded )
						
					} // if ( y+1 < row && cMaze.matrix[y+1][x] != 'O' && cMaze.matrix[y+1][x] != 'V')
	
						face = Left; // ����V �V�� 
						i++; // ��V�����[�@  
						
				} // if ( i < 4 && face == Down )
				
				if ( i < 4 && face == Left ){ // �V�� 
					if ( x-1 >= 0 && cMaze.matrix[y][x-1] == 'G' ){ // �Y���W�X��� �B���G  

						founded = true; // ���G 
						count = count + 1; // ���G���Ӽƥ[�@ 
						G.x = x-1; // ����G��x�y��  
						G.y = y; // ����G��y�y�� 
						return;
						
					} // if ( x-1 >= 0 && cMaze.matrix[y][x-1] == 'G' )
					
					if ( x-1 >= 0 && cMaze.matrix[y][x-1] != 'O' && cMaze.matrix[y][x-1] != 'V'){
						// �U�@�B���W�X��� �B ������(O) && ���ਫ���L����(V)
						 
						if ( cMaze.matrix[y][x-1] == 'E') { // �U�@�B��'E'�令'V' 
							cMaze.matrix[y][x-1] = 'V';
							this -> matrix[y][x-1] = 'V';
						} // if ( cMaze.matrix[y][x-1] == 'E')
						
						walk( face, x-1, y, founded, aMaze, cMaze, count, G ); // �~��V�� 
						
						if ( founded ) {
							
							if (aMaze.matrix[y][x - 1] != 'G') aMaze.matrix[y][x - 1] = 'R'; // ���G��NaMaze�����|'R'��� 
							return; 
							
						} // if ( founded ) 
					} // if ( x-1 >= 0 && cMaze.matrix[y][x-1] != 'O' && cMaze.matrix[y][x-1] != 'V')
					
						face = Up; // ����V �V�W 
						i++; // ��V�����[�@  
						
				} // if ( i < 4 && face == Left )
				
				if ( i < 4 && face == Up ){ // �V�W 
					if ( y-1 >= 0 && cMaze.matrix[y-1][x] == 'G' ){ // �Y���W�X��� �B���G  
						
						founded = true; // ���G 
						count = count + 1; // ���G���Ӽƥ[�@ 
						G.x = x; // ����G��x�y��  
						G.y = y-1; // ����G��y�y�� 
						return;
						
					} // if ( y-1 >= 0 && cMaze.matrix[y-1][x] == 'G' )
					
					if ( y-1 >= 0 && cMaze.matrix[y-1][x] != 'O' && cMaze.matrix[y-1][x] != 'V'){
						// �U�@�B���W�X��� �B ������(O) && ���ਫ���L����(V) 
						
						if ( cMaze.matrix[y-1][x] == 'E') { // �U�@�B��'E'�令'V' 
							cMaze.matrix[y-1][x] = 'V';
							this -> matrix[y-1][x] = 'V';
						} // if ( cMaze.matrix[y-1][x] == 'E')
		
						walk( face, x, y-1, founded, aMaze, cMaze, count, G ); // �~��V�W 
						
						if ( founded ) { // ���G��NaMaze�����|'R'���
							if (aMaze.matrix[y - 1][x] != 'G') aMaze.matrix[y - 1][x] = 'R';  
							return; 	
						} // if ( founded )
						
					} // if ( y-1 >= 0 && cMaze.matrix[y-1][x] != 'O' && cMaze.matrix[y-1][x] != 'V')
					
						face = Right; // ����V �V�k 
						i++; // ��V�����[�@  
						
				} // if ( i < 4 && face == Up )
				
			} // for ( int i = 0; i < 4 ;) 
			
			founded = false;
			return;
			
		} // walk( Face face, int x, int y, bool& founded, Maze &aMaze, Maze cMaze, int &count, Goal &G ) 
		
		void shortWalk( Face face, int x, int y, Maze &aMaze, Maze cMaze, int &node ){
			
			
			for ( int i = 0; i < 4 && node < shortest;) { // �˴��|�Ӥ�V �̧� �k �U �� �W 
														  // �B�B�Ƥ��W�L�̵u���|�B�� 
				if ( i < 4 && face == Right && node < shortest ){ // �V�k  
					if ( x+1 < col && cMaze.matrix[y][x+1] == 'G' ){ // �Y���W�X��� �B���G 
						
						if ( node < shortest ) { // ����ثe�̵u���|�٤� 
							alter(aMaze, aMaze, 'R', 'E'); // aMaze��'R'���|�٭� 
							aMaze.matrix[0][0] = 'R'; // aMaze�_�I���]��'R' 
							shortest = node; // ��s�̵u���|�B�� 
							alter(cMaze, aMaze, 'V', 'R'); // �NcMaze��(�̵u)���|'V' �b aMaze��'R'�Х� 
						}
						

						return;
						
					} // if ( x+1 < col && cMaze.matrix[y][x+1] == 'G' )
					 
					if ( x+1 < col && cMaze.matrix[y][x+1] != 'O' && cMaze.matrix[y][x+1] != 'V'){ 
						// �U�@�B���W�X��� �B ������(O) && ���ਫ���L����(V) 
						
						if ( cMaze.matrix[y][x+1] == 'E') { // �U�@�B��'E'�令'V' 
							cMaze.matrix[y][x+1] = 'V';
							this -> matrix[y][x+1] = 'V';
							node++; // �B�ƥ[�@ 
						} // if ( cMaze.matrix[y][x+1] == 'E') 
						
						shortWalk( face, x+1, y, aMaze, cMaze, node ); // �~��V�k 
				
						node--; // �]���j��^�e�@�B �B�ƴ�@ 
						cMaze.matrix[y][x+1] = 'E'; // �N���L�����٭� ���F���v�T��̵u���| 
						
						//cout << "*" << count << endl;
						
						
					} // if ( x+1 < col && cMaze.matrix[y][x+1] != 'O' && cMaze.matrix[y][x+1] != 'V')
					
					face = Down; // ����V �V�U 
					i++; // ��V�����[�@ 
					
				} // if ( i < 4 && face == Right )
				
				if ( i < 4 && face == Down && node < shortest ){ // �V�U 
					if ( y+1 < row && cMaze.matrix[y+1][x] == 'G' ){ // �Y���W�X��� �B���G  
						
						if ( node < shortest ) { // ����ثe�̵u���|�٤� 
							alter(aMaze, aMaze, 'R', 'E'); // aMaze��'R'���|�٭� 
							aMaze.matrix[0][0] = 'R'; // aMaze�_�I���]��'R' 
							shortest = node; // ��s�̵u���|�B�� 
							alter(cMaze, aMaze, 'V', 'R'); // �NcMaze��(�̵u)���|'V' �b aMaze��'R'�Х� 
						}
						
					} // if ( y+1 < row && cMaze.matrix[y+1][x] == 'G' ) 
					
					if ( y+1 < row && cMaze.matrix[y+1][x] != 'O' && cMaze.matrix[y+1][x] != 'V'){
						// �U�@�B���W�X��� �B ������(O) && ���ਫ���L����(V) 
						
						if ( cMaze.matrix[y+1][x] == 'E') { // �U�@�B��'E'�令'V' 
							cMaze.matrix[y+1][x] = 'V';
							this -> matrix[y+1][x] = 'V';
							node++; // �B�ƥ[�@ 
						} // if ( cMaze.matrix[y+1][x] == 'E')
						
						shortWalk( face, x, y+1, aMaze, cMaze, node ); // �~��V�U
						
						node--; // �]���j��^�e�@�B �B�ƴ�@  
						cMaze.matrix[y+1][x] = 'E'; // �N���L�����٭� ���F���v�T��̵u���|  
						
						
						
					} // if ( y+1 < row && cMaze.matrix[y+1][x] != 'O' && cMaze.matrix[y+1][x] != 'V')
	
						face = Left; // ����V �V�� 
						i++; // ��V�����[�@  
						
				} // if ( i < 4 && face == Down )
				
				if ( i < 4 && face == Left && node < shortest ){ // �V�� 
					if ( x-1 >= 0 && cMaze.matrix[y][x-1] == 'G' ){ // �Y���W�X��� �B���G  
						
						if ( node < shortest ) { // ����ثe�̵u���|�٤� 
							alter(aMaze, aMaze, 'R', 'E'); // aMaze��'R'���|�٭� 
							aMaze.matrix[0][0] = 'R'; // aMaze�_�I���]��'R' 
							shortest = node; // ��s�̵u���|�B�� 
							alter(cMaze, aMaze, 'V', 'R'); // �NcMaze��(�̵u)���|'V' �b aMaze��'R'�Х� 
						}
						
						return;
						
					} // if ( x-1 >= 0 && cMaze.matrix[y][x-1] == 'G' )
					
					if ( x-1 >= 0 && cMaze.matrix[y][x-1] != 'O' && cMaze.matrix[y][x-1] != 'V'){
						// �U�@�B���W�X��� �B ������(O) && ���ਫ���L����(V)
						 
						if ( cMaze.matrix[y][x-1] == 'E') { // �U�@�B��'E'�令'V' 
							cMaze.matrix[y][x-1] = 'V';
							this -> matrix[y][x-1] = 'V';
							node++; // �B�ƥ[�@
						} // if ( cMaze.matrix[y][x-1] == 'E')
						
						shortWalk( face, x-1, y, aMaze, cMaze, node ); // �~��V�� 
				
						node--; // �]���j��^�e�@�B �B�ƴ�@  
						cMaze.matrix[y][x-1] = 'E'; // �N���L�����٭� ���F���v�T��̵u���|  
					
				
						
					} // if ( x-1 >= 0 && cMaze.matrix[y][x-1] != 'O' && cMaze.matrix[y][x-1] != 'V')
					
						face = Up; // ����V �V�W 
						i++; // ��V�����[�@  
						
				} // if ( i < 4 && face == Left )
				
				if ( i < 4 && face == Up && node < shortest ){ // �V�W 
					if ( y-1 >= 0 && cMaze.matrix[y-1][x] == 'G' ){ // �Y���W�X��� �B���G  
						
						if ( node < shortest ) { // ����ثe�̵u���|�٤� 
							alter(aMaze, aMaze, 'R', 'E'); // aMaze��'R'���|�٭� 
							aMaze.matrix[0][0] = 'R'; // aMaze�_�I���]��'R' 
							shortest = node; // ��s�̵u���|�B�� 
							alter(cMaze, aMaze, 'V', 'R'); // �NcMaze��(�̵u)���|'V' �b aMaze��'R'�Х� 
						}
						
						return;
						
					} // if ( y-1 >= 0 && cMaze.matrix[y-1][x] == 'G' )
					
					if ( y-1 >= 0 && cMaze.matrix[y-1][x] != 'O' && cMaze.matrix[y-1][x] != 'V'){
						// �U�@�B���W�X��� �B ������(O) && ���ਫ���L����(V) 
						
						if ( cMaze.matrix[y-1][x] == 'E') { // �U�@�B��'E'�令'V' 
							cMaze.matrix[y-1][x] = 'V';
							this -> matrix[y-1][x] = 'V';
							node++; // �B�ƥ[�@ 
						} // if ( cMaze.matrix[y-1][x] == 'E')
		
						shortWalk( face, x, y-1, aMaze, cMaze, node ); // �~��V�W 
				
						node--; // �]���j��^�e�@�B �B�ƴ�@  
						cMaze.matrix[y-1][x] = 'E'; // �N���L�����٭� ���F���v�T��̵u���|  
						
						
						
					} // if ( y-1 >= 0 && cMaze.matrix[y-1][x] != 'O' && cMaze.matrix[y-1][x] != 'V')
					
						face = Right; // ����V �V�k 
						i++; // ��V�����[�@  
						
				} // if ( i < 4 && face == Up )
				
			} // for ( int i = 0; i < 4 ;) 
		
			return;
			
		} // walk( Face face, int x, int y, Maze &aMaze, Maze cMaze, int &node ) 
		
		// ������m�ഫ�r��  
		void alter( Maze cMaze, Maze &aMaze, char ch, char to ) {  
			
			for (int j = 0 ; j < row ; j++){
    			for( int i = 0 ; i < col ; i++ ){
    				if (cMaze.matrix[j][i] == ch) aMaze.matrix[j][i] = to; // cMaze ���Ҧ�ch�r�� �b������aMaze ������m�ഫ��to�r��  
				}  
			}
			return;
		}
	
		// ����O���� 
		void clr(){
			matrix.clear();
		} // void clr()
		
		
		void show(){ // �L�X�Ҧ��g�c��� 
			for (int j = 0 ; j < row ; j++){
    			for( int i = 0 ; i < col ; i++ ){
    				cout << matrix[j][i];   
				} 
				cout << endl; 
			}
			cout << endl;  
		} // void show()
	
	
};


int main(){
	
	int command = 0;
	do
	{
		Maze aMaze; 
		string fileName; // fileName �ΨӦs�n�}�Ҫ����W�� 
		Modes mode = oneG; // �]�wmode ��l�Ȭ�oneG 
		
		cout<<endl<<"*** Path Finding ***";
		cout<<endl<<"* 0. Quit          *";
		cout<<endl<<"* 1. One goal      *";
		cout<<endl<<"* 2. More goals    *";
		cout<<endl<<"* 3. Shortest path *";
		cout<<endl<<"********************";
		cout<<endl<<"Input a command(0, 1, 2, 3):";
		cin>>command;
		
		if((command == 1) || (command == 2) || (command == 3 )){ 
			if(command == 2) mode = moreG; // �]�wmode ��moreG 
			if(command == 3) mode = shortestG; // �]�wmode ��shortestG
			cout<<endl<<"Input a file number (e.g., 201, 202, ...): ";
			cin>>fileName; // ��J���W�� 
			
			if(aMaze.load(fileName)){ // ���J��󤺮e �æs�JaMaze�� 
				Maze vMaze(aMaze); // �ƻsaMaze ��s�Ъ����� vMaze��  
				bool success = vMaze.visit(mode, aMaze); // ���X(�Ҹg�L�����|) �O�_�̫ᦳ��� �n�䪺�Ҧ��ؼ� 
	
				mode = oneG; // �]�w����l�� 
				vMaze.show(); // �N���L�����|��matrix �L�X�� 
				
				if ( (command == 1) || (command == 2 ) ){
					if ( success ) aMaze.show(); // �Y�F�����Ҧ��ؼ� �N ��ؼи��|��matrix �L�X�� 
				}
				
				if ( command == 3 ){
					if ( vMaze.shortest != 9999999 ) {
						aMaze.show();
						cout << endl << "Shortest path lenth = " << vMaze.shortest << endl;
						
					}
					else cout << "### There is no path to find a goal! ###" << endl;
					system("pause");
				}
				vMaze.clr(); // ���� 
				aMaze.clr(); // ����
			}
			
		}
		else if(command == 0) break; // ���}(���X�j�鵲��) 
		else cout<<endl<<"Command does not exist!"<<endl; // ���s�b�����O         
	} while(true);
	system("pause");
	return 0;
}


