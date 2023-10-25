// 11127116 ����E 
# include <iostream>
# include <string>
#include <fstream>
#include <vector>
#include <cctype> 

using namespace std;

class Maze {

	
	public :
		bool load ( string fileName, int mode ); // �q�ɮץ[���g�c
		bool findGoal( Maze &vMaze, int row, int column, int dir ); // �M��g�c�����ؼ� 
		void show(); // ��ܰg�c����e���A 
		bool findWay(Maze &vMaze, int mode); // �B�z�h�ӥؼЪ��̨θ��|���D 
		void findGoal3( Maze &vMaze, int row, int column, int dir,int vNum, bool &find );
		int howLong; // ���L�h�� 
		Maze(){
			found = 0; // ��l�Ƥw��쪺�X�f�Ƭ�0 
			goals = 1; // �w�]���X�f�Ƭ�1 
			howLong = 1000; 
		}
		
		
	private :
		int length; // �g�c������
		int width;  // �g�c���e��
		int dir;    // �ثe����V
		vector<string> trace; // �Ψ��x�s�g�c���C�@����
		vector<string> all; 
		int goals; // �X�f���ƶq
		int found; // �w��쪺�X�f��
		
};

int main () {
	int cmd = 1; // ���O 
	while ( cmd != 0 ) {
		Maze aMaze; // �Ыؤ@�Ӱg�c����
		string fileName; // �s�x�ɮצW
		int mode = 1; // �Ҧ� (1�N��@�ӥX�f, 2�N��h�ӥX�f)
		// ��ܻ��� 
		cout << endl << "*** Path Finding ***";
		cout << endl << "* 0. Quit          *";
		cout << endl << "* 1. One goal      *";
		cout << endl << "* 2. More goals    *";
		cout << endl << "* 3. shortest path *";
		cout << endl << "********************";
		cout << endl << "Input a command(0, 1, 2, 3):";
		cin >> cmd; // ��J���O
		
		// ���J�δM��g�c 
		if ( cmd == 1 || cmd == 2 || cmd == 3 ) {
			if ( cmd == 2 )
				mode = 2;
				
			if ( cmd == 3 )
				mode = 3;
			
			cout << endl << "input file name : " ;
			cin >> fileName;
			if ( aMaze.load( fileName, mode ) ) {
				Maze vMaze(aMaze);
				bool success = aMaze.findWay( vMaze, mode );

				vMaze.show();
				if ( success ) {
					aMaze.show();
					if ( mode == 3 )
						cout << endl << "shortest path : " << aMaze.howLong+1;
				}
				mode = 1;
					
			} 
		} // if
		else if ( cmd == 0 ) {
			break ; // �����{��
		}
		else {
			cout << endl << "command does not exist" << endl; // ��ܿ��~�T��
		} // else
		
	} // while
	
	cout << "pause" ; // ��ܵ����T��
	return 0;
}

// �H�U�O Maze ���O��������ƪ���{

bool Maze :: load ( string fileName, int mode ) {
	// �[���g�c���
	fileName = "input" + fileName + ".txt"; // �զX�ɮצW
	std::ifstream file;
	file.open( fileName.c_str() , std::ios::in); // ���}��Ƨ�
	// �p�G�L�k�}����� Unable to open the file.
	if (!file.is_open()) {
        cout << "Unable to open the file." << endl;
        return false;
    }
    
    string line;
    int count = 0;
    file >> length >> width;  // Ū���g�c���j�p 
    getline(file,line); // ��Ŧ�Ū�� 

	// Ū���g�c���C�@����
    while ( ! file.eof() ) {
    	getline(file,line);
        trace.push_back(line);  // �N��K�[�� vector ��
    }
    
    file.close(); // �����ɮ�
    
     // �p�Gmode���G�A��J�X�f���ƶq
    if ( mode == 2 ) {
    	cout << "Nunber of goals ? ";
    	cin >> goals;
	}
    return true;
} // load

bool Maze :: findGoal( Maze &vMaze, int row, int column, int dir ) {
	// �o�Ө�ƪ��ت��O�q���w����m(row, column)�}�l�A�չϴM��g�c���X�f�C
    // ��Ʒ|�ھڷ�e����V(dir)�i��j���A�æb���n�ɧ��ܤ�V�C
    // �Y���X�f�Ƶ����J���ƶq�A�h��^true�F�_�h��^false�C
    
	bool control = false; // �ΨӰO����U�o�Ӹ`�I�O�_�����g����( �O�_��R�I ) 
	int count = 0; // �ΨӰO����U�o�Ӹ`�I���L�X�Ӥ�V 
	
	// �Ψ��קKvector��index�ܦ�-1 
	if ( column < 0 ) 
		return false;
		
	// �ˬd��e��m�O�_���X�f(G)
	if ( vMaze.trace[column][row] == 'G' ) {
		vMaze.found = vMaze.found + 1;
	} // if
	
	if ( vMaze.goals == vMaze.found ) { // �p�G��쪺�ؼмƵ���P��J�Ȭ۵��^�����Ȧ�
	 
		return true;
	}
	else if ( 0 > row || row >= length || 0 > column || column >= width ) {  // �p�G�W�X�g�c����ɡA�h��^false
		return false;
	}
	else if ( vMaze.trace[column][row] == 'O' || vMaze.trace[column][row] == 'V' || vMaze.trace[column][row] == 'T' ) {
		// �p�G��e��m�O�@����(O)�B�w�X�ݹL�����|(V)�Τw�X�ݹL���ؼ�(T)�A�h��^false
		return false;
	}
	else if( vMaze.trace[column][row] == 'E' || vMaze.trace[column][row] == 'G' ) { // �p�G��e��m�O�J�f(E)�ΥX�f(G) 
		
		// �аO���w�X��
		if ( vMaze.trace[column][row] == 'E' )
			vMaze.trace[column][row] = 'V';  
		else 
			vMaze.trace[column][row] = 'T';
		
		// ���թҦ��|�Ӥ�V�i��j��
		while ( count < 4 ) {
			switch ( dir % 4 ) {
				case 0 :
					control = findGoal( vMaze, row + 1, column, dir );
					break;
					
				case 1 :
					control = findGoal( vMaze, row, column + 1, dir );
					break;
					
				case 2 :
					control = findGoal( vMaze, row - 1, column, dir );
					break;
					
				case 3 :
					control = findGoal( vMaze, row, column - 1, dir );
					break;
			}
			if ( control ) {
				// �p�G�b�Y�Ӥ�V�W���X�f�A�h�аO��e��m�����|(R)�ê�^true
				trace[column][row] = 'R';
				return true;
			}
			dir = dir+1;// ���ܤ�V
			count = count+1;// �W�[�w���ժ���V��
		}
	}
	
	return false; // �p�G�Ҧ���V���L�k���X�f�A�h��^false
}

void Maze :: show (  ) {
	
	// �o�Ӱj�骺�ت��O�N�Ҧ���ܥؼЪ� 'T'( �w���L���ؼ� ) �r�Ŵ����^ 'G' �r��
	for (int i = 0; i < trace.size(); i++) {
    	for (int j = 0; j < trace[i].size(); j++) {
        	if (trace[i][j] == 'T') {
            	trace[i][j] = 'G';
        	}
    	}
	}

	// �o�Ӱj�骺�ت��O��ܾ�Ӱg�c����e���A
	for ( int i = 0; i < trace.size(); i++ ) {
		cout << endl << trace.at(i);
	}
}

bool Maze :: findWay( Maze &vMaze, int mode ) {
	int row = 0, column = 0, dir = 0, num = goals; // ��l�ư_�l��m�M��V 
	int vNum = 0;
	vector<string> temp = trace; // �Ыؤ@���{��vector���x�s��e�g�c�����A 
	Maze oMaze(vMaze); // �Ыؤ@�ӷs���g�c����@�������쥻G�����ت��ƥ�(���F�ѨMG��R�����D) 

	bool find = false; // �Ω�P�_�O�_���ؼЪ��лx
	if ( mode == 3 ) {
		all = vMaze.trace;
		findGoal3( vMaze, row, column, dir, vNum, find );
		vMaze.trace = all;
		for (int i = 0; i < trace.size(); i++) {
    		for (int j = 0; j < trace[i].size(); j++) {
        		if (trace[i][j] == 'V') {
            		trace[i][j] = 'R';
        		}
    		}
		}
	
		if ( find == false )
			return false; 
	
		return true;
	}

		
	// �B�z�h�ӥؼЪ��̨θ��|���D
	
	// �B�z�h�ӥؼЪ��̨θ��|���D
	while ( vMaze.goals > 0 ) {
		Maze tMaze( vMaze );
		find = findGoal( tMaze, row, column, dir );
		if ( !find ) {
			findGoal( vMaze, row, column, dir );
			return false;
		}

		// �ѨM�������D 
		for (int i = 0; i < trace.size(); i++) {
    		for (int j = 0; j < trace[i].size(); j++) {
				if ( trace[i][j] == 'R' && temp[i][j] != 'R' ) {
					temp[i][j] = 'R';
				}
    		}
		}
		vMaze.goals = vMaze.goals-1;
	}
	vMaze.goals = num;
	findGoal( vMaze, row, column, dir ); // �ͦ�vMaze 
	
	// �ѨMG��R�����D 
	for (int i = 0; i < trace.size(); i++) {
    	for (int j = 0; j < trace[i].size(); j++) {
			if ( temp[i][j] == 'R' && oMaze.trace[i][j] == 'G' ) {
				temp[i][j] = 'G';
			}
   		}
	}
	trace = temp; // �x�s��s�᪺�g�c���A
	return true;
}

void Maze :: findGoal3( Maze &vMaze, int row, int column, int dir, int vNum, bool &find ) {

    
	int count = 0; 
	
	if ( column < 0 ) 
		return ;

	if ( vNum >= howLong ) {
		return ;
	}
		
	if ( vMaze.trace[column][row] == 'G' ) {
		howLong = vNum;
		find = true;
		trace = vMaze.trace;
		return ;
	} // if
	


	if ( 0 > row || row >= length || 0 > column || column >= width ) {  // �p�G�W�X�g�c����ɡA�h��^false
		return ;
	}
	else if ( vMaze.trace[column][row] == 'O' || vMaze.trace[column][row] == 'V' ) {
		// �p�G��e��m�O�@����(O)�B�w�X�ݹL�����|(V)
		return ;
	}
	else if( vMaze.trace[column][row] == 'E'  ) { // �p�G��e��m�O�J�f(E)	
	// �аO���w�X��

	vMaze.trace[column][row] = 'V'; 
	all[column][row] = 'V';

		
		// ���թҦ��|�Ӥ�V�i��j��
	while ( count < 4 ) {
		switch ( dir % 4 ) {
			case 0 :
				findGoal3( vMaze, row + 1, column, dir, vNum+1, find );
				break;
									
			case 1 :
				findGoal3( vMaze, row, column + 1, dir, vNum+1, find );
				break;
					
			case 2 :
				findGoal3( vMaze, row - 1, column, dir, vNum+1, find );
				break;
					
			case 3 :
				findGoal3( vMaze, row, column - 1, dir, vNum+1, find );
				break;
		}

		dir = dir+1;// ���ܤ�V
		count = count+1;// �W�[�w���ժ���V��
		}
	}
	
	vMaze.trace[column][row] = 'E'; 
	return ; // �p�G�Ҧ���V���L�k���X�f�A�h��^false	

}
