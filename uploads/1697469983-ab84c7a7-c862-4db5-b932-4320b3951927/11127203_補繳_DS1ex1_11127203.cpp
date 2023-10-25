// 11127203 ���O�p 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std ;

enum Modes {
    oneG = 1,   // command == 1�A��@��G 
    moreG = 2,   // command == 2�A��h��G 
} ;


class Maze {
private:
    int ROWS, COLS ; // x�Ay�� 
    vector< vector<char> > maze ; //�g�c�x�} 
    int dx[4] = {0, 1, 0, -1} ; // x �b��V�W�|�ӥi�઺���ʨB�J�G0 ��ܤ����ʡA1 ��ܦV�k���ʡA-1 ��ܦV�����ʡC 
	int dy[4] = {1, 0, -1, 0} ; // y �b��V�W�|�ӥi�઺���ʨB�J�G0 ��ܤ����ʡA1 ��ܦV�U���ʡA-1 ��ܦV�W���ʡC

public:
    Maze( int rows, int cols ) : ROWS( rows ), COLS( cols ), maze( rows, vector<char>( cols ) ) {} // C++�غc�禡���w�q�A�Ψӫإߤ@�ӦW��Maze�����O������C��������ӰѼơGrows�Mcols�A�Ω���w�g�c����ƩM�C�ơC
    bool load( string fileNumber ) {
    	string fileName = "input" + fileNumber + ".txt" ; // �NfileNumber�אּstring�˦�"input + fileNumber + .txt" 
		const char* charFileName = fileName.c_str() ; // �N fileName ���x�s�� C++ �r���ഫ�� C�r�� 
			                                             // �A�]��ifstream�u���� C�r��@���ɮצW�ٰѼơC 
        ifstream inputFile( charFileName ) ; // ���}txt

        if ( !inputFile.is_open() ) { // �p�G�����}txt�� 
            cout << "\n" << fileName << " does not exist!" << endl;  //��X��r 
            return false ; // ��^false 
        } // if ( !inputFile.is_open() )

        inputFile >> COLS >> ROWS ; // Ū�J��P�C 
        
        maze.resize( ROWS, vector<char>( COLS ) ) ; // ���s�w�q�g�c�j�p�A������~�I�I�I�I 

        for ( int i = 0; i < ROWS; i++ ) {  // Ū�i�檺�}�C���e
            string line ;
            inputFile >> line ; // Ū�i�}�C���e
            for ( int j = 0; j < COLS; j++ ) { // Ū�i�C���}�C���e
                maze[i][j] = line[j] ; // ��r����i�}�C
            } // for ( int j = 0; j < COLS; j++ )
        } // for ( int i = 0; i < ROWS; i++ )
        
       	//�qtxt��Ū�i�g�c��ƨ��x�s�b�x�} 

        inputFile.close() ;  // �������

        return true ; // ��Ū�Jtxt�ɡA��^true 
    } // load( string fileName)

	void showV() {
    		// �L�X�g�c���e
    		for ( int i = 0; i < ROWS; i++ ) { 
        		for ( int j = 0; j < COLS; j++ ) {
            		cout << maze[i][j] ;
        		} // for (int j = 0; j < COLS; j++)
        		cout << endl ;
    		} // for (int i = 0; i < ROWS; i++)
	} // showV() �L�X�M�����|V
	
	void showR() { 
    	for ( int i = 0; i < ROWS; i++ ) {
        	for ( int j = 0; j < COLS; j++ ) {
            	if ( maze[i][j] == 'V' ) {
                	cout << 'E' ;
            	} // if ( maze[i][j] == 'V' ) �p�G��V�N��^E 
				else {
                cout << maze[i][j];
            	} // else ��X�줺�e 
            	
        	} // for (int j = 0; j < COLS; j++)
        	cout << endl ; // ���� 
   		} // for (int i = 0; i < ROWS; i++)
	} // showR() // �L�X�������|R 

	bool isValid( int x, int y ) {
    	return x >= 0 && x < ROWS && y >= 0 && y < COLS ;  
	} // �ˬd�O�_����� 


    bool findRPath( int x, int y, int dir ) {
        if ( maze[x][y] == 'G' ) {
            return true ; // ���X�f
        } // if ( maze[x][y] == 'G' )
        
        else if ( maze[x][y] == 'E' ) {
        	maze[x][y] = 'V' ;  //�аOV 
		} // else if ( maze[x][y] == 'E' )

    	int newX = x + dx[dir] ;  // ��e�y�� (x, y) �}�l�A�b������V�W�]���V�^���ʪ��s�y�� newX  
    	int newY = y + dy[dir] ; // ��e�y�� (x, y) �}�l�A�b������V�W�]�C��V�^���ʪ��s�y�� newY 

        if ( isValid( newX, newY ) == true && ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' ) ) { // ���j�M����|
            if ( findRPath( newX, newY, dir ) == true ) { // �ˬd�b�s���y�� (newX, newY) �W�O�_���@�����Ī����|
            	maze[x][y] = 'R' ; // �p�G���A�N��e��m (x, y) �аO�� 'R' 
                return true ; // ��^ true ��ܧ��F���|
            } // if ( findRPath( newX, newY ) == true )
			else {
				if ( dir == 3 ) // �p�G��V���W�A���s�ܦ^�k 
				    dir = -1 ; //���s�]�w�� 
        		bool findR = findRPath( x, y, dir+1 ) ; // ��e�y�� (x, y) �W�A���զb�U�@�Ӥ�V dir+1 �W�~��j�M���|
        		if ( findR == true ) { 
        			maze[x][y] = 'R' ; //�p�G�b�s��V�W���F���|�A�N�аO�ثe��m�� 'R'
        			return true ; // �^��true 
				} // if ( findR == true )
        	
			} // else
			
    	} // if ( isValid( newX, newY ) == true && ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' )
		else { // �p�G�I���ê�� 'O'�A�h���է��ܤ�V
        	for ( int newDir = 0; newDir < 4; ++newDir ) {
            	int nextX = x + dx[dir] ; // ��e�y�� (x, y) �}�l�A�b������V�W�]���V�^���ʪ��s�y�� newX  
            	int nextY = y + dy[dir] ; // ��e�y�� (x, y) �}�l�A�b������V�W�]�C��V�^���ʪ��s�y�� newY 

            	if  ( isValid( nextX, nextY ) && ( maze[nextX][nextY] == 'E'  || maze[nextX][nextY] == 'G' ) ) { // ���j�M����| 
					if ( maze[nextX][nextY] == 'G' ) // �ˬd�b�s���y�� (newX, newY) �W�O�_����'G' 
					    return true ;

                	if ( findRPath( x, y, dir ) ) { // ���ܤ�V�ôM����|
                    	return true;
                	} // if ( findRPath( x, y, dir ) )
                	
            	} // if ( isValid( nextX, nextY ) && maze[nextX][nextY] == 'E' )
            	
            	else { 
            		if ( dir == 3 ) { // �p�G�w��W�A���ܤ�V���k 
            			dir = 0 ;
					} // if ( dir == 3 )
					else{
						dir++ ;  // �k�B�W�B���B�U 
					} // else
					
				} // else
				
        	} // for ( int newDir = 0; newDir < 4; ++newDir ) 
        	
    	} // else

    return false; // �S�������|
	} // bool findRPath( int x, int y, int dir )


    bool findVPath( int x, int y, int dir ) { // ��M��V���| 
        if ( maze[x][y] == 'G' ) {
            return true ; // ���X�f
        } // if ( maze[x][y] == 'G' )
        
        else if ( maze[x][y] == 'E' ) {
        	maze[x][y] = 'V' ; //�аOV 
		} // else if ( maze[x][y] == 'E' )

    	int newX = x + dx[dir] ; // ��e�y�� (x, y) �}�l�A�b������V�W�]���V�^���ʪ��s�y�� newX  
    	int newY = y + dy[dir] ; // ��e�y�� (x, y) �}�l�A�b������V�W�]�C��V�^���ʪ��s�y�� newY 

        if ( isValid( newX, newY ) == true && ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' ) ) { // ���j�M����|
			maze[x][y] = 'V' ; // �аO��e��m�� 'V'�A��ܤw�g���L
			
            if ( findVPath(newX, newY, dir) == true ) { // ���j�M����|
                return true;
            } // if ( findVPath( newX, newY ) == true )
			else {
				if ( dir == 3 ) // �p�G��V���W�A���s�ܦ^�k 
				    dir = -1 ; //���s�]�w�� 
        		bool findV = findVPath( x, y, dir+1 ) ; // ��e�y�� (x, y) �W�A���զb�U�@�Ӥ�V dir+1 �W�~��j�M���|
        		if ( findV == true ) {
        			return true ;  // �^��true 
				} // if ( findV == true )
        	
			} // else
    	} // if ( isValid( newX, newY ) == true && ( maze[newX][newY] == 'E' || maze[newX][newY] == 'G' )
		else { // �p�G�I���ê�� 'O'�A�h���է��ܤ�V
        	for ( int newDir = 0; newDir < 4; ++newDir ) {
            	int nextX = x + dx[dir] ; // ��e�y�� (x, y) �}�l�A�b������V�W�]���V�^���ʪ��s�y�� newX  
            	int nextY = y + dy[dir] ; // ��e�y�� (x, y) �}�l�A�b������V�W�]�C��V�^���ʪ��s�y�� newY
            	//cout << "maze:" << maze[nextX][nextY] << endl ;

            	if ( isValid( nextX, nextY ) && ( maze[nextX][nextY] == 'E' || maze[nextX][nextY] == 'G' )  ) { 
					maze[x][y] = 'V' ; // �аO��e��m�� 'V'�A��ܤw�g���L
					if ( maze[nextX][nextY] == 'G' )  // �ˬd�b�s���y�� (newX, newY) �W�O�_����'G'
					    return true ;

                	// ���ܤ�V�ôM����|
                	if (findVPath(x, y, dir)) { // ���ܤ�V�ôM����|
                    	return true ;
                	} // if ( findPath( x, y, dir ) )
                	
            	} // if ( isValid( nextX, nextY ) && maze[nextX][nextY] == 'E' )
            	
            	else {
            		if ( dir == 3 ) { // �p�G�w��W�A���ܤ�V���k
            			dir = 0 ;
					} // if ( dir == 3 )
					else {
						dir++ ;  // �k�B�W�B���B�U 
					} // else
				}
        	} // for ( int newDir = 0; newDir < 4; ++newDir ) {
    	} // else 

    return false ; // �S�������|
	} // bool findVPath( int x, int y, int dir )

}; // class Maze() 

int main() {
	char command ; // ���O 
	do {
		Maze aMaze( 0,0 ) ; //�]�m��l�g�c�j
		string fileName ; // txt�Ʀr 
		Modes mode = oneG ; //�Ҧ��@�A��@��G 

		
		cout << "\n" ;
		cout << "*** Path Finding ***\n" ;
		cout << "* 0. Quit          *\n" ;
		cout << "* 1. One goal      *\n" ;
		cout << "* 2. More goals    *\n" ;
		cout << "********************\n" ;
		cout << "Input a command(0, 1, 2): " ;
		cin >> command ;
		if ( ( command == '1' ) || ( command == '2' ) ) {
			if ( command == '2' ) // '2'�A��h��G 
			    mode = moreG ; 
			
			cout << "\n" ;
			cout << "Input a file number: " ;
			cin >> fileName ;
			if ( mode == oneG ) { // '1'�A��@��G
			
				if ( aMaze.load( fileName ) ) { //Ū�J�g�c 
					Maze vMaze(aMaze) ; //�ƻs��V���|���g�c 
					bool vsuccess = vMaze.findVPath( 0, 0, 0 ) ; //V���|�g�c�O�_����			
					vMaze.showV() ; //�L�XV���| 
					cout << "\n" ; //���� 
					if ( vsuccess == true ) { // �p�G���\���V���| 
						aMaze.findRPath( 0, 0, 0 ) ; // ��XR���| 
						aMaze.showR() ; // �L�XR���| 
						cout << "\n" ; //���� 
					} // if ( vsuccess == true )
					
				    
				} // if ( aMaze.ioad( fileName ) )
				
				
			} // if ( mode == oneG )
			
			
			
			else if ( mode == moreG ){ //�Ҧ�2�A��hG 
				mode = oneG ;
			} //else if ( mode == moreG )
			
		} // if ( ( command == '1' ) || ( command == '2' ) )
		
		else if ( command == '0' ) // ��J0���}�{�� 
		    break ;
		    
		else //�D'0'�B'1'�B'2' 
		    cout << "\n" << "Command does not exist!\n" ;
	} while ( true ) ;
	
	system( "pause" ) ; // �Ȱ��{�ǰ���A���ݫ��UEnter��
	return 0 ;
} // main()


