//11027115_���q�� 

#include <iostream> //in out
#include <cstdlib>
#include <vector> // vector
#include <iomanip> // setw
#include <math.h> //sqrt
#include <fstream>
#include <string> 
#include <utility> // pair

#define MAX_LEN   235
#define no 0
#define oor 1
#define oand 2 

using namespace std ;

struct Token{	// �s��Ǫ�Node 
	char token = '\0' ;
	Token * next = NULL ;	// �U�@�� 
};

struct Token_or{	// �s�B��l��Node 
	char token = '\0' ;
	int num = 0 ;	// �C�ӹB��l���u������ 
	Token_or * next = NULL ;	// �U�@�� 
	Token_or * pre = NULL ;		// �e�@�� 
};

// ��Ǫ� 
Token * head = NULL ;
Token * now = NULL ;
// �B��l�� 
Token_or * Oor = NULL ;
Token_or * oorcur = NULL ;

void write() {
	
	now = head ;
	cout << "Postfix expression: " ;

	while ( now -> next != NULL ) {
		if ( now->token >= '0' && now->token <= '9' )	cout << now -> token ;	// �Ʀr�����L�X 
		else if ( now->token == ' ' )	cout << ", "  ;		// �ΪŮ�N��n�r�� 
		else if (  now->token != '+' ||  now->token != '-' ||  now->token != '*' ||  now->token != '/'){	// �B��l������ 
		
			cout << now->token ;	// ���L�X 
			if ( now->next->token != '\0' )	{	 	// �T�{�U�@�榳�F�� 
			
				if ( now -> next->token == ' ' ){ 	// �p�G�O�B��l���A�� 
													// �n�N�A���ٲ��� �ҥH�������U�@�� 
					now = now ->next ;							
					if ( now -> next-> token != '\0') 	cout << ", " ;	// �p�G�O\0 �N��O�̫�@�� ���ݭn�r���F 
				}		
			}					
		}
		now = now -> next ;		// �U�@�� 
	}
	cout << endl ;	// ���� 
}

bool legal( string input ) { // ���Ϊ���Ʀr�Ÿ� 
	for ( int i = 0 ; i < input.length() ; i++ ) {
		if ( input[i] == ' ') continue ; // �ťժ������U�@��
		if( input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && input[i] != '(' && input[i] != ')' && !( input[i] >= '0' && input[i] <= '9' ) ){
			cout << endl << "Error 1: " << input[i] << " is not a legitimate character." << endl ;
			return false ;
		} 
	}
	
	return true ;
}

bool parentheses( string input ) { // ����A���A�S���ˬd�A���������T�u���������� 
	int left = 0, right = 0 ;
	for ( int i = 0 ; i < input.length() ; i++ ) {	// �p�⥪�k�A�����ƶq 
		if ( input[i] == '(' ) left++ ;
		if ( input[i] == ')' ) right++ ;
	}
	
	if ( left != right ) {	// �ƶq�@�˥N���� 
		cout << endl << "Error 2: there is one extra open parenthesis." << endl;
		return false;
	}
	
	return true ;
}

bool is_infix( string input ) {	// �O���O���Ǫ��Φ� 
	int sth = no ; 			// �ݫe�@��O�Ʀr�٬O�[��Ÿ� 
	char tempor = '\0' ;	// �Ȧs�e�@�ӹB��l�O���� 
	
	for ( int i = 0 ; i < input.length() ; i++ ) {
		if ( input[i] == ' ' ) continue ;	// �ťո��L 
		if ( sth == no ) { 					// no �N���٨S�����T 
			if ( input[i] <= '9' && input[i] >= '0' ) sth = oand ;	// ���B�⤸ 
			else sth = oor ; 										// ���B��l 		
			continue ; 												// ����Ĥ@�Ӫ���T�᪽�����U�@�� 
		}
				
		if ( input[i] == '(' ) { //���A��
			
			tempor = input[i] ;
			if ( sth == oand && input[i-1] !='(' ) { //  �Ʀr (   ���ˤl �ӥB���O��ӬA���|�b�@�_ 
				cout << endl << "Error 3: there is one extra operand." << endl ;
				return false ;
			} 			
			
			i++ ; // �������A���k���
			 
			if ( input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' ) { // ( �Ÿ�  ���ˤl  
				cout << endl << "Error 3: there is one extra operand." << endl ;
				return false ;				
			}
			else if ( input[i] == ' ' ) continue ; // �p�G�U�@�ӬO�Ů檽���U�@���j�� 
			
			sth = oor ; // ���欰�A�����Ÿ��]��oor
			 
		}
		else if ( input[i] == ')' ) { // �k�A�� 
			tempor = input[i] ;
			
			if ( sth == oor && input[i-1] !=')' ) { //	�Ÿ� )  ���ˤl �ӥB���O��ӬA���|�b�@�_ 
				cout << endl << "Error 3: there is one extra operand." << endl ;
				return false ;
			} 			
			
			i++ ; // �������A���k���
			 
			if ( i > input.length() ) return true ; 			// �k�A�����̫�@�� 
			else if ( input[i] <= '9' && input[i] >= '0' ) { 	//	)�Ʀr  ���ˤl  
				cout << endl << "Error 3: there is one extra operand." << endl ;
				return false ;				
			}
			else if ( input[i] == ' ' ) continue ; 	// �p�G�U�@�ӬO�Ů檽���U�@���j�� 
				
			sth = oor ; 							// ���欰�A�����Ÿ��]��oor 			
			
		}
		else if ( input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' ) { // �O�B�⤸ 
			
			if ( sth == no ) { 		// �}�Y�Ĥ@�ӬO�Ÿ����� 
				cout << endl << "Error 3: there is one extra operand." << endl ;
				return false ;				
			}
			else if ( sth == oor ) { 			// �W�@�Ӥ]�O�B���s���ӬO���諸 
				if ( tempor == ')' || tempor == '(' ) continue ;	// ���D�O�A�� ) * ( ���ˤl 
				else{
					cout << endl << "Error 3: there is one extra operand." << endl ;
					return false ;	
				}		
			}
			else {
				sth = oor ; //  ���欰�A�����Ÿ��]��oor 	
			}
		}
		else sth = oand ; //  �W����B��Ÿ��i�ೣŪ�L�����O,�ҥH�O�Ʀr 
	}
	return true ;
}

void re_ans(){ // �N�̫ᵪ�צh�l���Ů���� ���|���s���ӪŮ�s�b�����D 
	now = head ;
	while( now -> next != NULL ) {
		
		if ( now ->token == ' ' ) {
			if ( now ->next ->token == ' ' ) {
				now ->next = now ->next->next ;
			}
		}
		
		now = now->next ;
	}
}

void pushoor() { // �N�B��l��J��Ǫ����פ� 
	
	if ( oorcur -> token == '(' ) { 	// �J��k�A��  ���Υ�i�h 
		if ( oorcur ->pre != NULL ) {	
			oorcur = oorcur -> pre ;	// ���|���٦��B��l �N���Щ��e�@�� 
			delete oorcur -> next ;		// ���� 	
		}
		else {
			delete oorcur ;				// �p�G�S���e�@��h�NOor��l���ܦ�NULL 
			Oor = NULL ;
			oorcur = Oor ;
		}
		
		return ; // ���� 
	}
	
	// �N�B��l��J���פ� 
	now->token = oorcur->token ; 
	now ->next = new Token ;
	now = now ->next ;
	// �õ����Ů� ��@�r�� 
	now->token = ' ' ;
	now->next = new Token ;
	now = now->next ;
	
	if ( oorcur ->pre != NULL ) {
		oorcur = oorcur -> pre ;	// ���|���٦��B��l �N���Щ��e�@�� 
		delete oorcur -> next ;		// ����
	}
	else {
		delete oorcur ;				// �p�G�S���e�@��h�NOor��l���ܦ�NULL 
		Oor = NULL ;
		oorcur = Oor ;
	}

	
}

void check( char input ){	// �ˬd�B��l���|�̭��٦��S���F�� 

	if ( oorcur == NULL ) return ;	// �S�F�赲�� 
	
	if ( input == '+' || input == '-' ){	// Ū�i+��- 
		if( 1 > oorcur-> num )	return ;	//�@������|���B��l�u�����Ǥp��+��-�� �N���� 
		else {						
			pushoor();				// �j�󵥩� �N���|������i���G�� 
			check( input ) ;		// �M��A�~���ˬd 
		}		
	}
	else if ( input == '*' || input == '/' ){	// Ū�i*��/ 
		if( 2 > oorcur-> num )	return ;		//�@������|���B��l�u�����Ǥp��*��/�� �N����
		else {
			pushoor();				// �j�󵥩� �N���|������i���G�� 
			check( input ) ;		// �M��A�~���ˬd 
		}			
	}
	
	return ;	// ���� 
}

void postfix( string input ) {	// �������� 
	head = new Token ;
	now = head ;
	
	int left = 0, right = 0 ;
	
	for ( int i = 0 ; i < input.length() ; i++ ) {
		if ( input[i] == ' ' ) continue ;
		
		if ( input[i] >= '0' && input[i] <= '9' ) { // �Ʀr������i���G 
			now->token = input[i] ;
			now->next = new Token ;
			now = now->next ;	
			if ( i == input.length()-1 ) {
				now->token = ' ' ;
				now->next = new Token ;
				now = now->next ;	
			}
			continue ;		
		}
		else if ( input[i] == '+' || input[i] == '-' ){ // �p�G�O�Ÿ���stack�� 
			
			now->token = ' ' ;
			now->next = new Token ;
			now = now->next ;	
			
			if ( Oor == NULL ){ // ���|���Ū��ɭ� 

				Oor = new Token_or ;
				oorcur = Oor ;
				
				oorcur->token = input[i] ;
				oorcur->num = 1 ;
				oorcur->next = NULL ;	
				
				continue ;								
								
			}
			else if ( 1 <= oorcur->num )	check( input[i] ) ;
			
			// �qcheck�X�Ӧ��i��ɭPOor�ONULL �ҥH�n�Anew 
			if (Oor == NULL){
				Oor = new Token_or ;
				oorcur = Oor ;
			}
			
			oorcur->next = new Token_or ;
			oorcur->next->pre = oorcur ;
			oorcur = oorcur->next ; 
						
			oorcur->token = input[i] ;
			oorcur->num = 1 ;											

		} 
		else if ( input[i] == '*' || input[i] == '/' ) {

			
			now->token = ' ' ;
			now->next = new Token ;
			now = now->next ;	
			
			if ( Oor == NULL ){ // ���|���Ū��ɭ� 

				Oor = new Token_or ;
				oorcur = Oor ;				
	
				oorcur->token = input[i] ;
				oorcur->num = 2 ;	
				oorcur->next = NULL ;
				
				continue ;								
								
			}		
			if ( 2 <= oorcur->num )		check( input[i] ) ;

			// �qcheck�X�Ӧ��i��ɭPOor�ONULL �ҥH�n�Anew			
			if (Oor == NULL){
				Oor = new Token_or ;
				oorcur = Oor ;
			}
			
			oorcur->next = new Token_or ;
			oorcur->next->pre = oorcur ;
			oorcur = oorcur->next ; 
							
			oorcur->token = input[i] ;
			oorcur->num = 2 ;
			 	
	
		}
		else if ( input[i] == '(' ) {	
	
			if ( Oor == NULL ){ // ���|���Ū��ɭ� 
				Oor = new Token_or ;
				oorcur = Oor ;					
				oorcur->token = input[i] ;
				oorcur->num = 0 ;	
				continue ;								
								
			}
			
			oorcur->next = new Token_or ;
			oorcur->next->pre = oorcur ;
			oorcur = oorcur->next ; 
												
			oorcur->token = input[i] ;
			oorcur->num = 0 ;
						
		}
		else if ( input[i] == ')' ) {
			
			now->token = ' ' ;
			now->next = new Token ;
			now = now->next ;			

			pushoor() ;
			if ( oorcur -> token == '(' ) {

				if ( oorcur ->pre != NULL ) {
					oorcur = oorcur -> pre ;
					delete oorcur -> next ;				
					
				}
				else {
					delete oorcur ;
					Oor = NULL ;
					oorcur = Oor ;
					
				}
			}
		}	
	}
	
	while( oorcur != NULL ) {		// ����Ū���F �N�B��l�M�� 
		if ( oorcur -> token == '\0' ) {
			delete oorcur ;
			Oor = NULL ;
			oorcur = Oor ;
			break ;
		}
		
		pushoor() ;		
	}	
	
	now = NULL ;
}

int main(void) {
	
	int command ;
		
	do{
		cout << endl << "* Arithmetic Expression Evaluator *" << endl ;
		cout << "* 0. QUIT                         *" << endl ;
		cout << "* 1. Infix2postfix Transformation *" << endl ;
		cout << "***********************************" << endl ;
		cout << "Input a command(0, 1): "  ;
		cin >> command ;
		cin.ignore(MAX_LEN,'\n');	
			
		switch( command ){
			case 0 :
				break ;
			case 1 :	
			
				cout << endl << "Input an infix expression: "  ;
				string input ;
				getline ( cin, input ) ;
				
				if ( !legal(input) || !parentheses( input ) || !is_infix( input )) break ;
				cout << "It is a legitimate infix expression." << endl ;	
				
				postfix( input ) ;
				re_ans() ;
				write() ;
					
				break ;
		}
		
	}while( command != 0 ) ;
} 

/*
Test
(29+101)*33/25
24*7770/(55+30*2)
(90+(70*(68-55/10)))
69/33+30*5-24/8

24*7770^(55+30*2)
(90+(70*(68-55/10))
(29+101)*33/25)
69/3++30*5-24/8

1+2*3+(4-7)*(2+1)*(5+2)+6
*/

