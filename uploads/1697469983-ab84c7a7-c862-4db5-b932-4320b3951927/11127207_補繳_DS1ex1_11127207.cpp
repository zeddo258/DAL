// 11127207 ������

#include <iostream>
#include <fstream> // ���Y�� 
#include <string>
#include <list>  
#include <utility> // �]�t std :: pair 

using namespace std ;

class Mazechart {
	ifstream in ;
private :
	int reachGoal ; // �ݬO���O�F��ݭn���ؼм� 
	int line ; // ��e�o�@�� 
	int row ; // ��e�o�@�C 
	int i ; // �}�C�檺�j�p 
	int j ; // �}�C�C���j�p 
	int number ; // Ū���Ʀr 
	char chart[100][100] ; //�D�n�ϥΪ��}�C 
	std :: list <std :: pair< int, int > > thePath ; //�s���Ҩ��L���C�@�� ���FGOAL 
	int lineGoal[100] ; // ���������L��GOAL���� 
	int rowGoal[100] ; // ���������L��GOAL���C 
	int saveLine[100] ; //�����Q�R���B�P��gaol�������C 
	int saveRow[100] ;
	int saveNumber ;
	bool havepath ;
	bool needpath ;
	
	int needLine[100] ;
	int needRow[100] ;
	int need ;
	
 	
	int GetNumber () {
		in >> number ;   //����O�ƥ��̪��Ʀr 
		return number ;
	} // GetNumber()	
			
public :
	Mazechart() {  // ��class���ݭn��l�ƪ��ܼƪ�l�� 
		need = 0 ;
		needpath = false ;
		havepath = false ;
		saveNumber = 0 ; 
		reachGoal = 0 ;
		line = 0 ;
		row = 0 ;
	} // Mazechart 
	
	char Maze ;	
		
	bool Correctfile ( string i ) { //�ˬd��ƪ����T�� 
		string a = "input" + i + ".txt" ;
		in.open( a.c_str() ) ;
		if ( in.fail() ) {  // �p�G�S���o�Ӹ�� 
			cout << endl << "input" << i << ".txt does not exist" << endl ;
			in.close() ; // ���� 
			return false ;
		} // if
		else
			return true ;
		
	} // Correctfile
	
	void Read() { // Ū��� 
		i = GetNumber() ;
		j = GetNumber() ;
		
		for ( int row = 0 ; row < j ; row++ ) {
			for ( int line = 0 ; line < i ; line++ ) {
				in >> Maze ;
				chart[line][row] = Maze ;
			} // for
			
		} // for
		
	} // Read()	
	
	bool Move( int x ) { // �ѹ����ʨ̾ڨðO���ۤv���ʮ�l && �W�U���k�{���X�ҬۦP�u�����ǬO�k�U���W
	 	int time = 0 ;
	 	bool haveGoal = false ;
	 	if ( line == 0 && row == 0 ) {
	 		thePath.push_back(std::make_pair( line, row ) ) ;
	 		chart[0][0] = 'V' ;
	 	} // if
	 		
		while( time <= 4  ) { // �u�n�W�U���k�|�Ӥ�V���ݹL�B�Stime�F��4�N���X�j��  
			while( line < i  ) { // ���ʥB���_�ˬd�O�_���i�H�L�h�����|  �o�O���k�䨫�� 
				if ( chart[line + 1][row] == 'O' || chart[line + 1][row] == 'V' || line + 1 == i ) {
					time = time + 1 ;		// �p�G�O���L�����Φ���ê���άO���time�|+1 
					break ;					// time�u�n�j��|���N�N��O���� 
				} // if
				
				else if ( chart[line + 1][row] == 'E' ) { // �p�G�O�i�H�q�L�����N�O���_�Ө��ܦ�V 
					time = 0 ;
					line++ ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
					havepath = true ;
				} // else
				
				else if ( chart[line + 1][row] == 'G' ) { // �p�G���goal���P�_ 
					if ( reachGoal > 0 ) {   
						if ( Detect( line + 1, row ) != true ) {  // �w�g���@�ӥH�W��goal 
							line++ ;
							time = 0 ;                         
							lineGoal[reachGoal] = line ;    // �Ngoal�y�аO���b�S�w�}�C�� �H�K�� 
							rowGoal[reachGoal] = row ;		 
							reachGoal = reachGoal + 1 ;  // �o�N��ثe�w�g��쪺goal�ƶq 
						} // if
						else {
							time = time + 1 ; // �N��o��goal�w�g���L 
							break ;
						} // else
					}
					else {  // �٨S�J�����@��goal�����p 
						line++ ;
						time = 0 ;
						TurnRoute() ;
						lineGoal[reachGoal] = line ;  // �Ngoal�y�аO���b�S�w�}�C�� �H�K�� 
						rowGoal[reachGoal] = row ;
						reachGoal = reachGoal + 1 ;
					} //esle
					
					if ( reachGoal == x ) {  // �ƶq�F�Хi�H��^�D�{�� 
						return true ;
					} // if
					
				} // else if
				
			} // while
			
			
			while( row < j ) {  // ���U��  �����P���k�{��  
				if ( chart[line][row + 1] == 'O' || chart[line][row + 1] == 'V' || row + 1 == j ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[line][row + 1] == 'E' ) {
					time = 0 ;
					row++ ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
					havepath = true ;
				} // else if
				else if ( chart[line][row + 1] == 'G' ) {
					if ( reachGoal > 0 ) {
						if ( Detect( line, row + 1 ) != true ) {  // �w�g���@�ӥH�W��goal 
							row++ ;
							time = 0 ;
							lineGoal[reachGoal] = line ;
							rowGoal[reachGoal] = row ;
							reachGoal = reachGoal + 1 ;
						} // if
						else {
							time = time + 1 ;
							break ;
						}
					}
					
					else if ( reachGoal == 0 ){
						row++ ;
						time = 0 ;
						
						TurnRoute() ;
						
						lineGoal[reachGoal] = line ;
						rowGoal[reachGoal] = row ;
						reachGoal = reachGoal + 1 ;
					} //esle
					
						
					if ( reachGoal == x ) {
						return true ;
					}
					
				} // else if
				
			} // while
			
			
			while( line > 0 ) { // move left  �����P���k�{�� 
				if ( chart[line - 1][row] == 'O' || chart[line - 1][row] == 'V' ) {
					time = time + 1 ;
					break ;
				}
				else if ( chart[line - 1][row] == 'E' ) {
					time = 0 ;
					line-- ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;	
					havepath = true ;
				}
				else if ( chart[line - 1][row] == 'G' ) {
					if ( reachGoal > 0 ) {
						if ( Detect( line - 1, row ) != true ) {  // �w�g���@�ӥH�W��goal
							needpath = false ;
							line-- ;
							time = 0 ;
							TurnRoute() ;
							lineGoal[reachGoal] = line ;
							rowGoal[reachGoal] = row ;
							reachGoal = reachGoal + 1 ;
						
						} // if
						else {
							time = time + 1 ;
							break ;
						} // else
					}
					else {
						line-- ;
						time = 0 ;
						lineGoal[reachGoal] = line ;
						rowGoal[reachGoal] = row ;
						reachGoal = reachGoal + 1 ;
					} //esle
						
					if ( reachGoal == x ) {
						return true ;
					}
				} // else if
				
			} // while
			
			
			while( row > 0 ) { // move up �����P���k�{��  
				
				if ( chart[line][row - 1] == 'O' || chart[line][row - 1] == 'V' ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[line][row - 1] == 'E' ) {
					row-- ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
					havepath = true ;	
					time = 0 ;
				} // else if 
				
				else if ( chart[line][row - 1] == 'G' ) {
					if ( reachGoal > 0 ) {
						if ( Detect( line, row - 1) != true ) {  // �w�g���@�ӥH�W��goal 
							row-- ;
							time = 0 ;
							lineGoal[reachGoal] = line ;
							rowGoal[reachGoal] = row ;
							reachGoal = reachGoal + 1 ;
							
						} // if
						else {
							time = time + 1 ;
							break ;
						} // else 
					}
					else {
						row-- ;
						TurnRoute() ;
						time = 0 ;
						lineGoal[reachGoal] = line ;
						rowGoal[reachGoal] = row ;
						reachGoal = reachGoal + 1 ;
					} //esle
					
						
					if ( reachGoal == x ) {
						return true ;
					}
				} // else if
				
			} // while
			
			
		} // while
		
		if ( time >= 4 ) {
			havepath = false ;
			return false ;
		}
		
	} // Move
	
	bool Check() { // ���e��O�_�٦����|�i�H�� 
        std::pair<int, int> lastPair = thePath.back();
        line = lastPair.first ;
        row = lastPair.second ;  // ���O�N�Ȧs�x�b�ܼ� i �M j ��
        
        if ( DetectGoal( line, row ) == true ) { 	// ���]�h�^�h���P��goal
			if ( DetectRoute( line, row ) == true ) { // �B�����|�P�򦳸��Φ����g���L����(V)�i��
				saveLine[saveNumber] = line ;     	 // �N���y�Ь����H�K�Q�R�� 
        		saveRow[saveNumber] = row ;
        		saveNumber++ ;
        	} // if
    	} // if
    	thePath.pop_back();
		
		if ( thePath.size() > 0 )  // Return false�N���٦����|�i�H�ˬd�O�_�٥i�H�� 
			return false ;
		else 
			return true ;		
	} // check
	
	bool Detect( int p, int f ) {  // �ˬd�O���O���촿�g�q�L��goal 
		int g = 0 ;
		int h = 0 ;
		int x = 0 ;
		while ( x < reachGoal ) {
			g = lineGoal[x] ;
			h = rowGoal[x] ;
			if ( p == g && f == h )
				return true ;  // ���ƤF 
			x++ ;
		} // for
		
		return false ;
		
	} // Detcet
	
	bool DetectGoal ( int i, int j ) { // �ˬd�W�U���k�O�_��GOAL 
		if ( chart[i + 1][j] == 'G' ) {
			return true ;
		} // if
		
		else if ( chart[i][j + 1] == 'G' ) {
			return true ;
		} // else if
		
		else if ( chart[i - 1][j] == 'G' ) {
			return true ;
		} // else if
		
		else if ( chart[i][j - 1] == 'G' ) {
			return true ;
		} // else if
		
		else {  								 // �p�G���S���N��O���� 
			return false ;       
		}
		
	} // DetectGoal.
	
	bool DetectRoute ( int line, int row ) { // �ˬd�W�U���k�O�_������ 
		if ( line + 1 > i && chart[i][j + 1] == 'O' && chart[i][j - 1] == 'O'  ) { // �k��J����� �B�W�U�ҵL���i�� 
			return false ;
		} // if
		
		else if ( line - 1 < 0  && chart[i][j + 1] == 'O' && chart[i][j - 1] == 'O'  ) { // ����J����� �B�W�U�ҵL���i��
			return false ;
		} // else if
		
		else if ( row + 1 > j && chart[i + 1][j] == 'O' && chart[i - 1][j] == 'O'  ) { // �U���J����� �B���k�ҵL���i�� 
			return false ;
		} // else if
		
		else if ( row - 1 < 0 && chart[i + 1][j] == 'O' && chart[i - 1][j] == 'O'  ) { // �W���J����� �B���k�ҵL���i�� 
			return false ;
		} // else if
		
		return true ;       
		
	} // DetectGoal.
	 
	
	void Translate() {  // �N���n���|�୼R    PS.�i��|���Q�~�R�� �|��Debug()���{���ɦ^ 
	    std::pair<int, int> lastPair = thePath.back();
		line = lastPair.first ;
        row = lastPair.second ;
        chart[line][row] = 'R' ;

	} // Translate
	
	void Trans() {
		for ( int row = 0 ; row < j ; row++ ) {  // �h�l���|���ܦ�E 
			for ( int line = 0 ; line < i ; line ++ ) {
				if ( chart[line][row] == 'V' )
					chart[line][row] = 'E' ;	
			} // for
		}
	} // Trans
	
	void Fill() {  
		for ( int row = 0 ; row < j ; row++ ) {  // �קK�ਤ��R�Q�~�R 
			for ( int line = 0 ; line < i ; line ++ ) {
				if (chart[line][row] == 'V' ) { 
					if ( chart[line + 1][row] == 'R' && chart[line][row + 1] == 'R' ) // �k�U 
						chart[line][row] = 'R' ;
					else if ( chart[line + 1][row] == 'R' && chart[line][row - 1] == 'R' ) // �k�W 
						chart[line][row] = 'R' ;	
					else if ( chart[line - 1][row] == 'R' && chart[line][row + 1] == 'R' ) // ���U
				 		chart[line][row] = 'R' ;
					else if ( chart[line - 1][row] == 'R' && chart[line][row - 1] == 'R' ) // ���W 
				 		chart[line][row] = 'R' ;
				}				 	
			} // for
		}	
		
	}
	
	bool Cut() { // �R���h�l���I 
		thePath.pop_back();
		if ( thePath.size() > 0 )
			return false ;
		else 
			return true ;
	} // Cut
	
	void Debug() {  // ��Q�~�R�������n���|�ɦ^��     ps�ɤB 
		int deLine = 0 ;
		int deRow = 0 ;
		for ( int x = 0 ; x < saveNumber ; x++ ) {
			deLine = saveLine[x] ;
			deRow = saveRow[x] ;
			chart[deLine][deRow] = 'R' ;
			
		} // for
		
	} // Debug
	
	void Debug2() { // �L�X�O�d�����n���| 
		int deLine = 0 ;
		int deRow = 0 ;		
		for ( int x = 0 ; x < need ; x++ ) {
			deLine = needLine[x] ;
			deRow = needRow[x] ;
			chart[deLine][deRow] = 'R' ;
			
		} // for	
	}
	
	void Print() { // �L�X�Ϫ� 
		for ( int row = 0 ; row < j ; row++ ) {
			for ( int line = 0 ; line < i ; line ++ ) 
				cout << chart[line][row] ;
			
			cout << endl ;
			
		} // for
		
	} // Print
	
	void TurnRoute() { // �O�d�ݨ�G�H��^�Y�ݪ����| 
		std::list < std::pair < int, int > > :: iterator it;
		for ( it = thePath.begin() ; it != thePath.end() ; it++ ) {
			needLine[need] = it -> first ;
			needRow[need] = it -> second ;
			need = need + 1 ;	
    	}
		
	}	

			
} ;	


int main() {
	int x = 0 ;
	do {
		Mazechart aMaze ;  // �غc�l 
		string fileName ;   // �ɮצW 
		int command = 0 ;  // ���O 
		
		cout << endl << "*** Path Finding ***" ;
		cout << endl << "*0. Quit           *" ;   // �ϥΪ̩Ҭݨ쪺���� 
		cout << endl << "*1. One goal       *" ;
		cout << endl << "*2. More goals     *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2): " ;
		cin >> command ;
		cout << endl ;
		
		
		if ( command == 1 || command == 2 ) {  // �p�G��J���O1��2 
            cout << "Input a file number(ex.201, 202,... ) : "  ;
            string fileNumber ;
            cin >> fileNumber ;  // �����ɮצW�� 
                  
			bool success = aMaze.Correctfile( fileNumber ) ; //�ݬݬO�_���o���ɮ� 
			
			if ( success == true ) {
				aMaze.Read() ; // Ū�J�O�ƥ�������� 
				bool findGoal = false ;
				bool end = false ; 
				if ( command == 1 ) {
					while ( findGoal != true && end != true ) { // �u�n�����|�ΨS����L���i�H�A���N���X�j�� 
						findGoal = aMaze.Move( 1 ) ;  
						if ( findGoal != true ) { 
							end = aMaze.Check() ;  // �ˬd���g���L�����O�_�٦����i�H��							
						}  // if 						
					
					} // if
					
				} // if
				
				else if ( command == 2 ) {
					cout << endl << "Number of G(goals) :" ;
					int goal = 0 ;
					cin >> goal ;  // �ϥΪ̿�J�ݭn���ؼм� 
					while ( findGoal != true && end != true ) { // �P�W	
						findGoal = aMaze.Move( goal ) ;   // �ݻݭn�h�֭ӥؼ� 
						if ( findGoal != true ) {
							end = aMaze.Check() ;
							
						} // if
									
					} // while
					
				} // else if
				
				aMaze.Print() ;
				if ( findGoal == true ) { // ���]�����w�ƶq��goal�N�L�X�a��R���|���� 
					aMaze.Translate() ;
					while ( aMaze.Cut() != true )
						aMaze.Translate( ) ;
						
					cout << endl ;
					aMaze.Debug() ; // �ɦ^�Q�~�R�����n���| 
					if ( command == 2 )
						aMaze.Debug2() ;  // �o�O�b�n�@�ӥH�W�����|�|�J�쪺bug�n�O�d���^�Y�ݪ����n���| 
					aMaze.Fill() ;	
					aMaze.Trans() ; // ��L�θ��|�ରE 
					aMaze.Print() ;	
				} // if
				
				cout << endl ; 
			} // else
			
		} // if
		
		else if ( command == 0 ) // �p�G���O��0�N���X�{�� 
			return 0 ;
			
		else { // �p�G���O���~ 
			cout << endl << "Command does not exist!" << endl ;	
		} // else11
  
	} while (true) ;
	
	system("pause") ;
	return 0 ; 
} // main
 
