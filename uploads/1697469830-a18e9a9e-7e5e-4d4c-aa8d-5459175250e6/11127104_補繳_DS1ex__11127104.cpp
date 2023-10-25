// 11127104 ���R�w 
#include <iostream>
#include <fstream>
#include <string>
using namespace std ;
typedef char char5050[50][50] ;

class Maze {
	
	private : 
		int mode = 1 ; // ��ؼФΦh�ؼ� 
		char5050 map, mapOfG ; //  map�O�s�g�c���G���}�C, mapOfG�O�s���\�����| 
		int row, column, direction = 1 ; // row�O�g�c���C, column�O�g�c����, x�By�O�g�c�����Ӧ�m, direction 1 = �k, 2 = �U, 3 = ��, 4 = �W 
		int NumOfG = 1, NowOfG = 0 ; // NumOfG�O�ݭn�X�ӥؼ�, NowOfG�O�{�b���X�ӥؼ� 
		bool Stop = false ; // �O�_�����~�򨫰g�c
		//bool returnR = false ;

    public :
    	
	void setmode( int whatmode ) { // �]�wmode
		mode = whatmode ;
	}

    void load() { // Ū��� 
    	ifstream input ; // Ū��ƶi�Ӫ����� 
    	string fileName ; // �ɮצW�٪��r�� 
    	bool RightOrWrong = true ; // ��J�O�_���T 
    	do // ���ư�����J���T 
		{
			RightOrWrong = true ; // ��l�ƬO�_��J���T 
			cout << endl << "Input a file number (e.g.,101,102,103,104....):" ; // ��J�ɮצW�� 
			cin >> fileName ;
			fileName = "input" + fileName + ".txt" ; // ���ɮצW�ٲզ����㪺�r�� 
			input.open( fileName.c_str() ) ; // ���ɮצW�٦r���ন�r���}�C, �ö}���ɮ� 
			if ( input.fail() ) { // �T�{�O�_���\�}���ɮ�, �S�}���\�N��RightOrWrong�]��false��ܧ䤣���ɮ� 
				cout << endl << "File does not exist!" << endl ;
				RightOrWrong = false ;
			}
				
			if ( RightOrWrong ) { // �p�G���\����ɮ� 
				if ( mode == 2 ) { // ��ܦh�ӥؼ� 
					do { // �n�D��J�ؼмƶq, �í��ư����o��d�򤺪��ؼмƶq 
						cout << endl << "Number of G (goals):" ;
						cin >> NumOfG ;
						if ( NumOfG < 1 || NumOfG > 100 ) {
							cout << endl << "### The number must be in [1,100] ###" << endl ;
						}
						else {
							break ;  
						}
					} while(1) ;
				}
					
				input >> column >> row ; // �q�ɮ׸̿�J�g�c����B�C 
				for (  int i = 0 ; i < row ; i ++ ) { // �q�ɮ׸̿�J�g�c��map�MmapOfG 
					for (  int j = 0 ; j < column ; j ++ ) {
						input >> map[i][j] ;
						mapOfG[i][j] = map[i][j] ;
					}
				}
				
				break ;
			}
		} while(1) ;
		
		input.close() ; // �������Ū�J��y 
	}  
	
	void findGoal() { // ����findG�o�Ө禡 
		findG( 0, 0, false ) ;
	}
	
	void findG( int x, int y, bool returnR ) { // ���g�c 

		map[y][x] = 'V' ; //�g�L�����|�]��V 
	
		if ( direction == 1 ) { // ��V���V�k������ 
			
			if ( map[y][x+1] == 'E' || map[y][x+1] == 'G' ) { // �P�_�A�V�k�O�_�i�� 
				if ( map[y][x+1] == 'G' ) { // �P�_�A�V�k�O�_��G 
					NowOfG ++ ; // �{�����ؼмƥ[�@ 
					returnR = true ;
					mapOfG[y][x] = 'R' ; // �]����m�����\�����|
					if ( NowOfG == NumOfG ) { // �P�_�{�����ؼмƬO�_�F��n�D���ؼм� 
						Stop = true ; // �����~�򨫰g�c 
						return ; // ���X���h���j 
					}
				
					findG( x+1, y, returnR ) ; // �٨S�F��n�D���ؼмƴN�A�~��V�k 
					map[y][x+1] = 'G' ; // �]���W�h���j�|��G�]��V,�ҥH�n�]�^G 
				}
				else {
					findG( x+1, y, returnR ) ; // �A�V�k��E�����p 
				}
			
				if ( Stop ) { // �W�h���j�O�_�w�g�����~�򨫰g�c 
					if ( mapOfG[y][x] != 'G' ) { // �P�_����m�O�_��G 
						mapOfG[y][x] = 'R' ;  // �]����m�����\�����|
					}
				
					return ; // �^�W�h 
				}
			
			}
		
			direction = 2 ; // �V�k�����U�h���V�U 
		
		
		}
	
		if ( direction == 2 ) { // ��V���V�U������  
		
			if ( map[y+1][x] == 'E' || map[y+1][x] == 'G' ) { // �P�_�A�V�U�O�_�i�� 
				if ( map[y+1][x] == 'G' ) { // �P�_�A�V�U�O�_��G 
					NowOfG ++ ; // �{�����ؼмƥ[�@ 
					returnR = true ;
					mapOfG[y][x] = 'R' ; // �]����m�����\�����| 
					if ( NowOfG == NumOfG ) { // �P�_�{�����ؼмƬO�_�F��n�D���ؼм�  
						Stop = true ; // �����~�򨫰g�c  
						return ; // ���X���h���j  
					}
					findG( x, y+1, returnR ) ; // �٨S�F��n�D���ؼмƴN�A�~��V�U 
					map[y+1][x] = 'G' ; // �]���W�h���j�|��G�]��V,�ҥH�n�]�^G 
				}
				else {
					findG( x, y+1, returnR ) ; // �A�V�U��E�����p 
				}
			
				if ( Stop ) { // �W�h���j�O�_�w�g�����~�򨫰g�c  
					if ( mapOfG[y][x] != 'G' ) { // �P�_����m�O�_��G  
						mapOfG[y][x] = 'R' ; // �]����m�����\�����| 
					}
					return ; // �^�W�h  
				}
			}
		
			direction = 3 ; // �V�U�����U�h���V��  
		
		}

  		 if ( direction == 3 ) { // ��V���V��������   
			
			if ( map[y][x-1] == 'E' || map[y][x-1] == 'G' ) { // �P�_�A�V���O�_�i��  
				if ( map[y][x-1] == 'G' ) { // �P�_�A�V���O�_��G 
					NowOfG ++ ; // �{�����ؼмƥ[�@  
					returnR = true ;
					mapOfG[y][x] = 'R' ; // �]����m�����\�����|
					if ( NowOfG == NumOfG ) { // �P�_�{�����ؼмƬO�_�F��n�D���ؼм�   
						Stop = true ; // �����~�򨫰g�c     
						return ; // ���X���h���j   
					}
					findG( x-1, y, returnR ) ; // �٨S�F��n�D���ؼмƴN�A�~��V�� 
					map[y][x-1] = 'G' ; // �]���W�h���j�|��G�]��V,�ҥH�n�]�^G 
				} 
				else {
					findG( x-1, y, returnR ) ; // �A�V����E�����p 
				}
				if ( Stop ) { // �W�h���j�O�_�w�g�����~�򨫰g�c 
					if ( mapOfG[y][x] != 'G' ) { // �P�_����m�O�_��G   
						mapOfG[y][x] = 'R' ;  // �]����m�����\�����| 
					}
					return ; // �^�W�h
				}
			}
		
			direction = 4 ; // �V�������U�h���V�W 
		
		}
	
		if ( direction == 4 ) { // ��V���V�W������   
			
			if ( map[y-1][x] == 'E' || map[y-1][x] == 'G' ) { // �P�_�A�V�W�O�_�i��  
				if ( map[y-1][x] == 'G' ) { // �P�_�A�V�W�O�_��G  
					NowOfG ++ ; // �{�����ؼмƥ[�@   
					returnR = true ;
					mapOfG[y][x] = 'R' ; // �]����m�����\�����|
					if ( NowOfG == NumOfG ) { // �P�_�{�����ؼмƬO�_�F��n�D���ؼм�   
						Stop = true ; // �����~�򨫰g�c 
						return ; // ���X���h���j 
					}
					findG( x, y-1, returnR ) ; // �٨S�F��n�D���ؼмƴN�A�~��V�W 
					map[y-1][x] = 'G' ; // �]���W�h���j�|��G�]��V,�ҥH�n�]�^G
				} 
				else {
					findG( x, y-1, returnR ) ; // �A�V�W��E�����p 
				}
			
				if ( Stop ) { // �W�h���j�O�_�w�g�����~�򨫰g�c  
					if ( mapOfG[y][x] != 'G' ) { // �P�_����m�O�_��G 
						mapOfG[y][x] = 'R' ; // �]����m�����\�����|  
					}
					return ; // �^�W�h
				}
			}
			
		    
			if ( map[y][x+1] == 'E' || map[y][x+1] == 'G' ) { // �]���w�g�����k�U���W�@�Ӵ`��, �ҥH�A�`���@��, �q�k�}�l, ���P�_�O�_�i�V�k 
				direction = 1 ; // ��V�]���k 
				if ( map[y][x+1] == 'G' ) { // �P�_�A�V�k�O�_��G 
					NowOfG ++ ; // �{�����ؼмƥ[�@ 
					returnR = true ;
					mapOfG[y][x] = 'R' ; // �]����m�����\�����|
					if ( NowOfG == NumOfG ) { // �P�_�{�����ؼмƬO�_�F��n�D���ؼм� 
						Stop = true ; // �����~�򨫰g�c 
						return ; // ���X���h���j 
					}
				
					findG( x+1, y, returnR ) ; // �٨S�F��n�D���ؼмƴN�A�~��V�k 
					map[y][x+1] = 'G' ; // �]���W�h���j�|��G�]��V,�ҥH�n�]�^G 
				}
				else {
					findG( x+1, y, returnR ) ; // �A�V�k��E�����p 
				}
				
				if ( Stop ) { // �W�h���j�O�_�w�g�����~�򨫰g�c 
					if ( mapOfG[y][x] != 'G' ) { // �P�_����m�O�_��G  
						mapOfG[y][x] = 'R' ; // �]����m�����\�����|  
					}
	
					return ; // �^�W�h 
				}
			}
		
			else if ( map[y+1][x] == 'E' || map[y+1][x] == 'G' ) { // �P�_�O�_�i�V�U 
				direction = 2 ; // ��V�]���U 
				if ( map[y+1][x] == 'G' ) { // �P�_�A�V�U�O�_��G 
					NowOfG ++ ; // �{�����ؼмƥ[�@ 
					returnR = true ;
					mapOfG[y][x] = 'R' ; // �]����m�����\�����|
					if ( NowOfG == NumOfG ) { // �P�_�{�����ؼмƬO�_�F��n�D���ؼм�  
						Stop = true ; // �����~�򨫰g�c   
						return ; // ���X���h���j  
					}
					findG( x, y+1, returnR ) ; // �٨S�F��n�D���ؼмƴN�A�~��V�U 
					map[y+1][x] = 'G' ; // �]���W�h���j�|��G�]��V,�ҥH�n�]�^G 
				}
				else {
					findG( x, y+1, returnR ) ; // �A�V�U��E�����p 
				}
				if ( Stop ) { // �W�h���j�O�_�w�g�����~�򨫰g�c 
					if ( mapOfG[y][x] != 'G' ) { // �P�_����m�O�_��G 
						mapOfG[y][x] = 'R' ; // �]����m�����\�����| 
					}
	
					return ; // �^�W�h 
				}
			}
		
			else if ( map[y][x-1] == 'E' || map[y][x-1] == 'G' ) { // �P�_�O�_�i�V�� 
				direction = 3 ; // ��V�]���� 
				if ( map[y][x-1] == 'G' ) { // �P�_�A�V���O�_��G 
					NowOfG ++ ; // �{�����ؼмƥ[�@  
					returnR = true ;
					mapOfG[y][x] = 'R' ; // �]����m�����\�����|
					if ( NowOfG == NumOfG ) { // �P�_�{�����ؼмƬO�_�F��n�D���ؼм�   
						Stop = true ; // �����~�򨫰g�c      
						return ; // ���X���h���j   
					}
					findG( x-1, y, returnR ) ; // �٨S�F��n�D���ؼмƴN�A�~��V��  
					map[y][x-1] = 'G' ; // �]���W�h���j�|��G�]��V,�ҥH�n�]�^G 
				} 
				else {
					findG( x-1, y, returnR ) ; // �A�V����E�����p 
				} 
				
				if ( Stop ) { // �W�h���j�O�_�w�g�����~�򨫰g�c 
					if ( mapOfG[y][x] != 'G' ) { // �P�_����m�O�_��G 
						mapOfG[y][x] = 'R' ; // �]����m�����\�����| 
					}
	
					return ; // �^�W�h 
				}
			}
			
		}
		
		if ( returnR ) {
			if ( mapOfG[y][x] != 'G' ) { // �P�_����m�O�_��G 
				mapOfG[y][x] = 'R' ; // �]����m�����\�����| 
			} 
		}
		//cout << "_---------------" ;
		return ; // �^�W�h 
	}
	
	void ClearMaze() { //��l�Ƽƭ� 
	    Stop = false ;
	    direction = 1 ; // ��V�@�}�l���V�k 
	    NowOfG = 0 ;
	    NumOfG = 1 ;
		for ( int i = 0 ; i < 50 ; i++ ) { // �M�Űg�c�Φ��\���| 
			for( int j = 0 ; j < 50 ; j ++ ) {
				map[i][j] = '0' ;
				mapOfG[i][j] = '0' ;
			}
		}
	}
	
	void ShowMazeV() { // ��X���L�����| 
		for ( int i = 0 ; i < row ; i ++ ) { // ��X���L�����|�� 
			for ( int j = 0 ; j < column ; j ++ ) {
				cout << map[i][j] ;
			}
		
			cout << endl ;
		}
	} 
	
	void ShowMazeR() { // ��X���\�����| 
		cout << endl ;
		for ( int i = 0 ; i < row ; i ++ ) {
			for ( int j = 0 ; j < column ; j ++ ) {
				cout << mapOfG[i][j] ;
			}
	
			cout << endl ;
		}
	}
	
	bool IsSuccess() { // �^�ǬO�_���\���Ҧ��ؼ� 
		return Stop ;
	}
} ;

int main() {
	int command = 0 ; // �ϥΪ̪���J���ܼ� 
	
	do // ���ư��檽��ϥΪ̵������� 
	{
		Maze aMaze ;
		// string fileName ; // �ɮצW�٪��r�� 
		
		cout << endl << "*** Path Finding ***" ; // �ϥΪ̤��� 
		cout << endl << "* 0.Quit           *" ;
		cout << endl << "* 1.One goal       *" ;
		cout << endl << "* 2.More goal      *" ;
		cout << endl << "********************" ;
		cout << endl << "Input a command( 0, 1, 2 ):" ;
		cin >> command ; // ��J�ʧ@ 
		
		aMaze.setmode( command ) ; // �]�wmode 
			
		if ( command == 1 || command == 2 ) { // ����ʧ@��1��2�����p 
			
			aMaze.load() ; // Ū����� 
			
			aMaze.findGoal() ; // ���g�c 

			aMaze.ShowMazeV() ; // ��X���L�����| 
			if ( aMaze.IsSuccess() ) { // �P�_�O�_�����Ҧ��ؼ� 
				aMaze.ShowMazeR() ; // ��X���\�����| 
			}
			
			aMaze.ClearMaze() ; // ��l�Ƹ�� 
			
			
		}
		else if ( command == 0 ) {
			break ; // ������� 
		}
		else {
			cout << endl << "Command does not exist!" << endl ;	// ��X���ާ@���s�b 
		}
	
	} while(1) ;
}

