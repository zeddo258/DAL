// 11127207 ������

# include <iostream>
# include <string> 
# include <cstdlib>
# include <new>

# define MAX_LEN 255

using namespace std ;


struct listNode {  // �x�s����r������23+2�ܦ�����23,+,2�� 
	string c ;  
	struct listNode *next ;	// structure of each node in list
} ;

class expLIST {  // �B�z�r��O�_�����Ǧ����D�n�{�� 
	bool repeat ;	// ���L���ƪ��B��� 
	listNode*head,*tail ; // only two data members 
	
public :
	expLIST() { //��l�� 
		head = NULL ;
		tail = NULL ;
		repeat = true ;
	} // end expList initializer

	listNode* gethead() {
		return head;
	} 
	
    void insert( string ch ) { //�إ߫��Ц�C 
    	
        listNode * newNode = new listNode ; // �Ыث��Шö�J�F�� 
        newNode -> c = ch ;
        newNode -> next = NULL ;
        
        if ( head == NULL ) { // �إ߫��Ъ��Y 
            head = newNode;
            tail = newNode;
        } // if
		else {
			if ( tail -> c == "+" || tail -> c == "-" || tail -> c == "*" || tail -> c == "/" ) { 
				if ( ch == "+" || ch == "-" || ch == "*" || ch == "/" ) { //�ˬd���S�� ++ +-�������~ 
					repeat = false ;
					cout << "Error 3: there is one extra operator."	;
				} // if
				
			} // if
		
            tail -> next = newNode ;
            tail = newNode;
        }
    }

	bool allRight() { // ��^�ˬd�X�����~ 
		if ( repeat == true && Check() == true ) { // ���L���ƩΦh�l���B��ũιB��l 
			return true ;
		}
		else {
			return false ;
		}
		
	} // allRight()
	
	bool Check() { // �ˬd���L���ƩΦh�l���B��ũιB��l  
		
		listNode * check = head ; // �q�Y�ˬd������ 
		while ( check -> next != NULL ) {
			string save = check -> c ;
			if ( save != "+" && save != "-" && save != "*" && save != "/" && save != "(" && save != ")" ) {
				if ( check -> c == "(" ) {
					cout << "Error 3 : there is one extra operand." << endl ;
					return false ;
				} // if
					
			} // if
			else if ( save == ")" ) {
				if ( check -> c == "+" && check -> c == "*" && check -> c == "/" && check -> c == "-" ) {
					cout << "Error 3 : there is one extra operand." << endl ;
					cout << check -> c << endl ;
					return false ;
				} // if
				
			} // else if
			
			check = check -> next ;
		}	// while
		
		if ( check -> c == "+" || check -> c == "/" && check -> c == "*" && check -> c == "-" ) {
			cout << "Error 3 : there is one extra operator." << endl ;
			return false ;
		}
		else
			return true ;
	} // Check()
	
	bool isEmpty() {  // decide whrith list is empty
		listNode * check = head ; // �q�Y�ˬd������ 
		int length = 0 ;
		while ( check != NULL ) {
			length++ ;
			check = check -> next ;
		}	// while
		
		if ( length == 0 ) {
			cout << "Error 3: there is one extra operator."<< endl ;
			return false ;
		} // if
		else 
			return true ;
			
	} // end expList:: isEmpty
	
	bool  isBalanced() { // �ˬd�O�_���۵������k�A�� 
		int left = 0 ;
		int right = 0 ;
		listNode * check = head ; // �q�Y�ˬd������  
		while ( check != NULL ) {
			if ( check -> c == "(" )
				left = left + 1 ;
			else if ( check -> c == ")" )
				right = right + 1 ;
			check = check -> next ;
		} // while
		
		if ( left > right ) { // ���A���h��k�A�� 
			cout << "Error 2: there is one extra open parenthesis." << endl ;
			return false ;
		} // if
		else if ( right > left ) { // �k�A���h�󥪬A�� 
			cout << "Error 2: there is one extra close parenthesis." << endl ;
			return false ;
		} // else if
		else 
			return true ;
		
		
	} // end isBalanced()
	
	void clear() { // clear up the entire list
	
		listNode * current = head ;
    	while (current != NULL ) {  
        	listNode * temp = current;
        	current = current -> next;
        	delete temp;
    	} // while
    	
    	head = NULL ;	 // �M�Ÿ�ƥH�K�y��memory leak 
	} // clear()
	
	
};

class expStack {  // �B�z���|�M��ᶵ�� 
	struct theList{ // ���G������ 
		string c ;
		struct theList *next ;	
	};
	
	struct save{ // �Ȧs�B��Ū����� 
		string ch ;
		struct save *next ;
	};

theList *first, *second ;
save *top, *end;

public:	
    expStack() { // ��l�� 
		first = NULL ;
		second = NULL ;
		top = NULL ;
		end = NULL ;   
    }
    

	void push( string x ) { // �إ߭n�L�X���ᶵ�������Шö�J 
        theList * newNode = new theList ;
        newNode -> c = x ;
        newNode -> next = NULL ;
        
		if ( first == NULL ) {
            first = newNode;
            second = newNode;
        } // if
		else {
            second -> next = newNode ;
            second = newNode;
        } // else
        
	} // push
	
	void push2( string x ) { // �s�B��Ū� 
        save * newNode = new save ;
        newNode -> ch = x ;
        newNode -> next = NULL ;
        
		if ( top == NULL ) {
            top = newNode;
            end = newNode;
        } // if
		else {
            end -> next = newNode ;
            end = newNode;
        } // else
        
	} // push
	
	int getPriority( string op ) { // �ˬd�u���� 
    	if (op == "*" || op == "/" )
        	return 2;
    	else if (op == "+" || op == "-" )
        	return 1;
    	return 0;
	}
	
	bool isEmpty() { // �ˬd���Ц�C�O�_���� 
		
		if( top == NULL ) {
			return true ;
		} // if
		else
			return false ;
		
	} // isEmpty()
	
	string getTop() { // ����Ц�C�̧��ݪ����� 
		save *temp = top ;
		if ( temp -> next == NULL ) {
			return temp -> ch ;
		} // if
		
		else {
			while ( temp -> next != NULL ) {
				temp = temp -> next ;
			} // while
			
			return temp -> ch ;
		}
		
		
	} // getTop()
	
	void deleteTop() { // �R���̧��ݪ����� 
		save *temp = top ;
		if ( temp == NULL ) {
			return ;
		}
		
		if ( temp -> next == NULL ) {
			delete temp ;
			top = NULL ;
			end = NULL ;
		} // if
		
		else {
			save* previous = NULL ;
			while ( temp -> next != NULL ) {
				previous = temp ;
				temp = temp -> next ;
			} // while
			
			delete temp ;
			previous -> next = NULL ;
			end = previous ;
		}
		
	} // deleteTop()
	
	void turnToPostfix( listNode *temp ) {  // ��������ᶵ�� 
		cout << "It is a legitimate infix expression." << endl ;
		
		while ( temp != NULL ) { // �ˬd 
			if ( temp -> c != "+" && temp -> c != "-" && temp -> c != "*"
				&& temp -> c != "/" && temp -> c != "(" && temp -> c != ")" ) { // �p�G�O�B��l������J���G���Ф� 
        		push( temp -> c ) ;	
			} // if
			else if (temp -> c == "+" || temp -> c == "-" || temp -> c == "*" || temp -> c == "/" ) { // ���B��� 
				if ( isEmpty() == true ) { // �Ȧs�B��Ū����ШS�F�� 
					push2( temp -> c ) ;
				} // if 
				else if ( isEmpty() != true && getPriority( getTop() ) < getPriority( temp -> c ) ) { // �g�@�Ө��̤W�誺function
					push2( temp -> c ) ; // ���F��B�s�B��ū��г̧����u���פp��ثeŪ�J���B��� 
				} // else if
				else if( isEmpty() != true  && getPriority( getTop() ) >= getPriority( temp -> c ) ) { // �ˬd���󤣷|�]�i�o�� 
					push( getTop() ) ; // ���F��B�s�B��ū��г̧����u���פj�󵥩�ثeŪ�J���B��� 
					deleteTop() ;      // �B��̧��ݫ��B��żu�X ����pop()�Mtop() 
					push2( temp -> c ) ;
				} // else
				
			} // else if
			else if ( temp -> c == "(" ) { // �O(�N������J�s�B��Ū����� 
				push2( temp -> c ) ;
			} // else if
			else if ( temp -> c == ")" ) { //������۹�����(���_��B��ū��и̪��F��u�X 
				
				while ( getTop() != "(" ) {
					if ( isEmpty() != true ) {
						push( getTop() ) ;
						deleteTop() ;
					} // if
					
				} // while
				
				if ( getTop() == "(" ) { // ���۹�����( �çR�� 
					deleteTop() ;
				} // if
				
			} // else if
			
			temp = temp -> next ; 
		} // while
		
		if ( isEmpty() != true ) { // ��Ѿl����J���G���� 
			while ( isEmpty() != true ) {
				push( getTop() ) ;
				deleteTop() ;
			} // while
			
		} // if
		
	} // turnToPostfix()	
	
	void Print() { // �L�X���G 
		theList * current = first ;
		while ( current != NULL ) {
			cout << current -> c ;
			if ( current -> next != NULL )
				cout << "," ;
			current = current -> next ;	
		} // while
		
	} // Print()
	
	void Clear() { // �R�����G���Ъ����e 
		theList * current = first ;
    	while ( current != NULL ) {  
        	theList * temp = current;
        	current = current -> next;
        	delete temp;
    	} // while
    	
    	first = NULL ;	 // �M�Ÿ�ƥH�K�y��memory leak 	
	} // Clear()
	
}; // expStack
	



int main( void ) {
	int command = 0 ; // use command
	bool character = true ; // ����~�� 
	expLIST List ;  
	
	do {
		character = true ;
		string infixS = "" ; 
		string token = "" ;
		int x = 0 ;
		cout << endl << "* Arithmetic Expression Evaluator*" ;  //�ϥΪ̬ݨ쪺���O 
		cout << endl << "* 0.QUIT                         *" ;
		cout << endl << "* 1.Infix2postfix Transformation *" ;
		cout << endl << "**********************************" ;
		cout << endl << "Input a choice(0 , 1): " ;
		cin >> command ;
		cin.ignore( MAX_LEN, '\n' ) ;
		
		switch (command) {	
			case 0 : break ;
			case 1 :
				cout << endl << "Input an infix exression: " ;  
				getline(cin, infixS) ; // Ū���B�⦡ 
				
				for ( size_t i = 0; i < infixS.length(); i++ ) {  // ��r���r�� 
					char ch = infixS[i];
					if ( ch >= '0' && ch <= '9' ) {  // ��J�ɩw�q 
						token = token + ch ;  // �O�Ʀr�N���x�s�b�r�� 
					} // if
					else if ( ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '(' || ch == ')' ) { // �ˬd�O�_�����ŦX���F�� 
						if ( token != "" ) // ���Ʀr�r�����J 
							List.insert( token );
						token = ch ;
						List.insert( token ); // ��J�B��� 
						token = "" ;
					} // else if
					else if ( ch == ' ' ) // do nothing 
						x = x + 1 ; 
					else {
						cout << "Error 1 " << ch << " is not a legitmate character." << endl ; // �ˬd�O�_�����X�k���r�Ŧb�r�ꤤ 
						character = false ; 
					} // else
					
				} // for
				
				
				if ( token != "" ) // �r����ƬO ) �� 
					List.insert( token );  
       			
				if ( List.isEmpty() && List.isBalanced() 
					  && List.allRight() && character == true ) { // �T�{�B�⦡�����S���D 
					  	listNode *temp = List.gethead() ; // ���o�ˬd�ɰ��n�����Ъ��Y 
					 	expStack list2 ;
						list2.turnToPostfix( temp ) ; // �ন�ᶵ�� 
						list2.Print() ; // �L�X���G 
						cout << endl ;  
						list2.Clear() ; // �M�ū��� 
						List.clear() ; // �M�ū��� 
					}  // end if
					
				else { // �J����~���p�M���쵲��C 
					List.clear() ;
				}
				
				break ;
				
				default : cout << endl << "Command does not exist!" << endl ;
					
		} // end switch
		
	} while ( command != 0 ) ;
	
	system( "pause" ) ;
	return 0 ;
	
} // main
