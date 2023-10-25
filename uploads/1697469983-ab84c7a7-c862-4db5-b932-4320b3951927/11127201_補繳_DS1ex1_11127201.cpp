// 11127201 ���~�� 
#include<iostream> 
#include<string.h> // String,c_str
#include <fstream>
#include<math.h>
#include<cstdlib>
#include <vector>


using namespace std ;

struct Ggrid  // �g�c���C�@�� 
{
	bool IsG = false ; // G���S�����L(���G�����p) 
	bool already = false; // ���񳣥����L 
    char type ; 
    int step = 0 ;
};


class Maze {
	
    public : 
		int length ; // �g�c���� 
		int width ; // �g�c�e�� 
		Ggrid **grid ;
		string filenumber ; // a file name(�ɦW)
		fstream file ;
		
		//================================�ʺA�x�}===============================================
		// �]�����T�w�h�j�A�ΰʺA�x�}�N���|���O�Ӧh�Ŷ� 

		Ggrid **Setmaze ( int length, int width ) {
			Ggrid **grid = new Ggrid*[length+2] ; // �гy���Ъ��� 
			for(int i = 0 ; i < length + 2 ; i++ ) {
				grid[i] = new Ggrid[width+2] ; // �Ыث��мe�� 
			} // for (�C�@��t�@�ӪŶ�) 
			
			return grid;	
		} // Setmaze() 
		


        // =====================================Ū��============================================= 
		
		
		bool OpenFile() {
			file.open( ( "input" + filenumber +  ".txt" ).c_str() ) ; // open the file �}��� 
			if ( file == NULL )  {
				// �S���ɮ׿�X���~ 
				cout << endl << filenumber << ".txt does not exist!" << endl ;
				return false ;
			} // if ( file == NULL )
            else 
			    return true  ;  
		} // OpenFile()

		
		
		
		// =====================================input�s��========================================= 
		
		void InputFile()  {
		// �NŪ����󪺫H���s�b�ܼƤ�	
		// >> �B��Ÿ��q�ɮפ����X�ƾڪ��N���m�᭱���ܼƤ� 
			file >> length ; // �Nfile �̭����ƭȦs�ilength(����) 
			file >> width ; // �Nfile �̭����ƭȦs�iwidth(�e��) 
		} // InputFile()  
		
		
		
		// =====================================input============================================ 
		
		void Input() {
			
			for( int y = 0 ; y < width + 2 ; y++ ){ 
			    for ( int x = 0 ; x < length + 2 ; x++ ) 
					grid[x][y].type = 'O'; // �]�w��� 
					// �T�O�g�c�~����ɨ���è�(�̥~��) 
			} // for
			
			for( int y = 1 ; y < width + 1 ; y++ ){
				for ( int x = 1 ; x < length + 1 ; x++ ) 
					file >> grid[x][y].type ; // Ū���ɮפ��C�@�ӲŸ���b�g�c�� 
			} // for
		} // Input()  
		
		
		
		//===================================output==================================================
		
		void Print()	{
			for( int y = 1 ; y < width + 1 ; y++ ){
				for ( int x = 1 ; x < length + 1 ; x++ ) 
					cout << grid[x][y].type ; // ���n���o�H�b�@�_ 
				cout << endl ;  // �C�j��W��� 
			} // for 
			
			cout << endl ; // ���j�g�c���A 
		} // Print()
		
		void Print1()	{
			int f = 0 ;
			for( int y = 1 ; y < width + 1 ; y++ ){
				for ( int x = 1 ; x < length + 1 ; x++ ) 
				    if ( grid[x][y].type == 'R'  ) f++ ; 
			} // for 
			
			if ( f > 1 ) {
				for ( int a = 1 ; a < width + 1 ; a++) {
					for ( int z = 1 ; z < length + 1 ; z++ )
						cout << grid[z][a].type; 
					cout << endl;	
				} //for	 
			} // if   
			
			cout << endl ; // ���j�g�c���A 
		} // Print()
		
		
		// =====================================����1============================================ 

		void Mission1(int x, int y, int length, int width, Ggrid **grid, bool &touch, char &direction) {
    	// �u�n�OE�N�@�����e��
    		if (grid[x][y].type == 'G') touch = false;  // �I��ؼ�G �פ���� 
    		else if (grid[x][y].type == 'E' || grid[x][y].type == 'V') {
        		if (grid[x][y].type == 'E') {
            		grid[x][y].type = 'V'; // �ѹ������a����˦�V
       		 	} // if 

       			 // �����ѹ����L����
        		grid[x][y].step = 1; // �w�g���L 
        		// �O�s��l��V�A�H�K�b�ݭn�^�h�ϥ�
        		char originalDirection = direction;
        		// ��s����V�� 
        		char newDirection = direction;
        		while (true) {
            		// ���շs����V ���F�˹�S�����L 
            		int newX = x, newY = y;
            		if (newDirection == 'R') newX = x + 1;
            		else if (newDirection == 'D') newY = y + 1;
            		else if (newDirection == 'L') newX = x - 1;
            		else if (newDirection == 'U') newY = y - 1;

            		// �ˬd�s��V�O�_���ġA�H�άO�_�w���L 
            		if ((grid[newX][newY].type == 'E' || grid[newX][newY].type == 'G') && touch && grid[newX][newY].step == 0) {
                		direction = newDirection; // ��s��V
                		Mission1(newX, newY, length, width, grid, touch, direction); // �~��V�e 
                		return;
        	    	} // if  
					else {
                		// ���դU�@�Ӥ�V 
                		if (newDirection == 'R') newDirection = 'D';
                		else if (newDirection == 'D') newDirection = 'L';
                		else if (newDirection == 'L') newDirection = 'U';
                		else if (newDirection == 'U') newDirection = 'R';


			    		// �d�O�_�w�g�����Ҧ���V�A�p�G�O�ݭn�^�h
            			if (  newDirection == originalDirection  ) {
                		// �^�h�@�B�A�����쥼��������
                			if (originalDirection == 'R' && x > 0 && grid[x-1][y].type != 'O' ) x--;
               	 			else if (originalDirection == 'D' && y > 0 && grid[x][y - 1].type != 'O' ) y--;
                			else if (originalDirection == 'L' && x < length - 1 && grid[x + 1][y].type != 'O'  ) x++;
                			else if (originalDirection == 'U' && y < width - 1 && grid[x][y + 1].type != 'O') y++;
                			else {
                    			touch = false; // �Ҧ���V���w�����S�k�^�h
                   	 			return;
                    		} // else 
       					}// if 
				
                		direction = originalDirection; // ���`��l��V 
            		} // else
        		} // while 
    		} // else if 

    		// �ѹ����� 
    		if (direction == 'R' && (grid[x + 1][y].type == 'E' || grid[x + 1][y].type == 'G') && touch) 
        		Mission1(x + 1, y, length, width, grid, touch, direction); // �ѹ����k
				
    		else if (direction == 'D' && (grid[x][y + 1].type == 'E' || grid[x][y + 1].type == 'G') && touch) 
        		Mission1(x, y + 1, length, width, grid, touch, direction); // �ѹ����U
        		
				
    		else if (direction == 'L' && (grid[x - 1][y].type == 'E' || grid[x - 1][y].type == 'G') && touch) 
        		Mission1(x - 1, y, length, width, grid, touch, direction); // �ѹ�����
        	
    		else if (direction == 'U' && (grid[x][y - 1].type == 'E' || grid[x][y - 1].type == 'G') && touch) 
        		Mission1(x, y - 1, length, width, grid, touch, direction); // �ѹ����W
		 } //  Mission1()


		void Mission1_2( int x, int y, int length, int width, Ggrid **grid, bool &touch ) {
			if ( grid[x][y].type == 'G'   )  { 
			    int d = 0 ;
				for( int y = 1 ; y < width + 1 ; y++ ){
					for ( int x = 1 ; x < length + 1 ; x++ ) 
	                	if ( grid[x][y].type == 'V'  ) d++;
				} // for 
			 
			    if ( d > 0 )  touch = true; 
			    else {
					touch = false ; // �I��ؼ� G
					return;
			    } //else 
		    } // if 
			else grid[x][y].type = 'R' ; // �N���L���a�賣���] R 
			
			if ( ( grid[x+1][y].type == 'V' || grid[x+1][y].type == 'G' ) && touch ) {
				Mission1_2( x+1, y, length, width, grid, touch ) ;
				if ( touch ) grid[x+1][y].type = 'E' ; // �N�����]��E 
			} // if (�k) 
			
			if ( ( grid[x][y+1].type == 'V' || grid[x][y+1].type == 'G' ) && touch ) {
				Mission1_2( x, y+1, length, width, grid, touch ) ;
				if ( touch ) grid[x][y+1].type = 'E' ; // �N�����]��E  
			} // if (�U) 
			
			if ( ( grid[x-1][y].type == 'V' || grid[x-1][y].type == 'G' ) && touch ) {
				Mission1_2( x-1, y, length, width, grid, touch ) ;
				if ( touch ) grid[x-1][y].type = 'E' ; // �N�����]��E  
			} // if (��) 
			
			if ( ( grid[x][y-1].type == 'V' || grid[x][y-1].type == 'G' ) && touch ) {
				Mission1_2( x, y-1, length, width, grid, touch ) ;
				if ( touch ) grid[x][y-1].type = 'E' ; // �N�����]��E  
			} // if (�W) 
			
			
		
	
		} // Mission1_2()
		
		
		// ====================================���ȤG=================================================



	void Mission2(int x, int y, int length, int width, Ggrid **grid, bool &touch, char &direction, int &totalTargets) {
    	// �p�G�ؼжq�w���s����j��
    	if (totalTargets == 0) {
        	touch = false;
        	return;
    	} // if 

   		 if ( grid[x][y].type == 'G' ) {
    		 if (grid[x][y].step == 0) { 
        	    grid[x][y].step = 1; 
            	totalTargets--; // ���@�ӥؼд�֤@��
            }// if 

        	if ( direction == 'R') {
        		if (  (grid[x + 1][y].type == 'E' ) && touch )
       				Mission2( x + 1, y, length, width, grid, touch, direction, totalTargets ); // �ѹ����k
       			else if ( ( grid[x+1][y].type == 'O' || grid[x][y+1].type == 'V'  )  && touch ) {
       				direction = 'D' ;
       		   	 	Mission2( x, y + 1, length, width, grid, touch, direction, totalTargets ); // �ѹ����U  
				} // else if 
   			} // if  
			else if ( direction == 'D' ) {
				if (   ( grid[x][y + 1].type == 'E' ) && touch)
       				Mission2(x, y + 1, length, width, grid, touch, direction, totalTargets); // �ѹ����U
       			else if ( ( grid[x][y+1].type == 'O' || grid[x][y+1].type == 'V' )  && touch) {
       				direction = 'L' ;
       		    	Mission2(x - 1, y, length, width, grid, touch, direction, totalTargets );  // �ѹ����� 
				} // else if 
   		 	} // else if 
			else if ( direction == 'L' ) {
				if (  ( grid[x - 1][y].type == 'E' ) && touch )
       				Mission2(x - 1, y, length, width, grid, touch, direction, totalTargets); // �ѹ�����
       			else if ( ( grid[x-1][y].type == 'O' || grid[x-1][y].type == 'V' )  && touch) {
       				direction = 'U';
       		   	 	Mission2(x, y - 1, length, width, grid, touch, direction, totalTargets); // �ѹ����W
				} // else if 
    		} // else if  
			else if ( direction == 'U' ) {
				if (   (grid[x][y - 1].type == 'E' ) && touch )
       				Mission2(x, y - 1, length, width, grid, touch, direction, totalTargets); // �ѹ����W
       			else if ( ( grid[x][y-1].type == 'O' || grid[x][y-1].type == 'V' )  && touch) {
       				direction = 'U';
       		    	Mission2(x + 1, y, length, width, grid, touch, direction, totalTargets ); // �ѹ����k
				} // else if 
    		} // else if 
    	} //if
		else if (grid[x][y].type == 'E' || grid[x][y].type == 'V') {
        	if (grid[x][y].type == 'E') {
            	grid[x][y].type = 'V'; // �ѹ������a����˦�V
        	} //if 

        	// �ݦѹ����S�����L 
        	grid[x][y].step = 1; // �w�g���L 
        	// �O�s��l��V�A�H�K�b�ݭn�^�h�ϥ�
        	char originalDirection = direction;
        	// ��s����V
        	char newDirection = direction;
        	while (true) {
            	// ���u�s��V���e 
            	int newX = x, newY = y;
            	if (newDirection == 'R') newX = x + 1;
            	else if (newDirection == 'D') newY = y + 1;
            	else if (newDirection == 'L') newX = x - 1;
            	else if (newDirection == 'U') newY = y - 1;

            	// �ˬd�s��V�O�_���ġA�H�άO�_�w���L 
            	if ((grid[newX][newY].type == 'E' || grid[newX][newY].type == 'G') && touch && grid[newX][newY].step == 0) {
                	direction = newDirection; // ��s��V
                	Mission2(newX, newY, length, width, grid, touch, direction, totalTargets); // �~�򩹫e 
                	return;
            	} //if  
				else {
					 // ��U�@�Ӥ�V
                	if (newDirection == 'R') newDirection = 'D';
                	else if (newDirection == 'D') newDirection = 'L';
                	else if (newDirection == 'L') newDirection = 'U';
                	else if (newDirection == 'U') newDirection = 'R';
                
					 // �d�O�_�w�g�����Ҧ���V�A�p�G�O�ݭn�^�h
            		if (newDirection == originalDirection) {
                	// �^�h�@�B�A�����쥼��������
                		if (originalDirection == 'R' && x > 0 && grid[x - 1][y].type != 'O') x--;
                		else if (originalDirection == 'D' && y > 0 && grid[x][y - 1].type != 'O') y--;
                		else if (originalDirection == 'L' && x < length - 1 && grid[x + 1][y].type != 'O') x++;
                		else if (originalDirection == 'U' && y < width - 1 && grid[x][y + 1].type != 'O') y++;
                		else {
                    		touch = false; // �Ҧ���V���w�����L�k�^�h
                   	 		return;
                    	} // else  
                
					} // if 
				
               		 direction = originalDirection; // ���`��l��V
				} // else			
        	}//while 
    	}// else if 

    	// ���u��V�e�i 
    	if (direction == 'R' && (grid[x + 1][y].type == 'E' || grid[x + 1][y].type == 'G') && touch) 
        	Mission2(x + 1, y, length, width, grid, touch, direction, totalTargets); // �ѹ����k
    	else if (direction == 'D' && (grid[x][y + 1].type == 'E' || grid[x][y + 1].type == 'G') && touch) 
        	Mission2(x, y + 1, length, width, grid, touch, direction, totalTargets); // �ѹ����U
    	else if (direction == 'L' && (grid[x - 1][y].type == 'E' || grid[x - 1][y].type == 'G') && touch) 
        	Mission2(x - 1, y, length, width, grid, touch, direction, totalTargets); // �ѹ�����
    	else if (direction == 'U' && (grid[x][y - 1].type == 'E' || grid[x][y - 1].type == 'G') && touch) 
        	Mission2(x, y - 1, length, width, grid, touch, direction, totalTargets); // �ѹ����W
	} // Mission2()
		
		
		void Mission2_2( int x, int y, int length, int width, Ggrid **grid, bool &touch , int &total ) {
		
			if ( grid[x][y].type == 'G' ) {
				if ( !grid[x][y].IsG ) total-- ; // �I��ؼ�  
				grid[x][y].IsG = true ; // �N�I��L�� G �O���_�� 
			} // if 
			else if ( touch && grid[x][y].type != 'G') grid[x][y].type = 'R' ; // �N���L���a�賣���]�� R  
		
			
			if ( total == 0  ) touch  = false ; // �פ���� 
			else if ( ( grid[x+1][y].type == 'V' || grid[x+1][y].type == 'G' ) && touch ) 
				Mission2_2( x+1, y, length, width, grid, touch , total ) ; // �ѹ����k 
			else if ( ( grid[x][y+1].type == 'V' || grid[x][y+1].type == 'G' ) && touch ) 
				Mission2_2( x, y+1, length, width, grid, touch, total ) ; // �ѹ����U 
			else if ( ( grid[x-1][y].type == 'V' || grid[x-1][y].type == 'G' ) && touch ) 
				Mission2_2( x-1, y, length, width, grid, touch , total ) ; // �ѹ����� 
			else if ( ( grid[x][y-1].type == 'V' || grid[x][y-1].type == 'G' ) && touch ) 
				Mission2_2( x, y-1, length, width, grid, touch , total ) ; // �ѹ����W 
			
			if ( !touch ) grid[x][y].already = true ; // �N�̫�@�� G �����|�O���_�� 
		} //  Mission2_2()		
		// =================================== G ��������============================================
		
		void AllGreset( int length, int width, Ggrid **grid ) {  
			for( int y = 1 ; y < width + 1 ; y++ ) {
				for ( int x = 1 ; x < length + 1 ; x++ ) if( grid[x][y].IsG ) grid[x][y].IsG = false ;
			} // for 
		} // AllGreset()
		
		// =================================-�N R �אּ V============================================
		
		void ResetV( int length, int width, Ggrid **grid ) {
			for( int y = 1 ; y < width + 1 ; y++ ){
				for ( int x = 1 ; x < length + 1 ; x++ ) if( grid[x][y].type == 'R') grid[x][y].type = 'V' ;
			} // for 
		} // ResetV()
		
		// ==================================�N V �אּ E============================================
		
		void ResetE( int length, int width, Ggrid **grid ) {
			for( int y = 1 ; y < width + 1 ; y++ ){
				for ( int x = 1 ; x < length + 1 ; x++ ) if( grid[x][y].type == 'V') grid[x][y].type = 'E' ;
			} // for 
		} // ResetE()


		
		// =================================�N�����_�Ӫ����|�]�� R===============================
		
		void ResetR( int length, int width, Ggrid **grid ) {
			for( int y = 1 ; y < width + 1 ; y++ ){
				for ( int x = 1 ; x < length + 1 ; x++ ) if( grid[x][y].already && !grid[x][y].IsG ) grid[x][y].type = 'R' ;
			} // for
		} // ResetR()
		
		
		
		bool Isdigit( string num ) { 
			int thelength = num.length() ;
			for ( int i = 0 ; i < thelength ; i++ ) {  // �@�Ӥ@�ӬݬO���O�Ʀr 
				if ( num[i] < '0' || num[i] > '9' ) return false ; 
			} // for  
			
			return true ;
		} //  Isdigi() 	
};

int main() {
	int command = 0 ; // user command
	Maze maze ;
	do {
		int x = 1, y = 1, total = 1 ;
		int step = 1, shorteststep = 0 ;
		bool touch = true ;
		string G ;
		
		cout << endl << "*** Path Finding ***" ;
		cout << endl << "* 0. Quit          *" ;
		cout << endl << "* 1. One goal      *" ;
		cout << endl << "* 2. More goals    *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2):" ;
		cin >> command ; // get the command(��o���O)
		
		
		
		if ( command == 0 ) break ; //'0':stop 
		else if ( command == 1 || command == 2  ){ 
			cout << "Input a file number (e.g., 201, 202, ...):" ;
			cin >> maze.filenumber ; // �ɮױo�s��
			if ( maze.OpenFile() ) {
				maze.InputFile() ; // �s����� 
				maze.grid = maze.Setmaze ( maze.length, maze.width ) ;  // �ЫذʺA�}�C 
				maze.Input() ; // �]�w�g�c 
				
				if ( command == 1 ) {
					char direction = 'R';
					maze.Mission1( x, y, maze.length, maze.width, maze.grid, touch ,  direction  ) ;
					maze.Print() ; // �L�X�� 
					if ( !touch ) {
						x = 1, y = 1, touch = true ;
						maze.Mission1_2( x, y, maze.length, maze.width, maze.grid, touch) ;
						maze.Print1() ; // �L�X�� 
					} // if 
					else x = 1, y = 1, touch = true ;
			    } // if ( command == 1 )
				else if ( command == 2 ) {
				    do { 
						cout << "Number of G (goals):" ;// �g�c�ݭn�h�֥ؼ� 
						cin >> G ;// Ū�i�Ӫ��� 
						total = std::atoi( G.c_str() ) ;//�NŪ�i�Ӫ��Ÿ��ন�Ʀr 
						if ( ( total > 100 || total < 1 ) ) cout << "### The number must be in [1,100] ###" << endl ;	
				   } while ( !maze.Isdigit( G ) || ( total > 100 || total < 1 ) ) ;

				    char direction = 'R';
					int temp = total ;
					int num = 0 ;
					maze.Mission2( x, y, maze.length, maze.width, maze.grid, touch, direction, total ) ;
					maze.Print();
						if ( !touch ) {
							total = temp ;
							x = 1, y = 1, touch = true ;	
							for ( int i = 1 ; i <= total ; i++ ) { // �� Mission2Run2 �] 1 �� total �� 
								total = i ;
								maze.AllGreset( maze.length, maze.width, maze.grid ) ;
								maze.Mission2_2( x, y, maze.length, maze.width, maze.grid, touch, total ) ;
								maze.ResetV( maze.length, maze.width, maze.grid ) ;
								x = 1, y = 1, touch = true ;	
								total = temp ;
							} // for	 
					
							maze.ResetR( maze.length, maze.width, maze.grid ) ;
							maze.ResetE( maze.length, maze.width, maze.grid ) ;
				 			maze.Print();
						} // if  	
				}  // else if ( command == 2 ) 
				
				maze.file.close() ; 
		        delete[] maze.grid ;
			} // if 
		} // else if ( command == 1 || command == 2  )	
		else cout << endl  << "Command does not exist!" << endl ;
		
	} while(true );
	
	
	system( "pause" ) ; // pause the execution �Ȱ����� ( system ����ާ@�R�O�Apause �Ω�Ȱ����浥�i��J�A����|��ܮפU���N���~�� ) 
	return 0 ;
	
} // main 
