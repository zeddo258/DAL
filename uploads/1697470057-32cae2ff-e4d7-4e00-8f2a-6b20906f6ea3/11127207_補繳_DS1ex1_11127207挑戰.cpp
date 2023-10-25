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
	std :: list <std :: pair< int, int > > nowPath ; // �����^�Y�ݪ���� 
	std :: list <std :: pair< int, int > > printPath ; // �n�L���s�̵u���| 
	std :: list <std :: pair< int, int > > dPath ; // �����^�Y�ݪ���l�����X�����
	std :: list <std :: pair< int, int > > sPath ; // �����ø� 
	int lineGoal[100] ; // ���������L��GOAL���� 
	int rowGoal[100] ; // ���������L��GOAL���C 
	int saveLine[100] ; //�����Q�R���B�P��gaol�������C 
	int saveRow[100] ;
	int saveNumber ;
	bool havepath ;
	bool needpath ;
	
	int needLine[100] ; // �x�s���|�� 
	int needRow[100] ;
	int need ;
	
	 

	bool haveShorest ; // �ثe�L�γB �ɶ��Ӥ��Χ�}   
	int preLength ; // �����̪��ؼЪ����� 
	int nowLength ; // �����ثe���� 
	int goalLine ; // ����G����m 
	int goalRow ;
	int shortlength ; // �n�^�Ǫ��̵u���|�� 
	bool touchGoal ; // �ثe�L�γB�ɶ�������} 
	
 	
	int GetNumber () {
		in >> number ;   //����O�ƥ��̪��Ʀr 
		return number ;
	} // GetNumber()	
			
public :
	Mazechart() {  // ��class���ݭn��l�ƪ��ܼƪ�l�� 
		touchGoal = false ;
		shortlength = 0 ;
		nowLength = 0 ;
		preLength = 0 ;
		haveShorest = false ;

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
	
	bool Move3() {
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
					preLength++ ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
				} // else
				
				else if ( chart[line + 1][row] == 'G' ) { // �p�G���goal���P�_ 
					goalLine = line ;
					goalRow = row ;
					preLength++ ;
					line++ ;
					time = 0 ;
					lineGoal[reachGoal] = line ;  // �Ngoal�y�аO���b�S�w�}�C�� �H�K�� 
					rowGoal[reachGoal] = row ;
					reachGoal = reachGoal + 1 ;
					return true ;

					
				} // else if
				
			} // while
			
			
			while( row < j ) {  // ���U��  �����P���k�{��  
				if ( chart[line][row + 1] == 'O' || chart[line][row + 1] == 'V' || row + 1 == j ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[line][row + 1] == 'E' ) {
					preLength++ ;
					time = 0 ;
					row++ ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
				} // else if
				else if ( chart[line][row + 1] == 'G' ) {
					goalLine = line ;
					goalRow = row ;
					preLength++ ;
					row++ ;
					time = 0 ;
					lineGoal[reachGoal] = line ;
					rowGoal[reachGoal] = row ;
					reachGoal = reachGoal + 1 ;
					return true ;
					
				} // else if
				
			} // while
			
			
			while( line > 0 ) { // move left  �����P���k�{�� 
				if ( chart[line - 1][row] == 'O' || chart[line - 1][row] == 'V' ) {
					time = time + 1 ;
					break ;
				}
				else if ( chart[line - 1][row] == 'E' ) {
					preLength++ ;
					time = 0 ;
					line-- ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;	
				}
				else if ( chart[line - 1][row] == 'G' ) {
					goalLine = line ;
					goalRow = row ;
					preLength++ ;
					line-- ;
					time = 0 ;
					lineGoal[reachGoal] = line ;
					rowGoal[reachGoal] = row ;
					reachGoal = reachGoal + 1 ;
					return true ;
						
				} // else if
				
			} // while
			
			
			while( row > 0 ) { // move up �����P���k�{��  
				
				if ( chart[line][row - 1] == 'O' || chart[line][row - 1] == 'V' ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[line][row - 1] == 'E' ) {
					row-- ;
					preLength++ ;
					thePath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
					havepath = true ;	
					time = 0 ;
				} // else if 
				
				else if ( chart[line][row - 1] == 'G' ) {
					goalLine = line ;
					goalRow = row ;
					row-- ;
					preLength++ ;
					time = 0 ;
					lineGoal[reachGoal] = line ;
					rowGoal[reachGoal] = row ;
					reachGoal = reachGoal + 1 ;
					if ( nowLength < preLength )
						return true ;
				} // else if
				
			} // while
			
			
		} // while
		
		if ( time >= 4 ) {
			
			return false ;
			
		}	
		
	} // Move3

	
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
	
	bool Check1() { // ���e��O�_�٦����|�i�H�� 
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
    	else {
    		preLength-- ;
    		thePath.pop_back();
		}
		
		
		
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
	
	bool Haves() {  // �ݦ��S���ø� 
		if (  chart[line + 1][row] == 'E' && chart[line - 1][row] == 'E' ) { // �k��J����� �B�W�U�ҵL���i�� 
			return true ;
		} // if
		
		else if ( chart[line][row - 1] == 'E' && chart[line][row + 1] == 'E'  ) { // ����J����� �B�W�U�ҵL���i��
			return true ;
		} // else if
		
		return false ;    
		
	}	
	

	bool Mod() { // �䦳�S����u���| 
	 	int time = 0 ; 
	 	int x = 0 ;
	 	std::list < std::pair < int, int > > :: iterator it;
		while( time <= 4 && nowPath.size() + dPath.size() < preLength ) { // �ݬO���O�����ӥB�����쥻��쪺���|�j 
			while( line < i && nowPath.size() + dPath.size() < preLength ) { // ���ʥB���_�ˬd�O�_���i�H�L�h�����|  �o�O���k�䨫�� 
				if ( chart[line + 1][row] == 'O' || line + 1 == i ||  chart[line + 1][row] == 'V' ) {
					time = time + 1 ;		// �p�G�O���L�����Φ���ê���άO���time�|+1 
					break ;					// time�u�n�j��|���N�N��O���� 
				} // if
				
				
				else if ( chart[line + 1][row] == 'E' && nowPath.size() + dPath.size() < preLength ) { // �p�G�O�i�H�q�L�����N�O���_�Ө��ܦ�V 
					time = 0 ;
					line++ ;
					dPath.push_back(std::make_pair( line, row ) ) ; //�⨫�L���I�Ȧs�blist�� 
					chart[line][row] = 'V' ; 
					if ( Haves() == true ) { //�ݦ��S���ø� 
						Mod2( line - 1, row ) ;
					}
						
					if ( reach() == true && nowPath.size() + dPath.size() < preLength && touchGoal != true )
						return true ; // �p�G��쪺���|���Q���L�B�o�O�i�H�۳s���̵u���|�N�^�� 

				} // else
				else if ( chart[line + 1][row] == 'G' ) {
					time = 0 ; //�T�{��쪺���N�O���O���ƦӥB������Ӥj 
					if ( nowPath.size() + dPath.size() < preLength && Detect( line + 1, row) != true ) {
						shortlength = nowPath.size() + dPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else 
						return false ;
				}
			} // while
			
			
			while( row < j && nowPath.size() + dPath.size() < preLength ) {  // ���U��  �����P���k�{��  
				if ( chart[line][row + 1] == 'O' || row + 1 == j ||  chart[line][row + 1] == 'V' ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[line][row + 1] == 'E' && nowPath.size() + dPath.size() < preLength ) {
					time = 0 ;
					row++ ;
					x++ ;
					chart[line][row] = 'V' ;
					dPath.push_back(std::make_pair( line, row ) ) ;
					if ( Haves() == true ) {
						Mod2( line + 1, row ) ;
					}
					if ( reach() == true && nowPath.size() + dPath.size() < preLength && touchGoal != true )
						return true ;
				} // else if
				else if ( chart[line][row+ 1] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + dPath.size() < preLength && Detect( line, row + 1) != true ) {
						shortlength = nowPath.size() + dPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else {
						return false ;
					}
				}
			} // while
			
			
			while( line > 0 && nowPath.size() + dPath.size() < preLength ) { // move left  �����P���k�{�� 
				if ( chart[line - 1][row] == 'O' ||  chart[line - 1][row] == 'V' ) {
					time = time + 1 ;
					break ;
				}
				else if ( chart[line - 1][row] == 'E' && nowPath.size() + dPath.size() < preLength ) {
					time = 0 ;
					line-- ;
					x++ ;
					dPath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;
					if ( Haves() == true ) {
						Mod2( line + 1, row ) ;
					}
					if ( reach() == true && nowPath.size() + dPath.size() < preLength && touchGoal != true && Detect( line - 1, row) != true )
						return true ;				 
					
				}
				else if ( chart[line - 1][row] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + dPath.size() < preLength ) {
						shortlength = nowPath.size() + dPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else 
						return false ;
				}
			} // while
			
			
			while( row > 0 && nowPath.size() + dPath.size() < preLength ) { // move up �����P���k�{��  
				
				if ( chart[line][row - 1] == 'O' ||  chart[line][row - 1] == 'V' ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[line][row - 1] == 'E' && nowPath.size() + dPath.size() < preLength ) {
					row-- ;
					x++ ;
					dPath.push_back(std::make_pair( line, row ) ) ;
					chart[line][row] = 'V' ;	
					time = 0 ;
					if ( Haves() == true ) {
						Mod2( line - 1, row ) ;
					}
					if ( reach() == true && nowPath.size() + dPath.size() < preLength && touchGoal != true && Detect( line, row - 1) != true)
						return true ;
				} // else if 
				else if ( chart[line + 1][row] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + dPath.size() < preLength ) {
						shortlength = nowPath.size() + dPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else 
						return false ;
				}
			} // while
			
			
		} // while
		
		
		if ( time >= 4 || nowPath.size() + dPath.size() >= preLength ) {
    		dPath.clear() ; // �p�G�S����u���|��쥻�Ȧs����ƲM�� 
			return false ;		
		}		
		
	} // Mod
	
	bool Mod2( int l, int r ) { // �b�ø��䦳�S����u���| 
	 	int time = 0 ; 
	 	int x = 0 ;
	 	std::list < std::pair < int, int > > :: iterator it;
	 	sPath.push_back(std::make_pair( l, r ) ) ;
	 	chart[l][r] = 'V' ;
		while( time <= 4 && nowPath.size() + sPath.size() + dPath.size() < preLength ) { // �u�n�W�U���k�|�Ӥ�V���ݹL�B�Stime�F��4�N���X�j��  
			while( l < i && nowPath.size() + sPath.size() + dPath.size() < preLength ) { // ���ʥB���_�ˬd�O�_���i�H�L�h�����|  �o�O���k�䨫�� 
				if ( chart[l + 1][r] == 'O' || l + 1 == i ||  chart[l + 1][r] == 'V' ) {
					time = time + 1 ;		// �p�G�O���L�����Φ���ê���άO���time�|+1 
					break ;					// time�u�n�j��|���N�N��O���� 
				} // if
				
				
				else if ( chart[l + 1][r] == 'E' && nowPath.size() + sPath.size() + dPath.size() < preLength ) { // �p�G�O�i�H�q�L�����N�O���_�Ө��ܦ�V 
					time = 0 ;
					l++ ;
					sPath.push_back(std::make_pair( l, r ) ) ;
					chart[l][r] = 'V' ; 	
					if ( reach() == true && nowPath.size() + sPath.size() + dPath.size() < preLength && touchGoal != true )
						return true ;

				} // else
				else if ( chart[l + 1][r] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + sPath.size() + dPath.size() < preLength && Detect( l + 1, r) != true ) {
						shortlength = nowPath.size() + sPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else 
						return false ;
				}
			} // while
			
			
			while( r < j && nowPath.size() + sPath.size() + dPath.size() < preLength ) {  // ���U��  �����P���k�{��  
				if ( chart[l][r + 1] == 'O' || r + 1 == j ||  chart[l][r + 1] == 'V' ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[l][r + 1] == 'E' && nowPath.size() + dPath.size() + sPath.size() < preLength ) {
					time = 0 ;
					r++ ;
					chart[l][r] = 'V' ;
					sPath.push_back(std::make_pair( l, r ) ) ;
					if ( reach() == true && nowPath.size() + dPath.size() < preLength && touchGoal != true )
						return true ;
				} // else if
				else if ( chart[l][r+ 1] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + dPath.size() + sPath.size() < preLength && Detect( l, r + 1) != true ) {
						shortlength = nowPath.size() + dPath.size() + sPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else {
						return false ;
					}
				}
			} // while
			
			
			while( l > 0 && nowPath.size() + dPath.size() + sPath.size() < preLength ) { // move left  �����P���k�{�� 
				if ( chart[l - 1][r] == 'O' ||  chart[l - 1][r] == 'V' ) {
					time = time + 1 ;
					break ;
				}
				else if ( chart[l - 1][r] == 'E' && nowPath.size() + dPath.size() + sPath.size() < preLength ) {
					time = 0 ;
					l-- ;

					sPath.push_back(std::make_pair( l, r ) ) ;
					chart[l][r] = 'V' ;

					if ( reach() == true && nowPath.size() + dPath.size() + sPath.size() < preLength && touchGoal != true && Detect( l - 1, r) != true )
						return true ;				 
					
				}
				else if ( chart[l - 1][r] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + dPath.size() + sPath.size() < preLength ) {
						shortlength = nowPath.size() + dPath.size() + sPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else 
						return false ;
				}
			} // while
			
			
			while( r > 0 && nowPath.size() + dPath.size() + sPath.size() < preLength ) { // move up �����P���k�{��  
				
				if ( chart[l][r - 1] == 'O' ||  chart[l][r - 1] == 'V' ) {
					time = time + 1 ;
					break ;
				} // if
				else if ( chart[l][r - 1] == 'E' && nowPath.size() + dPath.size() + sPath.size() < preLength ) {
					r-- ;
					sPath.push_back(std::make_pair( l, r ) ) ;
					chart[line][row] = 'V' ;	
					time = 0 ;
					if ( reach() == true && nowPath.size() + dPath.size() + sPath.size() < preLength && touchGoal != true && Detect( l, r - 1) != true)
						return true ;
				} // else if 
				else if ( chart[l + 1][r] == 'G' ) {
					time = 0 ;
					if ( nowPath.size() + dPath.size() + sPath.size() < preLength ) {
						shortlength = nowPath.size() + dPath.size() + sPath.size() + 1 ;
						touchGoal = true ;
						return true ;
					}
					else 
						return false ;
				}
			} // while
			
			
		} // while
		
		
		if ( time >= 4 || nowPath.size() + dPath.size() + sPath.size() >= preLength ) {
    		sPath.clear() ;
			return false ;		
		}		
		
	} // Mod

	
	bool findShortest() { // ��̵u���| �S���N�^�ǿ��~ 
		std::list < std::pair < int, int > > :: iterator it;
		bool x = false ;
		for ( it = thePath.begin() ; it != thePath.end() ; it++ ) {
			line = it -> first ;
			row = it -> second ;
			nowPath.push_back(std::make_pair( line, row ) ) ;
			if ( Mod()== true ) { 
				x = true ; 
				Copy() ;
			}
			 
    	}	
		
		if ( x == true ) { 
			return true ;
		}
		
		shortlength = thePath.size() + 1 ;
		return false ;
		
	
	}
	 
	
	void Copy() { // ���쪺�̵u���|�s���b�o��list�� 
		std::list < std::pair < int, int > > :: iterator it;
		bool x = false ;
		for ( it = nowPath.begin() ; it != nowPath.end() ; it++ ) {
			line = it -> first ;
			row = it -> second ;
			printPath.push_back(std::make_pair( line, row ) ) ;
		}
		for ( it = dPath.begin() ; it != dPath.end() ; it++ ) {
			line = it -> first ;
			row = it -> second ;
			printPath.push_back(std::make_pair( line, row ) ) ;
		}
		
		if ( touchGoal != true ) // �p�G�o�ӳ̵u���|���q�L�w���L�����|�N�[�i�h 
			printPath.push_back(std::make_pair( goalLine, goalRow ) ) ;

	}
	
	bool reach() { // �̵u���|���q�L�w���L�����| ���ץ[�W�Ӹ��|�H�β��I 
		if ( line + 1 == goalLine && row == goalRow ) {
			shortlength = nowPath.size() + dPath.size() + 2 ;
			return true ;
		}
		else if ( line - 1 == goalLine && row == goalRow ) {
			shortlength = nowPath.size() + dPath.size() + 2 ;
			return true ;
		}
		else if ( line == goalLine && row + 1 == goalRow ) {
			shortlength = nowPath.size() + dPath.size() + 2 ;
			return true ;
		}
		else if ( line == goalLine && row - 1 == goalRow ) {
			shortlength = nowPath.size() + dPath.size() + 2 ;
			return true ;
		}
			
		return false ;
	}
	
	void Turnshort() { // ��̵u���|���ܨ�ϤW 
		std::list < std::pair < int, int > > :: iterator it;
		int l = 0 ;
		int r = 0 ;
		for ( it = printPath.begin() ; it != printPath.end() ; it++ ) {
			l = it -> first ;
			r = it -> second ;
			chart[l][r] = 'R' ;
		}
		
	}
	void noShortPath() { // �S���̵u���| �����L�X�쥻���| 
		std::list < std::pair < int, int > > :: iterator it;
		int l = 0 ;
		int r = 0 ;
		for ( it = thePath.begin() ; it != thePath.end() ; it++ ) {
			l = it -> first ;
			r = it -> second ;
			chart[l][r] = 'R' ;
		}		
		
	}
	
	int GetLength() { // �^�Ǫ��� 
		return shortlength ;	
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
		cout << endl << "*3. Shortest path  *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command(0, 1, 2, 3 ): " ;
		cin >> command ;
		cout << endl ;
		
		
		if ( command == 1 || command == 2 || command == 3 ) {  // �p�G��J���O1��2 
            cout << "Input a file number(ex.201, 202,... ) : "  ;
            string fileNumber ;
            cin >> fileNumber ;  // �����ɮצW�� 
			bool findGoal = false ;
			bool end = false ;      
			bool success = aMaze.Correctfile( fileNumber ) ; //�ݬݬO�_���o���ɮ� 
			
			if ( success == true ) {
				aMaze.Read() ; // Ū�J�O�ƥ�������� 

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
				
				else if ( command == 3 ) {
					while ( findGoal != true && end != true ) { // ���˥X�Ϫ�H�άݦ��L���| 
						findGoal = aMaze.Move3() ;   
						if ( findGoal != true ) {
							end = aMaze.Check1() ;
						} 			
					} // while
						
					bool shor = false ;
					int g = 0 ;
					shor = aMaze.findShortest() ;
					aMaze.Print() ;
					cout << endl ;
					if ( findGoal == true ) {
						if ( shor == true ) {	// �����̵u���| 
							aMaze.Turnshort() ;
						}
						else { // �S�����̵u���| 
							aMaze.noShortPath() ;
						}
						
						aMaze.Trans() ; // ��L�θ��|�ରE
						aMaze.Print() ;
						g = aMaze.GetLength() ;
						cout << "Shortest path length = " ;
						cout << g << endl ;
					}
					else // �p�G���S�������|���� 
						cout << "### There is no path to find a goal! ###" << endl ;	
						
					
					
						
					
				} // else if
				
				if ( command == 1 || command == 2 ) {
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
				}
					
					
				
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
 
