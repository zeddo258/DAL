#include<string>
#include<cstdlib>
#include<iostream>
#include<new>


#define MAX_LEN 255


using namespace std ;


// T可在宣告expLIST這個class的object時再定義為某種variable 
template <class T>

//  expLIST用來儲存劃分好的中序式以及後序式 
class expLIST {
	
	private:

		// 儲存變數資料的節點 
		struct listNode {
			T value ;
			listNode *next ;
		};
	
		// 頭尾節點的pointer 
		listNode *head, *tail ;
	
	public:
		
		
		expLIST(): head(NULL), tail(NULL){  // constructor and initialize head, tail
		}

		// 確認此object的資料是否為空 
		bool isEmpty() const {
			if ( head == NULL )
				return true ;
			else 
				return false ;
			
			// return head == NULL
				
		} // isEmpty()
		
		// 加一個新的value節點進來這個list 
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
		
		// 取得head value的值 
		void getHead( T & outValue ){
			
			outValue = head->Value ;
			
		} // getHead()
		
		// 刪除首個value 節點 
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
		
		// 刪除首個value節點並取得其value 
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
		
		// 將list清空 
		void clearUp(){
			for( listNode *temp = head ; temp != NULL ; temp = temp->next ) {
				head = head->next ;
				temp->next = NULL ;
				delete temp ;
				temp = head ;
			} // for
		} // clearUp()
		
		// 顯示所有list中的value 
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

// T可在宣告expSTACK這個class的object時再定義為某種variable 
template <class T>
// 實作堆疊的class 
class expSTACK {
	
	private :
		// 用來儲存堆疊所形成的資料 
		struct stackNode {
			T value ;
			stackNode *next ;
		};
		
		// 堆疊最上層的資料 
		stackNode *topPtr ;
	
	public :
		
		expSTACK(): topPtr(NULL) {
		} // constructor
		
		// 確認此堆疊是否為空 
		bool isEmpty() const {
			if( topPtr == NULL )
				return true ;
			else
				return false ;
		} // isEmpty()
		
		// 加一個新的資料進這個stack 
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
		
		// 取得此stack的首個資料的value 
		void getTop( T & outValue ) {
			outValue = topPtr->value ;
		} // getTop()
		
		// 刪除此stack首個資料 
		void pop() {
			stackNode *temp = topPtr ;
			topPtr = topPtr->next ;
			delete temp ;
			temp = NULL ;
		} // pop()
		
		// 刪除此stack首個資料並取得其value 
		void pop( T & outValue ) {
			
			getTop(outValue) ;
			stackNode *temp = topPtr ;
			topPtr = topPtr->next ;
			delete temp ;
			temp = NULL ;
			
		} // pop(outValue)
		
		// 顯示stack中所儲存的value 
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


// 排除空白找出下一個字或符號 
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

// 排除空白找出上一個字或符號 
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

// 確認ch是否為數字 
bool isDigit( char ch ) {
	
	if( ch >= '0' && ch <= '9' )
		return true ;
		
	return false ;
	
} // isDigit()

// 確認ch是否為合法運算符+-*/ 
bool isLegalOperator( char ch ) {
	
	if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' )
		return true ;
		
	return false ;
	
} // isLegalOperator()

// 確認string是否為合法的中序式 
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

// 將string字串轉換成list的方式儲存 
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

// 將list中的中序式轉換為後序式 
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
				
				// 確認infixS是否為合法中序式 
				if( isExp(infixS) && isBalanced(infixS) && isLegal( infixS ) ) {
					cout << "It is a legitimate infix expression." << endl ;
					str2list( infixS, strlist ) ;
					cout << "Postfix expression:" ;
					
					// 將中序式轉換成後序式並印出 
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
	} while( command != 0 ) ; // command 0 會使程式停止 
	
	system("pause") ;
	return 0 ;
	
} // main()
