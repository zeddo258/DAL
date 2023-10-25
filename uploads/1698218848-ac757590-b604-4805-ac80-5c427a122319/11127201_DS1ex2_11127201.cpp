// 11127201 ���~�� 
#include<iostream> 
#include<string>
#include<cstdlib>

#define MAX_LEN 255  // maximum string length 
using namespace std ;

class Node {
	
	public:
		
		string *stack ;
		string formula = "", error1char = ""  ;
		int num = -1 ;
		int number = 0, plusCount = 0, minusCount = 0, multiplyCount = 0, divideCount = 0;
		int totalbrackets = 0, leftbrackets = 0, rightbrackets = 0 ;
		bool isdigit = false, istogether = false, error3 = false ;
		
		struct SequenceToken {
			string element ;  // �r�Ť��� 
			SequenceToken *next ;
		};
		
		SequenceToken* head = NULL ; // ��F����C�Y 
		SequenceToken* walk = NULL ; // ��F����C�M�� 
		SequenceToken* tail = NULL ; // ��F����C���� 

		void push( string element ) { // �N���r�걵�b��Ǫ�Link�� 		
			if (tail == NULL) { // �O�Ū����p�Ыطs�`�I 
            	tail = new SequenceToken;
            	head = tail;
        	} // if 
			else {
           		tail->next = new SequenceToken;  // �b���ڳЫطs�`�I 
            	tail = tail->next; 
        	} // else 
        	
        	tail->next = NULL;
       		tail->element = element;
		} // push()
		
		struct SequenceSybol {
			int Syboljudge = 0 ; // �Ÿ����� 
			string element ; // �Ÿ����� 
			SequenceSybol *next ;  
		};
				
		SequenceSybol* headsy = NULL ; // �Ÿ���C�Y 
		SequenceSybol* tailsy = NULL ; // �Ÿ���C��  
		SequenceSybol* walksy = NULL ; //�Ÿ���C�M�� 


		void Sybolpush( string element ) { // �N�ާ@�r�Ū��r�걵�b�Ÿ���Link�� 
			tailsy->next = new SequenceSybol ;
			tailsy = tailsy->next ;
			tailsy->next = NULL ;
			tailsy->element = element ;  
			tailsy->Syboljudge = Sybol( element ) ; // �w�q�Ÿ��j�p  
		} // Sybolpush()
		
		string Sybolpop() { // ���XLink���̫�@�� (���X�̫�@�Ӿާ@��) 
			string temp = tailsy->element ; // �����̫�@�Ӫ��Ÿ� 
			walksy = headsy ; // �N�M���]�b�Y���L����] 
			
			if (walksy != NULL && walksy->next != NULL) { // ����u���@�Ӥ����ά��� 
    			while (walksy->next->next != NULL) 
        			walksy = walksy->next; // walk����tail���e�@�� 
    
    			delete tailsy; // �R���̫�@�� 
    			walksy->next = NULL; // �R�����ӳ]��NULL  
    			tailsy = walksy; // tail����s��Link�̫�@��
			} // if 		
			
			return temp ;	
		} // Sybolpop()
		
		void Transform() { // �N�����ର���
			if ( tailsy == NULL ) { // �Ÿ�Link���O�Ū��A���]�@���ݩʬ� 0 ���r�� 
				tailsy = new SequenceSybol ;
				headsy = tailsy;
				walksy = tailsy ;
				tailsy->next = NULL ;
				tailsy->Syboljudge = 0; // �S������Ÿ��]0 
				tailsy->element = "" ; // �s�`�I�������]�m 
			} // if 
			for ( int i = 0 ; i < formula.length() ; i++ ) { // �N�@���}�C���ȱ���Link�� 
				if ( stack[i].empty() ) break ; // ��@���}�C�I��Ű}�C�N���U�� 
			
				if ( IsSybol( stack[i] ) ||  stack[i] == "(" || stack[i]== ")" ) { // �O�Ÿ� 

					if ( Sybol( stack[i] ) == 0 ) Sybolpush( stack[i] ) ; // �I�� "(" �N�����K�[�Ÿ�����@�s���� 
					else if ( Sybol( stack[i] ) == 3 ) { // �I�� ")" �N���X�Ÿ�Link�����F�誽��� "(" ���X �åB��J���Link�� 
						while ( tailsy->Syboljudge != 0 ) push( Sybolpop() ) ; // ���X "("�᪺�Ҧ��Ÿ� �åB��J���Link�� 
						Sybolpop() ; // �N "(" ���X 
					} // else if 
					else if ( Sybol( stack[i] ) > tailsy->Syboljudge ) Sybolpush( stack[i] ) ; // ��Ÿ��ݩʪ��ƭȤ�e�@�Ӥj�N�N���|�W�h 
					else { // �Ÿ��ݩʪ��ƭȸ�e�@�Ӥ@�ˤj�Τ���p�N���X�Ÿ������F�讳�쩳������ �åB��J���Link�� 
						while ( ( tailsy->Syboljudge >= Sybol( stack[i] ) - 1 ) && tailsy->Syboljudge != 0 ) push( Sybolpop() ) ; // ���X�����᪺�Ҧ��Ÿ� �åB��J���Link�� 
						Sybolpush( stack[i] ) ; // �N�@�ˤj�Τ���p���Ÿ���J�Ÿ���Link�� 
					} // else 

				} // if 
				else {
					if ( tail == NULL ) { // �� tail Link���O�Ū����L�s���Ŷ� 
						tail = new SequenceToken ;
						head = tail;
						walk = tail ;
						tail->next = NULL ;
						tail->element = stack[i] ;
					} // if 
					else push( stack[i] ) ; // ��J��Ǥ� 
				} // else if 
			} // for  
			
			while ( headsy->next != NULL ) push( Sybolpop() ) ; // �N�ѤU���Ÿ�����J���Link�� 
		} // Transform()
		
    	void Postfix() { // ��X���e��� 
    		while ( walk != NULL ) {
	    		cout << walk->element ;
	    		if ( walk->next != NULL ) cout << ", " ;
	    		walk = walk->next ;
			} // while
			
			cout << endl << endl ;
		} // Postfix()
		
		void *Setstack () {  // �Ыؤ@�ӰʺA�}�C�Ӱ��x�s  
			stack = new string[formula.length()] ;  // �x�s��F���o�Ÿ���Ʀr 
		} // Setstack() 

		void GetToken() { // �N��J���r������U�ӼƦr�M�Ÿ� 
			for ( int i = 0 ; i < formula.length() ; i++ ) {
				// �M����J���l���C�ӲŸ� 
				if ( !formula.substr( i, 1 ).empty() && ( formula.substr( i, 1 ).compare( " " ) != 0 ) ) {
					//�ˬd��e�Ÿ����O�Ū��B���O�Ů� 
					if ( Isdigit(formula.substr(i, 1)) ) isdigit = true ; // �ݦ���O�_���Ʀr 
					else isdigit = false ;  
					
					if ( istogether ) istogether = false ;  // �B�z�L 
					else if ( !isdigit ) num++ ; // �O�Ÿ��N�n�����]������O�Ʀr 
					else if ( num == -1 ) num++ ; // �O�Ʀr���ɭԨåB�Ʀr�b�Ĥ@�ӭn�N -1 �ܬ� 0 
					
					stack[num] = stack[num] + formula.substr( i, 1 ) ; //��e�r�ųs�����x�sstack���۹��m   
					if ( !isdigit ) {
						num++;
						istogether = true ; // ��O�Ÿ����ɭԪ�������U�Ӱ}�C �A��ܤw�B�z 
					} // if 
				} // if 
			} // for
		} // GetToken() 
			
		int Sybol( string element ) { // �ݦ��r��O���ӲŸ� 
 			if (element == "+" || element == "-") return 1; //(+-�@�_��)
        	if (element == "*" || element == "/") return 2;//(*/�@�_��)
        	if (element == "(") return 0;
        	if (element == ")") return 3;
		} // Sybol()
		
		bool IsSybol( string element ) { // �ݦ��O���O�Ÿ��� 
 			if (element == "+" || element == "-" || element == "*" || element == "/" ) return true;
			else return false ;
		} // IsSybol()
		
		
		int CountSybol() { // �����C�ӲŸ��M�Ʀr�ƶq �ǰe���~�T�� 
			bool stop = false ;
			bool special = false ;
            for ( int i = 0 ; i < formula.length() ; i++ ) {
                if ( stack[i].empty() ) break ; // ���l�O�Ū� 
                
                if ( Isdigit( stack[i] ) ) number++ ; // �O�Ʀr 
                else if ( stack[i] == "+"  ) plusCount++ ;  // �O�[�� 
                else if ( stack[i] == "-"  ) minusCount++ ; // �O� 
                else if ( stack[i] ==  "*" ) multiplyCount++ ; //�O���� 
                else if ( stack[i] ==  "/" ) divideCount++ ; //�O���� 
                else if ( stack[i] == "("  ) { 
                    leftbrackets++;//�O���A�� 
					totalbrackets++ ; // �A���`�ƶq 
					special = true ; /// �����A�� 
                    if ( i != formula.length() - 1 ) {
                    	// �ˬd���A���᭱�X�k�� 
                        if (  IsSybol( stack[i+1] )  || stack[i+1] == ")")
							  	error3 = true ; //�A���ᤣ��O�B��Ÿ��Ϊ̥k�A��  ���O()��(-3) 
                    } // if 
                } // else if
                else if ( stack[i] ==  ")"  ) {
                	if ( !special ) return 3; // �O)3(�����p 
                	
                    rightbrackets++; // �O�k�A�� 
					totalbrackets-- ; // ����[�k��� 
                    
                    if ( i != 0 ) {
                    	// �ˬd�k�A���᭱�X�k�� 
                        if (  IsSybol( stack[i-1] ) || stack[i-1] == "(" ) 
							error3 = true ; //�A���ᤣ��O�B��Ÿ��Ϊ̥k�A�� ���O(11-)
                    } // if
                
                } // else if 
                else if ( !stop ){
                    // �J���O�Ʀr�]���O�B��Ÿ� 
					error1char = stack[i]; // ���~�Ÿ� 
					stop = true ;  // �����ˬd 
				} // else if 
            } // for
            
            
       		if ( error1char[0] != '\0' ) return 1; // �ݦ��S�����O�B��Ÿ����F�� 
         	else if (leftbrackets > rightbrackets) return 2; // �ݥ��A�����S���j��k�A��  
        	else if (leftbrackets < rightbrackets ) return 3;// �ݥk�A�����S���j�󥪬A��  
        	else if (error3) return 4;  
        	else if (number - 1 < (plusCount + minusCount + multiplyCount + divideCount)) return 5; // �p�G�ާ@���Ƥ֩�B��Ÿ���-1  �B��Ÿ���Ʀr�h   
        	else if (number - 1 > (plusCount + minusCount + multiplyCount + divideCount)) return 6; // �p�G�B��Ÿ��֩�ާ@���Ʀr-1  �Ʀr��B��Ÿ��h 
 			else return 7; // ���T�� 
        } // CountSybol()
        
        
        void Output( int errorCode ) { // ��X 
            switch (errorCode) {
            case 1: // �s�b���X�k�r�� 
                cout << "Error 1: " << error1char << " is not a legitimate character." << endl ;
                break;
            case 2: // �s�b�h�l���A�� 
                cout << "Error 2: There is one extra open parenthesis." << endl ;
                break;
            case 3: // �s�b�h�l�k�A��  
                cout << "Error 2: There is one extra close parenthesis." << endl ;
                break;
            case 4: // �A�������X�k 
                cout << "Error 3: It is not infix in the parentheses." << endl;
                break;
            case 5: // �s�b�h�l�B��Ÿ� 
                cout << "Error 3: There is one extra operator." << endl ;
                break;
            case 6:  // �s�b�h�l�ާ@�ƪ��Ʀr 
                cout << "Error 3: There is one extra operand." << endl ;
                break;
            case 7: // �����T�L�X�� 
                cout << "It is a legitimate infix expression." << endl;
            	cout << "Postfix expression: ";
                Postfix(); // �L�X��� 
                break;
        	} // switch
        } // Output()
        
        void Reset() { // ��l�� 
            num = -1 ;
            number = 0, plusCount = 0, minusCount = 0, multiplyCount = 0, divideCount = 0;
			totalbrackets = 0, leftbrackets = 0, rightbrackets = 0;
            isdigit = false, istogether = false, error3 = false ;
            formula = "", error1char = "" ;
            
            // ����ʺA���t���s 
            delete[] stack; 
            stack = NULL ;
            
            // ����`�I 
            while (head != NULL) {
        		SequenceToken* temp = head;
        		head = head->next;
        		delete temp;
   	 		} //while
   	 		
   	 		head = NULL, walk = NULL, tail = NULL;
    		headsy = NULL, tailsy = NULL, walksy = NULL;
        } // Reset()
		
		bool Isdigit( string num ) { // �P�_�Ʀr 
        	int length = num.length();
        	for (int i = 0; i < length; i++) {
            	if (num[i] < '0' || num[i] > '9') {
                	return false;
           	 	} // if 
        	} // for
        	
       		return true;
		} //  Isdigit
		
		void Operate() { // ���J�Ȭ� 1 
			getline( cin, formula ) ; // Ū���l 
			Setstack() ; // �Ыؤ@�ӰʺA�}�C�Ӱ��x�s 
			GetToken() ; // �N��J���r������U�ӼƦr�M�Ÿ�
			int errorCode = CountSybol(); // ���άݦ����~�P�_ 
			if (  errorCode == 7 ) Transform(); // �ഫ����� 
			Output( errorCode ) ; 
			Reset() ; // ���m 
		} // operate()
};


int main(void) {
	Node node ;
	int command = 0 ; // user command
	string infixS ;
 	do {
		cout << endl << "*Arithmetic Expression Evaluator *" ;
		cout << endl << "*0. QUIT                         *" ;
		cout << endl << "*1. Infix2postfix Transformation *" ;
		cout << endl << "**********************************" ;
		cout << endl << "Input a choice(0, 1):" ;
		cin >> command;  // get the command(��o���O)
		
		cin.ignore( MAX_LEN, '\n' ) ; // clear the input buffer
		
		switch ( command ) {
			case 0:break;
			case 1:
					cout << endl << "Input an infix expression:" ;
            		node.Operate() ;									   
					break ;
			default: cout << endl << "Command dose not exist!" 	<< endl;								
		} // end switch
	} while( command != 0 ) ;
	
	node.stack = NULL ;
	system( "pause" ) ; // pause the execution �Ȱ����� ( system ����ާ@�R�O�Apause �Ω�Ȱ����浥��J�A����|��ܮפU���N���~�� )
	return 0 ;
} // end main
