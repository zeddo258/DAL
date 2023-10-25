#include<string>
#include<cstdlib>
#include<iostream>
#include<new>


#define MAX_LEN 255


using namespace std ;


// T�i�b�ŧiexpLIST�o��class��object�ɦA�w�q���Y��variable 
template <class T>

//  expLIST�Ψ��x�s�����n�����Ǧ��H�Ϋ�Ǧ� 
class expLIST {
	
	private:

		// �x�s�ܼƸ�ƪ��`�I 
		struct listNode {
			T value ;
			listNode *next ;
		};
	
		// �Y���`�I��pointer 
		listNode *head, *tail ;
	
	public:
		
		
		expLIST(): head(NULL), tail(NULL){  // constructor and initialize head, tail
		}

		// �T�{��object����ƬO�_���� 
		bool isEmpty() const {
			if ( head == NULL )
				return true ;
			else 
				return false ;
			
			// return head == NULL
				
		} // isEmpty()
		
		// �[�@�ӷs��value�`�I�i�ӳo��list 
		void append( const T inValue ) {
			try {
				if( head == NULL) {
					
					head = new listNode ;
					head->value = inValue ;
					head->next = NULL ;
					tail = head ;
					
				} // if( head == NULL) 
				else {
					tail->next = new listNode ;
					tail = tail->next ;
					tail->value = inValue ;
					tail->next = NULL ; 
				}
			} // try
			catch(std::bad_alloc& ba){

				std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl ;

			} // catch()
		} // append()
		
		// ���ohead value���� 
		void getHead( T & outValue ){
			
			outValue = head->Value ;
			
		} // getHead()
		
		// �R������value �`�I 
		void del(){
			
			if( head == tail ) {
				delete head ;
				head = NULL ;
				tail = NULL ;
			} // if
			else {
				listNode *temp ;
				temp = head ;
				head = head->next ;
				delete temp ;
				temp = NULL ;
			} // else 
			
		} // delete()
		
		// �R������value�`�I�è��o��value 
		void del( T & outValue ) {
			

			outValue = head->value ;
			
			if( head == tail ) {
				delete head ;
				head = NULL ;
				tail = NULL ;
			} // if
			else {
				listNode *temp ;
				temp = head ;
				head = head->next ;
				delete temp ;
				temp = NULL ;
			} // else 
			
		} // del(outValue)
		
		// �Nlist�M�� 
		void clearUp(){
			for( listNode *temp = head ; temp != NULL ; temp = temp->next ) {
				head = head->next ;
				temp->next = NULL ;
				delete temp ;
				temp = head ;
			} // for
		} // clearUp()
		
		// ��ܩҦ�list����value 
		void show() {
			
			for( listNode *temp = head ; temp != NULL ; temp = temp->next ) {
				if( temp->next != NULL )
					cout << " " << temp->value << "," ;
				else
					cout << " " << temp->value ;
			} // for
			
		} // show()
		
		~expLIST(){
			while( !isEmpty() ) {
				del() ;
			} // while( !isEmpty ) 
		} // destuctor
		
}; // class expLIST

// T�i�b�ŧiexpSTACK�o��class��object�ɦA�w�q���Y��variable 
template <class T>
// ��@���|��class 
class expSTACK {
	
	private :
		// �Ψ��x�s���|�ҧΦ������ 
		struct stackNode {
			T value ;
			stackNode *next ;
		};
		
		// ���|�̤W�h����� 
		stackNode *topPtr ;
	
	public :
		
		expSTACK(): topPtr(NULL) {
		} // constructor
		
		// �T�{�����|�O�_���� 
		bool isEmpty() const {
			if( topPtr == NULL )
				return true ;
			else
				return false ;
		} // isEmpty()
		
		// �[�@�ӷs����ƶi�o��stack 
		void push(const T inValue ){
			try{
				stackNode *newNode = new stackNode ;
				newNode->value = inValue ;
				newNode->next = topPtr ;
				topPtr = newNode ;
			}//try
			catch( std::bad_alloc& ba) {
				
			 std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl ;
				// cout << endl ;
			} // catch
			
		} // push()
		
		// ���o��stack�����Ӹ�ƪ�value 
		void getTop( T & outValue ) {
			outValue = topPtr->value ;
		} // getTop()
		
		// �R����stack���Ӹ�� 
		void pop() {
			stackNode *temp = topPtr ;
			topPtr = topPtr->next ;
			delete temp ;
			temp = NULL ;
		} // pop()
		
		// �R����stack���Ӹ�ƨè��o��value 
		void pop( T & outValue ) {
			
			getTop(outValue) ;
			stackNode *temp = topPtr ;
			topPtr = topPtr->next ;
			delete temp ;
			temp = NULL ;
			
		} // pop(outValue)
		
		// ���stack�����x�s��value 
		void show() {
			
			for( stackNode *temp = topPtr ; temp != NULL ; temp = temp->next ) {
				if( temp->next != NULL )
					cout << " " << temp->value << "," ;
				else
					cout << " " << temp->value ;
			} // for
			
		} // show()
		
		~expSTACK() {
			while(!isEmpty())
				pop() ;
		} // destructor
		
};


// check the validity of each symbol
bool isExp( string& string ) {
	
	for( int i = 0 ; i < string.length() ; i = i + 1 ) {
		if ( (string[i] != '+' ) && ( string[i] != '-' ) && ( string[i] != '*' ) && ( string[i] != '/' ) 
				&& ( string[i] != '(' ) && ( string[i] != ')' ) && ( string[i] != ' ' ) ) {
				
			if ( ( ( string[i] < '0') || ( string[i] > '9' ) ) ) {
				cout << "Error 1: " << string[i] << " is not a legitimate character." << endl ;
				return false ;		
			} // if ( check digits )
				

		} // if( check symbols )
	} // for i
	
	return true ;
	
} // isExp()

// check the validity of balanced parentheses
bool isBalanced( const string string ) {
	
	expSTACK<char> aStack ;
	bool balanceNow = true ;
	
	for( int i = 0 ; ( i < string.length() ) && ( balanceNow == true ) ; i = i + 1 ) {
		
		if ( string[i] == '(' ) 
			aStack.push( string[i] ) ;

		else if ( string[i] == ')' ) {
			
			if( !aStack.isEmpty() )
				aStack.pop() ;
			else {
				balanceNow = false ;
			} // else 
		} // else if
		
	} // for i
	
	if( balanceNow && aStack.isEmpty() ) 
		return true ;
	else if ( !balanceNow ) {
		cout << "Error 2: there is one extra close parenthesis." << endl ;
		aStack.~expSTACK() ;
		return false ;
	} // else if
	else if ( !aStack.isEmpty() ){
		cout << "Error 2: there is one extra open parenthesis." << endl ;
		aStack.~expSTACK() ;
		return false ;
	} // else if 
	
} // isBalanced()


// �ư��ťէ�X�U�@�Ӧr�βŸ� 
int findNext( const string string, int index ) {
	
	index = index + 1 ;
	if ( index > string.length() - 1 )
		return -1 ;
		
	while( string[index] == ' ' ) {
		
		if ( index > string.length() - 1 )
			return -1 ;

		index = index + 1 ;
	} // while
	
	return index ;
	
} // findNext()

// �ư��ťէ�X�W�@�Ӧr�βŸ� 
int findLast( const string string, int index ) {
	
	
	index = index - 1 ;
	if ( index < 0 )
		return -1 ;
		
	while( string[index] == ' ' ) {
		
		if ( index < 0 )
			return -1 ;

		index = index - 1 ;
	} // while
	
	return index ;
	
} // findNext()

// �T�{ch�O�_���Ʀr 
bool isDigit( char ch ) {
	
	if( ch >= '0' && ch <= '9' )
		return true ;
		
	return false ;
	
} // isDigit()

// �T�{ch�O�_���X�k�B���+-*/ 
bool isLegalOperator( char ch ) {
	
	if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' )
		return true ;
		
	return false ;
	
} // isLegalOperator()

// �T�{string�O�_���X�k�����Ǧ� 
bool isLegal( const string string ) {
// check head and tail operator
	int first = 0 ;
	int index ;
	
	if ( string[first] == ' ' )
		index = findNext( string, first ) ;
	else
		index = 0 ;

	if ( index == -1 ) {
		cout << "Error 3: there is one extra operator." << endl ;
		return false ;
	} // if ( index == -1 )
	else if ( string[index] == '*' || string[index] == '/' || string[index] == '+' || string[index] == '-' ) {
		cout << "Error 3: there is one extra operator." << endl ;
		return false ;
	} // if
	
	int thelast = string.length() - 1 ;
	
	if ( string[thelast] == ' ' )
		index = findLast( string, thelast ) ;
	else
		index = thelast ;
		
	if ( index == -1 ) {
		cout << "Error 3: there is one extra operator." << endl ;
		return false ;
	} // if ( index == -1 )	
	else if ( string[index] == '*' || string[index] == '/' || string[index] == '+' || string[index] == '-' ) {
		cout << "Error 3: there is one extra operator." << endl ;
		return false ;
	} // if

// for extra operand and extra operator 
	for( int i = 0 ; i < string.length() ; i = i + 1 ) {
		
		// extra operand
		if ( string[i] == '(' ) {
			int index = findLast( string, i ) ;
			if ( index != -1 ) {
				if ( isDigit( string[index]  ) ) {
					cout << "Error 3: there is one extra operand." << endl ;
					return false ;
				} // if
			} // if ( index != -1 )
			
			
			index = findNext( string, i ) ;
			if ( index != -1 ) {
				if( string[index] == ')' || isLegalOperator( string[index] ) ) {
					cout << "Error 3: it is not infix in the parentheses." << endl ;
					return false ;
				} // if( string[index] == ')' || isLegalOperator( string[index] ) )
			} // if ( index != -1 )
			
			
		} // if ( string[i] == '(' )
		
		if ( string[i] == ')' ) {
			int index = findNext( string, i ) ;
			if ( index != -1 ) {
				if ( isDigit( string[index]  ) ) {
					cout << "Error 3: there is one extra operand." << endl ;
					return false ;
				}
			} // if ( index != -1 )
			
			index = findLast( string, i ) ;
			if ( index != -1 ) {
				if( string[index] == '(' || isLegalOperator( string[index] ) ) {
					cout << "Error 3: it is not infix in the parentheses." << endl ;
					return false ;
				} // if( string[index] == ')' || isLegalOperator( string[index] ) )
			} // if ( index != -1 )
			
		} // if ( string[i] == ')' )
	
		// extra operator
		if ( isLegalOperator( string[i] ) ) {
			
			int index = findNext( string, i ) ;
			
			if ( index == -1 ) {
				cout << "Error 3: there is one extra operator." << endl ;
				return false ;
			} // if ( index == -1 )
			else {
				if ( isLegalOperator( string[index] ) ) {
					cout << "Error 3: there is one extra operator." << endl ;
					return false ;
				} // if ( isLegalOperator( string[index] ) )
			} // else
			
		} // if ( isLegalOperator( string[i] ) )
	

	} // for i

	return true ;
	
} // isLegal()

// �Nstring�r���ഫ��list���覡�x�s 
void str2list( string str, expLIST<string> &list ) {
	
	string NoSpace ;
	string tempN = "" ;
	string tempO = "" ;
	
	for( int i = 0 ; i < str.length() ; i = i + 1 ) {
		if( str[i] != ' ' ) {
			NoSpace = NoSpace + str[i] ;
		} // if( str[i] != ' ' )
	} // for i
	
	int j = 0 ;
	
	while( j < NoSpace.length() ) {
		
		if ( isDigit( NoSpace[j] ) ){
			
			tempN = tempN + NoSpace[j] ;
			while( isDigit( NoSpace[j+1] ) && j+1 < NoSpace.length() ) {
				
				j = j + 1 ;
				tempN = tempN + NoSpace[j] ;
				
			} // while
			
			list.append( tempN ) ;
			tempN = "" ;
			
		} // if
		
		else if ( isLegalOperator( NoSpace[j] ) || NoSpace[j] == '(' || NoSpace[j] == ')' ) {
			tempO = tempO + NoSpace[j] ;
			list.append( tempO ) ;
			tempO = "" ;
		} // if
		
		j = j + 1 ;
		
	} // while( j < str.length() )
	
	
	
	
} // str2list() 

// �Nlist�������Ǧ��ഫ����Ǧ� 
bool infix2postfix( expLIST<string> &infix, expLIST<string> &postfix ) {
	
	expSTACK<string> aStack ;
	string temp = "" ;
	string tempTop = "" ;	
	bool placed = false ;
	

	while( !infix.isEmpty() ) {
		infix.del(temp) ;

		if ( isDigit( temp[0] ) ) {
			postfix.append( temp ) ;	
		} // if
		
		else if ( temp[0] == '(' )
			aStack.push(temp) ;
			
		else if ( isLegalOperator( temp[0] ) ) {
			
			if ( aStack.isEmpty() ) {
				
				aStack.push(temp) ;
			} // if
			
			else {
				
				
				if ( temp[0] == '+' || temp[0] == '-' ) {
					
					aStack.getTop( tempTop ) ;
						
					while ( tempTop[0] != '(' && !aStack.isEmpty() ) {
						
						aStack.pop() ;
						postfix.append( tempTop ) ;
						
						if ( !aStack.isEmpty() ) {
							aStack.getTop( tempTop ) ;
						} // if ( !aStack.isEmpty() )
						
					} // while ( tempTop != '(' && !aStack.isEmpty() )
					
					aStack.push( temp ) ;
					
				} // if ( temp[0] == '+' || temp[0] == '-' )
				
				else if ( temp[0] == '*' || temp[0]  == '/' ) {
					aStack.getTop( tempTop ) ;
					
					while( !placed ) {
						
						if ( tempTop[0] == '+' || tempTop[0] == '-' || tempTop[0] == '(' ) {
							aStack.push(temp) ;
							placed = true ;
						} // if
						else if ( tempTop[0] == '*' || tempTop[0] == '/' ) {
							aStack.pop() ;
							postfix.append( tempTop ) ;
							
							if( aStack.isEmpty() || tempTop[0] == '(' ) {
								aStack.push(temp) ;
								placed = true ;
							} // if
						} // else if
						
						aStack.getTop( tempTop ) ;
					} // while
					
					
					placed = false ;
				} // else if
				
				
			} // else
			
		} // else if
		
		else if ( temp[0] == ')' ) {
			aStack.getTop(tempTop) ;

			while( tempTop[0] != '(' ) {
				postfix.append( tempTop ) ;
				aStack.pop() ;
				aStack.getTop(tempTop) ;
			} // while
			aStack.pop() ;
		} // else if


	} // while( !infix.isEmpty() )
//	cout<<endl ;
//    postfix.show() ;

	while( !aStack.isEmpty() ) {
		string tempX ;
		aStack.pop(tempX) ;
		postfix.append(tempX) ;
	} // while
	
	infix.~expLIST() ;
	aStack.~expSTACK() ; 
	
	return true ;
	
} // infix2postfix()






int main(void) {
	
	int command = 0 ;
	
	do {
	
		string infixS ;
		expLIST<string> postfixlist ;
		expLIST<string> strlist ;
		cout << endl << "* Arithmetic Expression Evaluator *" ; 
		cout << endl << "* 0. QUIT                         *" ; 
		cout << endl << "* 1. Infix2postfix Transformation *" ;
		cout << endl << "***********************************" ;  
		cout << endl << "Input a choice(0, 1): " ; 
		
		cin >> command ;
		
		cin.ignore( MAX_LEN, '\n' ) ;
		
		switch( command ) {
			
			case 0 :
				break ;
			
			case 1 :
				cout << endl << "Input an infix expression: " ;
				getline( cin, infixS ) ;
				
				// �T�{infixS�O�_���X�k���Ǧ� 
				if( isExp(infixS) && isBalanced(infixS) && isLegal( infixS ) ) {
					cout << "It is a legitimate infix expression." << endl ;
					str2list( infixS, strlist ) ;
					cout << "Postfix expression:" ;
					
					// �N���Ǧ��ഫ����Ǧ��æL�X 
					if ( infix2postfix( strlist, postfixlist ) ) {
						postfixlist.show() ;
						cout << endl ;
					} // if
					
					postfixlist.~expLIST() ;
					
				} // if (isExp)
			
				break ;
				
			default :
				cout << endl << "Command does not exist!" << endl ;
				break ;
			
		} // switch()
	} while( command != 0 ) ; // command 0 �|�ϵ{������ 
	
	system("pause") ;
	return 0 ;
	
} // main()
