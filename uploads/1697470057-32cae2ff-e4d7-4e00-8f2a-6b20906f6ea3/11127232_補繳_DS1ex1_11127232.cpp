// �Ǹ�:11127232 �m�W:�L౮f 
 
#include <iostream>
#include <vector>
#include <limits.h>
#include <string>
#include <fstream>

/* 
���ѫᦳ�A��(���ȤT)���{���A
�N��o���ܼƩάOfunction�ȷ|�b���O3�Ψ�C 
*/

 
using namespace std;

const int direct[4][2] = { { 0 , 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } }; // ���O�N���k�B�U�B���B�W�樫�@�B 

struct Coor{ // �ΨӦs�y�Ц�m����ƫ��A 
	
	int x;
	int y;
	
};

class Maze {
	
private:
	
	int check; 				// �ˬd�O�_�����G(�ؼ�) 
	int width; 				// �g�c���� 
	int height; 			// �g�c���� 
	int shortpath;			// �̵u���| 
	int limit;				// ���j����(���ȤT) 
	int run_times;			// �ثe�����B��(���ȤT) 
	vector<string> data;	// �g�c�����  
	vector<string> backup;	// �g�c��ƪ��ƥ�( �Ω��x�s���G(�ؼ�)�����|R ) 
	vector<string> mapV;	// �x�s���|V(���ȤT) 
	vector<string> mapR;	// �x�s���|R(���ȤT) 
	vector<Coor> target;	// �Ψ��x�sG(�ؼ�)����m 
	int g_num;				// ����`�@�n�M��X��G(�ؼ�) 
	bool success;			// ��ܬO�_�����\�b�g�c�����۹����ƶq���ؼ� 
	
	ifstream file;			// �гy�@�ӥi�Ψ�Ū���ɮת����� 

	
public:
	
	bool load() {							// Ū�J��� 
		
        string name = "";					
        
        cin >> name;						// ��J���W�� 
        name = "input" + name + ".txt";
		 
		file.open(name.c_str());			// ���}��������ɮ� 
		
	    if (!file.is_open()) {				// �T�{�ɮ׬O�_���Q���} 
	    	
	        cout << "\n" << name << " does not exist!" << endl;	
	    	return false;					// �N���J���~���ɦW 
	        
	    }
	    
	    check = 0;							// ��l��check( 0���|�����ؼ� ) 
	    g_num = 1;							// ��l�ƥؼЪ��Ӽ�( �w�]1�� ) 
	    success = false;					// ��l��success( �P�_�O�_�����\���g_num�ӥؼ� ) 
	    Setdata();							// ��J�g�c��� 
	    mapV = data;						// �x�s�g�c���(���ȤT) 
	    mapR = data;						// �x�s�g�c���(���ȤT) 
	    file.close();						// ��������� 
	    
	    return true;						// ���\��J���T�ɦW 
    }
	
	void Setdata() {						
		
		string input = "";
		
		file >> width;
		file >> height;
		
		for ( int i = 0; i < height; i++ ) {
			
			file >> input;
			data.push_back( input );
			
		}
		
	}
	
	void Setgoal() {
		
		cin >> g_num;
		
	}
	
	void Revise( int x, int y, char ch ) {		// ���g�c��T 
		data[x][y] = ch;				
	}
	
	void Delete_V() {							// �N�g�c���Ҧ���V�令E( �N�w�樫�����|�٭� ) 
		
		for( int x = 0; x < height; x++ ) {
			for( int y = 0; y < width; y++ ){
		    	if ( data[x][y] == 'V' )
		    		Revise( x, y, 'E' );
			}
		}
		
	}
	
	void VtoR() {								// �N���|V�令R(���ȤT) 
		
		for( int x = 0; x < height; x++ ) {
			for( int y = 0; y < width; y++ ){
		    	if ( data[x][y] == 'V' )
		    		mapR[x][y] = 'R';
			}
		}
		
	}
	
	void RtoE() {								// �N���|R�令E(���ȤT) 			
		
		for( int x = 0; x < height; x++ ) {
			for( int y = 0; y < width; y++ ){
		    	if ( mapR[x][y] == 'R' )
		    		mapR[x][y] = 'E';
			}
		}
		
	}
	
	void Copy_V( int x, int y ) {				// �NmapV�������y�Ч令V(���ȤT) 
		
		mapV[x][y] = 'V';
		
	}
	
	void Restore_G() {							// �N�g�c���Ҧ���G�٭�
		
		for( int i = 0; i < target.size(); i++ ) 
			data[target[i].x][target[i].y] = 'G';
		
	}
	
	void Copy_R() {								// �x�s���|R����m��t�@�i�ƥ��a�ϤW 
		
		for( int x = 0; x < height; x++ ) {
			for( int y = 0; y < width; y++ ){
		    	if ( data[x][y] == 'R' && backup[x][y] != 'G' )
		    		backup[x][y] = 'R';
			}
		}
		
	}
	
	bool IsValid( int x, int y ) {				// �P�_�ѹ��O�_���ʨ�W�X��ɩάO����
	
		if ( x >= 0 && y >= 0 && x < height && y < width &&
		     data[x][y] != 'O' && data[x][y] != 'V' )
			return true;
			
		return false;
	
	}
	
	void Print_V() {							// �L�X����g�c��V���|��T (���ȤT)
		
		for( int i = 0; i < height; i++ )
			cout << mapV[i] << endl;
		  
	}
	
	void Print_R() {							// �L�X����g�c��R���|��T (���ȤT)
		
		cout << endl;
		for( int i = 0; i < height; i++ )
			cout << mapR[i] << endl;
		  
	}
	
	void Print() {								// �L�X����g�c��T 
		
		for( int i = 0; i < height; i++ )
			cout << data[i] << endl;
		  
	}
	
	void Move_V( int x, int y, int last ) {		// �ѹ����� ( �ΨӰO�����|V ) 
	
		for ( int i = last; i < last + 4 && check == 0 ; i++ ) {	// �|�Ӥ�V 
			
			int path = i % 4;	
			x = x + direct[path][0];			// ���S�w��V���ʤ@�� 
			y = y + direct[path][1];
	
			if ( IsValid( x, y ) ) {			// �T�{�L����ζW�X���				
				
				
				if ( data[x][y] == 'G' ) {		// ���ؼЪ��� 
					Coor g_xy = { x, y };		// �x�s�ؼЦ�m 
					target.push_back( g_xy );	// �O����쪺�ؼЦ�m 
				}
													
				Revise( x, y, 'V' );			// �N���y�ЭקאּV( ���L���� ) 
				 
				if ( target.size() == g_num ) {	// �p�G�Ҧ��ؼг��Q��쪺��  
					success = true;				// �N��j�M���\
					
					check = 1;
					break;
					
				}
				
				Move_V( x, y, path );
			}
			
			x = x - direct[path][0];
			y = y - direct[path][1];
	
			
		}
		
	}
	
	void Move_R( int x, int y, int last ) {		// �ѹ����� ( �ΨӰO�����|R ) 
	
		for ( int i = last; i < last + 4 && check == 0 ; i++ ) { 
			
			int path = i % 4;
			x = x + direct[path][0];
			y = y + direct[path][1];
			
			if ( IsValid( x, y ) ) {
				
				if ( data[x][y] == 'G' ) {
				 	
					Revise( x, y, 'E' );		// �M���G���ܴN��L�ק令E 
					check = 1;					// �������j 
					break;
					
				}
				
				Revise( x, y, 'V' );	
				Move_R( x, y, path );
				
				if ( check == 1 ) {				// ���^�s�W���|R
					Revise( x, y, 'R' );	
				}
				
			}
			
			x = x - direct[path][0];
			y = y - direct[path][1];
	
			
		}
		
	}
	
	void Move_V2( int x, int y, int last, int road ) {	// �ѹ����� (���ȤT) 
	
		if ( run_times > limit )				// �W�L�a�ϨB�Ƶ������j 
			return;
	
		for ( int i = last; i < last + 4 && shortpath > road + 1 ; i++ ) {	// �|�Ӥ�V 
			
			int path = i % 4;	
			x = x + direct[path][0];			// ���S�w��V���ʤ@�� 
			y = y + direct[path][1];
	
			if ( IsValid( x, y ) ) {			// �T�{�L����ζW�X���	
				
				road++;
				run_times++;
				
				if ( data[x][y] == 'G' ) {		// ���ؼЪ��� 
				
					shortpath = road; 
					check = 1;
					
					RtoE();						// �N���|R�令E
					VtoR();						// �N���|V�令R
	
				}
				
				else {

					Revise( x, y, 'V' );		// �N���y�ЭקאּV( ���L���� ) 
					Copy_V( x, y );				// �N���|V�ƻs��mapV�� 
					
				}	
				 
				Move_V2( x, y, path, road );	// �~�� 
				
				road--;							// ���|����@( ���^�� ) 
			}
					
			x = x - direct[path][0];
			y = y - direct[path][1];
	
			
		}
		
	    if (  data[x][y] != 'G' ) {			// �N��^�����令E 
				
			Revise( x, y, 'E' );
			
		}
		
	}
	
	void Clean() {								// �M����� 
		
		data.clear();
		backup.clear();
		target.clear();
		
	}
	
	void Findgoals() {
		
		Revise( 0, 0, 'V');						//  �N�}�Y�]���w���L�����|( �}�Y����E )  
		Move_V( 0, 0, 0 ); 						//  �q�Y�}�l���k���� 
				
		Restore_G();							//  �N�Q�令V���ؼ��٭즨G 
		Print(); 								//  �L�X���L���|V���a�� 
		Delete_V();								//  �N���L�����|V�R���ô�����E( �٭�a�� ) 
		backup = data;							//  �]�m�ƥΦa�� 
		
		if ( success ) {						//  �p�G�����\�����w�ƶq���ؼЪ���  
			
			for ( int i = 0; i < g_num; i++ ) {	//  �j�Mg_num���g�c 
			
				check = 0;
				Move_R( 0, 0, 0 );			
				Delete_V();			 
				Copy_R();						//  �N��쪺���|R�̧ǽƻs��ƥ��g�c�� 
			}

			data = backup;						//  �䧹��ϱodata����ƥ��g�c���a�� 
			Revise( 0, 0, 'R' );				//  �N�}�Y�אּ���|R( �}�Y����R )
				
			cout << endl;
			Print(); 							//  �L�Xdata������� 
			
		}
		
		cout << endl;
 
	}
	
	void Test3() {
		
		shortpath = INT_MAX;			// ���]�B�Ƭ��̤j 
		limit = width * height * 4;		// �����B�� 
		run_times = 0;
		data[0][0] = 'V';				// �}�Y����E 
		mapV[0][0] = 'V';				// �}�Y����E  
		
		Move_V2( 0, 0, 0, 1 );			// �q���I�}�l���k�A�@�}�l���|����1 
		
		
		Print_V();						// �L�X���L�����| 
		
		if ( check == 1 ) {				// �p�G�����G 
			
			Print_R();
			cout << endl << endl << "Shortest path length = " << shortpath << endl;
		}
		
		else {							// �p�G�S���G 
			cout << endl << endl << "### There is no path to find a goal! ###" << endl;
		}
		
		system("pause");
			
	}
	
};

int main() {
	
	do {
		
		cout << "*** Path Finding ***\n";
	    cout << "* 0. Quit          *\n";
	    cout << "* 1. One goal      *\n";
	    cout << "* 2. More goals    *\n";
	    cout << "* 3. Shortest path *\n";
	    cout << "********************\n";
	    cout << "Input a command(0, 1, 2, 3): ";
	    
	    Maze map;
	    string command;
	    
		cin >> command;												// ��J���O 
		
		if ( command.compare( "1" ) == 0 || command.compare( "2" ) == 0 || command.compare( "3" ) == 0 ) {	// 1�O��@�ӥؼ�,2�O��h�ӥؼ� 
		
			cout << "\nInput a file number: ";	 
			
			if ( map.load() ) {										// Ū�J��� 
				
		    	if ( command.compare( "2" ) == 0 ) {
		    		
		    		cout << "\nNumber of G (goals): ";
					map.Setgoal();									// �]�w�n��h�֥ؼ� 
		    		
				}
				
		    	if ( command.compare( "3" ) == 0 ) {
		    		
					map.Test3();							
		    		
				}
				
				else if ( command.compare( "3" ) != 0 ) {
				
					map.Findgoals();   								// �M��æL�X���� 
					
				}
				
			}
			
		}
		
		else if ( command.compare( "0" ) == 0 )						// ��J���O0�h���� 
			break;
			
		else														// ��J�������O( ���O0�B1�B2�B3 ) 
			cout << "\nCommand does not exist!" << endl;
	
		cout << endl;
		
		map.Clean();												// �M����� 
		
	} while ( true );
	
} 
