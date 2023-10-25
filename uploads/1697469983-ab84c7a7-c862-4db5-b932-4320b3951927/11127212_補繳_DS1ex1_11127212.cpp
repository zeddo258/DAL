// 11127212 ���դ�
# include <iostream>
# include <vector>
# include <string.h>
# include <fstream>
# include <sstream>
# include <stdlib.h>


using namespace std;

enum Modes {
	oneG, moreG         // ��ؼҦ� ;
};

class Maze {
private :
	int Gpoint = 0 ;			// ���X��G�I 
	int length = 0, width = 0 ; // length and width of maze
	char maze[100][100] ; 		// the maze
	int gxpoint[50], gypoint[50] ;  // ������G���I 
	int Gnum = 0 ;              // ���X��G�I 
public :
	char getmaze( int i, int j ) { // �o��g�c�C�Ӧ�m���� 
		return maze[i][j] ;
	} // getmaze
	void setmaze( char A, int x, int y ) { // �]�w�g�c���� 
		maze[x][y] = A ;
	} // setmaze
	void clr() {

		for ( int i = 0 ; i < width ; i ++ ) {	// �M�Űg�c���Ҧ��� 
			for ( int j = 0 ; j < length ; j ++ ) {
				maze[i][j] = '/0' ;
			} // for
		} // for
	} // clr
	void show() {
		for ( int i = 0 ; i < width ; i ++ ) {	// ��ܰg�c 
			cout << endl ;
			for ( int j = 0 ; j < length ; j ++ ) {
				cout << maze[i][j] ;
			} // for
		} // for
	} // showmaze

	bool load ( char filenum[50], Modes mode ) {
		string numline1, mazeline ;				// 
		char filename[50] = "input" ;
		int point ;
		strcat( filename, filenum ) ;
		strcat( filename, ".txt") ;
		ifstream file(filename) ;	// open the file
		if ( ! file.is_open()) {     // if the file can open
			cout << "Unable to open file : " << filename << endl ;
			return false ;
		} // if

		if ( mode == oneG ) Gpoint = 1 ;
		if ( mode == moreG ) {
			cout << endl << "Input how many \"G\" : " ;
			cin >> Gpoint ;
		} // if

		getline(file, numline1) ;  // ���o�Ĥ@����

		LineNumber( numline1 ) ; // ��Ĥ@�����ഫ���g�c�����M�e

		for ( int i = 0 ; i < width ; i ++ ) {	//�@��@���g�c����_��
			getline(file, mazeline) ;
			for ( int j = 0 ; j < length ; j ++ ) {
				maze[i][j] = mazeline[j] ;
			} // for
		} // for


	} // load

	void LineNumber( string line1 ) { // ��Ĥ@�����ഫ���g�c�����M�e

		char getnum ;							// Ū���r�ꤺ�e
		char snum1[5] = "\0", snum2[5] = "\0" ;	// �r�ꫬ�A���Ʀr
		int place = 0 ;			        // line1 �����
		for ( ; line1[place] != ' ' ; place ++ ){	// ��Ĥ@�ӼƦr���X��
			snum1[place] = line1[place] ;			
		} // for

		place ++ ;					// ���L�Ů�
		int snum2p = 0 ;						// �ĤG�Ӿ�ƪ����
		while ( place < line1.size() ) {			// ��ĤG�ӼƦr���X��
			snum2[snum2p] = line1[place] ;
			snum2p ++ ;
			place ++ ;
		} // while


		length = atoi(snum1) ;   				// �N�����Ʀr�r���ഫ�����
		width = atoi(snum2) ;					// �N�e���Ʀr�r���ഫ����� 

	} // LineNumber

	bool findGoals( Maze & vmaze ) {			// �M��ؼ� 
		Maze dead_way(vmaze);					// �������� 
		Maze G_way(vmaze) ;						// �˰h���ɭԭn�O���������|���| 
		return findway( vmaze, dead_way,G_way ,0, 0, 0 ) ; // �I�s���g�c����� 
	} // findGoals

	bool findway( Maze & vmaze,Maze & dead_way,Maze & G_way, int dir, int x, int y ) {	// �M��U�@�B 
		bool isG ;	// �O���q���Ӥ�V�� 
		int from = (dir+2)%4 ;							// �P�_����O�_��G�I 
		vmaze.setmaze( 'V', x, y ) ;			// �b���L���I�d�UV (vmaze) 
		maze[x][y] = 'R' ;						// �b���L���I�d�UR (amaze) 

		/*G_way.show() ;
		cout << endl ;*/

		dir = next( vmaze, dead_way, dir, x, y, 0, isG ) ;  // ��X�U�@�B�n������� 
		if ( isG == 1 ) {									// �P�_�O�_�J��G 
			Gpoint -- ;										// �p�G�J��G�A�ݭn�J�쪺G�N��1 
			int ax = x, ay = y ;							// �}�l�O��G�I����m 
			nextway(dir,ax,ay) ;
			gxpoint[Gnum] = ax ;
			gypoint[Gnum] = ay ;
			Gnum ++ ;
			if ( Gpoint == 0 ) { reG( vmaze ); dead_way.clr() ; G_way.clr(); return true; } ; // �p�G�J��Gpoint = 0��ܤw�g�������{�A�N�����o�Ө禡
	 
		}
		if ( dir == 0 ) return findway( vmaze,dead_way, G_way ,dir, x, y+1 ) ;		// �V�k����U�@�� 
		else if ( dir == 1 ) return findway( vmaze,dead_way,G_way, dir, x+1, y ) ;	// �V�U����U�@�� 
		else if ( dir == 2 ) return findway( vmaze,dead_way, G_way, dir, x, y-1 ) ;	// �V������U�@�� 
		else if ( dir == 3 ) return findway( vmaze,dead_way,G_way, dir, x-1, y ) ;	// �V�W����U�@�� 

		else if ( dir == -1 ) {														// �S�������A�ݭn�˰h 
			backway( vmaze, dead_way,G_way, dir,from, x, y, false ) ;					// �˰h 
			if ( dir == -2 ) { dead_way.clr(); G_way.clr() ; return false ; }					// �h��_�I�A��ܨS�����A�^��false 
			else return findway( vmaze,dead_way,G_way, dir, x, y ) ;				// ����L���|�A�b�I�s�@��findway 
		}

	} // findway
	
	void nextway( int dir, int & x, int & y ) {			// ��X�U�@�B���y��							
		if ( dir == 0 ) y++ ; 
		else if ( dir == 1 ) x++ ;
		else if ( dir == 2 ) y-- ;
		else if ( dir == 3 ) x-- ;
	} // nextway
	


	void backway( Maze & vmaze, Maze & dead_way, Maze & G_way, int & dir,int from, int & x, int & y, bool groute ) { // �˰h 

		//dead_way.show() ; cout << endl ;
		bool isG ;													// �O�_���g�LG 
		int ax=x,ay=y ;
		if ( x == 0 && y == 0 ) {									// �P�_�O�_���^�_�I�F 
			cout << "���s�b���|" ;
			reG(vmaze) ;											// �]��G�b�]���|���ɭԷ|V�BR�Q�\���A�ҥH�n�ɦ^�h 
			dir = -2 ;
			return ;
		} // if
			
		
		 

		if (from!=-1) {	
			dead_way.setmaze('D',x,y) ;
			checkRcE(from,G_way,maze,x,y,groute) ;											// �Ĥ@���I�sbackway�u�ݭn�h�^�e�@��N�n 
			nextway(from,x,y) ;
			
			backway(vmaze,dead_way,G_way,dir,-1,x,y,groute) ;
			return ;
		} // if
		//cout << "223" ;
		dir = next( vmaze, dead_way, 0, x, y, 0, isG ) ;	// �M��O�_�٦������L����
		if ( dir != -1 )  return ; 									// ����L���|�N�i�Hreturn�F 
		dead_way.setmaze('D',x,y) ;						// �bdead_way�����o���������� 

		if ( y+1 < length && maze[x][y+1]== 'R' && dead_way.getmaze(x,y+1) != 'D'  ) // �H�U�ʧ@���h�^�e�@�� 
		{  checkRcE(0,G_way,maze,x,y,groute) ;y ++ ; backway( vmaze, dead_way, G_way , dir,from, x, y, groute ) ; }
		else if ( x+1 < width && maze[x+1][y] == 'R' && dead_way.getmaze(x+1,y) != 'D' ) 
		{  checkRcE(1,G_way,maze,x,y,groute) ;x ++ ; backway( vmaze, dead_way, G_way, dir,from, x, y, groute ) ; }
		else if ( y-1 >= 0 && maze[x][y-1] == 'R' && dead_way.getmaze(x,y-1) != 'D') 
		{ checkRcE(2,G_way,maze,x,y,groute) ;y -- ; backway( vmaze, dead_way, G_way, dir,from, x, y, groute ) ; }
		else if ( x-1 >= 0 && maze[x-1][y] == 'R' && dead_way.getmaze(x-1,y) != 'D') 
		{ checkRcE(3,G_way,maze,x,y,groute) ;x -- ; backway( vmaze, dead_way, G_way, dir,from ,x, y, groute ) ; }

	} // backway
	
	void checkRcE(int dir,Maze G_way,char maze[100][100],int x,int y,bool & groute ) {    	// �P�_�O�_�n��R�ഫ��E 
		if (groute) {G_way.setmaze('G',x,y) ; return ; }									// �P�_�˰h�ɬO�_�|�g�L�|��G�����| 
		if(haveG(dir,G_way,x,y) ) {groute = true ; G_way.setmaze('G',x,y) ; return ; }		// �P�_�����|�O�_�|����FG�����| 
		if ( maze[x][y] == 'R' ) maze[x][y] = 'E' ;		// �h�^�ɱNmaze��R�令E 
	}  // checkRcE
	
	bool haveG( int dir, Maze G_way, int x, int y ) {			// �ˬd�˰h���ɭԦ����|�O�_�]�O��G�����| 
		dir ++ ;			
						 									
		for( int i = 1; i <= 3 ; i ++, dir ++ ) {// �P�_�|�Ӥ��O�_��G
			dir %= 4 ;						 
			int xx = x, yy = y ;
			nextway(dir,xx,yy) ;
			if ( ( xx < width && xx > 0 && yy < length && yy > 0 ) && G_way.getmaze(xx,yy) == 'G') return true ; 
		} // for
		
		return false ;
	} // howmanyR

	int next( Maze vmaze, Maze dead_way, int dir, int x, int y, int time, bool & isG ) { // �P�_�U�@��n�����䨫�A�άO�S���F 

		for ( int i = 0 ; i < 4 ; i ++ ) {					
			dir%=4 ;
			if ( ( y+1 < length && dir == 0 ) && dead_way.getmaze(x,y+1) != 'D' && ( vmaze.getmaze(x,y+1) == 'E' || vmaze.getmaze(x,y+1) == 'G' ) )
				{isG = IsG(vmaze.getmaze(x,y+1)) ;return dir ;}
			else if ( ( x+1 < width && dir == 1 ) && dead_way.getmaze(x+1,y) != 'D' && ( vmaze.getmaze(x+1,y) ==  'E' || vmaze.getmaze(x+1,y) == 'G' ) )
				{isG = IsG(vmaze.getmaze(x+1,y)) ;return dir ;}
			else if ( ( y-1 >= 0 && dir == 2 ) && dead_way.getmaze(x,y-1) != 'D' && ( vmaze.getmaze(x,y-1) ==  'E' || vmaze.getmaze(x,y-1) == 'G' ) )
				{isG = IsG(vmaze.getmaze(x,y-1)) ;return dir ;}
			else if ( ( x-1 >= 0 && dir == 3 ) && dead_way.getmaze(x-1,y) != 'D' && ( vmaze.getmaze(x-1,y) ==  'E' || vmaze.getmaze(x-1,y) == 'G' ) )
				{isG = IsG(vmaze.getmaze(x-1,y)) ;return dir ;}
			else dir++ ;										// ������V 
		}
	
		return -1 ;// �p�G�|�Ӥ�쳣�M��L�A��ܨS�� 
	
	} // haveway

	bool IsG ( char G ) {								// �P�_�O�_��G 
		if ( G == 'G' ) return 1 ;
		else return 0 ;
	} // isG

	void reG( Maze & vmaze ) {				// �]��G�b�]���|���ɭԷ|V�BR�Q�\���A�ҥH�n�ɦ^�h
		if( Gnum >= 1 ) {
			for ( int i = 0 ; i < Gnum ; i ++ ) {
				maze[gxpoint[i]][gypoint[i]] = 'G' ;
				vmaze.setmaze('G',gxpoint[i],gypoint[i]) ;
			} // for
		}
	} // reG



};




int main(void) {
	int command = 0 ;     // user command
	do {
		Maze aMaze ;        // a matrix
		char fileName[50] ;   // a file name
		Modes mode = oneG ; // default: one goal

		cout << endl << "*** Path Finding ***" ;
		cout << endl << "*0. Quit           *" ;
		cout << endl << "*1. One Goal       *" ;
		cout << endl << "*2. More goals     *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2) :" ;
		cin >> command ;       // get the command
		if ((command == 1) || (command == 2)) {
			if ( command == 2 )
				mode = moreG ; // one or more goals


			cout << endl << "Input a file number (e.g.,201, 202, ...) :" ;
			cin >> fileName ;
			if ( aMaze.load(fileName, mode))   	// load the orignal matrix
			{	Maze vMaze(aMaze) ;   			// a copy to keep the visited cells
				bool success = aMaze.findGoals(vMaze) ; // find a path to goal(s)

				mode = oneG	;					// reset to default
				vMaze.show() ;					// Show on screen the visited cells
				cout << endl ;
				if ( success )					// to check if the goal is reached or not
					aMaze.show() ;				// show on screen the route to reached the goal
				vMaze.clr() ;					// clear up the copy

			} // end inner-if

			aMaze.clr() ;						// clear up the orignal matrix
		} // end outer-if
		else if (command==0)						// '0' : stop the program
			break ;
		else
			cout << endl << "Command does not exist!" << endl ;
	} while (true) ;
	system("pause") ;

						// pause the execution
	return 0 ;


} // end of main
