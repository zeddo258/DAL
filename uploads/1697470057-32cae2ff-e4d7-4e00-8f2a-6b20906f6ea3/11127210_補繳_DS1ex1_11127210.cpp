// ��u�G�A 11127210 �B�ۧ� 
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std ;

// �x�s�g�c�����|��T
struct Block {
	char pos ; // �O�������|�����A E O V G R 
	bool GisPassed = false ; // �Y��Block��pos�x�s���O�ؼ�G�A����G�O�_�w�g�Q���L 
	bool VFalsereturned = false ; // �Y��Block��pos�x�s���OV�A���������|�|�Ӥ��e��O�_�������Φh�l����
	bool Rsign = false ; // �O�_���̵u���| 
	int step = 0 ; // �x�s�����|���_�I���̵u�B�� 
};


// �g�c���U����T 
class Maze {
public:
	
	// Constructor 	
	Maze() {}
	
	// Copy Constructor
	Maze( Maze& other ){
		
		// �ƻs Maze�̪��U����T 
		row = other.getRow() ;
		col = other.getCol() ;
		countG = other.getcountG() ;
		mouseDirection = other.getMouseDirection() ;
		
		for( int i = 0 ; i < row ; i++ ) {
			for( int j = 0 ; j < col ; j++ ) {
				maze[i][j].pos = other.getPos( i, j ) ;
				maze[i][j].GisPassed = other.getGisPassed( i, j ) ;
				maze[i][j].VFalsereturned = other.getVFalsereturned( i, j ) ;
			} // for j
		} // for i
		
	} 
	
	// �^�� Gfounded
	bool getGfounded() {
		return Gfounded ;
	} 
	// �^��shortest
	int getShortest () {
		return shortest ;
	}
	 
	// �^��step 
	int getStep () {
		return step ;
	}

	// �^��mouseDirection
	int getMouseDirection() {
		return mouseDirection ;
	}


	// �^��maze����m��T pos
	char getPos( int x, int y ) {
		return maze[x][y].pos ;
	} 
	
	// �^��maze�� GisPassed
	bool getGisPassed( int x, int y ) {
		return maze[x][y].GisPassed ;
	} 
	
	// �^��maze�� VFalsereturned
	bool getVFalsereturned( int x, int y ) {
		return maze[x][y].VFalsereturned ;
	}
	
	// �^��row���� 
	int getRow() {
		return row ;
	} // getRow()
	
	// �^��col���� 
	int getCol() {
		return col ;
	} // getCol()

	// �ƥX�ثe�g�L���ؼ�G�ƶq 
	void addG() {
		countG = countG + 1 ;
	} // addG() 
	
	// �^��countG���� 
	int getcountG() {
		return countG ;
	} // getcountG()
	
	// �^��Gfounded


	// ���ܦѹ��ثe���ʪ���V�A���Ǭ�: 0(�k) 1(�U) 2(��) 3(�W) �`�� 
	void changeDirection() {
		if ( mouseDirection == 3 ) {
			mouseDirection = 0 ;
		} // if
		else {
			mouseDirection = mouseDirection + 1 ;	
		}
	} // changeDirection()

	// �L�X�g�c 
	void show() {
		
		for( int i = 0 ; i < row ; i++ ){
			for( int j = 0 ; j < col ; j++ ){
				
				if ( j == (col - 1) )
					cout << maze[i][j].pos << endl ;
				else 
					cout << maze[i][j].pos ;
					
			} // for j
		} // for i
		
	} // show()
	
	



	// ��l�ưg�c��T 
	void resetAll() {
		
		row = 0 ;
		col = 0 ;
		mouseDirection = 0 ;
		countG = 0 ;
		shortest = 999999999 ;
		Gfounded = false ;
		
		
		for( int i = 0 ; i < 100 ; i++ ){
			for( int j = 0 ; j < 100 ; j++ ){
				maze[i][j].pos = '\0' ;
			} // for j
		} // for i
			
	} // resetAll
	
	
	// ���J�g�c 
	bool load( string Snumber ) {
		
		// �ܼư� 
		ifstream in ;
		string filename ;
		char temp ; // �Ȯ��x�s�r�� 

		
		// �}�ҥH"Input" + Snumber + ".txt"���W�r���ɮ� 
		filename = "Input" + Snumber + ".txt" ;
		in.open( filename.c_str() ) ;
		
		// �Y�}���ɮץ��ѡA�h��Xfilename + "does not exist!" 
		if ( in.fail() ) {
			cout << filename + " does not exist!" << endl ;
			return false ;
		} // if ( in.fall ) 
		
		else {
			
			// Ū�J�g�c���j�p 
			in >> col >> row ;
			
			// �קKrow�H��col�O�t�Ʃ�0 
			if( row < 1 || col < 1) {
				return false ;
			} //if( row < 1 || col < 1)
			
			// Ū�J�g�c���Ĥ@����� 
			in >> temp ;

			// Ū�J�g�c����ơA�æs��maze			
			for( int i = 0 ; i < row ; i++ ){
				for( int j = 0 ; j < col ; j++ ){
					maze[i][j].pos = temp ;
					in >> temp ;
				} // for j
			} // for i
			
			
		} // else 
		
		in.close() ; // ����O���� 
	} // load( string Snumber )
	
	
	// �u�ݭn���@�ӥؼ�G�����p 
	bool findAGoal ( int x, int y ) {
		
		// dx,dy ���ѹ������ʤ�V 
		int dx[10] = { 0, 1, 0, -1 } ;
		int dy[10] = { 1, 0, -1, 0 } ;
		
		// newX,newY ���ѹ��U�@�B���y�� 
		int newX ;
		int newY ;
		
		
		// �Y��pos�O�ؼ�G�A�^��true����j 
		if ( maze[x][y].pos == 'G' ) {
			return true ;
	 	} // if ( maze[x][y].pos == 'G' )

		// �Y��pos�OE�Y�O�i�H�������|�A�NE�אּV(visited) 
		if( maze[x][y].pos == 'E' ) {
			maze[x][y].pos = 'V' ;
			
		} // if( maze[x][y].pos == 'E' )
		
		// �w��{�b�y�Ъ��k�U���W�i���ˬd�A�Y��E�άOG�Y�̲{�b�ѹ����ʤ�V�e���Ӯy�� 
		for( int i = 0 ; i < 4 ; i = i + 1 ) {
			newX = x + dx[mouseDirection] ;
			newY = y + dy[mouseDirection] ;
			
			if ( maze[newX][newY].pos == 'E' || maze[newX][newY].pos == 'G' ) {
				if( findAGoal( newX, newY ) )
					return true ;		
			} // if ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' )
			
			changeDirection() ; // ���ܦѹ���V  

		} // for i
		
		// �Y�k�U���W�|�Ӥ�쪺�e�賣�O�����Φh�l�����Y�^��false�A�åHVFalsereturned���� 
		maze[x][y].VFalsereturned = true ;
		return false ;
 
	} // findAGoal ()
	
	
	// �b�������ƶq��G�H��A���@��R���|�A�Ϩ䤣���즺���Φh�l���� 
	bool findRoute ( int x, int y, int NumOfGoal ) {
		
		// dx,dy ���ѹ������ʤ�V 
		int dx[10] = { 0, 1, 0, -1 } ;
		int dy[10] = { 1, 0, -1, 0 } ;
		// newX,newY ���ѹ��U�@�B���y�� 
		int newX ;
		int newY ;
		
		// �Y���y�ЬOG�B�S���Q���L�A��XR���|�A�N���y�г]�m�����L�ðO��G���Ӽ� 
		if ( maze[x][y].pos == 'G' && maze[x][y].GisPassed == false ) {
			maze[x][y].GisPassed = true ;
			SetRoute() ;
			addG() ;
	 	} // if ( maze[x][y].pos == 'G' && maze[x][y].isPassed == false )
	 	
	 	// �ˬd�ثe���G���ƶq�O�_�w�g���� 
		if ( getcountG() == NumOfGoal )
			return true ;
		
		// �Y���y�Ь�E(�i�������|)�A�Хܬ�V(visited) 
		if( maze[x][y].pos == 'E' ) {
			maze[x][y].pos = 'V' ;
		} // if( maze[x][y].pos == 'E' )
		
		
		// �w��{�b�y�Ъ��k�U���W�i���ˬd�A�Y��E�άOG�Y�̲{�b�ѹ����ʤ�V�e���Ӯy�� 
		for( int i = 0 ; i < 4 ; i = i + 1 ) {
			newX = x + dx[mouseDirection] ;
			newY = y + dy[mouseDirection] ;
			
			if ( maze[newX][newY].pos == 'E' || maze[newX][newY].pos == 'G' ) {
				if( findRoute( newX, newY, NumOfGoal ) )
					return true ;		
			} // if ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' )
			
			changeDirection() ; // ���ܦѹ���V 

			
		} // for i
		
		
		// �Y�k�U���W�|�Ӥ�쪺�e�賣�O�����Φh�l�����Y�^��false�A�åHVFalsereturned���� 
		maze[x][y].VFalsereturned = true ;
		return false ;
 
	} // findRoute ()
	
	// �b�M��h�ӥؼ�G�����p�U�A��X�@�����|���ѹ��i�H���h��G 
	bool findGoals ( int x, int y, int NumOfGoal ) {
		
		// dx,dy ���ѹ������ʤ�V 
		int dx[10] = { 0, 1, 0, -1 } ;
		int dy[10] = { 1, 0, -1, 0 } ;
		// newX,newY ���ѹ��U�@�B���y�� 
		int newX ;
		int newY ;
		
		// �Y���y�ЬOG�B�S���Q���L�A�N���y�г]�m�����L�ðO��G���Ӽ� 
		if ( maze[x][y].pos == 'G' && maze[x][y].GisPassed == false ) {
			maze[x][y].GisPassed = true ;
			addG() ;
	 	} // if ( maze[x][y].pos == 'G' && maze[x][y].isPassed == false )
	 	
	 	// �ˬd�ثe���G���ƶq�O�_�w�g���� 
		if ( getcountG() == NumOfGoal )
			return true ;
			
		// �Y���y�Ь�E(�i�������|)�A�Хܬ�V(visited) 
		if( maze[x][y].pos == 'E' ) {
			maze[x][y].pos = 'V' ;
			
		} // if( maze[x][y].pos == 'E' )
		
		// �w��{�b�y�Ъ��k�U���W�i���ˬd�A�Y��E�άOG�Y�̲{�b�ѹ����ʤ�V�e���Ӯy�� 
		for( int i = 0 ; i < 4 ; i = i + 1 ) {
			newX = x + dx[mouseDirection] ;
			newY = y + dy[mouseDirection] ;
			
			if ( maze[newX][newY].pos == 'E' || maze[newX][newY].pos == 'G' ) {
				if( findGoals( newX, newY, NumOfGoal ) )
					return true ;		
			} // if ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' )
			
			changeDirection() ; // ���ܦѹ���V 

			
		} // for i
		
		// �Y�k�U���W�|�Ӥ�쪺�e�賣�O�����Φh�l�����Y�^��false
		return false ;
 
	} // findGoals ()
	
	
	// �HVFalsereturned�P�_�ó]�m���������Φh�l���������|R 
	void SetRoute() {
		
		
		for( int i = 0 ; i < row ; i++ ) {
			for( int j = 0 ; j < col ; j++ ) {
				
				// �Y���y�ЬOV�B���O�����Φh�l�����A�Y�]�m�����|R 
				if ( maze[i][j].pos == 'V' && maze[i][j].VFalsereturned == false ) {
					 maze[i][j].pos = 'R' ;
				} // if ( maze[i][j].pos == 'V' && maze[i][j].VFalsereturned == false )
				
				// �Y���y�ЬOV�B�O�����Φh�l�����A�Y���|���o����(�]�m��E) 
				else if ( maze[i][j].pos == 'V' && maze[i][j].VFalsereturned == true ) {
					maze[i][j].pos = 'E' ;
					
					
				} // else if ( maze[i][j].pos == 'V' && maze[i][j].VFalsereturned == true )
			} // for j
		} // for i
		
	} // SetRoute()
	
	// ��X��ؼ�G���̵u���| 
	bool findShortestPath( int x, int y ) {
		
		// dx,dy ���ѹ������ʤ�V 
		int dx[10] = { 0, 1, 0, -1 } ;
		int dy[10] = { 1, 0, -1, 0 } ;
		
		// newX,newY ���ѹ��U�@�B���y�� 
		int newX ;
		int newY ;
		
		// �O�����L��step�� 
		step = step + 1 ;
		maze[x][y].step = step ;
		
		// �קK���shortest��A�h��h�l��step(�N��step>=shortest�����p) 
		if ( step >= shortest ) {
		    step = step - 1 ;
			return false ;
		} // if ( step > shortest )
		
		
		// �Y���y�Ь�E(�i�������|)�A�Хܬ�V(visited) 
		if( maze[x][y].pos == 'E' ) {
			maze[x][y].pos = 'V' ;	
		} // if( maze[x][y].pos == 'E' )
		


		
		// �Y��pos�O�ؼ�G�AGfounded�]�m�������G�A���ˬd�ثe��step���S���񤧫e��shortest�p�A���hstep���Nshortest 
		if ( maze[x][y].pos == 'G' ) {
			Gfounded = true ;

			if ( shortest > step ) {
				shortest = step ;
				
				// �h�^�W�@�B�t�M��Lshortest 
				step = step - 1 ;
				return false ;
			} // if 


	 	} // if ( maze[x][y].pos == 'G' && shortest == 0 )

		
		// �w��{�b�y�Ъ��k�U���W�i���ˬd�A�Y��E�άOG�Y�̲{�b�ѹ����ʤ�V�e���Ӯy�� 
		for( int i = 0 ; i < 4 ; i = i + 1 ) {
			newX = x + dx[mouseDirection] ;
			newY = y + dy[mouseDirection] ;
			
			if ( maze[newX][newY].pos == 'E' || maze[newX][newY].pos == 'G' ) {
				findShortestPath( newX, newY ) ;

			} // if ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' )
			
			// �Y�OV�����ˬd�ثe���L�����|�O�_��u�A�_�h�L�����e 
			else if ( maze[newX][newY].pos == 'V' ) {
				if ( (step + 1) < maze[newX][newY].step && ( (step + 1) < shortest ) ) {
					maze[newX][newY].pos = 'E' ;
					findShortestPath( newX, newY ) ;
				} // if ( (step + 1) < maze[newX][newY].step )
			} // else if ( maze[newX][newY].pos == 'V' )
			
			changeDirection() ; // ���ܦѹ���V  

		} // for i
		
		// �Y�k�U���W�|�Ӥ�쪺�e�賣��Lshortest path�F�A�N��^�W�@�B�ˬd�W�@�B����L��V 
		step = step - 1 ;
		return false ;
 
	} // findShortestPath()
	
	
	bool SetShortestPath( int x, int y, int path ) {
		
		// path���̵u���|���Z�� 
		
		// dx,dy ���ѹ������ʤ�V 
		int dx[10] = { 0, 1, 0, -1 } ;
		int dy[10] = { 1, 0, -1, 0 } ;
		
		// newX,newY ���ѹ��U�@�B���y�� 
		int newX ;
		int newY ;
		
		// �O�����L��step�� 
		step = step + 1 ;
		maze[x][y].Rsign = true ;
		maze[x][y].step = step ;
		
		
		// �קK���shortest��A�h��h�l��step(�N��step>=shortest�����p�B���椣�|�O�̵u���|) 
		if ( step >= shortest ) {
		    step = step - 1 ;
		    maze[x][y].Rsign = false ;
			return false ;
		} // if ( step > shortest )
		
		
		// �Y���y�Ь�E(�i�������|)�A�Хܬ�V(visited) 
		if( maze[x][y].pos == 'E' ) {
			maze[x][y].pos = 'V' ;	
		} // if( maze[x][y].pos == 'E' )
		

		
		// �Y��pos�O�ؼ�G�AGfounded�]�m�������G�A���ˬd�ثe��step���S���񤧫e��shortest�p�A���hstep���Nshortest 
		if ( maze[x][y].pos == 'G' ) {
			
			if ( shortest > step ) {

				shortest = step ;
				
				// �Ypath����Ĥ@��shortest(�Ĥ@�ӧ�쪺G)�Y�L�X�ӳ̵u���| 
				if ( path == shortest  && Gfounded == false) {
				
					Gfounded = true ;
				
					for( int i = 0 ; i < row ; i++ ) {
						for( int j = 0 ; j < col ; j++ ) {	
							if ( maze[i][j].pos == 'V' && maze[i][j].Rsign == true ) {
								maze[i][j].pos = 'R' ;
							} // if ( maze[i][j].pos == 'V' && maze[i][j].Rsign == true )
							else if ( maze[i][j].pos == 'V' && maze[i][j].Rsign == false ) {
								maze[i][j].pos = 'E' ;
							} // else if ( maze[i][j].pos == 'V' && maze[i][j].Rsign == false )
						} // for j
					} // for i
					show() ;
					cout << endl ;
				} // if ( path == shortest  && Gfounded == false) 

				// �h�^�W�@�B�t�M��Lshortest 
				step = step - 1 ;
				maze[x][y].Rsign = false ;
				return false ;
			} // if 
			
			else {
				// �Ypath����Ĥ@��shortest(�Ĥ@�ӧ�쪺G)�Y�L�X�ӳ̵u���| 
				if ( path == shortest  && Gfounded == false) {
				
					Gfounded = true ;
				
					for( int i = 0 ; i < row ; i++ ) {
						for( int j = 0 ; j < col ; j++ ) {	
							if ( maze[i][j].pos == 'V' && maze[i][j].Rsign == true ) {
								maze[i][j].pos = 'R' ;
							} // if ( maze[i][j].pos == 'V' && maze[i][j].Rsign == true )
							else if ( maze[i][j].pos == 'V' && maze[i][j].Rsign == false ) {
								maze[i][j].pos = 'E' ;
							} // else if ( maze[i][j].pos == 'V' && maze[i][j].Rsign == false )
						} // for j
					} // for i
					show() ;
					cout << endl ;
				} // if ( path == shortest  && Gfounded == false) 
				
			}  // else


	 	} // if ( maze[x][y].pos == 'G' )

		
		// �w��{�b�y�Ъ��k�U���W�i���ˬd�A�Y��E�άOG�Y�̲{�b�ѹ����ʤ�V�e���Ӯy�� 
		for( int i = 0 ; i < 4 ; i = i + 1 ) {
			newX = x + dx[mouseDirection] ;
			newY = y + dy[mouseDirection] ;
			
			if ( maze[newX][newY].pos == 'E' || maze[newX][newY].pos == 'G' ) {
				SetShortestPath( newX, newY, path ) ;

							
			} // if ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' )
			
			
			// �Y�OV�����ˬd�ثe���L�����|�O�_��u�A�_�h�L�����e
			else if ( maze[newX][newY].pos == 'V' ) {
				if ( (step + 1) < maze[newX][newY].step && ( (step + 1) < shortest ) ) {
					maze[newX][newY].pos = 'E' ;
					SetShortestPath( newX, newY, path ) ;
				} // if ( (step + 1) < maze[newX][newY].step )
			} // else if ( maze[newX][newY].pos == 'V' )
			
			changeDirection() ; // ���ܦѹ���V  

		} // for i
		
		// �Y�k�U���W�|�Ӥ�쪺�e�賣��Lshortest path�F�A�N��^�W�@�B�ˬd�W�@�B����L��V 
		step = step - 1 ;
		maze[x][y].Rsign = false ;
		return false ;
 
	} // SetShortestPath()
private:

	int row = 0, col = 0 ; // �g�c�j�p( row * col ) 
	Block maze[100][100] ; // �g�c��T 
	int countG = 0 ; // �����ثeG���ƶq
	 
	//�ѹ����ʤ�V 0�N��k�A1�N��U�A2�N���A3�N��W( default = 0 ) 
	int mouseDirection = 0 ; // �ثe�ѹ�����V 
	int shortest = 999999999 ;
	int step = 0 ;
	bool Gfounded = false ; // ��ܦ��S�����G 
};

int main(void){
	int command = 1 ; // ���O ( default = 1 )
	
	
	do{

	int startX = 0, startY = 0 ; // �_�l�I( 0 , 0 ) 
    int NumOfGoal = 1 ; // �n�䪺�ؼ�G�ƶq( default = 1 ) 
	string fileName ; // �nŪ���ɮצW�� 
    Maze aMaze ; // �g�c 
    aMaze.resetAll() ; // ��l�ưg�c 

	// ���ϥΪ̫��O����T�H�μ��D 
	cout << endl << "*** Path Finding ***" ;
	cout << endl << "* 0. Quit          *" ;
	cout << endl << "* 1. One goal      *" ;
	cout << endl << "* 2. More goals    *" ;
	cout << endl << "* 3. Shortest path *" ;
	cout << endl << "********************" ;
	cout << endl << "Input a command(0, 1, 2, 3): " ;
	
	cin >> command ; // get command
	
	// �T�{��J�����O�O�_�� ( 0,1,2 ) �_�h���s��J 
	while ( command < 0 || command > 3 ) {
		cout << endl ;
		cout << "Command does not exsist!" << endl ;
		cout << endl << "*** Path Finding ***" ;
		cout << endl << "* 0. Quit          *" ;
		cout << endl << "* 1. One goal      *" ;
		cout << endl << "* 2. More goals    *" ;
		cout << endl << "* 3. Shortest path *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2, 3): " ;
		cin >> command ;
	} // while ( command < 0 || command > 2 )
	

	// command = 1 �� 2 ������ 
    if ( (command == 1) || ( command == 2) || ( command == 3 ) ) {
    	
    	// �޾ɨϥΪ̿�J�nŪ�J���ɮצW�� 
    	cout << endl ;
    	cout << "Input a file number (e.g.,201,202,...): " ;
		cin >> fileName ;

			
		// Ū�J�g�c 
    	if ( aMaze.load( fileName ) ) {
			
			bool success = false ;

			Maze vMaze(aMaze) ; // vMaze�ΨӦL�X�ѹ�Visted�����| 

			// ���h��G���B�z 
			if ( command == 2 ) {
				
				// �޾ɨϥΪ̿�JG����T 
				cout << "Number of G (goals): " ;
				cin >> NumOfGoal ;
				while ( NumOfGoal < 1 || NumOfGoal > 100 ) {
					cout << endl ;
					cout << "### The number must be in [1,100] ###" << endl ;
					cout << endl ;
					cout << "Number of G (goals): " ;
					cin >> NumOfGoal ;
    	   	 	} // while ( mode >= 1 && mode <= 100 )
    	   	 	
    	   	 	
    	   	 	success = vMaze.findGoals( startX, startY, NumOfGoal ) ; // ��X�������ؼ�G�ƶq�����| 
				vMaze.show() ; // ��ܰg�c�ثe���� 
				cout << endl ;
				 
				// �Y���\�����|R�A��ܨí��]�g�c 
    	   	 	if ( success ) {
    	   	 		aMaze.findRoute( startX, startY, NumOfGoal ) ;
    	   	 		aMaze.show() ;
				} // if ( success )
    	   	 	
    	   	 	vMaze.resetAll() ;
    	   	 	aMaze.resetAll() ;
    	   	 	
			} // if ( command == 2 )

			// �u���@��G���B�z 
			else if( command == 1 ) {
				
				
				success = aMaze.findAGoal( startX, startY ) ; // ��XG
				
				// �Y���\��XG�A��ܨ�ѹ����L�����|V�A�H�ΨS�������Φh�l������R 
				if ( success ) {
					aMaze.show() ;
					cout << endl ;
				
					aMaze.SetRoute() ;
			
					aMaze.show() ;
					aMaze.resetAll() ;
				} // if ( success )
				
				// �Y�S����XG�A��ܨ�ѹ����L�����|V 
				else{
					aMaze.show() ;
					aMaze.resetAll() ;
				} // else
				
			} // else if ( command == 1 )
			
			// ��XG�̵u���|���B�z 
			else if ( command == 3 ) {

				// ��X�̵u���|���B�ơA�æL�X���| 
				aMaze.findShortestPath( startX, startY ) ;
				aMaze.show() ;
				cout << endl ;
				
				// �Y�����G(��ܦܤ֦��@���̵u���|)�A�Y�L�X��쪺�Ĥ@���̵u���| 
				if ( aMaze.getGfounded() ){
					vMaze.SetShortestPath( startX, startY, aMaze.getShortest() ) ;
					cout << endl ;
					cout << "Shortest path length = " << aMaze.getShortest() << endl ;
				} // if ( aMaze.getGfounded() )
				
				aMaze.resetAll() ;
				vMaze.resetAll() ;
			} // else if ( command == 3 ) 
			
		} // if ( aMaze.load( fileName ) )

	} // if ( (command == 1) || ( command == 2) || ( command == 3 ) )
	
	// command = 0 �h�X	    
	else if ( !command )
		break ;
	// ���O���~ 
	else
		cout << endl << "Command does not exsist!" << endl ;
		
	} while ( true ) ;

	system("pause") ;
	return 0 ;
	

} // main()
